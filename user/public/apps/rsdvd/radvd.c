/*
 *
 *   Authors:
 *    Pedro Roque		<roque@di.fc.ul.pt>
 *    Lars Fenneberg		<lf@elemental.net>
 *
 *   This software is Copyright 1996-2000 by the above mentioned author(s),
 *   All Rights Reserved.
 *
 *   The license which is distributed with this software in the file COPYRIGHT
 *   applies to this software. If your distribution is missing this file, you
 *   may request it from <pekkas@netcore.fi>.
 *
 */

#include "config.h"
#include "includes.h"
#include "radvd.h"
#include "pathnames.h"
#include "log_api.h"
#include "sal/sal_ipv6.h"
#include "sal/sal_lan.h"

#include "scutil.h"
#include <math.h>

#ifdef HAVE_NETLINK
#include "netlink.h"
#endif

#include <poll.h>

struct Interface *IfaceList = NULL;

#ifdef HAVE_GETOPT_LONG

char usage_str[] = {
"\n"
"  -c, --configtest       Parse the config file and exit.\n"
"  -C, --config=PATH      Sets the config file.  Default is /etc/radvd.conf.\n"
"  -d, --debug=NUM        Sets the debug level.  Values can be 1, 2, 3, 4 or 5.\n"
"  -D, --deprecate        Switch to deprecate mode.\n"
"  -f, --facility=NUM     Sets the logging facility.\n"
"  -h, --help             Show this help screen.\n"
"  -l, --logfile=PATH     Sets the log file.\n"
"  -m, --logmethod=X      Sets the log method to one of: syslog, stderr, stderr_syslog, logfile, or none.\n"
"  -p, --pidfile=PATH     Sets the pid file.\n"
"  -t, --chrootdir=PATH   Chroot to the specified path.\n"
"  -u, --username=USER    Switch to the specified user.\n"
"  -n, --nodaemon         Prevent the daemonizing.\n"
"  -v, --version          Print the version and quit.\n"
};

struct option prog_opt[] = {
	{"debug", 1, 0, 'd'},
	{"deprecate", 0, 0, 'D'},
	{"configtest", 0, 0, 'c'},
	{"config", 1, 0, 'C'},
	{"pidfile", 1, 0, 'p'},
	{"logfile", 1, 0, 'l'},
	{"logmethod", 1, 0, 'm'},
	{"facility", 1, 0, 'f'},
	{"username", 1, 0, 'u'},
	{"chrootdir", 1, 0, 't'},
	{"version", 0, 0, 'v'},
	{"help", 0, 0, 'h'},
	{"singleprocess", 0, 0, 's'},
	{"nodaemon", 0, 0, 'n'},
	{NULL, 0, 0, 0}
};

#else

char usage_str[] =
	"[-hsvcnD] [-d level] [-C config_file] [-m log_method] [-l log_file]\n"
	"\t[-f facility] [-p pid_file] [-u username] [-t chrootdir]";

#endif

extern FILE *yyin;

char *conf_file = NULL;
char *pname;
int sock = -1;
int deprecate_flag = 0;

volatile int sighup_received = 0;
volatile int sigterm_received = 0;
volatile int sigint_received = 0;
volatile int sigusr1_received = 0;

void sighup_handler(int sig);
void sigterm_handler(int sig);
void sigint_handler(int sig);
void sigusr1_handler(int sig);
void timer_handler(void *data);
void kickoff_adverts(void);
void version(void);
void usage(void);
int drop_root_privileges(const char *);
int readin_config(char *);
int check_conffile_perm(const char *, const char *);
pid_t strtopid(char const * pidstr);
void write_pid_file(char const *);
void main_loop(void);

#define LINE_LENGTH 128
#define IPV6_ADDR_GLOBAL	0x0000U

