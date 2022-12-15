/* dhcpd.c
 *
 * udhcp Server
 * Copyright (C) 1999 Matthew Ramsay <matthewr@moreton.com.au>
 *			Chris Trew <ctrew@moreton.com.au>
 *
 * Rewrite by Russ Dill <Russ.Dill@asu.edu> July 2001
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

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <time.h>
#include <sys/time.h>

#include "debug.h"
#include "dhcpd.h"
#include "arpping.h"
#include "socket.h"
#include "options.h"
#include "files.h"
#include "leases.h"
#include "packet.h"
#include "serverpacket.h"
#include "pidfile.h"
#include "static_leases.h"
#include "option_action.h"
#if defined(__SC_BUILD__) && defined(__SC_LEASE_RETAIN__)
#include "lease_retain.h"
#endif

/* globals */
struct dhcpOfferedAddr *leases[MAX_INTERFACES];
struct server_config_t server_config[MAX_INTERFACES];
int default_enable = TRUE;

struct client_option_s *vendor_header = NULL;
struct client_option_s *client_header = NULL;
struct client_option_s *user_class_header = NULL;

#define WRITE_LEASE_FILE_INTERVAL 10
int past_seconds = 0;
int no_of_ifaces = 0;

static char conf_file[256] = "";
static int signal_flag = 0;
static int signal_sig = -1;

/* Exit and cleanup */
static void exit_server(int retval, int ifid)
{
#ifdef __SC_BUILD__
    syslog(LOG_INFO, "%s"LOG_ERRCODE_H002, log_type_db[GENERAL_LOG]);
#endif
    SC_DEBUG(DEBUG_DHCPD, "exit server, retval:%d, ifid:%d\n", retval, ifid);
    //pidfile_delete(server_config[ifid].pidfile);
    unlink("/var/run/udhcpd.pid");
    CLOSE_LOG();
    exit(retval);
}

static void update_lease_files(void)
{
    int i;
    for (i = 0; i < no_of_ifaces; i++)
        write_leases(i);
}

/* -- Jeff Sun -- Apr.23.2005 -- add here for make ipaddr expire */ 
static void expire_action(u_int32_t ipaddr)
{
    int i; 
    unsigned int j;
    for(i=0;i<no_of_ifaces;i++)
    {
        if(server_config[i].active == FALSE)
            continue;

        for(j=0;j<server_config[i].max_leases;j++)
            if(leases[i][j].yiaddr == ipaddr)
                leases[i][j].expires = time(0);
    }  
}
/* SIGUSR1 handler */
static void do_expire(void)
{
    FILE *fp;
    char ip[20];
    char *pp;
    struct in_addr addr;

    if(access("/tmp/dhcpd.delete",F_OK)==0)
    {
        if( (fp=fopen("/tmp/dhcpd.delete","r")) != NULL )
        {
            while(fgets(ip,20,fp)!=NULL)
            {
                if( (pp=strchr(ip,'#')) != NULL )
                {
                    *pp='\0';
                    inet_aton(ip, &addr);
                    expire_action(addr.s_addr);
                }
            }
            fclose(fp);
        }
        system("/bin/rm -rf /tmp/dhcpd.delete");
    }
}

static void print_lease_info(void)
{    
    int i, j;
    time_t curr = time(0);
    unsigned char *mac, *ip;

    printf("\nMAC Address\t\tIP Address\tRemaining Time\n");
    for(i = 0; i < no_of_ifaces; i++)
    {
        for(j = 0; j < server_config[i].max_leases; j++)
        {
            if (leases[i][j].expires > curr)
            {
                mac = (unsigned char *)leases[i][j].chaddr;
                ip = (unsigned char *)&leases[i][j].yiaddr;
                printf("%02x:%02x:%02x:%02x:%02x:%02x\t%u.%u.%u.%u\t%d\n",
                       mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
                       ip[0], ip[1], ip[2], ip[3], leases[i][j].expires-curr);
            }
        }
    }
}

/* signal handler */
static void udhcpd_recv_signal(int sig)
{
    LOG(LOG_INFO, "udhcp server receive signal %d", sig);
    SC_DEBUG(DEBUG_DHCPD, "udhcp server receive signal %d\n", sig);
    signal_sig = sig;
    signal_flag = 1;
}

