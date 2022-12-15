/**
 * @file   
 * @author 
 * @date   2010-08-30
 * @brief  
 *
 * Copyright - 2009 SerComm Corporation. All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document without notice.
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising
 * out of the application or use of any product or circuit. SerComm Corporation specifically
 * disclaims any and all liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of others.
 */
/**
 * @file log_api.h
 * @author Phil Zhang
 * @date   2009-11-18
 * @brief  LOG read API   
 *
 * Copyright - 2009 SerComm Corporation. All Rights Reserved. 
 * SerComm Corporation reserves the right to make changes to this document without notice. 
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability 
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising 
 * out of the application or use of any product or circuit. SerComm Corporation specifically 
 * disclaims any and all liability, including without limitation consequential or incidental damages; 
 * neither does it convey any license under its patent rights, nor the rights of others. 
 */

#ifndef __LOG_API_H__
#define __LOG_API_H__

#include "log_errcode_de.h"

#ifndef _VOX_LOG_ 
   #define NVRAM_MOUNT_DIR      "/tmp/logdata/"
   #define JFFS2_MOUNT_DIR      NVRAM_MOUNT_DIR
#else
    #define JFFS2_MOUNT_DIR     "/tmp/datamtd/"
    #define MOUNT_FLAG_FILE     "/tmp/mount_jff2_ok"
#endif

#define LOG_FLASH_DIR "log/" 
#define SORT_LOG_DIR "/tmp/sort_log/"   /*[M] filter file*/
#define SAVE_LOG_FILE_NAME "log_web.txt"

#define LOG_FILE_SUFFIX ".log"
#define CUR_LOG_FILE  "current" /*/data/log/current.log*/
#define RC_INIT_UPTIME "/tmp/rc_init_uptime"

#define  LOG_SC_COMPRESS
#define NVRAM_COMPRESS_DIR      "/mnt/appdat/sc_log/"
#define NVRAM_COMPRESS_FILE_SUFFIX     ".scz" 

#define DEFAULT_LOG_BUF_SIZE    64*1024 //64K

#define VOICE_MAX_RECORD_CALLLOG_NUM   100

enum all_log_type_enum{
    ALL_LOG=0,
    GENERAL_LOG,
    VOIP_IN,
    VOIP_OUT,
    VOIP_MISS,
    MAX_TYPE_LOG,
};

static char *log_type_db[MAX_TYPE_LOG]={
    "[ALL]",
    "[GENERAL]", /*General*/
    "[VOIPIN]", 
    "[VOIPOUT]", 
    "[VOIPMISS]",
};

int create_sort_log2file(int log_type);
void uncompress_log2ram(void);
void compress_current_syslog_ram2flash(void);
void del_ALL_syslog(int log_type);
int get_syslog_sort_logmessage(int log_type ,char * buffer , int  buf_len);

#endif /*__LOG_API_H__*/
