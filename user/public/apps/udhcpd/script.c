/* script.c
 *
 * Functions to call the DHCP client notification scripts 
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

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#ifdef __SC_BUILD__
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>
#include "log_api.h"
#include <sal/sal_wan.h>

#endif

#include "options.h"
#include "dhcpd.h"
#include "dhcpc.h"
#include "packet.h"
#include "options.h"
#include "debug.h"
#ifdef __SC_BUILD__
extern int scIpChanged ;
extern int scRouteChanged;
extern int scDnsChanged;
#define CAL_ENABLE      "1"
#define CAL_DISABLE      "0"
#endif
/* get a rough idea of how long an option will be (rounding up...) */
static int max_option_length[] = {
	[OPTION_IP] =		sizeof("255.255.255.255 "),
	[OPTION_IP_PAIR] =	sizeof("255.255.255.255 ") * 2,
	[OPTION_STRING] =	1,
	[OPTION_BOOLEAN] =	sizeof("yes "),
	[OPTION_U8] =		sizeof("255 "),
	[OPTION_U16] =		sizeof("65535 "),
	[OPTION_S16] =		sizeof("-32768 "),
	[OPTION_U32] =		sizeof("4294967295 "),
	[OPTION_S32] =		sizeof("-2147483684 "),
#ifdef __SC_BUILD__
	[OPTION_ROUTE] =	sizeof("255/255.255.255.255/255.255.255.255 "),
#endif
};

int myPipe(char *command, char **output);

static int upper_length(int length, struct dhcp_option *option)
{
	return max_option_length[option->flags & TYPE_MASK] *
	       (length / option_lengths[option->flags & TYPE_MASK]);
}


static int sprintip(char *dest, char *pre, unsigned char *ip) {
	return sprintf(dest, "%s%d.%d.%d.%d ", pre, ip[0], ip[1], ip[2], ip[3]);
}

/* Fill dest with the text of option 'option'. */
static void fill_options(char *dest, unsigned char *option, struct dhcp_option *type_p)
{
	int type, optlen;
	u_int16_t val_u16;
	int16_t val_s16;
	u_int32_t val_u32;
	int32_t val_s32;
	int len = option[OPT_LEN - 2];

	dest += sprintf(dest, "%s=", type_p->name);
    
	type = type_p->flags & TYPE_MASK;
	optlen = option_lengths[type];
	for(;;) {
		switch (type) {
		case OPTION_IP_PAIR:
			dest += sprintip(dest, "", option);
			*(dest++) = '/';
			option += 4;
			optlen = 4;
		case OPTION_IP:	/* Works regardless of host byte order. */

			dest += sprintip(dest, "", option);
 			break;
		case OPTION_BOOLEAN:
			dest += sprintf(dest, *option ? "yes " : "no ");
			break;
		case OPTION_U8:
			dest += sprintf(dest, "%u ", *option);
			break;
		case OPTION_U16:
			memcpy(&val_u16, option, 2);
			dest += sprintf(dest, "%u ", ntohs(val_u16));
			break;
		case OPTION_S16:
			memcpy(&val_s16, option, 2);
			dest += sprintf(dest, "%d ", ntohs(val_s16));
			break;
		case OPTION_U32:
			memcpy(&val_u32, option, 4);
			dest += sprintf(dest, "%lu ", (unsigned long) ntohl(val_u32));
			break;
		case OPTION_S32:
			memcpy(&val_s32, option, 4);
			dest += sprintf(dest, "%ld ", (long) ntohl(val_s32));
			break;
#ifdef __SC_BUILD__
		case OPTION_ROUTE:
			dest += sprintf(dest, "%u ", *option);
			*(dest++) = '/';
			dest += sprintip(dest, "", &option[1]);
			*(dest++) = '/';
			dest += sprintip(dest, "", &option[5]);
			break;
#endif
		case OPTION_STRING:
			memcpy(dest, option, len);
			dest[len] = '\0';
			return;	 /* Short circuit this case */
		}
		option += optlen;
		len -= optlen;
		if (len <= 0) break;
	}
}


