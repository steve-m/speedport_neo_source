#ifndef _CAL_TR069_H_
#define _CAL_TR069_H_


int cal_tr069_get_enable(void);
int cal_tr069_set_enable(char *value);
int cal_tr069_get_wan_id(void);
int cal_tr069_set_wan_id(int wanId);
int cal_tr069_set_wan_iface(char *value);
int cal_tr069_set_wan_ip(char *value);
int cal_tr069_set_acs_url(char *value);
char *cal_tr069_get_acs_url(void);
int cal_tr069_get_option43_override(void);
int cal_tr069_set_option43_override(char *value);
int cal_tr069_set_acs_user(char *value);
char *cal_tr069_get_acs_user(void);
int cal_tr069_set_acs_pwd(char *value);
char *cal_tr069_get_acs_pwd(void);
int cal_tr069_set_cpe_user(char *value);
char *cal_tr069_get_cpe_user(void);
int cal_tr069_set_cpe_pwd(char *value);
char *cal_tr069_get_cpe_pwd(void);
int cal_tr069_set_cpe_port(char *value);
int cal_tr069_get_cpe_port(void);
int cal_tr069_set_inform_enable(char *value);
int cal_tr069_get_inform_enable(void);
int cal_tr069_set_inform_interval(char *value);
int cal_tr069_get_inform_interval(void);
int cal_tr069_set_inform_time(char *value);
char *cal_tr069_get_inform_time(void);
#endif /*_CAL_TR069_H_*/


