/*	$KAME: dhcp6c.c,v 1.164 2006/01/10 02:46:09 jinmei Exp $	*/
/*
 * Copyright (C) 1998 and 1999 WIDE Project.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/queue.h>
#include <errno.h>
#include <limits.h>
#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif
#include <net/if.h>
#ifdef __FreeBSD__
#include <net/if_var.h>
#endif

#include <netinet/in.h>
#ifdef __KAME__
#include <net/if_dl.h>
#include <netinet6/in6_var.h>
#endif

#include <arpa/inet.h>
#include <netdb.h>

#include <signal.h>
#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <ifaddrs.h>

#include <dhcp6.h>
#include <config.h>
#include <common.h>
#include <timer.h>
#include <dhcp6c.h>
#include <control.h>
#include <dhcp6_ctl.h>
#include <dhcp6c_ia.h>
#include <prefixconf.h>
#include <auth.h>
#include "log_api.h"
#include "sal/sal_wan.h"
#include "sal/sal_dhcp6.h"
#include "scutil.h"


static int debug = 0;
static int exit_ok = 0;
static u_long sig_flags = 0;
#define SIGF_TERM 0x1
#define SIGF_HUP 0x2

const dhcp6_mode_t dhcp6_mode = DHCP6_MODE_CLIENT;

int sock;	/* inbound/outbound udp port */
int rtsock;	/* routing socket */
int ctlsock = -1;		/* control TCP port */
int solicit_flag = -1; 
int restart_solicit = 0;
char *ctladdr = DEFAULT_CLIENT_CONTROL_ADDR;
char *ctlport = DEFAULT_CLIENT_CONTROL_PORT;

//#define DEFAULT_KEYFILE SYSCONFDIR "/dhcp6cctlkey"
//#define DEFAULT_KEYFILE "/etc/dhcp6cctlkey"
#define DEFAULT_KEYFILE "/tmp/dhcp6cctlkey"
#define CTLSKEW 300

static char *conffile = DHCP6C_CONF;

static const struct sockaddr_in6 *sa6_allagent;
static struct duid client_duid;

static struct vclass vendor_class;

static char *pid_file = DHCP6C_PIDFILE;

static char *ctlkeyfile = DEFAULT_KEYFILE;
static struct keyinfo *ctlkey = NULL;
static int ctldigestlen;

static int infreq_mode = 0;

static inline int get_val32 __P((char **, int *, u_int32_t *));
static inline int get_ifname __P((char **, int *, char *, int));

static void usage __P((void));
static void client6_init __P((void));
static void client6_startall __P((int));
static void free_resources __P((struct dhcp6_if *));
static void client6_mainloop __P((void));
static int client6_do_ctlcommand __P((char *, ssize_t));
static void client6_reload __P((void));
static int client6_ifctl __P((char *ifname, u_int16_t));
static void check_exit __P((void));
static void process_signals __P((void));
static struct dhcp6_serverinfo *find_server __P((struct dhcp6_event *,
						 struct duid *));
static struct dhcp6_serverinfo *select_server __P((struct dhcp6_event *));
static void client6_recv __P((void));
static int client6_recvreconfig __P((struct dhcp6_if *, struct dhcp6 *,
					ssize_t, struct dhcp6_optinfo *));
static int client6_recvadvert __P((struct dhcp6_if *, struct dhcp6 *,
				   ssize_t, struct dhcp6_optinfo *));
static int client6_recvreply __P((struct dhcp6_if *, struct dhcp6 *,
				  ssize_t, struct dhcp6_optinfo *));
static void client6_signal __P((int));
static struct dhcp6_event *find_event_withid __P((struct dhcp6_if *,
						  u_int32_t));
static int construct_confdata __P((struct dhcp6_if *, struct dhcp6_event *));
static int construct_reqdata __P((struct dhcp6_if *, struct dhcp6_optinfo *,
    struct dhcp6_event *));
static void destruct_iadata __P((struct dhcp6_eventdata *));
static void ts_sub __P((struct timespec *, struct timespec *, struct timespec *));
static struct dhcp6_timer *client6_expire_refreshtime __P((void *));
static int process_auth __P((struct authparam *, struct dhcp6 *dh6, ssize_t,
    struct dhcp6_optinfo *, struct dhcp6_if *));
static int set_auth __P((struct dhcp6_event *, struct dhcp6_optinfo *));

struct dhcp6_timer *client6_timo __P((void *));
int client6_start __P((struct dhcp6_if *));
static void info_printf __P((const char *, ...));

#if 1 //brcm
int updateDhcp6sConfDnsList __P((struct dhcp6_optinfo *));
#endif

extern int client6_script __P((char *, int, struct dhcp6_optinfo *));
extern int IA_PD_no_prefix;
#define MAX_ELAPSED_TIME 0xffff
static int recv_response = -1;
static int rapidcommit_change = -1;
char if_name[16];
char *dns_changed;
struct timespec recv_reply_time;
int
main(argc, argv)
	int argc;
	char **argv;
{
	int ch, pid;
	char *progname;
	FILE *pidfp;
	struct dhcp6_if *ifp;

#ifndef HAVE_ARC4RANDOM
	srandom(time(NULL) & getpid());
#endif

	if ((progname = strrchr(*argv, '/')) == NULL)
		progname = *argv;
	else
		progname++;

	while ((ch = getopt(argc, argv, "c:dDfik:p:")) != -1) {
		switch (ch) {
		case 'c':
			conffile = optarg;
			break;
		case 'd':
			debug = 1;
			break;
		case 'D':
			debug = 2;
			break;
		case 'f':
			foreground++;
			break;
		case 'i':
			infreq_mode = 1;
			break;
		case 'k':
			ctlkeyfile = optarg;
			break;
		case 'p':
			pid_file = optarg;
			break;
		default:
			usage();
			exit(0);
		}
	}
	argc -= optind;
	argv += optind;

	if (argc == 0) {
		usage();
		exit(0);
	}
#if 0
    openlog(" dhcp6", 0, LOG_AUTH);
	syslog(LOG_INFO, "DHCPV6 client started");

	if (foreground == 0)
		openlog(progname, LOG_NDELAY|LOG_PID, LOG_DAEMON);

	setloglevel(debug);
#endif

	strcpy(if_name,argv[0]);

	client6_init();
	while (argc-- > 0) { 
		if ((ifp = ifinit(argv[0])) == NULL) {
			dprintf(LOG_ERR, FNAME, "failed to initialize %s",
			    argv[0]);
			system("echo \"DHCPv6 client stop: failed to initialize\" > /dev/console");
			exit(1);
		}
		argv++;
	}

	if (infreq_mode == 0 && (cfparse(conffile)) != 0) {
		dprintf(LOG_ERR, FNAME, "failed to parse configuration file");
		system("echo \"DHCPv6 client stop: configuration failed\" > /dev/console");
		exit(1);
	}

	if (foreground == 0 && infreq_mode == 0) {
		if (daemon(0, 0) < 0)
			err(1, "daemon");
	}

	/* dump current PID */
	pid = getpid();
	if ((pidfp = fopen(pid_file, "w")) != NULL) {
		fprintf(pidfp, "%d\n", pid);
		fclose(pidfp);
	}

	system("echo \"DHCPv6 client start\" > /dev/console");
	client6_startall(0);
	client6_mainloop();
	system("echo \"DHCPv6 client stop\" > /dev/console");
	exit(0);
}

static void
usage()
{

	fprintf(stderr, "usage: dhcp6c [-c configfile] [-dDfi] "
	    "[-p pid-file] interface [interfaces...]\n");
}

/*------------------------------------------------------------*/

void
client6_init()
{
	struct addrinfo hints, *res;
	static struct sockaddr_in6 sa6_allagent_storage;
	int error, on = 1;

	/* get our DUID */
	if (get_duid(DUID_FILE, &client_duid, if_name)) {
		dprintf(LOG_ERR, FNAME, "failed to get a DUID");
		system("echo \"DHCPv6 client stop: DUID failed\" > /dev/console");
		exit(1);
	}
#if 0
	if (dhcp6_ctl_authinit(ctlkeyfile, &ctlkey, &ctldigestlen) != 0) {
		dprintf(LOG_NOTICE, FNAME,
		    "failed initialize control message authentication");
		/* run the server anyway */
	}
#endif
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_INET6;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags = AI_PASSIVE;
	error = getaddrinfo(NULL, DH6PORT_DOWNSTREAM, &hints, &res);
	if (error) {
		dprintf(LOG_ERR, FNAME, "getaddrinfo: %s",
		    gai_strerror(error));
		system("echo \"DHCPv6 client stop: get addr failed\" > /dev/console");
		exit(1);
	}
	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock < 0) {
		dprintf(LOG_ERR, FNAME, "socket");
		system("echo \"DHCPv6 client stop: socket failed\" > /dev/console");
		exit(1);
	}
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT,
		       &on, sizeof(on)) < 0) {
		dprintf(LOG_ERR, FNAME,
		    "setsockopt(SO_REUSEPORT): %s", strerror(errno));
		system("echo \"DHCPv6 client stop: socket failed\" > /dev/console");
		exit(1);
	}
#ifdef IPV6_RECVPKTINFO
	if (setsockopt(sock, IPPROTO_IPV6, IPV6_RECVPKTINFO, &on,
		       sizeof(on)) < 0) {
		dprintf(LOG_ERR, FNAME,
			"setsockopt(IPV6_RECVPKTINFO): %s",
			strerror(errno));
		system("echo \"DHCPv6 client stop: socket failed\" > /dev/console");
		exit(1);
	}
#else
	if (setsockopt(sock, IPPROTO_IPV6, IPV6_PKTINFO, &on,
		       sizeof(on)) < 0) {
		dprintf(LOG_ERR, FNAME,
		    "setsockopt(IPV6_PKTINFO): %s",
		    strerror(errno));
		system("echo \"DHCPv6 client stop: socket failed\" > /dev/console");
		exit(1);
	}
#endif
	if (setsockopt(sock, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &on,
		       sizeof(on)) < 0) {
		dprintf(LOG_ERR, FNAME,
		    "setsockopt(sock, IPV6_MULTICAST_LOOP): %s",
		    strerror(errno));
		system("echo \"DHCPv6 client stop: socket failed\" > /dev/console");
		exit(1);
	}
	if (setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY,
	    &on, sizeof(on)) < 0) {
		dprintf(LOG_ERR, FNAME, "setsockopt(IPV6_V6ONLY): %s",
		    strerror(errno));
		system("echo \"DHCPv6 client stop: socket failed\" > /dev/console");
		exit(1);
	}

	/*
	 * According RFC3315 2.2, only the incoming port should be bound to UDP
	 * port 546.  However, to have an interoperability with some servers,
	 * the outgoing port is also bound to the DH6PORT_DOWNSTREAM.
	 */
	if (bind(sock, res->ai_addr, res->ai_addrlen) < 0) {
		dprintf(LOG_ERR, FNAME, "bind: %s", strerror(errno));
		system("echo \"DHCPv6 client stop: bind failed\" > /dev/console");
		exit(1);
	}
	freeaddrinfo(res);

	/* open a routing socket to watch the routing table */
	if ((rtsock = socket(PF_ROUTE, SOCK_RAW, 0)) < 0) {
		dprintf(LOG_ERR, FNAME, "open a routing socket: %s",
		    strerror(errno));
		system("echo \"DHCPv6 client stop: socket failed\" > /dev/console");
		exit(1);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_INET6;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	error = getaddrinfo(DH6ADDR_ALLAGENT, DH6PORT_UPSTREAM, &hints, &res);
	if (error) {
		dprintf(LOG_ERR, FNAME, "getaddrinfo: %s",
		    gai_strerror(error));
		system("echo \"DHCPv6 client stop: get addr failed\" > /dev/console");
		exit(1);
	}
	memcpy(&sa6_allagent_storage, res->ai_addr, res->ai_addrlen);
	sa6_allagent = (const struct sockaddr_in6 *)&sa6_allagent_storage;
	freeaddrinfo(res);

	/* set up control socket */
#if 0
	if (ctlkey == NULL)
		dprintf(LOG_NOTICE, FNAME, "skip opening control port");
	else if (dhcp6_ctl_init(ctladdr, ctlport,
	    DHCP6CTL_DEF_COMMANDQUEUELEN, &ctlsock)) {
		dprintf(LOG_ERR, FNAME,
		    "failed to initialize control channel");
		exit(1);
	}
#endif

	if (signal(SIGHUP, client6_signal) == SIG_ERR) {
		dprintf(LOG_WARNING, FNAME, "failed to set signal: %s",
		    strerror(errno));
		system("echo \"DHCPv6 client stop: signal failed\" > /dev/console");
		exit(1);
	}
	if (signal(SIGTERM, client6_signal) == SIG_ERR) {
		dprintf(LOG_WARNING, FNAME, "failed to set signal: %s",
		    strerror(errno));
		system("echo \"DHCPv6 client stop: signal failed\" > /dev/console");
		exit(1);
	}
}

