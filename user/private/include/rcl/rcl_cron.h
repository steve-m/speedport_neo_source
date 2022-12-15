#ifndef _RCL_CRON_H
#define _RCL_CRON_H

int rcl_cron_start_wlan_sch(int argc, char** argv);
int rcl_cron_stop_wlan_sch(int argc, char** argv);

int rcl_cron_start_sync_sch(int argc, char **argv);
int rcl_cron_stop_sync_sch(int argc, char **argv);

int rcl_cron_start_backup_sch(int argc, char **argv);
int rcl_cron_stop_backup_sch(int argc, char **argv);

int rcl_cron_start_time_rule(int argc, char **argv);
int rcl_cron_stop_time_rule(int argc, char **argv);

#endif

