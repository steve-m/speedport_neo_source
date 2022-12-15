/**
 * @file   wan_t.c
 * @author Martin Huang martin_huang@sdc.sercomm.com
 * @date   2011-08-11
 * @brief  support multiple wan configuration abstract layer API.
 *
 * Copyright - 2011 SerComm Corporation. All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document without notice.
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising
 * out of the application or use of any product or circuit. SerComm Corporation specifisally
 * disclaims any and all liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of others.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <sc_nvram.h>
#include "sal_wan.h"

#define WAN_CFG_BASE			"/tmp/0/"

#define SAL_WAN_TMP_CFG_NAME			"s000"	

#define SAL_WAN_TMP_L2_IF_CFG_NAME		"l2_ifName"
#define SAL_WAN_TMP_L2_UNTAG_IF_CFG_NAME	"l2_untagifName"
#define SAL_WAN_TMP_WAN_ACCESS_TYPE		"wan_access_type"
#define SAL_WAN_TMP_DSL_STATUS_NAME		"dsl_status"
#define SAL_WAN_TMP_DSL_MODE_NAME		"dsl_mode"
#define SAL_WAN_TMP_CON_MODE_CFG_NAME	        "con_mode"
#define SAL_WAN_TMP_CON_TYPE_CFG_NAME	        "con_type"
#define SAL_WAN_TMP_CON_IP_VER_TYPE	        "con_ip_ver"
#define SAL_WAN_TMP_CON_IPV6_PRI_MODE	        "con_ipv6_pri"
#define SAL_WAN_TMP_DSL_LINK_STATUS_NAME		"dsl_link_status"

#define SAL_WAN_TMP_IP_ST_NAME			"con_ip"
#define SAL_WAN_TMP_GW_ST_NAME			"con_gw"
#define SAL_WAN_TMP_IP_MASK_ST_NAME		"con_ipmask"
#define SAL_WAN_TMP_DNS1_ST_NAME		"con_dns1"
#define SAL_WAN_TMP_DNS2_ST_NAME		"con_dns2"
#define SAL_WAN_TMP_LEASE_ST_NAME		"con_lease"
#define SAL_WAN_TMP_OPT12_ST_NAME		"con_option12"
#define SAL_WAN_TMP_OPT42_ST_NAME		"con_option42"
#define SAL_WAN_TMP_OPT43_ST_NAME		"con_option43"
#define SAL_WAN_TMP_OPT2_ST_NAME		"con_option2"

#define SAL_WAN_TMP_DHCP_SERVER_ST_NAME		"con_dhcp_server"

#define SAL_WAN_TMP_GW_MAC_ST_NAME		"con_gw_mac"

#define SAL_WAN_TMP_PPP_SESSION_ST_NAME	        "con_ppp_session"
#define SAL_WAN_TMP_PPP_TRIGGER_ST_NAME	        "con_ppp_trigger"
#define SAL_WAN_TMP_TRIGGER_FLAG	        "con_trigger_flag"
#define SAL_WAN_TMP_UPTIME_ST_NAME		"con_uptime"
#define SAL_WAN_TMP_STATE_ST_NAME		"con_state"
#define SAL_WAN_TMP_CLIENT_PID_ST_NAME		"con_client_pid"
#define SAL_WAN_TMP_AUTH_FAILED_ST_NAME		"con_auth_failed"
#define SAL_WAN_TMP_AUTH_FAIL_CODE_ST_NAME  	"con_auth_fail_code"
#define SAL_WAN_TMP_ERROR_LOG_CODE_ST_NAME  	"con_error_log_code"
#define SAL_WAN_TMP_FAIL_CODE_ST_NAME		"con_fail_code"
#define SAL_WAN_TMP_AUTH_FAILED_INFO_ST_NAME		"con_auth_failed_info"

#define SAL_WAN_TMP_HW_IDLE_TIME_ST_NAME	"con_hw_idle_time"
#define SAL_WAN_TMP_PPP_LCP_ST_NAME		"con_lcp_state"
#define SAL_WAN_TMP_SERVICE_ST_NAME		"con_service_state"
#define SAL_WAN_TMP_PHY_INIT_ST_NAME		"con_phy_init"

#define SAL_WAN_TMP_IPV6_STATE		        "conv6_state"
#define SAL_WAN_TMP_IPV6_UPTIME		        "conv6_uptime"
#define SAL_WAN_TMP_IPV6_LLLOCAL		"conv6_local_addr"
#define SAL_WAN_TMP_IPV6_LLREMOTE		"conv6_remote_addr"
#define SAL_WAN_TMP_IPV6_GLOBAL		        "conv6_global_addr"
#define SAL_WAN_TMP_IPV6_PREFIX_ST_NAME 	"conv6_assigned_prefix"
#define SAL_WAN_TMP_IPV6_DNS1_ST_NAME		"conv6_dns1"
#define SAL_WAN_TMP_IPV6_DNS2_ST_NAME		"conv6_dns2"
#define SAL_WAN_TMP_IPV6_SERVICE_ST_NAME	"conv6_service_state"
#define SAL_WAN_TMP_PPP_CFG_PROVIDER_NAME	"ppp_cfg_provider_name"
#define SAL_WAN_TMP_PPP_CFG_USER_NAME		"ppp_cfg_user_name"
#define SAL_WAN_TMP_PPP_CFG_PASSWORD		"ppp_cfg_password"

#define SAL_WAN_TMP_VALUE_MAX_LENGTH	256
#define SAL_WAN_TMP_PATH_MAX_LENGTH		256


#define NVRAN_GET_WAN_FUNC(funcname, name, buffer)\
char *funcname(int wan)\
{\
	{\
		static char buffer[SAL_WAN_TMP_VALUE_MAX_LENGTH];\
		char *p;\
		char wan_nvram_path[SAL_WAN_TMP_PATH_MAX_LENGTH];\
    	snprintf(wan_nvram_path, sizeof(wan_nvram_path), WAN_CFG_BASE"%d/%s", wan, SAL_WAN_TMP_CFG_NAME);\
    	buffer[0] = '\0';\
		p = nvram_get_fun(name, wan_nvram_path);\
		if(p)\
		{\
			snprintf(buffer, sizeof(buffer), "%s", p);\
			free(p);\
		}\
		return buffer;\
	}\
}

#define NVRAN_SET_WAN_FUNC(funcname, name)\
int funcname(int wan, char *value)\
{\
	{\
		char wan_nvram_path[SAL_WAN_TMP_PATH_MAX_LENGTH];\
		if(!value)\
			return -1;\
    	snprintf(wan_nvram_path, sizeof(wan_nvram_path), WAN_CFG_BASE"%d/%s", wan, SAL_WAN_TMP_CFG_NAME);\
		return nvram_set_p(wan_nvram_path, name, value);\
	}\
}

#define NVRAN_GET_PHY_FUNC(funcname, name, buffer)\
char *funcname(int wan)\
{\
	{\
		static char buffer[SAL_WAN_TMP_VALUE_MAX_LENGTH];\
		char *p;\
		char wan_nvram_path[SAL_WAN_TMP_PATH_MAX_LENGTH];\
    	snprintf(wan_nvram_path, sizeof(wan_nvram_path), WAN_CFG_BASE"%s", SAL_WAN_TMP_CFG_NAME);\
    	buffer[0] = '\0';\
		p = nvram_get_fun(name, wan_nvram_path);\
		if(p)\
		{\
			snprintf(buffer, sizeof(buffer), "%s", p);\
			free(p);\
		}\
		return buffer;\
	}\
}

#define NVRAN_SET_PHY_FUNC(funcname, name)\
int funcname(int wan, char *value)\
{\
	{\
		char wan_nvram_path[SAL_WAN_TMP_PATH_MAX_LENGTH];\
		if(!value)\
			return -1;\
    	snprintf(wan_nvram_path, sizeof(wan_nvram_path), WAN_CFG_BASE"%s",  SAL_WAN_TMP_CFG_NAME);\
		return nvram_set_p(wan_nvram_path, name, value);\
	}\
}
	
NVRAN_GET_WAN_FUNC(sal_wan_get_l2_if_name_t, SAL_WAN_TMP_L2_IF_CFG_NAME, l2_ifName)
NVRAN_SET_WAN_FUNC(sal_wan_set_l2_if_name_t, SAL_WAN_TMP_L2_IF_CFG_NAME)

NVRAN_GET_WAN_FUNC(sal_wan_get_l2_untag_if_name_t, SAL_WAN_TMP_L2_UNTAG_IF_CFG_NAME, l2_untagifName)
NVRAN_SET_WAN_FUNC(sal_wan_set_l2_untag_if_name_t, SAL_WAN_TMP_L2_UNTAG_IF_CFG_NAME)

NVRAN_GET_WAN_FUNC(sal_wan_get_con_mode_t, SAL_WAN_TMP_CON_MODE_CFG_NAME, con_mode)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_mode_t, SAL_WAN_TMP_CON_MODE_CFG_NAME)

NVRAN_GET_WAN_FUNC(sal_wan_get_con_type_t, SAL_WAN_TMP_CON_TYPE_CFG_NAME, con_type)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_type_t, SAL_WAN_TMP_CON_TYPE_CFG_NAME)

NVRAN_GET_WAN_FUNC(sal_wan_get_con_ip_ver_type_t, SAL_WAN_TMP_CON_IP_VER_TYPE, con_ip_ver)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_ip_ver_type_t, SAL_WAN_TMP_CON_IP_VER_TYPE)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_ipv6_pri_mode_t, SAL_WAN_TMP_CON_IPV6_PRI_MODE, con_ipv6_pri)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_ipv6_pri_mode_t, SAL_WAN_TMP_CON_IPV6_PRI_MODE)

NVRAN_GET_WAN_FUNC(sal_wan_get_con_ip_t, SAL_WAN_TMP_IP_ST_NAME, con_ip)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_ip_t, SAL_WAN_TMP_IP_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_gw_t, SAL_WAN_TMP_GW_ST_NAME, con_gw)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_gw_t, SAL_WAN_TMP_GW_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_ipmask_t, SAL_WAN_TMP_IP_MASK_ST_NAME, con_ipmask)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_ipmask_t, SAL_WAN_TMP_IP_MASK_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_dns1_t, SAL_WAN_TMP_DNS1_ST_NAME, con_dns1)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_dns1_t, SAL_WAN_TMP_DNS1_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_dns2_t, SAL_WAN_TMP_DNS2_ST_NAME, con_dns2)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_dns2_t, SAL_WAN_TMP_DNS2_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_opt12_t, SAL_WAN_TMP_OPT12_ST_NAME, con_opt12)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_opt12_t, SAL_WAN_TMP_OPT12_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_opt2_t, SAL_WAN_TMP_OPT2_ST_NAME, con_opt2)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_opt2_t, SAL_WAN_TMP_OPT2_ST_NAME)

NVRAN_GET_WAN_FUNC(sal_wan_get_con_opt42_t, SAL_WAN_TMP_OPT42_ST_NAME, con_opt42)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_opt42_t, SAL_WAN_TMP_OPT42_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_opt43_t, SAL_WAN_TMP_OPT43_ST_NAME, con_opt43)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_opt43_t, SAL_WAN_TMP_OPT43_ST_NAME)

NVRAN_GET_WAN_FUNC(sal_wan_get_con_lease_t, SAL_WAN_TMP_LEASE_ST_NAME, con_lease)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_lease_t, SAL_WAN_TMP_LEASE_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_dhcp_server_t, SAL_WAN_TMP_DHCP_SERVER_ST_NAME, con_dhcp_server)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_dhcp_server_t, SAL_WAN_TMP_DHCP_SERVER_ST_NAME)

NVRAN_GET_WAN_FUNC(sal_wan_get_con_gw_mac_t, SAL_WAN_TMP_GW_MAC_ST_NAME, con_gw_mac)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_gw_mac_t, SAL_WAN_TMP_GW_MAC_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_ppp_session_t, SAL_WAN_TMP_PPP_SESSION_ST_NAME, con_session)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_ppp_session_t, SAL_WAN_TMP_PPP_SESSION_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_ppp_trigger_t, SAL_WAN_TMP_PPP_TRIGGER_ST_NAME, con_trigger)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_ppp_trigger_t, SAL_WAN_TMP_PPP_TRIGGER_ST_NAME)

NVRAN_GET_WAN_FUNC(sal_wan_get_con_trigger_flag_t, SAL_WAN_TMP_TRIGGER_FLAG, con_trigger_flag)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_trigger_flag_t, SAL_WAN_TMP_TRIGGER_FLAG)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_uptime_t, SAL_WAN_TMP_UPTIME_ST_NAME, con_uptime)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_uptime_t, SAL_WAN_TMP_UPTIME_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_state_t, SAL_WAN_TMP_STATE_ST_NAME, con_state)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_client_pid_t, SAL_WAN_TMP_CLIENT_PID_ST_NAME, con_client_pid)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_state_t, SAL_WAN_TMP_STATE_ST_NAME)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_client_pid_t, SAL_WAN_TMP_CLIENT_PID_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_auth_failed_t, SAL_WAN_TMP_AUTH_FAILED_ST_NAME, con_auth_failed)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_auth_failed_t, SAL_WAN_TMP_AUTH_FAILED_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_auth_fail_code_t, SAL_WAN_TMP_AUTH_FAIL_CODE_ST_NAME, con_auth_fail_code)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_auth_fail_code_t, SAL_WAN_TMP_AUTH_FAIL_CODE_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_error_log_code_t, SAL_WAN_TMP_ERROR_LOG_CODE_ST_NAME, con_error_log_code)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_error_log_code_t, SAL_WAN_TMP_ERROR_LOG_CODE_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_fail_code_t, SAL_WAN_TMP_FAIL_CODE_ST_NAME, con_fail_code)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_fail_code_t, SAL_WAN_TMP_FAIL_CODE_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_auth_failed_info_t, SAL_WAN_TMP_AUTH_FAILED_INFO_ST_NAME, con_auth_failed_info)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_auth_failed_info_t, SAL_WAN_TMP_AUTH_FAILED_INFO_ST_NAME)


NVRAN_GET_WAN_FUNC(sal_wan_get_con_hw_idle_t, SAL_WAN_TMP_HW_IDLE_TIME_ST_NAME, con_hw_idle)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_hw_idle_t, SAL_WAN_TMP_HW_IDLE_TIME_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_con_lcp_state_t, SAL_WAN_TMP_PPP_LCP_ST_NAME, con_lcp_state)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_lcp_state_t, SAL_WAN_TMP_PPP_LCP_ST_NAME)

NVRAN_GET_WAN_FUNC(sal_wan_get_con_service_state_t, SAL_WAN_TMP_SERVICE_ST_NAME, con_service_state)
NVRAN_SET_WAN_FUNC(sal_wan_set_con_service_state_t, SAL_WAN_TMP_SERVICE_ST_NAME)

NVRAN_GET_PHY_FUNC(sal_wan_get_con_phy_init_t, SAL_WAN_TMP_PHY_INIT_ST_NAME, con_phy_init_state)
NVRAN_SET_PHY_FUNC(sal_wan_set_con_phy_init_t, SAL_WAN_TMP_PHY_INIT_ST_NAME)

NVRAN_GET_PHY_FUNC(sal_wan_get_dsl_status_t, SAL_WAN_TMP_DSL_STATUS_NAME, dsl_status)
NVRAN_SET_PHY_FUNC(sal_wan_set_dsl_status_t, SAL_WAN_TMP_DSL_STATUS_NAME)

NVRAN_GET_PHY_FUNC(sal_wan_get_dsl_link_status_t, SAL_WAN_TMP_DSL_LINK_STATUS_NAME, dsl_link_status)
NVRAN_SET_PHY_FUNC(sal_wan_set_dsl_link_status_t, SAL_WAN_TMP_DSL_LINK_STATUS_NAME)


NVRAN_GET_PHY_FUNC(sal_wan_get_dsl_mode_t, SAL_WAN_TMP_DSL_MODE_NAME, dsl_mode)
NVRAN_SET_PHY_FUNC(sal_wan_set_dsl_mode_t, SAL_WAN_TMP_DSL_MODE_NAME)

NVRAN_GET_PHY_FUNC(sal_wan_get_wan_access_type_t, SAL_WAN_TMP_WAN_ACCESS_TYPE, wan_access_type)
NVRAN_SET_PHY_FUNC(sal_wan_set_wan_access_type_t, SAL_WAN_TMP_WAN_ACCESS_TYPE)

NVRAN_GET_WAN_FUNC(sal_wan_get_ipv6_con_state_t, SAL_WAN_TMP_IPV6_STATE, conv6_state)
NVRAN_SET_WAN_FUNC(sal_wan_set_ipv6_con_state_t, SAL_WAN_TMP_IPV6_STATE)
NVRAN_GET_WAN_FUNC(sal_wan_get_ipv6_con_uptime_t, SAL_WAN_TMP_IPV6_UPTIME, conv6_uptime)
NVRAN_SET_WAN_FUNC(sal_wan_set_ipv6_con_uptime_t, SAL_WAN_TMP_IPV6_UPTIME)

NVRAN_GET_WAN_FUNC(sal_wan_get_ipv6_con_local_addr_t, SAL_WAN_TMP_IPV6_LLLOCAL, conv6_local_addr)
NVRAN_SET_WAN_FUNC(sal_wan_set_ipv6_con_local_addr_t, SAL_WAN_TMP_IPV6_LLLOCAL)
NVRAN_GET_WAN_FUNC(sal_wan_get_ipv6_con_remote_addr_t, SAL_WAN_TMP_IPV6_LLREMOTE, conv6_remote_addr)
NVRAN_SET_WAN_FUNC(sal_wan_set_ipv6_con_remote_addr_t, SAL_WAN_TMP_IPV6_LLREMOTE)
NVRAN_GET_WAN_FUNC(sal_wan_get_ipv6_con_global_addr_t, SAL_WAN_TMP_IPV6_GLOBAL, conv6_global_addr)
NVRAN_SET_WAN_FUNC(sal_wan_set_ipv6_con_global_addr_t, SAL_WAN_TMP_IPV6_GLOBAL)
NVRAN_GET_WAN_FUNC(sal_wan_get_ipv6_con_assigned_prefix_t, SAL_WAN_TMP_IPV6_PREFIX_ST_NAME, conv6_prefix)
NVRAN_SET_WAN_FUNC(sal_wan_set_ipv6_con_assigned_prefix_t, SAL_WAN_TMP_IPV6_PREFIX_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_ipv6_con_dns1_t, SAL_WAN_TMP_IPV6_DNS1_ST_NAME, conv6_dns1)
NVRAN_SET_WAN_FUNC(sal_wan_set_ipv6_con_dns1_t, SAL_WAN_TMP_IPV6_DNS1_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_ipv6_con_dns2_t, SAL_WAN_TMP_IPV6_DNS2_ST_NAME, conv6_dns2)
NVRAN_SET_WAN_FUNC(sal_wan_set_ipv6_con_dns2_t, SAL_WAN_TMP_IPV6_DNS2_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_ipv6_con_service_state_t, SAL_WAN_TMP_IPV6_SERVICE_ST_NAME, conv6_service_state)
NVRAN_SET_WAN_FUNC(sal_wan_set_ipv6_con_service_state_t, SAL_WAN_TMP_IPV6_SERVICE_ST_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_tmp_ppp_cfg_provider_name_t, SAL_WAN_TMP_PPP_CFG_PROVIDER_NAME, ppp_cfg_provider_name)
NVRAN_SET_WAN_FUNC(sal_wan_set_tmp_ppp_cfg_provider_name_t, SAL_WAN_TMP_PPP_CFG_PROVIDER_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_tmp_ppp_cfg_user_name_t, SAL_WAN_TMP_PPP_CFG_USER_NAME, ppp_cfg_user_name)
NVRAN_SET_WAN_FUNC(sal_wan_set_tmp_ppp_cfg_user_name_t, SAL_WAN_TMP_PPP_CFG_USER_NAME)
NVRAN_GET_WAN_FUNC(sal_wan_get_tmp_ppp_cfg_password_t, SAL_WAN_TMP_PPP_CFG_PASSWORD, ppp_cfg_password)
NVRAN_SET_WAN_FUNC(sal_wan_set_tmp_ppp_cfg_password_t, SAL_WAN_TMP_PPP_CFG_PASSWORD)


void sal_wan_store_cp_info(int wan, WAN_CP_INFO_t *info)
{
	//assert(info);
	char session_number[16];
	sal_wan_set_con_ip_t(wan, inet_ntoa(info->ip));
	sal_wan_set_con_gw_t(wan, inet_ntoa(info->gw));
	sal_wan_set_con_ipmask_t(wan, inet_ntoa(info->ipmask));
	sal_wan_set_con_dns1_t(wan, inet_ntoa(info->dns1));
	sal_wan_set_con_dns2_t(wan, inet_ntoa(info->dns2));
	sal_wan_set_con_lease_t(wan, info->lease_time);
	sal_wan_set_con_opt12_t(wan, info->opt12);
	sal_wan_set_con_opt42_t(wan, info->opt42);
	sal_wan_set_con_opt43_t(wan, info->opt43);
	if(info->ppp_session)
	{
	     snprintf(session_number, sizeof(session_number), "%d", info->ppp_session);
	     sal_wan_set_con_ppp_session_t(wan, session_number);
	}
	sal_wan_set_con_gw_mac_t(wan, info->gw_mac);
	sal_wan_set_con_uptime_t(wan, info->uptime);
	sal_wan_set_con_state_t(wan, info->state);
}
int sal_wan_load_cp_info(int wan, WAN_CP_INFO_t *info)
{
	char *session;
    char *dns_enable = NULL;
	char *con_mode = NULL;
	inet_aton(sal_wan_get_con_ip_t(wan), &info->ip);
	inet_aton(sal_wan_get_con_gw_t(wan), &info->gw);
	inet_aton(sal_wan_get_con_ipmask_t(wan),&info->ipmask);

    inet_aton(sal_wan_get_con_dns1_t(wan), &info->dns1);
    inet_aton(sal_wan_get_con_dns2_t(wan), &info->dns2);

	info->opt43 = sal_wan_get_con_opt43_t(wan);
	info->lease_time = sal_wan_get_con_lease_t(wan);
	info->gw_mac = sal_wan_get_con_gw_mac_t(wan);
	info->uptime = sal_wan_get_con_uptime_t(wan);
	info->state = sal_wan_get_con_state_t(wan);
	session = sal_wan_get_con_ppp_session_t(wan);
	if(strlen(session))
		info->ppp_session = atoi(sal_wan_get_con_ppp_session_t(wan));
	return 0;
}
	
char *sal_wan_get_lease_expires(int wan)
{
	static char dhcp_expired_str[64] = "";
	long wan_uptime=0;
	long lease=0;
	char *please = sal_wan_get_con_lease_t(wan);
	char *uptime = sal_wan_get_con_uptime_t(wan);
	if(strlen(please) && strlen(uptime))
	{
		sscanf(please, "%d", &lease);
		sscanf(uptime, "%d", &wan_uptime);
	}
	strcpy(dhcp_expired_str, scGetStdTime(wan_uptime + lease));
	return dhcp_expired_str;
}
char *sal_wan_get_connection_time(int wan)
{
	static char uptime_str[32] = "";
	FILE *fp = NULL;
	char *uptime = sal_wan_get_con_uptime_t(wan);
	char tmp[128] = "";
	int wan_uptime = 0;
	int time_now = 0;
	int time_h = 0;
	int time_min = 0;
	int time_sec = 0;
       
        if(strlen(uptime)==0)
            uptime = sal_wan_get_ipv6_con_uptime_t(wan);

	if(!strlen(uptime))
	   return uptime_str;
	
	sscanf(uptime, "%d", &wan_uptime);
	
        if((fp = fopen("/proc/uptime", "r")) == NULL)
	{
		return uptime_str;
	}
	fgets(tmp, sizeof(tmp), fp);
	sscanf(tmp, "%d", &time_now);
	fclose(fp);
	time_h = (time_now - wan_uptime)/3600;
	time_min = ((time_now - wan_uptime)%3600)/60;
	time_sec = (time_now - wan_uptime)%60;
	sprintf(uptime_str, "%02d:%02d:%02d", time_h, time_min, time_sec);
	return uptime_str;
}