int
client6_start(ifp)
	struct dhcp6_if *ifp;
{
	struct dhcp6_event *ev;

	if (solicit_flag == 1) {
		dprintf(LOG_NOTICE, FNAME, 
			"another solicit is active, terminate.");
		return (0);
	}
	/* make sure that the interface does not have a timer */
	if (ifp->timer != NULL) {
		dprintf(LOG_DEBUG, FNAME,
		    "removed existing timer on %s", ifp->ifname);
		dhcp6_remove_timer(&ifp->timer);
	}

	/* create an event for the initial delay */
	if ((ev = dhcp6_create_event(ifp, DHCP6S_INIT)) == NULL) {
		dprintf(LOG_NOTICE, FNAME, "failed to create an event");
		return (-1);
	}
	TAILQ_INSERT_TAIL(&ifp->event_list, ev, link);

	if ((ev->authparam = new_authparam(ifp->authproto,
	    ifp->authalgorithm, ifp->authrdm)) == NULL) {
		dprintf(LOG_WARNING, FNAME, "failed to allocate "
		    "authentication parameters");
		dhcp6_remove_event(ev);
		return (-1);
	}

	if ((ev->timer = dhcp6_add_timer(client6_timo, ev)) == NULL) {
		dprintf(LOG_NOTICE, FNAME, "failed to add a timer for %s",
		    ifp->ifname);
		dhcp6_remove_event(ev);
		return (-1);
	}
	dhcp6_reset_timer(ev);
	solicit_flag = 1;

	return (0);
}

static void
client6_startall(isrestart)
	int isrestart;
{
	struct dhcp6_if *ifp;

	for (ifp = dhcp6_if; ifp; ifp = ifp->next) {
		if (isrestart &&ifreset(ifp)) {
			dprintf(LOG_NOTICE, FNAME, "failed to reset %s",
			    ifp->ifname);
			continue; /* XXX: try to recover? */
		}
		if (client6_start(ifp)) {
			system("echo \"DHCPv6 client stop: start failed\" > /dev/console");
			exit(1); /* initialization failure.  we give up. */
		}
	}
}

static void
free_resources(freeifp)
	struct dhcp6_if *freeifp;
{
	struct dhcp6_if *ifp;

	for (ifp = dhcp6_if; ifp; ifp = ifp->next) {
		struct dhcp6_event *ev, *ev_next;

		if (freeifp != NULL && freeifp != ifp)
			continue;

		/* release all IAs as well as send RELEASE message(s) */
		release_all_ia(ifp);

		/*
		 * Cancel all outstanding events for each interface except
		 * ones being released.
		 */
		for (ev = TAILQ_FIRST(&ifp->event_list); ev; ev = ev_next) {
			ev_next = TAILQ_NEXT(ev, link);

			if (ev->state == DHCP6S_RELEASE)
				continue; /* keep it for now */

			dhcp6_remove_event(ev);
		}
	}
}

static void
check_exit()
{
	struct dhcp6_if *ifp;

	if (!exit_ok)
		return;

	for (ifp = dhcp6_if; ifp; ifp = ifp->next) {
		/*
		 * Check if we have an outstanding event.  If we do, we cannot
		 * exit for now.
		 */
		if (!TAILQ_EMPTY(&ifp->event_list))
			return;
	}

	/* We have no existing event.  Do exit. */
	dprintf(LOG_INFO, FNAME, "exiting");
	
	unlink("/var/ip6dns");
	system("echo \"DHCPv6 client stop\" > /dev/console");

	exit(0);
}

static void
process_signals()
{
	if ((sig_flags & SIGF_TERM)) {
		terminate_flag = 1;
		exit_ok = 1;
		free_resources(NULL);
		unlink(pid_file);
		check_exit();
	}
	if ((sig_flags & SIGF_HUP)) {
		dprintf(LOG_INFO, FNAME, "restarting");
		free_resources(NULL);
		client6_startall(1);
	}

	sig_flags = 0;
}

static void
client6_mainloop()
{
	struct timespec *w;
	int ret, maxsock;
	fd_set r;
	unlink("/var/ip6dns");
	while(1) {
		if (sig_flags)
			process_signals();

		w = dhcp6_check_timer();
		if (w == NULL) {
			if (restart_solicit == 1) {
				restart_solicit = 0;
				dprintf(LOG_INFO, FNAME, "restarting");
				free_resources(NULL);
				client6_startall(1);
				w = dhcp6_check_timer();
			}
		}

		FD_ZERO(&r);
		FD_SET(sock, &r);
		maxsock = sock;
		if (ctlsock >= 0) {
			FD_SET(ctlsock, &r);
			maxsock = (sock > ctlsock) ? sock : ctlsock;
			(void)dhcp6_ctl_setreadfds(&r, &maxsock);
		}

		ret = pselect(maxsock + 1, &r, NULL, NULL, w, NULL);

		switch (ret) {
		case -1:
			if (errno != EINTR) {
				dprintf(LOG_ERR, FNAME, "select: %s",
				    strerror(errno));
				system("echo \"DHCPv6 client stop: select failed\" > /dev/console");
				exit(1);
			}
			continue;
		case 0:	/* timeout */
			break;	/* dhcp6_check_timer() will treat the case */
		default:
			break;
		}
		if (FD_ISSET(sock, &r))
			client6_recv();
			
		if (ctlsock >= 0) {
			if (FD_ISSET(ctlsock, &r)) {
				(void)dhcp6_ctl_acceptcommand(ctlsock,
				    client6_do_ctlcommand);
			}
			(void)dhcp6_ctl_readcommand(&r);
		}
	}
}

static inline int
get_val32(bpp, lenp, valp)
	char **bpp;
	int *lenp;
	u_int32_t *valp;
{
	char *bp = *bpp;
	int len = *lenp;
	u_int32_t i32;

	if (len < sizeof(*valp))
		return (-1);

	memcpy(&i32, bp, sizeof(i32));
	*valp = ntohl(i32);

	*bpp = bp + sizeof(*valp);
	*lenp = len - sizeof(*valp);

	return (0);
}

static inline int
get_ifname(bpp, lenp, ifbuf, ifbuflen)
	char **bpp;
	int *lenp;
	char *ifbuf;
	int ifbuflen;
{
	char *bp = *bpp;
	int len = *lenp, ifnamelen;
	u_int32_t i32;

	if (get_val32(bpp, lenp, &i32))
		return (-1);
	ifnamelen = (int)i32;

	if (*lenp < ifnamelen || ifnamelen > ifbuflen)
		return (-1);

	memset(ifbuf, 0, sizeof(ifbuf));
	memcpy(ifbuf, *bpp, ifnamelen);
	if (ifbuf[ifbuflen - 1] != '\0')
		return (-1);	/* not null terminated */

	*bpp = bp + sizeof(i32) + ifnamelen;
	*lenp = len - (sizeof(i32) + ifnamelen);

	return (0);
}

static int
client6_do_ctlcommand(buf, len)
	char *buf;
	ssize_t len;
{
	struct dhcp6ctl *ctlhead;
	u_int16_t command, version;
	u_int32_t p32, ts, ts0;
	int commandlen;
	char *bp;
	char ifname[IFNAMSIZ];
	time_t now;

	memset(ifname, 0, sizeof(ifname));

	ctlhead = (struct dhcp6ctl *)buf;

	command = ntohs(ctlhead->command);
	commandlen = (int)(ntohs(ctlhead->len));
	version = ntohs(ctlhead->version);
	if (len != sizeof(struct dhcp6ctl) + commandlen) {
		dprintf(LOG_ERR, FNAME,
		    "assumption failure: command length mismatch");
		return (DHCP6CTL_R_FAILURE);
	}

	/* replay protection and message authentication */
	if ((now = time(NULL)) < 0) {
		dprintf(LOG_ERR, FNAME, "failed to get current time: %s",
		    strerror(errno));
		return (DHCP6CTL_R_FAILURE);
	}
	ts0 = (u_int32_t)now;
	ts = ntohl(ctlhead->timestamp);
	if (ts + CTLSKEW < ts0 || (ts - CTLSKEW) > ts0) {
		dprintf(LOG_INFO, FNAME, "timestamp is out of range");
		return (DHCP6CTL_R_FAILURE);
	}

	if (ctlkey == NULL) {	/* should not happen!! */
		dprintf(LOG_ERR, FNAME, "no secret key for control channel");
		return (DHCP6CTL_R_FAILURE);
	}
	if (dhcp6_verify_mac(buf, len, DHCP6CTL_AUTHPROTO_UNDEF,
	    DHCP6CTL_AUTHALG_HMACMD5, sizeof(*ctlhead), ctlkey) != 0) {
		dprintf(LOG_INFO, FNAME, "authentication failure");
		return (DHCP6CTL_R_FAILURE);
	}

	bp = buf + sizeof(*ctlhead) + ctldigestlen;
	commandlen -= ctldigestlen;

	if (version > DHCP6CTL_VERSION) {
		dprintf(LOG_INFO, FNAME, "unsupported version: %d", version);
		return (DHCP6CTL_R_FAILURE);
	}

	switch (command) {
	case DHCP6CTL_COMMAND_RELOAD:
		if (commandlen != 0) {
			dprintf(LOG_INFO, FNAME, "invalid command length "
			    "for reload: %d", commandlen);
			return (DHCP6CTL_R_DONE);
		}
		client6_reload();
		break;
	case DHCP6CTL_COMMAND_START:
		if (get_val32(&bp, &commandlen, &p32))
			return (DHCP6CTL_R_FAILURE);
		switch (p32) {
		case DHCP6CTL_INTERFACE:
			if (get_ifname(&bp, &commandlen, ifname,
			    sizeof(ifname))) {
				return (DHCP6CTL_R_FAILURE);
			}
			if (client6_ifctl(ifname, DHCP6CTL_COMMAND_START))
				return (DHCP6CTL_R_FAILURE);
			break;
		default:
			dprintf(LOG_INFO, FNAME,
			    "unknown start target: %ul", p32);
			return (DHCP6CTL_R_FAILURE);
		}
		break;
	case DHCP6CTL_COMMAND_STOP:
		if (commandlen == 0) {
			exit_ok = 1;
			free_resources(NULL);
			unlink(pid_file);
			check_exit();
		} else {
			if (get_val32(&bp, &commandlen, &p32))
				return (DHCP6CTL_R_FAILURE);

			switch (p32) {
			case DHCP6CTL_INTERFACE:
				if (get_ifname(&bp, &commandlen, ifname,
				    sizeof(ifname))) {
					return (DHCP6CTL_R_FAILURE);
				}
				if (client6_ifctl(ifname,
				    DHCP6CTL_COMMAND_STOP)) {
					return (DHCP6CTL_R_FAILURE);
				}
				break;
			default:
				dprintf(LOG_INFO, FNAME,
				    "unknown start target: %ul", p32);
				return (DHCP6CTL_R_FAILURE);
			}
		}
		break;
	default:
		dprintf(LOG_INFO, FNAME,
		    "unknown control command: %d (len=%d)",
		    (int)command, commandlen);
		return (DHCP6CTL_R_FAILURE);
	}

  	return (DHCP6CTL_R_DONE);
}

static void
client6_reload()
{
	/* reload the configuration file */
	if (cfparse(conffile) != 0) {
		dprintf(LOG_WARNING, FNAME,
		    "failed to reload configuration file");
		return;
	}

	dprintf(LOG_NOTICE, FNAME, "client reloaded");

	return;
}

