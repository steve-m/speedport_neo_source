#ifndef __SAL_BGM_H__
#define __SAL_BGM_H__

#define WPS_STATUS_INPROGRESS	"1"
#define WPS_STATUS_SUCCESS		"2"
#define WPS_STATUS_FAIL			"3"
char *sal_wps_get_wps_method(void);
int sal_wps_set_wps_method(char *value);

char *sal_wps_get_wps_pin(void);
int sal_wps_set_wps_pin(char *value);

char *sal_wps_get_wps_configstate(void);
int sal_wps_set_wps_configstate(char *value);

char *sal_wps_get_wps_status(void);
int sal_wps_set_wps_status(char *value);

#endif
