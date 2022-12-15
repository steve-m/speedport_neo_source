/***********************************************************************
*
* plugin.c
*
* pppd plugin for kernel-mode PPPoE on Linux
*
* Copyright (C) 2001 by Roaring Penguin Software Inc., Michal Ostrowski
* and Jamal Hadi Salim.
*
* Much code and many ideas derived from pppoe plugin by Michal
* Ostrowski and Jamal Hadi Salim, which carries this copyright:
*
* Copyright 2000 Michal Ostrowski <mostrows@styx.uwaterloo.ca>,
*                Jamal Hadi Salim <hadi@cyberus.ca>
* Borrows heavily from the PPPoATM plugin by Mitchell Blank Jr.,
* which is based in part on work from Jens Axboe and Paul Mackerras.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version
* 2 of the License, or (at your option) any later version.
*
***********************************************************************/

static char const RCSID[] =
"$Id: plugin.c,v 1.17 2008/06/15 04:35:50 paulus Exp $";

#define _GNU_SOURCE 1
#include "pppoe.h"

#include "pppd/pppd.h"
#include "pppd/fsm.h"
#include "pppd/lcp.h"
#include "pppd/ipcp.h"
#include "pppd/ccp.h"
/* #include "pppd/pathnames.h" */

#include <linux/types.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <linux/ppp_defs.h>
#include <linux/if_ppp.h>
#include <linux/if_pppox.h>

#ifndef _ROOT_PATH
#define _ROOT_PATH ""
#endif
#ifdef __SC_BUILD__
#include <sal/sal_wan.h>
#define _PATH_ETHOPT         _ROOT_PATH "/tmp/ppp/options."
#else
#define _PATH_ETHOPT         _ROOT_PATH "/etc/ppp/options."
#endif

char pppd_version[] = VERSION;

/* From sys-linux.c in pppd -- MUST FIX THIS! */
extern int new_style_driver;

char *pppd_pppoe_service = NULL;
#ifdef __SC_BUILD__
char *acName = NULL;
char *existingSession = NULL;
int printACNames = 0;
char *pppoe_reqd_mac = NULL;
int wanid = 0;
#else
static char *acName = NULL;
static char *existingSession = NULL;
static int printACNames = 0;
static char *pppoe_reqd_mac = NULL;
#endif
unsigned char pppoe_reqd_mac_addr[6];

static int PPPoEDevnameHook(char *cmd, char **argv, int doit);
#ifdef SC_DT_SUPPORT
char    untagdevname[32];       /* untagged Deveic name */
bool    preferredmethod = 1;    /* 1 means use devname as preferred device
                                   0 means use untagdevname as preferred */
int     padi_timeout = 3;       /* amount of time between PADI requests(unit: seconds)*/
int     backoff_timer = 60;     /* backoff timer for one session detect */
#endif
static option_t Options[] = {
    { "device name", o_wild, (void *) &PPPoEDevnameHook,
      "PPPoE device name",
      OPT_DEVNAM | OPT_PRIVFIX | OPT_NOARG  | OPT_A2STRVAL | OPT_STATIC,
      devnam},
#ifdef SC_DT_SUPPORT
    { "untagdevname", o_string, untagdevname,
      "PPPoE untagged device name",
      OPT_PRIO | OPT_STATIC, 
      NULL, MAXNAMELEN},
    { "preferredmethod", o_bool, &preferredmethod,
      "index untagdevname as preferred device", 0 },
    { "padi_timeout", o_int, (void *)&padi_timeout,
      "Amount of time between PADI requests"},
    { "backoff_timer", o_int, (void *)&backoff_timer,
      "Backoff timer"},
#endif
#ifdef __SC_BUILD__
    { "pppoe_srv_name", o_string, (void *)&pppd_pppoe_service,
      "Desired PPPoE service name" },
    { "rp_pppoe_ac",      o_string, (void *)&acName,
      "Desired PPPoE access concentrator name" },
    { "rp_pppoe_sess",    o_string, (void *)&existingSession,
      "Attach to existing session (sessid:macaddr)" },
    { "rp_pppoe_verbose", o_int, (void *)&printACNames,
      "Be verbose about discovered access concentrators"},
    { "pppoe-mac", o_string, (void *)&pppoe_reqd_mac,
      "Only connect to specified MAC address" },
    { "rp_pppoe_wanid",    o_int, (void *)&wanid,
      "wan id" },
#else
	{ "rp_pppoe_service", o_string, &pppd_pppoe_service,
      "Desired PPPoE service name" },
    { "rp_pppoe_ac",      o_string, &acName,
      "Desired PPPoE access concentrator name" },
    { "rp_pppoe_sess",    o_string, &existingSession,
      "Attach to existing session (sessid:macaddr)" },
    { "rp_pppoe_verbose", o_int, &printACNames,
      "Be verbose about discovered access concentrators"},
    { "pppoe-mac", o_string, &pppoe_reqd_mac,
      "Only connect to specified MAC address" },
#endif
    { NULL }
};
int (*OldDevnameHook)(char *cmd, char **argv, int doit) = NULL;
static PPPoEConnection *conn = NULL;

