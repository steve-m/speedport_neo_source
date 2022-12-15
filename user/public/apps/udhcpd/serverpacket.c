/* serverpacket.c
 *
 * Constuct and send DHCP server packets
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

#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <stdarg.h>
#include "packet.h"
#include "debug.h"
#include "dhcpd.h"
#include "options.h"
#include "leases.h"
#include "static_leases.h"

#ifdef __SC_BUILD__
#include <sys/un.h>
#include "snbd_hostdb.h"
#include "snbd_cmd.h"
#endif

#ifdef TR069
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <netinet/in.h>	
#include <arpa/inet.h>
#define BROADBRAND_ENTERPRISE_NUMBER 3561    /* assigned by IANA */
#define DT_ENTERPRISE_NUMBER 2937    /* assigned by IANA */
#define GW_IDENTITY "/tmp/dhcp.vendoroption"

#endif

#if defined(__SC_BUILD__) && defined(DT_SMART_SETUP)
static int get_string_option(char *pkt, int opt, char buf[])
{
    uint8_t *option_p = get_option(pkt, opt);
    if(!option_p)
        return -1;

    uint8_t len = *(option_p-1);

    memcpy(buf, option_p, len);
    buf[len] = 0;

    return 0;
}
static char *DFND_productClass[] = {
    "DTWNEOV01PV", /* NeoVoice */
    NULL
};

static int check_dfnd_device(char *pkt)
{
    char productclass[256] = {0};

    if(get_string_option(pkt, 60, productclass) == -1)
        return 0;

    int i;
    for(i = 0; DFND_productClass[i] != NULL; i++) {
        if(strcmp(productclass, DFND_productClass[i]) == 0)
            return 1;
    }

    return 0;
}
#endif

/* send a packet to giaddr using the kernel ip stack */
static int send_packet_to_relay(struct dhcpMessage *payload, int ifid)
{
    DEBUG(LOG_INFO, "Forwarding packet to relay");

    return kernel_packet(payload, server_config[ifid].server, SERVER_PORT,
                         payload->giaddr, SERVER_PORT);
}


/* send a packet to a specific arp address and ip address by creating our own ip packet */
static int send_packet_to_client(struct dhcpMessage *payload, int force_broadcast, int ifid)
{
    unsigned char *chaddr;
    u_int32_t ciaddr;

    if (force_broadcast) {
        DEBUG(LOG_INFO, "broadcasting packet to client (NAK)");
        SC_DEBUG(DEBUG_DHCPD, "broadcasting packet to client (NAK)\n");
        ciaddr = INADDR_BROADCAST;
        chaddr = MAC_BCAST_ADDR;
    } else if (payload->ciaddr) {
        DEBUG(LOG_INFO, "unicasting packet to client ciaddr");
        SC_DEBUG(DEBUG_DHCPD, "unicasting packet to client ciaddr\n");
        ciaddr = payload->ciaddr;
        chaddr = payload->chaddr;
    } else if (ntohs(payload->flags) & BROADCAST_FLAG) {
        DEBUG(LOG_INFO, "broadcasting packet to client (requested)");
        SC_DEBUG(DEBUG_DHCPD, "broadcasting packet to client (requested)\n");
        ciaddr = INADDR_BROADCAST;
        chaddr = MAC_BCAST_ADDR;
    } else {
        DEBUG(LOG_INFO, "unicasting packet to client yiaddr");
        SC_DEBUG(DEBUG_DHCPD, "unicasting packet to client yiaddr\n");
        ciaddr = payload->yiaddr;
        chaddr = payload->chaddr;
    }
    return raw_packet(payload, server_config[ifid].server, SERVER_PORT,
                      ciaddr, CLIENT_PORT, chaddr, server_config[ifid].ifindex);
}


/* send a dhcp packet, if force broadcast is set, the packet will be broadcast to the client */
static int send_packet(struct dhcpMessage *payload, int force_broadcast, int ifid)
{
    int ret;

    if (payload->giaddr)
        ret = send_packet_to_relay(payload, ifid);
    else ret = send_packet_to_client(payload, force_broadcast, ifid);
    return ret;
}


static void init_packet(struct dhcpMessage *packet, struct dhcpMessage *oldpacket, char type, int ifid)
{
    init_header(packet, type);
    packet->xid = oldpacket->xid;
    memcpy(packet->chaddr, oldpacket->chaddr, 16);
    packet->flags = oldpacket->flags;
    packet->giaddr = oldpacket->giaddr;
    packet->ciaddr = oldpacket->ciaddr;
    add_simple_option(packet->options, DHCP_SERVER_ID, server_config[ifid].server);
}


