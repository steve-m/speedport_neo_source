#ifndef _SNBD_HOSTDB_H_
#define _SNBD_HOSTDB_H_

#include <stdint.h>
#include <netinet/if_ether.h>

enum {
    SNBD_L3ADDR_TYPE_UNKNOW = 0,
    SNBD_L3ADDR_TYPE_FIXED,
    SNBD_L3ADDR_TYPE_DHCP,
};

#define SNBD_L3ADDR_IP4_LEN (4)
#define SNBD_L3ADDR_IP6_LEN (16)
#define SNBD_L3ADDR_MAX_LEN (16)
struct snbd_l3addr {
    int id;
    int ndm_family;
    int ndm_state;
    int addr_type;
    uint8_t l3addr[SNBD_L3ADDR_MAX_LEN];
    struct snbd_l3addr *next;
};

enum {
    SNBD_HOST_NAME_TYPE_UNKNOW = 0,
    SNBD_HOST_NAME_TYPE_AUTO,
    SNBD_HOST_NAME_TYPE_NBNS,
    SNBD_HOST_NAME_TYPE_DHCP,
    SNBD_HOST_NAME_TYPE_DFND,
    SNBD_HOST_NAME_TYPE_MANUAL,
};

enum {
    SNBD_HOST_CONN_NONE = 0,
    SNBD_HOST_CONN_WIRED,
    SNBD_HOST_CONN_WLAN,
    SNBD_HOST_CONN_WLAN_5G,
 //   SNBD_HOST_CONN_MANUAL,
};

enum {
    SNBD_HOST_ADDR_SOURCE_NONE = 0,
    SNBD_HOST_ADDR_SOURCE_STATIC,
    SNBD_HOST_ADDR_SOURCE_AUTOIP,
    SNBD_HOST_ADDR_SOURCE_DHCP,
};

#define SNBD_HOST_NAME_LEN  (64)
struct snbd_host {
    int conn_type;
    uint8_t l2addr[ETH_ALEN];
    char name[SNBD_HOST_NAME_LEN];
    int name_type;
    int addr_source;
    struct snbd_l3addr *l3addr;

    int is_proxy;
    /* sync */
    int sync;    /* SYNC this host with data model */
    int host_id; /* cml table entry index */
    int dhcp_id; /* dhcp table entry index */

    time_t wlan_log_time; /* record time when print W019/W020 */
    uint8_t wlan_connect; /* mark wlan client connection*/

    /* list management */
    struct snbd_host *next;

    struct snbd_host *via;
    struct dfnd_info *dfnd;
};

struct snbd_host_list_head {
    pthread_rwlock_t rw_lock;
    struct snbd_host *hosts;
};
extern struct snbd_host_list_head snbd_host_list;
#define snbd_host_for_each(p, body) do {\
    pthread_rwlock_rdlock(&snbd_host_list.rw_lock);\
    for((p) = snbd_host_list.hosts; (p); (p) = (p)->next) {\
        body;\
    }\
    pthread_rwlock_unlock(&snbd_host_list.rw_lock);\
} while(0);


char* snbd_l2addr_to_str(uint8_t *l2addr, int addrlen);
/*
 * host api
 */
struct snbd_host* snbd_host_new(void);
void snbd_host_free(struct snbd_host *host_p);
uint8_t snbd_host_active(struct snbd_host *host_p);
int snbd_host_manual_configured(struct snbd_host *host_p);
void snbd_host_set_sync(struct snbd_host *host_p, int sync,int hostid);
void snbd_host_set_conn_type(struct snbd_host *host_p, int type);
struct snbd_l3addr *snbd_host_set_l3addr(struct snbd_host *host_p,
                                         struct snbd_l3addr *l3addr_p);
struct snbd_l3addr* snbd_host_get_l3addr(struct snbd_host *host_p,
                                         int family, uint8_t *l3addr);
int snbd_host_set_name(struct snbd_host *host_p, char *name,
                       int name_type);
int snbd_host_set_l2addr(struct snbd_host *host_p, uint8_t *l2addr,
                         int addrlen);
int snbd_host_set_l2addr_by_str(struct snbd_host *host_p, char *str);
void snbd_host_dump(struct snbd_host *host_p);
void snbd_host_l3addr_notify(struct snbd_host *host_p,
                             int family, uint8_t *l3addr,
                             int updown);

/*
 * hostdb api
 */
int snbd_hostdb_init(void);
int snbd_hostdb_add(struct snbd_host *host_p,int hostid);
int snbd_hostdb_del(struct snbd_host *host_p);
struct snbd_host* snbd_host_get_by_id(int id);
struct snbd_host* snbd_host_get_by_l2addr(uint8_t *l2addr, int addrlen);
struct snbd_host* snbd_host_get_by_l3addr(int family, uint8_t *l3addr);
void snbd_hostdb_dump(void);
int sndb_check_wifi_log(struct snbd_host *host_p,char *status);

#endif /* _SNBD_HOSTDB_H_ */
