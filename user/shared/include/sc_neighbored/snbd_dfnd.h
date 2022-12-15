#ifndef _DFND_H_
#define _DFND_H_

#include <pthread.h>
#include <semaphore.h>
#include <openssl/asn1.h>
#include <openssl/evp.h>

#include "snbd_cmd.h"

#define JRPC_LOG_FILE   "/tmp/jrpc.log"

enum {
    DFND_SVC_WLAN_24_PRIVATE,
    DFND_SVC_WLAN_50_PRIVATE,
    DFND_SVC_WLAN_ENCRYPTION,
    DFND_SVC_WLAN_24_ACTIVATION,
    DFND_SVC_WLAN_50_ACTIVATION,
    DFND_SVC_WLAN_TIME_CONTROL,
    DFND_SVC_WLAN_ACCESS_CONTROL,
    DFND_SVC_WLAN_GUEST_ACCESS,
    DFND_SVC_TELEPHONY_CONFIGURATION,
    DFND_SVC_FXS_CONFIGURATION,
    DFND_SVC_FIRMWARE_UPDATE,
    DFND_SVC_LED_STATUS,
    DFND_SVC_MAX = 32
};

typedef enum {
    DFND_CMD_RECV_INFORM,
    DFND_CMD_RECV_KEY_EXCHANGE_REPLY,
    DFND_CMD_INITIAL_CONF,
    DFND_CMD_UPDATE_CONF,
    DFND_CMD_FW_UPDATE,
    DFND_CMD_UNMANAGE_DEV,
} dfnd_cmd_type;

struct dfnd_cmd {
    int type;
    struct dfnd_cmd *next;
    char params[0];
};
#define DFND_CMD(p) ((struct dfnd_cmd *)(p))

struct dfnd_cmd_fwupd {
    struct dfnd_cmd base;
    char productClass[16];
    char serialNumber[32];
    char imageURL[1024];
    char digest[128];
};
struct dfnd_cmd_key_ex_reply {
    struct dfnd_cmd base;
    char *Y_str;
};
#define DFND_CMD_KEY_EX_REPLY(p) ((struct dfnd_cmd_key_ex_reply *)(p))

struct dfnd_cmd_q {
    struct dfnd_cmd *begin;
    struct dfnd_cmd *end;
    pthread_mutex_t mutex;
    sem_t sem;
};

struct dfnd_info {
    /* persistent information */
    char *protocolVersion;
    char *deviceClass;
    char *productClass;
    char *deviceName;
    char *serialNumber;
    char *firmwareVersion;
    char *provisioningCode;
    int serviceSummary[DFND_SVC_MAX];
    int configurationValue[DFND_SVC_MAX];

    int dev_id;
    int id; /* datamodel id */
    char *key;
    BIGNUM *x;

    /* runtime information */
    struct snbd_host *host;
    int thread_run;
    pthread_t thread;
    struct dfnd_cmd_q cmd_q;

    struct dfnd_cmd *pending_cmd;
    int pending_act_time;
};

static char *dfnd_known_productclass[] = {
    "DTWNEOV01PV",
    NULL
};

int dfnd_sync_from_datamodel(void);
int dfnd_jrpc_server_init(void);
int snbd_dfnd_cmd_handler(unsigned char *buf, int len);

#endif /* _DFND_H_ */
