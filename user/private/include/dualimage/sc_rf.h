/* =============================================================================      
 *         Copyright (C) 2006, Sercomm Corporation,  All Rights Reserved
 * =============================================================================    
 * The Header File Of Running Flash
 * 
 * [ Revise History ]:
 *  v1.00     init      Jim Yang
 * =============================================================================
 */

#ifndef _SC_RUNNING_FLAGE_H_
#define _SC_RUNNING_FLAGE_H_

#define SC_BIT_IN_BYTE_NUM			(8)



#ifdef SUPPORT_DUALIMAGE
#define SC_PID_MTD_PATH             ("/dev/mtd0")
#define SC_XMLCONFIG_MTD_PATH       ("/config/vd168_cfg")  //("/tmp/ubi9_0/xmlx")
#define SC_XMLCONFIG_MTD_PATH2      ("/config/vd168_cfg2") //("/tmp/ubi9_0/xmlx")
#define SC_MTB_MTD_PATH        	    ("/dev/mtdxxx")
#else
#define SC_PID_MTD_PATH             ("/dev/mtd0")
#define SC_XMLCONFIG_MTD_PATH       ("/config/vd168_cfg")  //("/tmp/ubi9_0/xmlx")
#define SC_MTB_MTD_PATH        	    ("/dev/mtdxxx")
#endif

/*
 * for Dual Image Information
 * SC_FW_IMG_CFG_FILE - file store Firmware Information
 * eSC_FW_VERSION_LEN - firmware version length (MAX 14 bytes)
 */
#define SC_FW_IMG_CFG_FILE			"/tmp/fw_info/fw_cfg_file"
#define eSC_FW_VERSION_LEN			(14)
	

/*
 * Dual Image Information
 * structure defined refer to fw info
 */
enum {
    eSC_BOOL_FALSE = 0,
    eSC_BOOL_TRUE
};

typedef struct 
{
    char version[eSC_FW_VERSION_LEN];
    unsigned int isCommittedB;
    unsigned int isUsedB;
    unsigned int isValidB;
}tFwImgCfg;

unsigned short  util_get_fw_version(void);
int util_read_fw_info_to_ram(char *pathStrP);

/*
 * add for firmware information read/wirte
 * read or write firmware information between Ram-file and Stucture
 * file - "/tmp/fw_info/fw_info_cfg"
 * structure - tFwImgCfg
 */
#endif /* End Of _SC_RUNNING_FLAGE_H_ */

