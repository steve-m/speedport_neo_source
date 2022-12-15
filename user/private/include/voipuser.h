#ifndef _VOIP_USER_H_
#define _VOIP_USER_H_

//vgw app will update this file
#define FILE_VGW_VOIP_STATUS        "/var/voip"
#define FILE_VGW_VOIP_CALL_STATE	"/var/voip1"
#define VOICE_LINE_STATE_RESULT     "/tmp/line_state_result"
#define VOICE_DIAGNOSIS_CFG         "/tmp/voice_diagnosis_cfg" 
#define VOICE_DIAGNOSE_FILE	"/tmp/vgw_to_dignosis"
#define VOICE_DIAGNOSE_HOOK	"/tmp/vgw_hook"


enum VOICE_LINE_ID
{
    VOICE_LINE_ID_1 = 0,
    VOICE_LINE_ID_2,
    VOICE_LINE_ID_NUM,
};

enum VOICE_APP_STATUS
{
    VOICE_APP_UP = 0,
    VOICE_APP_CONNECTING,
    VOICE_APP_DISABLED,
    VOICE_APP_ERROR,
};

/**
* Warning: keep the sequence same as typedef enum VGW_REG_STATUS_s 
*              in drivers/voip/vgw/include/vm_common.h
*                                       2011/06/27, Andic
*
**/
enum VOICE_VGW_STATUS
{
    VOICE_VGW_DISABLED = 0,
    VOICE_VGW_REGISTERING,
    VOICE_VGW_UP,
    VOICE_VGW_ERROR,
    VOICE_VGW_INITIALIZING,
    VOICE_VGW_UNREGISTERING,
    VOICE_VGW_QUIESCENT,
    VOICE_VGW_USERNAMEERR,   /* Weizhi, 2013/07/08 [0040153] notify user name error */
    VOICE_VGW_PWERR,         /* Weizhi, 2013/07/08 [0040145] notify password error */
};

enum VOICE_VGW_CALL_STATE
{
    VOICE_VGW_CALL_STATE_TBD=-1,		/* Registering or Error */
    VOICE_VGW_CALL_STATE_IDLE=0,		/* Idle */
    VOICE_VGW_CALL_STATE_CALLING=1,	/* Outgoing Active Call */
    VOICE_VGW_CALL_STATE_RINGING=2,	/* RINGING */
    VOICE_VGW_CALL_STATE_CONNECTING=3,	/* Outgoing Call Wait Remote Answer*/
    VOICE_VGW_CALL_STATE_INCALL=4,		/* Incoming Active Call  */
    VOICE_VGW_CALL_STATE_HOLD=5,		/* HOLD  */
    VOICE_VGW_CALL_STATE_DISCONN=6,	/* Disconnecting, Send BYE and Wait for 200OK  */
};

enum VOICE_EXTRA_ERROR_CODE
{
    VOICE_EXTRA_ERROR_NONE = 0,
    VOICE_EXTRA_ERROR_NET,
    VOICE_EXTRA_ERROR_PHONE,
};

/* phy_line: 1/2 */
char *voice_get_line_status(int phy_line);
char *voice_get_line_call_state(int phy_line);

/*
 * @fn int voice_app_status_get(int line, int *err_id)
 * @brief
 *          get line status, and set extra error info if error
 * @param[in] 
 *          line: 0/1 for line 0/1
 *          errno: keep error id here if error, which is defined 
 *                   in enum VOICE_EXTRA_ERROR_CODE
 * @return
 *          value defined in enum VOICE_APP_STATUS
 */
int voice_app_status_get(int line, int *err_id);

/*
 * @fn 
 * @brief
 * @param[in] 
 *          line: 0/1 for line 0/1
 * @return
 *          0: valid, -1: invalid
 */
int valid_line(int line);

int voice_line_register_ok(int line);

/*********************************
*  VOICE DIAGNOSIS
*
*********************************/
enum DIAGNOSIS_CFG_LIST
{
    DIAGNOSIS_CFG_WAN_IP = 0,
    DIAGNOSIS_CFG_WAN_MAC,
    DIAGNOSIS_CFG_WAN_IFACE,
    DIAGNOSIS_CFG_WAN_GW,
    DIAGNOSIS_CFG_DNS_HOST,
    DIAGNOSIS_CFG_CMD_PHONE_CONNECTION,
    DIAGNOSIS_CFG_CMD_RING_ON,
    DIAGNOSIS_CFG_CMD_RING_OFF,
    DIAGNOSIS_CFG_MAX
};

