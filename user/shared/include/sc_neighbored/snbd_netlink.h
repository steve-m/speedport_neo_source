#ifndef _SNBD_NETLINK_H_
#define _SNBD_NETLINK_H_

#include <linux/netlink.h>
#include <linux/rtnetlink.h>

int snbd_netlink_socket_init(char *ifname);
int snbd_netlink_socket_handle(int nl_fd);
int snbd_netlink_init_neighbor(int family);
int snbd_netlink_l3addr_set_state(uint8_t *l2addr, int family,
                                  uint8_t *l3addr, int state);
int snbd_netlink_l3addr_solicit(uint8_t *l2addr, int family,
                                uint8_t *l3addr);

#endif /* _SNBD_NETLINK_H_ */
