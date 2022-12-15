/* dhcpd.c
 *
 * udhcp DHCP client
 *
 * Russ Dill <Russ.Dill@asu.edu> July 2001
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <errno.h>

#include "dhcpd.h"
#include "dhcpc.h"
#include "options.h"
#include "clientpacket.h"
#include "packet.h"
#include "script.h"
#include "socket.h"
#include "debug.h"
#include "pidfile.h"
#ifdef __SC_BUILD__
#include "log_api.h"
#include <sal/sal_wan.h>
#endif
static int state;
static unsigned long requested_ip; /* = 0 */
static unsigned long lease_time;
static unsigned long server_addr;
static unsigned long timeout;
static int packet_num; /* = 0 */
static int fd;
static int signal_pipe[2];
#ifdef __SC_BUILD__

int scIpChanged = 0;
int scRouteChanged = 0;
int scDnsChanged = 0;
#endif
#define LISTEN_NONE 0
#define LISTEN_KERNEL 1
#define LISTEN_RAW 2
static int listen_mode;
extern int route_count;/*  How many routes we have got in option 33 and 121 */

#define DEFAULT_SCRIPT	"/usr/share/udhcpc/default.script"

struct client_config_t client_config = {
	/* Default options. */
	abort_if_no_lease: 0,
#ifdef __SC_BUILD__
	foreground: 1,
#else
	foreground: 0,
#endif
	quit_after_lease: 0,
	background_if_no_lease: 0,
	interface: "eth0",
	pidfile: NULL,
	script: DEFAULT_SCRIPT,
	clientid: NULL,
#ifdef __SC_BUILD__
	vendorid: NULL,
#endif
	hostname: NULL,
#ifdef __SC_BUILD__
	server:NULL,
#endif
	ifindex: 0,
	arp: "\0\0\0\0\0\0",		/* appease gcc-3.0 */
#ifdef __SC_BUILD__
	user: NULL,
        option2_source_ntp : 0,
        option42_source_ntp : 0,
	wanid:1,
#endif
};

#ifndef BB_VER
static void show_usage(void)
{
	printf(
"Usage: udhcpc [OPTIONS]\n\n"
#ifdef __SC_BUILD__
"  -a, --autooption=id             auto add option basing on ntp/others \n"
#endif

"  -c, --clientid=CLIENTID         Client identifier\n"
"  -H, --hostname=HOSTNAME         Client hostname\n"
"  -h                              Alias for -H\n"
"  -f, --foreground                Do not fork after getting lease\n"
"  -b, --background                Fork to background if lease cannot be\n"
"                                  immediately negotiated.\n"
"  -i, --interface=INTERFACE       Interface to use (default: eth0)\n"

"  -n, --now                       Exit with failure if lease cannot be\n"
#ifdef __SC_BUILD__
"  -N, --nooption=id               Do not request option id \n"
#endif
"                                  immediately negotiated.\n"
"  -p, --pidfile=file              Store process ID of daemon in file\n"
"  -q, --quit                      Quit after obtaining lease\n"
"  -r, --request=IP                IP address to request (default: none)\n"
#ifdef __SC_BUILD__
"  -R, --nooption=id               Request option id \n"
#endif
"  -s, --script=file               Run file at dhcp events (default:\n"
#ifdef __SC_BUILD__
"  -S, --server=IP                 IP address of l2tp server(default: none)\n"

"  -u, --userclass=userclass       user class \n"
#endif
"                                  " DEFAULT_SCRIPT ")\n"
"  -v, --version                   Display version\n"
#ifdef __SC_BUILD__

"  -V, --vendorid=VendorID         The Vendor ID used for DHCP option 60\n"
"  -w, --wanid=WANID               The wanid of the WAN to use (default: 1)\n"
#endif
	);
	exit(0);
}
#endif


/* just a little helper */
static void change_mode(int new_mode)
{
	DEBUG(LOG_INFO, "entering %s listen mode",
		new_mode ? (new_mode == 1 ? "kernel" : "raw") : "none");
	close(fd);
	fd = -1;
	listen_mode = new_mode;
}


