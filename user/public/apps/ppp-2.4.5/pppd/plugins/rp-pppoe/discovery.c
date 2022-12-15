/***********************************************************************
*
* discovery.c
*
* Perform PPPoE discovery
*
* Copyright (C) 1999 by Roaring Penguin Software Inc.
*
***********************************************************************/

static char const RCSID[] =
"$Id: discovery.c,v 1.6 2008/06/15 04:35:50 paulus Exp $";

#define _GNU_SOURCE 1
#include "pppoe.h"
#include "pppd/pppd.h"

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef HAVE_SYS_UIO_H
#include <sys/uio.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef USE_LINUX_PACKET
#include <sys/ioctl.h>
#include <fcntl.h>
#endif

#include <signal.h>
#ifdef __SC_BUILD__
#include <syslog.h>
#include "log_api.h"

static int ac_name_flag=0;
#endif

#ifdef SC_DT_SUPPORT
static unsigned char hostuniq[ETH_ALEN];  
#endif

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
static void
parseForHostUniq(UINT16_t type, UINT16_t len, unsigned char *data,
		 void *extra)
{
    int *val = (int *) extra;
#ifdef SC_DT_SUPPORT
    if (type == TAG_HOST_UNIQ && len == ETH_ALEN) {
	if (memcmp(data, hostuniq, ETH_ALEN)==0) {
	    *val = 1;
	}
    }
#else
    if (type == TAG_HOST_UNIQ && len == sizeof(pid_t)) {
	pid_t tmp;
	memcpy(&tmp, data, len);
	if (tmp == getpid()) {
	    *val = 1;
	}
    }
#endif /* SC_DT_SUPPORT */
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
static int
packetIsForMe(PPPoEConnection *conn, PPPoEPacket *packet)
{
    int forMe = 0;
#if 0 //def SC_DT_DEBUG
       mybug("%s, %02x:%02x:%02x:%02x:%02x:%02x\n", __FUNCTION__, 
             packet->ethHdr.h_dest[0], packet->ethHdr.h_dest[1], packet->ethHdr.h_dest[2], 
             packet->ethHdr.h_dest[3], packet->ethHdr.h_dest[4], packet->ethHdr.h_dest[5]);
#endif
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
static void
parsePADOTags(UINT16_t type, UINT16_t len, unsigned char *data,
	      void *extra)
{
    struct PacketCriteria *pc = (struct PacketCriteria *) extra;
    PPPoEConnection *conn = pc->conn;
    int i;
#ifdef __SC_BUILD__
    char *tag_p=NULL;    
#endif
    switch(type) {
    case TAG_AC_NAME:
	pc->seenACName = 1;
#ifdef __SC_BUILD__
	if(len>0)
	{
    	tag_p=malloc(len+1);
    	if(tag_p)
    	{
    	    ac_name_flag=1;
    	    memset(tag_p, 0, len+1);
        	strncpy(tag_p, data, len);
//            syslog(LOG_INFO, "%s PPPoE of WAN %d, PADO is received, BRAS name is %s.", log_type_db[WAN_LOG], wanid, tag_p);
            free(tag_p);
        }
    }    
#endif
	if (conn->printACNames) {
	    info("Access-Concentrator: %.*s", (int) len, data);
	}
#ifdef __SC_BUILD__
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
	if (conn->serviceName && len == strlen(conn->serviceName) &&
	    !strncmp((char *) data, conn->serviceName, len)) {
	    pc->serviceNameOK = 1;
	}
	break;
    case TAG_AC_COOKIE:
	conn->cookie.type = htons(type);
	conn->cookie.length = htons(len);
	memcpy(conn->cookie.payload, data, len);
	break;
    case TAG_RELAY_SESSION_ID:
	conn->relayId.type = htons(type);
	conn->relayId.length = htons(len);
	memcpy(conn->relayId.payload, data, len);
	break;
    case TAG_SERVICE_NAME_ERROR:
	error("PADO: Service-Name-Error: %.*s", (int) len, data);
#ifdef SC_DT_SUPPORT
    {
        char buf[256];
        memcpy(buf, data, len);
        buf[len]='\0';
        syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0015, log_type_db[GENERAL_LOG], buf);
        sal_wan_set_con_error_log_code_t(wan_id, "R015");
    }
#endif
	conn->error = 1;
	break;
    case TAG_AC_SYSTEM_ERROR:
	error("PADO: System-Error: %.*s", (int) len, data);
	conn->error = 1;
	break;
    case TAG_GENERIC_ERROR:
	error("PADO: Generic-Error: %.*s", (int) len, data);
	conn->error = 1;
	break;
    }
}

/**********************************************************************
*%FUNCTION: parsePADSTags
*%ARGUMENTS:
* type -- tag type
* len -- tag length
* data -- tag data
* extra -- extra user data (pointer to PPPoEConnection structure)
*%RETURNS:
* Nothing
*%DESCRIPTION:
* Picks interesting tags out of a PADS packet
***********************************************************************/
static void
parsePADSTags(UINT16_t type, UINT16_t len, unsigned char *data,
	      void *extra)
{
    PPPoEConnection *conn = (PPPoEConnection *) extra;
    switch(type) {
    case TAG_SERVICE_NAME:
	dbglog("PADS: Service-Name: '%.*s'", (int) len, data);
	break;
    case TAG_SERVICE_NAME_ERROR:
	error("PADS: Service-Name-Error: %.*s", (int) len, data);
	conn->error = 1;
	break;
    case TAG_AC_SYSTEM_ERROR:
	error("PADS: System-Error: %.*s", (int) len, data);
	conn->error = 1;
	break;
    case TAG_GENERIC_ERROR:
	error("PADS: Generic-Error: %.*s", (int) len, data);
	conn->error = 1;
	break;
    case TAG_RELAY_SESSION_ID:
	conn->relayId.type = htons(type);
	conn->relayId.length = htons(len);
	memcpy(conn->relayId.payload, data, len);
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
static void
sendPADI(PPPoEConnection *conn)
{
    PPPoEPacket packet;
    unsigned char *cursor = packet.payload;
    PPPoETag *svc = (PPPoETag *) (&packet.payload);
    UINT16_t namelen = 0;
    UINT16_t plen;
    int omit_service_name = 0;
 
    if (conn->serviceName) {
	namelen = (UINT16_t) strlen(conn->serviceName);
	if (!strcmp(conn->serviceName, "NO-SERVICE-NAME-NON-RFC-COMPLIANT")) {
	    omit_service_name = 1;
	}
    }

    /* Set destination to Ethernet broadcast address */
    memset(packet.ethHdr.h_dest, 0xFF, ETH_ALEN);
    memcpy(packet.ethHdr.h_source, conn->myEth, ETH_ALEN);

    packet.ethHdr.h_proto = htons(Eth_PPPOE_Discovery);
    packet.vertype = PPPOE_VER_TYPE(1, 1);
    packet.code = CODE_PADI;
    packet.session = 0;

    if (!omit_service_name) {
	plen = TAG_HDR_SIZE + namelen;
	CHECK_ROOM(cursor, packet.payload, plen);

	svc->type = TAG_SERVICE_NAME;
	svc->length = htons(namelen);

	if (conn->serviceName) {
	    memcpy(svc->payload, conn->serviceName, strlen(conn->serviceName));
	}
	cursor += namelen + TAG_HDR_SIZE;
    } else {
	plen = 0;
    }

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
#ifdef __SC_BUILD__
//    syslog(LOG_INFO, "%s PPPoE of WAN %d, PADI is sent.", log_type_db[WAN_LOG], wanid);
#endif
}

#ifdef SC_DT_SUPPORT
/***********************************************************************
*%FUNCTION: scSendPADI
*%ARGUMENTS:
* conn -- PPPoEConnection structure
*%RETURNS:
* Nothing
*%DESCRIPTION:
* Sends a PADI packet
***********************************************************************/
static void
scSendPADI(PPPoEConnection *conn)
{
    PPPoEPacket packet;
    unsigned char *cursor = packet.payload;
    PPPoETag *svc = (PPPoETag *) (&packet.payload);
    UINT16_t namelen = 0;
    UINT16_t plen;
    int omit_service_name = 0;
    
    //warn("<%s>********** %s **********\n", __FUNCTION__, (conn->method==1)?"1st":"2nd");
    if (conn->serviceName) {
	namelen = (UINT16_t) strlen(conn->serviceName);
	if (!strcmp(conn->serviceName, "NO-SERVICE-NAME-NON-RFC-COMPLIANT")) {
	    omit_service_name = 1;
	}
    }

    /* Set destination to Ethernet broadcast address */
    memset(packet.ethHdr.h_dest, 0xFF, ETH_ALEN);
    memcpy(packet.ethHdr.h_source, conn->myEth, ETH_ALEN);

    packet.ethHdr.h_proto = htons(Eth_PPPOE_Discovery);
    packet.vertype = PPPOE_VER_TYPE(1, 1);
    packet.code = CODE_PADI;
    packet.session = 0;

    if (!omit_service_name) {
	plen = TAG_HDR_SIZE + namelen;
	CHECK_ROOM(cursor, packet.payload, plen);

	svc->type = TAG_SERVICE_NAME;
	svc->length = htons(namelen);

	if (conn->serviceName) {
	    memcpy(svc->payload, conn->serviceName, strlen(conn->serviceName));
	}
	cursor += namelen + TAG_HDR_SIZE;
    } else {
	plen = 0;
    }

    /* If we're using Host-Uniq, copy it over */
    if (conn->useHostUniq) {
	PPPoETag hostUniq;
	hostUniq.type = htons(TAG_HOST_UNIQ);
	hostUniq.length = ETH_ALEN;
	memcpy(hostUniq.payload, conn->myEth, ETH_ALEN);
        /* backup hostuniq for parse next step */
        memcpy(hostuniq, conn->myEth, ETH_ALEN);
	CHECK_ROOM(cursor, packet.payload, ETH_ALEN + TAG_HDR_SIZE);
	memcpy(cursor, &hostUniq, ETH_ALEN + TAG_HDR_SIZE);
	cursor += ETH_ALEN + TAG_HDR_SIZE;
	plen += ETH_ALEN + TAG_HDR_SIZE;
    }

    packet.length = htons(plen);

    if(conn->method == SC_TAGGED_IF)
    {
        sendPacket(conn, conn->discoverySocket, &packet, (int) (plen + HDR_SIZE));
#ifdef SC_DT_DEBUG
        mybug("%s, send PADI with main ifname\n", __FUNCTION__);
#endif
    }
    else
    {
        sendPacket(conn, conn->discoveryUntagSocket, &packet, (int) (plen + HDR_SIZE));
#ifdef SC_DT_DEBUG
        mybug("%s, send PADI with second ifname\n", __FUNCTION__);
#endif
    }
#ifdef __SC_BUILD__
    //PADI is send
    syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R101, log_type_db[GENERAL_LOG]);
#endif
}
#endif /* SC_DT_SUPPORT */

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
		error("select (waitForPADO): %m");
		return;
	    }
	    if (r == 0) return;        /* Timed out */
	}

	/* Get the packet */
	receivePacket(conn->discoverySocket, &packet, &len);

	/* Check length */
	if (ntohs(packet.length) + HDR_SIZE > len) {
	    error("Bogus PPPoE length field (%u)",
		   (unsigned int) ntohs(packet.length));
	    continue;
	}