enum DIAGNOSIS_STATE_LIST
{
    DIAGNOSIS_STATE_NO_RUN = 0,
    DIAGNOSIS_STATE_INITIALIZING,
    DIAGNOSIS_STATE_EQUIPMENT,
    DIAGNOSIS_STATE_RINGTONE,
    DIAGNOSIS_STATE_DIAL_TONE,
    DIAGNOSIS_STATE_NUMBERING,
    DIAGNOSIS_STATE_FINISH,
};

enum DIAGNOSIS_CMD_LIST
{
    DIAGNOSIS_CMD_SET_INITIALIZING = 0,
    DIAGNOSIS_CMD_SET_EQUIPMENT,
    DIAGNOSIS_CMD_SET_RINGTONE,
    DIAGNOSIS_CMD_SET_DIAL_TONE,
    DIAGNOSIS_CMD_SET_NUMBERING,
    DIAGNOSIS_CMD_SET_FINISH,
    DIAGNOSIS_CMD_GET_STATE,
    DIAGNOSIS_CMD_ALL,
};

enum DIAGNOSIS_STATE_STATUS
{
    DIAGNOSIS_STATE_STATUS_NOT_EXECUTE = 0,
    DIAGNOSIS_STATE_STATUS_IN_PROGRESS,
    DIAGNOSIS_STATE_STATUS_DONE,
};

enum DIAGNOSIS_ERROR_CODE
{
    DIAGNOSIS_ERROR_NONE = 0,
    DIAGNOSIS_ERROR_LINE_NO,
    DIAGNOSIS_ERROR_WAN_IFACE,
    DIAGNOSIS_ERROR_WAN_GATEWAY,
    DIAGNOSIS_ERROR_WAN_DNS,
    DIAGNOSIS_ERROR_VOICE_UNREG,
    DIAGNOSIS_ERROR_PHONE_UNCON,
    DIAGNOSIS_ERROR_PHONE_UNPICKUP,
    DIAGNOSIS_ERROR_PHONE_UNHANGUP,
    DIAGNOSIS_ERROR_WRONG_NUMBER,
    DIAGNOSIS_ERROR_WRONG_CMD,
};

typedef struct
{
    int line_no; //0,1,-1(ignore line no)
    int cmd_set; // value in enum DIAGNOSIS_CMD_LIST
}diagnosis_method_t;

typedef struct
{
    int line_no; //0,1,-1(ignore line no)
    int state; //value in enum DIAGNOSIS_STATE_LIST
    int status; //value in enum DIAGNOSIS_STATE_STATUS
    int error; //value in enum DIAGNOSIS_ERROR_CODE
    char exinfo[64];
}diagnosis_status_t;

#define LOCAL_VOICE_DIAGNOSIS "/tmp/local_voice_diagnosis"
#define LOCAL_VOICE_BUFF_SIZE 128

//#define VOICE_DIAGNOSIS_DEBUG

#ifdef VOICE_DIAGNOSIS_DEBUG
#define VOICE_DIAG_DEBUG(format,argument...) printf(format,##argument)
#else
#define VOICE_DIAG_DEBUG(format,argument...)
#endif

/*
 * @fn int voice_diagnosis_client(diagnosis_method_t *diag_in, diagnosis_status_t *diag_out)
 * @brief
 *          run diagnosis step and also get diagnosis result
 * @param[in] 
 *          diag_in: 
 *               client send diagnosis step cmd to server by diag_in
 *          diag_out: 
 *               if set cmd is DIAGNOSIS_CMD_GET_STATE, diag_out will be used to save result
 * @warning
 *          diag_in, and diag_out should be valid
 * @return
 *          if >= 0, client&server excute cmd ok;if < 0, error
 */
int voice_diagnosis_client(diagnosis_method_t *diag_in, diagnosis_status_t *diag_out);

#endif

