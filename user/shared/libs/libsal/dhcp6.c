#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sc_nvram.h>
#include "sal/sal_dhcp6.h"

#define SAL_DHCP6_VALUE_MAX_LENGTH	256
#define SAL_DHCP6_PATH_MAX_LENGTH		256

#define DHCP6_CFG_BASE "/tmp/ipv6/dhcp6.sal"

#define NVRAN_GET_DHCP6_FUNC(funcname, name, buffer)\
char *funcname(void)\
{\
	{\
		static char buffer[SAL_DHCP6_VALUE_MAX_LENGTH];\
		char *p;\
		char dhcp6_nvram_path[SAL_DHCP6_PATH_MAX_LENGTH];\
    	snprintf(dhcp6_nvram_path, sizeof(dhcp6_nvram_path), DHCP6_CFG_BASE);\
    	buffer[0] = '\0';\
		p = nvram_get_fun(name, dhcp6_nvram_path);\
		if(p)\
		{\
			snprintf(buffer, sizeof(buffer), "%s", p);\
			free(p);\
		}\
		return buffer;\
	}\
}

#define NVRAN_SET_DHCP6_FUNC(funcname, name)\
int funcname(char *value)\
{\
	{\
		char dhcp6_nvram_path[SAL_DHCP6_PATH_MAX_LENGTH];\
		if(!value)\
			return -1;\
    	snprintf(dhcp6_nvram_path, sizeof(dhcp6_nvram_path), DHCP6_CFG_BASE);\
		return nvram_set_p(dhcp6_nvram_path, name, value);\
	}\
}


#define SAL_DHCP6_CLIENT_SERVERADDR			"client_server_addr"
#define SAL_DHCP6_CLIENT_SERVERDUID			"client_server_duid"
#define SAL_DHCP6_CLIENT_SERVERREFRESHTIME	"client_server_refresh_time"
#define SAL_DHCP6_SUGGESTED_T1				"client_suggested_t1"
#define SAL_DHCP6_SUGGESTED_T2				"client_suggested_t2"

NVRAN_GET_DHCP6_FUNC(sal_dhcp6_get_client_server_addr, SAL_DHCP6_CLIENT_SERVERADDR, value)
NVRAN_SET_DHCP6_FUNC(sal_dhcp6_set_client_server_addr, SAL_DHCP6_CLIENT_SERVERADDR)
NVRAN_GET_DHCP6_FUNC(sal_dhcp6_get_client_server_duid, SAL_DHCP6_CLIENT_SERVERDUID, value)
NVRAN_SET_DHCP6_FUNC(sal_dhcp6_set_client_server_duid, SAL_DHCP6_CLIENT_SERVERDUID)
NVRAN_GET_DHCP6_FUNC(sal_dhcp6_get_client_server_refresh_time, SAL_DHCP6_CLIENT_SERVERREFRESHTIME, value)
NVRAN_SET_DHCP6_FUNC(sal_dhcp6_set_client_server_refresh_time, SAL_DHCP6_CLIENT_SERVERREFRESHTIME)
NVRAN_GET_DHCP6_FUNC(sal_dhcp6_get_client_suggested_t1, SAL_DHCP6_SUGGESTED_T1, value)
NVRAN_SET_DHCP6_FUNC(sal_dhcp6_set_client_suggested_t1, SAL_DHCP6_SUGGESTED_T1)
NVRAN_GET_DHCP6_FUNC(sal_dhcp6_get_client_suggested_t2, SAL_DHCP6_SUGGESTED_T2, value)
NVRAN_SET_DHCP6_FUNC(sal_dhcp6_set_client_suggested_t2, SAL_DHCP6_SUGGESTED_T2)
