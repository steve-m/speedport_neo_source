#ifndef _CFG_Management_H_
#define _CFG_Management_H_

char *cal_Management_enable_get();
int cal_Management_enable_set(char *val);
char* cal_Management_URL_get();
int cal_Management_URL_set(char* val);
char* cal_Management_username_get();
int cal_Management_username_set(char* val);
char* cal_Management_password_get();
int cal_Management_password_set(char* val);
char* cal_Management_periodicInform_enable_get();
int cal_Management_periodicInform_enable_set(char* val);
char* cal_Management_periodicInform_Interval_get();
int cal_Management_periodicInform_Interval_set(char* val);
char* cal_Management_periodicInform_time_get();
int cal_Management_periodicInform_time_set(char* val);
char* cal_Management_parameterkey_get();
int cal_Management_parameterkey_set(char* val);
char* cal_Management_connectionrequest_URL_get();
int cal_Management_connectionrequest_URL_set(char* val);
char* cal_Management_connectionrequest_username_get();
int cal_Management_connectionrequest_username_set(char* val);
char* cal_Management_connectionRequest_password_get();
int cal_Management_connectionRequest_password_set(char* val);
char *cal_Management_UpgradesManaged_get();
int cal_Management_UpgradesManaged_set(char *val);

/* ManageableDevice */
int cal_Management_ManageableDevice_entry_get(int id, void **);
int cal_Management_ManageableDevice_entry_set(int id, void *);
int cal_Management_ManageableDevice_entry_del(int host_id);
int cal_Management_ManageableDevice_entry_add(char *option_125, char *ipstr);
/*to add here*/
#endif