/* perform a renew */
static void perform_renew(void)
{
	LOG(LOG_INFO, "Performing a DHCP renew");
	switch (state) {
	case BOUND:
		change_mode(LISTEN_KERNEL);
	case RENEWING:
	case REBINDING:
		state = RENEW_REQUESTED;
		break;
	case RENEW_REQUESTED: /* impatient are we? fine, square 1 */
		run_script(NULL, "deconfig");
	case REQUESTING:
	case RELEASED:
		change_mode(LISTEN_RAW);
		state = INIT_SELECTING;
		break;
	case INIT_SELECTING:
		break;
		default:
			break;
	}

	/* start things over */
	packet_num = 0;

	/* Kill any timeouts because the user wants this to hurry along */
	timeout = 0;
}


/* perform a release */
static void perform_release(void)
{
	char buffer[16];
	struct in_addr temp_addr;

	/* send release packet */
	if (state == BOUND || state == RENEWING || state == REBINDING) {
		temp_addr.s_addr = server_addr;
		sprintf(buffer, "%s", inet_ntoa(temp_addr));
		temp_addr.s_addr = requested_ip;
		LOG(LOG_INFO, "Unicasting a release of %s to %s", 
				inet_ntoa(temp_addr), buffer);
		send_release(server_addr, requested_ip); /* unicast */
		run_script(NULL, "deconfig");

	}
	LOG(LOG_INFO, "Entering released state");

	change_mode(LISTEN_NONE);
	state = RELEASED;
	timeout = 0x7fffffff;


}


/* Exit and cleanup */
static void exit_client(int retval)
{
#ifdef __SC_BUILD__
	sal_wan_set_con_client_pid_t(client_config.wanid, "0");
#endif
	pidfile_delete(client_config.pidfile);
	CLOSE_LOG();

	exit(retval);
}


/* Signal handler */
static void signal_handler(int sig)
{
	if (send(signal_pipe[1], &sig, sizeof(sig), MSG_DONTWAIT) < 0) {
		LOG(LOG_ERR, "Could not send signal: %s",
			strerror(errno));
	}
}


static void background(void)
{
	int pid_fd;

	pid_fd = pidfile_acquire(client_config.pidfile); /* hold lock during fork. */
	while (pid_fd >= 0 && pid_fd < 3) pid_fd = dup(pid_fd); /* don't let daemon close it */
	if (daemon(0, 0) == -1) {
		perror("fork");
		exit_client(1);
	}
	client_config.foreground = 1; /* Do not fork again. */
	pidfile_write_release(pid_fd);
#ifdef __SC_BUILD__
    char pid_buf[16];
    snprintf(pid_buf, sizeof(pid_buf), "%d", getpid());
    sal_wan_set_con_client_pid_t(client_config.wanid, pid_buf);
#endif

}

#ifdef COMBINED_BINARY
int udhcpc_main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	unsigned char *temp, *message;
	unsigned long t1 = 0, t2 = 0, xid = 0;
	unsigned long start = 0, lease;
	fd_set rfds;
	int retval;
	struct timeval tv;
	int c, len;
	struct dhcpMessage packet;
	struct in_addr temp_addr;
#ifdef __SC_BUILD__
	struct in_addr serv_addr;
        unsigned int interval = 0;
#endif
	int pid_fd;
	time_t now;
	int max_fd;
	int sig;
#ifdef __SC_BUILD__	
    int do_detect = 0; //detect dhcp server
    int count_detect = 0;
    int i;
    int option_code = 0;
