#ifndef _CAL_VOICE_H_
#define _CAL_VOICE_H_

#define DEFAULT_VOICESERVICE_ID                 1
#define DEFAULT_EXTENSIONPROF_ID                1
#define TONLINE_REGISTRAR_SERVER                "tel.t-online.de"
#define TONLINE_PROVIDER_NAME                   "Telekom"
#define TONLINE_REGISTRAR_PORT                  "5060"

#define VOICE_MAX_FXS_EXTENSION_NUM             2
#define MAX_DECT_NUMBER                         5

#ifdef SUPP_LOCAL_PBX
#define VOICE_MAX_SIP_EXTENSION_NUM             3
#else 
#define VOICE_MAX_SIP_EXTENSION_NUM             0
#endif

#define VOICE_MAX_EXTENSION_NUM                 (VOICE_MAX_FXS_EXTENSION_NUM+MAX_DECT_NUMBER+VOICE_MAX_SIP_EXTENSION_NUM)
#define VOICE_MAX_PHONEPLUG_NAME_LENGTH         40 //Max in GUI is 32.

#define VOICE_MAX_PROVIDER_NUM                  15
#define VOICE_MAX_LINE_NUM                      15
#define VOIP_MAX_SUPPORT_LINE	                VOICE_MAX_LINE_NUM
#define VOICE_MAX_PHONEBOOK_NUM                 100

#define VOICE_TELEKOM_ACS_ONLY_PROFILE          1
#define VOICE_TELEKOM_USER_PROFILE              2
#define VOICE_TELEKOM_BNG_PROFILE               3
#define VOICE_OTHER_PROFILE                     4

#define VOICE_EXT_PROFILE_FXS                   1
#define VOICE_EXT_PROFILE_DECT                  2
#define VOICE_EXT_PROFILE_SIP                   3

#define VOICE_MAX_CALLLOG_NUM	                100

#define VOICE_EXT_ID_VGW_TO_USER(vgwId)         (vgwId+1)    
#define VOICE_EXT_ID_USER_TO_VGW(userId)        (userId-1)
#define VOICE_DECT_ID_VGW_TO_USER(vgwId)        (vgwId+2)    
#define VOICE_DECT_ID_USER_TO_VGW(userId)       (userId-2)

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

enum
{
	VOICE_CALLLOG_MISSED=0,
	VOICE_CALLLOG_TAKEN,
    VOICE_CALLLOG_DIALED,
    VOICE_CALLLOG_ALL
}LogType;

typedef struct cal_voice_calllog_num_s
{
	int missedlog_num;
	int takenlog_num;
	int dialedlog_num;
}cal_voice_calllog_num_t;

typedef struct cal_voice_calllog_entry_s
{
	char date[32];
	char time[32];
	char callingnum[201];
	char callednum[201];
	char szPort[32];
	int duration;
    unsigned int u32EntryId;
}cal_voice_calllog_entry_t;

#define SIP_ADDR_LEN                250
#define COMMON_AUTH_LEN             129
#define PHONE_NUMBER_LEN            64 
#define COMMON_STR_LEN              16
#define KEY_STR_LEN                 8
#define DISPLAY_NAME_LEN            250

typedef struct cal_voice_provider_s {
	int  providerId;
    int  profileId;
	char name[128+1];
	char regServer[256+1];
	char regPort[8];
	char proxyServer[256+1];
	char proxyPort[8];
    char STUNServer[256+1];
} cal_voice_provider_t;

typedef struct cal_voice_check_provider_s {
    cal_voice_provider_t *general;
    char ob_proxy[SIP_ADDR_LEN];
    char ob_proxy_port[8];
}cal_voice_check_provider_t;

typedef struct cal_voice_line_reg_s {
    int  providerId;
	int  extLineId;
    char bEnable[20];
	char directoryNumber[32+1];
    char authUserName[128+1];
    char authPassword[128+1];
    char sipuri[512];    
} cal_voice_line_reg_t;

typedef struct cal_voice_line_feature_s {
	int  extLineId;
	char busy_reject[2];
	char lineuse[2];
	char clir[2]; 
} cal_voice_line_feature_t;

typedef struct cal_voice_line_s {
    int  providerId;
    int  profileId;
	int  extLineId;
    char bEnable[20];
    char status[20];
	char directoryNumber[32+1];
    char authUserName[128+1];
    char authPassword[128+1];
	char busy_reject[2];
	char lineuse[2];
	char clir[2];
} cal_voice_line_t;

typedef struct cal_line_map_s
{
	int  line_id;
	char directNumber[64];
    int  profile_id;
    int  inLineId;
}cal_line_map_t;

typedef struct cal_voice_callctrl_map_s
{
    char bEnable;
	int  extID;
    int  inMapNum;
	int  inMap[VOICE_MAX_LINE_NUM];
	int  outMap;
    char szAlternativeLineRef[33];
    int  unAlternativeLineIndex;
    char szExtenName[260];
    char szExtenType[12];
}cal_voice_callctrl_map_t;