#ifdef USE_BPF
	/* If it's not a Discovery packet, loop again */
	if (etherType(&packet) != Eth_PPPOE_Discovery) continue;
#endif

	/* If it's not for us, loop again */
	if (!packetIsForMe(conn, &packet)) continue;

	if (packet.code == CODE_PADO) {
	    if (NOT_UNICAST(packet.ethHdr.h_source)) {
		error("Ignoring PADO packet from non-unicast MAC address");
		continue;
	    }
	    if (conn->req_peer
		&& memcmp(packet.ethHdr.h_source, conn->req_peer_mac, ETH_ALEN) != 0) {
		warn("Ignoring PADO packet from wrong MAC address");
		continue;
	    }
	    if (parsePacket(&packet, parsePADOTags, &pc) < 0)
		return;
#ifdef __SC_BUILD__
//		if(ac_name_flag==0)
//		    syslog(LOG_INFO, "%s PPPoE of WAN %d, PADO is received, BRAS name is NULL.", log_type_db[WAN_LOG], wanid);
#endif
	    if (conn->error)
		return;
	    if (!pc.seenACName) {
		error("Ignoring PADO packet with no AC-Name tag");
		continue;
	    }
	    if (!pc.seenServiceName) {
		error("Ignoring PADO packet with no Service-Name tag");
		continue;
	    }
	    conn->numPADOs++;
	    if (pc.acNameOK && pc.serviceNameOK) {
#ifdef __SC_BUILD__
		static unsigned char buf[64];
		int len = sizeof(buf);
#endif
		memcpy(conn->peerEth, packet.ethHdr.h_source, ETH_ALEN);
#ifdef __SC_BUILD__
		if(0 == getTagValueFromPacket(&packet, TAG_SERVICE_NAME, buf, &len))
		{
			/*Martin Huang:Trick service name*/
			if(NULL == conn->serviceName)
				conn->serviceName = buf;			
		}
#endif
                conn->discoveryState = STATE_RECEIVED_PADO;
		break;
	    }
	}
    } while (conn->discoveryState != STATE_RECEIVED_PADO);
}

