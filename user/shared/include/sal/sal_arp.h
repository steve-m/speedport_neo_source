#ifndef _SAL_ARP_H_
#define _SAL_ARP_H_

typedef struct 
{
	char ip[32];
	int type;
	int flags;
	char hwa[32];
	char mask[16];
	char dev[32];	
}sal_arp;

#define SAL_ARP_MAX_ENTRY 64

/* not need to free the memory, because it's static */
int sal_arp_get_arp_entry(sal_arp ** arp_info);

#endif
