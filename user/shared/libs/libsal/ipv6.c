#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sc_nvram.h>
#include "sal/sal_ipv6.h"

#define SAL_IPV6_VALUE_MAX_LENGTH		256
#define SAL_IPV6_PATH_MAX_LENGTH		256

#define IPV6_CFG_BASE "/tmp/ipv6/ipv6.sal"

#define NVRAN_GET_IPV6_FUNC(funcname, name, buffer)\
char *funcname(void)\
{\
	{\
		static char buffer[SAL_IPV6_VALUE_MAX_LENGTH];\
		char *p;\
		char ipv6_nvram_path[SAL_IPV6_PATH_MAX_LENGTH];\
    	snprintf(ipv6_nvram_path, sizeof(ipv6_nvram_path), IPV6_CFG_BASE);\
    	buffer[0] = '\0';\
		p = nvram_get_fun(name, ipv6_nvram_path);\
		if(p)\
		{\
			snprintf(buffer, sizeof(buffer), "%s", p);\
			free(p);\
		}\
		return buffer;\
	}\
}

#define NVRAN_SET_IPV6_FUNC(funcname, name)\
int funcname(char *value)\
{\
	{\
		char ipv6_nvram_path[SAL_IPV6_PATH_MAX_LENGTH];\
		if(!value)\
			return -1;\
    	snprintf(ipv6_nvram_path, sizeof(ipv6_nvram_path), IPV6_CFG_BASE);\
		return nvram_set_p(ipv6_nvram_path, name, value);\
	}\
}


#define SAL_IPV6_WAN_GUA					"wan_global_addr"
#define SAL_IPV6_WAN_LLA					"wan_linklocal_addr"
#define SAL_IPV6_LAN_GUA					"lan_global_addr"
#define SAL_IPV6_LAN_LLA					"lan_linklocal_addr"
#define SAL_IPV6_LAN_RA_MTU					"lan_ra_mtu"
#define SAL_BASIC_PRIVACY					"basic_privacy"
#define SAL_RA_DFT_LFT						"ra_dft_lftime"
#define SAL_RA_ROUTEINFO					"ra_routeinfo"
#define SAL_ND_WAN_RETRANS_TIMER			"nd_wan_retranstimer"

NVRAN_GET_IPV6_FUNC(sal_ipv6_get_wan_global_addr, SAL_IPV6_WAN_GUA, value)
NVRAN_SET_IPV6_FUNC(sal_ipv6_set_wan_global_addr, SAL_IPV6_WAN_GUA)
NVRAN_GET_IPV6_FUNC(sal_ipv6_get_wan_linklocal_addr, SAL_IPV6_WAN_LLA, value)
NVRAN_SET_IPV6_FUNC(sal_ipv6_set_wan_linklocal_addr, SAL_IPV6_WAN_LLA)
NVRAN_GET_IPV6_FUNC(sal_ipv6_get_lan_global_addr, SAL_IPV6_LAN_GUA, value)
NVRAN_SET_IPV6_FUNC(sal_ipv6_set_lan_global_addr, SAL_IPV6_LAN_GUA)
NVRAN_GET_IPV6_FUNC(sal_ipv6_get_lan_linklocal_addr, SAL_IPV6_LAN_LLA, value)
NVRAN_SET_IPV6_FUNC(sal_ipv6_set_lan_linklocal_addr, SAL_IPV6_LAN_LLA)
NVRAN_GET_IPV6_FUNC(sal_ipv6_get_lan_ra_mtu, SAL_IPV6_LAN_RA_MTU, value)
NVRAN_SET_IPV6_FUNC(sal_ipv6_set_lan_ra_mtu, SAL_IPV6_LAN_RA_MTU)
NVRAN_GET_IPV6_FUNC(sal_ipv6_get_basic_privacy, SAL_BASIC_PRIVACY, value)
NVRAN_SET_IPV6_FUNC(sal_ipv6_set_basic_privacy, SAL_BASIC_PRIVACY)
NVRAN_GET_IPV6_FUNC(sal_ipv6_get_ra_defaultlftime, SAL_RA_DFT_LFT, value)
NVRAN_SET_IPV6_FUNC(sal_ipv6_set_ra_defaultlftime, SAL_RA_DFT_LFT)
NVRAN_GET_IPV6_FUNC(sal_ipv6_get_ra_routeinfo, SAL_RA_ROUTEINFO, value)
NVRAN_SET_IPV6_FUNC(sal_ipv6_set_ra_routeinfo, SAL_RA_ROUTEINFO)
NVRAN_GET_IPV6_FUNC(sal_ipv6_get_nd_wan_retranstimer, SAL_ND_WAN_RETRANS_TIMER, value)
NVRAN_SET_IPV6_FUNC(sal_ipv6_set_nd_wan_retranstimer, SAL_ND_WAN_RETRANS_TIMER)
