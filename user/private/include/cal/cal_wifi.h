#ifndef _CFG_wifi_H_
#define _CFG_wifi_H_

#define WIFI_SEC_NONE               "None"
#define WIFI_SEC_WEP64              "WEP-64"
#define WIFI_SEC_WEP128             "WEP-128"
#define WIFI_SEC_WPAPSK             "WPA-Personal"
#define WIFI_SEC_WPA2PSK            "WPA2-Personal"
#define WIFI_SEC_WPAPSKMIX          "WPA-WPA2-Personal"
#define WIFI_SEC_WPARADIO           "WPA-Enterprise"
#define WIFI_SEC_WPA2RADIO          "WPA2-Enterprise"
#define WIFI_SEC_WPARADIOMIX        "WPA-WPA2-Enterprise"

#define WIFI_SEC_CIPHER_TKIP        "TKIP"
#define WIFI_SEC_CIPHER_AES         "AES"
#define WIFI_SEC_CIPHER_AES_TKIP    "AES-TKIP"
#include "cal_cfg.h"



int cal_AccessPoint_AssociatedDevice_entry_update(int APindex);
char* cal_wifi_RadioNumberOfEntries_get();
char* cal_wifi_SSIDNumberOfEntries_get();
char* cal_wifi_AccessPointNumberOfEntries_get();
char* cal_wifi_ConfigChanged_get();
int cal_wifi_ConfigChanged_set(char* val);
#ifdef HW_STARTER
char* cal_wifi_X_SC_WifiMode_get();
int cal_wifi_X_SC_WifiMode_set(char* val);
#endif 
char* cal_wifi_Enable_get(int radio);
int cal_wifi_Enable_set(int radio, char* val);
char *cal_wifi_Status_get(int radio);
int cal_wifi_Alias_set(int radio, char *val);
char *cal_wifi_Alias_get(int radio);
char *cal_wifi_Name_get(int radio);
char *cal_wifi_Upstream_get(int radio);
char *cal_wifi_MaxBitRate_get(int radio);
char *cal_wifi_OperatingFrequencyBand_get(int radio);
int cal_wifi_OperatingFrequencyBand_set(int radio, char *val);
char *cal_wifi_SupportedStandardsget(int radio);
char *cal_wifi_PossibleChannelsget(int radio);
char *cal_wifi_ChannelsInUseget(int radio);
char *cal_wifi_AutoChannelSupported(int radio);
char *cal_wifi_MCS_get(int radio);
int cal_wifi_MCS_set(int radio, char *val);
char *cal_wifi_TransmitPowerSupported(int radio);
char *cal_wifi_IEEE80211hSupported(int radio);
char *cal_wifi_StatsBytesSent_get(int ssid);
char *cal_wifi_StatsBytesReceived_get(int ssid);
char *cal_wifi_StatsPacketsSent_get(int ssid);
char *cal_wifi_StatsErrorsSent_get(int ssid);
char *cal_wifi_StatsErrorsReceived_get(int ssid);
char* cal_wifi_SupportedFrequencyBands_get(int radio);
char* cal_wifi_OperatingStandards_get(int radio);
int cal_wifi_OperatingStandards_set(int radio, char* val);
char* cal_wifi_Channel_get(int radio);
int cal_wifi_Channel_set(int radio, char* val);
char* cal_wifi_AutoChannelEnable_get(int radio);
int cal_wifi_AutoChannelEnable_set(int radio, char* val);
char* cal_wifi_OperatingChannelBandwidth_get(int radio);
int cal_wifi_OperatingChannelBandwidth_set(int radio, char* val);
char* cal_wifi_ExtensionChannel_get(int radio);
int cal_wifi_ExtensionChannel_set(int radio, char* val);
char* cal_wifi_GuardInterval_get(int radio);
int cal_wifi_GuardInterval_set(int radio, char* val);
char* cal_wifi_TransmitPower_get(int radio);
int cal_wifi_TransmitPower_set(int radio, char* val);
char *cal_wifi_X_SC_OutputPower_get(int radio);
int cal_wifi_X_SC_OutputPower_set(int radio, char *val);
char* cal_wifi_IEEE80211hEnabled_get(int radio);
int cal_wifi_IEEE80211hEnabled_set(int radio, char* val);
char* cal_wifi_IEEE80211dEnabled_get(int radio);
int cal_wifi_IEEE80211dEnabled_set(int radio, char* val);
char* cal_wifi_RegulatoryDomain_get(int radio);
int cal_wifi_RegulatoryDomain_set(int radio, char* val);
char* cal_wifi_speed_get(int radio);
int cal_wifi_speed_set(int radio, char* val);
char* cal_wifi_Coexistence_get(int radio);
int cal_wifi_Coexistence_set(int radio, char* val);

char* cal_wifi_LowerLayers_get(int ssid);
int cal_wifi_LowerLayers_set(int ssid, char* val);
char* cal_wifi_SSID_get(int ssid);
int cal_wifi_SSID_set(int ssid, char* val);
char *cal_wifi_ssid_Enable_get(int ssid);
int cal_wifi_ssid_Enable_set(int ssid, char *val);
char *cal_wifi_ssid_Status_get(int ssid);
char *cal_wifi_ssid_Alias_get(int ssid);
int cal_wifi_ssid_Alias_set(int ssid, char *val);
char *cal_wifi_ssid_BSSID_get(int ssid);
char *cal_wifi_ssid_MACAddress_get(int ssid);
char *cal_wifi_ssid_StatsBytesSent_get(int ssid);
char *cal_wifi_ssid_StatsBytesReceived_get(int ssid);
char *cal_wifi_ssid_StatsPacketsSent_get(int ssid);
char *cal_wifi_ssid_StatsErrorsSent_get(int ssid);
char *cal_wifi_ssid_StatsErrorsReceived_get(int ssid);


