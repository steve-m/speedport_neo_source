#ifndef _SERVERPACKET_H
#define _SERVERPACKET_H

#ifdef __SC_BUILD__
#include "packet.h"
#endif

#ifdef __SC_BUILD__
int sendOffer(struct dhcpMessage *oldpacket, int ifid, struct pkt_extra_info *extra_info);
#else
int sendOffer(struct dhcpMessage *oldpacket, int ifid);
#endif
int sendNAK(struct dhcpMessage *oldpacket, int ifid);
#ifdef __SC_BUILD__
int sendACK(struct dhcpMessage *oldpacket, u_int32_t yiaddr, int ifid, struct pkt_extra_info *extra_info);
#else
int sendACK(struct dhcpMessage *oldpacket, u_int32_t yiaddr, int ifid);
#endif
int send_inform(struct dhcpMessage *oldpacket, int ifid);

#endif