static int
client6_ifctl(ifname, command)
	char *ifname;
	u_int16_t command;
{
	struct dhcp6_if *ifp;

	if ((ifp = find_ifconfbyname(ifname)) == NULL) {
		dprintf(LOG_INFO, FNAME,
		    "failed to find interface configuration for %s",
		    ifname);
		return (-1);
	}

	dprintf(LOG_DEBUG, FNAME, "%s interface %s",
	    command == DHCP6CTL_COMMAND_START ? "start" : "stop", ifname);

	switch(command) {
	case DHCP6CTL_COMMAND_START:
		free_resources(ifp);
		if (client6_start(ifp)) {
			dprintf(LOG_NOTICE, FNAME, "failed to restart %s",
			    ifname);
			return (-1);
		}
		break;
	case DHCP6CTL_COMMAND_STOP:
		free_resources(ifp);
		if (ifp->timer != NULL) {
			dprintf(LOG_DEBUG, FNAME,
			    "removed existing timer on %s", ifp->ifname);
			dhcp6_remove_timer(&ifp->timer);
		}
		break;
	default:		/* impossible case, should be a bug */
		dprintf(LOG_ERR, FNAME, "unknown command: %d", (int)command);
		break;
	}

	return (0);
}

static struct dhcp6_timer *
client6_expire_refreshtime(arg)
	void *arg;
{
	struct dhcp6_if *ifp = arg;

	dprintf(LOG_DEBUG, FNAME,
	    "information refresh time on %s expired", ifp->ifname);

	dhcp6_remove_timer(&ifp->timer);
	client6_start(ifp);

	return (NULL);
}

struct dhcp6_timer *
client6_timo(arg)
	void *arg;
{
	struct dhcp6_event *ev = (struct dhcp6_event *)arg;
	struct dhcp6_if *ifp;
	int state = ev->state;

	ifp = ev->ifp;
	ev->timeouts++;

	/*
	 * Unless MRC is zero, the message exchange fails once the client has
	 * transmitted the message MRC times.
	 * [RFC3315 14.]
	 */
	if (ev->max_retrans_cnt && ev->timeouts >= ev->max_retrans_cnt) {
		dprintf(LOG_INFO, FNAME, "no responses were received");
		dhcp6_remove_event(ev);

		if (state != DHCP6S_RENEW && state != DHCP6S_REBIND) {
			unlink("/var/ip6dns");
			if (state == DHCP6S_REQUEST) {
				restart_solicit = 1;
			} else {
				sal_dhcp6_set_client_server_addr("");
				sal_dhcp6_set_client_server_duid("");
				sal_dhcp6_set_client_server_refresh_time("");
				if (state == DHCP6S_RELEASE) {
					system("echo \"DHCPv6 client stop: release retry failed\" > /dev/console");
				} 
                                else {
                                    if(recv_response == 0){
                                        syslog(LOG_INFO, "%s"LOG_ERRCODE_P004, log_type_db[GENERAL_LOG]);
                                        syslog(LOG_INFO, "%s"LOG_ERRCODE_P006, log_type_db[GENERAL_LOG],"no DHCPv6 prefix available"); 
                                    }	
                                    system("echo \"DHCPv6 client stop: retry 5 times\" > /dev/console");
                                    system("killall -SIGALRM pppd_1");
				}
				exit(1);
			}
		}

		return (NULL);
	}

	switch(ev->state) {
	case DHCP6S_INIT:
		ev->timeouts = 0; /* indicate to generate a new XID. */
		if ((ifp->send_flags & DHCIFF_INFO_ONLY) || infreq_mode)
			ev->state = DHCP6S_INFOREQ;
		else {
			ev->state = DHCP6S_SOLICIT;
			if (construct_confdata(ifp, ev)) {
				dprintf(LOG_ERR, FNAME, "can't send solicit");
				system("echo \"DHCPv6 client stop: solicit failed\" > /dev/console");
				exit(1); /* XXX */
			}
		}
		dhcp6_set_timeoparam(ev); /* XXX */
		/* fall through */
	case DHCP6S_REQUEST:
	case DHCP6S_RELEASE:
	case DHCP6S_INFOREQ:
		client6_send(ev);
		break;
	case DHCP6S_RENEW:
	case DHCP6S_REBIND:
		if (ev->state == DHCP6S_REBIND) {
			sal_dhcp6_set_client_server_addr("");
			sal_dhcp6_set_client_server_duid("");
			sal_dhcp6_set_client_server_refresh_time("");
		}
		if (!TAILQ_EMPTY(&ev->data_list))
			client6_send(ev);
		else {
			dprintf(LOG_INFO, FNAME,
			    "all information to be updated was canceled");
			dhcp6_remove_event(ev);
			return (NULL);
		}
		break;
	case DHCP6S_SOLICIT:
		sal_dhcp6_set_client_server_addr("");
		sal_dhcp6_set_client_server_duid("");
		sal_dhcp6_set_client_server_refresh_time("");
		if (ev->servers) {
			/*
			 * Send a Request to the best server.
			 * Note that when we set Rapid-commit in Solicit,
			 * but a direct Reply has been delayed (very much),
			 * the transition to DHCP6S_REQUEST (and the change of
			 * transaction ID) will invalidate the reply even if it
			 * ever arrives.
			 */
			ev->current_server = select_server(ev);
			if (ev->current_server == NULL) {
				/* this should not happen! */
				dprintf(LOG_NOTICE, FNAME,
				    "can't find a server");
				system("echo \"DHCPv6 client stop: find server failed\" > /dev/console");
				exit(1); /* XXX */
			}
			if (duidcpy(&ev->serverid,
			    &ev->current_server->optinfo.serverID)) {
				dprintf(LOG_NOTICE, FNAME,
				    "can't copy server ID");
				return (NULL); /* XXX: better recovery? */
			}
			ev->timeouts = 0;
			ev->state = DHCP6S_REQUEST;
			dhcp6_set_timeoparam(ev);

			if (ev->authparam != NULL)
				free(ev->authparam);
			ev->authparam = ev->current_server->authparam;
			ev->current_server->authparam = NULL;

			if (construct_reqdata(ifp,
			    &ev->current_server->optinfo, ev)) {
				dprintf(LOG_NOTICE, FNAME,
				    "failed to construct request data");
				break;
			}
		}
		client6_send(ev);
		break;
	}

	dhcp6_reset_timer(ev);

	return (ev->timer);
}

static int
construct_confdata(ifp, ev)
	struct dhcp6_if *ifp;
	struct dhcp6_event *ev;
{
	struct ia_conf *iac;
	struct dhcp6_eventdata *evd = NULL;
	struct dhcp6_list *ial = NULL, pl;
	struct dhcp6_ia iaparam;

	TAILQ_INIT(&pl);	/* for safety */

	for (iac = TAILQ_FIRST(&ifp->iaconf_list); iac;
	    iac = TAILQ_NEXT(iac, link)) {

	/* If we are sending a renew message in 
	* response to a reconfigure message, we 
	* would want to add all IAs even though 
	* they are valid.
	*/
#if 0
		/* ignore IA config currently used */
		if (!TAILQ_EMPTY(&iac->iadata))
			continue;
#endif
		evd = NULL;
		if ((evd = malloc(sizeof(*evd))) == NULL) {
			dprintf(LOG_NOTICE, FNAME,
			    "failed to create a new event data");
			goto fail;
		}
		memset(evd, 0, sizeof(evd));

		memset(&iaparam, 0, sizeof(iaparam));
		iaparam.iaid = iac->iaid;
		switch (iac->type) {
		case IATYPE_PD:
			ial = NULL;
			if ((ial = malloc(sizeof(*ial))) == NULL)
				goto fail;
			TAILQ_INIT(ial);

			TAILQ_INIT(&pl);
			dhcp6_copy_list(&pl,
			    &((struct iapd_conf *)iac)->iapd_prefix_list);
			if (dhcp6_add_listval(ial, DHCP6_LISTVAL_IAPD,
			    &iaparam, &pl) == NULL) {
				goto fail;
			}
			dhcp6_clear_list(&pl);

			evd->type = DHCP6_EVDATA_IAPD;
			evd->data = ial;
			evd->event = ev;
			evd->destructor = destruct_iadata;
			TAILQ_INSERT_TAIL(&ev->data_list, evd, link);
			break;
		case IATYPE_NA:
			ial = NULL;
			if ((ial = malloc(sizeof(*ial))) == NULL)
				goto fail;
			TAILQ_INIT(ial);

			TAILQ_INIT(&pl);
			dhcp6_copy_list(&pl,
			    &((struct iana_conf *)iac)->iana_address_list);
			if (dhcp6_add_listval(ial, DHCP6_LISTVAL_IANA,
			    &iaparam, &pl) == NULL) {
				goto fail;
			}
			dhcp6_clear_list(&pl);

			evd->type = DHCP6_EVDATA_IANA;
			evd->data = ial;
			evd->event = ev;
			evd->destructor = destruct_iadata;
			TAILQ_INSERT_TAIL(&ev->data_list, evd, link);
			break;
		default:
			dprintf(LOG_ERR, FNAME, "internal error");
			system("echo \"DHCPv6 client stop: internal error\" > /dev/console");
			exit(1);
		}
	}

	return (0);

  fail:
	if (evd)
		free(evd);
	if (ial)
		free(ial);
	dhcp6_remove_event(ev);	/* XXX */
	
	return (-1);
}

static int
construct_reqdata(ifp, optinfo, ev)
	struct dhcp6_if *ifp;
	struct dhcp6_optinfo *optinfo;
	struct dhcp6_event *ev;
{
	struct ia_conf *iac;
	struct dhcp6_eventdata *evd = NULL;
	struct dhcp6_list *ial = NULL;
	struct dhcp6_ia iaparam;

	/* discard previous event data */
	dhcp6_remove_evdata(ev);

	if (optinfo == NULL)
		return (0);

	for (iac = TAILQ_FIRST(&ifp->iaconf_list); iac;
	    iac = TAILQ_NEXT(iac, link)) {
		struct dhcp6_listval *v;

		/* ignore IA config currently used */
		if (!TAILQ_EMPTY(&iac->iadata))
			continue;

		memset(&iaparam, 0, sizeof(iaparam));
		iaparam.iaid = iac->iaid;

		ial = NULL;
		evd = NULL;

		switch (iac->type) {
		case IATYPE_PD:
			if ((v = dhcp6_find_listval(&optinfo->iapd_list,
			    DHCP6_LISTVAL_IAPD, &iaparam, 0)) == NULL)
				continue;

			if ((ial = malloc(sizeof(*ial))) == NULL)
				goto fail;

			TAILQ_INIT(ial);
			if (dhcp6_add_listval(ial, DHCP6_LISTVAL_IAPD,
			    &iaparam, &v->sublist) == NULL) {
				goto fail;
			}

			if ((evd = malloc(sizeof(*evd))) == NULL)
				goto fail;
			memset(evd, 0, sizeof(*evd));
			evd->type = DHCP6_EVDATA_IAPD;
			evd->data = ial;
			evd->event = ev;
			evd->destructor = destruct_iadata;
			TAILQ_INSERT_TAIL(&ev->data_list, evd, link);
			break;
		case IATYPE_NA:
			if ((v = dhcp6_find_listval(&optinfo->iana_list,
			    DHCP6_LISTVAL_IANA, &iaparam, 0)) == NULL)
				continue;

			if ((ial = malloc(sizeof(*ial))) == NULL)
				goto fail;

			TAILQ_INIT(ial);
			if (dhcp6_add_listval(ial, DHCP6_LISTVAL_IANA,
			    &iaparam, &v->sublist) == NULL) {
				goto fail;
			}

			if ((evd = malloc(sizeof(*evd))) == NULL)
				goto fail;
			memset(evd, 0, sizeof(*evd));
			evd->type = DHCP6_EVDATA_IANA;
			evd->data = ial;
			evd->event = ev;
			evd->destructor = destruct_iadata;
			TAILQ_INSERT_TAIL(&ev->data_list, evd, link);
			break;
		default:
			dprintf(LOG_ERR, FNAME, "internal error");
			system("echo \"DHCPv6 client stop: internal error\" > /dev/console");
			exit(1);
		}
	}

