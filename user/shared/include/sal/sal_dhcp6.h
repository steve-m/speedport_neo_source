#ifndef __SAL_DHCP6_H__
#define __SAL_DHCP6_H__

char *sal_dhcp6_get_client_server_addr(void);
int sal_dhcp6_set_client_server_addr(char *value);

char *sal_dhcp6_get_client_server_duid(void);
int sal_dhcp6_set_client_server_duid(char *value);

char *sal_dhcp6_get_client_server_refresh_time(void);
int sal_dhcp6_set_client_server_refresh_time(char *value);

char *sal_dhcp6_get_client_suggested_t1(void);
int sal_dhcp6_set_client_suggested_t1(char *value);

char *sal_dhcp6_get_client_suggested_t2(void);
int sal_dhcp6_set_client_suggested_t2(char *value);

#endif//__SAL_DHCP6_H__

