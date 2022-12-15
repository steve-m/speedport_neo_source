#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sc_nvram.h>

#define SAL_LOGIN_TMP_VALUE_MAX_LENGTH	512
#define SAL_LOGIN_TMP_PATH_MAX_LENGTH		256

#define LOGIN_CFG_BASE "/tmp/login.sal"

#define NVRAN_GET_LOGIN_FUNC(funcname, name, buffer)\
char *funcname(void)\
{\
	{\
		static char buffer[SAL_LOGIN_TMP_VALUE_MAX_LENGTH];\
		char *p;\
		char login_nvram_path[SAL_LOGIN_TMP_PATH_MAX_LENGTH];\
    	snprintf(login_nvram_path, sizeof(login_nvram_path), LOGIN_CFG_BASE);\
    	buffer[0] = '\0';\
		p = nvram_get_fun(name, login_nvram_path);\
		if(p)\
		{\
			snprintf(buffer, sizeof(buffer), "%s", p);\
			free(p);\
		}\
		return buffer;\
	}\
}

#define NVRAN_SET_LOGIN_FUNC(funcname, name)\
int funcname(char *value)\
{\
	{\
		char login_nvram_path[SAL_LOGIN_TMP_PATH_MAX_LENGTH];\
		if(!value)\
			return -1;\
    	snprintf(login_nvram_path, sizeof(login_nvram_path), LOGIN_CFG_BASE);\
		return nvram_set_p(login_nvram_path, name, value);\
	}\
}


#define SAL_LOGIN_IP_NAME           "login_ip"
#define SAL_LOGIN_FAILEDIP_NAME     "failed_ip"
#define SAL_LOGIN_MAC_NAME          "login_mac"
#define SAL_LOGIN_FAILEDMAC_NAME    "failed_mac"    
#define SAL_LOGIN_STA_PIN_NAME      "wps_sta_pin"        
#define SAL_LOGIN_TIME_OUT_NAME     "timeout"        
#define SAL_LOGIN_SECONDS_LEFT_NAME "secondsleft"        
#define SAL_LOGIN_SID_NAME          "session_id"        
#define SAL_LOGIN_LAST_SID_NAME     "last_session_id"        
#define SAL_LOGIN_CSRF_TOKEN        "csrf_token"    
#define SAL_LOGIN_LAST_CSRF_TOKEN        "last_csrf_token"    
#define SAL_LOGIN_CSRF_TOKEN_HIDDEN        "csrf_token_hidden"    
#define SAL_LOGIN_PASSWORD           "login_password"    
#define SAL_TR064_FAILEDIP_NAME      "tr064_failed_times"
#define SAL_LOGIN_CHALLENGE           "login_challenge"    

