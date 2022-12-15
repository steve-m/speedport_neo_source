#ifndef _CFG_ppp_H_
#define _CFG_ppp_H_

char* cal_ppp_connection_enable_get(unsigned int wanid);
int cal_ppp_connection_enable_set(unsigned int wanid, char* val);
char* cal_ppp_connection_ipcpenable_get(unsigned int wanid);
int cal_ppp_connection_ipcpenable_set(unsigned int wanid, char* val);
char* cal_ppp_connection_ipv6cpenable_get(unsigned int wanid);
int cal_ppp_connection_ipv6cpenable_set(unsigned int wanid, char* val);
char* cal_ppp_connection_provider_get(unsigned int wanid);
int cal_ppp_connection_provider_set(unsigned int wanid, char* val);
char* cal_ppp_connection_conn_id_get(unsigned int wanid);
int cal_ppp_connection_conn_id_set(unsigned int wanid, char* val);
char* cal_ppp_connection_access_num_get(unsigned int wanid);
int cal_ppp_connection_access_num_set(unsigned int wanid, char* val);
char* cal_ppp_connection_jonit_num_get(unsigned int wanid);
int cal_ppp_connection_jonit_num_set(unsigned int wanid, char* val);
char* cal_ppp_connection_if_name_get(unsigned int wanid);
int cal_ppp_connection_if_name_set(unsigned int wanid, char* val);
char* cal_ppp_connection_idle_time_get(unsigned int wanid);
int cal_ppp_connection_idle_time_set(unsigned int wanid, char* val);
char* cal_ppp_connection_user_name_get(unsigned int wanid);
int cal_ppp_connection_user_name_set(unsigned int wanid, char* val);
char* cal_ppp_connection_password_get(unsigned int wanid);
int cal_ppp_connection_password_set(unsigned int wanid, char* val);
char* cal_ppp_connection_mtu_get(unsigned int wanid);
int cal_ppp_connection_mtu_set(unsigned int wanid, char* val);
char* cal_ppp_connection_trigger_get(unsigned int wanid);
int cal_ppp_connection_trigger_set(unsigned int wanid, char* val);
char* cal_ppp_connection_lcp_echo_get(unsigned int wanid);
int cal_ppp_connection_lcp_echo_set(unsigned int wanid, char* val);
char* cal_ppp_connection_lcp_retry_get(unsigned int wanid);
int cal_ppp_connection_lcp_retry_set(unsigned int wanid, char* val);
char* cal_ppp_connection_auto_ipv4_enable_get(unsigned int wanid);
int cal_ppp_connection_auto_ipv4_enable_set(unsigned int wanid, char* val);
char* cal_ppp_connection_ac_name_get(unsigned int wanid);
int cal_ppp_connection_ac_name_set(unsigned int wanid, char* val);
char* cal_ppp_connection_service_name_get(unsigned int wanid);
int cal_ppp_connection_service_name_set(unsigned int wanid, char* val);
char* cal_ppp_connection_ipv4_addr_get(unsigned int wanid);
int cal_ppp_connection_ipv4_addr_set(unsigned int wanid, char* val);
char* cal_ppp_connection_dns_get(unsigned int wanid);
int cal_ppp_connection_dns_set(unsigned int wanid, char* val);
char* cal_ppp_connection_provider_type_get(unsigned int wanid);
int cal_ppp_connection_provider_type_set(unsigned int wanid, char* val);
char* cal_ppp_connection_other_provider_name_get(unsigned int wanid);
int cal_ppp_connection_other_provider_name_set(unsigned int wanid, char* val);
char* cal_ppp_connection_other_username_get(unsigned int wanid);
int cal_ppp_connection_other_username_set(unsigned int wanid, char* val);
char* cal_ppp_connection_other_passwd_get(unsigned int wanid);
int cal_ppp_connection_other_passwd_set(unsigned int wanid, char* val);
char* cal_ppp_connection_reset_get(unsigned int wanid
);
int cal_ppp_connection_reset_set(unsigned int wanid
, char* val);
char* cal_ppp_privacy_ipv6_enable_get();
int cal_ppp_privacy_ipv6_enable_set(char* val);
char* cal_ppp_privacy_ipv6_pppoedown_get();
int cal_ppp_privacy_ipv6_pppoedown_set(char* val);
char* cal_ppp_privacy_ipv6_autoreconnectinterval_get();
int cal_ppp_privacy_ipv6_autoreconnectinterval_set(char* val);
char* cal_ppp_wan_privacy_ipv6_randomoffset_get();
int cal_ppp_wan_privacy_ipv6_randomoffset_set(char* val);
char* cal_ppp_wan_privacy_ipv6_nextevent_get();
int cal_ppp_wan_privacy_ipv6_nextevent_set(char* val);

/*to add here*/
#endif
