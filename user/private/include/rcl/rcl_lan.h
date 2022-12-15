
#ifndef _RCL_LAN_H_
#define _RCL_LAN_H_

#define DHCP_LEASE_TIME_IN_UNCONFIGRED_MODE 60      //seconds
#define DHCP_LEASE_TIME_DEFAULT             1814400 //seconds
#define DHCP_DEFAULT_MAX_LEASES             253
int rcl_lan_dhcpd_cfg_create(void);
int rcl_lan_dhcpd_cfg_reload(void);
int rcl_lan_dhcpd_start(void);
int rcl_lan_dhcpd_stop(void);
int rcl_lan_static_ip_start();

#endif /* _RCL_LAN_H_ */
