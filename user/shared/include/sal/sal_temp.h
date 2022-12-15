#ifndef __SAL_TEMP_H__
#define __SAL_TEMP_H__

char *sal_temp_get_wps_turn_on_wifi(void);
int sal_temp_set_wps_turn_on_wifi(char *value);

char *sal_temp_get_wlan_start(void);
int sal_temp_set_wlan_start(char *value);

char *sal_temp_get_wlan_stop(void);
int sal_temp_set_wlan_stop(char *value);

char *sal_temp_get_log_offset(void);
int sal_temp_set_log_offset(char *value);

char *sal_temp_get_acs_url(void);
int sal_temp_set_acs_url(char *value);

char *sal_temp_get_tr069_up_by(void);
int sal_temp_set_tr069_up_by(char *value);

char *sal_temp_get_tr069_event(void);
int sal_temp_set_tr069_event(char *value);

char *sal_temp_get_device_reboot(void);
int sal_temp_set_device_reboot(char *value);

char *sal_temp_get_acs_reach(void);
int sal_temp_set_acs_reach(char *value);

char *sal_halp_get_halp_login_username(void);
int sal_halp_set_halp_login_username(char *value);

char *sal_halp_get_halp_login_password(void);
int sal_halp_set_halp_login_password(char *value);

char *sal_halp_get_refresh_token(void);
int sal_halp_set_refresh_token(char *value);

char *sal_halp_get_refresh_token_uptime(void);
int sal_halp_set_refresh_token_uptime(char *value);

char *sal_halp_get_refresh_token_lifetime(void);
int sal_halp_set_refresh_token_lifetime(char *value);
#endif//__SAL_TEMP_H__