/* add in the bootp options */
static void add_bootp_options(struct dhcpMessage *packet, int ifid)
{
    packet->siaddr = server_config[ifid].siaddr;
    if (server_config[ifid].sname)
        strncpy(packet->sname, server_config[ifid].sname, sizeof(packet->sname) - 1);
    if (server_config[ifid].boot_file)
        strncpy(packet->file, server_config[ifid].boot_file, sizeof(packet->file) - 1);
}

#ifdef TR069
/*static char *cpe_getSerialNumber(void)
  {
  FILE *fp;
  char tmp[18] = {'\0'};	
  static	char serialnumber[18] = {0,};
  int i=0,j=0;

  if((fp=fopen("/tmp/mac","r"))!=NULL){
  fread(tmp,20,1,fp);
  tmp[17] = '\0';
  for(i=0;i<17;i++){
  if(tmp[i] != ':'){
  serialnumber[j] = tmp[i];
  j++;
  }
  }		    
  fclose(fp);
  serialnumber[j] = '\0';
  return (serialnumber);
  }
//fclose(fp);
sprintf(serialnumber,"%s",CWMP_MANUFACTURER_SERIAL);

return (serialnumber);
}*/

static void add_vendor_options(struct dhcpMessage *packet, int ifid)
{
    unsigned char *data = NULL,*pt=NULL;
    unsigned char oui[9]="",sn[66]="",prds[66]="";
    int len = 0,rc=-1;

    pt=server_config[ifid].manufacturer_oui;
    len = sprintf(oui,"%c%c%s",(unsigned char)1,(unsigned char)strlen(pt),pt);
    pt=server_config[ifid].serial_number;
    len += sprintf(sn,"%c%c%s",(unsigned char)2,(unsigned char)strlen(pt),pt);
    pt=server_config[ifid].model_name;
    len += sprintf(prds,"%c%c%s",(unsigned char)3,(unsigned char)strlen(pt),pt);

    data = (unsigned char *)malloc(len + 8);
    if(data==NULL)
        return;
    memset(data, 0, len+8);
    sprintf(data,"%c%c%c%c%c%c%c%s%s%s"
            ,(unsigned char)DHCP_VENDOR_SPEC     /* option-code 8bits */
            ,(unsigned char)(len + 5)            /* option-len 8bits */
            /* enterprise-number 32bits */
            ,(unsigned char)(DT_ENTERPRISE_NUMBER>>24)
            ,(unsigned char)(DT_ENTERPRISE_NUMBER>>16)
            ,(unsigned char)(DT_ENTERPRISE_NUMBER>>8)
            ,(unsigned char)DT_ENTERPRISE_NUMBER
            ,(unsigned char)len                  /* data-len 8bits */
            /* sub-option*/
            ,oui
            ,sn
            ,prds);
    rc = add_option_string(packet->options, data);

    free(data);
    return;
}
#endif

/* add dns option, check if there is fix dns server */
static void add_dns_option(unsigned char *optionptr, unsigned char *pipe_dns, int ifid)
{
#define IP_LEN  4
    unsigned char dns[400] = "";
    u_int32_t dns_server;
    unsigned int len = 0;

    dns[OPT_CODE] = DHCP_DNS_SERVER;
    if (server_config[ifid].dns_server)
    {
        struct dhcp_ip_list_s *cur = server_config[ifid].dns_server;
        while(cur)
        {
            memcpy(dns + OPT_DATA + len, &cur->ip, sizeof(cur->ip));
            len += sizeof(cur->ip);
            cur = cur->next;
        }
    }

    /* dns_proxy enable add lan ip in the dns option
       lan ip is the first ip in the pipe_dns */
    if (server_config[ifid].dns_proxy && '1' == *server_config[ifid].dns_proxy)
    {
        memcpy(dns + OPT_DATA + len, pipe_dns + OPT_DATA, pipe_dns[OPT_LEN]);
        len += pipe_dns[OPT_LEN];
    }
    else if (pipe_dns[OPT_LEN] > IP_LEN)
    {
        memcpy(dns + OPT_DATA + len, pipe_dns + OPT_DATA + IP_LEN, pipe_dns[OPT_LEN] - IP_LEN);
        len += pipe_dns[OPT_LEN] - IP_LEN;
    }
    if (len > 0)
    {
        dns[OPT_LEN] = len;
        add_option_string(optionptr, dns);
    }
}

