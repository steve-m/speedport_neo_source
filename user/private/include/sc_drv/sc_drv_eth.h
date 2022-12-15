
#ifndef	_SC_DRV_ETH_H_
#define	_SC_DRV_ETH_H_

#include "sc_drv_types.h"

typedef enum
{
    SC_DRV_ETH_PORT_ID_NONE = 0,
    SC_DRV_ETH_PORT_1_ID,
    SC_DRV_ETH_PORT_2_ID,
    SC_DRV_ETH_PORT_3_ID,
    SC_DRV_ETH_PORT_4_ID,
    SC_DRV_ETH_PORT_ID_LAST
} SC_DRV_ETH_PORT_ID ;

typedef enum
{
    SC_DRV_ETH_PORT_LINK_DOWN = 0,
    SC_DRV_ETH_PORT_LINK_UP,
    SC_DRV_ETH_PORT_LINK_LAST
} SC_DRV_ETH_PORT_LINK_STATUS;

typedef enum
{
    SC_DRV_ETH_PORT_DUPLEX_MODE_FULL = 0,
    SC_DRV_ETH_PORT_DUPLEX_MODE_HALF,
    SC_DRV_ETH_PORT_DUPLEX_MODE_LAST
} SC_DRV_ETH_PORT_DUPLEX_MODE;

typedef enum
{
	SC_DRV_ETH_PORT_RATE_10	    = 0,	/* 10	Mb/s */
	SC_DRV_ETH_PORT_RATE_100	= 2,	/* 100	Mb/s */
	SC_DRV_ETH_PORT_RATE_1000	= 4,	/* 1000	Mb/s */
	SC_DRV_ETH_PORT_RATE_AUTO	= 8,	/* 1000	Mb/s */
	SC_DRV_ETH_PORT_RATE_LAST
}SC_DRV_ETH_PORT_RATE;

typedef struct _ScDrv_Eth_Port_Status
{
    int port_id;        /* SC_DRV_ETH_PORT_ID */
    int link_status;    /* SC_DRV_ETH_PORT_LINK_STATUS */
    int duplex_mode;    /* SC_DRV_ETH_PORT_DUPLEX_MODE */
    int rate;           /* SC_DRV_ETH_PORT_DUPLEX_MODE */
} ScDrv_Eth_Port_Status_t;

typedef struct _ScDrv_Host_Eth_Info
{
    char host_mac[SC_DRV_MAC_LEN];
    int port_id; /* SC_DRV_ETH_PORT_ID */
} ScDrv_Host_Eth_Info_t;

typedef struct _ScDrv_Eth_Port_Stats
{
    int port_id; /* SC_DRV_ETH_PORT_ID */
    unsigned long rx_bytes;
    unsigned long rx_pkts;
    unsigned long rx_err_pkts;
    unsigned long rx_mcast_pkts;
    unsigned long rx_bcast_pkts;
    unsigned long tx_bytes;
    unsigned long tx_pkts;
    unsigned long tx_err_pkts;
    unsigned long tx_mcast_pkts;
    unsigned long tx_bcast_pkts;
} ScDrv_Eth_Port_Stats_t;


#endif /* _SC_DRV_ETH_H_ */

