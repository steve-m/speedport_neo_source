#ifndef _SCSHAREDUTIL_H_
#define _SCSHAREDUTIL_H_
#include <netinet/in.h>

#ifndef A_CHAR_DEFINED
typedef char                    A_CHAR;
#define A_CHAR_DEFINED
#endif

#ifndef A_INT8_DEFINED
typedef A_CHAR                  A_INT8;
#define A_INT8_DEFINED
#endif

#ifndef A_INT16_DEFINED
typedef short                   A_INT16;
#define A_INT16_DEFINED
#endif

#ifndef A_INT32_DEFINED
typedef int                     A_INT32;
#define A_INT32_DEFINED
#endif

#ifndef A_UCHAR_DEFINED
typedef unsigned char           A_UCHAR;
#define A_UCHAR_DEFINED
#endif

#ifndef A_UINT8_DEFINED
typedef A_UCHAR                 A_UINT8;
#define A_UINT8_DEFINED
#endif

#ifndef A_UINT16_DEFINED
typedef unsigned short          A_UINT16;
#define A_UINT16_DEFINED
#endif

#ifndef A_UINT32_DEFINED
typedef unsigned int            A_UINT32;
#define A_UINT32_DEFINED
#endif

#ifndef A_UINT_DEFINED
typedef unsigned int            A_UINT;
#define A_UINT_DEFINED
#endif

#ifndef A_BOOL_DEFINED
typedef int                     A_BOOL;
#define A_BOOL_DEFINED
#endif

#ifndef A_INT64_DEFINED
typedef long long               A_INT64;
#define A_INT64_DEFINED
#endif

#ifndef A_UINT64_DEFINED
typedef unsigned long long      A_UINT64;
#define A_UINT64_DEFINED
#endif

#ifndef A_LONGSTATS_DEFINED
typedef A_UINT64                A_LONGSTATS;
#define A_LONGSTATS_DEFINED
#endif

#ifndef UINT32_DEFINED
typedef A_UINT32                UINT32;
#define UINT32_DEFINED
#endif

#ifndef INT16_DEFINED
typedef A_INT16                 INT16;
#define INT16_DEFINED
#endif

#ifndef  INT32_DEFINED
typedef A_INT32			        INT32;
#define INT32_DEFINED
#endif

#ifndef CHAR_DEFINED
typedef char			        CHAR;
#define CHAR_DEFINED
#endif

#ifndef BYTE_DEFINED
typedef unsigned char		    BYTE;
#define BYTE_DEFINED
#endif

#ifndef WORD_DEFINED
typedef unsigned short 		    WORD;
#define WORD_DEFINED
#endif

#ifndef DWORD_DEFINED
typedef unsigned int		    DWORD;
#define DWORD_DEFINED
#endif

#ifndef VOID_DEFINED
typedef void 			        VOID;
#define VOID_DEFINED
#endif

typedef struct if_info_s{
	char ifname[16];
	char ipaddr[16];
	char mac[18];
	char mac_raw[18];
	char mask[16];
	struct in_addr gw;
	int  mtu;
}if_info_t;

#ifdef AF_INET6
#define PATH_PROCNET_IFINET6    "/proc/net/if_inet6"
#define PATH_PROCNET_ROUTE6     "/proc/net/ipv6_route"
#define IPV6_ADDR_LINKLOCAL     0x0020U
#define IPV6_ADDR_GLOBAL        0x0000U
#endif

int get_sockfd(void);
int getIFInfo(char *if_name, if_info_t *if_info);
int ibmpc_to_utf8(uint8_t *in, int insize, uint8_t **out);
int scWlanMacExit(unsigned char *mac);
unsigned long util_crc32(char *data, int length);

int util_lock(char *file, int retry_time);
void  util_unlock(int fd);

#define LOCK_RETRY_COUNT    3
int util_lock_reg(int fd, short type, int retry_time);

#define util_read_lock(fd, retry_time) \
    util_lock_reg((fd), F_RDLCK, (retry_time))

#define util_write_lock(fd, retry_time) \
    util_lock_reg((fd), F_WRLCK, (retry_time))

#define util_un_lock(fd, retry_time)\
    util_lock_reg((fd), F_UNLCK, (retry_time))

long get_uptimes(void);
void getTimeofDay(char *buffer);
int check_call_status(int status);
int check_cwmp_state(void);
int getMgtBrInfo(if_info_t *if_info);
int getIP6Info1(char *ifname, char *address, int ipv6_addr_scope);
int lan_ipv6_prefix_generate(char *prefix);
int lan_ipv6_subnetid_generate(char *p_subnetid_h);
int get_productname(char *buffer);
#endif /* End Of _SCSHAREDUTIL_H_ */
