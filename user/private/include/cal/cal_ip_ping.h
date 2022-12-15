#ifndef _CAL_IP_PING_H_
#define _CAL_IP_PING_H_

#define CAL_IP_PING_TMP_MAX_CHAR 	8	
#define CAL_IP_PING_MAX				256	

typedef struct
{
	char key[CAL_IP_PING_TMP_MAX_CHAR];
	char state[CAL_IP_PING_TMP_MAX_CHAR];
	char interface[CAL_IP_PING_MAX];
	char host[CAL_IP_PING_MAX];
    char repeat[CAL_IP_PING_TMP_MAX_CHAR];
	char num[CAL_IP_PING_TMP_MAX_CHAR];
	char timeout[CAL_IP_PING_TMP_MAX_CHAR];
	char block_size[CAL_IP_PING_TMP_MAX_CHAR];
	char dscp[CAL_IP_PING_TMP_MAX_CHAR];
	char succ_cnt[CAL_IP_PING_TMP_MAX_CHAR];
	char fail_cnt[CAL_IP_PING_TMP_MAX_CHAR];
	char ave_time[CAL_IP_PING_TMP_MAX_CHAR];
	char min_time[CAL_IP_PING_TMP_MAX_CHAR];
	char max_time[CAL_IP_PING_TMP_MAX_CHAR];  
} cal_ip_ping;

int cal_ip_ping_get(cal_ip_ping* ip_ping);
int cal_ip_ping_set(cal_ip_ping*  ip_ping);

#endif