#ifdef SC_DT_SUPPORT
static int scBackupPreferredMethod(int method)
{
    FILE *fp=NULL;
    char buf[32];
    int cur_method=1;

    fp = fopen("/mnt/appdat/poe_method", "r");
    if(fp)
    {
        fread(buf, 1, sizeof(buf), fp);
        if(strncmp(buf, "0", 1)==0)
            cur_method = 0;     
        fclose(fp); 
    
        if(method==cur_method)
            return 1;
    }

    if(method==SC_TAGGED_IF)
    {
        system("echo 1 > /mnt/appdat/poe_method");
    }
    else
    {
        system("echo 0 > /mnt/appdat/poe_method");
    }
    
    return 0;
}
/**********************************************************************
*%FUNCTION: scWaitForPADO
*%ARGUMENTS:
* conn -- PPPoEConnection structure
* timeout -- how long to wait (in seconds)
*%RETURNS:
* Nothing
*%DESCRIPTION:
* Waits for a PADO packet and copies useful information
***********************************************************************/
void
scWaitForPADO(PPPoEConnection *conn, int timeout)
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

    do {
	if (BPF_BUFFER_IS_EMPTY) {
	    tv.tv_sec = timeout;
	    tv.tv_usec = 0;

	    FD_ZERO(&readable);
	    FD_SET((conn->method==SC_TAGGED_IF)?conn->discoverySocket:conn->discoveryUntagSocket, &readable);

	    while(1) {
		r = select((conn->method==SC_TAGGED_IF)?conn->discoverySocket+1:conn->discoveryUntagSocket+1, &readable, NULL, NULL, &tv);
		if (r >= 0 || errno != EINTR) break;
	    }
	    if (r < 0) {
		error("select (waitForPADO): %m");
		return;
	    }
	    if (r == 0) return;        /* Timed out */
	}

	/* Get the packet */
        if(conn->method==SC_TAGGED_IF)
            receivePacket(conn->discoverySocket, &packet, &len);
        else
	    receivePacket(conn->discoveryUntagSocket, &packet, &len);
#ifdef SC_DT_DEBUG
        mybug("%s, recv packet: interface %s\n", __FUNCTION__, (conn->method==SC_TAGGED_IF)?"main":"second");
#endif
	/* Check length */
	if (ntohs(packet.length) + HDR_SIZE > len) {
	    error("Bogus PPPoE length field (%u)",
		   (unsigned int) ntohs(packet.length));
#ifdef SC_DT_SUPPORT
        syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0016, log_type_db[GENERAL_LOG], "");
        sal_wan_set_con_error_log_code_t(wan_id, "R016");
#endif
	    continue;
	}
