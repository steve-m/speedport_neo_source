/**
 * @file   cal_wan.h
 * @author Martin_Huang@sdc.sercomm.com
 * @date   2011-09-01
 * @brief
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
#ifndef __CAL_WAN_H__
#define __CAL_WAN_H__

#include <netinet/in.h>

#define DEFAULT_WANDEV_ID	1
#define CAL_WAN_MIN_NUM		1
#if defined(SC_CUSTOMER_MT)
#define CAL_WAN_MAX_NUM		3
#else
#define CAL_WAN_MAX_NUM		2
#endif
#define CAL_WAN_SERVICE_NUM	4

#define WAN_CFG_BASE			"/tmp/0/"
#define CAL_WAN_ACCESS_TYPE_GPON 	"GPON"
#define CAL_WAN_ACCESS_TYPE_ETHER 	"Ethernet"
#define CAL_WAN_ACCESS_TYPE_DSL 	"DSL"
#define CAL_WAN_ACCESS_TYPE_VDSL 	"VDSL"
#define CAL_WAN_ACCESS_TYPE_VIB 	"VIB"

#define CAL_WAN_HOST				"Unconfigured"
#define CAL_WAN_ROUTE				"IP_Routed"
#define CAL_WAN_PPPOE_BRIDGE		"PPPoE_Bridged"
#define CAL_WAN_IPOE_BRIDGE			"IP_Bridged"

#define CAL_WAN_CON_MODE_PPPOE		"PPPoE"
#define CAL_WAN_CON_MODE_PPPOA		"PPPoA"
#define CAL_WAN_CON_MODE_PPPOS		"PPPoS"
#define CAL_WAN_CON_MODE_STATIC		"Static"
#define CAL_WAN_CON_MODE_DHCP		"DHCP"

#define CAL_ENABLE			"1"
#define CAL_DISABLE			"0"
#define CAL_LINK_ON			"1"
#define CAL_LINK_OFF	    "0"
#define CAL_WAN_PPP_DOD			"OnDemand"
#define CAL_WAN_PPP_ALWAYSON		"AlwaysOn"
#define CAL_WAN_PPP_MANUAL		"Manual"



#define CAL_WAN_INVALID_PBIT		"-1"

#define BRCTL                           "/usr/sbin/brctl"
#define IFCONFIG		        "/sbin/ifconfig"
#define VCONFIG				"/sbin/vconfig"
#define DHCPD				"/usr/sbin/udhcpd"
#define KILLALL				"/usr/bin/killall"
#define PPPD				"/usr/sbin/pppd"
#define RC				"/usr/sbin/rc"
#define IPROUTE2_CONFIG			"/usr/sbin/iproute2_config"

#define DHCPC				"udhcpc"

#define CAL_WAN_SERVICE_TYPE_DATA	"DATA"
#define CAL_WAN_SERVICE_TYPE_VOIP	"VOIP"
#define CAL_WAN_SERVICE_TYPE_MGNT	"MGNT"
#define CAL_WAN_SERVICE_TYPE_OTHER	"IPTV"
#define CAL_WAN_SERVICE_TYPE_IPTV	"IPTV"

#ifndef SERVICE_DATA

#define SERVICE_DATA		(0x1 << 0)
#define SERVICE_VOIP		(0x1 << 1)
#define SERVICE_MGNT		(0x1 << 2)
#define SERVICE_OTHER		(0x1 << 3)
#define SERVICE_IPTV		(0x1 << 3)

#define SERVICE_ALL (SERVICE_DATA | SERVICE_VOIP | SERVICE_MGNT | SERVICE_OTHER | SERVICE_IPTV)

#endif

typedef struct tag_PPP_CON_PROFILE{
	char *l2_type;
        char *l2_if_name;
        char *l2_untag_if_name;
	char *enable;
	char *connection_type;
	char *name;
	char *transport_type;
	char *nat_enable;
	char *user_name;
	char *password;
	char *max_mru;
	char *mac;
	char *ac_name;
	char *service_name;
	char *connection_trigger;
	char *idle_time;
        char *ipv4_idle_timer;
	char *lcp_echo;
	char *lcp_retry;
	char *ip;
	char *dns_enable;
	char *dns_override;
	char *dns_servers;
	char *if_name;
	char *vlan_id;
	char *cid;
} PPP_CON_PROFILE_t;

typedef struct tag_IP_CON_PROFILE{
	char *l2_type;
	char *l2_if_name;
	char *enable;
	char *connection_type;
	char *name;
	char *address_type;
	char *nat_enable;
	char *ip;
	char *subnetmask;
	char *gateway;
	char *max_mtu;
	char *mac;
	char *dns_enable;
	char *dns_override;
	char *dns_servers;
	char *if_name;
	char *vlan_id;
	char *cid;
	char *host_name;
	char *client_id;
	char *vendor_id;
	char *user_class;
        char *option2_source_ntp;
        char *option42_source_ntp;
        char *option2_en;
	char *option12_en;
	char *option43_en;
        char *option42_en;
        char *option50_en;
        char *option51_en;
        char *option121_en;
} IP_CON_PROFILE_t;

#define HCAL_WAN_IS_VALID_WAN_ID(wan_id) (((wan_id) >=0 && (wan_id) < CAL_WAN_MAX_NUM) ? 1 : 0)

int hcal_wan_map_wandev_id_str_to_uwan_id(char *id_stack_str);

int hcal_revert_connection(int wan, void *profile, int is_ppp);

int hcal_wan_set_default_con_service(int wan);
/*
 *  success wanid
 *  otherwise -1
 *
 * */
