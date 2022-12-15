#ifndef __SAL_LOGIN_H__
#define __SAL_LOGIN_H__

#define LOGIN_STATUS_OK               "1"
#define LOGIN_STATUS_FAIL             "0"

char *sal_login_get_login_ip(void);
int sal_login_set_login_ip(char *value);

char *sal_login_get_failed_ip(void);
int sal_login_set_failed_ip(char *value);

char *sal_login_get_wps_pin(void);
int sal_login_set_wps_pin(char *value);

char * sal_login_get_timeout(void);
int sal_login_set_timeout(char *value);

int sal_login_get_login_status(void);

char * sal_login_get_password(void);
int sal_login_set_password(char *value);

char *sal_tr064_get_failed_times(void);
int sal_tr064_set_failed_times(char *value);

char * sal_login_get_challenge(void);
int sal_login_set_challenge(char *value);

#endif

