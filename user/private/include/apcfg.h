
#ifndef __APCFGh
#define __APCFGh
#include <netinet/in.h>
#include <arpa/inet.h>

#include "utility.h"

int apcprint(const char *format, ...);
#ifdef G_DEBUG
#define G_debug(...) do{\
    char buf[256] = ""; \
    FILE *fp; \
    snprintf(buf, sizeof(buf), __VA_ARGS__); \
    fp = fopen("/tmp/tmp_gavin", "a+"); \
    if(pf) \
    { \
        fprintf(fp, "%s\n", buf); \
        fclose(fp); \
    } \
    }while(0)
#else
#define G_Debug(...)
#endif

#define CFG_MAX_DOMAINNMLEN       128
#define VLAN_TAG_MAX		4094
#define VLAN_TAG_MIN		1
#define VOIP_SIP_TELNO_LEN_MAX   256
#define CFG_MIN_8021P_PRIORITY    0
#define CFG_MAX_8021P_PRIORITY    7
#define CFG_MIN_PRIORITY_MODE   0
#define CFG_MAX_PRIORITY_MODE    7

#define CFG_MAX_PASSPHRASE       63
#define MIN_PASSPHRASE_SIZE      8
#define ENABLE          "1"
#define DISABLE         "0"

#define DEV_TYPE_BRIDGE 0
#define DEV_TYPE_ROUTER 1

#define NV_NAME_LEN (128)
#define NV_VLAUE_LEN (256)

#define 	HEX_PIDOFF_HWID 			8
#define     HEX_PIDOFF_PRODUCTID      	76  
#define 	HEX_PIDOFF_SWVERSION		100
#define 	HEX_HWID_LEN				12
#define     HEX_PRODUCTID_LEN        	4

/********************************************************/
/*		Get/Set function on system		 				*/	
/********************************************************/
char *   apCfgSysNameGet(void);
#define DEFAULT_SYSNAME                 ""
#define MAX_SYSNAME                     15

#define DEFAULT_DESC                 ""
#define MAX_DESC                     39

/*
 * Country/Region Codes from MS WINNLS.H
 * Numbering from ISO 3166
 */
enum CountryCode {
    CTRY_DEFAULT			  = 0,
    CTRY_ALBANIA              = 8,       /* Albania */
    CTRY_ALGERIA              = 12,      /* Algeria */
    CTRY_ARGENTINA            = 32,      /* Argentina */
    CTRY_ARMENIA              = 51,      /* Armenia */
    CTRY_AUSTRALIA            = 36,      /* Australia */
    CTRY_AUSTRIA              = 40,      /* Austria */
    CTRY_AZERBAIJAN           = 31,      /* Azerbaijan */
    CTRY_BAHRAIN              = 48,      /* Bahrain */
    CTRY_BELARUS              = 112,     /* Belarus */
    CTRY_BELGIUM              = 56,      /* Belgium */
    CTRY_BELIZE               = 84,      /* Belize */
    CTRY_BOLIVIA              = 68,      /* Bolivia */
    CTRY_BRAZIL               = 76,      /* Brazil */
    CTRY_BRUNEI_DARUSSALAM    = 96,      /* Brunei Darussalam */
    CTRY_BULGARIA             = 100,     /* Bulgaria */
    CTRY_CANADA               = 124,     /* Canada */
    CTRY_CHILE                = 152,     /* Chile */
    CTRY_CHINA                = 156,     /* People's Republic of China */
    CTRY_COLOMBIA             = 170,     /* Colombia */
    CTRY_COSTA_RICA           = 188,     /* Costa Rica */
    CTRY_CROATIA              = 191,     /* Croatia */
    CTRY_CYPRUS               = 196,
    CTRY_CZECH                = 203,     /* Czech Republic */
    CTRY_DENMARK              = 208,     /* Denmark */
    CTRY_DOMINICAN_REPUBLIC   = 214,     /* Dominican Republic */
    CTRY_ECUADOR              = 218,     /* Ecuador */
    CTRY_EGYPT                = 818,     /* Egypt */
    CTRY_EL_SALVADOR          = 222,     /* El Salvador */
    CTRY_ESTONIA              = 233,     /* Estonia */
    CTRY_FAEROE_ISLANDS       = 234,     /* Faeroe Islands */
    CTRY_FINLAND              = 246,     /* Finland */
    CTRY_FRANCE               = 250,     /* France */
    CTRY_FRANCE2              = 255,     /* France2 */
    CTRY_GEORGIA              = 268,     /* Georgia */
    CTRY_GERMANY              = 276,     /* Germany */
    CTRY_GREECE               = 300,     /* Greece */
    CTRY_GUATEMALA            = 320,     /* Guatemala */
    CTRY_HONDURAS             = 340,     /* Honduras */
    CTRY_HONG_KONG            = 344,     /* Hong Kong S.A.R., P.R.C. */
    CTRY_HUNGARY              = 348,     /* Hungary */
    CTRY_ICELAND              = 352,     /* Iceland */
    CTRY_INDIA                = 356,     /* India */
    CTRY_INDONESIA            = 360,     /* Indonesia */
    CTRY_IRAN                 = 364,     /* Iran */
    CTRY_IRAQ                 = 368,     /* Iraq */
    CTRY_IRELAND              = 372,     /* Ireland */
    CTRY_ISRAEL               = 376,     /* Israel */
    CTRY_ITALY                = 380,     /* Italy */
    CTRY_JAMAICA              = 388,     /* Jamaica */
    CTRY_JAPAN                = 392,     /* Japan */
    CTRY_JAPAN1               = 393,     /* Japan (JP1) */
    CTRY_JAPAN2               = 394,     /* Japan (JP0) */
    CTRY_JAPAN3               = 395,     /* Japan (JP1-1) */
    CTRY_JAPAN4               = 396,     /* Japan (JE1) */
    CTRY_JAPAN5               = 397,     /* Japan (JE2) */
    CTRY_JAPAN6               = 4006,     /* Japan (J6) */