#ifdef SC_DT_DEBUG
        mybug("%s, recv packet: check length pass, type:%04x\n", __FUNCTION__, etherType(&packet));
#endif
#ifdef USE_BPF
	/* If it's not a Discovery packet, loop again */
	if (etherType(&packet) != Eth_PPPOE_Discovery) continue;
#endif
#ifdef SC_DT_DEBUG
        mybug("%s, recv packet: check pppoe type pass\n", __FUNCTION__);
#endif
	/* If it's not for us, loop again */
	if (!packetIsForMe(conn, &packet)) continue;
#ifdef SC_DT_DEBUG
       mybug("%s, recv ppp discovery packet for me\n", __FUNCTION__);
#endif
	if (packet.code == CODE_PADO) {
	    if (NOT_UNICAST(packet.ethHdr.h_source)) {
		error("Ignoring PADO packet from non-unicast MAC address");
#ifdef SC_DT_SUPPORT
        syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0016, log_type_db[GENERAL_LOG], "PADO packet from non-unicast MAC address");
        sal_wan_set_con_error_log_code_t(wan_id, "R016");
#endif
		continue;
	    }
	    if (conn->req_peer
		&& memcmp(packet.ethHdr.h_source, conn->req_peer_mac, ETH_ALEN) != 0) {
		warn("Ignoring PADO packet from wrong MAC address");
#ifdef SC_DT_SUPPORT
        syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0016, log_type_db[GENERAL_LOG], "PADO packet from wrong MAC address");
        sal_wan_set_con_error_log_code_t(wan_id, "R016");