	return (0);

  fail:
	if (evd)
		free(evd);
	if (ial)
		free(ial);
	dhcp6_remove_event(ev);	/* XXX */
	
	return (-1);
}

static void
destruct_iadata(evd)
	struct dhcp6_eventdata *evd;
{
	struct dhcp6_list *ial;

	if (evd->type != DHCP6_EVDATA_IAPD && evd->type != DHCP6_EVDATA_IANA) {
		dprintf(LOG_ERR, FNAME, "assumption failure %d", evd->type);
		system("echo \"DHCPv6 client stop: assumption failed\" > /dev/console");
		exit(1);
	}

	ial = (struct dhcp6_list *)evd->data;
	dhcp6_clear_list(ial);
	free(ial);
}

static struct dhcp6_serverinfo *
select_server(ev)
	struct dhcp6_event *ev;
{
	struct dhcp6_serverinfo *s;

	/*
	 * pick the best server according to RFC3315 Section 17.1.3.
	 * XXX: we currently just choose the one that is active and has the
	 * highest preference.
	 */
	for (s = ev->servers; s; s = s->next) {
		if (s->active) {
			dprintf(LOG_DEBUG, FNAME, "picked a server (ID: %s)",
			    duidstr(&s->optinfo.serverID));
			sal_dhcp6_set_client_server_duid(duidstr(&s->optinfo.serverID));
			return (s);
		}
	}

	return (NULL);
}

static void
client6_signal(sig)
	int sig;
{

	dprintf(LOG_INFO, FNAME, "received a signal (%d)", sig);

	switch (sig) {
	case SIGTERM:
		sig_flags |= SIGF_TERM;
		break;
	case SIGHUP:
		sig_flags |= SIGF_HUP;
		break;
	}
}

void
client6_send(ev)
	struct dhcp6_event *ev;
{
	struct dhcp6_if *ifp;
	char buf[BUFSIZ];
	struct sockaddr_in6 dst;
	struct dhcp6 *dh6;
	struct dhcp6_optinfo optinfo;
	ssize_t optlen, len;
	struct dhcp6_eventdata *evd;

	ifp = ev->ifp;

	dh6 = (struct dhcp6 *)buf;
	memset(dh6, 0, sizeof(*dh6));

	switch(ev->state) {
	case DHCP6S_SOLICIT:
                recv_response = 0; 
		dh6->dh6_msgtype = DH6_SOLICIT;
		break;
	case DHCP6S_REQUEST:
		dh6->dh6_msgtype = DH6_REQUEST;
		break;
	case DHCP6S_RENEW:
		dh6->dh6_msgtype = DH6_RENEW;
		break;
	case DHCP6S_REBIND:
		dh6->dh6_msgtype = DH6_REBIND;
		break;
	case DHCP6S_RELEASE:
		dh6->dh6_msgtype = DH6_RELEASE;
		break;
	case DHCP6S_INFOREQ:
		dh6->dh6_msgtype = DH6_INFORM_REQ;
		break;
	default:
		dprintf(LOG_ERR, FNAME, "unexpected state");
		system("echo \"DHCPv6 client stop: unexpected state\" > /dev/console");
		exit(1);	/* XXX */
	}

	if (ev->timeouts == 0 || rapidcommit_change == 1) {
		/*
		 * A client SHOULD generate a random number that cannot easily
		 * be guessed or predicted to use as the transaction ID for
		 * each new message it sends.
		 *
		 * A client MUST leave the transaction-ID unchanged in
		 * retransmissions of a message. [RFC3315 15.1]
		 */
#ifdef HAVE_ARC4RANDOM
		ev->xid = arc4random() & DH6_XIDMASK;
#else
		ev->xid = random() & DH6_XIDMASK;
#endif
		dprintf(LOG_DEBUG, FNAME, "a new XID (%x) is generated",
		    ev->xid);
	}
	dh6->dh6_xid &= ~ntohl(DH6_XIDMASK);
	dh6->dh6_xid |= htonl(ev->xid);
	len = sizeof(*dh6);

	/*
	 * construct options
	 */
	dhcp6_init_options(&optinfo);

	/* server ID */
	switch (ev->state) {
	case DHCP6S_SOLICIT:
		if (ev->timeouts != 0) {
			ifp->send_flags &= 0x1;
		}
		break;
	case DHCP6S_REQUEST:
	case DHCP6S_RENEW:
	case DHCP6S_RELEASE:
		if (duidcpy(&optinfo.serverID, &ev->serverid)) {
			dprintf(LOG_ERR, FNAME, "failed to copy server ID");
			goto end;
		}
		break;
	}

	/* client ID */
	if (duidcpy(&optinfo.clientID, &client_duid)) {
		dprintf(LOG_ERR, FNAME, "failed to copy client ID");
		goto end;
	}

	/* rapid commit (in Solicit only) */
	if (ev->state == DHCP6S_SOLICIT &&
	    (ifp->send_flags & DHCIFF_RAPID_COMMIT)) {
		optinfo.rapidcommit = 1;
                rapidcommit_change = 1;
	}
        else {
            rapidcommit_change = 0;
        }
	// Ethan 
	optinfo.reconfig = 1; // Set Reconfigure Accept option to 1

	/*Set Vendor Class Option*/

	//

	/* elapsed time */
	if (ev->timeouts == 0) {
		clock_gettime(CLOCK_MONOTONIC, &ev->ts_start);
		optinfo.elapsed_time = 0;
	} else {
		struct timespec now, ts_diff;
		long et;

		clock_gettime(CLOCK_MONOTONIC, &now);
		ts_sub(&now, &ev->ts_start, &ts_diff);

		/*
		 * The client uses the value 0xffff to represent any elapsed
		 * time values greater than the largest time value that can be
		 * represented in the Elapsed Time option.
		 * [RFC3315 22.9.]
		 */
		if (ts_diff.tv_sec >= (MAX_ELAPSED_TIME / 100) + 1) {
			/*
			 * Perhaps we are nervous too much, but without this
			 * additional check, we would see an overflow in 248
			 * days (of no responses). 
			 */
			et = MAX_ELAPSED_TIME;
		} else {
			et = ts_diff.tv_sec * 100 + ts_diff.tv_nsec / 10000000;
			if (et >= MAX_ELAPSED_TIME)
				et = MAX_ELAPSED_TIME;
		}
		optinfo.elapsed_time = (int32_t)et;
		if (ev->state != DHCP6S_RENEW && ev->state != DHCP6S_REBIND && ev->state != DHCP6S_REQUEST) {
			if (optinfo.elapsed_time > ev->max_retrans_dur) {
				char print_ln[128];

				memset(print_ln, 0, 128);
				/* no more retries after 32 seconds */
				sprintf(print_ln, "echo \"DHCPv6 client stop: %d seconds over %d seconds\" > /dev/console", optinfo.elapsed_time, ev->max_retrans_dur);
				system(print_ln);
				unlink("/var/ip6dns");
				sal_dhcp6_set_client_server_addr("");
				sal_dhcp6_set_client_server_duid("");
				sal_dhcp6_set_client_server_refresh_time("");
				system("killall -SIGALRM pppd_1");
				exit(1);
			}
		}
	}

	/* option request options */
	if (ev->state != DHCP6S_RELEASE &&
	    dhcp6_copy_list(&optinfo.reqopt_list, &ifp->reqopt_list)) {
		dprintf(LOG_ERR, FNAME, "failed to copy requested options");
		goto end;
	}

	/* configuration information specified as event data */
	for (evd = TAILQ_FIRST(&ev->data_list); evd;
	     evd = TAILQ_NEXT(evd, link)) {
		switch(evd->type) {
		case DHCP6_EVDATA_IAPD:
			if (dhcp6_copy_list(&optinfo.iapd_list,
			    (struct dhcp6_list *)evd->data)) {
				dprintf(LOG_NOTICE, FNAME,
				    "failed to add an IAPD");
				goto end;
			}
			break;
		case DHCP6_EVDATA_IANA:
			if (dhcp6_copy_list(&optinfo.iana_list,
			    (struct dhcp6_list *)evd->data)) {
				dprintf(LOG_NOTICE, FNAME,
				    "failed to add an IAPD");
				goto end;
			}
			break;
		default:
			dprintf(LOG_ERR, FNAME, "unexpected event data (%d)",
			    evd->type);
			system("echo \"DHCPv6 client stop: unexpected event\" > /dev/console");
			exit(1);
		}
	}

	/* authentication information */
	if (set_auth(ev, &optinfo)) {
		dprintf(LOG_INFO, FNAME,
		    "failed to set authentication option");
		goto end;
	}

	/* set options in the message */
	if ((optlen = dhcp6_set_options(dh6->dh6_msgtype,
	    (struct dhcp6opt *)(dh6 + 1),
	    (struct dhcp6opt *)(buf + sizeof(buf)), &optinfo)) < 0) {
		dprintf(LOG_INFO, FNAME, "failed to construct options");
		goto end;
	}
	len += optlen;

	/* calculate MAC if necessary, and put it to the message */
	if (ev->authparam != NULL) {
		switch (ev->authparam->authproto) {
		case DHCP6_AUTHPROTO_DELAYED:
			if (ev->authparam->key == NULL)
				break;

			if (dhcp6_calc_mac((char *)dh6, len,
			    optinfo.authproto, optinfo.authalgorithm,
			    optinfo.delayedauth_offset + sizeof(*dh6),
			    ev->authparam->key)) {
				dprintf(LOG_WARNING, FNAME,
				    "failed to calculate MAC");
				goto end;
			}
			break;
		default:
			break;	/* do nothing */
		}
	}

	/*
	 * Unless otherwise specified in this document or in a document that
	 * describes how IPv6 is carried over a specific type of link (for link
	 * types that do not support multicast), a client sends DHCP messages
	 * to the All_DHCP_Relay_Agents_and_Servers.
	 * [RFC3315 Section 13.]
	 */
	dst = *sa6_allagent;
	dst.sin6_scope_id = ifp->linkid;

	if (sendto(sock, buf, len, 0, (struct sockaddr *)&dst,
	    sysdep_sa_len((struct sockaddr *)&dst)) == -1) {
		dprintf(LOG_ERR, FNAME,
		    "transmit failed: %s", strerror(errno));
		if (errno == ENETUNREACH || errno == ENETDOWN) {
			ev->max_retrans_cnt = 1;
		}
		goto end;
	}

	dprintf(LOG_DEBUG, FNAME, "");
	dprintf(LOG_DEBUG, FNAME, "------DHCPv6 Client TX Packet Start----------------");

	dprintf(LOG_DEBUG, FNAME, "send %s to %s",
	    dhcp6msgstr(dh6->dh6_msgtype), addr2str((struct sockaddr *)&dst));

	{
		struct dhcp6_optinfo optinfo2;
		struct dhcp6opt *p, *ep;
		
		dhcp6_init_options(&optinfo2);
		p = (struct dhcp6opt *)(dh6 + 1);
		ep = (struct dhcp6opt *)((char *)buf + len);
		if (dhcp6_get_options(p, ep, &optinfo2, DHCP6_SEND, NULL) < 0) {
			dprintf(LOG_DEBUG, FNAME, "failed to parse options");
		}
		dhcp6_clear_options(&optinfo2);
	}

	dprintf(LOG_DEBUG, FNAME, "------DHCPv6 Client TX Packet End----------------");
	dprintf(LOG_DEBUG, FNAME, "");

	unlink(RECV_OPT_FILE);

  end:
	dhcp6_clear_options(&optinfo);
	return;
}

/* result will be a - b */
static void
ts_sub(a, b, result)
	struct timespec *a, *b, *result;
{
	if (a->tv_sec < b->tv_sec ||
	    (a->tv_sec == b->tv_sec && a->tv_nsec < b->tv_nsec)) {
		result->tv_sec = 0;
		result->tv_nsec = 0;

		return;
	}

	result->tv_sec = a->tv_sec - b->tv_sec;
	if (a->tv_nsec < b->tv_nsec) {
		result->tv_nsec = a->tv_nsec + 1000000000 - b->tv_nsec;
		result->tv_sec -= 1;
	} else
		result->tv_nsec = a->tv_nsec - b->tv_nsec;