#define ADD_DNS_OPTIONS() \
    do{\
        add_dns_option(packet.options, curr->data, ifid);\
        \
    }while(0)

/* send a DHCP OFFER to a DHCP DISCOVER */
#ifdef __SC_BUILD__
int sendOffer(struct dhcpMessage *oldpacket, int ifid, struct pkt_extra_info *extra_info)
#else
int sendOffer(struct dhcpMessage *oldpacket, int ifid)
#endif
{
    struct dhcpMessage packet;
    struct dhcpOfferedAddr *lease = NULL;
    u_int32_t req_align = 0, lease_time_align = server_config[ifid].lease;
    unsigned char *req, *lease_time;
    struct option_set *curr;
    struct in_addr addr;

    uint32_t static_lease_ip;

#ifdef __SC_BUILD__
    char hostname[MAX_HOSTNAME_LEN]="";
    if(extra_info && extra_info->dscp == 0x18)
        lease_time_align = UINT_MAX;
#endif
#ifdef TR069
    unsigned char *vendor_spc;
    vendor_spc = get_option(oldpacket, DHCP_VENDOR_SPEC);
#endif
    init_packet(&packet, oldpacket, DHCPOFFER, ifid);

    static_lease_ip=getIpByMac(server_config[ifid].static_leases,oldpacket->chaddr);
#if defined(__SC_BUILD__) && defined(__SC_ARP__)
    if (static_lease_ip && !check_ip(static_lease_ip, ifid, packet.chaddr))
#else
        if (static_lease_ip)
#endif
        {
            /*It is a static lease... use it*/
            packet.yiaddr=static_lease_ip;
        }

    /* ADDME: if static, short circuit */
    if (!packet.yiaddr)
    {
        /* the client is in our lease/offered table */
#if defined(__SC_BUILD__) && defined(__SC_ARP__)
        if ((lease = find_lease_by_chaddr(oldpacket->chaddr, ifid))&& !check_ip(lease->yiaddr, ifid, packet.chaddr))
#else
            if ((lease = find_lease_by_chaddr(oldpacket->chaddr, ifid)))
#endif
            {
                if (!lease_expired(lease))
                    lease_time_align = lease->expires - time(0);
                packet.yiaddr = lease->yiaddr;
                SC_DEBUG(DEBUG_DHCPD, "Find a lease info, and use the ip:%08x\n", lease->yiaddr);
            }
        /* Or the client has a requested ip */
            else if ((req = get_option(oldpacket, DHCP_REQUESTED_IP)) &&
                     /* Don't look here (ugly hackish thing to do) */
                     memcpy(&req_align, req, 4) &&
                     /* and the ip is in the lease range */
                     ntohl(req_align) >= ntohl(server_config[ifid].start) &&
                     ntohl(req_align) <= ntohl(server_config[ifid].end) &&
                     ntohl(req_align) != ntohl(server_config[ifid].server) &&
                     !static_lease_ip &&
                     /* and its not already taken/offered */ /* ADDME: check that its not a static lease */
                     ((!(lease = find_lease_by_yiaddr(req_align, ifid)) ||

                       /* or its taken, but expired */ /* ADDME: or maybe in here */
                       lease_expired(lease))))
            {
                /* check id addr is not taken by a static ip */
#ifdef __SC_BUILD__
#ifdef __SC_ARP__
                if(!check_ip(req_align, ifid, packet.chaddr))
#else
                    if(!check_ip(req_align, ifid))
#endif
#else
                        if(!check_ip(req_align))
#endif
                        {
                            packet.yiaddr = req_align; /* FIXME: oh my, is there a host using this IP? */
                            SC_DEBUG(DEBUG_DHCPD, "Use requested ip:%08x\n", req_align);
                        }
                        else
                        {
                            /*is it now a static lease, no,beacause find_address skips static lease*/
                            packet.yiaddr = find_address(0, ifid);
                            /* try for an expired lease */
                            if (!packet.yiaddr)
                                packet.yiaddr = find_address(1, ifid);
                            SC_DEBUG(DEBUG_DHCPD, "Find an assignable address:%08x\n", packet.yiaddr);
                        }
            }
        /* otherwise, find a free IP */ /*ADDME: is it a static lease? */
            else
            {
                packet.yiaddr = find_address(0, ifid);
                /* try for an expired lease */
                if (!packet.yiaddr)
                    packet.yiaddr = find_address(1, ifid);
                SC_DEBUG(DEBUG_DHCPD, "Find a free address:%08x\n", packet.yiaddr);
            }
        if(!packet.yiaddr)
        {
            LOG(LOG_WARNING, "no IP addresses to give -- OFFER abandoned");
            SC_DEBUG(DEBUG_DHCPD, "no IP addresses to give -- OFFER abandoned\n");
            return -1;
        }
#ifdef __SC_BUILD__
        {
            char *tmp=get_option(oldpacket,DHCP_HOST_NAME);
            int len=0;
            if(tmp)
            {
                len=*(tmp-1);

                if(len > sizeof(hostname) - 1)
                    len = sizeof(hostname) - 1;

                strncpy(hostname,tmp,len);
                hostname[len] = '\0';
            }
            //printf("client->name==%s\n",hostname);
        }
        if (!add_lease(packet.chaddr, packet.yiaddr, server_config[ifid].offer_time, ifid,hostname))
        {
            LOG(LOG_WARNING, "lease pool is full -- OFFER abandoned");
            SC_DEBUG(DEBUG_DHCPD, "lease pool is full -- OFFER abandoned\n");
            return -1;
        }
#else
        if (!add_lease(packet.chaddr, packet.yiaddr, server_config[ifid].offer_time, ifid))
        {
            LOG(LOG_WARNING, "lease pool is full -- OFFER abandoned");
            return -1;
        }
#endif
        if ((lease_time = get_option(oldpacket, DHCP_LEASE_TIME)))
        {
            memcpy(&lease_time_align, lease_time, 4);
            lease_time_align = ntohl(lease_time_align);
            if (lease_time_align > server_config[ifid].lease)
                lease_time_align = server_config[ifid].lease;
        }

        /* Make sure we aren't just using the lease time from the previous offer */
        if (lease_time_align < server_config[ifid].min_lease)
            lease_time_align = server_config[ifid].lease;
        /* ADDME: end of short circuit */
    }

#ifdef __SC_BUILD__
    if(extra_info && extra_info->dscp == 0x18)
        lease_time_align = UINT_MAX;
#if defined(DT_SMART_SETUP)
    if(check_dfnd_device(oldpacket))
        lease_time_align = 360 * 24 * 3600;
#endif
#endif
    add_simple_option(packet.options, DHCP_LEASE_TIME, htonl(lease_time_align));
    curr = server_config[ifid].options;
    while (curr) {
        if (curr->data[OPT_CODE] != DHCP_LEASE_TIME && curr->data[OPT_CODE] != DHCP_VENDOR_INFO)
        {
            if (curr->data[OPT_CODE] == DHCP_DNS_SERVER)
            {
                ADD_DNS_OPTIONS();
            }
            else
                add_option_string(packet.options, curr->data);
        }
        curr = curr->next;
    }
#ifdef TR069
    if(vendor_spc)
        add_vendor_options(&packet, ifid);
#endif

    add_bootp_options(&packet, ifid);

    addr.s_addr = packet.yiaddr;
#ifndef __SC_BUILD__
    LOG(LOG_INFO, "sending OFFER of %s", inet_ntoa(addr));
#endif
    SC_DEBUG(DEBUG_DHCPD, "sending OFFER of %s\n", inet_ntoa(addr));

    return send_packet(&packet, 0, ifid);
}


