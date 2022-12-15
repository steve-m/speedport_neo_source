#ifndef _SNBD_CMD_H_
#define _SNBD_CMD_H_

#include <stdint.h>
#include "snbd_hostdb.h"

#define SNBD_CMD_SOCKET_PATH "/var/run/snbd_cmd_socket"

enum {
    SNBD_CMD_TYPE_UNKNOW = 0,
    SNBD_CMD_TYPE_CMDLINE,
    SNBD_CMD_TYPE_DHCPV4,
    SNBD_CMD_TYPE_DHCPV6,
    SNBD_CMD_TYPE_NMBS,
    SNBD_CMD_TYPE_GUI,
    SNBD_CMD_TYPE_PERIODIC,
    SNBD_CMD_TYPE_DFND,

    SNBD_CMD_TYPE_WLAN = 20,
    SNBD_CMD_TYPE_MAX
};

struct snbd_cmd {
    int type;
    unsigned char payload[0];
};
#define SNBD_CMD(cmd) ((struct snbd_cmd *)(cmd))

enum {
    SNBD_CMD_DHCPV4_NEW,
    SNBD_CMD_DHCPV4_RELEASE,
    SNBD_CMD_DHCPV4_LEASE_EXPIRED,
};
struct snbd_cmd_dhcpv4 {
    struct snbd_cmd base;
    int dhcp_cmd;
    char name[SNBD_HOST_NAME_LEN];
    uint8_t l2addr[ETH_ALEN];
    struct snbd_l3addr l3addr;
    uint32_t lease_time;
    int option_nr;
    uint8_t options[4][256 + 2];
};
#define SNBD_CMD_DHCPV4(buf) ((struct snbd_cmd_dhcpv4 *)(buf))

struct snbd_cmd_wlan {
    int type; /* base */
    int on_off;
    uint8_t l2addr[ETH_ALEN];
    int wl_index;
};
#define SNBD_CMD_WLAN(buf) ((struct snbd_cmd_wlan *)(buf))

enum {
    SNBD_CMD_GUI_NEW_HOST,
    SNBD_CMD_GUI_DEL_HOST,
    SNBD_CMD_GUI_UPDATE_HOST,
};
struct snbd_cmd_gui {
    struct snbd_cmd base;
    int cmd;
    uint8_t payload[0];
};
#define SNBD_CMD_GUI(buf) ((struct snbd_cmd_gui *)(buf))

enum {
    SNBD_CMD_PERIODIC_SYNC_NETLINK,
    SNBD_CMD_PERIODIC_SYNC_WIFI,
};
struct snbd_cmd_periodic {
    struct snbd_cmd base;
    int cmd;
    uint8_t payload[0];
};
#define SNBD_CMD_PERIODIC(buf) ((struct snbd_cmd_periodic *)(buf))

enum {
    SNBD_CMD_DFND_CFG_UPDATE,
    SNBD_CMD_DFND_FW_UPDATE,
    SNBD_CMD_DFND_TIME_FW_UPDATE,
    SNBD_CMD_DFND_DUMP_JRPC_LOG,
};
struct snbd_cmd_dfnd {
    struct snbd_cmd base;
    int cmd;
    uint8_t payload[0];
};
#define SNBD_CMD_DFND(x) ((struct snbd_cmd_dfnd *)(x))
struct snbd_cmd_dfnd_cfg_update {
    struct snbd_cmd_dfnd dfnd_cmd;
    int svc_type;
};
#define SNBD_CMD_CFG_UPDATE(x) ((struct snbd_cmd_dfnd_cfg_update *)(x))
#define SNBD_CMD_SEND_DFND_CFG_UPDATE(type) \
    do {\
        struct sockaddr_un addr;\
        memset(&addr, 0, sizeof(addr));\
        addr.sun_family = AF_UNIX;\
        strcpy(addr.sun_path, SNBD_CMD_SOCKET_PATH);\
        struct snbd_cmd_dfnd_cfg_update cmd;\
        cmd.dfnd_cmd.base.type = SNBD_CMD_TYPE_DFND;\
        cmd.dfnd_cmd.cmd = SNBD_CMD_DFND_CFG_UPDATE;\
        cmd.svc_type = (type);\
        sendto(fd, &cmd, sizeof(cmd), 0, (struct sockaddr *)&addr, sizeof(addr));\
    } while(0)

int snbd_cmd_socket_init(void);
int snbd_cmd_socket_handle(int fd);


#endif /* _SNBD_CMD_H_ */
