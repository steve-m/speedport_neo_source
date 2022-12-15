#ifndef _CRON_API_H_
#define _CRON_API_H_

#define _PATH_CRON_PID              "/var/cron/cron.pid"
#define CRON_LOCAL_SOCKET           "/var/cron/cron_local_socket"
#define CRON_SOCK_WAIT_TIME         60

#define CRON_SENTRY_MIN_LEN         (60*2+1)
#define CRON_SENTRY_HOUR_LEN        (24*2+1)
#define CRON_SENTRY_DOM_LEN         (31*2+1)
#define CRON_SENTRY_MONTH_LEN       (12*2+1)
#define CRON_SENTRY_DOW_LEN         (8*2+1) /* 0 -7 */
#define CRON_SENTRY_CMD_LEN         (256+1)
#define CRON_SENTRY_GROUP_LEN       (64)

#define PCTRL_GROUP     "pctrl" 
#define WLAN_SCH_GROUP  "wlan_scheduler"
#define SYNC_SCH_GROUP  "sync_schd"
#define BACKUP_SCH_GROUP "backup_schd"
#define TIME_RULE_GROUP "trule"

enum {
    CRON_SOCKET_CIRCLE = 0,
    CRON_SOCKET_ONCE,
    CRON_SOCKET_FLUSH,
    CRON_SOCKET_LOCK,
    CRON_SOCKET_UNLOCK,
    CRON_SOCKET_STAT
};

enum {
    CRON_STAT_ERR = 0,
    CRON_STAT_LOCK,
    CRON_STAT_IN_RANGE,
    CRON_STAT_OUT_RANGE
};

typedef struct _circle_entry {
    char min[CRON_SENTRY_MIN_LEN];
    char hour[CRON_SENTRY_HOUR_LEN];
    char dom[CRON_SENTRY_DOM_LEN];
    char month[CRON_SENTRY_MONTH_LEN];
    char dow[CRON_SENTRY_DOW_LEN];
    char cmd[CRON_SENTRY_CMD_LEN];
}circle_entry;

typedef struct _once_entry {
    char stime[16];
    char etime[16];
    char dow[CRON_SENTRY_DOW_LEN];
    char in_cmd[CRON_SENTRY_CMD_LEN];
    char out_cmd[CRON_SENTRY_CMD_LEN];
}once_entry;


typedef struct _flush_entry { /* 1. delete group entry, 2. delete command */
    char cmd[CRON_SENTRY_CMD_LEN];
}flush_entry;

typedef	struct _s_entry
{
    int type;       /* add_circle, add_once, delete_group */    
    char group[CRON_SENTRY_GROUP_LEN];      /* pctrl, wifi */
    char id[32];
    union 
    {
        circle_entry circle;
        once_entry once;
        flush_entry flush;
    }data;      
}s_entry;

int cron_request_once(char *, char *, char *, char *, char *, char *, char *);
int cron_request_circle(char *, char *,  char *, char *, char *);
int cron_request_flush(char *, char *);
int cron_request_stat(char *group, char *id, int wait_sec);
int cron_request_lock(char *group, char *id);
int cron_request_unlock(char *group, char *id);

#endif

