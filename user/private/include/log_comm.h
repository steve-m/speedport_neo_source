/**
 * @file   
 * @author 
 * @date   2012-07-02
 * @brief  
 *
 * Copyright - 2012 SerComm Corporation. All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document without notice.
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising
 * out of the application or use of any product or circuit. SerComm Corporation specifically
 * disclaims any and all liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of others.
 */
/**
 * @file log_comm.h
 * @author Andy wang
 * @date   2012-07-1802
 * @brief  LOG common define    
 *
 * Copyright - 2012 SerComm Corporation. All Rights Reserved. 
 * SerComm Corporation reserves the right to make changes to this document without notice. 
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability 
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising 
 * out of the application or use of any product or circuit. SerComm Corporation specifically 
 * disclaims any and all liability, including without limitation consequential or incidental damages; 
 * neither does it convey any license under its patent rights, nor the rights of others. 
 */

#ifndef __LOG_COMMON_H__
#define __LOG_COMMON_H__

#define NTP_GET_TIME_MSG "System get NTP time"
//#define NTP_GET_TIME_MSG "sc used msg:ntp client success get time from ntp server."
#define FIRST_LOG "Booting HPNA Router"

#define START_TIME_1 "01.01.2000 00:00:00"
#define START_TIME_2 "01.01.1970 00:00:00"
#define NOW_TIME     "01.01.2011 00:00:00"

#define RESET_TIME      10      /*when uptime is 10, set date as 1970-01-01 00:00:00*/


#define LOG_TYPE_START GENERAL_LOG
#define LOG_TYPE_END VOIP_MISS 

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

#define MAX_FILE_ID             100000
#define PER_LOG_FILE_SIZE       (2*1024)
#define FILE_PATH_LENGTH        256
#define LOG_NAME_LENGTH         32
#define PER_MSG_MAX_LENGTH      512


static char *log_save_dir[MAX_TYPE_LOG]={
    "ALL/",
    "general/", //General
    "voipin/", 
    "voipout/", 
    "voipmiss/",
};

static char *log_sort_file_name[MAX_TYPE_LOG]={
    "ALL",
    "general.txt", //General
    "voipin.txt", 
    "voipout.txt", 
    "voipmiss.txt",
};


static char *log_sort_file_temp_name[MAX_TYPE_LOG]={
    "ALL",
    "general_temp.txt", //General
    "voipin_temp.txt", 
    "voipout_temp.txt", 
    "voipmiss_temp.txt",
};

static int log_syslog_file_size[MAX_TYPE_LOG]={
    114*1024,
    66*1024, //General
    16*1024, 
    16*1024, 
    16*1024,
};



unsigned long get_file_size(char *file_name);
int get_previous_id(int cur_id);
time_t get_log_time(char *s_time);
time_t get_gmt_time(char *s_time);

void get_log_info(int logtype ,int *max_id, int *min_id, unsigned long *total_size, unsigned long *current_size);
void get_compress_log_info(int logtype,int *max_id, int *min_id, unsigned long *total_size, unsigned long *current_size);

#endif //__LOG_COMM_H__