typedef struct cal_vgw_provider_s {
    char proxy[SIP_ADDR_LEN];
    char proxy_port[8];
    char sec_proxy[SIP_ADDR_LEN];
    char sec_proxy_port[8];
    char reg_proxy[SIP_ADDR_LEN];
    char reg_proxy_port[8];
    char user_agent_domain[SIP_ADDR_LEN];
    char sec_user_agent_domain[SIP_ADDR_LEN];
    char ob_enable[2];
    char ob_proxy[SIP_ADDR_LEN];
    char ob_proxy_port[8];
    char sec_ob_proxy[SIP_ADDR_LEN];
    char sec_ob_proxy_port[8];
    char expire[10];
    char dnssrv_enable[2];
    int  sipprovider_id;
    int  profile_id;
} cal_vgw_provider_t;

typedef struct cal_vgw_line_reg_s {
    char enable[20];
    char user[COMMON_AUTH_LEN];
    char pw[COMMON_AUTH_LEN];
    char telno[PHONE_NUMBER_LEN];
    char display_name[DISPLAY_NAME_LEN];
    char single_use[2];
    char busy_reject[2];
    char telno_hide[2];
    int  send_reg;
    int  cf_mode;
    char CFU_number[KEY_STR_LEN];
    char CFB_number[KEY_STR_LEN];
    char CFN_number[KEY_STR_LEN];
    int  sipprovider_id;
    int  sipprofile_id;   // this id is xml profile node index 
    int  sipline_id;      // this id is xml line node index 
    int  extline_id;  
} cal_vgw_line_reg_t;

typedef struct cal_voice_dfnd_telConf_s {
    char authUserName[64];
    char authPassword[64];
    unsigned int registrarServerPort;
    char registrarServerTransport[5];
    char registrarServer[64];
    unsigned int registrationInterval;
} cal_voice_dfnd_telConf_t;

typedef struct cal_voice_dfnd_fxsConf_s {
    unsigned int callWaiting;
    char connectedDevice[32];
} cal_voice_dfnd_fxsConf_t;

typedef struct cal_codec_s
{
    unsigned short u16Entryid;
    char CodecName[32];
    unsigned short u16PacketizationPeriod;
    char bSilenceSuppression;
    char bEnabled;
    unsigned short u16Priority;
}cal_codec_t;

/* Voice codec types from /xChange/dslx_common/voice_res_gw/codec */
typedef enum
{
   CODEC_NULL           = (0),        /* NULL */
   CODEC_PCMU,   /* G.711 ulaw */
   CODEC_PCMA,   /* G.711 alaw */
   CODEC_G726_16,   /* G.726 - 16 kbps */
   CODEC_G726_24,   /* G.726 - 24 kbps */
   CODEC_G726_32,   /* G.726 - 32 kbps */
   CODEC_G726_40,   /* G.726 - 40 kbps */
   CODEC_G7231_53,   /* G.723.1 - 5.3 kbps */
   CODEC_G7231_63,   /* G.723.1 - 6.3 kbps */
   CODEC_G7231A_53,   /* G.723.1A - 5.3 kbps */
   CODEC_G7231A_63,   /* G.723.1A - 6.3 kbps */
   CODEC_G729A,  /* G.729A */
   CODEC_G729B,  /* G.729B */
   CODEC_G711_LINEAR,  /* Linear media queue data */
   CODEC_G728,  /* G.728 */
   CODEC_G729,  /* G.729 */
   CODEC_G729E,  /* G.729E */
   CODEC_BV16,  /* BRCM Broadvoice - 16 kbps */
   CODEC_BV32,  /* BRCM Broadvoice - 32 kbps */
   CODEC_NTE,  /* Named telephone events */
   CODEC_ILBC_20,  /* iLBC speech coder - 20 ms frame / 15.2 kbps */
   CODEC_ILBC_30,  /* iLBC speech coder - 30 ms frame / 13.3 kbps */
   CODEC_G7231_53_VAR, /* G723.1 variable rates (preferred=5.3) */
   CODEC_G7231_63_VAR, /* G723.1 variable rates (preferred=6.3) */
   CODEC_G7231_VAR, /* G723.1 variable rates */
   CODEC_T38,  /* T.38 fax relay */
   CODEC_T38_MUTE,  /* Mute before switching to T.38 fax relay */
   CODEC_RED,  /* Redundancy - RFC 2198 */
   CODEC_G722_MODE_1,  /* G.722 Mode 1 64 kbps */
   CODEC_LINPCM128,  /* Narrowband linear PCM @ 128 Kbps */
   CODEC_LINPCM256,  /* Wideband linear PCM @ 256 Kbps */

   CODEC_GSMAMR_12K,  /* GSM AMR codec @ 12.2 kbps */
   CODEC_GSMAMR_10K,  /* GSM AMR codec @ 10.2 kbps */
   CODEC_GSMAMR_795,  /* GSM AMR codec @ 7.95 kbps */
   CODEC_GSMAMR_740,  /* GSM AMR codec @ 7.4 kbps */
   CODEC_GSMAMR_670,  /* GSM AMR codec @ 6.7 kbps */
   CODEC_GSMAMR_590,  /* GSM AMR codec @ 5.9 kbps */
   CODEC_GSMAMR_515,  /* GSM AMR codec @ 5.15 kbps */
   CODEC_GSMAMR_475,  /* GSM AMR codec @ 4.75 kbps */

   CODEC_AMRWB_66,    /* AMR WB codec @ 6.6 kbps */
   CODEC_AMRWB_885,   /* AMR WB codec @ 8.85 kbps */
   CODEC_AMRWB_1265,  /* AMR WB codec @ 12.65 kbps */
   CODEC_AMRWB_1425,  /* AMR WB codec @ 14.25 kbps */
   CODEC_AMRWB_1585,  /* AMR WB codec @ 15.85 kbps */
   CODEC_AMRWB_1825,  /* AMR WB codec @ 18.25 kbps */
   CODEC_AMRWB_1985,  /* AMR WB codec @ 19.85 kbps */
   CODEC_AMRWB_2305,  /* AMR WB codec @ 23.05 kbps */
   CODEC_AMRWB_2385,  /* AMR WB codec @ 23.85 kbps */
   
   /* Maximum number of codec types. */
   CODEC_MAX_TYPES,

   /* Place-holder for dynamic codec types that haven't been mapped yet */
   CODEC_DYNAMIC        = (0xffff),

   /* Place-holder for unknown codec types that should be ignored/removed from list */
   CODEC_UNKNOWN        = (0xfffe)
} CODEC_TYPE;