/**********************************************************************
 * %FUNCTION: PPPOEInitDevice
 * %ARGUMENTS:
 * None
 * %RETURNS:
 *
 * %DESCRIPTION:
 * Initializes PPPoE device.
 ***********************************************************************/
static int
PPPOEInitDevice(void)
{
    conn = malloc(sizeof(PPPoEConnection));
    if (!conn) {
	novm("PPPoE session data");
    }
    memset(conn, 0, sizeof(PPPoEConnection));
    conn->acName = acName;
    conn->serviceName = pppd_pppoe_service;
    conn->ifName = devnam;
    conn->discoverySocket = -1;
#ifdef SC_DT_SUPPORT
    if(checkUntagDevname(untagdevname))
    {
        conn->untagIfName = untagdevname;
    }
    else
        conn->untagIfName = NULL;
    conn->discoveryUntagSocket = -1;
    //conn->method = preferredmethod;
    conn->discoveryBackupSocket = -1;
#endif
    conn->sessionSocket = -1;
    conn->useHostUniq = 1;
    conn->printACNames = printACNames;
    conn->discoveryTimeout = PADI_TIMEOUT;

    return 1;
}

/**********************************************************************
 * %FUNCTION: PPPOEConnectDevice
 * %ARGUMENTS:
 * None
 * %RETURNS:
 * Non-negative if all goes well; -1 otherwise
 * %DESCRIPTION:
 * Connects PPPoE device.
 ***********************************************************************/
