/* leases.h */
#ifndef _LEASES_H
#define _LEASES_H

#ifdef __SC_BUILD__
#include "packet.h"
#define MAX_HOSTNAME_LEN 40
#endif
struct dhcpOfferedAddr {
	u_int8_t chaddr[16];
	u_int32_t yiaddr;	/* network order */
	u_int32_t expires;	/* host order */
	
#ifdef __SC_BUILD__
	u_int8_t hostname[MAX_HOSTNAME_LEN];
#endif
};

extern unsigned char blank_chaddr[];


#ifdef __SC_BUILD__
void clear_lease(u_int8_t *chaddr, u_int32_t yiaddr, int ifid);
struct dhcpOfferedAddr *add_lease(u_int8_t *chaddr, u_int32_t yiaddr, unsigned long lease, int ifid,char *hostname);
#else
void clear_lease(u_int8_t *chaddr, u_int32_t yiaddr);
struct dhcpOfferedAddr *add_lease(u_int8_t *chaddr, u_int32_t yiaddr, unsigned long lease, int ifid);
#endif
int lease_expired(struct dhcpOfferedAddr *lease);
#ifdef __SC_BUILD__
struct dhcpOfferedAddr *oldest_expired_lease(int ifid);
struct dhcpOfferedAddr *find_lease_by_chaddr(u_int8_t *chaddr, int ifid);
struct dhcpOfferedAddr *find_lease_by_yiaddr(u_int32_t yiaddr, int ifid);
u_int32_t find_address(int check_expired, int ifid);
#ifdef __SC_ARP__
int check_ip(u_int32_t addr, int ifid, u_int8_t *chaddr);
#else
int check_ip(u_int32_t addr, int ifid);
#endif
#else
struct dhcpOfferedAddr *oldest_expired_lease(void);
struct dhcpOfferedAddr *find_lease_by_chaddr(u_int8_t *chaddr);
struct dhcpOfferedAddr *find_lease_by_yiaddr(u_int32_t yiaddr);
u_int32_t find_address(int check_expired);
int check_ip(u_int32_t addr);
#endif

#endif