int
main(int argc, char *argv[])
{
	int c, log_method;
	char *logfile, *pidfile;
	int facility;
	char *username = NULL;
	char *chrootdir = NULL;
	int configtest = 0;
	int daemonize = 1;
#ifdef HAVE_GETOPT_LONG
	int opt_idx;
#endif

	pname = ((pname=strrchr(argv[0],'/')) != NULL)?pname+1:argv[0];

	srand((unsigned int)time(NULL));

	log_method = L_STDERR_SYSLOG;
	logfile = PATH_RADVD_LOG;
	conf_file = PATH_RADVD_CONF;
	facility = LOG_FACILITY;
	pidfile = PATH_RADVD_PID;

	/* parse args */
#define OPTIONS_STR "d:C:l:m:p:t:u:vhcsnD"
#ifdef HAVE_GETOPT_LONG
	while ((c = getopt_long(argc, argv, OPTIONS_STR, prog_opt, &opt_idx)) > 0)
#else
	while ((c = getopt(argc, argv, OPTIONS_STR)) > 0)
#endif
	{
		switch (c) {
		case 'C':
			conf_file = optarg;
			break;
		case 'd':
			set_debuglevel(atoi(optarg));
			break;
		case 'D':
			deprecate_flag = 1;
			break;
		case 'f':
			facility = atoi(optarg);
			break;
		case 'l':
			logfile = optarg;
			break;
		case 'p':
			pidfile = optarg;
			break;
		case 'm':
			if (!strcmp(optarg, "syslog"))
			{
				log_method = L_SYSLOG;
			}
			else if (!strcmp(optarg, "stderr_syslog"))
			{
				log_method = L_STDERR_SYSLOG;
			}
			else if (!strcmp(optarg, "stderr"))
			{
				log_method = L_STDERR;
			}
			else if (!strcmp(optarg, "logfile"))
			{
				log_method = L_LOGFILE;
			}
			else if (!strcmp(optarg, "none"))
			{
				log_method = L_NONE;
			}
			else
			{
				fprintf(stderr, "%s: unknown log method: %s\n", pname, optarg);
				exit(1);
			}
			break;
		case 't':
			chrootdir = strdup(optarg);
			break;
		case 'u':
			username = strdup(optarg);
			break;
		case 'v':
			version();
			break;
		case 'c':
			configtest = 1;
			break;
		case 's':
			fprintf(stderr, "privsep is not optional.  This options will be removed in a near future release.");
			break;
		case 'n':
			daemonize = 0;
			break;
		case 'h':
			usage();
#ifdef HAVE_GETOPT_LONG
		case ':':
			fprintf(stderr, "%s: option %s: parameter expected\n", pname,
				prog_opt[opt_idx].name);
			exit(1);
#endif
		case '?':
			exit(1);
		}
	}

	if (chrootdir) {
		if (!username) {
			fprintf(stderr, "Chroot as root is not safe, exiting\n");
			exit(1);
		}

		if (chroot(chrootdir) == -1) {
			perror("chroot");
			exit (1);
		}

		if (chdir("/") == -1) {
			perror("chdir");
			exit (1);
		}
		/* username will be switched later */
	}

	if (configtest) {
		log_method = L_STDERR;
	}

	if (log_open(log_method, pname, logfile, facility) < 0) {
		perror("log_open");
		exit(1);
	}

	if (!configtest) {
		flog(LOG_INFO, "version %s started", VERSION);
	}

	/* get a raw socket for sending and receiving ICMPv6 messages */
	sock = open_icmpv6_socket();
	if (sock < 0) {
		perror("open_icmpv6_socket");
		exit(1);
	}

	/* check that 'other' cannot write the file
         * for non-root, also that self/own group can't either
         */
	if (check_conffile_perm(username, conf_file) < 0) {
		if (get_debuglevel() == 0) {
			flog(LOG_ERR, "Exiting, permissions on conf_file invalid.\n");
			exit(1);
		}
		else
			flog(LOG_WARNING, "Insecure file permissions, but continuing anyway");
	}

	/* if we know how to do it, check whether forwarding is enabled */
	if (check_ip6_forwarding()) {
		flog(LOG_WARNING, "IPv6 forwarding seems to be disabled, but continuing anyway.");
	}

	/* parse config file */
	if (readin_config(conf_file) < 0) {
		flog(LOG_ERR, "Exiting, failed to read config file.\n");
		exit(1);
	}

	if (configtest) {
		fprintf(stderr, "Syntax OK\n");
		exit(0);
	}

#ifdef USE_PRIVSEP
	dlog(LOG_DEBUG, 3, "Initializing privsep");
	if (privsep_init() < 0) {
		perror("Failed to initialize privsep.");
		exit(1);
	}
#endif

	/* drop root privileges if requested. */
	if (username) {
		if (drop_root_privileges(username) < 0) {
			perror("drop_root_privileges");
			exit(1);
		}
	}

	/*
	 * okay, config file is read in, socket and stuff is setup, so
	 * lets fork now...
	 */

	if (get_debuglevel() == 0) {

		if (daemonize) {
			/* Detach from controlling terminal */
			if (daemon(0, 0) < 0)
				perror("daemon");
		}
	}

	write_pid_file(pidfile);

	/*
	 *	config signal handlers
	 */
	signal(SIGHUP, sighup_handler);
	signal(SIGTERM, sigterm_handler);
	signal(SIGINT, sigint_handler);
	signal(SIGUSR1, sigusr1_handler);

	kickoff_adverts();
	main_loop();
	flog(LOG_INFO, "removing %s", pidfile);
	unlink(pidfile);

	return 0;
}