static int
PPPOEConnectDevice(void)
{
    struct sockaddr_pppox sp;

#ifndef SC_DT_SUPPORT
    strlcpy(ppp_devnam, devnam, sizeof(ppp_devnam));
#endif
    if (existingSession) {
	unsigned int mac[ETH_ALEN];
	int i, ses;
	if (sscanf(existingSession, "%d:%x:%x:%x:%x:%x:%x",
		   &ses, &mac[0], &mac[1], &mac[2],
		   &mac[3], &mac[4], &mac[5]) != 7) {
	    fatal("Illegal value for rp_pppoe_sess option");
	}
	conn->session = htons(ses);
	for (i=0; i<ETH_ALEN; i++) {
	    conn->peerEth[i] = (unsigned char) mac[i];
	}
    } else {
#ifdef __SC_BUILD__
		conn->acName = acName;
    	conn->serviceName = pppd_pppoe_service;
#endif
#ifdef SC_DT_SUPPORT
        /* send PADT for error exit last time */
        if(access(LAST_PADT_INFO, F_OK)==0)
        {
            sendPADTForInit(conn, LAST_PADT_INFO);
            sleep(1);
        }
#endif
	discovery(conn);
	if (conn->discoveryState != STATE_SESSION) {
	    error("Unable to complete PPPoE Discovery");
	    return -1;
	}
    }

    /* Set PPPoE session-number for further consumption */
    ppp_session_number = ntohs(conn->session);

    /* Make the session socket */
    conn->sessionSocket = socket(AF_PPPOX, SOCK_STREAM, PX_PROTO_OE);
    if (conn->sessionSocket < 0) {
	error("Failed to create PPPoE socket: %m");
	goto errout;
    }
    sp.sa_family = AF_PPPOX;
    sp.sa_protocol = PX_PROTO_OE;
    sp.sa_addr.pppoe.sid = conn->session;
    memcpy(sp.sa_addr.pppoe.dev, conn->ifName, IFNAMSIZ);
    memcpy(sp.sa_addr.pppoe.remote, conn->peerEth, ETH_ALEN);
#ifdef SC_DT_SUPPORT
    strlcpy(ppp_devnam, conn->ifName, sizeof(ppp_devnam));
#endif
    /* Set remote_number for ServPoET */
    sprintf(remote_number, "%02X:%02X:%02X:%02X:%02X:%02X",
	    (unsigned) conn->peerEth[0],
	    (unsigned) conn->peerEth[1],
	    (unsigned) conn->peerEth[2],
	    (unsigned) conn->peerEth[3],
	    (unsigned) conn->peerEth[4],
	    (unsigned) conn->peerEth[5]);

    warn("Connected to %02X:%02X:%02X:%02X:%02X:%02X via interface %s",
	 (unsigned) conn->peerEth[0],
	 (unsigned) conn->peerEth[1],
	 (unsigned) conn->peerEth[2],
	 (unsigned) conn->peerEth[3],
	 (unsigned) conn->peerEth[4],
	 (unsigned) conn->peerEth[5],
	 conn->ifName);

    script_setenv("MACREMOTE", remote_number, 0);

    if (connect(conn->sessionSocket, (struct sockaddr *) &sp,
		sizeof(struct sockaddr_pppox)) < 0) {
	error("Failed to connect PPPoE socket: %d %m", errno);
	close(conn->sessionSocket);
	goto errout;
    }
#ifdef __SC_BUILD__
    	char gw_mac[32];
		char session_number[16];
		snprintf(gw_mac, sizeof(gw_mac), "%02x:%02x:%02x:%02x:%02x:%02x",
			(unsigned) conn->peerEth[0],
			(unsigned) conn->peerEth[1],
			(unsigned) conn->peerEth[2],
			(unsigned) conn->peerEth[3],
			(unsigned) conn->peerEth[4],
			(unsigned) conn->peerEth[5]);
		snprintf(session_number, sizeof(session_number), "%d", ntohs(conn->session));
        sal_wan_set_con_ppp_session_t(wanid, session_number);
        sal_wan_set_con_gw_mac_t(wanid, gw_mac);
#endif
#ifdef SC_DT_SUPPORT
    /* record padt info */
    char cmd[256];
    
    sprintf(cmd, "/bin/echo \"%d,%s,%s,\" > %s", conn->session, gw_mac, conn->ifName, LAST_PADT_INFO);
    system(cmd);
#ifdef SC_DT_DEBUG
    mybug("%s, create PADT info file %d,%s,%s.\n", __FUNCTION__, conn->session, gw_mac, conn->ifName);
#endif
#endif
    return conn->sessionSocket;

 errout:
    if (conn->discoverySocket >= 0) {
	sendPADT(conn, "connection error"/*NULL*/);
	close(conn->discoverySocket);
	conn->discoverySocket = -1;
    }
#ifdef SC_DT_SUPPORT
    if (conn->discoveryBackupSocket >= 0) {
	close(conn->discoveryBackupSocket);
	conn->discoveryBackupSocket = -1;
    }
    else {
	conn->discoveryUntagSocket = -1;
    }
#endif
    return -1;
}

static void
PPPOERecvConfig(int mru,
		u_int32_t asyncmap,
		int pcomp,
		int accomp)
{
#if 0 /* broken protocol, but no point harrassing the users I guess... */
    if (mru > MAX_PPPOE_MTU)
	warn("Couldn't increase MRU to %d", mru);
#endif
}