    CTRY_JAPAN7		      = 4007,	 /* Japan (J7) */
    CTRY_JAPAN8		      = 4008,	 /* Japan (J8) */
    CTRY_JAPAN9		      = 4009,	 /* Japan (J9) */

    CTRY_JAPAN10	      = 4010,	 /* Japan (J10) */
    CTRY_JAPAN11	      = 4011,	 /* Japan (J11) */
    CTRY_JAPAN12	      = 4012,	 /* Japan (J12) */

    CTRY_JAPAN13	      = 4013,	 /* Japan (J13) */
    CTRY_JAPAN14	      = 4014,	 /* Japan (J14) */
    CTRY_JAPAN15	      = 4015,	 /* Japan (J15) */

    CTRY_JAPAN16	      = 4016,	 /* Japan (J16) */
    CTRY_JAPAN17	      = 4017,	 /* Japan (J17) */
    CTRY_JAPAN18	      = 4018,	 /* Japan (J18) */

    CTRY_JAPAN19	      = 4019,	 /* Japan (J19) */
    CTRY_JAPAN20	      = 4020,	 /* Japan (J20) */
    CTRY_JAPAN21	      = 4021,	 /* Japan (J21) */

    CTRY_JAPAN22	      = 4022,	 /* Japan (J22) */
    CTRY_JAPAN23	      = 4023,	 /* Japan (J23) */
    CTRY_JAPAN24	      = 4024,	 /* Japan (J24) */
 
    CTRY_JAPAN25	      = 4025,	 /* Japan (J25) */
    CTRY_JAPAN26	      = 4026,	 /* Japan (J26) */
    CTRY_JAPAN27	      = 4027,	 /* Japan (J27) */
    CTRY_JAPAN28	      = 4028,	 /* Japan (J28) */
    CTRY_JAPAN29	      = 4029,	 /* Japan (J29) */
    CTRY_JAPAN30	      = 4030,	 /* Japan (J30) */
    CTRY_JAPAN31	      = 4031,	 /* Japan (J31) */
    CTRY_JAPAN32	      = 4032,	 /* Japan (J32) */
    CTRY_JAPAN33	      = 4033,	 /* Japan (J33) */
    CTRY_JAPAN34	      = 4034,	 /* Japan (J34) */
    CTRY_JAPAN35	      = 4035,	 /* Japan (J35) */