pid_t strtopid(char const * pidstr)
{
	return atol(pidstr);
}

void write_pid_file(char const * pidfile)
{
	int fd, ret;
	char pidstr[32];

	if ((fd = open(pidfile, O_RDONLY, 0)) > 0)
	{
		ret = read(fd, pidstr, sizeof(pidstr) - 1);
		if (ret < 0)
		{
			flog(LOG_ERR, "cannot read radvd pid file, terminating: %s", strerror(errno));
			exit(1);
		}
		if (ret > 0) {
				pid_t pid;
				pidstr[ret] = '\0';
				pid = strtopid(pidstr);
				if (pid > 0 && !kill(pid, 0)) {
					flog(LOG_ERR, "radvd already running, terminating.");
					exit(1);
				}
		}
		close(fd);
		fd = open(pidfile, O_CREAT|O_TRUNC|O_WRONLY, 0644);
	}
	else	/* FIXME: not atomic if pidfile is on an NFS mounted volume */
		fd = open(pidfile, O_CREAT|O_EXCL|O_WRONLY, 0644);

	if (fd < 0)
	{
		flog(LOG_ERR, "cannot create radvd pid file, terminating: %s", strerror(errno));
		exit(1);
	}

	snprintf(pidstr, sizeof(pidstr), "%ld\n", (long)getpid());

	ret = write(fd, pidstr, strlen(pidstr));
	if (ret != strlen(pidstr))
	{
		flog(LOG_ERR, "cannot write radvd pid file, terminating: %s", strerror(errno));
		exit(1);
	}

	close(fd);
}

void main_loop(void)
{
	struct pollfd fds[2];

	memset(fds, 0, sizeof(fds));

	fds[0].fd = sock;
	fds[0].events = POLLIN;
	fds[0].revents = 0;

#if HAVE_NETLINK
	fds[1].fd = netlink_socket();
	fds[1].events = POLLIN;
	fds[1].revents = 0;
#else
	fds[1].fd = -1;
	fds[1].events = 0;
	fds[1].revents = 0;
#endif

	system("/bin/echo 1 > /proc/sys/net/ipv6/conf/ppp1/accept_ra_pinfo");

	for (;;) {
		struct Interface *next = NULL;
		struct Interface *iface;
		int timeout = -1;
		int rc;

		if (IfaceList) {
			timeout = next_time_msec(IfaceList);
			next = IfaceList;
			for (iface = IfaceList; iface; iface = iface->next) {
				int t;
				t = next_time_msec(iface);
				if (timeout > t) {
					timeout = t;
					next = iface;
				}
			}
		}

		dlog(LOG_DEBUG, 5, "polling for %g seconds.", timeout/1000.0);

		rc = poll(fds, sizeof(fds)/sizeof(fds[0]), timeout);

		if (rc > 0) {
			if (fds[0].revents & (POLLERR | POLLHUP | POLLNVAL)) {
				flog(LOG_WARNING, "socket error on fds[0].fd");
			}
			else if (fds[0].revents & POLLIN) {
				int len, hoplimit;
				struct sockaddr_in6 rcv_addr;
				struct in6_pktinfo *pkt_info = NULL;
				unsigned char msg[MSG_SIZE_RECV];

				len = recv_rs_ra(msg, &rcv_addr, &pkt_info, &hoplimit);
				if (len > 0) {
					process(IfaceList, msg, len,
						&rcv_addr, pkt_info, hoplimit);
				}
			}
#ifdef HAVE_NETLINK
			if (fds[1].revents & (POLLERR | POLLHUP | POLLNVAL)) {
				flog(LOG_WARNING, "socket error on fds[1].fd");
			}
			else if (fds[1].revents & POLLIN) {
				process_netlink_msg(fds[1].fd);
			}
#endif
		}
		else if ( rc == 0 ) {
			if (next)
				timer_handler(next);
		}
		else if ( rc == -1 ) {
			dlog(LOG_INFO, 3, "poll returned early: %s", strerror(errno));
		}

		if (sigterm_received || sigint_received) {
			flog(LOG_WARNING, "Exiting, sigterm or sigint received.\n");
			break;
		}
	}
}