/**********************************************************************
 * %FUNCTION: PPPOEDisconnectDevice
 * %ARGUMENTS:
 * None
 * %RETURNS:
 * Nothing
 * %DESCRIPTION:
 * Disconnects PPPoE device
 ***********************************************************************/
static void
PPPOEDisconnectDevice(void)
{
    struct sockaddr_pppox sp;

    sp.sa_family = AF_PPPOX;
    sp.sa_protocol = PX_PROTO_OE;
    sp.sa_addr.pppoe.sid = 0;
    memcpy(sp.sa_addr.pppoe.dev, conn->ifName, IFNAMSIZ);
    memcpy(sp.sa_addr.pppoe.remote, conn->peerEth, ETH_ALEN);
    if (connect(conn->sessionSocket, (struct sockaddr *) &sp,
		sizeof(struct sockaddr_pppox)) < 0)
	error("Failed to disconnect PPPoE socket: %d %m", errno);
	
    close(conn->sessionSocket);
#ifdef __SC_BUILD__
    conn->sessionSocket = -1;
	
    /*Martin:by now we can not wait for receive padt from server*/
    //waitForPADT(conn, 1);
    sendPADTFromClient(conn, "disconnection"/*NULL*/);
	//conn->discoverySocket = -1;
#endif
    if (conn->discoverySocket >= 0)
    	close(conn->discoverySocket);
#ifdef SC_DT_SUPPORT
        conn->discoverySocket = -1;
        conn->discoveryUntagSocket = -1;
        if(conn->discoveryBackupSocket)
        {
            close(conn->discoveryBackupSocket);
            conn->discoveryBackupSocket = -1;
        }
#endif
}


static void
PPPOEDeviceOptions(void)
{
    char buf[256];
    snprintf(buf, 256, _PATH_ETHOPT "%s", devnam);
    if (!options_from_file(buf, 0, 0, 1))
	exit(EXIT_OPTION_ERROR);

}

struct channel pppoe_channel;

/**********************************************************************
 * %FUNCTION: PPPoEDevnameHook
 * %ARGUMENTS:
 * cmd -- the command (actually, the device name
 * argv -- argument vector
 * doit -- if non-zero, set device name.  Otherwise, just check if possible
 * %RETURNS:
 * 1 if we will handle this device; 0 otherwise.
 * %DESCRIPTION:
 * Checks if name is a valid interface name; if so, returns 1.  Also
 * sets up devnam (string representation of device).
 ***********************************************************************/
static int
PPPoEDevnameHook(char *cmd, char **argv, int doit)
{
    int r = 1;
    int fd;
    struct ifreq ifr;
    /*
     * Take any otherwise-unrecognized option as a possible device name,
     * and test if it is the name of a network interface with a
     * hardware address whose sa_family is ARPHRD_ETHER.
     */
    if (strlen(cmd) > 4 && !strncmp(cmd, "nic-", 4)) {
	/* Strip off "nic-" */
	cmd += 4;
    }

    /* Open a socket */
    if ((fd = socket(PF_PACKET, SOCK_RAW, 0)) < 0) {
	r = 0;
    }

    /* Try getting interface index */
    if (r) {
	strncpy(ifr.ifr_name, cmd, sizeof(ifr.ifr_name));
	if (ioctl(fd, SIOCGIFINDEX, &ifr) < 0) {
	    r = 0;
	} else {
	    if (ioctl(fd, SIOCGIFHWADDR, &ifr) < 0) {
		r = 0;
	    } else {
		if (ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER) {
		    if (doit)
			error("Interface %s not Ethernet", cmd);
		    r = 0;
		}
	    }
	}
    }

    /* Close socket */
    close(fd);
    if (r && doit) {
	strncpy(devnam, cmd, sizeof(devnam));
	if (the_channel != &pppoe_channel) {

	    the_channel = &pppoe_channel;
#ifndef _DISABLE_SERIAL_
	    modem = 0;
#endif
	    PPPOEInitDevice();
	}
	return 1;
    }

    return r;
}