#endif
		continue;
	    }
	    if (parsePacket(&packet, parsePADOTags, &pc) < 0)
		return;
#ifdef __SC_BUILD__
//		if(ac_name_flag==0)
//		    syslog(LOG_INFO, "%s PPPoE of WAN %d, PADO is received, BRAS name is NULL.", log_type_db[WAN_LOG], wanid);
#endif
	    if (conn->error)
		return;
	    if (!pc.seenACName) {
		error("Ignoring PADO packet with no AC-Name tag");
		continue;
	    }
	    if (!pc.seenServiceName) {
		error("Ignoring PADO packet with no Service-Name tag");
		continue;
	    }
	    conn->numPADOs++;
#ifdef SC_DT_DEBUG
            mybug("%s, recv valid PADO packet\n", __FUNCTION__);
#endif
	    if (pc.acNameOK && pc.serviceNameOK) {
#ifdef __SC_BUILD__
		static unsigned char buf[64];
		int len = sizeof(buf);
#endif
		memcpy(conn->peerEth, packet.ethHdr.h_source, ETH_ALEN);
#ifdef __SC_BUILD__
		if(0 == getTagValueFromPacket(&packet, TAG_SERVICE_NAME, buf, &len))
		{
			/*Martin Huang:Trick service name*/
			if(NULL == conn->serviceName)
				conn->serviceName = buf;			
		}
#endif
                /* fix poe socket and ifname after PADO received */
                if(conn->method!=SC_TAGGED_IF) //means will be use untagged socket at next stage always
                {
                    /* backup discoverySocket for free in future */
                    conn->discoveryBackupSocket = conn->discoverySocket;
                    
                    conn->discoverySocket = conn->discoveryUntagSocket;
                    conn->ifName = conn->untagIfName;
                    
                    if(conn->discoveryBackupSocket >=0)
                    {
                        close(conn->discoveryBackupSocket);
                        conn->discoveryBackupSocket = -1;
                        conn->discoveryUntagSocket = -1;
                    }
                }
                else
                {
                    if(conn->discoveryUntagSocket >=0)
                    {
                        close(conn->discoveryUntagSocket);
                        conn->discoveryUntagSocket = -1;
                        conn->discoveryBackupSocket = -1;
                    }
                }
                /* store method method to cal for poe reconn next time */
                scBackupPreferredMethod(conn->method);
                //PADO is received
                syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R102, log_type_db[GENERAL_LOG]);
		conn->discoveryState = STATE_RECEIVED_PADO;
		break;
	    }
	}
    } while (conn->discoveryState != STATE_RECEIVED_PADO);
}
#endif /* SC_DT_SUPPORT */

