
#ifndef __SAL_LAN_H__
#define __SAL_LAN_H__
char *sal_lan_get_ula_addr_t(void);
int sal_lan_set_ula_addr_t(char *value);

char *sal_lan_get_ula_prefix_t(void);
int sal_lan_set_ula_prefix_t(char *value);

char *sal_lan_get_gua_addr_t(void);
int sal_lan_set_gua_addr_t(char *value);

char *sal_lan_get_gua_prefix_t(void);
int sal_lan_set_gua_prefix_t(char *value);

char *sal_lan_get_old_gua_prefix_t(void);
int sal_lan_set_old_gua_prefix_t(char *value);

char *sal_lan_get_gua_56bit_prefix_t(void);
int sal_lan_set__gua_56bit_prefix_t(char *value);

char *sal_lan_get_subnetid_t(void);
int sal_lan_set_subnetid_t(char *value);

char *sal_lan_get_gua_prefix_len_t(void);
int sal_lan_set_gua_prefix_len_t(char *value);
#endif
