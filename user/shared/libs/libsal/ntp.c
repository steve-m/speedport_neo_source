#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sc_nvram.h>

#define SAL_NTP_TMP_VALUE_MAX_LENGTH	256
#define SAL_NTP_TMP_PATH_MAX_LENGTH		256

#define NTP_CFG_BASE "/tmp/ntp.sal"

#define NVRAN_GET_NTP_FUNC(funcname, name, buffer)\
char *funcname(void)\
{\
	{\
		static char buffer[SAL_NTP_TMP_VALUE_MAX_LENGTH];\
		char *p;\
		char ntp_nvram_path[SAL_NTP_TMP_PATH_MAX_LENGTH];\
    	snprintf(ntp_nvram_path, sizeof(ntp_nvram_path), NTP_CFG_BASE);\
    	buffer[0] = '\0';\
		p = nvram_get_fun(name, ntp_nvram_path);\
		if(p)\
		{\
			snprintf(buffer, sizeof(buffer), "%s", p);\
			free(p);\
		}\
		return buffer;\
	}\
}

#define NVRAN_SET_NTP_FUNC(funcname, name)\
int funcname(char *value)\
{\
	{\
		char ntp_nvram_path[SAL_NTP_TMP_PATH_MAX_LENGTH];\
		if(!value)\
			return -1;\
    	snprintf(ntp_nvram_path, sizeof(ntp_nvram_path), NTP_CFG_BASE);\
		return nvram_set_p(ntp_nvram_path, name, value);\
	}\
}


#define SAL_NTP_SERVER1_NAME        "ntp_server1"
#define SAL_NTP_SERVER2_NAME        "ntp_server2"        
#define SAL_NTP_ALIVE_SERVER_NAME   "ntp_alive_server"
#define SAL_NTP_TIMEZONE_NAME       "timezone"
#define SAL_NTP_LAST_STATUS_NAME    "last_status"
#define SAL_NTP_SYN_STATUS_NAME     "syn_status"

NVRAN_GET_NTP_FUNC(sal_ntp_get_server1, SAL_NTP_SERVER1_NAME, server1)
NVRAN_SET_NTP_FUNC(sal_ntp_set_server1, SAL_NTP_SERVER1_NAME)
NVRAN_GET_NTP_FUNC(sal_ntp_get_server2, SAL_NTP_SERVER2_NAME, server2)
NVRAN_SET_NTP_FUNC(sal_ntp_set_server2, SAL_NTP_SERVER2_NAME)

NVRAN_GET_NTP_FUNC(sal_ntp_get_alive_server, SAL_NTP_ALIVE_SERVER_NAME, alive_server)
NVRAN_SET_NTP_FUNC(sal_ntp_set_alive_server, SAL_NTP_ALIVE_SERVER_NAME)

NVRAN_GET_NTP_FUNC(sal_ntp_get_last_status, SAL_NTP_LAST_STATUS_NAME, last_status)
NVRAN_SET_NTP_FUNC(sal_ntp_set_last_status, SAL_NTP_LAST_STATUS_NAME)

NVRAN_GET_NTP_FUNC(sal_ntp_get_syn_status, SAL_NTP_SYN_STATUS_NAME, syn_status)
NVRAN_SET_NTP_FUNC(sal_ntp_set_syn_status, SAL_NTP_SYN_STATUS_NAME)

NVRAN_GET_NTP_FUNC(sal_ntp_get_timezone, SAL_NTP_TIMEZONE_NAME, timezone)
NVRAN_SET_NTP_FUNC(sal_ntp_set_timezone, SAL_NTP_TIMEZONE_NAME)

long sal_ntp_get_time_offset(void)
{
    long time_offset = 0;
    long hours, minutes;
    char sign;
    int ret;
    char *time_zone = sal_ntp_get_timezone();
    if(time_zone && strlen(time_zone))
    {
         ret = sscanf((time_zone + 3), "%c:%d:%d", &sign, &hours, &minutes);  
         if(3 == ret) 
         {                      
             time_offset = hours * 60 * 60 + minutes * 60; 
         
             if(sign == '-')
                 time_offset = -time_offset;  
             return time_offset;
         }          
          
    }
    return -1;

}
