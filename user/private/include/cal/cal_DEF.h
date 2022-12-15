#ifndef _CAL_DEF_H_
#define _CAL_DEF_H_

/* Define */
#define WAN_DEFAULT_ETHERNET_LINK           1
#define LAN_DEFAULT_ETHERNET_LINK           2

#define PPPOE_WAN_DEFAULT_IP_INTERFACE      1
#define DHCPC_WAN_DEFAULT_IP_INTERFACE      2
#if defined(SC_CUSTOMER_MT)
#define LAN_DEFAULT_IP_INTERFACE            4
#else
#define LAN_DEFAULT_IP_INTERFACE            3
#endif

#define PPPOE_DEFAULT_WAN_ID                1
#define DHCPC_DEFAULT_WAN_ID                2
#define DSL_DEFAULT_LINE_ID                 1

#define DSL_WAN_IF_NAME                     "nas1"
#define VDSL_WAN_IF_NAME                    "ptm0"
#if defined(SC_CUSTOMER_MT)
#define ETH_WAN_IF_NAME                     "eth1"
#else
#define ETH_WAN_IF_NAME                     "eth5"
#endif

#define LAN_DEFAULT_DHCPD_PROFILE            1



#endif //CAL_DEF_H