	return;
}

static void
client6_recv()
{
	char rbuf[BUFSIZ], cmsgbuf[BUFSIZ];
	struct msghdr mhdr;
	struct iovec iov;
	struct sockaddr_storage from;
	struct dhcp6_if *ifp;
	struct dhcp6opt *p, *ep;
	struct dhcp6_optinfo optinfo;
	ssize_t len;
	struct dhcp6 *dh6;
	struct cmsghdr *cm;
	struct in6_pktinfo *pi = NULL;

	memset(&iov, 0, sizeof(iov));
	memset(&mhdr, 0, sizeof(mhdr));

	solicit_flag = 0;
	iov.iov_base = (caddr_t)rbuf;
	iov.iov_len = sizeof(rbuf);
	mhdr.msg_name = (caddr_t)&from;
	mhdr.msg_namelen = sizeof(from);
	mhdr.msg_iov = &iov;
	mhdr.msg_iovlen = 1;
	mhdr.msg_control = (caddr_t)cmsgbuf;
	mhdr.msg_controllen = sizeof(cmsgbuf);
	if ((len = recvmsg(sock, &mhdr, 0)) < 0) {
		dprintf(LOG_ERR, FNAME, "recvmsg: %s", strerror(errno));
		return;
	}

	/* detect receiving interface */
	for (cm = (struct cmsghdr *)CMSG_FIRSTHDR(&mhdr); cm;
	     cm = (struct cmsghdr *)CMSG_NXTHDR(&mhdr, cm)) {
		if (cm->cmsg_level == IPPROTO_IPV6 &&
		    cm->cmsg_type == IPV6_PKTINFO &&
		    cm->cmsg_len == CMSG_LEN(sizeof(struct in6_pktinfo))) {
			pi = (struct in6_pktinfo *)(CMSG_DATA(cm));
		}
	}
	if (pi == NULL) {
		dprintf(LOG_NOTICE, FNAME, "failed to get packet info");
		return;
	}

	if ((ifp = find_ifconfbyid((unsigned int)pi->ipi6_ifindex)) == NULL) {
		dprintf(LOG_INFO, FNAME, "unexpected interface (%d) (rcv pid=%d)",
		    (unsigned int)pi->ipi6_ifindex, getpid());
#if 1 //brcm- for debug purpose
      dh6 = (struct dhcp6 *)rbuf;
      dprintf(LOG_DEBUG, FNAME, "receive %s from %s on ---",
            dhcp6msgstr(dh6->dh6_msgtype),
            addr2str((struct sockaddr *)&from));
#endif
		return;
	}

	if (len < sizeof(*dh6)) {
		dprintf(LOG_INFO, FNAME, "short packet (%d bytes)", len);
		return;
	}

	dh6 = (struct dhcp6 *)rbuf;

	dprintf(LOG_DEBUG, FNAME, "");
	dprintf(LOG_DEBUG, FNAME, "---DHCPv6 Client RX Packet Start--------------");

	dprintf(LOG_DEBUG, FNAME, "receive %s from %s on %s",
	    dhcp6msgstr(dh6->dh6_msgtype),
	    addr2str((struct sockaddr *)&from), ifp->ifname);

	/* get options */
	dhcp6_init_options(&optinfo);
	p = (struct dhcp6opt *)(dh6 + 1);
	ep = (struct dhcp6opt *)((char *)dh6 + len);
	if (dhcp6_get_options(p, ep, &optinfo, DHCP6_RECV, NULL) < 0) {
		dprintf(LOG_INFO, FNAME, "failed to parse options");
		return;
	}
#if DH6OPT_SOL_MAX_RT 
	if (optinfo.max_solicit_timeout >= 0) {
		recv_max_solicit_rt = optinfo.max_solicit_timeout * 1000;
	}
#endif

	dprintf(LOG_DEBUG, FNAME, "---DHCPv6 Client RX Packet End--------------");
	dprintf(LOG_DEBUG, FNAME, "");

	switch(dh6->dh6_msgtype) {
	case DH6_ADVERTISE:
		sal_dhcp6_set_client_server_refresh_time("0001-01-01T00:00:00Z");
		(void)client6_recvadvert(ifp, dh6, len, &optinfo);
		break;
	case DH6_REPLY:
		sal_dhcp6_set_client_server_addr(addr2str((struct sockaddr *)&from));
		sal_dhcp6_set_client_server_refresh_time("0001-01-01T00:00:00Z");
		(void)client6_recvreply(ifp, dh6, len, &optinfo);
		break;
	case DH6_RECONFIGURE:
		dprintf(LOG_INFO, FNAME, "recv DH6_RECONFIGURE");
		(void)client6_recvreconfig(ifp, dh6, len, &optinfo);
		
		break;
	default:
		dprintf(LOG_INFO, FNAME, "received an unexpected message (%s) "
		    "from %s", dhcp6msgstr(dh6->dh6_msgtype),
		    addr2str((struct sockaddr *)&from));
		break;
	}

	dhcp6_clear_options(&optinfo);
	return;
}

/**************************************************************************
 * FUNCTION NAME : client6_recvreconfig
 **************************************************************************
 * DESCRIPTION   :
 * Receive handler for all the RECONFIGURE messages. 
 * It is responsible for:
 *      - Performing sanity check and validating the RECONFIGURE message 
 *        against RFC requirements 
 *      - Handing over the packet to registered plugin for further 
 *        validation and acting based on the result from the plugin.
 *      - Set the state machine, timeout related params accordingly.
 *************************************************************************/
static int client6_recvreconfig(ifp, dh6, len, optinfo)
	struct dhcp6_if *ifp;
	struct dhcp6 *dh6;
	ssize_t len;
	struct dhcp6_optinfo *optinfo;
{
	struct dhcp6_event *ev = NULL;
	struct dhcp6_eventdata *evd;
	struct authparam* authparam;
	int state;
	struct dhcp6_list *ial = NULL;
	struct dhcp6_listval *op = NULL;
	int error = 0;

	/* packet validation based on Section 15.11 of RFC3315. */
	if (optinfo->serverID.duid_len == 0) {
		dprintf(LOG_DEBUG, FNAME, "no server ID option");
		return -1;
	} else {
		dprintf(LOG_DEBUG, FNAME, "server ID: %s, pref=%d",
		    duidstr(&optinfo->serverID),
		    optinfo->pref);
	}
	if (optinfo->clientID.duid_len == 0) {
		dprintf(LOG_DEBUG, FNAME, "no client ID option");
		return -1;
	}
	if (duidcmp(&optinfo->clientID, &client_duid)) {
		dprintf(LOG_DEBUG, FNAME, "client DUID mismatch");
		return -1;
	}

    if (optinfo->reconfig_msg_type == DH6OPT_RECONF_MSG_TYPE_UNDEF) {
        dprintf(LOG_DEBUG, FNAME, "Message Type not set in Reconfigure message");
        return -1;
    }

    switch(optinfo->reconfig_msg_type) {
        case DH6_RENEW:
            state = DHCP6S_RENEW;
            break;
        case DH6_INFORM_REQ:
            state = DHCP6S_INFOREQ;
            if(!TAILQ_EMPTY(&optinfo->iapd_list) || !TAILQ_EMPTY(&optinfo->iana_list)) {
                dprintf(LOG_ERR, FNAME, "IA options present in INFORM_REQ Reconfigure message");
                return -1;
            }
            break;
        default:
            dprintf(LOG_ERR, FNAME, "Invalid msg_type option in reconfigure message");
            return -1;
    }

	/* allocate new authentication parameter with 
       algorithm as Reconfigure, Proto - HMACMD5
       and RDM as monocounter
    */
	if ((authparam = new_authparam(ifp->authproto,
	    ifp->authalgorithm, ifp->authrdm)) == NULL) {
		dprintf(LOG_WARNING, FNAME, "memory allocation failed "
		    "for authentication parameters");
		return -1;
	}
	if (process_auth(authparam, dh6, len, optinfo, ifp)) {
		dprintf(LOG_DEBUG, FNAME, "failed to process authentication");
        free(authparam);
		return -1;
	}

//    ifp->reconf_in_progress = 1;

    /* Reset the Auth params to UNDEF. If using reconfigure key auth 
       protocol, the reconfigure key is used only to authenticate
       the reconfigure message, otherwise the other communication
       with the server is as normal (unauthenticated)
    */
    if(authparam && (ifp->authproto == DHCP6_AUTHPROTO_RECONFIG)) {
        memset(authparam, 0, sizeof(*authparam));
        authparam->authproto = DHCP6_AUTHPROTO_UNDEF;
        authparam->authalgorithm = DHCP6_AUTHALG_UNDEF;
        authparam->authrdm = DHCP6_AUTHRDM_UNDEF;
    }

    /* Create a renew/inform-req message */
	if ((ev = dhcp6_create_event(ifp, state)) == NULL) {
		dprintf(LOG_NOTICE, FNAME, "failed to create a new event");
		goto fail;
	}
	TAILQ_INSERT_TAIL(&ifp->event_list, ev, link);

	if ((ev->timer = dhcp6_add_timer(client6_timo, ev)) == NULL) {
		dprintf(LOG_NOTICE, FNAME,
		    "failed to create a new event timer");
		goto fail;
	}

	if (duidcpy(&ev->serverid, &optinfo->serverID)) {
		dprintf(LOG_NOTICE, FNAME, "failed to copy server ID");
		goto fail;
	}

    /* Copy the OROs from the Reconfigure message
       See the previous comment for RFC reference.
    */
    TAILQ_INIT(&ev->reconf_reqopt_list);
    if(!TAILQ_EMPTY(&optinfo->reqopt_list))
    {
        if(dhcp6_copy_list(&ev->reconf_reqopt_list, &optinfo->reqopt_list)) 
            goto fail;
    }
    /* No ORO present in Reconfigure Message. Also no IAs present. So copy
       the IAs from our saved configuration.
     */
    else if(TAILQ_EMPTY(&optinfo->iapd_list) && TAILQ_EMPTY(&optinfo->iana_list))
    {
       	if ((error = construct_confdata(ifp, ev)) != 0 ) {
        	dprintf(LOG_ERR, FNAME, "can't send message, error in construct_confdata");
            goto fail;
   		}
    }

    /* Accg to RFC 3315 - 19.4.2 - When responding to reconfigure, 
       client creates and sends the Renew message exactly in the 
       same manner as 18.1.3, with the exception that the client
       copies the ORO and any IA options from the Reconfigure
       message into the Renew message. 
       This is applicable only if the Reconfigure message sent
       by the server has ORO and IAs set.
    */
    if((state == DHCP6S_RENEW) && (!TAILQ_EMPTY(&optinfo->iapd_list) || !TAILQ_EMPTY(&optinfo->iana_list))) {
        for (op = TAILQ_FIRST(&optinfo->iapd_list); op; op = TAILQ_NEXT(op, link)) {

			ial = NULL;
			if ((ial = malloc(sizeof(*ial))) == NULL)
				goto fail;
			TAILQ_INIT(ial);

		    if (dhcp6_add_listval(ial, op->type, &op->uv, &op->sublist) == NULL)
			    goto fail;

            if ((evd = malloc(sizeof(*evd))) == NULL) {
    	    	dprintf(LOG_NOTICE, FNAME,
	    	        "failed to create a new event data");
    	    	goto fail;
    	    }
        	memset(evd, 0, sizeof(*evd));
		    evd->type = DHCP6_EVDATA_IAPD;
    		evd->data = ial;
	    	evd->event = ev;
		    evd->destructor = destruct_iadata;
    		TAILQ_INSERT_TAIL(&ev->data_list, evd, link);
       }

       for (op = TAILQ_FIRST(&optinfo->iana_list); op; op = TAILQ_NEXT(op, link)) {

			ial = NULL;
			if ((ial = malloc(sizeof(*ial))) == NULL)
				goto fail;
			TAILQ_INIT(ial);

		    if (dhcp6_add_listval(ial, op->type, &op->uv, &op->sublist) == NULL)
			    goto fail;

         	if ((evd = malloc(sizeof(*evd))) == NULL) {
	        	dprintf(LOG_NOTICE, FNAME,
		            "failed to create a new event data");
        		goto fail;
	        }
    	    memset(evd, 0, sizeof(*evd));
    		evd->type = DHCP6_EVDATA_IANA;
	    	evd->data = ial;
    		evd->event = ev;
	    	evd->destructor = destruct_iadata;
    		TAILQ_INSERT_TAIL(&ev->data_list, evd, link);
       }
    }
   