///////////////////////////////////////////////////////////////////////////
char *cfg_voice_extProf_ext_callFea_callWaitingStatus_get(int id0, int id1, int id2);
int cfg_voice_extProf_ext_callFea_callWaitingStatus_set(int id0, int id1, int id2, char *val);
char *cfg_voice_codecList_entryID_get(int id0, int id1);
int cfg_voice_codecList_entryID_set(int id0, int id1, char *val);
char *cfg_voice_codecList_codec_get(int id0, int id1);
int cfg_voice_codecList_codec_set(int id0, int id1, char *val);
char *cfg_voice_codecList_bitRate_get(int id0, int id1);
int cfg_voice_codecList_bitRate_set(int id0, int id1, char *val);
char *cfg_voice_codecList_packetizationPeriod_get(int id0, int id1);
int cfg_voice_codecList_packetizationPeriod_set(int id0, int id1, char *val);
char *cfg_voice_codecList_silenceSuppression_get(int id0, int id1);
int cfg_voice_codecList_silenceSuppression_set(int id0, int id1, char *val);
char *cfg_voice_codecList_enable_get(int id0, int id1);
int cfg_voice_codecList_enable_set(int id0, int id1, char *val);
char *cfg_voice_codecList_priority_get(int id0, int id1);
int cfg_voice_codecList_priority_set(int id0, int id1, char *val);

char *cfg_voice_DECTFixedPart_enable_get(int id0, int id1);
int cfg_voice_DECTFixedPart_enable_set(int id0, int id1, char *val);
char *cfg_voice_DECTFixedPart_status_get(int id0, int id1);
int cfg_voice_DECTFixedPart_status_set(int id0, int id1, char *val);
char *cfg_voice_DECTFixedPart_rfpi_get(int id0, int id1);
int cfg_voice_DECTFixedPart_rfpi_set(int id0, int id1, char *val);
char *cfg_voice_DECTFixedPart_pin_get(int id0, int id1);
int cfg_voice_DECTFixedPart_pin_set(int id0, int id1, char *val);
char *cfg_voice_DECTFixedPart_NEMOEnable_get(int id0, int id1);
int cfg_voice_DECTFixedPart_NEMOEnable_set(int id0, int id1, char *val);
char *cfg_voice_DECTFixedPart_RFPowerControl_get(int id0, int id1);
int cfg_voice_DECTFixedPart_RFPowerControl_set(int id0, int id1, char *val);

char *cfg_voice_initialCall_targetNumber_get(int id0);
int cfg_voice_initialCall_targetNumber_set(int id0, char *val);
char *cfg_voice_initialCall_callDuration_get(int id0);
int cfg_voice_initialCall_callDuration_set(int id0, char *val);
char *cfg_voice_initialCall_callSuccessTime_get(int id0);
int cfg_voice_initialCall_callSuccessTime_set(int id0, char *val);
char *cfg_voice_initialCall_maximumRetryAttempts_get(int id0);
int cfg_voice_initialCall_maximumRetryAttempts_set(int id0, char *val);
char *cfg_voice_initialCall_retry_get(int id0);
int cfg_voice_initialCall_retry_set(int id0, char *val);
char *cfg_voice_initialCall_time_get(int id0);
int cfg_voice_initialCall_time_set(int id0, char *val);
char *cfg_voice_initialCall_enable_get(int id0);
int cfg_voice_initialCall_enable_set(int id0, char *val);
char *cfg_voice_initialCall_status_get(int id0);
int cfg_voice_initialCall_status_set(int id0, char *val);

