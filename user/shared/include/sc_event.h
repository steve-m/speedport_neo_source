#ifndef _LOCAL_SOCKET_H_
#define _LOCAL_SOCKET_H_

#include <arpa/inet.h>
#define SC_EVENT_PATH "/tmp/sc_event"
struct sc_event_msg
{
    char name[64];
    char buf[0];
};

/*
 *Set dhcpv4 client options
 */
struct sc_dhcp_client_option
{
    char option15[128];
    char option54[9];
};

struct sc_routeinfo_option
{
    char sourcerouter[INET6_ADDRSTRLEN];
    char prefix[INET6_ADDRSTRLEN];
    char preferred_routeflag[8];
    unsigned int routelftime;
    unsigned int current_t;
};
#endif
