#ifndef __SAL_IPV6_H__
#define __SAL_IPV6_H__

char *sal_ipv6_get_wan_global_addr(void);
int sal_ipv6_set_wan_global_addr(char *value);

char *sal_ipv6_get_wan_linklocal_addr(void);
int sal_ipv6_set_wan_linklocal_addr(char *value);

char *sal_ipv6_get_lan_global_addr(void);
int sal_ipv6_set_lan_global_addr(char *value);

char *sal_ipv6_get_lan_linklocal_addr(void);
int sal_ipv6_set_lan_linklocal_addr(char *value);

char *sal_ipv6_get_basic_privacy(void);
int sal_ipv6_set_basic_privacy(char *value);

char *sal_ipv6_get_ra_defaultlftime(void);
int sal_ipv6_set_ra_defaultlftime(char *value);

char *sal_ipv6_get_ra_routeinfo(void);
int sal_ipv6_set_ra_routeinfo(char *value);

char *sal_ipv6_get_nd_wan_retranstimer(void);
int sal_ipv6_set_nd_wan_retranstimer(char *value);

char *sal_ipv6_get_lan_ra_mtu(void);
int sal_ipv6_set_lan_ra_mtu(char *value);
#endif//__SAL_IPV6_H__