char *cfg_voice_extProf_X_SC_SipExtAuthEnable_get(int id0, int id1);
int cfg_voice_extProf_X_SC_SipExtAuthEnable_set(int id0, int id1, char *val);
char *cfg_voice_extProf_SIPExt_Status_get(int id0, int id1, int id3);
int cfg_voice_extProf_SIPExt_Status_set(int id0, int id1, int id3, char *val);
char *cfg_voice_extProf_SIPExt_X_SC_PLC_EntryID_get(int id0, int id1, int id3);
int cfg_voice_extProf_SIPExt_X_SC_PLC_EntryID_set(int id0, int id1, int id3, char *val);
char *cfg_voice_extProf_SIPExt_AuthUserName_get(int id0, int id1, int id3);
int cfg_voice_extProf_SIPExt_AuthUserName_set(int id0, int id1, int id3, char *val);
char *cfg_voice_extProf_SIPExt_AuthPassword_get(int id0, int id1, int id3);
int cfg_voice_extProf_SIPExt_AuthPassword_set(int id0, int id1, int id3, char *val);
char *cfg_voice_netProf_sip_registrationPeriod_get(int id0, int id1);
int cfg_voice_netProf_sip_registrationPeriod_set(int id0, int id1, char *val);
char *cfg_voice_extProf_ext_X_SC_name_get(int id0, int id1, int id2);
int cfg_voice_extProf_ext_X_SC_name_set(int id0, int id1, int id2, char *val);
char *cfg_voice_netProf_line_sipRef_get(int id0, int id1, int id2);
int cfg_voice_netProf_line_sipRef_set(int id0, int id1, int id2, char *val);
char *cfg_voice_extProf_DECTPortablePartExt_status_get(int id0, int id1, int id2);
int cfg_voice_extProf_DECTPortablePartExt_status_set(int id0, int id1, int id2, char *val);
char *cfg_voice_extProf_DECTPortablePartExt_handsetType_get(int id0, int id1, int id2);
int cfg_voice_extProf_DECTPortablePartExt_handsetType_set(int id0, int id1, int id2, char *val);
char *cfg_voice_extProf_ext_status_get(int id0, int id1, int id2);
int cfg_voice_extProf_ext_status_set(int id0, int id1, int id2, char *val);
char *cfg_voice_line_callFea_callWaitingStatus_get(int id0, int id1, int id2);
int cfg_voice_line_callFea_callWaitingStatus_set(int id0, int id1, int id2, char *val);
char *cfg_voice_line_callFea_callWaitingEnable_get(int id0, int id1, int id2);
int cfg_voice_line_callFea_callWaitingEnable_set(int id0, int id1, int id2, char *val);
char *cfg_voice_line_callFea_anonymousCallEnable_get(int id0, int id1, int id2);
int cfg_voice_line_callFea_anonymousCallEnable_set(int id0, int id1, int id2, char *val);
char *cfg_voice_netProf_sipLine_entryID_get(int id0, int id1, int id2);
int cfg_voice_netProf_sipLine_entryID_set(int id0, int id1, int id2, char *val);