/***********************************************************************
*%FUNCTION: sendPADR
*%ARGUMENTS:
* conn -- PPPoE connection structur
*%RETURNS:
* Nothing
*%DESCRIPTION:
* Sends a PADR packet
***********************************************************************/
static void
sendPADR(PPPoEConnection *conn)
{
    PPPoEPacket packet;
    PPPoETag *svc = (PPPoETag *) packet.payload;
    unsigned char *cursor = packet.payload;

    UINT16_t namelen = 0;
    UINT16_t plen;

    if (conn->serviceName) {
	namelen = (UINT16_t) strlen(conn->serviceName);
    }
    plen = TAG_HDR_SIZE + namelen;
    CHECK_ROOM(cursor, packet.payload, plen);

    memcpy(packet.ethHdr.h_dest, conn->peerEth, ETH_ALEN);
    memcpy(packet.ethHdr.h_source, conn->myEth, ETH_ALEN);

    packet.ethHdr.h_proto = htons(Eth_PPPOE_Discovery);
    packet.vertype = PPPOE_VER_TYPE(1, 1);
    packet.code = CODE_PADR;
    packet.session = 0;

    svc->type = TAG_SERVICE_NAME;
    svc->length = htons(namelen);
    if (conn->serviceName) {
	memcpy(svc->payload, conn->serviceName, namelen);
    }
    cursor += namelen + TAG_HDR_SIZE;

    /* If we're using Host-Uniq, copy it over */
    if (conn->useHostUniq) {
	PPPoETag hostUniq;
#ifdef SC_DT_SUPPORT
	hostUniq.type = htons(TAG_HOST_UNIQ);
	hostUniq.length = ETH_ALEN;
	memcpy(hostUniq.payload, conn->myEth, ETH_ALEN);
	CHECK_ROOM(cursor, packet.payload, ETH_ALEN + TAG_HDR_SIZE);
	memcpy(cursor, &hostUniq, ETH_ALEN + TAG_HDR_SIZE);
	cursor += ETH_ALEN + TAG_HDR_SIZE;
	plen += ETH_ALEN + TAG_HDR_SIZE;
#else
	pid_t pid = getpid();
	hostUniq.type = htons(TAG_HOST_UNIQ);
	hostUniq.length = htons(sizeof(pid));
	memcpy(hostUniq.payload, &pid, sizeof(pid));
	CHECK_ROOM(cursor, packet.payload, sizeof(pid)+TAG_HDR_SIZE);
	memcpy(cursor, &hostUniq, sizeof(pid) + TAG_HDR_SIZE);
	cursor += sizeof(pid) + TAG_HDR_SIZE;
	plen += sizeof(pid) + TAG_HDR_SIZE;
#endif
    }

    /* Copy cookie and relay-ID if needed */
    if (conn->cookie.type) {
	CHECK_ROOM(cursor, packet.payload,
		   ntohs(conn->cookie.length) + TAG_HDR_SIZE);
	memcpy(cursor, &conn->cookie, ntohs(conn->cookie.length) + TAG_HDR_SIZE);
	cursor += ntohs(conn->cookie.length) + TAG_HDR_SIZE;
	plen += ntohs(conn->cookie.length) + TAG_HDR_SIZE;
    }

    if (conn->relayId.type) {
	CHECK_ROOM(cursor, packet.payload,
		   ntohs(conn->relayId.length) + TAG_HDR_SIZE);
	memcpy(cursor, &conn->relayId, ntohs(conn->relayId.length) + TAG_HDR_SIZE);
	cursor += ntohs(conn->relayId.length) + TAG_HDR_SIZE;
	plen += ntohs(conn->relayId.length) + TAG_HDR_SIZE;
    }

    packet.length = htons(plen);
    sendPacket(conn, conn->discoverySocket, &packet, (int) (plen + HDR_SIZE));
#ifdef __SC_BUILD__
    //PADR is send
    syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R103, log_type_db[GENERAL_LOG]);
#endif
}
#ifdef __SC_BUILD__
/**********************************************************************
*%FUNCTION: waitForPADT
*%ARGUMENTS:
* conn -- PPPoE connection info
* timeout -- how long to wait (in seconds)
*%RETURNS:
* Nothing
*%DESCRIPTION:
* Waits for a PADT packet and copies useful information
***********************************************************************/
void
waitForPADT(PPPoEConnection *conn, int timeout)
{
    fd_set readable;
    int r;
    struct timeval tv;
    PPPoEPacket packet;
    int len;

    conn->error = 0;
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
		error("select (waitForPADS): %m");
		return;
	    }
	    if (r == 0) return;
	}

	/* Get the packet */
	receivePacket(conn->discoverySocket, &packet, &len);

	/* Check length */
	if (ntohs(packet.length) + HDR_SIZE > len) {
	    error("Bogus PPPoE length field (%u)",
		   (unsigned int) ntohs(packet.length));
#ifdef SC_DT_SUPPORT
        syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0016, log_type_db[GENERAL_LOG], "");
        sal_wan_set_con_error_log_code_t(wan_id, "R016");