int hcal_get_default_con_service(void);
int hcal_wan_is_data_wan_non_bridge(void);

/*
 *  success wanid
 *  otherwise -1
 *
 * */
int hcal_get_default_wan_id(void);

char *hcal_wan_get_basic_if(int wan);
char *hcal_wan_get_basic_dsl_if(int wan);
char *hcal_wan_get_basic_eth_if(int wan);
int hcal_is_wan_if_unUsed(char *ifName);


int hcal_add_ppp_connection(int wan, PPP_CON_PROFILE_t *ppp_con_profile);
int hcal_del_ppp_connection(int wan);
int hcal_add_ip_connection(int wan, IP_CON_PROFILE_t *ip_con_profile);
int hcal_del_ip_connection(int wan);
int hcal_load_ppp_profile(int wan, PPP_CON_PROFILE_t *ppp_con_profile);
int hcal_load_ip_profile(int wan, IP_CON_PROFILE_t *ip_con_profile);


char *hcal_wan_get_name(int wan);
void hcal_wan_set_name(int wan, char *value);
char *hcal_wan_get_enable(int wan);
void hcal_wan_set_enable(int wan, char *value);
char *hcal_wan_get_nat_enable(int wan);
void hcal_wan_set_nat_enable(int wan, char *value);
char *hcal_wan_get_mode(int wan);
void hcal_wan_set_mode(int wan, char *value);
char *hcal_wan_get_con_type(int wan);
void hcal_wan_set_con_type(int wan, char *value);
char *hcal_wan_get_if_name(int wan);
void hcal_wan_set_if_name(int wan, char *value);
char *hcal_wan_get_mtu(int wan);
void hcal_wan_set_mtu(int wan, char *value);
char *hcal_wan_get_ip_vendor_id(int wan);
void hcal_wan_set_ip_vendor_id(int wan, char *value);
char *hcal_wan_get_ppp_service_name(int wan);
void hcal_wan_set_ppp_service_name(int wan, char *value);
char *hcal_wan_get_ppp_ac_name(int wan);
void hcal_wan_set_ppp_ac_name(int wan, char *value);
char *hcal_wan_get_ppp_trigger(int wan);
void hcal_wan_set_ppp_trigger(int wan, char *value);
char *hcal_wan_get_ppp_idle_time(int wan);
void hcal_wan_set_ppp_idle_time(int wan, char *value);
char *hcal_wan_get_ppp_user_name(int wan);
void hcal_wan_set_ppp_user_name(int wan, char *value);
char *hcal_wan_get_ppp_password(int wan);
void hcal_wan_set_ppp_password(int wan, char *value);

char *hcal_wan_get_ppp_lcp_echo(int wan);
void hcal_wan_set_ppp_lcp_echo(int wan, char *value);
char *hcal_wan_get_ppp_lcp_retry(int wan);
void hcal_wan_set_ppp_lcp_retry(int wan, char *value);

char *hcal_wan_get_ip_addr(int wan);
void hcal_wan_set_ip_addr(int wan, char *value);
char *hcal_wan_get_gateway(int wan);
void hcal_wan_set_gateway(int wan, char *value);

