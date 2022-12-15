#ifndef DNSMASQ_SC_H
#define DNSMASQ_SC_H

#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdarg.h>

#define SC_DEBUG(...) do {\
    FILE *fp = fopen("/dev/console", "w");\
    if(fp) {\
        fprintf(fp, __VA_ARGS__);\
        fclose(fp);\
    };\
}while(0);\


struct voip_server_hnode {
    char *server_name;
    struct voip_server_hnode *next;
};

#define SC_EA_MAX_SIZE      256
#define SC_EA_FILE          "/var/dnsmasq.eawlist"
struct ea_hnode {
    char *fqdn;
    struct ea_hnode *next;
};
extern struct ea_hnode *g_ea_wlist[SC_EA_MAX_SIZE];
extern unsigned int g_ea_flag;
#define SC_EA_DO_V4       (1u << 0)
#define SC_EA_DO_V6       (1u << 1)

#define SC_CMD_SOCK_PATH    "/var/run/dnsmasq_sc_cmd"

#define SC_CMD_RELOAD_EA    1
#define SC_CMD_FLUSH_EA     2
#define SC_CMD_DUMP_EA      3
#define SC_CMD_START_EA4    4
#define SC_CMD_STOP_EA4     5
#define SC_CMD_START_EA6    6
#define SC_CMD_STOP_EA6     7
#define SC_CMD_ADD_HOSTS    8
#define SC_CMD_DEL_HOSTS    9
#define SC_CMD_UPDATE_VOIP_SERVER      10
#define SC_CMD_DNS_CACHE    11
struct sc_cmd_dns_cache {
    pid_t   pid;
    size_t  qlen;
    time_t  now;
    int     is_sign;
    int     check_rebind;
    int     checking_disabled;
    int     qtype;
    char    name[1025];
    char    header[0];
};

#endif /* DNSMASQ_SC_H */
