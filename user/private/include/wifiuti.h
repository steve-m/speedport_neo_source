#ifndef _WIFI_UTI_H_
#define _WIFI_UTI_H_
void ATH_SCRIPT_DEL(char *scriptFile);
int ATH_SCRIPT_ADD(char *scriptFile, const char *format, ...);
void ATH_SCRIPT_RUN(char *scriptFile);
void wlanCreatWscConfig(int unit, int vap);
void wlanKillVap(char *scriptfile, int unit, int vap);
void wlanKillAllVap(char *scriptfile);
void wlanBasicApply(char *scriptfile, int wifi, int unit, int vap, int, int);
void wlanWdsApply(char *scriptfile, int unit, int vap_id);
void wlanAdvanceApply(char *scriptfile, int unit, int vap, int);
void wlanAclApply(char *scriptfile, int unit, int vap);
void wlanAclListApply(char *scriptfile, int unit);
void wlanSecurityApply(char *scriptfile, int unit, int vap);
void wlanNoApSecurityApply(char *scriptfile, int unit, int sta);
void wlanBridgeApply(char *scriptfile, int unit, int bss, int wds);
void wlanCorrectChannelOffsetApply(int unit);
int wlanModuleLoad(char *scriptfile, int unit);
int wlanModuleUnload(char *scriptfile, int unit);
int wlanStart(char *scriptfile, int wifi, int unit);
int wlanStop(char *scriptfile, int wifi, int unit, int unload_module/*1,0*/);
#endif