char *hcal_wan_get_ip_net_mask(int wan);
void hcal_wan_set_ip_net_mask(int wan, char *value);
char *hcal_wan_get_ip_host_name(int wan);
void hcal_wan_set_ip_host_name(int wan, char *value);

char *hcal_wan_get_ip_client_id(int wan);
void hcal_wan_set_ip_client_id(int wan, char *value);

char *hcal_wan_get_ip_user_class(int wan);
void hcal_wan_set_ip_user_class(int wan, char *value);

char *hcal_wan_get_dns_enable(int wan);
void hcal_wan_set_dns_enable(int wan, char *value);
char *hcal_wan_get_dns_override(int wan);
void hcal_wan_set_dns_override(int wan, char *value);


char *hcal_wan_get_dns_servers(int wan);
void hcal_wan_set_dns_servers(int wan, char *value);
char *hcal_wan_get_mac_addr(int wan);
void hcal_wan_set_mac_addr(int wan, char *value);
char *hcal_wan_get_termination_vlanid(int wan);
void hcal_wan_set_termination_vlanid(int wan, char *value);

char *hcal_wan_get_dscp(int wan);
void hcal_wan_set_dscp(int wan, char *value);

char *hcal_wan_get_ip_option2_source_ntp(int wan);
void hcal_wan_set_ip_option2_source_ntp(int wan, char *value);

char *hcal_wan_get_ip_option42_source_ntp(int wan);
void hcal_wan_set_ip_option42_source_ntp(int wan, char *value);

char *hcal_wan_get_ip_option2_enable(int wan);
void hcal_wan_set_ip_option2_enable(int wan, char *value);

char *hcal_wan_get_ip_option42_enable(int wan);
void hcal_wan_set_ip_option42_enable(int wan, char *value);

char *hcal_wan_get_ip_option43_enable(int wan);
void hcal_wan_set_ip_option43_enable(int wan, char *value);
char *hcal_wan_get_ip_option12_enable(int wan);
void hcal_wan_set_ip_option12_enable(int wan, char *value);

int hcal_wan_get_service_list(int wan);
void hcal_wan_set_service_list(int wan, int v);
char *hcal_wan_get_service_name_string(int service);

char *hcal_wan_get_id(int wan);
void hcal_wan_set_id(int wan, char *value);

char *hcal_wan_get_ppp_max_auth(int wan);
void hcal_wan_set_ppp_max_auth(int wan, char *value);

char *hcal_wan_get_ppp_idle_time(int wan);
void hcal_wan_set_ppp_idle_time(int wan, char *value);

char *hcal_wan_get_access_type(int wan);
//void hcal_wan_set_access_type(int wan, char *value);
char *hcal_wan_get_marking_pbit(int wan);
void hcal_wan_set_marking_pbit(int wan, char *value);
char *hcal_wan_get_arpping_enable(int wan);
void hcal_wan_set_arpping_enable(int wan, char *value);
char *hcal_wan_get_arpping_timeout(int wan);
void hcal_wan_set_arpping_timeout(int wan, char *value);
char *hcal_wan_get_arpping_maxfail(int wan);
void hcal_wan_set_arpping_maxfail(int wan, char *value);
 

char *cal_wan_get_connection_uri(void *id, int is_ppp);
void cal_wan_get_dev_id(void *id, char* value);
char* hcal_wan_id_map_uri(int wan_id);
int hcal_wan_uri_map_id(char* value);
int hcal_wan_pattern_xxx_map_id(char *value);
int hcal_wan_pattern_map_id(char *value);

char* hcal_list_visible_wan_name(int serviceType);
char* hcal_list_visible_non_bridge_wan_name(int serviceType);

char *hcal_wan_gpon_get_serial_number(int wan_id);
char *hcal_wan_gpon_get_password(int wan_id);
char *hcal_wan_gpon_get_default_state(int wan_id);
int hcal_wan_gpon_set_serial_number(int wan_id, char *value);
int hcal_wan_gpon_set_password(int wan_id, char *value);
int hcal_wan_gpon_set_default_state(int wan_id, char *value);
/*fix me */
#define DATA_WAN_VID hcal_wan_get_termination_vlanid(0)
#define IPTV_UNI_VID hcal_wan_get_termination_vlanid(3)
#define IPTV_STREAM_VID  99
#define UNUSED_VLAN    4094
#endif

