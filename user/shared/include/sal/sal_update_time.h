#ifndef __SAL_UPDATE_TIME_H__
#define __SAL_UPDATE_TIME_H__

char *sal_update_time_get_process_status(void);
int sal_update_time_set_process_status(char *value);
char *sal_update_time_get_dns_relay_forwarding(void);
int sal_update_time_set_dns_relay_forwarding(char *value);
char *sal_update_time_get_dns_client_server(void);
int sal_update_time_set_dns_client_server(char *value);
char *sal_update_time_get_routing_forwarding(void);
int sal_update_time_set_routing_forwarding(char *value);
char *sal_update_time_get_dhcpv4_server_client(void);
int sal_update_time_set_dhcpv4_server_client(char *value);
char *sal_update_time_get_dhcpv6_client_receivedoption(void);
int sal_update_time_set_dhcpv6_client_receivedoption(char *value);
char *sal_update_time_get_dhcpv6_server_pool_client(void);
int sal_update_time_set_dhcpv6_server_pool_client(char *value);
char *sal_update_time_get_usb_port(void);
int sal_update_time_set_usb_port(char *value);
char *sal_update_time_get_usb_host_info(void);
int sal_update_time_set_usb_host_info(char *value);
char *sal_update_time_get_lan_hosts_info(void);
int sal_update_time_set_lan_hosts_info(char *value);
char *sal_update_time_get_mgnt_dev_status(void);
int sal_update_time_set_mgnt_dev_status(char *value);
char *sal_update_time_get_mgnt_dev_num(void);
int sal_update_time_set_mgnt_dev_num(char *value);
char *sal_update_time_get_accesspoint1_sta_status(void);
int sal_update_time_set_accesspoint1_sta_status(char *value);
char *sal_update_time_get_accesspoint2_sta_status(void);
int sal_update_time_set_accesspoint2_sta_status(char *value);
char *sal_update_time_get_accesspoint3_sta_status(void);
int sal_update_time_set_accesspoint3_sta_status(char *value);
char *sal_update_time_get_accesspoint4_sta_status(void);
int sal_update_time_set_accesspoint4_sta_status(char *value);
#ifdef _SC_HOMEPLUG_
char *sal_update_time_get_homeplug_assocdevs(void);
int sal_update_time_set_homeplug_assocdevs(char *value);
#endif
#endif//__SAL_UPDATE_TIME_H__

