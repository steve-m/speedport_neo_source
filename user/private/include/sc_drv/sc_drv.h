
#ifndef	_SC_DRV_H_
#define	_SC_DRV_H_


#define SC_DRV_STR  "scDrv"
#define SC_DRV_FD_NAME_STR  "/dev/"SC_DRV_STR


typedef enum
{
    SC_DRV_IOCTL_NONE_CMD = 0,
    SC_DRV_IOCTL_GET_ETH_PORT_STATUS_CMD,
    SC_DRV_IOCTL_GET_ETH_PORT_BY_HOST_MAC_CMD,
    SC_DRV_IOCTL_GET_ETH_PORT_STATISTICS_CMD,
} SC_DRV_IOCTL_CMD;


#endif /* _SC_DRV_H_ */