    ev->timeouts = 0;
	dhcp6_set_timeoparam(ev);
	dhcp6_reset_timer(ev);

	if ((ev->authparam = copy_authparam(authparam)) == NULL) {
		dprintf(LOG_WARNING, FNAME,
		    "failed to copy authparam");
		goto fail;
	}

    /* Send the INFORM-REQ/RENEW message out */
	client6_send(ev);

    if(authparam) {
        free(authparam);
        authparam = NULL;
    }
	return 0;

    fail:
        if(ial)
            dhcp6_clear_list(ial);
        if(ev)
            dhcp6_remove_event(ev);
        //ifp->reconf_in_progress = 0;

        if(authparam) {
            free(authparam);
            authparam = NULL;
        }
    return -1;
}



static int
client6_recvadvert(ifp, dh6, len, optinfo)
	struct dhcp6_if *ifp;
	struct dhcp6 *dh6;
	ssize_t len;
	struct dhcp6_optinfo *optinfo;
{
	struct dhcp6_serverinfo *newserver, **sp;
	struct dhcp6_event *ev;
	struct dhcp6_eventdata *evd;
	struct authparam *authparam = NULL, authparam0;

        recv_response = 1; 
	/* find the corresponding event based on the received xid */
	ev = find_event_withid(ifp, ntohl(dh6->dh6_xid) & DH6_XIDMASK);
	if (ev == NULL) {
		dprintf(LOG_INFO, FNAME, "XID mismatch");
		return (-1);
	}

	/* packet validation based on Section 15.3 of RFC3315. */
	if (optinfo->serverID.duid_len == 0) {
		dprintf(LOG_INFO, FNAME, "no server ID option");
		return (-1);
	} else {
		dprintf(LOG_DEBUG, FNAME, "server ID: %s, pref=%d",
		    duidstr(&optinfo->serverID),
		    optinfo->pref);
	}
	if (optinfo->clientID.duid_len == 0) {
		dprintf(LOG_INFO, FNAME, "no client ID option");
		return (-1);
	}
	if (duidcmp(&optinfo->clientID, &client_duid)) {
		dprintf(LOG_INFO, FNAME, "client DUID mismatch");
		return (-1);
	}

	/* validate authentication */
	authparam0 = *ev->authparam;
	if (process_auth(&authparam0, dh6, len, optinfo, ifp)) {
		dprintf(LOG_INFO, FNAME, "failed to process authentication");
		return (-1);
	}

	/*
	 * The requesting router MUST ignore any Advertise message that
	 * includes a Status Code option containing the value NoPrefixAvail
	 * [RFC3633 Section 11.1].
	 * Likewise, the client MUST ignore any Advertise message that includes
	 * a Status Code option containing the value NoAddrsAvail. 
	 * [RFC3315 Section 17.1.3].
	 * We only apply this when we are going to request an address or
	 * a prefix.
	 */
	for (evd = TAILQ_FIRST(&ev->data_list); evd;
	    evd = TAILQ_NEXT(evd, link)) {
		u_int16_t stcode;
		char *stcodestr;

		switch (evd->type) {
		case DHCP6_EVDATA_IAPD:
			stcode = DH6OPT_STCODE_NOPREFIXAVAIL;
			stcodestr = "NoPrefixAvail";
			break;
		case DHCP6_EVDATA_IANA:
			stcode = DH6OPT_STCODE_NOADDRSAVAIL;
			stcodestr = "NoAddrsAvail";
			break;
		default:
			continue;
		}
		if (dhcp6_find_listval(&optinfo->stcode_list,
		    DHCP6_LISTVAL_STCODE, &stcode, 0)) {
                        if (stcode == DH6OPT_STCODE_NOPREFIXAVAIL){
                            syslog(LOG_INFO, "%s"LOG_ERRCODE_P006, log_type_db[GENERAL_LOG],"no DHCPv6 prefix available"); 
                        } 
			dprintf(LOG_INFO, FNAME,
			    "advertise contains %s status", stcodestr);
			return (-1);
		}
	}
        if (IA_PD_no_prefix == 1){
            syslog(LOG_INFO, "%s"LOG_ERRCODE_P006, log_type_db[GENERAL_LOG],"no DHCPv6 prefix available");
            return (-1);
        }
    if (TAILQ_EMPTY(&optinfo->dns_list)) {
        dprintf(LOG_INFO, FNAME, "no nameserver");
        return (-1);
    }

	if (ev->state != DHCP6S_SOLICIT ||
	    (ifp->send_flags & DHCIFF_RAPID_COMMIT) || infreq_mode) {
		/*
		 * We expected a reply message, but do actually receive an
		 * Advertise message.  The server should be configured not to
		 * allow the Rapid Commit option.
		 * We process the message as if we expected the Advertise.
		 * [RFC3315 Section 17.1.4]
		 */
		dprintf(LOG_INFO, FNAME, "unexpected advertise");
		/* proceed anyway */
	}

	/* ignore the server if it is known */
	if (find_server(ev, &optinfo->serverID)) {
		dprintf(LOG_INFO, FNAME, "duplicated server (ID: %s)",
		    duidstr(&optinfo->serverID));
		return (-1);
	}

	/* keep the server */
	if ((newserver = malloc(sizeof(*newserver))) == NULL) {
		dprintf(LOG_WARNING, FNAME,
		    "memory allocation failed for server");
		return (-1);
	}
	memset(newserver, 0, sizeof(*newserver));

	/* remember authentication parameters */
	newserver->authparam = ev->authparam;
	newserver->authparam->flags = authparam0.flags;
	newserver->authparam->prevrd = authparam0.prevrd;
	newserver->authparam->key = authparam0.key;

	/* allocate new authentication parameter for the soliciting event */
	if ((authparam = new_authparam(ev->authparam->authproto,
	    ev->authparam->authalgorithm, ev->authparam->authrdm)) == NULL) {
		dprintf(LOG_WARNING, FNAME, "memory allocation failed "
		    "for authentication parameters");
		free(newserver);
		return (-1);
	}
	ev->authparam = authparam;

	/* copy options */
	dhcp6_init_options(&newserver->optinfo);
	if (dhcp6_copy_options(&newserver->optinfo, optinfo)) {
		dprintf(LOG_ERR, FNAME, "failed to copy options");
		if (newserver->authparam != NULL)
			free(newserver->authparam);
		free(newserver);
		return (-1);
	}
	if (optinfo->pref != DH6OPT_PREF_UNDEF)
		newserver->pref = optinfo->pref;
	newserver->active = 1;
	for (sp = &ev->servers; *sp; sp = &(*sp)->next) {
		if ((*sp)->pref != DH6OPT_PREF_MAX &&
		    (*sp)->pref < newserver->pref) {
			break;
		}
	}
	newserver->next = *sp;
	*sp = newserver;

	if (newserver->pref == DH6OPT_PREF_MAX) {
		/*
		 * If the client receives an Advertise message that includes a
		 * Preference option with a preference value of 255, the client
		 * immediately begins a client-initiated message exchange.
		 * [RFC3315 Section 17.1.2]
		 */
		ev->current_server = newserver;
		if (duidcpy(&ev->serverid,
		    &ev->current_server->optinfo.serverID)) {
			dprintf(LOG_NOTICE, FNAME, "can't copy server ID");
			return (-1); /* XXX: better recovery? */
		}
		if (construct_reqdata(ifp, &ev->current_server->optinfo, ev)) {
			dprintf(LOG_NOTICE, FNAME,
			    "failed to construct request data");
			return (-1); /* XXX */
		}

		ev->timeouts = 0;
		ev->state = DHCP6S_REQUEST;

		free(ev->authparam);
		ev->authparam = newserver->authparam;
		newserver->authparam = NULL;

		client6_send(ev);

		dhcp6_set_timeoparam(ev);
		dhcp6_reset_timer(ev);
	} else if (ev->servers->next == NULL) {
		struct timespec *rest, elapsed, ts_rt, ts_irt, timo;

		/*
		 * If this is the first advertise, adjust the timer so that
		 * the client can collect other servers until IRT elapses.
		 * XXX: we did not want to do such "low level" timer
		 *      calculation here.
		 */
		rest = dhcp6_timer_rest(ev->timer);
		ts_rt.tv_sec = ev->retrans / 1000; //retrans in msec
		ts_rt.tv_nsec = (ev->retrans % 1000) * 1000000; //calculate the remain msec and turns it to nsec
		ts_irt.tv_sec = ev->init_retrans / 1000; //init_retrans in msec
		ts_irt.tv_nsec = (ev->init_retrans % 1000) * 1000000; //calculate the remain msec and turns it to nsec
		timespec_sub(&ts_rt, rest, &elapsed);
		if (TIMESPEC_LEQ(elapsed, ts_irt))
			timespec_sub(&ts_irt, &elapsed, &timo);
		else
			timo.tv_sec = timo.tv_nsec = 0;

		dprintf(LOG_DEBUG, FNAME, "reset timer for %s to %d.%06d",
		    ifp->ifname, (int)timo.tv_sec, (int)timo.tv_nsec);

		dhcp6_set_timer(&timo, ev->timer);
	}

	return (0);
}

static struct dhcp6_serverinfo *
find_server(ev, duid)
	struct dhcp6_event *ev;
	struct duid *duid;
{
	struct dhcp6_serverinfo *s;

	for (s = ev->servers; s; s = s->next) {
		if (duidcmp(&s->optinfo.serverID, duid) == 0)
			return (s);
	}

	return (NULL);
}

static int
client6_recvreply(ifp, dh6, len, optinfo)
	struct dhcp6_if *ifp;
	struct dhcp6 *dh6;
	ssize_t len;
	struct dhcp6_optinfo *optinfo;
{
	struct dhcp6_listval *lv;
	struct dhcp6_event *ev;
	int state;
	FILE *fp = NULL;
	char uptime[256] = {0};

        recv_response = 1;
	clock_gettime(CLOCK_MONOTONIC, &recv_reply_time);
	/* find the corresponding event based on the received xid */
	ev = find_event_withid(ifp, ntohl(dh6->dh6_xid) & DH6_XIDMASK);
	if (ev == NULL) {
		dprintf(LOG_INFO, FNAME, "XID mismatch");
		return (-1);
	}

	state = ev->state;
	if (state != DHCP6S_INFOREQ &&
	    state != DHCP6S_REQUEST &&
	    state != DHCP6S_RENEW &&
	    state != DHCP6S_REBIND &&
	    state != DHCP6S_RELEASE &&
	    (state != DHCP6S_SOLICIT ||
	     !(ifp->send_flags & DHCIFF_RAPID_COMMIT))) {
		dprintf(LOG_INFO, FNAME, "unexpected reply");
		return (-1);
	}

	/* A Reply message must contain a Server ID option */
	if (optinfo->serverID.duid_len == 0) {
		dprintf(LOG_INFO, FNAME, "no server ID option");
		return (-1);
	}

	/*
	 * DUID in the Client ID option (which must be contained for our
	 * client implementation) must match ours.
	 */
	if (optinfo->clientID.duid_len == 0) {
		dprintf(LOG_INFO, FNAME, "no client ID option");
		return (-1);
	}
	if (duidcmp(&optinfo->clientID, &client_duid)) {
		dprintf(LOG_INFO, FNAME, "client DUID mismatch");
		return (-1);
	}

	/* validate authentication */
	if (process_auth(ev->authparam, dh6, len, optinfo, ifp)) {
		dprintf(LOG_INFO, FNAME, "failed to process authentication");
		return (-1);
	}

