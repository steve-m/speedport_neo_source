#ifndef _CFG_HOSTS_H_
#define _CFG_HOSTS_H_


int cal_host_find_free_ipv4(char* ip4_found);
int cal_staic_ip_del_by_host_id(int host_id);
int cal_trule_delete_by_hostid(int host_id);
int cal_ptmp_delete_by_hostid(int host_id);
int cal_pfilter_delete_by_hostid(int host_id);
int cal_AccessControl_delete_by_hostid(int host_id);
int cal_static_ip_list_delete(int host_id);
int cal_host_entry_virtual_change(int host_id, int virtual_type);
int cal_static_ip_list_update(int host_id);
int cal_static_ip_update(char *lan_ip3);

#endif
