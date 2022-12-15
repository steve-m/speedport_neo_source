#ifndef _CFG_ip_H_
#define _CFG_ip_H_

char* cal_ip_ulaprefix_get();
int cal_ip_ulaprefix_set(char* val);
char* cal_ip_enable_get(unsigned int id);
int cal_ip_enable_set(unsigned int id, char* val);
char* cal_ip_if_name_get(unsigned int id);
int cal_ip_if_name_set(unsigned int id, char* val);
char* cal_ip_if_alias_get(unsigned int id);
int cal_ip_if_alias_set(unsigned int id, char* val);
char* cal_ip_name_get(unsigned int id);
int cal_ip_name_set(unsigned int id, char* val);
char* cal_ip_mode_get(unsigned int id);
int cal_ip_mode_set(unsigned int id, char* val);
char* cal_ip_mtu_get(unsigned int id);
int cal_ip_mtu_set(unsigned int id, char* val);
char* cal_ip_ipv4_addr_get(unsigned int id);
int cal_ip_ipv4_addr_set(unsigned int id, char* val);
char* cal_ip_net_mask_get(unsigned int id);
int cal_ip_net_mask_set(unsigned int id, char* val);
char* cal_ip_type_get(unsigned int id);

char* cal_ip_ipv4_enable_get(unsigned int id);
int cal_ip_ipv4_enable_set(unsigned int id, char* val);
char* cal_ip_ipv6_enable_get(unsigned int id);
int cal_ip_ipv6_enable_set(unsigned int id, char* val);
char* cal_ip_ipv6_ula_enable_get(unsigned int id);
int cal_ip_ipv6_ula_enable_set(unsigned int id, char* val);
char* cal_ip_ipv6_ula_subnetID_get(unsigned int id);
int cal_ip_ipv6_ula_subnetID_set(unsigned int id, char* val);
char* cal_ip_ipv6_pext_enable_get();
int cal_ip_ipv6_pext_enable_set(char* val);
char* cal_ip_ipv6_temp_valid_lifetime_get();
int cal_ip_ipv6_temp_valid_lifetime_set(char* val);
char* cal_ip_ipv6_temp_preffered_lifetime_get();
int cal_ip_ipv6_temp_preffered_lifetime_set(char* val);
char* cal_ip_x_sc_access_type_get();
int cal_ip_x_sc_access_type_set(char* val);
/*to add here*/
#endif