static int check_wan_ip6(char *wan_ifname)
{
	FILE *fp;
	char line[LINE_LENGTH];
	char wanip[INET6_ADDRSTRLEN] = {0};
	int ret = -1;

	fp = fopen("/proc/net/if_inet6", "r");
	if (fp == NULL)
		return ret;

	while (fgets(line, LINE_LENGTH, fp) != NULL) {
		if (strstr(line, wan_ifname)!=NULL && line[39]=='0' ) {
			flog(LOG_INFO, "WAN infetface get a GLOBAL IP\n");
			getIP6Info1(wan_ifname, wanip, IPV6_ADDR_GLOBAL);
			*(strchr(wanip, '/')) = '\0';
                        if (strcmp(wanip, sal_ipv6_get_wan_global_addr()) != 0){
                            sal_ipv6_set_wan_global_addr(wanip);
                            syslog(LOG_INFO, "%s"LOG_ERRCODE_P001, log_type_db[GENERAL_LOG], wanip);
                        }
			ret = 0;
			break;
		}
	}
	fclose(fp);

	return ret;
}

void
timer_handler(void *data)
{
	struct Interface *iface = (struct Interface *) data;
	double next = iface->RtrSolInterval / 1000.0;
	char tmp[8] = {0};

	if (next == 0) {
		next = 1;
	}

	dlog(LOG_DEBUG, 4, "timer_handler called for %s", iface->Name);
	if (iface->init_rscount > 1) {
		next = next * pow(2.0, (iface->init_rscount - 1));
	}

        if (other_config_flag != -1) {
            if (check_wan_ip6(iface->Name) == 0) {
                char *pidfile;

                sprintf(tmp, "%d", iface->RtrDefaultLifetime);
                sal_ipv6_set_ra_defaultlftime(tmp);

                if (other_config_flag == 1) {
                    char subnetID[4] = {0};
                    strcpy(subnetID, sal_lan_get_subnetid_t());
                    lan_ipv6_subnetid_generate(subnetID);
                    sal_lan_set_subnetid_t(subnetID);
                    system("/usr/sbin/rc_app dhcp6c restart > /dev/null 2>&1&");
                }

                pidfile = PATH_RADVD_PID;
                flog(LOG_INFO, "removing %s", pidfile);
                unlink(pidfile);
                exit(0);
            }
        }

	if (iface->init_rscount >= iface->RtrSolCount) {
		char *pidfile;
		int wan_id = 1;

		pidfile = PATH_RADVD_PID;
		flog(LOG_INFO, "removing %s", pidfile);
        	unlink(pidfile);
		if (recv_ra_prefix == 0) {
			syslog(LOG_INFO, "%s"LOG_ERRCODE_P006, log_type_db[GENERAL_LOG],
				"no RA prefix available");
		}
                else {
                    syslog(LOG_INFO, "%s"LOG_ERRCODE_P004, log_type_db[GENERAL_LOG]);
                } 
		syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0020, log_type_db[GENERAL_LOG], 
			"waiting for valid RA packets");
		sal_wan_set_con_error_log_code_t(wan_id, "R020");
		system("killall -SIGALRM pppd_1");
		exit(0);
	}
	if (send_rs(iface, NULL) != 0) {
		return;
	}

	iface->init_rscount++;
	iface->next_multicast = next_timespec(next);
}

void
kickoff_adverts(void)
{
	struct Interface *iface;

	/*
	 *	send initial advertisement and set timers
	 */

	for(iface=IfaceList; iface; iface=iface->next)
	{
		double next = iface->RtrSolInterval / 1000.0;

		if (next == 0) {
			next = 1;
		}
		clock_gettime(CLOCK_MONOTONIC, &iface->last_rs_time);

		if( iface->UnicastOnly )
			continue;

		clock_gettime(CLOCK_MONOTONIC, &iface->last_multicast);

		/* send an initial advertisement */
		if (send_rs(iface, NULL) == 0) {

			iface->init_rscount++;
			iface->next_multicast = next_timespec(next);
		}
	}
}