NVRAN_GET_LOGIN_FUNC(sal_login_get_login_ip, SAL_LOGIN_IP_NAME, sal_login_ip)
NVRAN_SET_LOGIN_FUNC(sal_login_set_login_ip, SAL_LOGIN_IP_NAME)
NVRAN_GET_LOGIN_FUNC(sal_login_get_failed_ip, SAL_LOGIN_FAILEDIP_NAME, sal_login_failed_ip)
NVRAN_SET_LOGIN_FUNC(sal_login_set_failed_ip, SAL_LOGIN_FAILEDIP_NAME)
NVRAN_GET_LOGIN_FUNC(sal_login_get_login_mac, SAL_LOGIN_MAC_NAME, sal_login_mac)
NVRAN_SET_LOGIN_FUNC(sal_login_set_login_mac, SAL_LOGIN_MAC_NAME)
NVRAN_GET_LOGIN_FUNC(sal_login_get_failed_mac, SAL_LOGIN_FAILEDMAC_NAME, sal_login_failed_mac)
NVRAN_SET_LOGIN_FUNC(sal_login_set_failed_mac, SAL_LOGIN_FAILEDMAC_NAME)
NVRAN_GET_LOGIN_FUNC(sal_login_get_wps_pin, SAL_LOGIN_STA_PIN_NAME, sal_wps_pin)
NVRAN_SET_LOGIN_FUNC(sal_login_set_wps_pin, SAL_LOGIN_STA_PIN_NAME)
NVRAN_GET_LOGIN_FUNC(sal_login_get_timeout, SAL_LOGIN_TIME_OUT_NAME,sal_timeout)
NVRAN_SET_LOGIN_FUNC(sal_login_set_timeout, SAL_LOGIN_TIME_OUT_NAME)
NVRAN_GET_LOGIN_FUNC(sal_login_get_secondsleft, SAL_LOGIN_SECONDS_LEFT_NAME,sal_secondsleft)
NVRAN_SET_LOGIN_FUNC(sal_login_set_secondsleft, SAL_LOGIN_SECONDS_LEFT_NAME)
NVRAN_GET_LOGIN_FUNC(sal_login_get_session_id, SAL_LOGIN_SID_NAME,sal_session_id)
NVRAN_SET_LOGIN_FUNC(sal_login_set_session_id, SAL_LOGIN_SID_NAME)
NVRAN_GET_LOGIN_FUNC(sal_login_get_last_session_id, SAL_LOGIN_LAST_SID_NAME,sal_last_session_id)
NVRAN_SET_LOGIN_FUNC(sal_login_set_last_session_id, SAL_LOGIN_LAST_SID_NAME)
NVRAN_GET_LOGIN_FUNC(sal_login_get_csrf_token, SAL_LOGIN_CSRF_TOKEN,sal_csrf_token)
NVRAN_SET_LOGIN_FUNC(sal_login_set_csrf_token, SAL_LOGIN_CSRF_TOKEN)
NVRAN_GET_LOGIN_FUNC(sal_login_get_last_csrf_token, SAL_LOGIN_LAST_CSRF_TOKEN,sal_last_csrf_token)
NVRAN_SET_LOGIN_FUNC(sal_login_set_last_csrf_token, SAL_LOGIN_LAST_CSRF_TOKEN)
NVRAN_GET_LOGIN_FUNC(sal_login_get_csrf_token_hidden, SAL_LOGIN_CSRF_TOKEN_HIDDEN,sal_csrf_token_hidden)
NVRAN_SET_LOGIN_FUNC(sal_login_set_csrf_token_hidden, SAL_LOGIN_CSRF_TOKEN_HIDDEN)
NVRAN_GET_LOGIN_FUNC(sal_login_get_password, SAL_LOGIN_PASSWORD,sal_login_password)
NVRAN_SET_LOGIN_FUNC(sal_login_set_password, SAL_LOGIN_PASSWORD)
NVRAN_GET_LOGIN_FUNC(sal_tr064_get_failed_times, SAL_TR064_FAILEDIP_NAME, sal_tr064_failed_times)

NVRAN_SET_LOGIN_FUNC(sal_tr064_set_failed_times, SAL_TR064_FAILEDIP_NAME)
NVRAN_GET_LOGIN_FUNC(sal_login_get_challenge, SAL_LOGIN_CHALLENGE,sal_login_challenge)
NVRAN_SET_LOGIN_FUNC(sal_login_set_challenge, SAL_LOGIN_CHALLENGE)

static int get_uptime_sec(char *buffer)
{
    FILE *fp = NULL;
    char time[64];

    fp = fopen("/proc/uptime", "r");
    if (fp == NULL)
        return -1;

    fgets(time, sizeof(time), fp);
    fclose(fp);
    sscanf(time,"%s %*s", buffer);
    
    return 0;
}

int sal_login_get_login_status(void)
{
    char current_time[64],last_time[64];
    
    if(strcmp(sal_login_get_session_id(), "")!=0)
    {
        if(get_uptime_sec(current_time)==0)
        {
            strcpy(last_time, sal_login_get_timeout());
            if((atoi(current_time)-atoi(last_time))>=900)
            {
                sal_login_set_session_id("");
                sal_login_set_last_session_id("");
                sal_login_set_login_ip("");
            }
        }
    }
    return (strcmp(sal_login_get_session_id(), "")==0)? 0:1;
}
