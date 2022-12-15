#ifndef __SC_NVRAM_H__
#define __SC_NVRAM_H__
/*
 * 2003/02/27  		             			    
 * 		       				released by Ron     
 */

/* line terminator by 0x00 
 * data terminator by two 0x00
 * value separaed by 0x01
 */	
#include <string.h>

#define NVRAM_TMP_PATH  "/tmp/nvram"		  
#define NVRAM_DEFAULT   "/tmp/nvram"            
#define NVRAM_LSDCC_PATH    "/tmp/nvram.lsdcc"		  
#define NVRAM_HOMEPLUG_PATH    "/tmp/nvram.homeplug"		  

#define END_SYMBOL	    0x00		  	
#define DIVISION_SYMBOL	    0x01		  

/* NVRAM_HEADER MAGIC*/ 
#define NVRAM_MAGIC 		    0x004E4F52		 /* RON */

/* used 12bytes, 28bytes reserved */
#define NVRAM_HEADER_SIZE   40       		 
/* max size in flash*/
//#define NVRAM_SIZE          65535		  /* nvram size 64k bytes*/
#define NVRAM_SIZE              0x10000

/* each line max size*/
#define NVRAM_BUFF_SIZE           4096		 

/* errorno */
#define NVRAM_SUCCESS       	    0
#define NVRAM_FLASH_ERR           1 
#define NVRAM_MAGIC_ERR	    2
#define NVRAM_LEN_ERR	    3
#define NVRAM_CRC_ERR	    4
#define NVRAM_SHADOW_ERR	    5
#define NVRAM_MALLOC_ERR	6

/*
 * nvram header struct 		            
 * magic    = 0x004E4F52 (RON)             
 * len      = 0~65495                      
 * crc      = use crc-32                    
 * reserved = reserved 	                    
 */
 
typedef struct nvram_header_s{
	unsigned long magic;
	unsigned long len;
	unsigned long crc;
	unsigned long reserved;
	
}nvram_header_t;

char* nvram_get_fun(const char *name,char *path);
extern int nvram_set_p(const char *path, const char* name,const char* value);
#endif