void reload_config(void)
{
	struct Interface *iface;

	flog(LOG_INFO, "attempting to reread config file");

	iface=IfaceList;
	while(iface)
	{
		struct Interface *next_iface = iface->next;
		struct AdvPrefix *prefix;
		struct AdvRoute *route;
		struct AdvRDNSS *rdnss;
		struct AdvDNSSL *dnssl;

		dlog(LOG_DEBUG, 4, "freeing interface %s", iface->Name);

		prefix = iface->AdvPrefixList;
		while (prefix)
		{
			struct AdvPrefix *next_prefix = prefix->next;

			free(prefix);
			prefix = next_prefix;
		}

		route = iface->AdvRouteList;
		while (route)
		{
			struct AdvRoute *next_route = route->next;

			free(route);
			route = next_route;
		}

		rdnss = iface->AdvRDNSSList;
		while (rdnss)
		{
			struct AdvRDNSS *next_rdnss = rdnss->next;

			free(rdnss);
			rdnss = next_rdnss;
		}

		dnssl = iface->AdvDNSSLList;
		while (dnssl)
		{
			struct AdvDNSSL *next_dnssl = dnssl->next;
			int i;

			for (i = 0; i < dnssl->AdvDNSSLNumber; i++)
				free(dnssl->AdvDNSSLSuffixes[i]);
			free(dnssl->AdvDNSSLSuffixes);
			free(dnssl);

			dnssl = next_dnssl;
		}

		free(iface);
		iface = next_iface;
	}

	IfaceList = NULL;

	/* reread config file */
	if (readin_config(conf_file) < 0) {
		perror("readin_config failed.");
		exit(1);
	}

	/* XXX: fails due to lack of permissions with non-root user */
	kickoff_adverts();

	flog(LOG_INFO, "resuming normal operation");
}

void
sighup_handler(int sig)
{
	/* Linux has "one-shot" signals, reinstall the signal handler */
	signal(SIGHUP, sighup_handler);

	sighup_received = 1;
}

void
sigterm_handler(int sig)
{
	/* Linux has "one-shot" signals, reinstall the signal handler */
	signal(SIGTERM, sigterm_handler);

	++sigterm_received;

	if(sigterm_received > 1){
		abort();
	}
}

void
sigint_handler(int sig)
{
	/* Linux has "one-shot" signals, reinstall the signal handler */
	signal(SIGINT, sigint_handler);

	++sigint_received;

	if(sigint_received > 1){
		abort();
	}
}


void reset_prefix_lifetimes(void)
{
	struct Interface *iface;
	struct AdvPrefix *prefix;
	char pfx_str[INET6_ADDRSTRLEN];


	flog(LOG_INFO, "Resetting prefix lifetimes");
	
	for (iface = IfaceList; iface; iface = iface->next) 
	{
		for (prefix = iface->AdvPrefixList; prefix;
							prefix = prefix->next) 
		{
			if (prefix->DecrementLifetimesFlag)
			{
				print_addr(&prefix->Prefix, pfx_str);
				dlog(LOG_DEBUG, 4, "%s/%u%%%s plft reset from %u to %u secs", pfx_str, prefix->PrefixLen, iface->Name, prefix->curr_preferredlft, prefix->AdvPreferredLifetime);
				dlog(LOG_DEBUG, 4, "%s/%u%%%s vlft reset from %u to %u secs", pfx_str, prefix->PrefixLen, iface->Name, prefix->curr_validlft, prefix->AdvValidLifetime);
				prefix->curr_validlft =
						prefix->AdvValidLifetime;
				prefix->curr_preferredlft =
						prefix->AdvPreferredLifetime;
			}
		}
		
	}

}

void sigusr1_handler(int sig)
{

	/* Linux has "one-shot" signals, reinstall the signal handler */
	signal(SIGUSR1, sigusr1_handler);

	sigusr1_received = 1;
}