int sendNAK(struct dhcpMessage *oldpacket, int ifid)
{
    struct dhcpMessage packet;
    init_packet(&packet, oldpacket, DHCPNAK, ifid);

#ifdef __SC_BUILD__
    syslog(LOG_INFO, "%s"LOG_ERRCODE_H003, log_type_db[GENERAL_LOG]);
#endif

    DEBUG(LOG_INFO, "sending NAK");

    return send_packet(&packet, 1, ifid);
}


#ifdef __SC_BUILD__
int sendACK(struct dhcpMessage *oldpacket, u_int32_t yiaddr, int ifid, struct pkt_extra_info *extra_info)
#else
int sendACK(struct dhcpMessage *oldpacket, u_int32_t yiaddr, int ifid)
#endif
{
    struct dhcpMessage packet;
    struct option_set *curr;

    struct in_addr addr;
    unsigned char *lease_time;
    char *buf, *s;
    u_int32_t lease_time_align = server_config[ifid].lease;
    FILE *fp, *timefp;
    //int vendor_len=0;
    int buf_len;
    unsigned char vendor_id[32]; // option 60
    long sys_time;
    struct in_addr client_addr;
    unsigned char client_mac[16] = "";
    unsigned char mac[18] = ""; 
    char line[256]; 
#ifdef __SC_BUILD__
    struct in_addr subnet_addr;
    struct in_addr gw_addr;
    struct in_addr dns_addr;
    char hostname[MAX_HOSTNAME_LEN]="";
    char lease_str[32]={0};
    char caddr_str[32]={0};
    char gwaddr_str[32]={0};
    char suaddr_str[32]={0};
    char dnsaddr_str[128]={0};
    char ack_date[32]={0};
    char ack_time[32]={0};
    struct tm *st;
    struct dhcp_ip_list_s *cur = NULL;

    subnet_addr.s_addr = server_config[ifid].netmask;
    gw_addr.s_addr = server_config[ifid].server;

    memcpy(client_mac, oldpacket->chaddr, 16);
    bzero(vendor_id, sizeof(vendor_id));
    get_vendor_id(oldpacket, vendor_id, 32);

    memcpy(&(client_addr.s_addr), &yiaddr, 4);

#endif

    unsigned char *req=NULL;
    u_int32_t req_align;
    if((req = get_option(oldpacket, DHCP_REQUESTED_IP)))
        memcpy(&req_align, req, 4);
#ifdef TR069
    unsigned char *vendor_spc=NULL;
    vendor_spc = get_option(oldpacket, DHCP_VENDOR_SPEC);
#endif
    init_packet(&packet, oldpacket, DHCPACK, ifid);
    packet.yiaddr = yiaddr;

    if ((lease_time = get_option(oldpacket, DHCP_LEASE_TIME))) {
        memcpy(&lease_time_align, lease_time, 4);
        lease_time_align = ntohl(lease_time_align);
        if (lease_time_align > server_config[ifid].lease)
            lease_time_align = server_config[ifid].lease;
        else if (lease_time_align < server_config[ifid].min_lease)
            lease_time_align = server_config[ifid].lease;
    }

#ifdef __SC_BUILD__
    if(extra_info && extra_info->dscp == 0x18)
        lease_time_align = UINT_MAX;
#if defined(DT_SMART_SETUP)
    if(check_dfnd_device(oldpacket))
        lease_time_align = 360 * 24 * 3600;
#endif
#endif
    add_simple_option(packet.options, DHCP_LEASE_TIME, htonl(lease_time_align));

    curr = server_config[ifid].options;
    while (curr) {
        if (curr->data[OPT_CODE] != DHCP_LEASE_TIME && curr->data[OPT_CODE] != DHCP_VENDOR)
        {
            if (curr->data[OPT_CODE] == DHCP_DNS_SERVER)
            {
                ADD_DNS_OPTIONS();
            }
            else
                add_option_string(packet.options, curr->data);
        }
        curr = curr->next;
    }

#ifdef TR069
    if(vendor_spc){
        add_vendor_options(&packet, ifid);
    }
#endif

    add_bootp_options(&packet, ifid);

    addr.s_addr = packet.yiaddr;

#ifndef __SC_BUILD__
    LOG(LOG_INFO, "sending ACK to %s", inet_ntoa(addr));
#endif
    if (send_packet(&packet, 0, ifid) < 0)
        return -1;
    sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",
            client_mac[0], client_mac[1], client_mac[2],
            client_mac[3], client_mac[4], client_mac[5]);
    if( (fp=fopen(VENDOR_FILE, "a+"))!=NULL )
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
                if(s == NULL)
                {
                    strcat(buf, line);
                }
            }
            fclose(fp);