static void signal_action(void)
{
    signal_flag = 0;

    if (SIGUSR1 == signal_sig)
    {
        do_expire();
        print_lease_info();
    }
    else if (SIGUSR2 == signal_sig)
    {
        reconfig_dhcpd(conf_file);
    }
    else if (SIGTERM == signal_sig)
    {
#if defined(__SC_BUILD__) && defined(__SC_LEASE_RETAIN__)
        retain_lease_info();
        LOG(LOG_INFO, "udhcp server retain lease end.");
#else
        update_lease_files();
#endif
        exit_server(0, 0);
    }
    else if (SIGHUP == signal_sig || SIGINT == signal_sig) 
    {
        update_lease_files();
        exit_server(0, 0);
    }

    signal_sig = -1;
}



void SendLogToPC(u_int8_t *chaddr,u_int32_t yiaddr,int flag)
{
    struct in_addr leaseip;
    char mac[20]="";
    char *ip;
    char sendbuf[100];

    leaseip.s_addr=yiaddr;
    ip=inet_ntoa(leaseip);
    sprintf(mac,"%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX\n"
            ,chaddr[0],chaddr[1],chaddr[2],chaddr[3],chaddr[4],chaddr[5]);
    if(flag == 1)	
        sprintf(sendbuf,"[SC][Dhcp]:%s %s Request", ip, mac);	
    else if(flag == 2)
        sprintf(sendbuf,"[SC][Dhcp]:%s %s Release", ip, mac);		
    else 
        return;
    syslog(4,sendbuf);
    return;   
}

/* add by jacob */
static int check_bind_mac(unsigned char *bind_mac, unsigned char *client_mac)
{
    unsigned int i, len;
    char mac[20];

    /* 00:c0:02:**:**:** length is 17 */
    len = strlen((char *)bind_mac);
    if (len > 20)
        return FALSE;

    sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", client_mac[0], client_mac[1],
            client_mac[2], client_mac[3], client_mac[4], client_mac[5]);

    if (len < strlen(mac))
        return FALSE;

    len = strlen(mac);
    for (i = 0; i < len; i++)
    {
        if ('*' == bind_mac[i])
            continue;
        if (tolower(bind_mac[i]) != tolower(mac[i]))
        {
            return FALSE;
        }
    }
    return TRUE;
}

static int get_subnet_id(u_int32_t client_ip)
{
    //struct option_set *option;
    int i;

    for (i = 0; i < no_of_ifaces; i++)
    {
        if ((server_config[i].netmask & server_config[i].server) == (server_config[i].netmask & client_ip))
            return i;
    }
    return -1;
}
/* end jacob */

#if defined(__SC_BUILD__) && defined(__SC_CONDITIONAL_SERVING_PER_IF__)
typedef struct bridge_port_mapping_entry_s
{
    int sc_port;
    int brg_port;
}bridge_port_mapping_entry_t;
static struct bridge_port_mapping_entry_s bridge_port_mapping_table[] = {
    {SC_PORT_LAN_1,     BRIDGE_PORT_LAN_1},
    {SC_PORT_LAN_2,     BRIDGE_PORT_LAN_2},
    {SC_PORT_LAN_3,     BRIDGE_PORT_LAN_3},
    {SC_PORT_LAN_4,     BRIDGE_PORT_LAN_4},
    {SC_PORT_WLAN_1,    BRIDGE_PORT_WLAN_1},
    {SC_PORT_WLAN_2,    BRIDGE_PORT_WLAN_2},
    {SC_PORT_WLAN_3,    BRIDGE_PORT_WLAN_3},
    {SC_PORT_WLAN_4,    BRIDGE_PORT_WLAN_4},
    {SC_PORT_NONE,      BRIDGE_PORT_NONE}
};

static int valid_source_bridge_port(int src_bridge_port)
{
    int i;

    for (i = 0; bridge_port_mapping_table[i].sc_port != SC_PORT_NONE; i++)
    {
        if (bridge_port_mapping_table[i].brg_port == src_bridge_port)
            return TRUE;
    }
    return FALSE;
}
static int check_bind_interface(int bind_if, int src_bridge_port)
{
    int i;

    if (SC_PORT_NONE == bind_if)
        return FALSE;

    for (i = 0; bridge_port_mapping_table[i].sc_port != SC_PORT_NONE; i++)
    {
        if (bridge_port_mapping_table[i].brg_port == src_bridge_port)
        {
            if (bridge_port_mapping_table[i].sc_port & bind_if)
                return TRUE;
            else
                return FALSE;
        }
    }
    return FALSE;
}
#endif /* __SC_CONDITIONAL_SERVING_PER_IF__ */

