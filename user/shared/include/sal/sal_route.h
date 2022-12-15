#ifndef _SAL_ROUTE_H_ 
#define _SAL_ROUTE_H_


#define SAL_ROUTE_MAX_ENTRY 64

typedef struct 
{
    char dst[32];
    char gw[32];
    char mask[32];
    char flags[8];
    char metric[8];
    char ref[8];
    char use[8];
	char dev[64];
}sal_route;

int sal_route_get_route_entry(sal_route** route);

#endif
