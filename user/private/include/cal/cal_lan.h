
#ifndef _CAL_LAN_H_
#define _CAL_LAN_H_



char* cal_lan_cfg_passwd_get();
int cal_lan_cfg_passwd_set(char* val);
int cal_lan_host_entry_get(int id, void **);
int cal_lan_host_entry_set(int id, void *);
int cal_lan_host_entry_del(int id);
char* cal_lan_dhcp_server_enable_get();
int cal_lan_dhcp_server_enable_set(char* val);
char* cal_lan_dhcp_conserv_enable_get();
int cal_lan_dhcp_conserv_enable_set(char* val);
char* cal_lan_dhcp_conserv_interface_get();
int cal_lan_dhcp_conserv_interface_set(char* val);
char* cal_lan_dhcp_conserv_vendor_id_get();
int cal_lan_dhcp_conserv_vendor_id_set(char* val);
char* cal_lan_dhcp_conserv_mac_get();
int cal_lan_dhcp_conserv_mac_set(char* val);
char* cal_lan_dhcp_server_start_ip_get();
int cal_lan_dhcp_server_start_ip_set(char* val);
char* cal_lan_dhcp_server_end_ip_get();
int cal_lan_dhcp_server_end_ip_set(char* val);
char* cal_lan_dhcp_server_lease_time_get();
int cal_lan_dhcp_server_lease_time_set(char* val);
char* cal_lan_dhcp_static_addr_devname_get();
int cal_lan_dhcp_static_addr_devname_set(char* val);
char* cal_lan_dhcp_static_addr_mac_get();
int cal_lan_dhcp_static_addr_mac_set(char* val);
char* cal_lan_dhcp_static_addr_ipaddr_get();
int cal_lan_dhcp_static_addr_ipaddr_set(char* val);
char* cal_lan_dhcp_server_option_tag_get();
int cal_lan_dhcp_server_option_tag_set(char* val);
char* cal_lan_dhcp_server_option_value_get();
int cal_lan_dhcp_server_option_value_set(char* val);
char* cal_lan_get();
int cal_lan_host_entry_ipv4_get(int hostid, int id, void **);
int cal_lan_host_entry_ipv4_set(int hostid, int id, void *);
int cal_lan_host_entry_ipv4_del(int hostid, int id);
int cal_lan_host_entry_ipv6_get(int hostid, int id, void **);
int cal_lan_host_entry_ipv6_set(int hostid, int id, void *);
int cal_lan_host_entry_ipv6_del(int hostid, int id);
int cal_lan_dhcp_server_client_list_get(int pool_id, int id, void **);
int cal_lan_dhcp_server_client_list_set(int pool_id, int id, void *);
int cal_lan_dhcp_server_client_list_del(int pool_id, int id);
int cal_lan_dhcp_server_client_ipv4_list_get(int pool_id, int client_id, int id, void **);
int cal_lan_dhcp_server_client_ipv4_list_set(int pool_id, int client_id, int id, void *);
int cal_lan_dhcp_server_client_ipv4_list_del(int pool_id, int client_id, int id);
int update_lan_hosts_info(char *buf);
/*to add here*/




typedef enum
{
#if defined(SC_CUSTOMER_MT)
    CAL_LAN_DEVICE_ID_DEFAULT = 4,
#else
    CAL_LAN_DEVICE_ID_DEFAULT = 3,
#endif
} CAL_LAN_DEVICE_ID;

typedef enum
{
    CAL_LAN_SUBNET_ID_MAIN = 0,
#if 0
    CAL_LAN_SUBNET_ID_2,
    CAL_LAN_SUBNET_ID_3,
    CAL_LAN_SUBNET_ID_4,
#endif
    CAL_LAN_SUBNET_ID_END
}CAL_LAN_SUBNET_ID;

typedef enum
{
    CAL_LAN_DHCP_OPTION_ID_6 = 1,
    CAL_LAN_DHCP_OPTION_ID_12,
    CAL_LAN_DHCP_OPTION_ID_15,
    CAL_LAN_DHCP_OPTION_ID_42,
    CAL_LAN_DHCP_OPTION_ID_66,
    CAL_LAN_DHCP_OPTION_ID_120,
    CAL_LAN_DHCP_OPTION_ID_240,
    CAL_LAN_DHCP_OPTION_ID_241,
    CAL_LAN_DHCP_OPTION_ID_242,
    CAL_LAN_DHCP_OPTION_ID_243,
    CAL_LAN_DHCP_OPTION_ID_244,
    CAL_LAN_DHCP_OPTION_ID_245,
    CAL_LAN_DHCP_OPTION_ID_246,
    CAL_LAN_DHCP_OPTION_ID_247,
    CAL_LAN_DHCP_OPTION_ID_248,
    CAL_LAN_DHCP_OPTION_ID_250,
    CAL_LAN_DHCP_OPTION_ID_END
}CAL_LAN_DHCP_OPTION_ID;

#define CAL_LAN_CONFIG_LEN_MAX 256

