#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sc_nvram.h>

#define SAL_WPS_TMP_VALUE_MAX_LENGTH    (256)
#define SAL_WPS_TMP_PATH_MAX_LENGTH     (256)

#define WPS_CFG_BASE "/tmp/wps.sal"

#define NVRAN_GET_WPS_FUNC(funcname, name, buffer)\
char *funcname(void)\
{\
	{\
		static char buffer[SAL_WPS_TMP_VALUE_MAX_LENGTH];\
		char *p;\
		char lan_nvram_path[SAL_WPS_TMP_PATH_MAX_LENGTH];\
    	snprintf(lan_nvram_path, sizeof(lan_nvram_path), WPS_CFG_BASE);\
    	buffer[0] = '\0';\
		p = nvram_get_fun(name, lan_nvram_path);\
		if(p)\
		{\
			snprintf(buffer, sizeof(buffer), "%s", p);\
			free(p);\
		}\
		return buffer;\
	}\
}

#define NVRAN_SET_WPS_FUNC(funcname, name)\
int funcname(char *value)\
{\
	{\
		char lan_nvram_path[SAL_WPS_TMP_PATH_MAX_LENGTH];\
		if(!value)\
			return -1;\
    	snprintf(lan_nvram_path, sizeof(lan_nvram_path), WPS_CFG_BASE);\
		return nvram_set_p(lan_nvram_path, name, value);\
	}\
}


#define SAL_WPS_TMP_WPS_METHOD       "wps_method"
#define SAL_WPS_TMP_WPS_PIN          "wps_pin"
#define SAL_WPS_TMP_WPS_CONFIGSTATE  "wps_configstate"
#define SAL_WPS_TMP_WPS_STATUS    "wps_status"

NVRAN_GET_WPS_FUNC(sal_wps_get_wps_method, SAL_WPS_TMP_WPS_METHOD, value)
NVRAN_SET_WPS_FUNC(sal_wps_set_wps_method, SAL_WPS_TMP_WPS_METHOD)
NVRAN_GET_WPS_FUNC(sal_wps_get_wps_pin, SAL_WPS_TMP_WPS_PIN, value)
NVRAN_SET_WPS_FUNC(sal_wps_set_wps_pin, SAL_WPS_TMP_WPS_PIN)
NVRAN_GET_WPS_FUNC(sal_wps_get_wps_configstate, SAL_WPS_TMP_WPS_CONFIGSTATE, value)
NVRAN_SET_WPS_FUNC(sal_wps_set_wps_configstate, SAL_WPS_TMP_WPS_CONFIGSTATE)
NVRAN_GET_WPS_FUNC(sal_wps_get_wps_status, SAL_WPS_TMP_WPS_STATUS, value)
NVRAN_SET_WPS_FUNC(sal_wps_set_wps_status, SAL_WPS_TMP_WPS_STATUS)