#if 0
            if((timefp = fopen("/proc/uptime","r")) != NULL)
            {
                char uptime[10];
                fscanf(timefp,"%s ", uptime);
                fclose(timefp);
                sys_time = atol(uptime);
            }
            else
#endif
                sys_time = time(0);
            if( (fp=fopen(VENDOR_FILE, "w"))!=NULL )
            {
                fprintf(fp, "%s", buf);
                fprintf(fp, "%s;%s;%s;%d;%d;\n",
                        vendor_id,
                        inet_ntoa(client_addr),
                        mac,
                        lease_time_align, sys_time);
                fclose(fp);
            }
            free(buf);
        }
        else
        {
            fclose(fp);
        }

    }
#ifdef __SC_BUILD__
    {
        char *tmp=get_option(oldpacket,DHCP_HOST_NAME);
        int len=0;
        if(tmp)
        {
            len=*(tmp-1);

            if(len > sizeof(hostname) - 1)
                len = sizeof(hostname) - 1;

            strncpy(hostname,tmp,len);
            hostname[len] = '\0';
        }
    }

    add_lease(packet.chaddr, packet.yiaddr, lease_time_align, ifid, hostname);
    //write_leases(ifid);
    sprintf(lease_str, "%d",lease_time_align);
    strcpy(caddr_str, inet_ntoa(client_addr));
    strcpy(gwaddr_str,inet_ntoa(gw_addr));
    strcpy(suaddr_str,inet_ntoa(subnet_addr));

    cur = server_config[ifid].dns_server;
    while(cur)
    {
        dns_addr.s_addr = cur->ip;
        sprintf(dnsaddr_str,"%s%s;",dnsaddr_str,inet_ntoa(dns_addr));
        cur = cur->next;
    }

    st = localtime(&sys_time);
    sprintf(ack_date,"%02d.%02d.%02d",st->tm_mday,st->tm_mon+1,st->tm_year+1900);
    sprintf(ack_time,"%02d:%02d:%02d",st->tm_hour,st->tm_min,st->tm_sec);

    /*
     * RFC 2131 specify requested-ip must include in INIT-REBOOT/SELECT and
     * must not include in RENEWING/REBINDING. So we use req to decided whether
     * the sending ACK is for renew.
     *
     * Record LOG in init-reboot and select only.
     */
    if(req) {
        char *unicode_p=NULL;
        ibmpc_to_utf8(hostname,strlen(hostname),&unicode_p);
        syslog(LOG_INFO, "%s"LOG_ERRCODE_H001, log_type_db[GENERAL_LOG],ack_date,ack_time,scWlanMacExit(mac)== 1 ? "WLAN":"LAN",unicode_p,mac,caddr_str,suaddr_str,dnsaddr_str,gwaddr_str,lease_str);
        free(unicode_p);
    }