int
drop_root_privileges(const char *username)
{
	struct passwd *pw = NULL;
	pw = getpwnam(username);
	if (pw) {
		if (initgroups(username, pw->pw_gid) != 0 || setgid(pw->pw_gid) != 0 || setuid(pw->pw_uid) != 0) {
			flog(LOG_ERR, "Couldn't change to '%.32s' uid=%d gid=%d",
					username, pw->pw_uid, pw->pw_gid);
			return (-1);
		}
	}
	else {
		flog(LOG_ERR, "Couldn't find user '%.32s'", username);
		return (-1);
	}
	return 0;
}

int
check_conffile_perm(const char *username, const char *conf_file)
{
	struct stat stbuf;
	struct passwd *pw = NULL;
	FILE *fp = fopen(conf_file, "r");

	if (fp == NULL) {
		flog(LOG_ERR, "can't open %s: %s", conf_file, strerror(errno));
		return (-1);
	}
	fclose(fp);

	if (!username)
		username = "ADMIN";

	pw = getpwnam(username);

	if (stat(conf_file, &stbuf) || pw == NULL)
		return (-1);

	if (stbuf.st_mode & S_IWOTH) {
                flog(LOG_ERR, "Insecure file permissions (writable by others): %s", conf_file);
		return (-1);
        }

	/* for non-root: must not be writable by self/own group */
	if (strncmp(username, "ADMIN", 5) != 0 &&
	    ((stbuf.st_mode & S_IWGRP && pw->pw_gid == stbuf.st_gid) ||
	     (stbuf.st_mode & S_IWUSR && pw->pw_uid == stbuf.st_uid))) {
                flog(LOG_ERR, "Insecure file permissions (writable by self/group): %s", conf_file);
		return (-1);
        }

        return 0;
}

int
check_ip6_forwarding(void)
{
	int forw_sysctl[] = { SYSCTL_IP6_FORWARDING };
	int value;
	size_t size = sizeof(value);
	FILE *fp = NULL;
	static int warned = 0;

#ifdef __linux__
	fp = fopen(PROC_SYS_IP6_FORWARDING, "r");
	if (fp) {
		int rc = fscanf(fp, "%d", &value);
		if(rc != 1){
			flog(LOG_ERR, "cannot read value from %s: %s", PROC_SYS_IP6_FORWARDING, strerror(errno));
			exit(1);
		}
		fclose(fp);
	}
	else
		flog(LOG_DEBUG, "Correct IPv6 forwarding procfs entry not found, "
	                       "perhaps the procfs is disabled, "
	                        "or the kernel interface has changed?");
#endif /* __linux__ */

	if (!fp && sysctl(forw_sysctl, sizeof(forw_sysctl)/sizeof(forw_sysctl[0]),
	    &value, &size, NULL, 0) < 0) {
		flog(LOG_DEBUG, "Correct IPv6 forwarding sysctl branch not found, "
			"perhaps the kernel interface has changed?");
		return(0);	/* this is of advisory value only */
	}

	if (value == 0 && !warned) {
		warned = 1;
		flog(LOG_DEBUG, "IPv6 forwarding setting is: %u, should be 1", value);
		return(-1);
	}

	return(0);
}

int
readin_config(char *fname)
{
	if ((yyin = fopen(fname, "r")) == NULL)
	{
		flog(LOG_ERR, "can't open %s: %s", fname, strerror(errno));
		return (-1);
	}

	if (yyparse() != 0)
	{
		flog(LOG_ERR, "error parsing or activating the config file: %s", fname);
		return (-1);
	}

	fclose(yyin);
	return 0;
}

void
version(void)
{
	fprintf(stderr, "Version: %s\n\n", VERSION);
	fprintf(stderr, "Compiled in settings:\n");
	fprintf(stderr, "  default config file		\"%s\"\n", PATH_RADVD_CONF);
	fprintf(stderr, "  default pidfile		\"%s\"\n", PATH_RADVD_PID);
	fprintf(stderr, "  default logfile		\"%s\"\n", PATH_RADVD_LOG);
	fprintf(stderr, "  default syslog facility	%d\n", LOG_FACILITY);
	fprintf(stderr, "Please send bug reports or suggestions to %s.\n",
		CONTACT_EMAIL);

	exit(1);
}

void
usage(void)
{
	fprintf(stderr, "usage: %s %s\n", pname, usage_str);
	exit(1);
}

