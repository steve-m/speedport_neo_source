#ifndef _SC_APPLY_H_
#define _SC_APPLY_H_

#include "scapply_client.h"

#define APL_FLAG_DIR            "/tmp/apl_flag"
#define APL_FLAG                APL_FLAG_DIR"/%d"

#define APL_FLAG_FILE_SPECIAL_NUMBER    (0) //it's for rft630 only, remove it later
#define APL_FLAG_FILE_INIT_NUMBER       (1)

#define APL_FLAG_NAME_LEN_MAX           (64)

#define APL_FLAG_CMD_LEN_MAX            (128)
#define APL_FLAG_MEMBERS_NUM_IN_CMD_MAX (8)
#define APL_FLAG_SEPARATE_SYMBOL        ','

enum
{
    APL_NONE=-1,      
    APL_BEGIN=0,      
    APL_ROOT=APL_BEGIN,      
    APL_REBOOT,    
    APL_LOGIN,     
    APL_TELNET,    
    APL_FTPD,
    APL_SSH,       
    APL_HTTPD,
    APL_BRIDGE,
    APL_CATV,
    APL_LOG,
    APL_FLASHLOG,
    APL_NTP,
    APL_SNMP,
    APL_TR069,
    APL_QTBL,
    APL_SRT,
    APL_ROUTEINFO,
    APL_GPONDEBUG,
    APL_RIP,
//LAN Features    
    APL_LANIPv4,
    APL_LANIF,
    APL_LANDHCPMODE,
    APL_NETWORKMAP,
    APL_STATICIP,
    APL_RADVD,
    APL_ULA,
    APL_DHCP6S,
    APL_LANIPv6,
//WAN Feateures
    APL_DHCP4C,
    APL_DHCP6C,
    APL_WAN,
    APL_WANIF,
    APL_WANIP,
    APL_WANIP1,
    APL_WANIP2,
    APL_ND_RETRANS,
    APL_RELOADPPPOE,
    APL_PRT,
    APL_IGDUPNP,
    APL_IGMPPROXY,
    APL_FIREWALL,
    APL_FW_PROTECT,
#ifdef OTE
    APL_FW_SPI_PROTECT,
#endif
    APL_FW_DOS,
    APL_FW_PORTSCAN,
    APL_FW_PING2WAN,
    APL_FW_ILGDGRAM,
    APL_FW_ALGH323,
    APL_FW_ALGSIP,
    APL_FW_ALGRTSP,
    APL_FW_VPNPASS_IPSEC,
    APL_FW_VPNPASS_PPTP,
    APL_FW_VPNPASS_L2TP,
    APL_FW_MGNTACL,
    APL_FW_DMZ,
    APL_FW_SPAPPS,
    APL_FW_VS,
    APL_FW_PTFILTER,
    APL_FW_IPFILTER,
    APL_FW_PCTRL,
    APL_FW_NAT,
    APL_DDNS,
// IPV6 Static DNS
    APL_DNS,     
    APL_VOIP,
    APL_VOIP_STATS,
//QoS
    APL_QOS_EGRESS,
    APL_QOS_INGRESS,
    APL_QOS_CLASSIFY,
    APL_QOS_RESTART,
//WLAN
    APL_WLAN,
    APL_WLAN_X,
    APL_WLAN_SCHEDULER,
//FON
    APL_FON,
    APL_FON_ACTIVE,
//Volume
    APL_VOLUME,
//PPPoe Passthrough
    APL_PPPOEPASSTHROUGH,
//ABUSE
    APL_ABUSE,
    APL_ABUSE_AUPD,
    APL_DEBUG,    
//Other not used
    APL_VLAN,
    APL_DESCRIPTION,
    APL_ETHSUP,
    APL_LLTD,
    APL_STP,
    APL_IGMPSNOOPING,
    APL_WLAN0,  
    APL_WLAN0_VAP0,
    APL_WLAN0_VAP1,
    APL_WLAN0_VAP2,
    APL_WLAN0_VAP3,
    APL_WLAN0_VAP4,
    APL_WLAN0_VAP5,
    APL_WLAN0_VAP6,
    APL_WLAN0_VAP7,
    APL_WLAN1, 
    APL_WLAN1_VAP0,
    APL_WLAN1_VAP1,
    APL_WLAN1_VAP2,
    APL_WLAN1_VAP3,
    APL_WLAN1_VAP4,
    APL_WLAN1_VAP5,
    APL_WLAN1_VAP6,
    APL_WLAN1_VAP7,
    APL_WLAN0_VAP8,
    APL_WLAN1_VAP8,
//Storage
    APL_SYNC, 
    APL_BACKUP, 
    APL_MEDIASRV,
    APL_SMB,
    APL_FTP,
    APL_MUSERS,
    APL_GUEST,
//Timerule
    APL_TRULE,
    APL_DSL_DIAG,
    APL_ETHACCESS,
    APL_HOMEPLUG_EN,
    APL_HOMEPLUG_LN,
    APL_HOMEPLUG_NPW,
    APL_HOMEPLUG_FCCO,
    APL_HOMEPLUG_HFID,
//Password
    APL_PASSWORD,
    APL_TR232,
    APL_END,
};

int apl_do_apply(int fileno);

//for rft630 only, need remove it later
void apl_set_flag(unsigned int id);

void apl_set_flag_new(int fileno, int id, int type, char *instance, int action);
int apcfgHaveChanged(int fileno);

#endif