static char *find_env(const char *prefix, char *defaultstr)
{
	extern char **environ;
	char **ptr;
	const int len = strlen(prefix);

	for (ptr = environ; *ptr != NULL; ptr++) {
		if (strncmp(prefix, *ptr, len) == 0)
			return *ptr;
	}
	return defaultstr;
}

/* put all the paramaters into an environment */
#ifdef __SC_BUILD__
#define ADDON_OPTIONS 10   // if you add options, increase this const
#endif
static char **fill_envp(struct dhcpMessage *packet)
{
	int num_options = 0;
	int i, j;
	char **envp;
	unsigned char *temp;
	char over = 0;
	
	if (packet == NULL)
		num_options = 0;
	else {
		for (i = 0; options[i].code; i++)
			if (get_option(packet, options[i].code))
				num_options++;
		if (packet->siaddr) num_options++;
		if ((temp = get_option(packet, DHCP_OPTION_OVER)))
			over = *temp;
		if (!(over & FILE_FIELD) && packet->file[0]) num_options++;
		if (!(over & SNAME_FIELD) && packet->sname[0]) num_options++;		
	}
#ifdef __SC_BUILD__	
	envp = malloc((num_options + ADDON_OPTIONS) * sizeof(char *));
#else
	envp = malloc((num_options + 5) * sizeof(char *));
#endif
	envp[0] = malloc(sizeof("interface=") + strlen(client_config.interface));
	sprintf(envp[0], "interface=%s", client_config.interface);
	envp[1] = find_env("PATH", "PATH=/bin:/usr/bin:/sbin:/usr/sbin");
	envp[2] = find_env("HOME", "HOME=/");
#ifdef __SC_BUILD__
	envp[3] = malloc(sizeof("wanid=") + sizeof(client_config.wanid));
	sprintf(envp[3], "wanid=%d", client_config.wanid); 
#endif
	if (packet == NULL) {
#ifdef __SC_BUILD__			
		envp[4] = NULL;
#else
		envp[3] = NULL;
#endif
		return envp;
	}
#ifdef __SC_BUILD__	
	envp[4] = malloc(sizeof("ip=255.255.255.255"));
	sprintip(envp[4], "ip=", (unsigned char *) &packet->yiaddr);
#else
	envp[3] = malloc(sizeof("ip=255.255.255.255"));
	sprintip(envp[3], "ip=", (unsigned char *) &packet->yiaddr);
#endif	
#ifdef __SC_BUILD__	
	for (i = 0, j = 5; options[i].code; i++) {
#else
	for (i = 0, j = 4; options[i].code; i++) {
#endif
		if ((temp = get_option(packet, options[i].code))) {
			envp[j] = malloc(upper_length(temp[OPT_LEN - 2], &options[i]) + strlen(options[i].name) + 2);
			fill_options(envp[j], temp, &options[i]);
			j++;
		}
	}
	if (packet->siaddr) {
		envp[j] = malloc(sizeof("siaddr=255.255.255.255"));
		sprintip(envp[j++], "siaddr=", (unsigned char *) &packet->siaddr);
	}
	if (!(over & FILE_FIELD) && packet->file[0]) {
		/* watch out for invalid packets */
		packet->file[sizeof(packet->file) - 1] = '\0';
		envp[j] = malloc(sizeof("boot_file=") + strlen(packet->file));
		sprintf(envp[j++], "boot_file=%s", packet->file);
	}
	if (!(over & SNAME_FIELD) && packet->sname[0]) {
		/* watch out for invalid packets */
		packet->sname[sizeof(packet->sname) - 1] = '\0';
		envp[j] = malloc(sizeof("sname=") + strlen(packet->sname));
		sprintf(envp[j++], "sname=%s", packet->sname);
	}
#ifdef __SC_BUILD__		
    if (scIpChanged)
    {
        envp[j] = malloc(sizeof("IpChanged=1"));
		sprintf(envp[j++], "IpChanged=1");
    }
    if (scRouteChanged)
    {
        envp[j] = malloc(sizeof("RouteChanged=1"));
		sprintf(envp[j++], "RouteChanged=1");
    }
    if (scDnsChanged)
    {
        envp[j] = malloc(sizeof("DnsChanged=1"));
		sprintf(envp[j++], "DnsChanged=1");
    }

	envp[j++] = find_env("SERVER", "SERVER=");
#endif
	envp[j] = NULL;
	return envp;
}

#ifdef __SC_BUILD__
int get_sockfd(void)
{

	 int sockfd = -1;
	
		//if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == -1)
		if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		{
			perror("user: socket creating failed");
			return (-1);
		}
	return sockfd;
}
#endif
#ifdef __SC_BUILD__
/* routing table */
typedef struct route_table_s{
	char dest[16];
	char gateway[16];
	char mask[16];
	int metric;
	char active[4];
	char interface[8];
	struct route_table_s *next;
} route_table_t;

#define BUFSZ PIPE_BUF
#define DHCPC_ROUTE_RELATED_OPTIONS_DEL	"/tmp/dhcpc_route_related_options_del"
#define ONE_OPTION_MAX_LEN 255
#define DHCP_LONG_OPTION 255
int route_count=0;       /* How many routes we have got in option 33 and 121 */
/*

Return value:
        0: ok
        -1: error
*/
int myPipe(char *command, char **output)
{
    FILE *fp;
    char buf[BUFSZ];
    int len;

    *output=malloc(1);
    strcpy(*output, "");
    if((fp=popen(command, "r"))==NULL)
        return -1;
    while((fgets(buf, BUFSZ, fp)) != NULL){
        len=strlen(*output)+strlen(buf);
        if((*output=realloc(*output, (sizeof(char) * (len+1))))==NULL)
        {
            pclose(fp);
            return -1;
        }
        strcat(*output, buf);
    }
    pclose(fp);
    return 0;
}

int do_route(route_table_t **route)
{
    char *output = NULL;
    char *pt = NULL;

    myPipe("/sbin/route -n",&output);
    pt=strstr(output,"Iface");

    if(!pt){
        *route=NULL;
    }else{
        char tmp[16];
        int len=strlen(output);

        route_table_t *now = NULL, *pre = NULL;

        while(*(pt++)!='\n');

        *route=malloc(sizeof(route_table_t));

        for(now=*route;(pt-output)<len;now=now->next){
            pre=now;
            sscanf(pt,"%s %s %s %s %d %s %s %s"
                   ,now->dest
                   ,now->gateway
                   ,now->mask
                   ,tmp
                   ,&now->metric
                   ,tmp
                   ,now->active
                   ,now->interface);
            while(*(pt++)!='\n');
            now->next=malloc(sizeof(route_table_t));
        }

        (now==*route)?(*route=NULL):(pre->next=NULL);
        free(now);
    }

    free(output);
    return 0;
}

int check_route_exist(char *dest, char *gw, char *mask, int metric, int invert)
{
    int ret = 0;
    route_table_t *now,*route_table,new_route;

    memset(&new_route, 0, sizeof(new_route));
    sprintf(new_route.dest, "%s", dest);
    sprintf(new_route.gateway, "%s", gw);
    sprintf(new_route.mask, "%s", mask);
    new_route.metric = metric;

    do_route(&route_table);

    for(now=route_table;now;now=now->next)
    {
        if(strcmp(new_route.dest, now->dest) == 0
           && strcmp(new_route.gateway, now->gateway) == 0
           && strcmp(new_route.mask, now->mask) == 0
           && (invert?(metric != now->metric):(metric == now->metric)))
        {
            ret = 1;
            break;
        }
    }
    /*free route_table*/
    while((now=route_table)!=NULL)
    {
        route_table=route_table->next;
        free(now);
    }
    return ret;
}

static uint32_t lan_netaddress(void)
{
    struct in_addr dest;
    struct in_addr netmask;
    if_info_t if_info;
    char *if_name = "br0";
    
    /* get lan ip and netmask */
    getIFInfo(if_name, &if_info);
    inet_pton(AF_INET, if_info.ipaddr, &dest);
    inet_pton(AF_INET, if_info.mask, &netmask);

    return (dest.s_addr & netmask.s_addr);

}

/*
    RFC3442
    if the DHCP server returns both a Classless Static Routes option and a Static Routes
    option, the DHCP client MUST ignore the Static Routes option.

    Code Len Destination 1    Router 1
    +-----+---+----+-----+----+----+----+----+----+
    | 121 | n | d1 | ... | dN | r1 | r2 | r3 | r4 |
    +-----+---+----+-----+----+----+----+----+----+
    Destination 2       Router 2
    +----+-----+----+----+----+----+----+
    | d1 | ... | dN | r1 | r2 | r3 | r4 |
    +----+-----+----+----+----+----+----+

    return
        0 received Classless Static Routes
 */
int sc_option121(struct dhcpMessage *packet)
{
    unsigned char *temp_op;
    unsigned char *temp;
    int len = 0;
    int mask_bitn, dest_n;
    struct in_addr dest;
    struct in_addr netmask;
    struct in_addr gw;
    int i;
    char cmdbuf[256], dest_buf[64], netmask_buf[64], gw_buf[64];
    unsigned char long_op_buf[512];
    int	long_option_len;
    uint32_t lan_netip;
   
    if (packet == NULL)
        return -1;

    if ((temp_op = get_option(packet, DHCP_CLASSLESS_ROUTE)) != NULL)
    {
    	/*If one option lenght > 255,server will separate the overflow bytes
    	  to another option 250.Luckly,we just need handle option 32 here.Pay
    	  attention when you add a option support if it may larger than 255 bytes
    	  For ex.option 32 len 256 separate to opt 32 with len 255 and opt 250 with
    	  len 1 */
    	//SC_CFPRINTF("got option 121\n");
    	if(temp_op[OPT_LEN -2] == ONE_OPTION_MAX_LEN)/*len is 255*/
    	{
    		//SC_CFPRINTF("option 121 is over flow\n");
    		if(temp_op[ONE_OPTION_MAX_LEN] == DHCP_LONG_OPTION)/*next is option 250*/
    		{
    			long_option_len = temp_op[ONE_OPTION_MAX_LEN + OPT_LEN];
    			//SC_CFPRINTF("next is option 250 with length %d\n", long_option_len);
    			/*merge opt 121 and opt 250 following to one buf*/
    			memcpy(long_op_buf, temp_op, ONE_OPTION_MAX_LEN);
    			memcpy(long_op_buf + ONE_OPTION_MAX_LEN, temp_op + ONE_OPTION_MAX_LEN
    								+ OPT_LEN + 1, long_option_len);
    			len = ONE_OPTION_MAX_LEN + long_option_len;
    			temp = long_op_buf;
    		}
    		else
    		{
    			//SC_CFPRINTF("impossible,next is not option 250,but option 32 is > 255\n");
    			return -1;
    		}
    	}
    	else
    	{
        	len = temp_op[OPT_LEN -2];
        	temp = temp_op;
        	//SC_CFPRINTF("option 121 length = %d\n", len);
		}
    }
    else
    {
        return -1;
	}
    /* we should only add 32 routes, so when route_count >31, we should ignore. */	
    lan_netip = lan_netaddress();
    /*
     * Delete old option 121 route added
     */
    {
        snprintf(cmdbuf, sizeof(cmdbuf), "sh %s; fc flush", DHCPC_ROUTE_RELATED_OPTIONS_DEL);
        system(cmdbuf);
    }
    unlink(DHCPC_ROUTE_RELATED_OPTIONS_DEL);
    while(len > 0 && route_count < 32){
        route_count++;
        mask_bitn = *(temp++);
        /* The net mask must not greater than 32 */
        /* destination net and netmask */
        if(mask_bitn > 32)
            break;
        dest_n = mask_bitn / 8;
        if (mask_bitn % 8)
            dest_n++;

        if((len = len - (1 + dest_n + 4)) < 0)
            break;

        /* netmask.  default is 255.255.255.255 */
        netmask.s_addr=0xFFFFFFFF;
        for (i = 0; i < (32 - mask_bitn); i++){
            netmask.s_addr = netmask.s_addr << 1;
        }
        netmask.s_addr = htonl(netmask.s_addr);

        dest.s_addr = *((uint32_t *)temp);
        dest.s_addr = dest.s_addr & netmask.s_addr;
        temp += dest_n;

        /* route gateway */
        gw.s_addr = *((uint32_t *)temp);
        temp += 4;

        /* dest ip and lan net adress ip compare */
        if(dest.s_addr == lan_netip)
            continue;

        /* add route, metric = ? */
        sprintf(dest_buf, "%s", inet_ntoa(dest));
        sprintf(netmask_buf, "%s", inet_ntoa(netmask));
        sprintf(gw_buf, "%s", inet_ntoa(gw));

        if(!check_route_exist(dest_buf, gw_buf, netmask_buf, 0, 1))
        {
            /* back up for del */
            sprintf(cmdbuf, "/bin/echo '/sbin/route del -net %s netmask %s gw %s' >> %s",
                    dest_buf, netmask_buf, gw_buf, DHCPC_ROUTE_RELATED_OPTIONS_DEL);
            system(cmdbuf);

            /* addd route */
            sprintf(cmdbuf, "/sbin/route add -net %s netmask %s gw %s\n",
                    dest_buf, netmask_buf, gw_buf);
            system(cmdbuf);
        }
    }

    system("fc flush");

    return 0;
}

/*
* 1) Check ip/gateway/dns changed or not
* 2) record the connection info
*/
static void
sc_ipGetHandler(struct dhcpMessage *packet)
{
	unsigned char *pStr;
	unsigned long ipLong;
	int wanid = client_config.wanid;
	int i;
	int lease;
	char str_lease[32];
	int wan_down;
	WAN_CP_INFO_t cp_info;
	WAN_CP_INFO_t cp_info_n;

	scIpChanged = scRouteChanged = scDnsChanged = 0;
	memset(&cp_info_n, 0, sizeof(cp_info_n));

	sal_wan_load_cp_info(wanid, &cp_info);

	if(cp_info.state && strcmp(cp_info.state, CAL_ENABLE) == 0)
		wan_down = 0;
	else
		wan_down = 1;
	/*
	* Check If IP changed
	*/
	cp_info_n.ip.s_addr = packet->yiaddr;
    if(wan_down || cp_info_n.ip.s_addr != cp_info.ip.s_addr)
    {
        scIpChanged = 1;
//        syslog(LOG_INFO, "%s WAN %d is up, IP is %s.", log_type_db[WAN_LOG], wanid, inet_ntoa(cp_info_n.ip));
    }

    /*
	* Check If IP subnet changed
	*/
	if ((pStr = get_option(packet, DHCP_SUBNET)) != NULL)
	{
		memcpy(&ipLong, pStr, 4);
		cp_info_n.ipmask.s_addr=ipLong;
    }else{
    	cp_info_n.ipmask.s_addr=0;
    }
	if(wan_down || cp_info_n.ipmask.s_addr != cp_info.ipmask.s_addr)
	{
	    scIpChanged = 1;
	    scRouteChanged = 1;
	}

	/*
	* Check If Gateway changed
	*/
	if ((pStr = get_option(packet, DHCP_ROUTER)) != NULL) {
		memcpy(&ipLong, pStr, 4);
		cp_info_n.gw.s_addr=ipLong;
	}else{
		cp_info_n.gw.s_addr=0;
    }
    if(wan_down || cp_info_n.gw.s_addr != cp_info.gw.s_addr)
	{
	    scRouteChanged = 1;

	}

    /*
	* Check If DNS changed
	*/
	if ((pStr = get_option(packet, DHCP_DNS_SERVER)) != NULL) {
		memcpy(&ipLong, pStr, 4);
		cp_info_n.dns1.s_addr=ipLong;

		if(*(pStr - 1) >= 8)
		{
    	    memcpy(&ipLong, pStr+4, 4);
    	    cp_info_n.dns2.s_addr=ipLong;
    	}else{
    		cp_info_n.dns2.s_addr=0;
    	}

	}else{
		cp_info_n.dns2.s_addr = cp_info_n.dns1.s_addr = 0;
    }
	if(cp_info_n.dns2.s_addr != cp_info.dns2.s_addr || cp_info_n.dns1.s_addr != cp_info.dns1.s_addr)
	{
	    scDnsChanged = 1;

	}
	if (!(pStr = get_option(packet, DHCP_LEASE_TIME))) {
		sprintf(str_lease, "%d", 60 * 60);
	} else {
		memcpy(&(lease), pStr, 4);
		lease = ntohl(lease);
		sprintf(str_lease, "%d", lease);
	}
	cp_info_n.lease_time = str_lease;
	if(is_option_required(DHCP_VENDOR_INFO))
	{
	    if ((pStr = get_option(packet, DHCP_VENDOR_INFO)) != NULL) {
    		cp_info_n.opt43 = pStr;
//                syslog(LOG_INFO, "%s Option 43 Received is %s from WAN %d.", log_type_db[WAN_LOG], pStr, wanid);
	    }
//	    else{
//		syslog(LOG_ERR, "%s No Option43 take out in DHCP ACK of WAN %d.", log_type_db[WAN_LOG], wanid);
//	    }
	}
	char uptime[256] = {0};
	FILE *fp;
  	fp = fopen("/proc/uptime", "r");
	if(fp)
	{
		fread(uptime, sizeof(uptime), 1, fp);
		uptime[strlen(uptime) -1] = '\0';//remove /r/n
		fclose(fp);
	}
	cp_info_n.uptime = uptime;
	cp_info_n.state = CAL_ENABLE;
	sal_wan_store_cp_info(wanid, &cp_info_n);

}
#endif
/* Call a script with a par file and env vars */
void run_script(struct dhcpMessage *packet, const char *name)
{
	int pid;
	char **envp;
    
	if (client_config.script == NULL)
        return;

#ifdef __SC_BUILD__
		if(name)
		{
			if((strcmp(name, "renew") == 0)
					|| (strcmp(name, "bound") == 0))
			{
				sc_ipGetHandler(packet);
			}
			else if(strcmp(name, "deconfig") == 0)
			{
				if(0 == strcmp(sal_wan_get_con_state_t(client_config.wanid), CAL_ENABLE))
				{
					sal_wan_set_con_state_t(client_config.wanid, CAL_DISABLE);
					sal_wan_set_con_uptime_t(client_config.wanid, "");
				}
			}
		}
#endif
	/* call script */
	pid = fork();
	if (pid) {
		waitpid(pid, NULL, 0);
		return;
	} else if (pid == 0) {
		envp = fill_envp(packet);

		/* close fd's? */
		/* exec script */
		DEBUG(LOG_INFO, "execle'ing %s", client_config.script);
		execle(client_config.script, client_config.script,
		       name, NULL, envp);
		LOG(LOG_ERR, "script %s failed: errno %d",
		    client_config.script, errno);
		exit(1);
	}			
}