//////////////////////////////////////////////////////////////////////
char * int2str(int value);
int cal_voice_instance_get_array(int **array, const char *format, ...);
char *cal_voice_X_SC_DECT_Active_get();
int cal_voice_X_SC_DECT_Active_set(char *val);
char *cal_voice_X_SC_DECT_halb_get();
int cal_voice_X_SC_DECT_halb_set(char *val);
char *cal_voice_X_SC_DECT_Eco_Mode_get();
int cal_voice_X_SC_DECT_Eco_Mode_set(char *val);
char *cal_voice_X_SC_DECT_PIN_get();
int cal_voice_X_SC_DECT_PIN_set(char *val);
char *cal_voice_X_SC_DECT_Adddect_get();
int cal_voice_X_SC_DECT_Adddect_set(char *val);
char *cal_voice_NPNum_get(int voice);
char *cal_voice_PINum_get(int voice);
char *cal_voice_EPNum_get(int voice);
char *cal_voice_cap_maxNPCount_get(int voice);
char *cal_voice_cap_maxEPCount_get(int voice);
char *cal_voice_cap_maxLineCount_get(int voice);
char *cal_voice_cap_maxCallLogNum_get(int voice);
char *cal_voice_phyIntf_intfID_get(int voice, int intf);
char *cal_voice_phyIntf_desc_get(int voice, int intf);
char *cal_voice_netProf_enable_get(int voice, int netprof);
int cal_voice_netProf_enable_set(int voice, int netprof, char *val);
char *cal_voice_netProf_DTMFMethod_get(int voice, int netprof);
char *cal_voice_netProf_STUNEnable_get(int voice, int netprof);
char *cal_voice_netProf_STUNServer_get(int voice, int netprof);
char *cal_voice_netProf_numLines_get(int voice, int netprof);
char *cal_voice_netProf_name_get(int voice, int netprof);
int cal_voice_netProf_name_set(int voice, int netprof, char *val);
char *cal_voice_netProf_faxPassThrough_get(int voice, int netprof);
char *cal_voice_netProf_servPro_name_get(int voice, int netprof);
int cal_voice_netProf_servPro_name_set(int voice, int netprof, char *val);
char *cal_voice_netProf_servPro_URL_get(int voice, int netprof);
int cal_voice_netProf_servPro_URL_set(int voice, int netprof, char *val);
char *cal_voice_netProf_servPro_contactPhoneNumber_get(int voice, int netprof);
int cal_voice_netProf_servPro_contactPhoneNumber_set(int voice, int netprof, char *val);
char *cal_voice_netProf_servPro_emailAddress_get(int voice, int netprof);
int cal_voice_netProf_servPro_emailAddress_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_proxyServer_get(int voice, int netprof);
int cal_voice_netProf_sip_proxyServer_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_proxyServerPort_get(int voice, int netprof);
int cal_voice_netProf_sip_proxyServerPort_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_proxyServerTransport_get(int voice, int netprof);
int cal_voice_netProf_sip_proxyServerTransport_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_registrarServer_get(int voice, int netprof);
int cal_voice_netProf_sip_registrarServer_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_registrarServerPort_get(int voice, int netprof);
int cal_voice_netProf_sip_registrarServerPort_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_userAgentDomain_get(int voice, int netprof);
int cal_voice_netProf_sip_userAgentDomain_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_userAgentPort_get(int voice, int netprof);
int cal_voice_netProf_sip_userAgentPort_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_userAgentTransport_get(int voice, int netprof);
int cal_voice_netProf_sip_userAgentTransport_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_outboundProxy_get(int voice, int netprof);
int cal_voice_netProf_sip_outboundProxy_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_outboundProxyResolvedAddress_get(int voice, int netprof);
char *cal_voice_netProf_sip_outboundProxyPort_get(int voice, int netprof);
int cal_voice_netProf_sip_outboundProxyPort_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_organization_get(int voice, int netprof);
int cal_voice_netProf_sip_organization_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_registerExpires_get(int voice, int netprof);
int cal_voice_netProf_sip_registerExpires_set(int voice, int netprof, char *val);
char *cal_voice_netProf_sip_registerRetryInterval_get(int voice, int netprof);
int cal_voice_netProf_sip_registerRetryInterval_set(int voice, int netprof, char *val);
char *cal_voice_netProf_rtp_localPortMin_get(int voice, int netprof);
char *cal_voice_netProf_sip_DSCPMark_get(int voice, int netprof);
char *cal_voice_netProf_rtp_DSCPMark_get(int voice, int netprof);
char *cal_voice_netProf_faxT38_highSpeedRedundancy_get(int voice, int netprof);
char *cal_voice_netProf_faxT38_lowSpeedRedundancy_get(int voice, int netprof);
char *cal_voice_netProf_line_enable_get(int voice, int netprof, int line);
int cal_voice_netProf_line_enable_set(int voice, int netprof, int line, char *val);
char *cal_voice_netProf_line_directoryNumber_get(int voice, int netprof, int line);
int cal_voice_netProf_line_directoryNumber_set(int voice, int netprof, int line, char *val);
char *cal_voice_netProf_line_status_get(int voice, int netprof, int line);
char *cal_voice_netProf_line_sip_authUserName_get(int voice, int netprof, int line);
int cal_voice_netProf_line_sip_authUserName_set(int voice, int netprof, int line, char *val);
char *cal_voice_netProf_line_sip_authPassword_get(int voice, int netprof, int line);
int cal_voice_netProf_line_sip_authPassword_set(int voice, int netprof, int line, char *val);
char *cal_voice_extProf_enable_get(int voice, int extprof);
int cal_voice_extProf_enable_set(int voice, int extprof, char *val);
char *cal_voice_extProf_digitMap_get(int voice, int extprof);
char *cal_voice_extProf_extNum_get(int voice, int extprof);
char *cal_voice_extProf_name_get(int voice, int extprof);
int cal_voice_extProf_name_set(int voice, int extprof, char *val);
char *cal_voice_extProf_ext_extensionNumber_get(int voice, int extprof, int ext);
char *cal_voice_extProf_ext_connDev_get(int voice, int extprof, int ext);
char *cal_voice_extProf_ext_callFea_callerIDEnable_get(int voice, int extprof, int ext);
char *cal_voice_extProf_ext_callFea_callWaitingEnable_get(int voice, int extprof, int ext);
char *cal_voice_extProf_ext_callFea_callForwardUnconditionalEnablee_get(int voice, int extprof, int ext);
int cal_voice_extProf_ext_callFea_callForwardUnconditionalEnablee_set(int voice, int extprof, int ext, char *val);
char *cal_voice_extProf_ext_callFea_callForwardUnconditionalNumber_get(int voice, int extprof, int ext);
int cal_voice_extProf_ext_callFea_callForwardUnconditionalNumber_set(int voice, int extprof, int ext, char *val);
char *cal_voice_extProf_ext_callFea_callForwardOnBusyEnable_get(int voice, int extprof, int ext);
int cal_voice_extProf_ext_callFea_callForwardOnBusyEnable_set(int voice, int extprof, int ext, char *val);
char *cal_voice_extProf_ext_callFea_callForwardOnBusyNumber_get(int voice, int extprof, int ext);
int cal_voice_extProf_ext_callFea_callForwardOnBusyNumber_set(int voice, int extprof, int ext, char *val);
char *cal_voice_extProf_ext_callFea_callForwardOnNoAnswerEnable_get(int voice, int extprof, int ext);
int cal_voice_extProf_ext_callFea_callForwardOnNoAnswerEnable_set(int voice, int extprof, int ext, char *val);
char *cal_voice_extProf_ext_callFea_callForwardOnNoAnswerNumber_get(int voice, int extprof, int ext);
int cal_voice_extProf_ext_callFea_callForwardOnNoAnswerNumber_set(int voice, int extprof, int ext, char *val);
char *cal_voice_extProf_ext_callFea_callForwardOnNoAnswerRingTimeout_get(int voice, int extprof, int ext);
int cal_voice_extProf_ext_callFea_callForwardOnNoAnswerRingTimeout_set(int voice, int extprof, int ext, char *val);
char *cal_voice_line_callFea_callForwardUnconditionalEnablee_get(int voice, int nNetProvider, int nLine);
int cal_voice_line_callFea_callForwardUnconditionalEnablee_set(int voice, int nNetProvider, int nLine, char *val);
char *cal_voice_line_callFea_callForwardUnconditionalNumber_get(int voice, int nNetProvider, int nLine);
int cal_voice_line_callFea_callForwardUnconditionalNumber_set(int voice, int nNetProvider, int nLine, char *val);
char *cal_voice_line_callFea_callForwardOnBusyEnable_get(int voice, int nNetProvider, int nLine);
int cal_voice_line_callFea_callForwardOnBusyEnable_set(int voice, int nNetProvider, int nLine, char *val);
char *cal_voice_line_callFea_callForwardOnBusyNumber_get(int voice, int nNetProvider, int nLine);
int cal_voice_line_callFea_callForwardOnBusyNumber_set(int voice, int nNetProvider, int nLine, char *val);
char *cal_voice_line_callFea_callForwardOnNoAnswerEnable_get(int voice, int nNetProvider, int nLine);
int cal_voice_line_callFea_callForwardOnNoAnswerEnable_set(int voice, int nNetProvider, int nLine, char *val);
char *cal_voice_line_callFea_callForwardOnNoAnswerNumber_get(int voice, int nNetProvider, int nLine);
int cal_voice_line_callFea_callForwardOnNoAnswerNumber_set(int voice, int nNetProvider, int nLine, char *val);
char *cal_voice_line_callFea_callForwardOnNoAnswerRingTimeout_get(int voice, int nNetProvider, int nLine);
int cal_voice_line_callFea_callForwardOnNoAnswerRingTimeout_set(int voice, int nNetProvider, int nLine, char *val);
char *cal_voice_extProf_ext_callFea_callTransferEnable_get(int voice, int extprof, int ext);
char *cal_voice_extProf_ext_callFea_MWIEnable_get(int voice, int extprof, int ext);
int cal_voice_extProf_ext_callFea_MWIEnable_set(int voice, int extprof, int ext, char *val);
int cal_voice_extProf_ext_callFea_messageWaiting_set(int voice, int extprof, int ext, char *val);
char *cal_voice_extProf_ext_callFea_messageWaiting_get(int voice, int extprof, int ext);
char *cal_voice_extProf_ext_callFea_anonymousCallBlockEnable_get(int voice, int extprof, int ext);
char *cal_voice_extProf_ext_callFea_doNotDisturbEnable_get(int voice, int extprof, int ext);
char *cal_voice_extProf_ext_voProc_txGain_get(int voice, int extprof, int ext);
int cal_voice_extProf_ext_voProc_txGain_set(int voice, int extprof, int ext, char *val);
char *cal_voice_extProf_ext_voProc_rxGain_get(int voice, int extprof, int ext);
int cal_voice_extProf_ext_voProc_rxGain_set(int voice, int extprof, int ext, char *val);
char *cal_voice_callCon_interDigitTimerStd_get(int voice);
char *cal_voice_callCon_inMap_enable_get(int voice, int inmap);
int cal_voice_callCon_inMap_enable_set(int voice, int inmap, char *val);
int cal_voice_callCon_inMap_lineRef_set(int voice, int inmap, char *val);
int cal_voice_callCon_inMap_extensionRef_set(int voice, int inmap, char *val);
char *cal_voice_callCon_outMap_enable_get(int voice, int inmap);
int cal_voice_callCon_outMap_enable_set(int voice, int inmap, char *val);
#if 0
int cal_add_voice_extProf_OurContacts(int id0, int id1);
int cal_del_voice_extProf_OurContacts(int id0, int id1, int id2);
int cal_idxtoid_voice_extProf_OurContacts(int id0, int id1, int index);
int cal_voice_extProf_ourCont_add_new_one(SH_DECT_OUR_CONTACT_DATA *pEntry);
int cal_voice_extProf_ourCont_update(SH_DECT_OUR_CONTACT_DATA *pEntry);
int cal_voice_extProf_ourCont_delete_one(SH_DECT_OUR_CONTACT_DATA *pEntry);
int cal_voice_extProf_ourCont_delete_all(void);
int cal_voice_extProf_ourCont_get_xml_all(SH_DECT_OUR_CONTACT_ALL_DATA *pAllOurContactData);
int cal_voice_extProf_email_add_new_one(SH_EMAIL_ONE_ACCOUNT_LIST_DATA *pEntry);
int cal_voice_extProf_email_delete_all(void);
int cal_voice_extProf_email_get_xml_all(SH_EMAIL_ACCOUNT_LIST_DATA *pEmailAllData);
int cal_voice_extProf_rss_add_new_one(SH_RSS_ONE_CHANNEL_LIST_DATA *pEntry);
int cal_voice_extProf_rss_delete_all(void);
int cal_voice_extProf_rss_get_xml_all(SH_RSS_CHANNEL_LIST_DATA *pRssAllData);
#endif