char* cal_wifi_ap_Enable_get(int ap);
int cal_wifi_ap_Enable_set(int ap, char* val);

char *cal_wifi_ap_Status_get(int ap);
char *cal_wifi_ap_WMMCapability_get(int ap);
char *cal_wifi_ap_UAPSDCapability_get(int ap);
char *cal_wifi_ap_AssociatedDeviceNumberOfEntries_get(int ap);
char *cal_wifi_ap_SecurityModesSupported_get(int ap);

char *cal_wifi_ap_WPS_ConfigMethodsEnabled_get(int ap);
int  cal_wifi_ap_WPS_ConfigMethodsEnabled_set(int ap, char *val);

char *cal_wifi_ap_SecurityCipherConfigMethods_get(int ap);
int cal_wifi_ap_SecurityCipherConfigMethods_set(int ap, char *val);

char* cal_wifi_ap_SSIDReference_get(int ap);
int cal_wifi_ap_SSIDReference_set(int ap, char* val);
char* cal_wifi_ap_SSIDAdvertisementEnabled_get(int ap);
int cal_wifi_ap_SSIDAdvertisementEnabled_set(int ap, char* val);
char* cal_wifi_ap_WMMEnable_get(int ap);
int cal_wifi_ap_WMMEnable_set(int ap, char* val);
char* cal_wifi_ap_UAPSDEnable_get(int ap);
int cal_wifi_ap_UAPSDEnable_set(int ap, char* val);
char* cal_wifi_ap_AccessControl_get(int ap);
int cal_wifi_ap_AccessControl_set(int ap, char* val);
char* cal_wifi_ap_AccessControlList_get(int ap);
int cal_wifi_ap_AccessControlList_set(int ap, char* val);
char* cal_wifi_ap_TimeRule_get(int ap);
int cal_wifi_ap_TimeRule_set(int ap, char* val);
char* cal_wifi_ap_TimeRuleDay_get(int ap);
int cal_wifi_ap_TimeRuleDay_set(int ap, char* val);
char* cal_wifi_ap_TimeRuleMon_get(int ap);
int cal_wifi_ap_TimeRuleMon_set(int ap, char* val);
char* cal_wifi_ap_TimeRuleTue_get(int ap);
int cal_wifi_ap_TimeRuleTue_set(int ap, char* val);
char* cal_wifi_ap_TimeRuleWed_get(int ap);
int cal_wifi_ap_TimeRuleWed_set(int ap, char* val);
char* cal_wifi_ap_TimeRuleThu_get(int ap);
int cal_wifi_ap_TimeRuleThu_set(int ap, char* val);
char* cal_wifi_ap_TimeRuleFri_get(int ap);
int cal_wifi_ap_TimeRuleFri_set(int ap, char* val);
char* cal_wifi_ap_TimeRuleSta_get(int ap);
int cal_wifi_ap_TimeRuleSta_set(int ap, char* val);
char* cal_wifi_ap_TimeRuleSun_get(int ap);
int cal_wifi_ap_TimeRuleSun_set(int ap, char* val);
int cal_wifi_ap_TimeRuleSun_set(int ap, char *val);
char *cal_wifi_ap_MaxAssociatedDevices_get(int ap);
char* cal_wifi_ap_ModeEnabled_get(int ap);
int cal_wifi_ap_ModeEnabled_set(int ap, char* val);
char *cal_wifi_ap_WEPKey_Index_get(int ap);
int cal_wifi_ap_WEPKey_Index_set(int ap, char *val);
char* cal_wifi_ap_WEPKey_get(int ap);
int cal_wifi_ap_WEPKey_set(int ap, char* val);
char *cal_wifi_ap_WEPKey_1_get(int ap);
int cal_wifi_ap_WEPKey_1_set(int ap, char *val);
char *cal_wifi_ap_WEPKey_2_get(int ap);
int cal_wifi_ap_WEPKey_2_set(int ap, char *val);
char *cal_wifi_ap_WEPKey_3_get(int ap);
int cal_wifi_ap_WEPKey_3_set(int ap, char *val);
char* cal_wifi_ap_PreSharedKey_get(int ap);
int cal_wifi_ap_PreSharedKey_set(int ap, char* val);
char* cal_wifi_ap_KeyPassphrase_get(int ap);
int cal_wifi_ap_KeyPassphrase_set(int ap, char* val);
char* cal_wifi_ap_wps_Enable_get(int ap);
int cal_wifi_ap_wps_Enable_set(int ap, char* val);
char* cal_wifi_ap_wps_ConfigMethodsSupported_get(int ap);

int cal_wifi_AccessControlList_set(char *pHostListStr);
//add by adley 
int cal_wlan_host_entry_tab_get(int id0, cfg_lan_host_entry_t **pp_cfg_lan_host_entry);
//add end 

/*to add here*/
#endif
