#ifndef _UTILITY_H_
#define _UTILITY_H_
#include "scutil.h"
#include <netinet/in.h>
#include <sys/socket.h>

typedef enum {
    A_ERROR = -1,               /* Generic error return */
    A_OK = 0,                   /* success */
    A_EINVAL,                   /* Invalid parameter */     
    A_NO_MEMORY,  
	A_ENOENT, 
	A_EXIST    
} A_STATUS;



#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif

#define LOCAL   static

#define WLAN_MAC_ADDR_SIZE      6
union wlanMACAddr {
    A_UINT8  octets[WLAN_MAC_ADDR_SIZE];
    A_UINT16 words[WLAN_MAC_ADDR_SIZE/2];
};
typedef union wlanMACAddr WLAN_MACADDR;

#define A_MACADDR_COPY(from, to)              \
    do {                                      \
        (to)->words[0] = (from)->words[0];    \
        (to)->words[1] = (from)->words[1];    \
        (to)->words[2] = (from)->words[2];    \
    } while (0)

#define A_MACADDR_COMP(m1, m2)                \
    ((((m1)->words[2] == (m2)->words[2]) &&   \
      ((m1)->words[1] == (m2)->words[1]) &&   \
      ((m1)->words[0] == (m2)->words[0])) == 0)
      
/*utility functions*/
int SYSTEM(const char *format, ...) ;
int COMMAND(const char *format, ...);
int myPipe(char *command, char **output);
int process_running(char *name);
int get_numeric_by_cmd(char *cmd, char *key);
int chek_numeric_string(char *buffer);
int chek_pppoe_setup_account(char *buffer);

int scIsIpAddress(A_UINT8 *ipAddr);
#ifdef SUPPORT_MULTIWAN_DOMAIN
char *scUrlIsDomain(A_UINT8 *domain);
#endif
int strNull( char *str);

void scToLows(A_UINT8 *charStr);
void scToUppers(A_UINT8 *charStr); 	
int scValidStr(A_UINT8 *charStr); 	
int scValidUrl(A_UINT8 *charStr);
int scValidIPv6(A_UINT8 *ipStr, A_UINT8 flag);
int scValidGWv6(A_UINT8 *ipStr);
int scValidMSName(A_UINT8 *str, A_UINT8 len);
int scValidDNSName(A_UINT8 *str, A_UINT8 len);
int scValidEmailAddr(A_UINT8 *email, A_UINT8 len);
int scChars2Hexs(unsigned char *charStr, int strLen, char *hexBuf , char *separator);
int macAddrToString(char *macAddress, char *buf , char *separator);
A_INT16 scHex2Char(A_UINT8 * str, A_UINT8 len, A_INT32 * value);
A_INT16 scHexs2Chars(A_UINT8 * hexs, A_UINT8 * str, A_UINT8 len, A_INT16 interval);
void scMacStr17ToStr12(A_UINT8 *str17, A_UINT8 *str12);
void scMacStr12ToStr17(A_UINT8 *str12, A_UINT8 *str17, char *separator);
A_BOOL  scValidHex(char ch);
A_BOOL  scValidHexs(char *str, int len);
A_BOOL 	scValidNetbiosName(char *pName, A_UINT16 len);
A_BOOL scValidIpAddress(A_UINT32 ipAddress);
A_BOOL scValidIpMask(A_UINT32 ipMask, A_UINT32 *pValidIpMask);
A_BOOL scValidIpGateWay(A_UINT32 gateway);
A_BOOL scValidIpMaskGateWay(A_UINT32 ipaddr, A_UINT32 netmask, A_UINT32 gateway);
A_BOOL asciiToPassphraseKey(A_UINT8 *pstr, A_UINT8 *pPpKey, int encryptedKeyLen);
A_BOOL scValidpassPhrase(char *phrase, int len);
void sgml_encode(char *pStrDest, char *pStrSrc, A_BOOL readOnly);
void scSecretHide(char *secret);
A_BOOL scSecretHidden(char *secret);
A_UINT16 scGetWord(A_UINT8 * buf);
void scSetWord(A_UINT8 * buf, A_UINT16 wValue);
A_UINT32 scGetDword(A_UINT8 * buf);
void scSetDword(A_UINT8 * buf, A_UINT32 dwValue);	