/*****************************************************************************

Function: cal_lan_get_xxx()
          Return: 1) NULL -- get error
                  2) A static buffer pointer, which include the value string.

Function: cal_lan_set_xxx()
          Return: 1) 0  -- success
                  2) !0 -- fail
                  
Parameters:
          int lanDev_id      -- defined in enum CAL_LAN_DEVICE_ID
                           
          int lanSub_id      -- defined in enum CAL_LAN_SUBNET_ID
          
          int dhcpTag_id     -- defined in enum CAL_LAN_DHCP_OPTION_ID
          
          int dhcpStatic_id  -- range: 1 to atoi(cal_lan_get_dhcp_static_address_num(...))
          
******************************************************************************/
char *cal_lan_get_enable(int lanDev_id, int lanSub_id);
int   cal_lan_set_enable(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_if_name(int lanDev_id, int lanSub_id);
int   cal_lan_set_if_name(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_ip_address(int lanDev_id, int lanSub_id);
int   cal_lan_set_ip_address(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_subnet_mask(int lanDev_id, int lanSub_id);
int   cal_lan_set_subnet_mask(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_dhcp_server_enable(int lanDev_id, int lanSub_id);
int   cal_lan_set_dhcp_server_enable(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_dhcp_start_ip(int lanDev_id, int lanSub_id);
int   cal_lan_set_dhcp_start_ip(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_dhcp_end_ip(int lanDev_id, int lanSub_id);
int   cal_lan_set_dhcp_end_ip(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_dhcp_reserved_address(int lanDev_id, int lanSub_id);
int   cal_lan_set_dhcp_reserved_address(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_dhcp_lease_time(int lanDev_id, int lanSub_id);
int   cal_lan_set_dhcp_lease_time(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_dns_proxy_enable(int lanDev_id, int lanSub_id);
int   cal_lan_set_dns_proxy_enable(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_rip_version(int lanDev_id, int lanSub_id);
int   cal_lan_set_rip_version(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_rip_direction(int lanDev_id, int lanSub_id);
int   cal_lan_set_rip_direction(int lanDev_id, int lanSub_id, char *value);

char *cal_lan_get_dhcp_option_tag(int lanDev_id, int lanSub_id, int dhcpTag_id);
char *cal_lan_get_dhcp_option_value(int lanDev_id, int lanSub_id, int dhcpTag_id);
int   cal_lan_set_dhcp_option_value(int lanDev_id, int lanSub_id, int dhcpTag_id, char *value);

char *cal_lan_get_conserv_enable(int lanDev_id, int lanSub_id);
int   cal_lan_set_conserv_enable(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_conserv_source_interface(int lanDev_id, int lanSub_id);
int   cal_lan_set_conserv_source_interface(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_conserv_vendor_id(int lanDev_id, int lanSub_id);
int   cal_lan_set_conserv_vendor_id(int lanDev_id, int lanSub_id, char *value);
char *cal_lan_get_conserv_mac(int lanDev_id, int lanSub_id);
int   cal_lan_set_conserv_mac(int lanDev_id, int lanSub_id, char *value);

char *cal_lan_get_dhcp_static_address_num(int lanDev_id, int lanSub_id);
char *cal_lan_get_dhcp_static_address_device_name(int lanDev_id, int lanSub_id, int dhcpStatic_id);
int   cal_lan_set_dhcp_static_address_device_name(int lanDev_id, int lanSub_id, int dhcpStatic_id, char *value);
char *cal_lan_get_dhcp_static_address_mac(int lanDev_id, int lanSub_id, int dhcpStatic_id);
int   cal_lan_set_dhcp_static_address_mac(int lanDev_id, int lanSub_id, int dhcpStatic_id, char *value);
char *cal_lan_get_dhcp_static_address_ip(int lanDev_id, int lanSub_id, int dhcpStatic_id);
int   cal_lan_set_dhcp_static_address_ip(int lanDev_id, int lanSub_id, int dhcpStatic_id, char *value);
int   cal_lan_add_dhcp_static_address_entry(int lanDev_id, int lanSub_id, int dhcpStatic_id);
int   cal_lan_del_dhcp_static_address_entry(int lanDev_id, int lanSub_id, int dhcpStatic_id);

char *cal_lan_get_dhcpd_lease_file_name(int lanDev_id, int lanSub_id);

/* Instead of old api */
int cal_lan_get_ip_inet_addr(void);
int cal_lan_get_netmask_inet_addr(void);


/* lan hosts */
char *cal_lan_get_host_num(int lanDev_id);
char *cal_lan_get_host_ip_address(int lanDev_id, int host_id);
int   cal_lan_set_host_ip_address(int lanDev_id, int host_id, char *value);
char *cal_lan_get_host_address_source(int lanDev_id, int host_id);
int   cal_lan_set_host_address_source(int lanDev_id, int host_id, char *value);
char *cal_lan_get_host_lease_time_remaining(int lanDev_id, int host_id);
int   cal_lan_set_host_lease_time_remaining(int lanDev_id, int host_id, char *value);
char *cal_lan_get_host_mac_address(int lanDev_id, int host_id);
int   cal_lan_set_host_mac_address(int lanDev_id, int host_id, char *value);
char *cal_lan_get_host_name(int lanDev_id, int host_id);
int   cal_lan_set_host_name(int lanDev_id, int host_id, char *value);
char *cal_lan_get_host_active(int lanDev_id, int host_id);
int   cal_lan_set_host_active(int lanDev_id, int host_id, char *value);
int   cal_lan_add_host_entry(int lanDev_id, int host_id);
int   cal_lan_del_host_entry(int lanDev_id, int host_id);
/*lan ports*/
typedef struct tag_LAN_PORTS_PARA{
    char enable;
    char multicast_vid_list[512];
}LAN_PORTS_PARA_t;

int cal_lan_get_ports_paras(int port_num, LAN_PORTS_PARA_t *paras);
char *cal_lan_get_port_enable(int lanDev_id, int port_id);
int cal_lan_set_port_enable(int lanDev_id, int port_id, char *value);
char *cal_lan_get_port_multicast_vid_list(int lanDev_id, int port_id);
int cal_lan_set_port_multicast_vid_list(int lanDev_id, int port_id, char *value);


#endif /* _CAL_LAN_H_ */

