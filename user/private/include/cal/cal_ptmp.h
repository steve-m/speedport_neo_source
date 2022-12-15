#ifndef _CFG_ptmp_H_
#define _CFG_ptmp_H_

int cal_ptmp_entry_tab_set(int ptmp_id, cfg_ptmp_entry_t *p_cal_ptmp_entry);
int cal_ptmp_entry_tab_del(int ptmp_id,int isTR069);
int cal_portmapping_entry_tab_del(int portmapping_id);
int cal_tr69_ptmp_entry_tab_set(int ptmp_id);
int cal_portmapping_entry_tab_update_host_id(int host_id,char *ip_addr);
int check_externalport_invalid(char *value,int id0, int isRange);
int check_protocol_change_invalid(char *value,int id0);

/*to add here*/
#endif