/* add by archer for statistical */
typedef struct if_adv_info_s{
    char ifname[16];
    unsigned long long rx_packets;	/* total packets received       */
	unsigned long long tx_packets;	/* total packets transmitted    */
	unsigned long long rx_bytes;	/* total bytes received         */
	unsigned long long tx_bytes;	/* total bytes transmitted      */
	unsigned long errors;	/* bad packets received         */
	unsigned long dropped;	/* no space in linux buffers    */
	unsigned long tx_errors;	/* bad packets transmitted         */
	unsigned long tx_dropped;	/* no space in linux buffers    */
}if_adv_info_t;

struct net_device_info {
	unsigned long long rx_packets;	/* total packets received       */
	unsigned long long tx_packets;	/* total packets transmitted    */
	unsigned long long rx_bytes;	/* total bytes received         */
	unsigned long long tx_bytes;	/* total bytes transmitted      */
	unsigned long rx_errors;	/* bad packets received         */
	unsigned long tx_errors;	/* packet transmit problems     */
	unsigned long rx_dropped;	/* no space in linux buffers    */
	unsigned long tx_dropped;	/* no space available in linux  */
	unsigned long rx_multicast;	/* multicast packets received   */
	unsigned long rx_compressed;
	unsigned long tx_compressed;
	unsigned long collisions;
	
    unsigned long rx_fifo_errors;	/* recv'r fifo overrun          */
    unsigned long tx_fifo_errors;
    unsigned long rx_frame_errors;	/* recv'd frame alignment error */
    unsigned long tx_carrier_errors;
};

typedef struct cfg_elem_s
{
    char *value;
    char *name;
}cfg_elem_t;
typedef struct cwmp_autonomous_s{
    char *pAnnounceURL;
    char *pTransferURL;
    char *pFileType;    
    char *pTargetFileName;    
    int iIsDownload;
    int ifileSize;
    int  iFaultStruct;
    time_t  tStartTime;
    time_t  tCompleteTime;
}cwmp_autonomous_t;

#define    MAX_APP_CFG_PATH_LEN            100

#define    LOAD_CFG_SUCCESS        0
#define    LOAD_CFG_ERROR          -1

/* add end */

int getCfgInfo(const char *cfgFilePath, cfg_elem_t *cfg);
int getIIPaddress(char *if_name, char *ipaddr);
int getIFAdvInfo(char *if_name, if_adv_info_t *if_info);
int getFlashMacAddress(char *pMac);
void libGetAPMacAddress(char *pMac);
void libGetLanMacAddress(char *pMac);
void libGetWanMacAddress(int wanId, char *mac_str);
int  lib_get_wan_mac_address(int wanId,char *mac);
int  lib_get_lan_mac_address(char *mac);
char* libGetWiFiMacAddress(int index);
char* libGetXDSLMacAddress(void);
char* libGetWANMacAddress(int index);
char* libGetPLCMacAddress(void);
char* getDefaultPasswd(void);
char* getDefaultSSID(void);
char* getDefaultWPAKEY(void);
char* getDefaultPIN(void);
void getManufacturerName(char *buffer);
int getProductName(char *buf);
int getFwVersion(char *buf);
int getVolumeLevel(char *buf);
int getVolumeLevelOld(char *buf);
int getBootVersion(char *buf);
int getDSLmodemVersion(char *buf);
int getDECTbaseVersion(char *buf);
int getPLCVersion(char *buf);
int getSerialNum(char *buf);
int getOemName(char *oemName);
int getManufacturerOUI(char *buf);
int getProductDesc(char *buffer);
void getExpireTimeofDay(char *buffer, time_t expiretime_remaining);
void getPrivacyNextEvent(char *buffer, time_t expiretime_remaining, int hour);
void getTZwithDST(char *buffer);
#ifdef SUPPORT_OD69
void getDateTimeForTR181(char *buffer);
#endif
void getUpTime(char *buffer);
void getHwVersion(char *buffer);
void getManufacturer(char *buffer);
void getVersion(char *buffer);
int getProductClass(char *buf);
int getModelName(char *buf);
unsigned short getVersion2(void);
int getversion3(char *version);
int getBuildTime(char* pTimeStr);
int getmode(char * mode);
char* getPPPConnectionProvider(char *buf);
int get_UpTime_sec(char *buffer);
int get_IPV6_DNS_primary(char *buffer);
int get_IPV6_DNS_secondary(char *buffer);
int get_ipv6_assigned_address_prefix(char *buffer);
int get_lan_used_address_range(char *buffer);
int get_ipv6_gua_address(char *buffer);
int get_ipv6_gateway_address(char *buffer);
int get_ipv6_prefix_lifetime(int *pltime, int *vltime);
int time_t_2_DateTime(time_t time, char *t);
int get_ipv6_gua_lft(char *ifname, char *pre_lft, char *vl_lft);
#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN            46
#endif
typedef struct if_infov6_s{
	char ifname[16];
	char ipaddr[INET6_ADDRSTRLEN];
    char gw[INET6_ADDRSTRLEN];
	
}if_infov6_t;
int getMgtBrv6Info(if_infov6_t *if_info);
int getIP6Info(char *ifname, char *address);
int getIP6Prefix1(char*ifname, char *address);
int getIP6GwInfo(char *ifname, char *gw );
int getEthernetStatus(void);
char * apCfgScPidGet(void);
int getDeviceStartType(void);

