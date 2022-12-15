#ifndef _CFG_dsl_H_
#define _CFG_dsl_H_

char* cal_dsl_v_basic_support_get();
char* cal_dsl_v_basic_select_get();
char* cal_dsl_v_al_prof_get();
char* cal_dsl_v_cur_prof_get();
char* cal_dsl_v_lpath_get();
char* cal_dsl_atm_link_type_get();
int cal_dsl_atm_link_type_set(char* val);
char* cal_dsl_atm_dest_addr_get();
int cal_dsl_atm_dest_addr_set(char* val);
char* cal_dsl_atm_encap_get();
int cal_dsl_atm_encap_set(char* val);
char* cal_dsl_atm_qos_class_get();
int cal_dsl_atm_qos_class_set(char* val);
char* cal_dsl_atm_PCR_get();
int cal_dsl_atm_PCR_set(char* val);
char* cal_dsl_atm_max_burst_size_get();
int cal_dsl_atm_max_burst_size_set(char* val);
char* cal_dsl_atm_SCR_get();
int cal_dsl_atm_SCR_set(char* val);
char* cal_dsl_FirmwareVersion_get();
int cal_dsl_FirmwareVersion_set(char* val);
char* cal_dsl_UpstreamMaxBitRate_get();
int cal_dsl_UpstreamMaxBitRate_set(char* val);
char* cal_dsl_DownstreamMaxBitRate_get();
int cal_dsl_DownstreamMaxBitRate_set(char* val);
/*to add here*/
#endif
