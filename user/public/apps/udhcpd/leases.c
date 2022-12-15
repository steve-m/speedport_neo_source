/*
 * leases.c -- tools to manage DHCP leases
 * Russ Dill <Russ.Dill@asu.edu> July 2001
 */

#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "debug.h"
#include "dhcpd.h"
#include "files.h"
#include "options.h"
#include "leases.h"
#include "arpping.h"
#ifdef __SC_BUILD__
#include "static_leases.h"
#endif
unsigned char blank_chaddr[] = {[0 ... 15] = 0};
#ifdef __SC_BUILD__
static	time_t time_bef_NTP=0;/* record the old time,use for currect time after ntp get new time */
#endif
/* clear every lease out that chaddr OR yiaddr matches and is nonzero */
#ifdef __SC_BUILD__
void clear_lease(u_int8_t *chaddr, u_int32_t yiaddr, int ifid)
#else
void clear_lease(u_int8_t *chaddr, u_int32_t yiaddr)
#endif
{
	unsigned int i, j;
	for (j = 0; j < 16 && !chaddr[j]; j++);
#ifdef __SC_BUILD__	
	for (i = 0; i < server_config[ifid].max_leases; i++)
#else
	for (i = 0; i < server_config.max_leases; i++)
#endif
		if ((j != 16 && !memcmp(leases[ifid][i].chaddr, chaddr, 16)) ||
		    (yiaddr && leases[ifid][i].yiaddr == yiaddr)) {
			memset(&(leases[ifid][i]), 0, sizeof(struct dhcpOfferedAddr));
		}
}

#ifdef __SC_BUILD__
/* add a lease into the table, clearing out any old ones */
struct dhcpOfferedAddr *add_lease(u_int8_t *chaddr, u_int32_t yiaddr, unsigned long lease, int ifid,char *hostname)
#else
struct dhcpOfferedAddr *add_lease(u_int8_t *chaddr, u_int32_t yiaddr, unsigned long lease, int ifid)
#endif
{
	struct dhcpOfferedAddr *oldest;
	/* clean out any old ones */
#ifdef __SC_BUILD__
	clear_lease(chaddr, yiaddr, ifid);

	oldest = oldest_expired_lease(ifid);
#else
	clear_lease(chaddr, yiaddr);
		
	oldest = oldest_expired_lease();
#endif
	if (oldest) {
		memcpy(oldest->chaddr, chaddr, 16);
		oldest->yiaddr = yiaddr;
		oldest->expires = time(0) + lease;
#ifdef __SC_BUILD__
                if(lease == UINT_MAX)
                    oldest->expires = UINT_MAX;
                memcpy(oldest->hostname,hostname, sizeof(oldest->hostname) - 1);
                oldest->hostname[sizeof(oldest->hostname) - 1] = '\0';
#endif
	}

	return oldest;
}


/* true if a lease has expired */

int lease_expired(struct dhcpOfferedAddr *lease)
{
#ifdef __SC_BUILD__
	/* -- Jeff Sun -- Apr.23.2005 -- Modify for update expire time after ntp get correct time */
    time_t now = time(0);
    int c;
    unsigned int i;
    
    /* init time_bef_NTP */
    if(time_bef_NTP==0) time_bef_NTP=now;

    /* ntp get new time,orig time is in year 2000,new time is after 2005.01.01, do update */
    if( now - time_bef_NTP > ((2005-2000)*365*24*60*60) )
    {
    	for (c = 0; c < no_of_ifaces; c++)
		{
			if (server_config[c].active == FALSE)
					continue;
            
        	for (i = 0; i < server_config[c].max_leases; i++)
        		if (leases[c][i].yiaddr != 0 && server_config[c].remaining)
       				leases[c][i].expires += (now-time_bef_NTP);
	    }    
    }
    time_bef_NTP=now;
    
	return (lease->expires < (unsigned long) now);
#else
	return (lease->expires < (unsigned long) time(0));
#endif
}	


/* Find the oldest expired lease, NULL if there are no expired leases */
#ifdef __SC_BUILD__
struct dhcpOfferedAddr *oldest_expired_lease(int ifid)
#else
struct dhcpOfferedAddr *oldest_expired_lease(void)
#endif
{
	struct dhcpOfferedAddr *oldest = NULL;
	unsigned long oldest_lease = time(0);
	unsigned int i;

#ifdef __SC_BUILD__	
	for (i = 0; i < server_config[ifid].max_leases; i++)
#else
	for (i = 0; i < server_config.max_leases; i++)
#endif
		if (oldest_lease > leases[ifid][i].expires) {
			oldest_lease = leases[ifid][i].expires;
			oldest = &(leases[ifid][i]);
		}
	return oldest;
		
}


