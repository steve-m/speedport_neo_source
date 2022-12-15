#ifndef _UTIL_SC_DRV_H_
#define _UTIL_SC_DRV_H_

#include "sc_drv/sc_drv.h"
#include "sc_drv/sc_drv_eth.h"

/* 
 * util_scDrv_get_eth_port_status()
 * return: -1 fail, 0 success
 * Result value will be saved in "eth_port_status".
*/
int util_scDrv_get_eth_port_status(ScDrv_Eth_Port_Status_t *eth_port_status);
/*
 * util_scDrv_get_eth_port_link_status()
 * return link_status code(SC_DRV_ETH_PORT_LINK_STATUS), or -1 if an error occurred.
 */
int util_scDrv_get_eth_port_link_status(int eth_port_id);
/*
 * util_scDrv_get_eth_port_duplex_mode()
 * return duplex_mode code(SC_DRV_ETH_PORT_DUPLEX_MODE), or -1 if an error occurred.
 */
int util_scDrv_get_eth_port_duplex_mode(int eth_port_id);
/*
 * util_scDrv_get_eth_port_rate()
 * return rate code(SC_DRV_ETH_PORT_RATE), or -1 if an error occurred.
 */
int util_scDrv_get_eth_port_rate(int eth_port_id);
/*
 * util_scDrv_get_eth_port_id_by_host_mac()
 * return port id(SC_DRV_ETH_PORT_ID), or -1 if an error occurred.
 */
int util_scDrv_get_eth_port_id_by_host_mac(unsigned char *mac);

#endif /* _UTIL_SC_DRV_H_ */