int cal_voice_ipphone_number_check(char *provider, char *number, char* trans_number);
int cal_voice_telno_xml_duplicate_check(char *ipphone_number);
int cal_vocie_provider_updatedate_tr64_idx();
int cal_del_voice_line_updatedate_tr64_idx(int in_index);
int cal_voice_totalLines_get(int id0);
int cal_get_voice_net_Line(int id0);
int cal_add_voice_bng_netProf(int id0, char *type);
int cal_del_voice_netProf(int id0, int id1);
int cal_idxtoid_voice_netProf(int id0, int index);
int cal_idxtoid_voice_netProf_Line(int id0, int id1, int index);
int cal_idxtoid_voice_extProf_ext(int id0, int id1, int index);
int cal_add_voice_netProf_Line(int id0, int id1, int id2);
int cal_del_voice_netProf_Line(int id0, int id1, int id2);
int cal_voice_line_status_active();
int cal_add_voice_extProf(int id0, int id1);
int cal_del_voice_extProf(int id0, int id1);
int cal_add_voice_extProf_ext(int id0, int id1, int id2);
int cal_del_voice_extProf_ext(int id0, int id1, int id2);
int cal_add_voice_callCon_inMap(int id0, int id1);
int cal_voice_call_extension_SetDefaultInOutMap(int id0, int nExtensionIndex);
int cal_voice_call_extension_deleteInOutMap(int id0, int nExtensionIndex);
int cal_del_voice_callCon_inMap(int id0, int id1);
int cal_add_voice_callCon_outMap(int id0, int id1);
int cal_del_voice_callCon_outMap(int id0, int id1);
char *cal_voice_callCon_inMap_lineRef_get(int id0, int id1);
char *cal_voice_callCon_inMap_extensionRef_get(int id0, int id1);
char *cal_voice_callCon_outMap_extensionRef_get(int id0, int id1);
char *cal_voice_callCon_outMap_lineRef_get(int id0, int id1);
int cal_voice_callCon_calllog_entry_get(int type, cal_voice_calllog_entry_t* pMissEntry,cal_voice_calllog_entry_t *pAnswerEntry,cal_voice_calllog_entry_t *pDialEntry,int *pMissNum,int *pAnswerNum,int *pDialNum);
int cal_voice_service_get_all_number_of_line(int id0);
int cal_voice_service_add_all_number_of_line(int id0);
int cal_voice_service_sub_all_number_of_line(int id0);
int cal_voice_service_get_all_number_of_group(int id0);
int cal_voice_service_add_all_number_of_group(int id0);
int cal_voice_service_sub_all_number_of_group(int id0);
int cal_voice_service_assign_group_id(int id0);
int cal_voice_service_free_group_id(int id0, int freeId);
int cal_voice_service_assign_line_primary_id(int id0);
int cal_voice_netProf_line_id_get(int id0, int id1, int id2);
int cal_voice_netProf_line_id_set(int id0, int id1, int id2, int val);
int cal_voice_netProf_group_id_get(int id0, int id1, int id2);
int cal_voice_netProf_group_id_set(int id0, int id1, int id2, int val);
int cal_voice_netProf_add_group_id_to_list(int id0, int id1, int groupId);
int cal_voice_netProf_remove_group_id_from_list(int id0, int id1, int removeGroupId);
int cal_voice_netProf_check_id_in_group_list(int id0, int id1, int checkGroupId);
int cal_voice_num_of_line_in_group(int id0, int checkGroupId);
int cal_voice_transform_groupId_to_profileId(int extId);
int cal_voice_transform_extLineId_to_inLineId(int extId, int *profileId, int *lineId);
int cal_match_server_account_profId(int id0, cal_voice_check_provider_t *provider);
int cal_add_voice_group(int id0, cal_voice_provider_t *provider);
int cal_move_group_to_other_prof(int id0, int groupId, int oldProfId, int newProfId);
int cal_voice_num_of_group_in_prof(int id0, int profile_id);
int cal_voice_get_total_line_map(cal_line_map_t *lineMap, int maxLine, int active);
int cal_voice_num_of_active_line(void);
void cal_voice_auto_out_map_set(int id0);
int cal_take_voice_group(int id0, cal_voice_provider_t *provider);
int cal_voice_group_update(cal_voice_provider_t *provider);
int cal_voice_line_reg_update(cal_voice_line_reg_t *line);
int cal_voice_get_all_provider_data(cal_voice_provider_t *provider, int maxNum);
int cal_voice_get_all_cgi_provider_data(cal_voice_provider_t *provider, int maxNum);
int cal_voice_get_all_line_data(cal_voice_line_t *line, int maxNum);
int cfg_voice_get_all_cgi_line_data(cal_voice_line_t *line, int maxNum);
char *cal_voice_group_line_status_get(int id0, int extLineId);
int cal_voice_group_line_enable_set(int id0, int extLineId, char *val);
char *cal_voice_group_line_directoryNumber_get(int id0, int extLineId);
int cal_del_voice_group_Line(int id0, int extLineId);
int cal_del_voice_group(int id0, int groupId);
int cal_voice_get_total_in_out_map(cal_voice_callctrl_map_t * ctrlMap, int maxSize);
int cal_voice_group_line_feature_update(int id0, cal_voice_line_feature_t *feature);
int cal_voice_group_callctrl_outmap_single_set(int id0, cal_voice_callctrl_map_t *ctrlMap);
int cal_voice_callctrl_inmap_numOfextNum(int id0, char *extNum);
int cal_voice_callctrl_rebuild_inmap(int id0, char *extNum);
int cal_voice_group_callctrl_inmap_single_set(int id0, cal_voice_callctrl_map_t *ctrlMap);
int cal_voice_get_vgw_all_provider_data(cal_vgw_provider_t *provider, int maxNum);
int cal_voice_get_vgw_all_line_data(cal_vgw_line_reg_t *line, int maxNum);
char *cal_voice_group_sip_outboundProxy_get(int id0, int groupId);
int cal_voice_group_sip_outboundProxy_set(int id0, int groupId, char *val);
char *cal_voice_group_sip_outboundProxyPort_get(int id0, int groupId);
int cal_voice_group_sip_outboundProxyPort_set(int id0, int groupId, char *val);
char *cal_voice_group_sip_registrarServer_get(int id0, int groupId);
char *cal_voice_group_sip_registrarServerPort_get(int id0, int groupId);
void cal_voice_acsAuto_profile_check_del(void);
int cal_voice_acsAuto_profile_lineNum_get(void);
void cal_voice_all_line_unregister(void);
int cal_voice_bng_profile_lineNum_get(void);
int cal_cgi_extID_to_extIndex(int extID);
void cal_get_voip_line_status(int netprof, int line, char *buf, int len);
int cal_voice_neoVoice_resources_check(void);
int cal_voice_neoVoice_register(int entryId);
int cal_voice_neoVoice_deregister(int entryId);
int cal_voice_neoVoice_extId_get(int neoVoiceId);
int cal_voice_dfnd_telephonyConfiguration_get(int dfnd_id, cal_voice_dfnd_telConf_t *telConf);
int cal_voice_dfnd_fxsConfiguration_get(int dfnd_id, cal_voice_dfnd_fxsConf_t *fxsConf);
int cal_voice_dfnd_telephonyConfiguration_set(cal_voice_dfnd_telConf_t *telConf);
int cal_voice_dfnd_fxsConfiguration_set(cal_voice_dfnd_fxsConf_t *fxsConf);
int cal_voice_codecList_get(int id0, cal_codec_t *codecList, int listSize);
void cal_voice_fw_update_data_transform(char *fw_ver);
void voip_dect_ptr_back2old(void);

/*to add here*/
#endif