#endif
	    continue;
	}

#ifdef USE_BPF
	/* If it's not a Discovery packet, loop again */
	if (etherType(&packet) != Eth_PPPOE_Discovery) continue;
#endif

	/* If it's not from the AC, it's not for me */
	if (memcmp(packet.ethHdr.h_source, conn->peerEth, ETH_ALEN)) continue;

	/* If it's not for us, loop again */
	if (!packetIsForMe(conn, &packet)) continue;

	/* Is it PADS?  */
	if (packet.code == CODE_PADT) {
	  if(packet.session == conn->session)
		return;
	    if (conn->error)
		return;
	    conn->discoveryState = STATE_TERMINATED;
        //PADT is received
	    syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R105, log_type_db[GENERAL_LOG]);
	    break;
	}
    } while (conn->discoveryState != STATE_TERMINATED);
}
#endif

/**********************************************************************
*%FUNCTION: waitForPADS
*%ARGUMENTS:
* conn -- PPPoE connection info
* timeout -- how long to wait (in seconds)
*%RETURNS:
* Nothing
*%DESCRIPTION:
* Waits for a PADS packet and copies useful information
***********************************************************************/
static void
waitForPADS(PPPoEConnection *conn, int timeout)
{
    fd_set readable;
    int r;
    struct timeval tv;
    PPPoEPacket packet;
    int len;

    conn->error = 0;
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
		error("select (waitForPADS): %m");
		return;
	    }
	    if (r == 0) return;
	}

	/* Get the packet */
	receivePacket(conn->discoverySocket, &packet, &len);

	/* Check length */
	if (ntohs(packet.length) + HDR_SIZE > len) {
	    error("Bogus PPPoE length field (%u)",
		   (unsigned int) ntohs(packet.length));
#ifdef SC_DT_SUPPORT
        syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0016, log_type_db[GENERAL_LOG], "");
        sal_wan_set_con_error_log_code_t(wan_id, "R016");
#endif
	    continue;
	}

#ifdef USE_BPF
	/* If it's not a Discovery packet, loop again */
	if (etherType(&packet) != Eth_PPPOE_Discovery) continue;
#endif

	/* If it's not from the AC, it's not for me */
	
	if (memcmp(packet.ethHdr.h_source, conn->peerEth, ETH_ALEN)) 
#ifdef __SC_BUILD__
	{
	    if (packetIsForMe(conn, &packet) && packet.code == CODE_PADO) {
			/*Martin Huang:Send PADT for non-first PADO*/
			sendPADTFromClientForMultiBras(conn, packet.ethHdr.h_source);
		}
	//	
            continue;
	}
#else
		continue;
#endif
	/* If it's not for us, loop again */
	if (!packetIsForMe(conn, &packet)) continue;

	/* Is it PADS?  */
	if (packet.code == CODE_PADS) {
	    /* Parse for goodies */
	    if (parsePacket(&packet, parsePADSTags, conn) < 0)
		return;
	    if (conn->error)
		return;
	    conn->discoveryState = STATE_SESSION;
#ifdef __SC_BUILD__
        //PADS is received
	    syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R104, log_type_db[GENERAL_LOG]);
#endif
	    break;
	}
    } while (conn->discoveryState != STATE_SESSION);

    /* Don't bother with ntohs; we'll just end up converting it back... */
    conn->session = packet.session;

    info("PPP session is %d", (int) ntohs(conn->session));

    /* RFC 2516 says session id MUST NOT be zero or 0xFFFF */
    if (ntohs(conn->session) == 0 || ntohs(conn->session) == 0xFFFF) {
	error("Access concentrator used a session value of %x -- the AC is violating RFC 2516", (unsigned int) ntohs(conn->session));
    }
}

