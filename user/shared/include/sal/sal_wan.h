/**
 * @file   sal_wan.h
 * @author Martin_Huang@sdc.sercomm.com
 * @date   2011-09-01
 * @brief  state abstract layer
 *
 * Copyright - 2011 SerComm Corporation. All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document without notice.
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising
 * out of the application or use of any product or circuit. SerComm Corporation specifically
 * disclaims any and all liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of others.
 *
 *
 */
#ifndef __SAL_WAN_H__
#define __SAL_WAN_H__

#include <netinet/in.h>

typedef struct tag_WAN_CP_INFO{
	struct in_addr ip;
	struct in_addr ipmask;
	struct in_addr gw;
	struct in_addr dns1;
	struct in_addr dns2;
	char *uptime;
	char *state;
	char *gw_mac;
	char *opt43;
        char *opt42;
	char *opt12;
        char *opt2;
	char *lease_time;
	int ppp_session;
}WAN_CP_INFO_t;


void sal_wan_store_cp_info(int wan, WAN_CP_INFO_t *info);
int sal_wan_load_cp_info(int wan, WAN_CP_INFO_t *info);
char *sal_wan_get_lease_expires(int wan);
char *sal_wan_get_connection_time(int wan);

char *sal_wan_get_con_lcp_state_t(int wan);
int sal_wan_set_con_lcp_state_t(int wan, char *value);
char *sal_wan_get_con_mode_t(int wan);
int sal_wan_set_con_mode_t(int wan, char *value);

char *sal_wan_get_con_type_t(int wan);
int sal_wan_set_con_type_t(int wan, char *value);

char *sal_wan_get_con_ip_ver_type_t(int wan);
int sal_wan_set_con_ip_ver_type_t(int wan, char *value);
char *sal_wan_get_con_ipv6_pri_mode_t(int wan);
int sal_wan_set_con_ipv6_pri_mode_t(int wan, char *value);

char *sal_wan_get_l2_if_name_t(int wan);
int sal_wan_set_l2_if_name_t(int wan, char *value);

char *sal_wan_get_l2_untag_if_name_t(int wan);
int sal_wan_set_l2_untag_if_name_t(int wan, char *value);

char *sal_wan_get_wan_access_type_t(int wan);
int sal_wan_set_wan_access_type_t(int wan, char *value);

char *sal_wan_get_dsl_status_t(int wan);
int sal_wan_set_dsl_status_t(int wan, char *value);

char *sal_wan_get_dsl_link_status_t(int wan);
int sal_wan_set_dsl_link_status_t(int wan, char *value);

char *sal_wan_get_dsl_mode_t(int wan);
int sal_wan_set_dsl_mode_t(int wan, char *value);

char *sal_wan_get_con_gw_mac_t(int wan);
int sal_wan_set_con_gw_mac_t(int wan, char *value);
char *sal_wan_get_con_ppp_session_t(int wan);
int sal_wan_set_con_ppp_session_t(int wan, char *value);
char *sal_wan_get_con_ppp_trigger_t(int wan);
int sal_wan_set_con_ppp_trigger_t(int wan, char *value);

char *sal_wan_get_con_trigger_flag_t(int wan);
int sal_wan_set_con_trigger_flag_t(int wan, char *value);
char *sal_wan_get_con_uptime_t(int wan);
int sal_wan_set_con_uptime_t(int wan, char *value);
char *sal_wan_get_con_state_t(int wan);
int sal_wan_set_con_state_t(int wan, char *value);
int sal_wan_set_con_client_pid_t(int wan, char *value);
char *sal_wan_get_con_client_pid_t(int wan);
int sal_wan_set_con_auth_failed_t(int wan, char *value);
char *sal_wan_get_con_auth_failed_t(int wan);
int sal_wan_set_con_auth_fail_code_t(int wan, char *value);
char *sal_wan_get_con_auth_fail_code_t(int wan);
int sal_wan_set_con_error_log_code_t(int wan, char *value);
char *sal_wan_get_con_error_log_code_t(int wan);
int sal_wan_set_con_fail_code_t(int wan, char *value);
char *sal_wan_get_con_fail_code_t(int wan);
int sal_wan_set_con_auth_failed_info_t(int wan, char *value);
char *sal_wan_get_con_auth_failed_info_t(int wan);