	/*
	 * If the client included a Rapid Commit option in the Solicit message,
	 * the client discards any Reply messages it receives that do not
	 * include a Rapid Commit option.
	 * (should we keep the server otherwise?)
	 * [RFC3315 Section 17.1.4]
	 */
	if (state == DHCP6S_SOLICIT &&
	    (ifp->send_flags & DHCIFF_RAPID_COMMIT) &&
	    !optinfo->rapidcommit) {
		dprintf(LOG_INFO, FNAME, "no rapid commit");
		return (-1);
	}

	/*
	 * The client MAY choose to report any status code or message from the
	 * status code option in the Reply message.
	 * [RFC3315 Section 18.1.8]
	 */
	for (lv = TAILQ_FIRST(&optinfo->stcode_list); lv;
	     lv = TAILQ_NEXT(lv, link)) {
		dprintf(LOG_INFO, FNAME, "status code: %s",
		    dhcp6_stcodestr(lv->val_num16));
		if (lv->val_num16 != 0) {
			/* status code != success*/
			return (-1);
		}
	}
        
        if (IA_PD_no_prefix == 1)
            return (-1);
	
        if (!TAILQ_EMPTY(&optinfo->dns_list)) {
		struct dhcp6_listval *d;
		int i = 0; 
                dns_changed = "";
		for (d = TAILQ_FIRST(&optinfo->dns_list); d;
		     d = TAILQ_NEXT(d, link), i++) {
			info_printf("nameserver[%d] %s",
			    i, in6addr2str(&d->val_addr6, 0));
			if (i == 0) {
                            if (strncmp(sal_wan_get_ipv6_con_dns1_t(PPPOE_WAN_DEFAULT_IP_INTERFACE), in6addr2str(&d->val_addr6, 0),
                                sizeof(in6addr2str(&d->val_addr6, 0))) != 0)
                                dns_changed = "1"; 
			        sal_wan_set_ipv6_con_dns1_t(PPPOE_WAN_DEFAULT_IP_INTERFACE, in6addr2str(&d->val_addr6, 0));
			} 
                        else if (i == 1) {
                            if (strncmp(sal_wan_get_ipv6_con_dns2_t(PPPOE_WAN_DEFAULT_IP_INTERFACE), in6addr2str(&d->val_addr6, 0),
                                sizeof(in6addr2str(&d->val_addr6, 0))) != 0)
                                dns_changed = "1";
				sal_wan_set_ipv6_con_dns2_t(PPPOE_WAN_DEFAULT_IP_INTERFACE, in6addr2str(&d->val_addr6, 0));
			}
		}
                                
#if 1 //brcm
//		if(state == DHCP6S_RENEW || state == DHCP6S_REBIND)
//			unlink("/var/ip6dns");

//		updateDhcp6sConfDnsList(optinfo);
#endif
	} else {
		if (ev->state != DHCP6S_RELEASE) {
			dprintf(LOG_INFO, FNAME, "no nameserver");
			return (-1);
		}
	}

	if (!TAILQ_EMPTY(&optinfo->dnsname_list)) {
		struct dhcp6_listval *d;
		int i = 0;

		for (d = TAILQ_FIRST(&optinfo->dnsname_list); d;
		     d = TAILQ_NEXT(d, link), i++) {
			info_printf("Domain search list[%d] %s",
			    i, d->val_vbuf.dv_buf);
		}
	}

	if (!TAILQ_EMPTY(&optinfo->ntp_list)) {
		struct dhcp6_listval *d;
		int i = 0;

		for (d = TAILQ_FIRST(&optinfo->ntp_list); d;
		     d = TAILQ_NEXT(d, link), i++) {
			info_printf("NTP server[%d] %s",
			    i, in6addr2str(&d->val_addr6, 0));
		}
	}

	if (!TAILQ_EMPTY(&optinfo->sip_list)) {
		struct dhcp6_listval *d;
		int i = 0;

		for (d = TAILQ_FIRST(&optinfo->sip_list); d;
		     d = TAILQ_NEXT(d, link), i++) {
			info_printf("SIP server address[%d] %s",
			    i, in6addr2str(&d->val_addr6, 0));
		}
	}

	if (!TAILQ_EMPTY(&optinfo->sipname_list)) {
		struct dhcp6_listval *d;
		int i = 0;

		for (d = TAILQ_FIRST(&optinfo->sipname_list); d;
		     d = TAILQ_NEXT(d, link), i++) {
			info_printf("SIP domain name[%d] %s",
			    i, d->val_vbuf.dv_buf);
		}
	}

	/*
	 * Call the configuration script, if specified, to handle various
	 * configuration parameters.
	 */
	if (ifp->scriptpath != NULL && strlen(ifp->scriptpath) != 0) {
		dprintf(LOG_DEBUG, FNAME, "executes %s", ifp->scriptpath);

		if (state == DHCP6S_SOLICIT || state == DHCP6S_REQUEST) {
			if (strcmp(sal_wan_get_ipv6_con_state_t(PPPOE_WAN_DEFAULT_IP_INTERFACE), "1") != 0) {
				fp = fopen("/proc/uptime", "r");
				if (fp) {
					fread(uptime, sizeof(uptime), 1, fp);
					uptime[strlen(uptime) -1] = '\0';
					fclose(fp);
				}
				sal_wan_set_ipv6_con_uptime_t(PPPOE_WAN_DEFAULT_IP_INTERFACE, uptime);
				system("/bin/touch /tmp/ipv6_wan_up");
			}
			sal_wan_set_ipv6_con_state_t(PPPOE_WAN_DEFAULT_IP_INTERFACE, "1");
		}

		client6_script(ifp->scriptpath, state, optinfo);
	}

	/*
	 * Set refresh timer for configuration information specified in
	 * information-request.  If the timer value is specified by the server
	 * in an information refresh time option, use it; use the protocol
	 * default otherwise.
	 */
	if (state == DHCP6S_INFOREQ) {
		int64_t refreshtime = DHCP6_IRT_DEFAULT;

		if (optinfo->refreshtime != DH6OPT_REFRESHTIME_UNDEF)
			refreshtime = optinfo->refreshtime;

		ifp->timer = dhcp6_add_timer(client6_expire_refreshtime, ifp);
		if (ifp->timer == NULL) {
			dprintf(LOG_WARNING, FNAME,
			    "failed to add timer for refresh time");
		} else {
			struct timespec tv;

			tv.tv_sec = (long)refreshtime;
			tv.tv_nsec = 0;

			if (tv.tv_sec < 0) {
				/*
				 * XXX: tv_sec can overflow for an
				 * unsigned 32bit value.
				 */
				dprintf(LOG_WARNING, FNAME,
				    "refresh time is too large: %lu",
				    (u_int32_t)refreshtime);
				tv.tv_sec = 0x7fffffff;	/* XXX */
			}

			dhcp6_set_timer(&tv, ifp->timer);
		}
	} else if (optinfo->refreshtime != DH6OPT_REFRESHTIME_UNDEF) {
		/*
		 * draft-ietf-dhc-lifetime-02 clarifies that refresh time
		 * is only used for information-request and reply exchanges.
		 */
		dprintf(LOG_INFO, FNAME,
		    "unexpected information refresh time option (ignored)");
	}

	/* update stateful configuration information */
	if (state != DHCP6S_RELEASE) {
		update_ia(IATYPE_PD, &optinfo->iapd_list, ifp,
		    &optinfo->serverID, ev->authparam);
		update_ia(IATYPE_NA, &optinfo->iana_list, ifp,
		    &optinfo->serverID, ev->authparam);
	}

	dhcp6_remove_event(ev);

	if (state == DHCP6S_RELEASE) {
		/*
		 * When the client receives a valid Reply message in response
		 * to a Release message, the client considers the Release event
		 * completed, regardless of the Status Code option(s) returned
		 * by the server.
		 * [RFC3315 Section 18.1.8]
		 */
		check_exit();
	}

	dprintf(LOG_DEBUG, FNAME, "got an expected reply, sleeping.");

	if (infreq_mode) {
		exit_ok = 1;
		free_resources(NULL);
		unlink(pid_file);
		check_exit();
	}
	return (0);
}

static struct dhcp6_event *
find_event_withid(ifp, xid)
	struct dhcp6_if *ifp;
	u_int32_t xid;
{
	struct dhcp6_event *ev;

	for (ev = TAILQ_FIRST(&ifp->event_list); ev;
	     ev = TAILQ_NEXT(ev, link)) {
		if (ev->xid == xid)
			return (ev);
	}

	return (NULL);
}

static int
process_auth(authparam, dh6, len, optinfo, ifp)
	struct authparam *authparam;
	struct dhcp6 *dh6;
	ssize_t len;
	struct dhcp6_optinfo *optinfo;
	struct dhcp6_if* ifp;
{
	struct keyinfo *key = NULL;
	int authenticated = 0;