void country_list_generate(void);
void set_default_country(void);

A_BOOL  scCompositor(int v[], int left, int right);
A_BOOL scConversionSSID(A_UINT8 *src, A_UINT8 *dest);
A_BOOL scConversionASCII(A_UINT8 *src, A_UINT8 *dest);
A_BOOL scConvertFirmwareVersion(char *version);
A_BOOL scVoIPExist(void);
A_BOOL  scWirelessCardExist(int unit);
unsigned char scWirelessCardType(int unit);
int  sc5GChannelExtensionGet(int channel);
int  scChannelExtensionGet(int channel);
int scChannelVailableCheck(int unit, int channel);

A_STATUS scWirelessRadioInfoStrGet(char* buf, int unit);

int scCountrySupportHT40(int unit, int country);
int scCountrySupport11A(int country);
int scChannelSupportHT40(int channel);
int scChannelSupportHT(int channel);

A_BOOL sc_RadioChannelUpdate(void);
A_BOOL sc_sleep(unsigned int val);
char *scManRateStrGet(int datarate);
int scWlanUpDownRecord(int );
int syslog_savetoall(void);

char* getSubnetStr(int ip, int mask);
int getSubnetPrefixLen(int mask);

int getLanToWanIdBinding(int *);


/*
 * get ethernet port status
 */
int scEthernetPortStatusGet(int);

int scFileCopy(char *File_from, char *File_to);

enum{
	MODE_FULL = 1,
	MODE_HALF = 0,
};
enum{
	SPEED_1000 = 0,
	SPEED_100 = 2,
	SPEED_10 = 4,
	ETHER_ON = 8,
	ETHER_OFF = 16,
};

#define UPGRADE_RESULT			"/tmp/var/upld_result"
int scUpgStatusGet(char *);

enum{
	POE_LINK_ERROR = -1,
	POE_LINK_DISCONNECT = 0,
	POE_LINK_CONNECT,
	POE_LINK_WAIT,
	POE_LINK_FAILED,
};
			
enum{
	POE_LCP_ERROR = -1,
	POE_LCP_SUCCESS = 0,
	POE_LCP_INIT,
	POE_LCP_COMEUP,
	POE_LCP_DOWN,
	POE_LCP_REJECT,
};

enum{
	POE_AUTH_ERROR = -1,
	POE_AUTH_SUCCESS = 0,
	POE_AUTH_FAIL,
};
enum{
	INTERNET_ERROR = -1,
	INTERNET_CONNECT = 0,
	INTERNET_FAIL,
	INTERNET_DISCONNECT,
};

char *scVoIPToneTypeNameMappingGet(int type);
char *scVoIPCoderTypeMappingGet(int type);
#define SC_CRYPT_SALT           "$1$SERCOMM$"

long get_uptime(void);
int scIsAllnumber(A_UINT8 *str);

#define MAC_BCAST_ADDR		(unsigned char *) "\xff\xff\xff\xff\xff\xff"

