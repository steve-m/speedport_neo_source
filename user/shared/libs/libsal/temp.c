#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sc_nvram.h>

/*
	Marc add to record the time of update object.
*/
#define SAL_TEMP_VALUE_MAX_LENGTH	256
#define SAL_TEMP_PATH_MAX_LENGTH		256

#define TEMP_CFG_BASE "/tmp/temp.sal"

#define NVRAN_GET_TEMP_FUNC(funcname, name, buffer)\
char *funcname(void)\
{\
	{\
		static char buffer[SAL_TEMP_VALUE_MAX_LENGTH];\
		char *p;\
		char temp_nvram_path[SAL_TEMP_PATH_MAX_LENGTH];\
    	snprintf(temp_nvram_path, sizeof(temp_nvram_path), TEMP_CFG_BASE);\
    	buffer[0] = '\0';\
		p = nvram_get_fun(name, temp_nvram_path);\
		if(p)\
		{\
			snprintf(buffer, sizeof(buffer), "%s", p);\
			free(p);\
		}\
		return buffer;\
	}\
}

#define NVRAN_SET_TEMP_FUNC(funcname, name)\
int funcname(char *value)\
{\
	{\
		char temp_nvram_path[SAL_TEMP_PATH_MAX_LENGTH];\
		if(!value)\
			return -1;\
    	snprintf(temp_nvram_path, sizeof(temp_nvram_path), TEMP_CFG_BASE);\
		return nvram_set_p(temp_nvram_path, name, value);\
	}\
}


#define SAL_TEMP_WPS_TURN_ON_WIFI    "wps_turn_on_wifi"
#define SAL_TEMP_WLAN_START    "wlan_start"
#define SAL_TEMP_WLAN_STOP    "wlan_stop"
#define SAL_TEMP_LOG_OFFSET_NAME	"log_offset"
#define SAL_TEMP_ACS_URL	"acs_url"
#define SAL_TEMP_TR069_UP_BY	"tr069_up_by"
#define SAL_TEMP_TR069_EVENT	"tr069_event"
#define SAL_TEMP_DEVICE_REBOOT	"device_reboot"
#define SAL_TEMP_ACS_REACH	"acs_reach"
#define SAL_HALP_LOGIN_USERNAME	        "halp_username"
#define SAL_HALP_LOGIN_PASSOWRD	        "halp_password"
#define SAL_HALP_REFRESH_TOKEN	        "refresh_token"
#define SAL_HALP_REFRESH_TOKEN_UPTIME	"refresh_token_uptime"
#define SAL_HALP_REFRESH_TOKEN_LIFETIME	"refresh_token_lifetime"

NVRAN_GET_TEMP_FUNC(sal_temp_get_wps_turn_on_wifi, SAL_TEMP_WPS_TURN_ON_WIFI, value)
NVRAN_SET_TEMP_FUNC(sal_temp_set_wps_turn_on_wifi, SAL_TEMP_WPS_TURN_ON_WIFI)

NVRAN_GET_TEMP_FUNC(sal_temp_get_wlan_start, SAL_TEMP_WLAN_START, value)
NVRAN_SET_TEMP_FUNC(sal_temp_set_wlan_start, SAL_TEMP_WLAN_START)

NVRAN_GET_TEMP_FUNC(sal_temp_get_wlan_stop, SAL_TEMP_WLAN_STOP, value)
NVRAN_SET_TEMP_FUNC(sal_temp_set_wlan_stop, SAL_TEMP_WLAN_STOP)

NVRAN_GET_TEMP_FUNC(sal_temp_get_log_offset, SAL_TEMP_LOG_OFFSET_NAME, log_offset)
NVRAN_SET_TEMP_FUNC(sal_temp_set_log_offset, SAL_TEMP_LOG_OFFSET_NAME)

NVRAN_GET_TEMP_FUNC(sal_temp_get_acs_url, SAL_TEMP_ACS_URL, acs_url)
NVRAN_SET_TEMP_FUNC(sal_temp_set_acs_url, SAL_TEMP_ACS_URL)

NVRAN_GET_TEMP_FUNC(sal_temp_get_tr069_up_by, SAL_TEMP_TR069_UP_BY, tr069_up_by)
NVRAN_SET_TEMP_FUNC(sal_temp_set_tr069_up_by, SAL_TEMP_TR069_UP_BY)

NVRAN_GET_TEMP_FUNC(sal_temp_get_tr069_event, SAL_TEMP_TR069_EVENT, tr069_event)
NVRAN_SET_TEMP_FUNC(sal_temp_set_tr069_event, SAL_TEMP_TR069_EVENT)

NVRAN_GET_TEMP_FUNC(sal_temp_get_device_reboot, SAL_TEMP_DEVICE_REBOOT, device_reboot)
NVRAN_SET_TEMP_FUNC(sal_temp_set_device_reboot, SAL_TEMP_DEVICE_REBOOT)

NVRAN_GET_TEMP_FUNC(sal_temp_get_acs_reach, SAL_TEMP_ACS_REACH, acs_reach)
NVRAN_SET_TEMP_FUNC(sal_temp_set_acs_reach, SAL_TEMP_ACS_REACH)

NVRAN_GET_TEMP_FUNC(sal_halp_get_halp_login_username, SAL_HALP_LOGIN_USERNAME, halp_username)
NVRAN_SET_TEMP_FUNC(sal_halp_set_halp_login_username, SAL_HALP_LOGIN_USERNAME)

NVRAN_GET_TEMP_FUNC(sal_halp_get_halp_login_password, SAL_HALP_LOGIN_PASSOWRD, halp_password)
NVRAN_SET_TEMP_FUNC(sal_halp_set_halp_login_password, SAL_HALP_LOGIN_PASSOWRD)

NVRAN_GET_TEMP_FUNC(sal_halp_get_refresh_token, SAL_HALP_REFRESH_TOKEN, refresh_token)
NVRAN_SET_TEMP_FUNC(sal_halp_set_refresh_token, SAL_HALP_REFRESH_TOKEN)

NVRAN_GET_TEMP_FUNC(sal_halp_get_refresh_token_uptime, SAL_HALP_REFRESH_TOKEN_UPTIME, refresh_token_uptime)
NVRAN_SET_TEMP_FUNC(sal_halp_set_refresh_token_uptime, SAL_HALP_REFRESH_TOKEN_UPTIME)

NVRAN_GET_TEMP_FUNC(sal_halp_get_refresh_token_lifetime, SAL_HALP_REFRESH_TOKEN_LIFETIME, refresh_token_lifetime)
NVRAN_SET_TEMP_FUNC(sal_halp_set_refresh_token_lifetime, SAL_HALP_REFRESH_TOKEN_LIFETIME)

