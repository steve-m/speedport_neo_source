/* socket.h */
#ifndef _SOCKET_H
#define _SOCKET_H

int read_interface(char *interface, int *ifindex, u_int32_t *addr, unsigned char *arp);
#if defined(__SC_BUILD__)
int listen_socket(unsigned int ip, int port, char *inf, int ip_pktinfo_need);
#else
int listen_socket(unsigned int ip, int port, char *inf);
#endif
int raw_socket(int ifindex);

#endif
