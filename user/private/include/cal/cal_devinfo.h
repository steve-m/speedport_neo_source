#ifndef _CAL_DEVINFO_H_
#define _CAL_DEVINFO_H_

char* cal_devinfo_Manufacturer_get();
int cal_devinfo_Manufacturer_set(char* val);
char* cal_devinfo_ManufacturerOUI_get();
int cal_devinfo_ManufacturerOUI_set(char* val);
char* cal_devinfo_ModelName_get();
int cal_devinfo_ModelName_set(char* val);
char* cal_devinfo_Description_get();
int cal_devinfo_Description_set(char* val);
char* cal_devinfo_ProductClass_get();
int cal_devinfo_ProductClass_set(char* val);
char* cal_devinfo_SerialNumber_get();
int cal_devinfo_SerialNumber_set(char* val);
char* cal_devinfo_HardwareVersion_get();
int cal_devinfo_HardwareVersion_set(char* val);
char* cal_devinfo_SoftwareVersion_get();
int cal_devinfo_SoftwareVersion_set(char* val);
char* cal_devinfo_ProvisioningCode_get();
int cal_devinfo_ProvisioningCode_set(char* val);
char* cal_devinfo_X_SC_Volume_Level_get();
int cal_devinfo_X_SC_Volume_Level_set(char* val);
char* cal_devinfo_UpTime_get();
int cal_devinfo_UpTime_set(char* val);
int cal_devinfo_DeviceLog_set(char* val);
char* cal_devinfo_X_SC_BootCodeVersion_get();
int cal_devinfo_X_SC_BootCodeVersion_set(char* val);
int cal_devinfo_process_entry_get(int id, void **);
int cal_devinfo_process_entry_set(int id, void *);
int cal_devinfo_process_entry_del(int id);
int cal_devinfo_process_entry_update(void);
char* cal_devinfo_DeviceLog_get(int * g_syslog_entry_num);
/*to add here*/


#if 0
#include "utility.h"

char *cal_dev_get_name(void);
char *cal_dev_get_manufacturer(void);
char *cal_dev_get_manufaurl(void);
char *cal_dev_get_manufaoui(void);
char *cal_dev_get_modelname(void);
char *cal_dev_get_modelnum(void);
char *cal_dev_get_modelurl(void);
char *cal_dev_get_descrip(void);
char *cal_dev_get_sn(void);
char *cal_dev_get_hwver(void);
char *cal_dev_get_swver(void);
char *cal_dev_get_fwver(void);
char *cal_dev_get_provision(void);
char *cal_dev_get_uptime(void);
int cal_dev_set_provision(char * value);
#endif

#endif
