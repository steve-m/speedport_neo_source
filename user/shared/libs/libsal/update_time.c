#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sc_nvram.h>

/*
	Marc add to record the time of update object.
*/
#define SAL_UPDATE_TIME_VALUE_MAX_LENGTH	256
#define SAL_UPDATE_TIME_PATH_MAX_LENGTH		256

#define UPDATE_TIME_CFG_BASE "/tmp/update_time.sal"

#define NVRAN_GET_UPDATE_TIME_FUNC(funcname, name, buffer)\
char *funcname(void)\
{\
	{\
		static char buffer[SAL_UPDATE_TIME_VALUE_MAX_LENGTH];\
		char *p;\
		char update_time_nvram_path[SAL_UPDATE_TIME_PATH_MAX_LENGTH];\
    	snprintf(update_time_nvram_path, sizeof(update_time_nvram_path), UPDATE_TIME_CFG_BASE);\
    	buffer[0] = '\0';\
		p = nvram_get_fun(name, update_time_nvram_path);\
		if(p)\
		{\
			snprintf(buffer, sizeof(buffer), "%s", p);\
			free(p);\
		}\
		return buffer;\
	}\
}

#define NVRAN_SET_UPDATE_TIME_FUNC(funcname, name)\
int funcname(char *value)\
{\
	{\
		char update_time_nvram_path[SAL_UPDATE_TIME_PATH_MAX_LENGTH];\
		if(!value)\
			return -1;\
    	snprintf(update_time_nvram_path, sizeof(update_time_nvram_path), UPDATE_TIME_CFG_BASE);\
		return nvram_set_p(update_time_nvram_path, name, value);\
	}\
}


#define SAL_UPDATE_TIME_PROCESS_STATUS     "process_status"
#define SAL_UPDATE_TIME_DNS_RELAY_FORWARDING     "dns_relay_forwarding"
#define SAL_UPDATE_TIME_DNS_CLIENT_SERVER     "dns_client_server"
#define SAL_UPDATE_TIME_ROUTING_FORWARDING     "routing_forwarding"
#define SAL_UPDATE_TIME_DHCPV4_SERVER_CLIENT     "dhcpv4_server_client"
#define SAL_UPDATE_TIME_DHCPV6_CLIENT_RECEIVEDOPTION     "dhcpv6_client_receivedoption"
#define SAL_UPDATE_TIME_DHCPV6_SERVER_POOL_CLIENT     "dhcpv6_server_pool_client"
#define SAL_UPDATE_TIME_USB_PORT     "usb_port"
#define SAL_UPDATE_TIME_USB_HOST_INFO     "usb_host_info"
#define SAL_UPDATE_TIME_LAN_HOSTS_INFO     "lan_hosts_info"
#define SAL_UPDATE_TIME_MGNT_DEV_STATUS     "mgnt_dev_status"
#define SAL_UPDATE_TIME_MGNT_DEV_NUM     "mgnt_dev_num"
#define SAL_UPDATE_TIME_ACCESSPOINT1_STA_STATUS     "ap1_sta_status"
#define SAL_UPDATE_TIME_ACCESSPOINT2_STA_STATUS     "ap2_sta_status"
#define SAL_UPDATE_TIME_ACCESSPOINT3_STA_STATUS     "ap3_sta_status"
#define SAL_UPDATE_TIME_ACCESSPOINT4_STA_STATUS     "ap4_sta_status"
#ifdef _SC_HOMEPLUG_
#define SAL_UPDATE_TIME_HOMEPLUG_ASSOCDEVS  "homeplug_assocdevs"
#endif


NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_process_status, SAL_UPDATE_TIME_PROCESS_STATUS, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_process_status, SAL_UPDATE_TIME_PROCESS_STATUS)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_dns_relay_forwarding, SAL_UPDATE_TIME_DNS_RELAY_FORWARDING, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_dns_relay_forwarding, SAL_UPDATE_TIME_DNS_RELAY_FORWARDING)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_dns_client_server, SAL_UPDATE_TIME_DNS_CLIENT_SERVER, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_dns_client_server, SAL_UPDATE_TIME_DNS_CLIENT_SERVER)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_routing_forwarding, SAL_UPDATE_TIME_ROUTING_FORWARDING, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_routing_forwarding, SAL_UPDATE_TIME_ROUTING_FORWARDING)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_dhcpv4_server_client, SAL_UPDATE_TIME_DHCPV4_SERVER_CLIENT, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_dhcpv4_server_client, SAL_UPDATE_TIME_DHCPV4_SERVER_CLIENT)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_dhcpv6_client_receivedoption, SAL_UPDATE_TIME_DHCPV6_CLIENT_RECEIVEDOPTION, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_dhcpv6_client_receivedoption, SAL_UPDATE_TIME_DHCPV6_CLIENT_RECEIVEDOPTION)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_dhcpv6_server_pool_client, SAL_UPDATE_TIME_DHCPV6_SERVER_POOL_CLIENT, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_dhcpv6_server_pool_client, SAL_UPDATE_TIME_DHCPV6_SERVER_POOL_CLIENT)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_usb_port, SAL_UPDATE_TIME_USB_PORT, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_usb_port, SAL_UPDATE_TIME_USB_PORT)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_usb_host_info, SAL_UPDATE_TIME_USB_HOST_INFO, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_usb_host_info, SAL_UPDATE_TIME_USB_HOST_INFO)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_lan_hosts_info, SAL_UPDATE_TIME_LAN_HOSTS_INFO, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_lan_hosts_info, SAL_UPDATE_TIME_LAN_HOSTS_INFO)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_mgnt_dev_status, SAL_UPDATE_TIME_MGNT_DEV_STATUS, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_mgnt_dev_status, SAL_UPDATE_TIME_MGNT_DEV_STATUS)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_mgnt_dev_num, SAL_UPDATE_TIME_MGNT_DEV_NUM, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_mgnt_dev_num, SAL_UPDATE_TIME_MGNT_DEV_NUM)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_accesspoint1_sta_status, SAL_UPDATE_TIME_ACCESSPOINT1_STA_STATUS, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_accesspoint1_sta_status, SAL_UPDATE_TIME_ACCESSPOINT1_STA_STATUS)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_accesspoint2_sta_status, SAL_UPDATE_TIME_ACCESSPOINT2_STA_STATUS, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_accesspoint2_sta_status, SAL_UPDATE_TIME_ACCESSPOINT2_STA_STATUS)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_accesspoint3_sta_status, SAL_UPDATE_TIME_ACCESSPOINT3_STA_STATUS, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_accesspoint3_sta_status, SAL_UPDATE_TIME_ACCESSPOINT3_STA_STATUS)
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_accesspoint4_sta_status, SAL_UPDATE_TIME_ACCESSPOINT4_STA_STATUS, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_accesspoint4_sta_status, SAL_UPDATE_TIME_ACCESSPOINT4_STA_STATUS)
#ifdef _SC_HOMEPLUG_
NVRAN_GET_UPDATE_TIME_FUNC(sal_update_time_get_homeplug_assocdevs, SAL_UPDATE_TIME_HOMEPLUG_ASSOCDEVS, update_time)
NVRAN_SET_UPDATE_TIME_FUNC(sal_update_time_set_homeplug_assocdevs, SAL_UPDATE_TIME_HOMEPLUG_ASSOCDEVS)
#endif
