#ifndef __SAL_NTP_H__
#define __SAL_NTP_H__

#define NTP_STATUS_DISABLED						"Disabled"
#define NTP_STATUS_UNSYNCHRONIZED				"Unsynchronized"
#define NTP_STATUS_SYNCHRONIZED					"Synchronized"
#define NTP_STATUS_ERROR_FAILEDTOSYNCHRONIZE	"Error_FailedToSynchronize"

char *sal_ntp_get_server1(void);
int sal_ntp_set_server1(char *value);

char *sal_ntp_get_server2(void);
int sal_ntp_set_server2(char *value);

char *sal_ntp_get_alive_server(void);
int sal_ntp_set_alive_server(char *value);

/* to set/get the last update status */
char *sal_ntp_get_last_status(void);
int sal_ntp_set_last_status(char *value);

char *sal_ntp_get_syn_status(void);
int sal_ntp_set_syn_status(char *value);

long sal_ntp_get_time_offset(void);

char *sal_ntp_get_timezone(void);
int sal_ntp_set_timezone(char *value);

#endif