	switch (optinfo->authproto) {
	case DHCP6_AUTHPROTO_UNDEF:
		/* server did not provide authentication option */
		break;
	case DHCP6_AUTHPROTO_DELAYED:
		if ((optinfo->authflags & DHCP6OPT_AUTHFLAG_NOINFO)) {
			dprintf(LOG_INFO, FNAME, "server did not include "
			    "authentication information");
			break;
		}

		if (optinfo->authalgorithm != DHCP6_AUTHALG_HMACMD5) {
			dprintf(LOG_INFO, FNAME, "unknown authentication "
			    "algorithm (%d)", optinfo->authalgorithm);
			break;
		}

		if (optinfo->authrdm != DHCP6_AUTHRDM_MONOCOUNTER) {
			dprintf(LOG_INFO, FNAME,"unknown RDM (%d)",
			    optinfo->authrdm);
			break;
		}

		/*
		 * Replay protection.  If we do not know the previous RD value,
		 * we accept the message anyway (XXX).
		 */
		if ((authparam->flags & AUTHPARAM_FLAGS_NOPREVRD)) {
			dprintf(LOG_WARNING, FNAME, "previous RD value is "
			    "unknown (accept it)");
		} else {
			if (dhcp6_auth_replaycheck(optinfo->authrdm,
			    authparam->prevrd, optinfo->authrd)) {
				dprintf(LOG_INFO, FNAME,
				    "possible replay attack detected");
				break;
			}
		}

		/* identify the secret key */
		if ((key = authparam->key) != NULL) {
			/*
			 * If we already know a key, its identification should
			 * match that contained in the received option.
			 * (from Section 21.4.5.1 of RFC3315)
			 */
			if (optinfo->delayedauth_keyid != key->keyid ||
			    optinfo->delayedauth_realmlen != key->realmlen ||
			    memcmp(optinfo->delayedauth_realmval, key->realm,
			    key->realmlen) != 0) {
				dprintf(LOG_INFO, FNAME,
				    "authentication key mismatch");
				break;
			}
		} else {
			key = find_key(optinfo->delayedauth_realmval,
			    optinfo->delayedauth_realmlen,
			    optinfo->delayedauth_keyid);
			if (key == NULL) {
				dprintf(LOG_INFO, FNAME, "failed to find key "
				    "provided by the server (ID: %x)",
				    optinfo->delayedauth_keyid);
				break;
			} else {
				dprintf(LOG_DEBUG, FNAME, "found key for "
				    "authentication: %s", key->name);
			}
			authparam->key = key;
		}

		/* check for the key lifetime */
		if (dhcp6_validate_key(key)) {
			dprintf(LOG_INFO, FNAME, "key %s has expired",
			    key->name);
			break;
		}

		/* validate MAC */
		if (dhcp6_verify_mac((char *)dh6, len, optinfo->authproto,
		    optinfo->authalgorithm,
		    optinfo->delayedauth_offset + sizeof(*dh6), key) == 0) {
			dprintf(LOG_DEBUG, FNAME, "message authentication "
			    "validated");
			authenticated = 1;
		} else {
			dprintf(LOG_INFO, FNAME, "invalid message "
			    "authentication");
		}

		break;
	case DHCP6_AUTHPROTO_RECONFIG:
		if ((optinfo->authflags & DHCP6OPT_AUTHFLAG_NOINFO)) {
			dprintf(LOG_DEBUG, FNAME, "server did not include "
			    "authentication information");
			break;
		}

		if (optinfo->authalgorithm != DHCP6_AUTHALG_HMACMD5) {
			dprintf(LOG_DEBUG, FNAME, "unknown authentication "
			    "algorithm (%d)", optinfo->authalgorithm);
			break;
		}

		if (optinfo->authrdm != DHCP6_AUTHRDM_MONOCOUNTER) {
			dprintf(LOG_DEBUG, FNAME,"unknown RDM (%d)",
			    optinfo->authrdm);
			break;
		}

		/*
		 * Replay protection.  If we do not know the previous RD value,
		 * we accept the message anyway (XXX).
		 */
		if ((authparam->flags & AUTHPARAM_FLAGS_NOPREVRD)) {
			dprintf(LOG_WARNING, FNAME, "previous RD value is "
			    "unknown (accept it)");
		} else {
			if (dhcp6_auth_replaycheck(optinfo->authrdm,
			    authparam->prevrd, optinfo->authrd)) {
				dprintf(LOG_DEBUG, FNAME,
				    "possible replay attack detected");
				break;
			}
		}

        /* If this is a Reply message containing a Reconfigure Key,
         * then, we need to set our interface authentication 
         * algorithm, protocol, and rdm accordingly to reflect
         * RECONFIGURE KEY AUTHENTICATION protocol. Also, we need
         * to record the key for further use
         */
        if(optinfo->reconfigauth_type == DH6_AUTH_RECONF_TYPE_KEY && dh6->dh6_msgtype == DH6_REPLY) {  
            ifp->authproto = optinfo->authproto;
            ifp->authalgorithm = optinfo->authalgorithm;
            ifp->authrdm = optinfo->authrdm;

            memcpy(ifp->reconfigauth_key, optinfo->reconfigauth_val, sizeof(optinfo->reconfigauth_val));

            return (0);
        } else if(optinfo->reconfigauth_type == DH6_AUTH_RECONF_TYPE_HMACMD5 && dh6->dh6_msgtype == DH6_RECONFIGURE) {
            /* Check if we have a key recorded, if so then validate the incoming
             * message with the recorded key
             */

            if(ifp->reconfigauth_key == NULL) {
                dprintf(LOG_ERR, FNAME, "No reconfigure key found to authenticate the message");
                return -1;
            }

            if((key = (struct keyinfo *)malloc(sizeof(struct keyinfo))) == NULL)
                return -1;
            memset(key, 0, sizeof(struct keyinfo));
            if((key->secret = (char *)malloc(sizeof(char) * sizeof(ifp->reconfigauth_key))) == NULL) {
                free(key);
                key = NULL;
                return -1;
            }
            memcpy(key->secret, ifp->reconfigauth_key, sizeof(ifp->reconfigauth_key));
            key->secretlen = strlen(key->secret);
            key->expire = 0;

    		/* check for the key lifetime */
	    	if (dhcp6_validate_key(key)) {
		    	dprintf(LOG_DEBUG, FNAME, "key %s has expired",
			        key->name);
                free(key->secret);
                free(key);
	    		break;
		    }

		    /* validate MAC */
		    if (dhcp6_verify_mac((char *)dh6, len, optinfo->authproto,
		        optinfo->authalgorithm,
		        optinfo->reconfigauth_offset + sizeof(*dh6), key) == 0) {
			    dprintf(LOG_DEBUG, FNAME, "message authentication "
			        "validated");
			    authenticated = 1;
		    } else {
			    dprintf(LOG_DEBUG, FNAME, "invalid message "
			    "authentication");
		    }
            
            free(key->secret);
            free(key);
       }
       else {
            dprintf(LOG_ERR, FNAME, "Only a Reply/Reconfigure message can contain Reconfigure Key Auth Params");
            return -1;
       }
	    break;




	default:
		dprintf(LOG_INFO, FNAME, "server sent unsupported "
		    "authentication protocol (%d)", optinfo->authproto);
		break;
	}

	if (authenticated == 0) {
		if (authparam->authproto != DHCP6_AUTHPROTO_UNDEF) {
			dprintf(LOG_INFO, FNAME, "message not authenticated "
			    "while authentication required");

			/*
			 * Right now, we simply discard unauthenticated
			 * messages.
			 */
			return (-1);
		}
	} else {
		/* if authenticated, update the "previous" RD value */
		authparam->prevrd = optinfo->authrd;
		authparam->flags &= ~AUTHPARAM_FLAGS_NOPREVRD;
	}

	return (0);
}

static int
set_auth(ev, optinfo)
	struct dhcp6_event *ev;
	struct dhcp6_optinfo *optinfo;
{
	struct authparam *authparam = ev->authparam;

	if (authparam == NULL)
		return (0);

	optinfo->authproto = authparam->authproto;
	optinfo->authalgorithm = authparam->authalgorithm;
	optinfo->authrdm = authparam->authrdm;

	switch (authparam->authproto) {
	case DHCP6_AUTHPROTO_UNDEF: /* we simply do not need authentication */
		return (0);
	case DHCP6_AUTHPROTO_DELAYED:
		if (ev->state == DHCP6S_INFOREQ) {
			/*
			 * In the current implementation, delayed
			 * authentication for Information-request and Reply
			 * exchanges doesn't work.  Specification is also
			 * unclear on this usage.
			 */
			dprintf(LOG_WARNING, FNAME, "delayed authentication "
			    "cannot be used for Information-request yet");
			return (-1);
		}

		if (ev->state == DHCP6S_SOLICIT) {
			optinfo->authflags |= DHCP6OPT_AUTHFLAG_NOINFO;
			return (0); /* no auth information is needed */
		}

		if (authparam->key == NULL) {
			dprintf(LOG_INFO, FNAME,
			    "no authentication key for %s",
			    dhcp6_event_statestr(ev));
			return (-1);
		}

		if (dhcp6_validate_key(authparam->key)) {
			dprintf(LOG_INFO, FNAME, "key %s is invalid",
			    authparam->key->name);
			return (-1);
		}

		if (get_rdvalue(optinfo->authrdm, &optinfo->authrd,
		    sizeof(optinfo->authrd))) {
			dprintf(LOG_ERR, FNAME, "failed to get a replay "
			    "detection value");
			return (-1);
		}

		optinfo->delayedauth_keyid = authparam->key->keyid;
		optinfo->delayedauth_realmlen = authparam->key->realmlen;
		optinfo->delayedauth_realmval =
		    malloc(optinfo->delayedauth_realmlen);
		if (optinfo->delayedauth_realmval == NULL) {
			dprintf(LOG_ERR, FNAME, "failed to allocate memory "
			    "for authentication realm");
			return (-1);
		}
		memcpy(optinfo->delayedauth_realmval, authparam->key->realm,
		    optinfo->delayedauth_realmlen);

		break;
	case DHCP6_AUTHPROTO_RECONFIG:
		return (0);

	default:
		dprintf(LOG_ERR, FNAME, "unsupported authentication protocol "
		    "%d", authparam->authproto);
		return (-1);
	}

	return (0);
}

static void
info_printf(const char *fmt, ...)
{
	va_list ap;
	char logbuf[LINE_MAX];

	va_start(ap, fmt);
	vsnprintf(logbuf, sizeof(logbuf), fmt, ap);

	dprintf(LOG_DEBUG, FNAME, "%s", logbuf);
	if (infreq_mode)
		printf("%s\n", logbuf);

	return;
}

#if 1 //brcm
const char *f_ip6Dns     = "/var/ip6dns";
//const char *f_dhcp6sConf = "/etc/dhcp6s.conf";
const char *f_dhcp6sConf = "/tmp/dhcp6s.conf";
const char *f_dhcp6sPid  = "/var/run/dhcp6s.pid";

extern int bcmSystemEx(char *command, int printFlag);
static int isDhcp6sDnsListChanged __P((struct dhcp6_optinfo *));

/***************************************************************************
 * Function:
 *    int isDhcp6sDnsListChanged(struct dhcp6_optinfo *opt)
 * Description:
 *    This function compares the dns list captured from the dhcp6s reply
 *    from the WAN interface with the dns list in the existing dhcp6s.conf
 *    and finds out if there is any change in the list.
 * Parameters:
 *    *opt  (IN) dhcp6 option info pointer.
 * Returns:
 *    1 if the dns list has changed. 0 otherwise
 ***************************************************************************/
int isDhcp6sDnsListChanged(struct dhcp6_optinfo *opt)
{
   FILE  *fp;
   int   dnsChange;
   struct dhcp6_listval *d;
   char  *dns, *token, *nextToken;
   char  line[256];

   /* open the existing dhcp6s.conf file for read */
   if ((fp = fopen(f_dhcp6sConf, "r")) == NULL)
   {
      /* error */
      dprintf(LOG_WARNING, FNAME, "failed to open %s", f_dhcp6sConf);
      return 1;   /* dns has changed */
   }

   /* First, we want to verify if the new dns list is already in
    * the existing dhcp6s.conf file.
    */
   dnsChange = 0;
   for (d = TAILQ_FIRST(&opt->dns_list); (!dnsChange && d); d = TAILQ_NEXT(d, link))
   {
      dnsChange = 1;

      /* start from the beginning of the file */
      fseek(fp, 0L, SEEK_SET);
      while (dnsChange && (fgets(line, sizeof(line), fp) != NULL))
      {
         /* look for domain-name-servers statement in the conf file */
         if (token = strstr(line, "domain-name-servers"))
         {
            /* skip the domain-name-servers token */
            strtok_r(token, " ;", &nextToken);

            /* parse the dns address tokens in the statement */
            while (dns = strtok_r(NULL, " ;", &nextToken))
            {
               if (strcmp(dns, in6addr2str(&d->val_addr6, 0)) == 0)
               {
                  /* this dns address is already in the conf file */
                  dnsChange = 0;
                  break;
               }
            }
         }
      }
   }

   /* return if the dns list has a new dns address */
   if (dnsChange)
   {
      fclose(fp);
      return dnsChange;
   }

   /* Now, we want to verify if there is any dns address in the
    * existing conf file no longer in the new dns list.
    */
   dnsChange = 0;
   fseek(fp, 0L, SEEK_SET);
   while (!dnsChange && (fgets(line, sizeof(line), fp) != NULL))
   {
      /* look for domain-name-servers statement in the conf file */
      if (token = strstr(line, "domain-name-servers"))
      {
         /* skip the domain-name-servers token */
         strtok_r(token, " ;", &nextToken);

         /* parse the dns address tokens in the statement */
         while (!dnsChange && (dns = strtok_r(NULL, " ;", &nextToken)))
         {
            /* See if this dns address is in the new dns list */
            dnsChange = 1;
		      for (d = TAILQ_FIRST(&opt->dns_list); d; d = TAILQ_NEXT(d, link))
		      {
               if (strcmp(dns, in6addr2str(&d->val_addr6, 0)) == 0)
               {
                  /* this dns address is in the new list */
                  dnsChange = 0;
                  break;
               }
		      }
         }
      }
   }
   fclose(fp);

   return dnsChange;

}  /* End of isDhcp6sDnsListChanged() */

/***************************************************************************
 * Function:
 *    int updateDhcp6sConfDnsList(struct dhcp6_optinfo *opt)
 * Description:
 *    This function creates or updates the dhcp6s.conf file with the dns
 *    info given in *opt, and starts the dhcp6s daemon.
 * Parameters:
 *    *opt  (IN) dhcp6 option info pointer.
 * Returns:
 *    0 if SUCCESS otherwise -1


Ethan: save domain name server ip into /var/ip6dns
 ***************************************************************************/
int updateDhcp6sConfDnsList(struct dhcp6_optinfo *opt)
{
   FILE  *fp_ip6Dns;
   struct dhcp6_listval *d;

   if(access(f_ip6Dns,F_OK)==0)
	return 0;

   if ((fp_ip6Dns = fopen(f_ip6Dns, "w")) == NULL)
   {
      /* error */
      dprintf(LOG_ERR, FNAME, "failed to open %s", f_ip6Dns);
      return -1;
   }

   for (d = TAILQ_FIRST(&opt->dns_list); d; d = TAILQ_NEXT(d, link))
   {
      fprintf(fp_ip6Dns, "%s\n", in6addr2str(&d->val_addr6, 0));
   }
   fclose(fp_ip6Dns);

   system("/usr/sbin/rc dhcp6 restart");
   return 0;

}  /* End of updateDhcp6sConfDnsList() */
#endif
