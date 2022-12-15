#ifndef _IPTV_API_H_
#define _IPTV_API_H_


int iptv_proxy_export_group_table(void);
int iptv_proxy_print_group_table(void);
int iptv_proxy_print_current_config(void);
char *iptv_proxy_get_pid_file(void);
char *iptv_proxy_get_group_table_exported_file(void);
char *iptv_proxy_get_group_table_exported_done_file(void);
char *iptv_proxy_get_history_file(void);


int iptv_snoop_cleanup_all(void);
int iptv_snoop_print_current_config(void);
int iptv_snoop_disable_igmp_relay(void);
int iptv_snoop_enable_igmp_relay(void);
int iptv_snoop_set_group_timer(int num);
int iptv_snoop_reset_group_timer(void);
int iptv_snoop_set_leave_timer(int num);
int iptv_snoop_reset_leave_timer(void);
int iptv_snoop_set_bootcast_group(char *ip_str);
int iptv_snoop_reset_bootcast_group(void);
int iptv_snoop_set_blocked_groups(char *str);
int iptv_snoop_reset_blocked_groups(void);
int iptv_snoop_export_bl_group_table(void);
int iptv_snoop_print_bl_group_table(void);
int iptv_snoop_print_bl_group_fwd_table(void);
int iptv_snoop_print_bl_active_group_list(void);
int iptv_snoop_save_log_to_file(void);
int iptv_snoop_clear_log(void);
int iptv_snoop_set_log_level(int level);
int iptv_snoop_get_log_level(void);
char *iptv_snoop_get_log_file(void);
char *iptv_snoop_get_bl_group_table_exported_file(void);


#endif /* _IPTV_API_H_ */