#ifdef SC_DT_SUPPORT
/**********************************************************************
 * %FUNCTION: checkUntagDevname
 * %ARGUMENTS:
 * ifname -- checking device name
 * %RETURNS:
 * 1 if we will handle this device; 0 otherwise.
 * %DESCRIPTION:
 * Checks if name is a valid interface name; if so, returns 1.  Also
 * sets up devnam (string representation of device).
 ***********************************************************************/
int
checkUntagDevname(char *devname)
{
    int r = 1;
    int fd;
    struct ifreq ifr;

    if(strlen(devname)<3 || devname==NULL)
        return 0;

    /* Open a socket */
    if ((fd = socket(PF_PACKET, SOCK_RAW, 0)) < 0) {
	r = 0;
    }

    /* Try getting interface index */
    if (r) {
	strncpy(ifr.ifr_name, devname, sizeof(ifr.ifr_name));
	if (ioctl(fd, SIOCGIFINDEX, &ifr) < 0) {
	    r = 0;
	} else {
	    if (ioctl(fd, SIOCGIFHWADDR, &ifr) < 0) {
		r = 0;
	    } else {
		if (ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER) {
		    error("Interface %s not Ethernet", devname);
		    r = 0;
		}
	    }
	}
    }

    /* Close socket */
    close(fd);
    return r;
}
#endif

/**********************************************************************
 * %FUNCTION: plugin_init
 * %ARGUMENTS:
 * None
 * %RETURNS:
 * Nothing
 * %DESCRIPTION:
 * Initializes hooks for pppd plugin
 ***********************************************************************/
void
plugin_init(void)

{
    if (!ppp_available() && !new_style_driver) {
	fatal("Linux kernel does not support PPPoE -- are you running 2.4.x?");
    }

    add_options(Options);
#ifndef __SC_BUILD__
    info("RP-PPPoE plugin version %s compiled against pppd %s",
	 RP_VERSION, VERSION);
#endif
}

void pppoe_check_options(void)
{
    unsigned int mac[6];
    int i;

    if (pppoe_reqd_mac != NULL) {
	if (sscanf(pppoe_reqd_mac, "%x:%x:%x:%x:%x:%x",
		   &mac[0], &mac[1], &mac[2], &mac[3],
		   &mac[4], &mac[5]) != 6) {
	    option_error("cannot parse pppoe-mac option value");
	    exit(EXIT_OPTION_ERROR);
	}
	for (i = 0; i < 6; ++i)
	    conn->req_peer_mac[i] = mac[i];
	conn->req_peer = 1;
    }

    lcp_allowoptions[0].neg_accompression = 0;
    lcp_wantoptions[0].neg_accompression = 0;

    lcp_allowoptions[0].neg_asyncmap = 0;
    lcp_wantoptions[0].neg_asyncmap = 0;

    lcp_allowoptions[0].neg_pcompression = 0;
    lcp_wantoptions[0].neg_pcompression = 0;

    if (lcp_allowoptions[0].mru > MAX_PPPOE_MTU)
	lcp_allowoptions[0].mru = MAX_PPPOE_MTU;
    if (lcp_wantoptions[0].mru > MAX_PPPOE_MTU)
	lcp_wantoptions[0].mru = MAX_PPPOE_MTU;

    ccp_allowoptions[0].deflate = 0;
    ccp_wantoptions[0].deflate = 0;

    ipcp_allowoptions[0].neg_vj = 0;
    ipcp_wantoptions[0].neg_vj = 0;

    ccp_allowoptions[0].bsd_compress = 0;
    ccp_wantoptions[0].bsd_compress = 0;
}

struct channel pppoe_channel = {
    .options = Options,
    .process_extra_options = &PPPOEDeviceOptions,
    .check_options = pppoe_check_options,
    .connect = &PPPOEConnectDevice,
    .disconnect = &PPPOEDisconnectDevice,
    .establish_ppp = &generic_establish_ppp,
    .disestablish_ppp = &generic_disestablish_ppp,
    .send_config = NULL,
    .recv_config = &PPPOERecvConfig,
    .close = NULL,
    .cleanup = NULL
};