    CTRY_JAPAN36          = 4036,    /* Japan (J36) */
    CTRY_JAPAN37          = 4037,    /* Japan (J37) */
    CTRY_JAPAN38          = 4038,    /* Japan (J38) */
    CTRY_JAPAN39          = 4039,    /* Japan (J39) */
    CTRY_JAPAN40          = 4040,    /* Japan (J40) */
    CTRY_JAPAN41          = 4041,    /* Japan (J41) */
    CTRY_JAPAN42          = 4042,    /* Japan (J42) */
    CTRY_JAPAN43          = 4043,    /* Japan (J43) */
    CTRY_JAPAN44          = 4044,    /* Japan (J44) */
    CTRY_JAPAN45          = 4045,    /* Japan (J45) */
    CTRY_JAPAN46          = 4046,    /* Japan (J46) */
    CTRY_JAPAN47          = 4047,    /* Japan (J47) */
    CTRY_JAPAN48          = 4048,    /* Japan (J48) */
    CTRY_JAPAN49          = 4049,    /* Japan (J49) */
    CTRY_JAPAN50          = 4050,    /* Japan (J50) */
    CTRY_JAPAN51          = 4051,    /* Japan (J51) */
    CTRY_JAPAN52          = 4052,    /* Japan (J52) */
    CTRY_JAPAN53          = 4053,    /* Japan (J53) */
    CTRY_JAPAN54          = 4054,    /* Japan (J54) */
    CTRY_JAPAN55          = 4055,    /* Japan (J55) */
    CTRY_JAPAN56          = 4056,    /* Japan (J56) */

    CTRY_JAPAN57          = 4057,    /* Japan (J57) */
    CTRY_JAPAN58          = 4058,    /* Japan (J58) */
    CTRY_JAPAN59          = 4059,    /* Japan (J59) */

    CTRY_AUSTRALIA2           = 5000,    /* Australia */
    CTRY_CANADA2              = 5001,    /* Canada */

    CTRY_JORDAN               = 400,     /* Jordan */
    CTRY_KAZAKHSTAN           = 398,     /* Kazakhstan */
    CTRY_KENYA                = 404,     /* Kenya */
    CTRY_KOREA_NORTH          = 408,     /* North Korea */
    CTRY_KOREA_ROC            = 410,     /* South Korea */
    CTRY_KOREA_ROC2           = 411,     /* South Korea */
    CTRY_KOREA_ROC3           = 412,     /* South Korea */
    CTRY_KUWAIT               = 414,     /* Kuwait */
    CTRY_LATVIA               = 428,     /* Latvia */
    CTRY_LEBANON              = 422,     /* Lebanon */
    CTRY_LIBYA                = 434,     /* Libya */
    CTRY_LIECHTENSTEIN        = 438,     /* Liechtenstein */
    CTRY_LITHUANIA            = 440,     /* Lithuania */
    CTRY_LUXEMBOURG           = 442,     /* Luxembourg */
    CTRY_MACAU                = 446,     /* Macau */
    CTRY_MACEDONIA            = 807,     /* the Former Yugoslav Republic of Macedonia */
    CTRY_MALAYSIA             = 458,     /* Malaysia */
    CTRY_MALTA		      = 470,	 /* Malta */
    CTRY_MEXICO               = 484,     /* Mexico */
    CTRY_MONACO               = 492,     /* Principality of Monaco */
    CTRY_MOROCCO              = 504,     /* Morocco */
    CTRY_NETHERLANDS          = 528,     /* Netherlands */
    CTRY_NETHERLANDS_ANTILLES = 530,     /* Netherlands Antilles */
    CTRY_NEW_ZEALAND          = 554,     /* New Zealand */
    CTRY_NICARAGUA            = 558,     /* Nicaragua */
    CTRY_NORWAY               = 578,     /* Norway */
    CTRY_OMAN                 = 512,     /* Oman */
    CTRY_PAKISTAN             = 586,     /* Islamic Republic of Pakistan */
    CTRY_PANAMA               = 591,     /* Panama */
    CTRY_PARAGUAY             = 600,     /* Paraguay */
    CTRY_PERU                 = 604,     /* Peru */
    CTRY_PHILIPPINES          = 608,     /* Republic of the Philippines */
    CTRY_POLAND               = 616,     /* Poland */
    CTRY_PORTUGAL             = 620,     /* Portugal */
    CTRY_PUERTO_RICO          = 630,     /* Puerto Rico */
    CTRY_QATAR                = 634,     /* Qatar */
    CTRY_ROMANIA              = 642,     /* Romania */
    CTRY_RUSSIA               = 643,     /* Russia */
    CTRY_SAUDI_ARABIA         = 682,     /* Saudi Arabia */
    CTRY_SERBIA_MONTENEGRO    = 891,     /* Serbia and Montenegro */
    CTRY_SINGAPORE            = 702,     /* Singapore */
    CTRY_SLOVAKIA             = 703,     /* Slovak Republic */
    CTRY_SLOVENIA             = 705,     /* Slovenia */
    CTRY_SOUTH_AFRICA         = 710,     /* South Africa */
    CTRY_SPAIN                = 724,     /* Spain */
    CTRY_SRI_LANKA	      = 144,     /* Sri Lanka */
    CTRY_SWEDEN               = 752,     /* Sweden */
    CTRY_SWITZERLAND          = 756,     /* Switzerland */
    CTRY_SYRIA                = 760,     /* Syria */
    CTRY_TAIWAN               = 158,     /* Taiwan */
    CTRY_THAILAND             = 764,     /* Thailand */
    CTRY_TRINIDAD_Y_TOBAGO    = 780,     /* Trinidad y Tobago */
    CTRY_TUNISIA              = 788,     /* Tunisia */
    CTRY_TURKEY               = 792,     /* Turkey */
    CTRY_UAE                  = 784,     /* U.A.E. */
    CTRY_UKRAINE              = 804,     /* Ukraine */
    CTRY_UNITED_KINGDOM       = 826,     /* United Kingdom */
    CTRY_UNITED_STATES        = 840,     /* United States */
    CTRY_UNITED_STATES_FCC49  = 842,     /* United States (Public Safety)*/
    CTRY_URUGUAY              = 858,     /* Uruguay */
    CTRY_UZBEKISTAN           = 860,     /* Uzbekistan */
    CTRY_VENEZUELA            = 862,     /* Venezuela */
    CTRY_VIET_NAM             = 704,     /* Viet Nam */
    CTRY_YEMEN                = 887,     /* Yemen */
    CTRY_ZIMBABWE             = 716      /* Zimbabwe */
};