int divide_str_to_array(char *s, char divide_symbol, char **array, int array_num);
void free_array_str(char **array, int array_num);

void get_ebtables_mac_with_token(const char *mac, char *ebtablesMac, char *token);
int sc_is_ipv4_prefix(char *str);
int sc_is_validate_value_range(char *str, char token, int begin_c, int end_c);
int sc_is_validate_interface(char *str);
int sc_is_validate_mac(char *str);
int util_mask_to_prefix(char *mask);
int util_convert_string_to_array(int ** array, char* p, char token);

#define _UTIL_MBUG_
void _util_mbug(const char *file, const char* func, int line, char *format, ...);
#define util_mbug(format, arg...) _util_mbug(__FILE__, __FUNCTION__, __LINE__, format, ##arg);




enum{
	VOIP_EXE_FINISH = 0,
	VOIP_EXE_STOP,
	VOIP_EXE_START,
};
#define VOIP_EXE_STATUS "/tmp/voip_exe_status"
void set_voip_exe_status(int st);
int get_voip_exe_status();

struct parsed_url {
	char *scheme;               /* mandatory */
	char *host;                 /* mandatory */
	char *port;                 /* optional */
	char *path;                 /* optional */
	char *query;                /* optional */
	char *fragment;             /* optional */
	char *username;             /* optional */
	char *password;             /* optional */
};

int parse_url(char *url, struct parsed_url **ppurl);
void parsed_url_free(struct parsed_url *purl);

/* for get port status */
#define SIOCMIBINFO                 (SIOCDEVPRIVATE + 3)
struct sc_port_status
{
    int link;//mib ulIfLastChange actually;
    int speed;
    int duplex;
};
/* end */

int get_call_status(char *buffer);
int getFonStatus(char *buf);
int getFonSessionUsersOnline(char *buf);
int getFonSessionStart(char *buf);
int getFonSessionUsers(char *buf);
int getFonSessionNAU(char *buf);
int getFonSessionAF(char *buf);
int getFonSessionBytesSent(char *buf);
int getFonSessionBytesReceived(char *buf);
int getFonTotalSessions(char *buf);
int getFonTotalUsers(char *buf);
int getFonTotalNAU(char *buf);
int getFonTotalAF(char *buf);

int get_RebootTime(char *buf);
int set_RebootTime(char *time);
int sc_reboot(void);
int get_mac_from_ipv4(char *mac, char *ip);
int get_mac_from_ipv6(char *mac, char *ip);
int sc_pppoe_tagged(void);
int scCheckInternetPassword(char *password);
int scConvertInternetPassword(char *password,char *buf);
char *string_encode(char code, char *str);
char *string_decode(char *str);
#define CALL_STATUS_ALL_IDLE            0
#define CALL_STATUS_EMERGENCY           11
int check_voice_is_connect(void);
int utf8_to_unicode(char* pInput, char** ppOutput);
void free_autonomous_struct(cwmp_autonomous_t* _pautonomous);
int cwmp_autonomous_even(cwmp_autonomous_t * _pautonomous);
int cwmp_autonomous_download_fail(cwmp_autonomous_t * _pautonomous);
int cwmp_autonomous_download_success(cwmp_autonomous_t * _pautonomous);
int cwmp_autonomous_upload_fail(cwmp_autonomous_t * _pautonomous);
int cwmp_autonomous_upload_success(cwmp_autonomous_t * _pautonomous);
int sc_getPidByName(const char *name);
int authe_list_checked(int wl_cnt);
int sc_get_port_status(struct sc_port_status *port_status, char *name); 
int sc_update_voip_server_to_dnsmasq(char *server_name); 

/*
 * Email Abuse Detection Functions
 */
#define EA_IWA_PATH          "/mnt/appdat/iwa.csv"
#define EA_IWA_DEF_PATH      "/etc/iwa.csv"
int EA_compare_version(int maj1, int min1, int maj2, int min2);
char* EA_get_running_info(int *major, int *minor, int *year, int *month, int *day);
char* EA_trim_fqdn(const char *fqdn);
#ifdef _SC_HOMEPLUG_
void resetPLCSetting(void);
#endif

char *shellcmd_dp_convert(char *str);
int shellcmd_connectors_check(char *str);
#endif