#ifdef SC_DT_SUPPORT
extern char    untagdevname[32];
extern bool    preferredmethod;
extern int     padi_timeout;
extern int     backoff_timer; 
#endif
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
    int padrAttempts = 0;
    int timeout = conn->discoveryTimeout;
#ifdef SC_DT_SUPPORT
    /* MK@PD2 reload ifName and untagIfName for fix mantis: 0030474 */
    conn->ifName = devnam;
    if(checkUntagDevname(untagdevname))
        conn->untagIfName = untagdevname;
    else
        conn->untagIfName = NULL;
#endif 
    conn->discoverySocket =
	openInterface(conn->ifName, Eth_PPPOE_Discovery, conn->myEth);
#ifdef SC_DT_SUPPORT   
    if(conn->untagIfName!=NULL)
        conn->discoveryUntagSocket =
    	    openInterface(conn->untagIfName, Eth_PPPOE_Discovery, conn->myEth);
#endif
 
    do {
	padiAttempts++;

#ifdef SC_DT_SUPPORT
	if (padiAttempts > MAX_PADI_ATTEMPTS) {
	    warn("Timeout waiting for PADO packets, sleep %d seconds to reset", backoff_timer<60?60:backoff_timer);
        syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0020, log_type_db[GENERAL_LOG], "waiting for PADO packets");
        sal_wan_set_con_error_log_code_t(wan_id, "R020");
            sal_wan_set_con_fail_code_t(wan_id,"Timeout");
            if(backoff_timer<60)
                backoff_timer = 60;
	    sleep(backoff_timer);
            padiAttempts = 0;
            continue;
	}
        if(padiAttempts == 1 || padiAttempts == 3
           || padiAttempts == 4 || padiAttempts == 7
           || padiAttempts == 8 || padiAttempts == 9
           || padiAttempts == 10)
        {
            conn->method = preferredmethod;                //send PADI with main interface
        }
        else
        {
            if(conn->untagIfName!=NULL && conn->discoveryUntagSocket!=-1)
                conn->method = (preferredmethod + 1)%2;    //send PADI with untagged interface
            else
                conn->method = preferredmethod;  
        }

        scSendPADI(conn);

	conn->discoveryState = STATE_SENT_PADI;
#ifdef __SC_BUILD__
	ac_name_flag=0;
#endif
        if(padi_timeout>60 || padi_timeout<1)
            padi_timeout = 3;
        scWaitForPADO(conn, padi_timeout);

#else /* SC_DT_SUPPORT */

	if (padiAttempts > MAX_PADI_ATTEMPTS) {
	    warn("Timeout waiting for PADO packets");
	    close(conn->discoverySocket);
	    conn->discoverySocket = -1;
	    return;
	}
	sendPADI(conn);
	conn->discoveryState = STATE_SENT_PADI;
#ifdef __SC_BUILD__
	ac_name_flag=0;
#endif
	waitForPADO(conn, timeout);

	timeout *= 2;
#endif /* SC_DT_SUPPORT */
    } while (conn->discoveryState == STATE_SENT_PADI);
#ifdef SC_DT_DEBUG
    mybug("%s, ready to send PADR packet\n", __FUNCTION__);
#endif
    timeout = conn->discoveryTimeout;
    do {
	padrAttempts++;
	if (padrAttempts > MAX_PADR_ATTEMPTS) {
	    warn("Timeout waiting for PADS packets");
	    close(conn->discoverySocket);
	    conn->discoverySocket = -1;
	    return;
	}
	sendPADR(conn);
	conn->discoveryState = STATE_SENT_PADR;
	waitForPADS(conn, timeout);

#if 0 //def __SC_BUILD__
	if(padrAttempts == MAX_PADI_ATTEMPTS)
	{
		/*Martin Huang:Give PPPoe server the last chance:maybe we could be lucky*/
		sendPADR(conn);
		conn->discoveryState = STATE_SENT_PADR;
		waitForPADS(conn, conn->discoveryTimeout);
	}
	timeout += conn->discoveryTimeout;
#else
	timeout *= 2;
#endif

    } while (conn->discoveryState == STATE_SENT_PADR);

    /* We're done. */
    conn->discoveryState = STATE_SESSION;
    return;
}
