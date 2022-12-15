#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sc_nvram.h>

#define SAL_LAN_TMP_VALUE_MAX_LENGTH    (256)
#define SAL_LAN_TMP_PATH_MAX_LENGTH     (256)

#define LAN_CFG_BASE "/tmp/lan.sal"

#define NVRAN_GET_LAN_FUNC(funcname, name, buffer)\
char *funcname(void)\
{\
	{\
		static char buffer[SAL_LAN_TMP_VALUE_MAX_LENGTH];\
		char *p;\
		char lan_nvram_path[SAL_LAN_TMP_PATH_MAX_LENGTH];\
    	snprintf(lan_nvram_path, sizeof(lan_nvram_path), LAN_CFG_BASE);\
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

#define NVRAN_SET_LAN_FUNC(funcname, name)\
int funcname(char *value)\
{\
	{\
		char lan_nvram_path[SAL_LAN_TMP_PATH_MAX_LENGTH];\
		if(!value)\
			return -1;\
    	snprintf(lan_nvram_path, sizeof(lan_nvram_path), LAN_CFG_BASE);\
		return nvram_set_p(lan_nvram_path, name, value);\
	}\
}


#define SAL_LAN_TMP_ULA_ADDR_NAME       "ula_addr"
#define SAL_LAN_TMP_ULA_PREFIX_NAME     "ula_prefix"
#define SAL_LAN_TMP_SUBNETID_NAME     "subnetID"
#define SAL_LAN_TMP_GUA_ADDR_NAME       "gua_addr"
#define SAL_LAN_TMP_GUA_PREFIX_NAME     "gua_prefix"
#define SAL_LAN_TMP_OLD_GUA_PREFIX_NAME     "old_gua_prefix"
#define SAL_LAN_TMP_GUA_56BIT_PREFIX_NAME  "gua_56bit_prefix"

#define SAL_LAN_TMP_PRIVACY_POLICY_NAME     "privacy_policy"

#define SAL_LAN_TMP_GUA_PREFIX_LEN     "gua_prefix_len"

NVRAN_GET_LAN_FUNC(sal_lan_get_ula_addr_t, SAL_LAN_TMP_ULA_ADDR_NAME, value)
NVRAN_SET_LAN_FUNC(sal_lan_set_ula_addr_t, SAL_LAN_TMP_ULA_ADDR_NAME)
NVRAN_GET_LAN_FUNC(sal_lan_get_ula_prefix_t, SAL_LAN_TMP_ULA_PREFIX_NAME, value)
NVRAN_SET_LAN_FUNC(sal_lan_set_ula_prefix_t, SAL_LAN_TMP_ULA_PREFIX_NAME)
NVRAN_GET_LAN_FUNC(sal_lan_get_subnetid_t, SAL_LAN_TMP_SUBNETID_NAME, value)
NVRAN_SET_LAN_FUNC(sal_lan_set_subnetid_t, SAL_LAN_TMP_SUBNETID_NAME)
NVRAN_GET_LAN_FUNC(sal_lan_get_gua_addr_t, SAL_LAN_TMP_GUA_ADDR_NAME, value)
NVRAN_SET_LAN_FUNC(sal_lan_set_gua_addr_t, SAL_LAN_TMP_GUA_ADDR_NAME)
NVRAN_GET_LAN_FUNC(sal_lan_get_gua_prefix_t, SAL_LAN_TMP_GUA_PREFIX_NAME, value)
NVRAN_SET_LAN_FUNC(sal_lan_set_gua_prefix_t, SAL_LAN_TMP_GUA_PREFIX_NAME)
NVRAN_GET_LAN_FUNC(sal_lan_get_old_gua_prefix_t, SAL_LAN_TMP_OLD_GUA_PREFIX_NAME, value)
NVRAN_SET_LAN_FUNC(sal_lan_set_old_gua_prefix_t, SAL_LAN_TMP_OLD_GUA_PREFIX_NAME)
NVRAN_GET_LAN_FUNC(sal_lan_get_gua_56bit_prefix_t, SAL_LAN_TMP_GUA_56BIT_PREFIX_NAME, value)
NVRAN_SET_LAN_FUNC(sal_lan_set_gua_56bit_prefix_t, SAL_LAN_TMP_GUA_56BIT_PREFIX_NAME)

NVRAN_GET_LAN_FUNC(sal_lan_get_privacy_policy_t, SAL_LAN_TMP_PRIVACY_POLICY_NAME, value)
NVRAN_SET_LAN_FUNC(sal_lan_set_privacy_policy_t, SAL_LAN_TMP_PRIVACY_POLICY_NAME)

NVRAN_GET_LAN_FUNC(sal_lan_get_gua_prefix_len_t, SAL_LAN_TMP_GUA_PREFIX_LEN, value)
NVRAN_SET_LAN_FUNC(sal_lan_set_gua_prefix_len_t, SAL_LAN_TMP_GUA_PREFIX_LEN)