#ifdef COMBINED_BINARY	
int udhcpd_main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{	
    fd_set rfds;
    struct timeval tv;
    int server_socket;
    int bytes, retval;
    struct dhcpMessage packet;
    unsigned char *state;
    unsigned char *vendor_id;
    unsigned char *server_id, *requested;
    u_int32_t server_id_align, requested_align;
    unsigned long timeout_end;
    struct option_set *option;
    struct dhcpOfferedAddr *lease;
    struct dhcpOfferedAddr static_lease;
    int pid_fd;
    int i;
    int active_count = 0;	
    uint32_t static_lease_ip;
#if defined(__SC_BUILD__)
    struct pkt_extra_info extra_info;
    int src_bridge_port;
#endif

#ifdef TR069
    unsigned char *vendor_spc=NULL;
#endif		
    OPEN_LOG("udhcpd");
    LOG(LOG_INFO, "udhcp server (v%s) started", VERSION);

    SC_DEBUG(DEBUG_DHCPD, "udhcp server start...\n");

    for (i = 0; i < MAX_INTERFACES; i++)
        memset(&server_config[i], 0, sizeof(struct server_config_t));

    if (argc < 2)
        snprintf(conf_file, sizeof(conf_file), "%s", DHCPD_CONF_FILE);
    else
        snprintf(conf_file, sizeof(conf_file), "%s", argv[1]);
    read_config(conf_file);

    if (argc >= 3 && !strcmp(argv[2], "-n"))
        default_enable = FALSE;

    if (no_of_ifaces == 0)
        exit(0);

    SC_DEBUG(DEBUG_DHCPD, "no_of_ifaces:%d\n", no_of_ifaces);

    for (i = 0; i < no_of_ifaces; i++)
    {
        pid_fd = pidfile_acquire(server_config[i].pidfile);
        pidfile_write_release(pid_fd);

        if ((option = find_option(server_config[i].options, DHCP_LEASE_TIME))) {
            memcpy(&server_config[i].lease, option->data + 2, 4);
            server_config[i].lease = ntohl(server_config[i].lease);
        }
        else server_config[i].lease = LEASE_TIME;

        if ((option = find_option(server_config[i].options, DHCP_SUBNET)))
        {
            memcpy(&server_config[i].netmask, option->data + 2, 4);
        }
        else
            server_config[i].netmask = htonl(SUBNET_MASK);

        leases[i] = malloc(sizeof(struct dhcpOfferedAddr) * server_config[i].max_leases);
        memset(leases[i], 0, sizeof(struct dhcpOfferedAddr) * server_config[i].max_leases);

        read_leases(server_config[i].lease_file, i);

        if (read_interface(server_config[i].interface, &server_config[i].ifindex,
                           &server_config[i].server, server_config[i].arp) < 0)
            server_config[i].active = FALSE;
        else
            server_config[i].active = TRUE;

#ifndef DEBUGGING
        pid_fd = pidfile_acquire(server_config[i].pidfile); /* hold lock during fork. */
        /* cfgmr req: do not fork */
        /*
           if (daemon(0, 0) == -1) {
           perror("fork");
           exit_server(1, i);
           }
           */

        pidfile_write_release(pid_fd);
#endif
    }

    for (active_count = 0, i = 0; i < no_of_ifaces; i++)
    {
        SC_DEBUG(DEBUG_DHCPD, "\ninterface:%s\n", server_config[i].interface?:"");
        SC_DEBUG(DEBUG_DHCPD, "active:%s\n", (server_config[i].active == TRUE)?"1":"0");
        SC_DEBUG(DEBUG_DHCPD, "cds_enable:%s\n", server_config[i].cds_enable?:"");
        SC_DEBUG(DEBUG_DHCPD, "vendor_bind:%s\n", server_config[i].vendor_bind?:"");
        SC_DEBUG(DEBUG_DHCPD, "mac_bind:%s\n", server_config[i].mac_bind?:"");
        if (TRUE == server_config[i].active)
            active_count++;
    }
    if (0 == active_count)
        exit_server(0, 0);

#if defined(__SC_BUILD__) && defined(__SC_LEASE_RETAIN__)
    if (load_retained_lease_info() > 0)
    {
        update_lease_files();
        clear_retained_lease_info();
    }
#endif

    signal(SIGUSR2, (void *)udhcpd_recv_signal);
    signal(SIGUSR1, (void *)udhcpd_recv_signal);
    signal(SIGTERM, (void *)udhcpd_recv_signal);
    signal(SIGINT, (void *)udhcpd_recv_signal);
    signal(SIGHUP, (void *)udhcpd_recv_signal);

    SC_DEBUG(DEBUG_DHCPD, "enter the main loop\n");

    server_socket = -1;
    while(1)  /* loop until universe collapses */
    {
        if (signal_flag)
        {
            signal_action();
        }

        if (server_socket < 0)
        {
#if defined(__SC_BUILD__) 
            if ((server_socket = listen_socket(INADDR_ANY, SERVER_PORT, DHCPD_LAN_IFNAME, 1)) < 0)
#else
                if ((server_socket = listen_socket(INADDR_ANY, SERVER_PORT, DHCPD_LAN_IFNAME)) < 0)
#endif
                {
                    LOG(LOG_ERR, "FATAL: couldn't create server socket, errno: %d", errno);
                    SC_DEBUG(DEBUG_DHCPD, "FATAL: couldn't create server socket, errno: %d\n", errno);
                    exit_server(0, 0);
                }
        }     
        /* fd set. */
        FD_ZERO(&rfds);
        FD_SET(server_socket, &rfds);

        /* set time */
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        retval = select(server_socket + 1, &rfds, NULL, NULL, &tv);
        if (retval == 0) {
            if (WRITE_LEASE_FILE_INTERVAL == past_seconds)
            {
                update_lease_files();
                past_seconds = 0;
            }
            else
                past_seconds++;
            continue;
        } else if (retval < 0) {
            DEBUG(LOG_INFO, "error on select");
            SC_DEBUG(DEBUG_DHCPD, "error on select, errno:%d, failed:%s\n", errno, strerror(errno));
            continue;
        }
#if defined(__SC_BUILD__)
        if ((bytes = get_packet(&packet, server_socket, &extra_info)) < 0) { /* this waits for a packet - idle */
#else
            if ((bytes = get_packet(&packet, server_socket)) < 0) { /* this waits for a packet - idle */
#endif
                if (bytes == -1 && errno != EINTR) {
                    DEBUG(LOG_INFO, "error on read, errno %d, reopening socket", errno);
                    SC_DEBUG(DEBUG_DHCPD, "error on read, errno %d, reopening socket\n", errno);
                    close(server_socket);
                    server_socket = -1;
                }
                continue;
            }

#if defined(__SC_BUILD__)
            src_bridge_port = extra_info.ptr_pktinfo.ipi_ifindex;
#endif

            if ((state = get_option(&packet, DHCP_MESSAGE_TYPE)) == NULL) {
                DEBUG(LOG_ERR, "couldn't get option from packet, ignoring");
                SC_DEBUG(DEBUG_DHCPD, "couldn't get option from packet, ignoring\n");
                continue;
            }

            // init i, no server config will be used
            i = no_of_ifaces;

            if (DHCPRELEASE == state[0])
            {
                i = get_subnet_id(packet.ciaddr);
                if (i < 0)
                    continue;
                goto FIND_DHCP_LEASE;
            }

            // check which server config meet the packet mac
            if (i == no_of_ifaces)
            {
                SC_DEBUG(DEBUG_DHCPD, "packet mac:%02x:%02x:%02x:%02x:%02x:%02x\n", 
                         packet.chaddr[0], packet.chaddr[1], packet.chaddr[2], 
                         packet.chaddr[3], packet.chaddr[4], packet.chaddr[5]);
                for (i = 0; i < no_of_ifaces; i++)
                {
                    if (server_config[i].active == FALSE || !server_config[i].cds_enable || *server_config[i].cds_enable != '1')
                        continue;
                    if (server_config[i].mac_bind && check_bind_mac(server_config[i].mac_bind, packet.chaddr))
                    {
                        break;
                    }
                }
            }

            // check which server config meet the DHCP_VENDOR_ID
            if (i == no_of_ifaces)
            {
                if ((vendor_id = get_option(&packet, DHCP_VENDOR)) != NULL)
                {
                    SC_DEBUG(DEBUG_DHCPD, "packet DHCP_VENDOR:%s\n", vendor_id);
                    for (i = 0; i < no_of_ifaces; i++)
                    {
                        if (server_config[i].active == FALSE || !server_config[i].cds_enable || *server_config[i].cds_enable != '1')
                            continue;

                        if (server_config[i].vendor_bind && strstr(vendor_id, server_config[i].vendor_bind))
                        {
                            break;
                        }
                    }
                }
            }

#if defined(__SC_BUILD__) && defined(__SC_CONDITIONAL_SERVING_PER_IF__)
            // check which server config meet the src_bridge_port
            if (i == no_of_ifaces)
            {
                if (valid_source_bridge_port(src_bridge_port))
                {
                    SC_DEBUG(DEBUG_DHCPD, "packet port:%d\n", src_bridge_port);
                    for (i = 0; i < no_of_ifaces; i++)
                    {
                        if (server_config[i].active == FALSE || !server_config[i].cds_enable || *server_config[i].cds_enable != '1')
                            continue;

                        if (check_bind_interface(server_config[i].brg_port_bind, src_bridge_port))
                        {
                            break;
                        }
                    }
                }
            }
#endif

            if (i == no_of_ifaces)
            {
                SC_DEBUG(DEBUG_DHCPD, "nothing match\n");
                if (TRUE == default_enable && server_config[DEFAULT_SERVER_CONFIG].cds_enable && *server_config[DEFAULT_SERVER_CONFIG].cds_enable != '1')
                    i = DEFAULT_SERVER_CONFIG;
                else
                {
                    if (DHCPREQUEST == state[0])
                        sendNAK(&packet, DEFAULT_SERVER_CONFIG);
                    continue;
                }
            }

FIND_DHCP_LEASE:
            /* ADDME: look for a static lease */
            static_lease_ip = getIpByMac(server_config[i].static_leases, &packet.chaddr);

            if(static_lease_ip)
            {
                printf("Found static lease: %x\n", static_lease_ip);
                SC_DEBUG(DEBUG_DHCPD, "Found static lease: %x\n", static_lease_ip);

                memcpy(&static_lease.chaddr, &packet.chaddr, 16);
                static_lease.yiaddr = static_lease_ip;
                static_lease.expires = 0;

                lease = &static_lease;

            }
            else
            {
                lease = find_lease_by_chaddr(packet.chaddr, i);
            }

            SC_DEBUG(DEBUG_DHCPD, "Select interface:%s, and now deal the state\n", server_config[i].interface?:"");

            switch (state[0]) {
            case DHCPDISCOVER:
                DEBUG(LOG_INFO,"received DISCOVER");
                SC_DEBUG(DEBUG_DHCPD, "received DISCOVER\n");
                if(do_option_action(state[0], &packet, i) != 0)
                    break;
                SC_DEBUG(DEBUG_DHCPD, "option action check ok\n");
#ifdef __SC_BUILD__
                if (sendOffer(&packet, i, &extra_info) < 0) {
                    LOG(LOG_ERR, "send OFFER failed");
                    SC_DEBUG(DEBUG_DHCPD, "send OFFER failed\n");
                }
#else
                if (sendOffer(&packet, i) < 0) {
                    LOG(LOG_ERR, "send OFFER failed");
                    SC_DEBUG(DEBUG_DHCPD, "send OFFER failed\n");
                }
#endif
                break;			

            case DHCPREQUEST:
                DEBUG(LOG_INFO, "received REQUEST");
                SC_DEBUG(DEBUG_DHCPD, "received REQUEST\n");
                if(do_option_action(state[0], &packet, i) != 0)
                    break;
                SC_DEBUG(DEBUG_DHCPD, "option action check ok\n");
                requested = get_option(&packet, DHCP_REQUESTED_IP);
                server_id = get_option(&packet, DHCP_SERVER_ID);
#ifdef __SC_BUILD__ 
                /* save client option file */
                sc_create_option_file(&packet, DHCP_VENDOR);
                //sc_create_option_file(&packet, DHCP_HOST_NAME);
                //sc_create_option_file(&packet, DHCP_VENDOR_INFO);
#endif
                if (requested) memcpy(&requested_align, requested, 4);
                if (server_id) memcpy(&server_id_align, server_id, 4);

                if (lease) { /*ADDME: or static lease */
                    if (server_id) {
                        /* SELECTING State */
                        DEBUG(LOG_INFO, "server_id = %08x", ntohl(server_id_align));
                        if (server_id_align == server_config[i].server && requested && 
                            requested_align == lease->yiaddr) {
#ifdef __SC_BUILD__
                            sendACK(&packet, lease->yiaddr, i, &extra_info);
#else
                            sendACK(&packet, lease->yiaddr, i);
#endif
                        }
                    } else {
                        if (requested) {
                            /* INIT-REBOOT State */
#if defined(__SC_BUILD__) && defined(__SC_ARP__)
                            if (lease->yiaddr == requested_align && !check_ip(lease->yiaddr, i, packet.chaddr))
#else
                                if (lease->yiaddr == requested_align)
#endif
#ifdef __SC_BUILD__
                                    sendACK(&packet, lease->yiaddr, i, &extra_info);
#else
                                    sendACK(&packet, lease->yiaddr, i);
#endif
                                else sendNAK(&packet, i);
                        } else {
                            /* RENEWING or REBINDING State */
#if defined(__SC_BUILD__) && defined(__SC_ARP__)
                            if (lease->yiaddr == packet.ciaddr && !check_ip(lease->yiaddr, i, packet.chaddr))
#else
                                if (lease->yiaddr == packet.ciaddr)
#endif
#ifdef __SC_BUILD__
                                    sendACK(&packet, lease->yiaddr, i, &extra_info);
#else
                                    sendACK(&packet, lease->yiaddr, i);
#endif
                                else {
                                    /* don't know what to do!!!! */
                                    sendNAK(&packet, i);
                                }	
                        }						
                    }
                    /* what to do if we have no record of the client */
                } else if (server_id) {
                    /* SELECTING State */
                    sendNAK(&packet,i);

                } else if (requested) {
                    /* INIT-REBOOT State */
                    if ((lease = find_lease_by_yiaddr(requested_align,i))) {
                        if (lease_expired(lease)) {
                            /* probably best if we drop this lease */
                            memset(lease->chaddr, 0, 16);
                            /* make some contention for this address */
                        } else { 
                            sendNAK(&packet,i);
                        }
                    } else if (requested_align < server_config[i].start ||
                               requested_align > server_config[i].end) {
                        sendNAK(&packet,i);
                    } else {
                        /* else remain silent */
                        sendNAK(&packet,i);
                    }

                } else {
                    /* RENEWING or REBINDING State */
                    sendNAK(&packet,i);

                }
                if(lease != NULL)          		
                {       			
                    SendLogToPC(packet.chaddr,lease->yiaddr,1);  
                }
                break;

            case DHCPDECLINE:
                DEBUG(LOG_INFO,"received DECLINE");
                SC_DEBUG(DEBUG_DHCPD, "received DECLINE\n");
                if (lease) {
                    memset(lease->chaddr, 0, 16);
                    lease->expires = time(0) + server_config[i].decline_time;
                }			
                break;

            case DHCPRELEASE:
                DEBUG(LOG_INFO,"received RELEASE");
                SC_DEBUG(DEBUG_DHCPD, "received RELEASE\n");
                if (lease) {        			
                    SendLogToPC(lease->chaddr,lease->yiaddr,2);
                    lease->expires = time(0);
                    //delete udhcp.lease
                    FILE *fp;
                    int buf_len;
                    unsigned char clientmac[16] = "";
                    unsigned char mac[18] = "";  
                    char *buf, *s;
                    char line[256];
                    memcpy(clientmac, packet.chaddr, 16); 
                    sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",
                            clientmac[0], clientmac[1], clientmac[2],
                            clientmac[3], clientmac[4], clientmac[5]);
                    if( (fp=fopen(VENDOR_FILE, "r"))!=NULL )
                    {
                        fseek(fp, 1, SEEK_END);
                        buf_len = ftell(fp) + 2;
                        rewind(fp);
                        if( (buf = (char*)malloc(sizeof(char)*buf_len))!=NULL )
                        {
                            memset(buf, 0, sizeof(char)*buf_len);
                            while(fgets(line, 255, fp))
                            {
                                s=strstr(line, mac);
                                if(s==NULL)
                                {
                                    strcat(buf, line);
                                }
                            }
                            fclose(fp);
                            if( (fp=fopen(VENDOR_FILE, "w"))!=NULL )
                            {
                                fprintf(fp, "%s", buf);
                                fclose(fp);
                            }
                            free(buf);
                        }
                        else
                        {
                            fclose(fp);
                        }
                    }
                }
                break;

            case DHCPINFORM:
                DEBUG(LOG_INFO,"received INFORM");
                SC_DEBUG(DEBUG_DHCPD, "received INFORM\n");
                send_inform(&packet, i);
                break;	

            default:
                LOG(LOG_WARNING, "unsupported DHCP message (%02x) -- ignoring", state[0]);
                SC_DEBUG(DEBUG_DHCPD, "unsupported DHCP message (%02x) -- ignoring\n", state[0]);
            }
        }
        return 0;
    }

