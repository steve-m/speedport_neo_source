/*
 * Perform PPPoE discovery
 *
 * Copyright (C) 2000-2001 by Roaring Penguin Software Inc.
 * Copyright (C) 2004 Marco d'Itri <md@linux.it>
 *
 * This program may be distributed according to the terms of the GNU
 * General Public License, version 2 or (at your option) any later version.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "pppoe.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_NETPACKET_PACKET_H
#include <netpacket/packet.h>
#elif defined(HAVE_LINUX_IF_PACKET_H)
#include <linux/if_packet.h>
#endif

#ifdef HAVE_NET_ETHERNET_H
#include <net/ethernet.h>
#endif

#ifdef HAVE_ASM_TYPES_H
#include <asm/types.h>
#endif

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_NET_IF_ARP_H
#include <net/if_arp.h>
#endif
//#ifdef __SC_BUILD__
#define __DEBUG__
#ifndef __DEBUG__
#define show_info(format, ...)
#else
void show_info(const char *format, ...)
{
    va_list args;
    FILE *fp;

    fp = fopen("/var/pppoe_discover.debug", "a+");

    if (!fp)
        return;

    va_start(args, format);
    vfprintf(fp, format, args);
    va_end(args);
    fclose(fp);

    return ;
}
#endif
//#endif
char *xstrdup(const char *s);
void usage(void);

void die(int status)
{
	exit(status);
}

/* Initialize frame types to RFC 2516 values.  Some broken peers apparently
   use different frame types... sigh... */

UINT16_t Eth_PPPOE_Discovery = ETH_PPPOE_DISCOVERY;
UINT16_t Eth_PPPOE_Session   = ETH_PPPOE_SESSION;

/**********************************************************************
*%FUNCTION: etherType
*%ARGUMENTS:
* packet -- a received PPPoE packet
*%RETURNS:
* ethernet packet type (see /usr/include/net/ethertypes.h)
*%DESCRIPTION:
* Checks the ethernet packet header to determine its type.
* We should only be receveing DISCOVERY and SESSION types if the BPF
* is set up correctly.  Logs an error if an unexpected type is received.
* Note that the ethernet type names come from "pppoe.h" and the packet
* packet structure names use the LINUX dialect to maintain consistency
* with the rest of this file.  See the BSD section of "pppoe.h" for
* translations of the data structure names.
***********************************************************************/
UINT16_t
etherType(PPPoEPacket *packet)
{
    UINT16_t type = (UINT16_t) ntohs(packet->ethHdr.h_proto);
    if (type != Eth_PPPOE_Discovery && type != Eth_PPPOE_Session) {
#ifdef __SC_BUILD__
	show_info("Invalid ether type 0x%x\n", type);
#else
	fprintf(stderr, "Invalid ether type 0x%x\n", type);
#endif
    }
    return type;
}