#endif
	static struct option arg_options[] = {
#ifdef __SC_BUILD__
		{"autooption",	required_argument,	0, 'a'},
#endif
	        {"clientid",	required_argument,	0, 'c'},
#ifdef __SC_BUILD__
		{"detect",	no_argument,		0, 'd'},
#endif
		{"foreground",	no_argument,		0, 'f'},
		{"background",	no_argument,		0, 'b'},
		{"hostname",	required_argument,	0, 'H'},
		{"hostname",    required_argument,  0, 'h'},
		{"interface",	required_argument,	0, 'i'},
		
		{"now", 	no_argument,		0, 'n'},
#ifdef __SC_BUILD__
		{"nooption",	required_argument,	0, 'N'},
#endif
		{"pidfile",	required_argument,	0, 'p'},
		{"quit",	no_argument,		0, 'q'},
		{"request",	required_argument,	0, 'r'},
#ifdef __SC_BUILD__
		{"reqoption",	required_argument,	0, 'R'},
#endif
		{"script",	required_argument,	0, 's'},
#ifdef __SC_BUILD__
		{"server",	required_argument, 	0, 'S'},
#endif
		{"version",	no_argument,		0, 'v'},
#ifdef __SC_BUILD__
		{"vendorid",required_argument,	0, 'V'},
		{"wanid",	required_argument,	0, 'w'},
#endif
		{"help",	no_argument,		0, '?'},
#ifdef __SC_BUILD__
		{"userclass",	required_argument,	0, 'u'},
#endif
		{0, 0, 0, 0}
	};
        lease_time = 60*60;
	/* get options */
	while (1) {

		int option_index = 0;
#ifdef __SC_BUILD__
		c = getopt_long(argc, argv, "a:c:dfbH:h:i:nN:p:qrl:R:s:S:u:vV:w:", arg_options, &option_index);
#else
		c = getopt_long(argc, argv, "c:fbH:h:i:np:qrl:s:v", arg_options, &option_index);
#endif
		if (c == -1) break;

		switch (c) {
#ifdef __SC_BUILD__
                case 'a':
			option_code = strtol(optarg, (char **)NULL, 16);
                        if(option_code == DHCP_TIME_OFFSET)
                            client_config.option2_source_ntp = 1;
                        else if(option_code == DHCP_NTP_SERVER)
                            client_config.option42_source_ntp = 1;
		        break;
#endif
		case 'c':
			len = strlen(optarg) > 255 ? 255 : strlen(optarg);
			if (client_config.clientid) free(client_config.clientid);
#ifdef __SC_BUILD__
			client_config.clientid = malloc(len + 3);
#else
			client_config.clientid = malloc(len + 2);
#endif
			client_config.clientid[OPT_CODE] = DHCP_CLIENT_ID;
#ifdef __SC_BUILD__
			client_config.clientid[OPT_LEN] = len + 1;
#else
			client_config.clientid[OPT_LEN] = len;
#endif
			client_config.clientid[OPT_DATA] = 0x1;//0 for non ethernet
#ifdef __SC_BUILD__
			strncpy(client_config.clientid + 3, optarg, len);
#else
			strncpy(client_config.clientid + OPT_DATA, optarg, len);
#endif
			break;
#ifdef __SC_BUILD__
		case 'd':
		    do_detect = 1;
		    break;
#endif
		case 'f':
			client_config.foreground = 1;
			break;
		case 'b':
			client_config.background_if_no_lease = 1;
			break;
		case 'h':
		case 'H':
			len = strlen(optarg) > 255 ? 255 : strlen(optarg);

			if (client_config.hostname) free(client_config.hostname);
			client_config.hostname = malloc(len + 2);
			client_config.hostname[OPT_CODE] = DHCP_HOST_NAME;
			client_config.hostname[OPT_LEN] = len;
			strncpy(client_config.hostname + 2, optarg, len);
			break;
#ifdef __SC_BUILD__
		case 'S':
		    len = strlen(optarg) > 255 ? 255 : strlen(optarg);
			if (client_config.server)
			    free(client_config.server);
			client_config.server = malloc(len + 1);
			client_config.server[len] = '\0';
			strncpy(client_config.server, optarg, len);
			break;
#endif
		case 'i':
			client_config.interface =  optarg;
			break;
		case 'n':
			client_config.abort_if_no_lease = 1;
			break;
#ifdef __SC_BUILD__
		case 'N':
			option_code = strtol(optarg, (char **)NULL, 16);
			for (i = 0; options[i].code; i++)
				if(option_code == options[i].code)
				{
					options[i].flags &= ~OPTION_REQ;
					break;
				}
			break;
#endif
#ifdef __SC_BUILD__
		case 'V':
			len = strlen(optarg) > 255 ? 255 : strlen(optarg);
			if (client_config.vendorid) free(client_config.vendorid);
			client_config.vendorid = malloc(len + 3);
			client_config.vendorid[OPT_CODE] = DHCP_VENDOR;
			client_config.vendorid[OPT_LEN] = len;
			strncpy(client_config.vendorid + OPT_DATA, optarg, len);
			break;
#endif
		case 'p':
			client_config.pidfile = optarg;
			break;
		case 'q':
			client_config.quit_after_lease = 1;
			break;
		case 'r':
			requested_ip = inet_addr(optarg);
			break;
                case 'l':
                        lease_time = strtol(optarg, (char **)NULL, 10);
#ifdef __SC_BUILD__
		case 'R':
			option_code = strtol(optarg, (char **)NULL, 16);
			for (i = 0; options[i].code; i++)
				if(option_code == options[i].code)
				{
					options[i].flags |= OPTION_REQ;
					break;
				}

			break;
#endif
		case 's':
			client_config.script = optarg;
			break;
#ifdef __SC_BUILD__
		case 'u':
			len = strlen(optarg) > 255 ? 255 : strlen(optarg);
			if (client_config.user) free(client_config.user);
			client_config.user = malloc(len + 4);
			client_config.user[OPT_CODE] = DHCP_USER_CLASS_ID;
			client_config.user[OPT_LEN] = len + 1;
			client_config.user[OPT_DATA] = len;
			strncpy(client_config.user + 3, optarg, len);
			break;
#endif
		case 'v':
			printf("udhcpcd, version %s\n\n", VERSION);
			exit_client(0);
			break;
#ifdef __SC_BUILD__
		case 'w':
			client_config.wanid =  atoi(optarg);
			break;
#endif
		default:
			show_usage();
		}
	}

	OPEN_LOG("udhcpc");
	LOG(LOG_INFO, "udhcp client (v%s) started", VERSION);

	pid_fd = pidfile_acquire(client_config.pidfile);
	pidfile_write_release(pid_fd);
