#ifndef _CFG_routing_H_
#define _CFG_routing_H_

int cal_routing_ipv4_forwarding_get(int router_id, int id, void **);
int cal_routing_ipv4_forwarding_set(int router_id, int id, void *);
int cal_routing_ipv4_forwarding_del(int router_id, int id);
int cal_routing_ipv4_entry_update(void);
int cal_routing_ipv6_forwarding_get(int router_id, int id, void **);
int cal_routing_ipv6_forwarding_set(int router_id, int id, void *);
int cal_routing_ipv6_forwarding_del(int router_id, int id);
int cal_routing_ipv6_entry_update(void);
/*to add here*/
#endif