char *sal_wan_get_con_hw_idle_t(int wan);
int sal_wan_set_con_hw_idle_t(int wan, char *value);

char *sal_wan_get_con_service_state_t(int wan);
int sal_wan_set_con_service_state_t(int wan, char *value);

char *sal_wan_get_con_ip_t(int wan);
int sal_wan_set_con_ip_t(int wan, char *value);
char *sal_wan_get_con_gw_t(int wan);
int sal_wan_set_con_gw_t(int wan, char *value);
char *sal_wan_get_con_ipmask_t(int wan);
int sal_wan_set_con_ipmask_t(int wan, char *value);
char *sal_wan_get_con_dns1_t(int wan);
int sal_wan_set_con_dns1_t(int wan, char *value);
char *sal_wan_get_con_dns2_t(int wan);
int sal_wan_set_con_dns2_t(int wan, char *value);
char *sal_wan_get_con_opt12_t(int wan);
int sal_wan_set_con_opt12_t(int wan, char *value);
char *sal_wan_get_con_opt42_t(int wan);
int sal_wan_set_con_opt42_t(int wan, char *value);
char *sal_wan_get_con_opt43_t(int wan);
int sal_wan_set_con_opt43_t(int wan, char *value);
char *sal_wan_get_con_opt2_t(int wan);
int sal_wan_set_con_opt2_t(int wan, char *value);

char *sal_wan_get_con_lease_t(int wan);
int sal_wan_set_con_lease_t(int wan, char *value);
char *sal_wan_get_con_dhcp_server_t(int wan);
int sal_wan_set_con_dhcp_server_t(int wan, char *value);

char *sal_wan_get_con_phy_init_t(int wan);
int sal_wan_set_con_phy_init_t(int wan, char *value);

char *sal_wan_get_ipv6_con_state_t(int wan);
int sal_wan_set_ipv6_con_state_t(int wan, char *value);
char *sal_wan_get_ipv6_con_uptime_t(int wan);
int sal_wan_set_ipv6_con_uptime_t(int wan, char *value);
char *sal_wan_get_ipv6_con_local_addr_t(int wan);
int sal_wan_set_ipv6_con_local_addr_t(int wan, char *value);
char *sal_wan_get_ipv6_con_remote_addr_t(int wan);
int sal_wan_set_ipv6_con_remote_addr_t(int wan, char *value);
char *sal_wan_get_ipv6_con_global_addr_t(int wan);
int sal_wan_set_ipv6_con_global_addr_t(int wan, char *value);
char *sal_wan_get_ipv6_con_assigned_prefix_t(int wan);
int sal_wan_set_ipv6_con_assigned_prefix_t(int wan, char *value);
char *sal_wan_get_ipv6_con_dns1_t(int wan);
int sal_wan_set_ipv6_con_dns1_t(int wan, char *value);
char *sal_wan_get_ipv6_con_dns2_t(int wan);
int sal_wan_set_ipv6_con_dns2_t(int wan, char *value);
char *sal_wan_get_ipv6_con_service_state_t(int wan);
int sal_wan_set_ipv6_con_service_state_t(int wan, char *value);
char *sal_wan_get_tmp_ppp_cfg_provider_name_t(int wan);
int sal_wan_set_tmp_ppp_cfg_provider_name_t(int wan, char *value);
char *sal_wan_get_tmp_ppp_cfg_user_name_t(int wan);
int sal_wan_set_tmp_ppp_cfg_user_name_t(int wan, char *value);
char *sal_wan_get_tmp_ppp_cfg_password_t(int wan);
int sal_wan_set_tmp_ppp_cfg_password_t(int wan, char *value);
#endif