#define DEBUG_USERNAME          "debug"
#define DEBUG_PASSWORD          "hjy_debug"

#define CFG_MIN_REBOOT_TIME        1
#define CFG_MAX_REBOOT_TIME        1000
enum 
{
    REBOOT_UNIT_SECOND=0,
    REBOOT_UNIT_MINUTE,
    REBOOT_UNIT_HOUR,
    REBOOT_UNIT_DAY,
    REBOOT_UNIT_WEEK,
    REBOOT_UNIT_MONTH
};


/*
 * switch port parameters
 */
#define MAX_VLAN_LIST          128
int cfgSwitchVlanModeGet(void);
A_STATUS cfgSwitchVlanModeSet(int v);
#define SWITCH_VLAN_ENABLE	1
#define SWITCH_VLAN_DISABLE	0

int cfgSwitchPortVidGet(int port);
A_STATUS cfgSwitchPortVidSet(int port, int v);
int cfgSwitchPortPriGet(int port);
A_STATUS cfgSwitchPortPriSet(int port, int v);
int cfgSwitchPortPriModeGet(int port);
int cfgSwitchPortMVidGet(int port);
A_STATUS cfgSwitchPortMVidSet(int port, int v);
int cfgSwitchVlanModeGet(void);
A_STATUS cfgSwitchVlanModeSet(int v);
int cfgSwitchPortVidGet(int port);
A_STATUS cfgSwitchVlanListApply(void);
A_STATUS cfgSwitchVlanListSet(char *p_str);
char *cfgSwitchVlanListGet(void);
A_STATUS cfgLayer3VlanSet(char *p_val);
char *cfgLayer3VlanGet(void);
A_STATUS cfgBRLayer3VlanSet(char *p_val);
A_STATUS cfgWanBindVlanSet(int wan, char *p_val);
char *cfgWanBindVlanGet(int wan);


#define CONNECT_MODE_ENABLE			3
#define CONNECT_MODE_WAN			2
#define CONNECT_MODE_LAN			1
#define CONNECT_MODE_DISABLE		0
/*
* Arpping 
*/
#define MIN_ARPPING_PERIOD  1
#define MAX_ARPPING_PERIOD  3600
#define MIN_ARPPING_TIMEOUT 1
#define MAX_ARPPING_TIMEOUT 3600
struct arpping_info {
    int wan_id;
    char if_name[16];
    struct in_addr src;                     /* Sender IP address */
    struct in_addr dst;                     /* Sender IP address */
    unsigned int arp_period;
    unsigned int arp_reply_timeout;
    unsigned int arp_ping_fail_count;
    unsigned int success_count;
    unsigned int failed_count;
    unsigned int average;
    unsigned int min;
    unsigned int max;
};

#endif