/**********************************************************************
*%FUNCTION: openInterface
*%ARGUMENTS:
* ifname -- name of interface
* type -- Ethernet frame type
* hwaddr -- if non-NULL, set to the hardware address
*%RETURNS:
* A raw socket for talking to the Ethernet card.  Exits on error.
*%DESCRIPTION:
* Opens a raw Ethernet socket
***********************************************************************/
int
openInterface(char const *ifname, UINT16_t type, unsigned char *hwaddr)
{
    int optval=1;
    int fd;
    struct ifreq ifr;
    int domain, stype;

#ifdef HAVE_STRUCT_SOCKADDR_LL
    struct sockaddr_ll sa;
#else
    struct sockaddr sa;
#endif

    memset(&sa, 0, sizeof(sa));

#ifdef HAVE_STRUCT_SOCKADDR_LL
    domain = PF_PACKET;
    stype = SOCK_RAW;
#else
    domain = PF_INET;
    stype = SOCK_PACKET;
#endif

    if ((fd = socket(domain, stype, htons(type))) < 0) {
	/* Give a more helpful message for the common error case */
	if (errno == EPERM) {
	    rp_fatal("Cannot create raw socket -- pppoe must be run as root.");
	}
	fatalSys("socket");
    }

    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)) < 0) {
	fatalSys("setsockopt");
    }

    /* Fill in hardware address */
    if (hwaddr) {
	strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	if (ioctl(fd, SIOCGIFHWADDR, &ifr) < 0) {
	    fatalSys("ioctl(SIOCGIFHWADDR)");
	}
	memcpy(hwaddr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
#ifdef ARPHRD_ETHER
	if (ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER) {
	    char buffer[256];
	    sprintf(buffer, "Interface %.16s is not Ethernet", ifname);
	    rp_fatal(buffer);
	}
#endif
	if (NOT_UNICAST(hwaddr)) {
	    char buffer[256];
	    sprintf(buffer,
		    "Interface %.16s has broadcast/multicast MAC address??",
		    ifname);
	    rp_fatal(buffer);
	}
    }

    /* Sanity check on MTU */
    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
    if (ioctl(fd, SIOCGIFMTU, &ifr) < 0) {
	fatalSys("ioctl(SIOCGIFMTU)");
    }
    if (ifr.ifr_mtu < ETH_DATA_LEN) {
#ifdef __SC_BUILD__
	show_info("Interface %.16s has MTU of %d -- should be %d.\n",
	      ifname, ifr.ifr_mtu, ETH_DATA_LEN);
	show_info("You may have serious connection problems.\n");
#else
	fprintf(stderr, "Interface %.16s has MTU of %d -- should be %d.\n",
	      ifname, ifr.ifr_mtu, ETH_DATA_LEN);
	fprintf(stderr, "You may have serious connection problems.\n");
#endif
    }

#ifdef HAVE_STRUCT_SOCKADDR_LL
    /* Get interface index */
    sa.sll_family = AF_PACKET;
    sa.sll_protocol = htons(type);

    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
    if (ioctl(fd, SIOCGIFINDEX, &ifr) < 0) {
	fatalSys("ioctl(SIOCFIGINDEX): Could not get interface index");
    }
    sa.sll_ifindex = ifr.ifr_ifindex;

#else
    strcpy(sa.sa_data, ifname);
#endif

    /* We're only interested in packets on specified interface */
    if (bind(fd, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
	fatalSys("bind");
    }

    return fd;
}


/***********************************************************************
*%FUNCTION: sendPacket
*%ARGUMENTS:
* sock -- socket to send to
* pkt -- the packet to transmit
* size -- size of packet (in bytes)
*%RETURNS:
* 0 on success; -1 on failure
*%DESCRIPTION:
* Transmits a packet
***********************************************************************/
int
sendPacket(PPPoEConnection *conn, int sock, PPPoEPacket *pkt, int size)
{
#if defined(HAVE_STRUCT_SOCKADDR_LL)
    if (send(sock, pkt, size, 0) < 0) {
	sysErr("send (sendPacket)");
	return -1;
    }
#else
    struct sockaddr sa;

    if (!conn) {
	rp_fatal("relay and server not supported on Linux 2.0 kernels");
    }
    strcpy(sa.sa_data, conn->ifName);
    if (sendto(sock, pkt, size, 0, &sa, sizeof(sa)) < 0) {
	sysErr("sendto (sendPacket)");
	return -1;
    }
#endif
    return 0;
}

/***********************************************************************
*%FUNCTION: receivePacket
*%ARGUMENTS:
* sock -- socket to read from
* pkt -- place to store the received packet
* size -- set to size of packet in bytes
*%RETURNS:
* >= 0 if all OK; < 0 if error
*%DESCRIPTION:
* Receives a packet
***********************************************************************/
int
receivePacket(int sock, PPPoEPacket *pkt, int *size)
{
    if ((*size = recv(sock, pkt, sizeof(PPPoEPacket), 0)) < 0) {
	sysErr("recv (receivePacket)");
	return -1;
    }
    return 0;
}

/**********************************************************************
*%FUNCTION: parsePacket
*%ARGUMENTS:
* packet -- the PPPoE discovery packet to parse
* func -- function called for each tag in the packet
* extra -- an opaque data pointer supplied to parsing function
*%RETURNS:
* 0 if everything went well; -1 if there was an error
*%DESCRIPTION:
* Parses a PPPoE discovery packet, calling "func" for each tag in the packet.
* "func" is passed the additional argument "extra".
***********************************************************************/
int
parsePacket(PPPoEPacket *packet, ParseFunc *func, void *extra)
{
    UINT16_t len = ntohs(packet->length);
    unsigned char *curTag;
    UINT16_t tagType, tagLen;

  
    if (PPPOE_VER(packet->vertype) != 1) {
#ifdef __SC_BUILD__
	show_info("Invalid PPPoE version (%d)\n",
		PPPOE_VER(packet->vertype));
#else
	fprintf(stderr, "Invalid PPPoE version (%d)\n",
		PPPOE_VER(packet->vertype));
#endif
	return -1;
    }
    if (PPPOE_TYPE(packet->vertype) != 1) {
#ifdef __SC_BUILD__
	show_info("Invalid PPPoE type (%d)\n",
		PPPOE_TYPE(packet->vertype));
#else
	fprintf(stderr, "Invalid PPPoE type (%d)\n",
		PPPOE_TYPE(packet->vertype));
#endif
	return -1;
    }

    /* Do some sanity checks on packet */
    if (len > ETH_DATA_LEN - 6) { /* 6-byte overhead for PPPoE header */
#ifdef __SC_BUILD__
	show_info("Invalid PPPoE packet length (%u)\n", len);
#else
	fprintf(stderr, "Invalid PPPoE packet length (%u)\n", len);
#endif
	return -1;
    }

    /* Step through the tags */
    curTag = packet->payload;
    while(curTag - packet->payload < len) {
	/* Alignment is not guaranteed, so do this by hand... */
	tagType = (curTag[0] << 8) + curTag[1];
	tagLen = (curTag[2] << 8) + curTag[3];
	if (tagType == TAG_END_OF_LIST) {
	    return 0;
	}
	if ((curTag - packet->payload) + tagLen + TAG_HDR_SIZE > len) {
#ifdef __SC_BUILD__
	    show_info("Invalid PPPoE tag length (%u)\n", tagLen);
#else
		fprintf(stderr, "Invalid PPPoE tag length (%u)\n", tagLen);
#endif
	    return -1;
	}
	func(tagType, tagLen, curTag+TAG_HDR_SIZE, extra);
	curTag = curTag + TAG_HDR_SIZE + tagLen;
    }
    return 0;
}

/**********************************************************************
*%FUNCTION: parseForHostUniq
*%ARGUMENTS:
* type -- tag type
* len -- tag length
* data -- tag data.
* extra -- user-supplied pointer.  This is assumed to be a pointer to int.
*%RETURNS:
* Nothing
*%DESCRIPTION:
* If a HostUnique tag is found which matches our PID, sets *extra to 1.
***********************************************************************/
void
parseForHostUniq(UINT16_t type, UINT16_t len, unsigned char *data,
		 void *extra)
{
    int *val = (int *) extra;
    if (type == TAG_HOST_UNIQ && len == sizeof(pid_t)) {
	pid_t tmp;
	memcpy(&tmp, data, len);
	if (tmp == getpid()) {
	    *val = 1;
	}
    }
}

/**********************************************************************
*%FUNCTION: packetIsForMe
*%ARGUMENTS:
* conn -- PPPoE connection info
* packet -- a received PPPoE packet
*%RETURNS:
* 1 if packet is for this PPPoE daemon; 0 otherwise.
*%DESCRIPTION:
* If we are using the Host-Unique tag, verifies that packet contains
* our unique identifier.
***********************************************************************/
int
packetIsForMe(PPPoEConnection *conn, PPPoEPacket *packet)
{
    int forMe = 0;

    /* If packet is not directed to our MAC address, forget it */
    if (memcmp(packet->ethHdr.h_dest, conn->myEth, ETH_ALEN)) return 0;

    /* If we're not using the Host-Unique tag, then accept the packet */
    if (!conn->useHostUniq) return 1;

    parsePacket(packet, parseForHostUniq, &forMe);
    return forMe;
}

/**********************************************************************
*%FUNCTION: parsePADOTags
*%ARGUMENTS:
* type -- tag type
* len -- tag length
* data -- tag data
* extra -- extra user data.  Should point to a PacketCriteria structure
*          which gets filled in according to selected AC name and service
*          name.
*%RETURNS:
* Nothing
*%DESCRIPTION:
* Picks interesting tags out of a PADO packet
***********************************************************************/
void
parsePADOTags(UINT16_t type, UINT16_t len, unsigned char *data,
	      void *extra)
{
    struct PacketCriteria *pc = (struct PacketCriteria *) extra;
    PPPoEConnection *conn = pc->conn;
    int i;
#ifdef __SC_BUILD__
    show_info("parsePADOTags:type=%s\n", type);
#endif
    switch(type) {
    case TAG_AC_NAME:
	pc->seenACName = 1;
#ifdef __SC_BUILD__
	show_info("Access-Concentrator: %.*s\n", (int) len, data);
	show_info("acName=%s, data=%s", conn->acName ? conn->acName : "", data);
    	int acNamePWildFlag = 0;
    	int acNameNWildFlag = 0; 
	unsigned char nameBuf[512] = {'\0'};	
	if(conn->acName)
	{
		unsigned char *p = conn->acName;
	        unsigned char *pBuf = nameBuf;
		if(*p == '!')
		{
			acNameNWildFlag = 1;
		}
		while(*p != '\0')
		{
		    if(*p == '*')
		    {
			acNamePWildFlag = 1;
		    }
		    if((*p != '!') && (*p != '*'))
		    {		
		    	*pBuf = *p;
			pBuf++;
		    }		
		    p++; 			
		}
	}
#endif
	if (conn->acName && len == strlen(conn->acName) &&
	    !strncmp((char *) data, conn->acName, len)) {
	    pc->acNameOK = 1;
	}
#ifdef __SC_BUILD__
	if(conn->acName)
	{
		if(acNameNWildFlag == 0 && acNamePWildFlag == 1)
		{
			if(NULL != strstr((char *) data, nameBuf))
			    pc->acNameOK = 1;		
		}
		else if(acNameNWildFlag == 1)
		{
			if(acNamePWildFlag == 1)
			{
				if(NULL == strstr((char *) data, nameBuf))
				    pc->acNameOK = 1;	
			}
			else
			{
				if(strncmp((char *) data, nameBuf, len - 1))
				    pc->acNameOK = 1;	
			}	
		}
	}
#endif
	break;
    case TAG_SERVICE_NAME:
	pc->seenServiceName = 1;
	if (len > 0) {
#ifdef __SC_BUILD__
	    show_info("Service-Name: %.*s\n", (int) len, data);
#else
		printf("       Service-Name: %.*s\n", (int) len, data);
#endif
	}
	if (conn->serviceName && len == strlen(conn->serviceName) &&
	    !strncmp((char *) data, conn->serviceName, len)) {
	    pc->serviceNameOK = 1;
	}
	break;
    case TAG_AC_COOKIE:
#ifdef __SC_BUILD__
	show_info("Got a cookie:");
#else
	printf("Got a cookie:");
#endif
	/* Print first 20 bytes of cookie */
	for (i=0; i<len && i < 20; i++) {
#ifdef __SC_BUILD__
	    show_info(" %02x", (unsigned) data[i]);
#else
		printf(" %02x", (unsigned) data[i]);
#endif
	}
#ifdef __SC_BUILD__
	if (i < len) show_info("...");
	show_info("\n");
#else
	if (i < len) printf("...");
		printf("\n");
#endif
	conn->cookie.type = htons(type);
	conn->cookie.length = htons(len);
	memcpy(conn->cookie.payload, data, len);
	break;
    case TAG_RELAY_SESSION_ID:
#ifdef __SC_BUILD__
	show_info("Got a Relay-ID:");
#else
	printf("Got a Relay-ID:");
#endif
	/* Print first 20 bytes of relay ID */
	for (i=0; i<len && i < 20; i++) {
#ifdef __SC_BUILD__
	    show_info(" %02x", (unsigned) data[i]);
#else
		printf(" %02x", (unsigned) data[i]);
#endif
	}
#ifdef __SC_BUILD__
	if (i < len) show_info("...");
	show_info("\n");
#else
	if (i < len) printf("...");
		printf("\n");
#endif
	conn->relayId.type = htons(type);
	conn->relayId.length = htons(len);
	memcpy(conn->relayId.payload, data, len);
	break;
    case TAG_SERVICE_NAME_ERROR:
#ifdef __SC_BUILD__
	show_info("Got a Service-Name-Error tag: %.*s\n", (int) len, data);
#else
	printf("Got a Service-Name-Error tag: %.*s\n", (int) len, data);
#endif
	break;
    case TAG_AC_SYSTEM_ERROR:
#ifdef __SC_BUILD__
	show_info("Got a System-Error tag: %.*s\n", (int) len, data);
#else
	printf("Got a System-Error tag: %.*s\n", (int) len, data);
#endif
	break;
    case TAG_GENERIC_ERROR:
#ifdef __SC_BUILD__
	show_info("Got a Generic-Error tag: %.*s\n", (int) len, data);
#else
	printf("Got a Generic-Error tag: %.*s\n", (int) len, data);
#endif
	break;
    }
}

/***********************************************************************
*%FUNCTION: sendPADI
*%ARGUMENTS:
* conn -- PPPoEConnection structure
*%RETURNS:
* Nothing
*%DESCRIPTION:
* Sends a PADI packet
***********************************************************************/
void
sendPADI(PPPoEConnection *conn)
{
    PPPoEPacket packet;
    unsigned char *cursor = packet.payload;
    PPPoETag *svc = (PPPoETag *) (&packet.payload);
    UINT16_t namelen = 0;
    UINT16_t plen;

    if (conn->serviceName) {
	namelen = (UINT16_t) strlen(conn->serviceName);
    }
    plen = TAG_HDR_SIZE + namelen;
    CHECK_ROOM(cursor, packet.payload, plen);

    /* Set destination to Ethernet broadcast address */
    memset(packet.ethHdr.h_dest, 0xFF, ETH_ALEN);
    memcpy(packet.ethHdr.h_source, conn->myEth, ETH_ALEN);

    packet.ethHdr.h_proto = htons(Eth_PPPOE_Discovery);
    packet.vertype = PPPOE_VER_TYPE(1, 1);
    packet.code = CODE_PADI;
    packet.session = 0;

    svc->type = TAG_SERVICE_NAME;
    svc->length = htons(namelen);
    CHECK_ROOM(cursor, packet.payload, namelen+TAG_HDR_SIZE);

    if (conn->serviceName) {
	memcpy(svc->payload, conn->serviceName, strlen(conn->serviceName));
    }
    cursor += namelen + TAG_HDR_SIZE;

    /* If we're using Host-Uniq, copy it over */
    if (conn->useHostUniq) {
	PPPoETag hostUniq;
	pid_t pid = getpid();
	hostUniq.type = htons(TAG_HOST_UNIQ);
	hostUniq.length = htons(sizeof(pid));
	memcpy(hostUniq.payload, &pid, sizeof(pid));
	CHECK_ROOM(cursor, packet.payload, sizeof(pid) + TAG_HDR_SIZE);
	memcpy(cursor, &hostUniq, sizeof(pid) + TAG_HDR_SIZE);
	cursor += sizeof(pid) + TAG_HDR_SIZE;
	plen += sizeof(pid) + TAG_HDR_SIZE;
    }

    packet.length = htons(plen);

    sendPacket(conn, conn->discoverySocket, &packet, (int) (plen + HDR_SIZE));
    if (conn->debugFile) {
	dumpPacket(conn->debugFile, &packet, "SENT");
	fprintf(conn->debugFile, "\n");
	fflush(conn->debugFile);
    }
}

/**********************************************************************
*%FUNCTION: waitForPADO
*%ARGUMENTS:
* conn -- PPPoEConnection structure
* timeout -- how long to wait (in seconds)
*%RETURNS:
* Nothing
*%DESCRIPTION:
* Waits for a PADO packet and copies useful information
***********************************************************************/
void
waitForPADO(PPPoEConnection *conn, int timeout)
{
    fd_set readable;
    int r;
    struct timeval tv;
    PPPoEPacket packet;
    int len;

    struct PacketCriteria pc;
    pc.conn          = conn;
    pc.acNameOK      = (conn->acName)      ? 0 : 1;
    pc.serviceNameOK = (conn->serviceName) ? 0 : 1;
    pc.seenACName    = 0;
    pc.seenServiceName = 0;
    conn->error = 0;
#ifdef __SC_BUILD__
    show_info("waitForPADO\n");

    show_info("conn->acName=%s\n",conn->acName);
#endif
    do {
	if (BPF_BUFFER_IS_EMPTY) {
	    tv.tv_sec = timeout;
	    tv.tv_usec = 0;
	
	    FD_ZERO(&readable);
	    FD_SET(conn->discoverySocket, &readable);

	    while(1) {
		r = select(conn->discoverySocket+1, &readable, NULL, NULL, &tv);
		if (r >= 0 || errno != EINTR) break;
	    }
	    if (r < 0) {
		perror("select (waitForPADO)");
		return;
	    }
	    if (r == 0) return;        /* Timed out */
	}
	
	/* Get the packet */
	receivePacket(conn->discoverySocket, &packet, &len);

	/* Check length */
	if (ntohs(packet.length) + HDR_SIZE > len) {
#ifdef __SC_BUILD__
	    show_info("Bogus PPPoE length field (%u)\n",
		   (unsigned int) ntohs(packet.length));
#else
 		fprintf(stderr, "Bogus PPPoE length field (%u)\n",
		   (unsigned int) ntohs(packet.length));
#endif
	    continue;
	}

#ifdef USE_BPF
	/* If it's not a Discovery packet, loop again */
	if (etherType(&packet) != Eth_PPPOE_Discovery) continue;
#endif

	if (conn->debugFile) {
	    dumpPacket(conn->debugFile, &packet, "RCVD");
	    fprintf(conn->debugFile, "\n");
	    fflush(conn->debugFile);
	}
	/* If it's not for us, loop again */
	if (!packetIsForMe(conn, &packet)) continue;

	if (packet.code == CODE_PADO) {
	    if (BROADCAST(packet.ethHdr.h_source)) {
#ifdef __SC_BUILD__
		show_info("Ignoring PADO packet from broadcast MAC address\n");
#else
		fprintf(stderr, "Ignoring PADO packet from broadcast MAC address\n");
#endif
		continue;
	    }
	    parsePacket(&packet, parsePADOTags, &pc);
	    if (conn->error)
		return;
	    if (!pc.seenACName) {
#ifdef __SC_BUILD__
		show_info("Ignoring PADO packet with no AC-Name tag\n");
#else
		fprintf(stderr, "Ignoring PADO packet with no AC-Name tag\n");
#endif
		continue;
	    }
	    if (!pc.seenServiceName) {
#ifdef __SC_BUILD__
		show_info("Ignoring PADO packet with no Service-Name tag\n");
#else
		fprintf(stderr, "Ignoring PADO packet with no Service-Name tag\n");
#endif
		continue;
	    }
	    conn->numPADOs++;
#ifdef __SC_BUILD__
	    show_info("--------------------------------------------------\n");
#else
		printf("--------------------------------------------------\n");
#endif
	    if (pc.acNameOK && pc.serviceNameOK) {
		memcpy(conn->peerEth, packet.ethHdr.h_source, ETH_ALEN);
		if (conn->printACNames) {
#ifdef __SC_BUILD__
		    show_info("AC-Ethernet-Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
			   (unsigned) conn->peerEth[0], 
			   (unsigned) conn->peerEth[1],
			   (unsigned) conn->peerEth[2],
			   (unsigned) conn->peerEth[3],
			   (unsigned) conn->peerEth[4],
			   (unsigned) conn->peerEth[5]);
#else
 			printf("AC-Ethernet-Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
			   (unsigned) conn->peerEth[0], 
			   (unsigned) conn->peerEth[1],
			   (unsigned) conn->peerEth[2],
			   (unsigned) conn->peerEth[3],
			   (unsigned) conn->peerEth[4],
			   (unsigned) conn->peerEth[5]);
#endif
		    continue;
		}
		conn->discoveryState = STATE_RECEIVED_PADO;
		break;
	    }
	}
    } while (conn->discoveryState != STATE_RECEIVED_PADO);
}

/**********************************************************************
*%FUNCTION: discovery
*%ARGUMENTS:
* conn -- PPPoE connection info structure
*%RETURNS:
* Nothing
*%DESCRIPTION:
* Performs the PPPoE discovery phase
***********************************************************************/
void
discovery(PPPoEConnection *conn)
{
    int padiAttempts = 0;
    int timeout = PADI_TIMEOUT;
#ifdef __SC_BUILD__
    show_info("discovery\n");
#endif
    conn->discoverySocket =
	openInterface(conn->ifName, Eth_PPPOE_Discovery, conn->myEth);

    do {
	padiAttempts++;
	if (padiAttempts > MAX_PADI_ATTEMPTS) {
#ifdef __SC_BUILD__
	    show_info("Timeout waiting for PADO packets\n");
#else
		fprintf(stderr, "Timeout waiting for PADO packets\n");
#endif
	    close(conn->discoverySocket);
	    conn->discoverySocket = -1;
	    return;
	}
	sendPADI(conn);
	conn->discoveryState = STATE_SENT_PADI;
	waitForPADO(conn, timeout);
    } while (!conn->numPADOs);
}

int main(int argc, char *argv[])
{
    int opt;
    PPPoEConnection *conn;

    conn = malloc(sizeof(PPPoEConnection));
    if (!conn)
	fatalSys("malloc");

    memset(conn, 0, sizeof(PPPoEConnection));

    while ((opt = getopt(argc, argv, "I:D:VUAS:C:h")) > 0) {
	switch(opt) {
	case 'S':
	    conn->serviceName = xstrdup(optarg);
	    break;
	case 'C':
	    conn->acName = xstrdup(optarg);
	    break;
	case 'U':
	    conn->useHostUniq = 1;
	    break;
	case 'D':
	    conn->debugFile = fopen(optarg, "w");
	    if (!conn->debugFile) {
#ifdef __SC_BUILD__
		show_info("Could not open %s: %s\n",
			optarg, strerror(errno));
#else
		fprintf(stderr, "Could not open %s: %s\n",
			optarg, strerror(errno));
#endif
		exit(1);
	    }
	    fprintf(conn->debugFile, "pppoe-discovery %s\n", RP_VERSION);
	    break;
	case 'I':
	    conn->ifName = xstrdup(optarg);
	    break;
	case 'A':
	    /* this is the default */
	    break;
	case 'V':
	case 'h':
	    usage();
	    exit(0);
	default:
	    usage();
	    exit(1);
	}
    }

    /* default interface name */
    if (!conn->ifName)
	conn->ifName = strdup("eth0");

    conn->discoverySocket = -1;
    conn->sessionSocket = -1;
    conn->printACNames = 1;

    discovery(conn);
    exit(0);
}

void rp_fatal(char const *str)
{
#ifdef __SC_BUILD__
    show_info("%s\n", str);
#else
	fprintf(stderr, "%s\n", str);
#endif
    exit(1);
}

void fatalSys(char const *str)
{
    perror(str);
    exit(1);
}

void sysErr(char const *str)
{
    rp_fatal(str);
}

char *xstrdup(const char *s)
{
    register char *ret = strdup(s);
    if (!ret)
	sysErr("strdup");
    return ret;
}

void usage(void)
{

    fprintf(stderr, "Usage: pppoe-discovery [options]\n");
    fprintf(stderr, "\nVersion " RP_VERSION "\n");
}
