/**
 * @file   
 * @author 
 * @date   2012-07-02
 * @brief  
 *
 * Copyright - 2012 SerComm Corporation. All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document without notice.
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising
 * out of the application or use of any product or circuit. SerComm Corporation specifically
 * disclaims any and all liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of others.
 */
/**
 * @file wifi_define_bcm
 * @author Andy wang
 * @date   2012-07-1802
 * @brief  wifi_define_bcm  
 *
 * Copyright - 2012 SerComm Corporation. All Rights Reserved. 
 * SerComm Corporation reserves the right to make changes to this document without notice. 
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability 
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising 
 * out of the application or use of any product or circuit. SerComm Corporation specifically 
 * disclaims any and all liability, including without limitation consequential or incidental damages; 
 * neither does it convey any license under its patent rights, nor the rights of others. 
 */

#ifndef __WIFI_DEFINE_BCM__
#define __WIFI_DEFINE_BCM__


#define WL_RADIO_NUM  2
#define WL_MAX_NUM_SSID  2

#ifdef HW_STARTER
#define  MAX_WLAN_IF  1               //SINGLE RADIO  DUAL BAND
#else 
#define  MAX_WLAN_IF  2               //DUAL RADIO  DUAL BAND
#endif 
#define DEFAULT_MAX_NUM_SSID  WL_RADIO_NUM*WL_MAX_NUM_SSID+1 /*MAX_NUM_SSID*radio numer(2:2.4G+5G) , +1 because the index 0 in xml is useless.*/

#define DEFAULT_WIFI_RADIO_ALL      0
#define DEFAULT_WIFI_RADIO_24GHZ    1
#define DEFAULT_WIFI_RADIO_5GHZ     2

#define DEFAULT_WANID DEFAULT_WIFI_RADIO_24GHZ
#define DEFAULT_WANID_5GHZ DEFAULT_WIFI_RADIO_5GHZ

#define DEFAULT_WIFI_24GHZ_SSID1    1
#define DEFAULT_WIFI_24GHZ_SSID2    2
#define DEFAULT_WIFI_5GHZ_SSID1     3
#define DEFAULT_WIFI_5GHZ_SSID2     4

//#define DEFAULT_WIFI_24GHZ_SSID1    1
//#define DEFAULT_WIFI_24GHZ_SSID2    2
//#define DEFAULT_WIFI_24GHZ_SSID3    3
//#define DEFAULT_WIFI_24GHZ_SSID4    4
//#define DEFAULT_WIFI_5GHZ_SSID1     5
//#define DEFAULT_WIFI_5GHZ_SSID2     6
//#define DEFAULT_WIFI_5GHZ_SSID3     7
//#define DEFAULT_WIFI_5GHZ_SSID4     8

#define DEFAULT_24G_MAINSSID DEFAULT_WIFI_24GHZ_SSID1
#define DEFAULT_5G_MAINSSID DEFAULT_WIFI_5GHZ_SSID1

#define BCM_24G_RADIO_INDEX		0
#ifdef HW_STARTER
#define BCM_5G_RADIO_INDEX		0
#else
#define BCM_5G_RADIO_INDEX		1
#endif 
#define FON_SSID_24G "wl0.1"
#define FON_SSID_5G  "wl1.1"

#define RADIO_MSSID_NAME  "/tmp/wRadio_%d_MSSID_%d_UP"
#define RADIO_STATUS_24GUP "/tmp/wlan24GUP"
#define RADIO_STATUS_5GUP  "/tmp/wlan5GUP"

#define RADIO_NAME_24G "Radio_24G"
#define RADIO_NAME_5G "Radio_5G"


#define RADIO_MAC_RATE_5G_867Mbps "867"
#define RADIO_MAC_RATE_5G_300Mbps "300"
#define RADIO_MAC_RATE_5G_450Mbps "450"

#define RADIO_MAX_RATE_24G_300MBps "300"
#define RADIO_MAX_RATE_24G_144MBps "144"
#define RADIO_MAX_RATE_24G_54MBps "54"

#define ABOVECONTROlCHANNEL  "AboveControlChannel"
#define BELOWCONTROlCHANNEL  "BelowControlChannel"
#define AUTOCONTROlCHANNEL   "Auto"

//#define WPS20_LOGO  0

#ifdef HW_STARTER
#define WIFI_24G_BAND "0" 
#define WIFI_5G_BAND  "1"
#endif 
#endif //__WIFI_DEFINE_BCM__
