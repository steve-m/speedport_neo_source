#ifndef _SCAPPLY_CLIENT_H_
#define _SCAPPLY_CLIENT_H_

#define MAX_SERVICE_PER_URI             (8)
#define SCAPPLY_LOCAL_SOCKET            "/tmp/scapply_local_socket"
#define MULTIPLE_SCAPPLY_CLINET_MAX     (4)

#define SCAPPLYD                        "/usr/sbin/service_ctrld "
#define SCAPPLY_CLIENT_SYSCALL          "/usr/sbin/service_ctrl_client "

#define SCAPPLY_CMD_SEPARATE_SYMBOL     ','
#define URI_OBJECT_SYMBOL               '.'

#define APPLY_RESULT_FILE_NAME_LEN_MAX  (64)
#define SCAPPLY_CLIENT_CMD_LEN_MAX      (1024)
#define SCAPPLY_MEMBERS_NUM_IN_CMD_MAX  (16)
#define SCAPPLY_CLIENT_CMD_RET_LEN_MAX  (32)

#define SCAPPLY_URI_LEN_MAX             (512)
#define SCAPPLY_SERVICE_LEN_MAX         (32)

#define SHORT_INSTANCE_NUM_MIN          (0)
#define SHORT_INSTANCE_NUM_MAX          (999)

#define PID_NUMBER_NONE                 (-1)

#define SOCK_WAIT_TIME                  1//seconds
#define SERVICE_CMD_GENERAL_WAIT_TIME   5//seconds
#define SERVICE_CMD_APPLY_WAIT_TIME     5//seconds
#define SERVICE_CMD_URISET_WAIT_TIME    5//seconds
#define SERVICE_CMD_GETSTATE_WAIT_TIME  5//seconds

enum{
    SCAPPLY_CMD_NONE = 0,
    SCAPPLY_CMD_LOCK,
    SCAPPLY_CMD_UNLOCK,
    SCAPPLY_CMD_PRAR_SET,
    SCAPPLY_CMD_INSTANCE_ADD,
    SCAPPLY_CMD_INSTANCE_DEL,
    SCAPPLY_CMD_EVENT,
    SCAPPLY_CMD_APPLY,
    SCAPPLY_CMD_DUMP_URI_TABLE,
    SCAPPLY_CMD_DUMP_APPLYQ,
    SCAPPLY_CMD_DUMP_LOCKQ,
    SCAPPLY_CMD_GET_STATE,
};

enum{
    SCAPPLY_SERVICE_ACTION_NONE = 0,
    SCAPPLY_SERVICE_ACTION_STOP,
    SCAPPLY_SERVICE_ACTION_START,
    SCAPPLY_SERVICE_ACTION_RESTART,
    SCAPPLY_SERVICE_ACTION_END
};

enum{
    SCAPPLY_SERVICE_INSTANCE_NONE = 0,
    SCAPPLY_SERVICE_INSTANCE_SHORT,
    SCAPPLY_SERVICE_INSTANCE_LONG,
    SCAPPLY_SERVICE_INSTANCE_END
};

enum{
    SCAPPLY_STATE_SUBCMD_NONE = 0,
    SCAPPLY_STATE_SUBCMD_APPLY_NEEDED,
    SCAPPLY_STATE_SUBCMD_END
};

#define SCAPPLY_DEBUG

#ifdef SCAPPLY_DEBUG
    #define SCAPPLY_CLIENT_DEBUG(fmt, args...) do{FILE *fp=fopen("/dev/console", "a+"); if(fp) {fprintf(fp, fmt, ##args);fclose(fp);}}while(0)
#else
    #define SCAPPLY_CLIENT_DEBUG(fmt, args...)
#endif


enum{
    SCAPPLY_API_TYPE_NONE = 0,
    SCAPPLY_API_TYPE_PID_AUTOADD,
};

int service_cmd_need_reply(int cmd, int subcmd);
int service_ctl_cmd_uri_set(int subcmd, char *uri, char *retbuff, int size, int wait_seconds);
int service_ctl_cmd_do_apply(char *retbuff, int size, int wait_seconds);
int service_ctl_cmd_get_state(int subcmd, char *retbuff, int size, int wait_seconds);
int service_ctl_cmd(int type, char *cmdstr, char *retbuff, int size, int wait_seconds);

int service_ctl_cmd_lock(void);
int service_ctl_cmd_unlock(void);

#endif