#ifdef __SC_BUILD__
	char pid_buf[16];
	snprintf(pid_buf, sizeof(pid_buf), "%d", getpid());
	sal_wan_set_con_client_pid_t(client_config.wanid, pid_buf);
#endif
	if (read_interface(client_config.interface, &client_config.ifindex, 
			   NULL, client_config.arp) < 0)
		exit_client(1);
		
	if (!client_config.clientid) {
		client_config.clientid = malloc(6 + 3);
		client_config.clientid[OPT_CODE] = DHCP_CLIENT_ID;
		client_config.clientid[OPT_LEN] = 7;
		client_config.clientid[OPT_DATA] = 1;
		memcpy(client_config.clientid + 3, client_config.arp, 6);
	}

	/* setup signal handlers */
	socketpair(AF_UNIX, SOCK_STREAM, 0, signal_pipe);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGTERM, signal_handler);

	state = INIT_SELECTING;
	run_script(NULL, "deconfig");
	change_mode(LISTEN_RAW);

	for (;;) {
#ifdef __SC_BUILD__
		if(timeout>0)
			tv.tv_sec = timeout;
		else
			tv.tv_sec = 0;
#else
		tv.tv_sec = timeout - time(0);
#endif
		tv.tv_usec = 0;
		FD_ZERO(&rfds);

		if (listen_mode != LISTEN_NONE && fd < 0) {
			if (listen_mode == LISTEN_KERNEL)
        #if defined(__SC_BUILD__)
                fd = listen_socket(INADDR_ANY, CLIENT_PORT, client_config.interface, 0);
        #else
				fd = listen_socket(INADDR_ANY, CLIENT_PORT, client_config.interface);
        #endif
			else
				fd = raw_socket(client_config.ifindex);
			if (fd < 0) {
				LOG(LOG_ERR, "FATAL: couldn't listen on socket, %s", strerror(errno));
				exit_client(0);
			}
		}
		if (fd >= 0) FD_SET(fd, &rfds);
		FD_SET(signal_pipe[0], &rfds);		

		if (tv.tv_sec > 0) {
			DEBUG(LOG_INFO, "Waiting on select...\n");
			max_fd = signal_pipe[0] > fd ? signal_pipe[0] : fd;
			retval = select(max_fd + 1, &rfds, NULL, NULL, &tv);
		} else retval = 0; /* If we already timed out, fall through */
	

		now = time(0);
		if (retval == 0) {
			/* timeout dropped to zero */
			switch (state) {
			case INIT_SELECTING:
#ifdef __SC_BUILD__
			    if(do_detect)
			    {
			        if(count_detect++ == 1)
			        {
				        exit_client(0);
			        }
			    }
#endif
				if (packet_num < 10) {
					if (packet_num == 0)
						xid = random_xid();

					/* send discover packet */
					send_discover(xid, requested_ip, lease_time); /* broadcast */
#ifdef __SC_BUILD__
//					syslog(LOG_INFO, "%s DHCP of WAN %d, discover is sent.", log_type_db[WAN_LOG], client_config.wanid);
				    timeout = ((packet_num == 0) ? 3 : (1 << (packet_num - 1)));
#else
					timeout = now + ((packet_num == 2) ? 4 : 2);
#endif

					packet_num++;
				} else {
					if (client_config.background_if_no_lease) {
						LOG(LOG_INFO, "No lease, forking to background.");
						background();
					} else if (client_config.abort_if_no_lease) {
						LOG(LOG_INFO, "No lease, failing.");
						exit_client(1);
				  	}
#ifdef __SC_BUILD__

					/* send discover packet */
					send_discover(xid, requested_ip, lease_time); /* broadcast */
					timeout = 600; // changed the time from 35 to 600 seconds
                    LOG(LOG_ERR, "No lease time with ACK, using 1 hour lease");
#else
					timeout = now + 60;
#endif
				}
				break;
			case RENEW_REQUESTED:
			case REQUESTING:
#ifdef __SC_BUILD__
				if (packet_num < 5) {
#else
				if (packet_num < 3) {
#endif
					/* send request packet */
					if (state == RENEW_REQUESTED)
						send_renew(xid, server_addr, requested_ip); /* unicast */
					else send_selecting(xid, server_addr, requested_ip); /* broadcast */
#ifdef __SC_BUILD__
//					syslog(LOG_INFO, "%s DHCP of WAN %d, request is sent.", log_type_db[WAN_LOG], client_config.wanid);
					timeout = 4 << packet_num;
#else
					timeout = now + ((packet_num == 2) ? 10 : 2);
#endif
					packet_num++;
				} else {

					/* timed out, go back to init state */
					if (state == RENEW_REQUESTED)
					{
					    run_script(NULL, "deconfig");
					}
					state = INIT_SELECTING;
#ifdef __SC_BUILD__
					timeout = 0;
#else
					timeout = now;
#endif
					packet_num = 0;
					change_mode(LISTEN_RAW);
				}
				break;
			case BOUND:
				/* Lease is starting to run out, time to enter renewing state */
				state = RENEWING;
				change_mode(LISTEN_KERNEL);
				DEBUG(LOG_INFO, "Entering renew state");
				/* fall right through */
			case RENEWING:
				/* Either set a new T1, or enter REBINDING state */
#ifdef __SC_BUILD__
                                interval = (t2 - t1)/2;

                                if(interval<60)
                                    interval = 60;
#endif
                                if ((t2 - t1) <= (lease / 14400 + 1)) {
					/* timed out, enter rebinding state */
					state = REBINDING;
#ifdef __SC_BUILD__
					timeout = (t2 - t1);
#else
					timeout = now + (t2 - t1);
#endif
					DEBUG(LOG_INFO, "Entering rebinding state");
				} else {
					/* send a request packet */
					send_renew(xid, server_addr, requested_ip); /* unicast */

#ifdef __SC_BUILD__
                                        if(t2 <= (t1 + interval))
                                        {
                                            state = REBINDING;
                                            timeout = t2 - t1;
                                            DEBUG(LOG_INFO, "Entering rebinding state");
                                        }
                                        else
                                        {
                                            t1 = interval + t1;
                                            timeout = interval;
                                        }
#else
					t1 = (t2 - t1) / 2 + t1;
					timeout = t1 + start;
#endif
				}
				break;
			case REBINDING:
				/* Either set a new T2, or enter INIT state */
#ifdef __SC_BUILD__
                                interval = (lease - t2)/2;

                                if(interval<60)
                                    interval = 60;
#endif
                                if ((lease - t2) <= (lease / 14400 + 1)) {
					/* timed out, enter init state */
					state = INIT_SELECTING;
					LOG(LOG_INFO, "Lease lost, entering init state");

					run_script(NULL, "deconfig");
#ifdef __SC_BUILD__
					timeout = 0;
#else
					timeout = now;
#endif
					packet_num = 0;
					change_mode(LISTEN_RAW);
				} else {
					/* send a request packet */
					send_renew(xid, 0, requested_ip); /* broadcast */
#ifdef __SC_BUILD__
                                        if(lease <= (t2 + interval))
                                        {
                                            state = INIT_SELECTING;
					    LOG(LOG_INFO, "Lease lost, entering init state");

					    run_script(NULL, "deconfig");
                                            timeout = lease-t2;
					    packet_num = 0;
					    change_mode(LISTEN_RAW);
                                        }
                                        else
                                        {
                                            t2 = interval + t2;
                                            timeout = interval;
                                        }
#else
					t2 = (lease - t2) / 2 + t2;
					timeout = t2 + start;
#endif

				}
				break;
			case RELEASED:
				/* yah, I know, *you* say it would never happen */
				timeout = 0x7fffffff;
				break;
			}
		} else if (retval > 0 && listen_mode != LISTEN_NONE && FD_ISSET(fd, &rfds)) {
			/* a packet is ready, read it */

			if (listen_mode == LISTEN_KERNEL)
        #ifdef __SC_BUILD__
                len = get_packet(&packet, fd, NULL);
        #else
				len = get_packet(&packet, fd);
        #endif
			else len = get_raw_packet(&packet, fd);

			if (len == -1 && errno != EINTR) {
				DEBUG(LOG_INFO, "error on read, %s, reopening socket", strerror(errno));
				change_mode(listen_mode); /* just close and reopen */
			}
#ifdef __SC_BUILD__
			timeout = tv.tv_sec;
#endif
			if (len < 0) continue;

			if (packet.xid != xid) {
				DEBUG(LOG_INFO, "Ignoring XID %lx (our xid is %lx)",
					(unsigned long) packet.xid, xid);
				continue;
			}

			if ((message = get_option(&packet, DHCP_MESSAGE_TYPE)) == NULL) {
				DEBUG(LOG_ERR, "couldnt get option from packet -- ignoring");
				continue;
			}

			switch (state) {
			case INIT_SELECTING:
				/* Must be a DHCPOFFER to one of our xid's */
				if (*message == DHCPOFFER) {
					if ((temp = get_option(&packet, DHCP_SERVER_ID))) {
					    memcpy(&server_addr, temp, 4);
#ifdef __SC_BUILD__
					    int len;
					    int i;
					    int lenx = 0;
					    char ntp_servers[256] = {0};
                                            int offset;
					    struct in_addr temp_addr;
					    temp_addr.s_addr = server_addr;
					    sal_wan_set_con_dhcp_server_t(client_config.wanid, inet_ntoa(temp_addr));
                                            if(is_option_required(DHCP_NTP_SERVER))
					    {
					        if((temp = get_option_x(&packet, DHCP_NTP_SERVER, &len)))
					        { 
					            for(i = 0; i < (len / 4); i++)
					            { 
					                 memcpy(&temp_addr.s_addr, (temp + i * 4), 4);
						         if(i)
						  	     lenx +=  snprintf(ntp_servers + lenx, sizeof(ntp_servers), ",%s", inet_ntoa(temp_addr));
						         else
							     lenx += snprintf(ntp_servers, sizeof(ntp_servers), "%s", inet_ntoa(temp_addr));
					            }
					            sal_wan_set_con_opt42_t(client_config.wanid, ntp_servers);
				 	        }
					    }
					    if(is_option_required(DHCP_TIME_OFFSET))
					    {
					        if((temp = get_option_x(&packet, DHCP_TIME_OFFSET, &len)))
					        { 
					            { 
					                 memcpy(&offset, temp, 4);
					                 snprintf(ntp_servers, sizeof(ntp_servers), "%d", ntohl(offset));
					            }
					            sal_wan_set_con_opt2_t(client_config.wanid, ntp_servers);
				 	        }
					    }	 
				        if(do_detect)
				        {
				            printf("server_ok");
				            exit_client(0);
				        }
#endif
				
			
						xid = packet.xid;
						requested_ip = packet.yiaddr;

						/* enter requesting state */
						state = REQUESTING;
#ifdef __SC_BUILD__
						timeout = 0;
#else
						timeout = now;
#endif
						packet_num = 0;
#ifdef __SC_BUILD__
//						syslog(LOG_INFO, "%s DHCP of WAN %d, offer is received.", log_type_db[WAN_LOG], client_config.wanid);
#endif
					} else {
						DEBUG(LOG_ERR, "No server ID in message");
					}
				}
				break;
			case RENEW_REQUESTED:
			case REQUESTING:
			case RENEWING:
			case REBINDING:
				if (*message == DHCPACK) {

					if (!(temp = get_option(&packet, DHCP_LEASE_TIME))) {
						LOG(LOG_ERR, "No lease time with ACK, using 1 hour lease");
						lease = 60 * 60;
					} else {
						memcpy(&lease, temp, 4);
						lease = ntohl(lease);
					}

#ifdef __SC_BUILD__
                    /*DHCP WAN, after HG receive DHCP offer from DHCP server, if the subnet of assigned IP overlapping HG's own LAN subnet, HG will send DHCP decline message to DHCP server and goto INIT_SELECTING state.*/
                    struct in_addr dest;
                    struct in_addr netmask;
                    if_info_t if_info;
                    getIFInfo("br0", &if_info);
                    inet_pton(AF_INET, if_info.ipaddr, &dest);
                    inet_pton(AF_INET, if_info.mask, &netmask);
                    if((packet.yiaddr & netmask.s_addr) == (dest.s_addr & netmask.s_addr))
                    {

                        send_decline(xid, server_addr, packet.yiaddr);
                        if (state != REQUESTING)
                        {
                            run_script(NULL, "deconfig");
                        }
                        state = INIT_SELECTING;
                        timeout = 0;
                        requested_ip = 0;
                        packet_num = 0;
                        change_mode(LISTEN_RAW);
                        sleep(3);
                        break;
                    }   
#endif 

					/* enter bound state */
					t1 = lease / 2;

					/* little fixed point for n * .875 */
					t2 = (lease * 0x7) >> 3;
					temp_addr.s_addr = packet.yiaddr;
					LOG(LOG_INFO, "Lease of %s obtained, lease time %ld",
						inet_ntoa(temp_addr), lease);
#ifdef __SC_BUILD__
//					syslog(LOG_INFO, "%s DHCP of WAN %d, ack is received.", log_type_db[WAN_LOG], client_config.wanid);
#endif
					start = now;
#ifdef __SC_BUILD__
					timeout = t1;
#else
					timeout = t1 + start;
#endif
					requested_ip = packet.yiaddr;

					run_script(&packet,
						   ((state == RENEWING || state == REBINDING) ? "renew" : "bound"));

					state = BOUND;
					change_mode(LISTEN_NONE);
                    route_count = 0;  /*  We should initialized route_count before     checking options. */
#ifdef __SC_BUILD__
                    sc_option121(&packet);
                    sc_send_client_options(&packet);
                    sc_record_all_option(&packet);
#endif
					if (client_config.quit_after_lease) 
						exit_client(0);

					if (!client_config.foreground)
						background();
					break;

				} else if (*message == DHCPNAK) {
					/* return to init state */
					LOG(LOG_INFO, "Received DHCP NAK");
					run_script(&packet, "nak");
					if (state != REQUESTING)
					{

						run_script(NULL, "deconfig");
					}
					state = INIT_SELECTING;
#ifdef __SC_BUILD__
					timeout = 0;
#else
					timeout = now;
#endif
					requested_ip = 0;
					packet_num = 0;
					change_mode(LISTEN_RAW);
					sleep(3); /* avoid excessive network traffic */
					}
					break;
				}
			}else if (retval > 0 && FD_ISSET(signal_pipe[0], &rfds))
			{
#ifdef __SC_BUILD__
				if (read(signal_pipe[0], &sig, sizeof(sig)) < 0) {
#else
				if (read(signal_pipe[0], &sig, sizeof(signal)) < 0) {
#endif
					DEBUG(LOG_ERR, "Could not read signal: %s",
						strerror(errno));
					continue; /* probably just EINTR */
				}
				switch (sig) {
				case SIGUSR1:
					perform_renew();
					break;
				case SIGUSR2:
					perform_release();
					break;
				case SIGTERM:
					LOG(LOG_INFO, "Received SIGTERM");
                    sleep(1); // when reboot, for apps teardown before release ip
                    perform_release(); // when reboot, release ip
					exit_client(0);
				}
		
		} else if (retval == -1 && errno == EINTR) {
			/* a signal was caught */
#ifdef __SC_BUILD__
				timeout = tv.tv_sec;
#endif

		} else {
			/* An error occured */
			DEBUG(LOG_ERR, "Error on select");
		}

	}
	return 0;
}