/* Find the first lease that matches chaddr, NULL if no match */
#ifdef __SC_BUILD__
struct dhcpOfferedAddr *find_lease_by_chaddr(u_int8_t *chaddr, int ifid)
#else
struct dhcpOfferedAddr *find_lease_by_chaddr(u_int8_t *chaddr)
#endif
{
	unsigned int i;
#ifdef __SC_BUILD__
	for (i = 0; i < server_config[ifid].max_leases; i++)
#else
	for (i = 0; i < server_config.max_leases; i++)
#endif
		if (!memcmp(leases[ifid][i].chaddr, chaddr, 16)) return &(leases[ifid][i]);
	
	return NULL;
}


/* Find the first lease that matches yiaddr, NULL is no match */
#ifdef __SC_BUILD__
struct dhcpOfferedAddr *find_lease_by_yiaddr(u_int32_t yiaddr, int ifid)
#else
struct dhcpOfferedAddr *find_lease_by_yiaddr(u_int32_t yiaddr)
#endif
{
	unsigned int i;
#ifdef __SC_BUILD__
	for (i = 0; i < server_config[ifid].max_leases; i++)
#else
	for (i = 0; i < server_config.max_leases; i++)
#endif
		if (leases[ifid][i].yiaddr == yiaddr) return &(leases[ifid][i]);
	
	return NULL;
}


/* find an assignable address, it check_expired is true, we check all the expired leases as well.
 * Maybe this should try expired leases by age... */
#ifdef __SC_BUILD__
u_int32_t find_address(int check_expired, int ifid)
#else
u_int32_t find_address(int check_expired) 
#endif
{
	u_int32_t addr, ret;
	struct dhcpOfferedAddr *lease = NULL;
#ifdef __SC_BUILD__
	addr = ntohl(server_config[ifid].start); /* addr is in host order here */
	for (;addr <= ntohl(server_config[ifid].end); addr++) {
#else
	addr = ntohl(server_config.start); /* addr is in host order here */
	for (;addr <= ntohl(server_config.end); addr++) {
#endif
		/* ie, 192.168.55.0 */
		if (!(addr & 0xFF)) continue;

		/* ie, 192.168.55.255 */
		if ((addr & 0xFF) == 0xFF) continue;


	  
#ifdef __SC_BUILD__
		if (addr == ntohl(server_config[ifid].server)) 
			continue;
		 /* only do if it is not a static lease address */
	    if (!reservedIp(server_config[ifid].static_leases,htonl(addr)))
	    {

            /* lease is not taken */
            ret = htonl(addr);

            if ((!(lease = find_lease_by_yiaddr(ret, ifid)) ||
                 /* or it expired and we are checking for expired leases */
                 (check_expired  && lease_expired(lease))) &&

                 /* and it isn't on the network */
            #ifdef __SC_ARP__
                    !check_ip(ret, ifid, NULL))
            #else
            	     !check_ip(ret, ifid))
            #endif
            {
            	return ret;
            	break;
            }

	    }
#else
	/* lease is not taken */
		ret = htonl(addr);
		if ((!(lease = find_lease_by_yiaddr(ret)) ||

		     /* or it expired and we are checking for expired leases */
		     (check_expired  && lease_expired(lease))) &&

		     /* and it isn't on the network */
	    	     !check_ip(ret)) {
			return ret;
			break;
		}
#endif
	}
	return 0;
}

/* check is an IP is taken, if it is, add it to the lease table */
#ifdef __SC_BUILD__
#ifdef __SC_ARP__
int check_ip(u_int32_t addr, int ifid, u_int8_t *chaddr)
#else
int check_ip(u_int32_t addr, int ifid)
#endif
#else
int check_ip(u_int32_t addr)
#endif
{
	struct in_addr temp;
#ifdef __SC_BUILD__
	char hostname[MAX_HOSTNAME_LEN]="";
#ifdef __SC_ARP__
    if (arpping(addr, server_config[ifid].server, server_config[ifid].arp, chaddr, DHCPD_LAN_IFNAME) == 0) {
#else
	if (arpping(addr, server_config[ifid].server, server_config[ifid].arp, DHCPD_LAN_IFNAME) == 0) {
#endif
		temp.s_addr = addr;
	 	LOG(LOG_INFO, "%s belongs to someone, reserving it for %ld seconds",
	 		inet_ntoa(temp), server_config[ifid].conflict_time);
/* Do not update client table even if we can discover them.
 * The discovered one may be fixed IP, we needn't them in the table.
 * If you want to add these, please make other related part work smart.
 * Known bug with this:
    When DHCPD restarted, one client can not get it's original IP address, it will get another one, the original one will NOT be used by anyone but only the client table.
 */

		//add_lease(blank_chaddr, addr, server_config[ifid].conflict_time, ifid,hostname);
#else
	if (arpping(addr, server_config.server, server_config.arp, server_config.interface) == 0) {
		temp.s_addr = addr;
	 	LOG(LOG_INFO, "%s belongs to someone, reserving it for %ld seconds", 
	 		inet_ntoa(temp), server_config.conflict_time);
	add_lease(blank_chaddr, addr, server_config[ifid].conflict_time, ifid);
#endif


		return 1;
	} else return 0;
}