#else
    add_lease(packet.chaddr, packet.yiaddr, lease_time_align, ifid);
#endif
    write_leases(ifid);

#ifdef __SC_BUILD__
    do {
        int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
        if(fd == -1)
            break;

        struct sockaddr_un addr;
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path, SNBD_CMD_SOCKET_PATH);

        struct snbd_cmd_dhcpv4 cmd;
        memset(&cmd, 0, sizeof(cmd));
        SNBD_CMD(&cmd)->type = SNBD_CMD_TYPE_DHCPV4;
        cmd.dhcp_cmd = SNBD_CMD_DHCPV4_NEW;
        strncpy(SNBD_CMD_DHCPV4(&cmd)->name, hostname, SNBD_HOST_NAME_LEN);
        memcpy(SNBD_CMD_DHCPV4(&cmd)->l2addr, client_mac, ETH_ALEN);
        SNBD_CMD_DHCPV4(&cmd)->l3addr.ndm_family = AF_INET;
        memcpy(SNBD_CMD_DHCPV4(&cmd)->l3addr.l3addr, &yiaddr, SNBD_L3ADDR_IP4_LEN);
        cmd.lease_time = lease_time_align;

        uint8_t *option60_p = get_option(oldpacket, 60);
        if(option60_p)
            memcpy(cmd.options[cmd.option_nr++], option60_p-2, *(option60_p-1) + 2);

        uint8_t *option61_p = get_option(oldpacket, 61);
        if(option61_p)
            memcpy(cmd.options[cmd.option_nr++], option61_p-2, *(option61_p-1) + 2);

        /* send option 125  add by adley*/
        uint8_t *option125_p = get_option(oldpacket, DHCP_VENDOR_SPEC);
        if(option125_p)
            memcpy(cmd.options[cmd.option_nr++], option125_p-2, *(option125_p-1) + 2);

        sendto(fd, &cmd, sizeof(cmd), 0, (struct sockaddr *)&addr, sizeof(addr));

        close(fd);

    } while(0);
#endif

    return 0;
}


int send_inform(struct dhcpMessage *oldpacket, int ifid)
{
    struct dhcpMessage packet;
    struct option_set *curr;

    init_packet(&packet, oldpacket, DHCPACK, ifid);

    curr = server_config[ifid].options;
    while (curr) {
        if (curr->data[OPT_CODE] != DHCP_LEASE_TIME)
        {
            if (curr->data[OPT_CODE] == DHCP_DNS_SERVER)
            {
                ADD_DNS_OPTIONS();
            }
            else
                add_option_string(packet.options, curr->data);
        }
        curr = curr->next;
    }

    add_bootp_options(&packet, ifid);

    return send_packet(&packet, 0, ifid);
}



