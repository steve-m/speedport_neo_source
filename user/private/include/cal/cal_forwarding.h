#ifndef _CAL_FORWARDING_H_
#define _CAL_FORWARDING_H_


#define CAL_FORWARD_TMP_MAX_CHAR    8
#define CAL_FORWARD_IP_MAX_CHAR     16
#define CAL_FORWARD_IF_MAX_CHAR     256

#define CAL_FORWARD_MAX             256
#define CAL_FORWARD_MAX_ENTRY_NUM   20

typedef struct
{
    char key[CAL_FORWARD_TMP_MAX_CHAR];
    char index[CAL_FORWARD_TMP_MAX_CHAR];
    char enable[CAL_FORWARD_TMP_MAX_CHAR];
    char dstip[CAL_FORWARD_IP_MAX_CHAR];
    char dstmask[CAL_FORWARD_IP_MAX_CHAR];
    char srcip[CAL_FORWARD_IP_MAX_CHAR];
    char srcmask[CAL_FORWARD_IP_MAX_CHAR];
    char gwip[CAL_FORWARD_IP_MAX_CHAR];
    char metric[CAL_FORWARD_TMP_MAX_CHAR];
    char interface[CAL_FORWARD_IF_MAX_CHAR];
    char mtu[CAL_FORWARD_TMP_MAX_CHAR];    
}cal_static_routing;

typedef struct
{
    char key[CAL_FORWARD_MAX];
    char enable[CAL_FORWARD_MAX];
    char name[CAL_FORWARD_MAX];
    char type[CAL_FORWARD_MAX];
    char route_key[CAL_FORWARD_MAX];
    char interface[CAL_FORWARD_MAX];
}cal_policy_forwarding;


/*************** policy forward *****************/
int cal_pf_get_entry_by_name(char *name, cal_policy_forwarding *entry);
int cal_pf_add_one_entry(cal_policy_forwarding* entry);
int cal_pf_get_one_entry(cal_policy_forwarding* entry);
int cal_pf_get_all_entry(cal_policy_forwarding** entry);
int cal_pf_del_one_entry(cal_policy_forwarding* entry);
int cal_pf_del_all_entry(void);
int cal_pf_get_entry_num(void);
int cal_pf_del_entry_array(int** index_array);
int cal_pf_modify_one_entry(cal_policy_forwarding* entry);


/*************** static routing *********************/
int cal_sr_add_one_entry(cal_static_routing* entry);
int cal_sr_get_one_entry(cal_static_routing* entry);
int cal_sr_get_all_entry(cal_static_routing** entry);
int cal_sr_del_one_entry(cal_static_routing* entry);
int cal_sr_del_all_entry(void);
int cal_sr_get_entry_num(void);
int cal_sr_del_entry_array(int** index_array);
int cal_sr_modify_one_entry(cal_static_routing* entry);

#endif
