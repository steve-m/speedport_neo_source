/**
 * @file   rcl_wan.h
 * @author Martin_Huang@sdc.sercomm.com
 * @date   2011-08-29
 * @brief  WAN rc layer API 
 *
 * Copyright - 2010 SerComm Corporation. All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document without notice.
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising
 * out of the application or use of any product or circuit. SerComm Corporation specifically
 * disclaims any and all liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of others.
 */
#ifndef __RCL_WAN_H__
#define __RCL_WAN_H__

int rcl_init_default_gpon_settings(void);
int rcl_stop_phy(int wan_id);
int rcl_start_phy(int wan_id);
int rcl_stop_gpon_debug(void);
int rcl_start_gpon_debug(void);
int rcl_stop_arpping(int wan_id);
int rcl_start_arpping(int wan_id);

int rcl_stop_gmp(int wan_id);
int rcl_start_gmp(int wan_id);
int rcl_stop_hwim(int wan_id);
int rcl_start_hwim(int wan_id);
int rcl_start_wan(int wan_id);
int rcl_stop_wan(int wan_id);
int rcl_start_wanif(void);
int rcl_stop_wanif(void);
int rcl_start_dsl(void);
int rcl_stop_dsl(void);
int rcl_start_cpm(int wan_id);
int rcl_stop_cpm(int wan_id);
int rcl_start_wan_service(int wan_id, char* ip_version, char *);
int rcl_stop_wan_service(int wan_id, char* ip_version, char *);
int rcl_init_wan_env(int wan_id);
int rcl_init_wans_env(void);
#endif
