/* =============================================================================      
 *         Copyright (C) 2006, Sercomm Corporation,  All Rights Reserved
 * =============================================================================    
 * The Header File Of Flash Content Parameter
 * 
 * [ Revise History ]:
 *  v1.00     init      Jim Yang
 * =============================================================================
 */

#ifndef _SC_FLASH_PARAM_H_
#define _SC_FLASH_PARAM_H_

#ifdef SC_FLASH_32M /*FR1019BL*/

#define SC_FLASH_BASE_ADDR      (0xBE000000)
#define SC_FLASH_TOTAL_SIZE		(0x2000000)         /* (32 * 1024 * 1024)   32M */
#define SC_FLASH_BLOCK_SIZE		(0x40000)           /* (256 * 1024)         256K */
#define SC_MAX_FW_LEN           (0xF00000)          /* (15360 * 1024)       15360K */
#define SC_MAX_KERN_LEN         (0x1C0000)          /* (1792 * 1024)       1792K */

#elif SC_FLASH_16M /*MiniGPON, RFT610, F620Gv2*/

#ifdef F620Gv2
#define SC_FLASH_BASE_ADDR      (0xBE000000)
#else
#define SC_FLASH_BASE_ADDR      (0xBF000000)
#endif

#define SC_FLASH_TOTAL_SIZE		(0x1000000)         /* (16 * 1024 * 1024)   16M */
#define SC_FLASH_BLOCK_SIZE		(0x20000)           /* (128 * 1024)         128K */
#define SC_MAX_FW_LEN           (0x720000)          
#define SC_MAX_KERN_LEN         (0x180000)          

#endif

#define SC_MAX_BOOT_LEN			(0x40000)           /* (256 * 1024)	        256K */
#define SC_CONFIG_PART_LEN		SC_FLASH_BLOCK_SIZE 
#define SC_MAX_RESERVED_LEN		SC_FLASH_BLOCK_SIZE 
#define SC_MAX_RF_LEN		    SC_FLASH_BLOCK_SIZE 

#define SC_MAX_BC_LEN		    (0x20000)           /* (2 * 64 * 1024)      128K */
#define SC_MAX_BENV_LEN		    (0x20000)           /* (2 * 64 * 1024)      128K */

#define SC_PROTECT_AREA_OFFSET  (0x00000000)
#define SC_BOOT1_OFFSET         (0x00040000)
#define SC_BOOT2_OFFSET         (0x00080000)
#define SC_RF_BOOT_MGW_OFFSET   (0x0003F000)
#define SC_RF_BOOT_OFFSET       (0x10)

#define SC_FW1_OFFSET           (0x000C0000)

#ifdef SUPPORT_DUALIMAGE
#define SC_CONFIG1_OFFSET       (SC_FW1_OFFSET+SC_MAX_FW_LEN+SC_MAX_RESERVED_LEN)
#define SC_FW2_OFFSET           (SC_CONFIG1_OFFSET+SC_CONFIG_PART_LEN)
#else
#define SC_CONFIG1_OFFSET       (0x00E00000)
#define SC_FW2_OFFSET           SC_FW1_OFFSET
#endif

#define SC_BOOT_COUNTER_OFFSET  (SC_FLASH_TOTAL_SIZE-SC_MAX_BENV_LEN-SC_MAX_BC_LEN)
#define SC_RUNNING_FLAG_OFFSET  (SC_BOOT_COUNTER_OFFSET-SC_MAX_RF_LEN)

#ifdef SUPPORT_DUALIMAGE
#define SC_CONFIG2_OFFSET       (SC_RUNNING_FLAG_OFFSET-SC_CONFIG_PART_LEN)
#else
#define SC_CONFIG2_OFFSET       SC_CONFIG1_OFFSET
#endif

#ifdef SUPPORT_DUALIMAGE
#define SC_XMLCFG_OFFSET        (0x007E0000)
#define SC_XMLCFG_SIZE          (0x20000)
#else
#define SC_XMLCFG_OFFSET        (0x00E20000)
#define SC_XMLCFG_SIZE          (0x40000)
#endif

#define SC_XMLCFG_BASE_ADDR	    (SC_FLASH_BASE_ADDR+SC_XMLCFG_OFFSET)

#define SC_RF_MGW_OFFSET        (0x0)
#define SC_RF_FW_OFFSET         (0x10)
#define SC_RF_CONFIG_OFFSET     ((SC_MAX_RF_LEN*3)/8)
#define SC_BC_MGW_OFFSET        (0x0)
#define SC_BC_FLAG_OFFSET       (0x10)

#define SC_RF_MAX_SIZE          SC_MAX_RF_LEN
#define SC_RF_FW_SIZE           ((SC_MAX_RF_LEN*3)/8-SC_RF_FW_OFFSET)
#define SC_RF_CONFIG_SIZE       ((SC_MAX_RF_LEN*5)/8)
#define SC_BC_MAX_SIZE			SC_MAX_BC_LEN
#define SC_BC_VALID_SIZE		(SC_BC_MAX_SIZE - SC_BC_FLAG_OFFSET)
#define SC_RF_BOOT_MAX_SIZE		(0x01000)	/* 4 * 1024 */
#define SC_RF_BOOT_VALID_SIZE   (0x00FF0)   /* (4 * 1024 - 0x10) */


#define SC_PROTECT_AREA_ADDR    (SC_FLASH_BASE_ADDR + SC_PROTECT_AREA_OFFSET)
#define SC_BOOT1_BASE_ADDR      (SC_FLASH_BASE_ADDR + SC_BOOT1_OFFSET)
#define SC_BOOT2_BASE_ADDR      (SC_FLASH_BASE_ADDR + SC_BOOT2_OFFSET)
#define SC_RF_BOOTMGW_BASE_ADDR (SC_FLASH_BASE_ADDR + SC_RF_BOOT_MGW_OFFSET)
#define SC_RF_BOOT_BASE_ADDR    (SC_RF_BOOTMGW_BASE_ADDR + SC_RF_BOOT_OFFSET)

#define SC_FW1_BASE_ADDR		(SC_FLASH_BASE_ADDR + SC_FW1_OFFSET)
#define SC_CONFIG1_BASE_ADDR	(SC_FLASH_BASE_ADDR + SC_CONFIG1_OFFSET)
#define SC_FW2_BASE_ADDR		(SC_FLASH_BASE_ADDR + SC_FW2_OFFSET)
#define SC_CONFIG2_BASE_ADDR	(SC_FLASH_BASE_ADDR + SC_CONFIG2_OFFSET)
#define SC_RF_BASE_ADDR         (SC_FLASH_BASE_ADDR + SC_RUNNING_FLAG_OFFSET)
#define SC_RF_MGW_BASE_ADDR     (SC_RF_BASE_ADDR + SC_RF_MGW_OFFSET)
#define SC_RF_FW_BASE_ADDR      (SC_RF_BASE_ADDR + SC_RF_FW_OFFSET)
#define SC_RF_CONFIG_BASE_ADDR  (SC_RF_BASE_ADDR + SC_RF_CONFIG_OFFSET)
#define SC_BC_BASE_ADDR         (SC_FLASH_BASE_ADDR + SC_BOOT_COUNTER_OFFSET)
#define SC_BC_MGW_BASE_ADDR     (SC_BC_BASE_ADDR + SC_BC_MGW_OFFSET)
#define SC_BC_FLAG_BASE_ADDR    (SC_BC_BASE_ADDR + SC_BC_FLAG_OFFSET)

#define NVRAM_BOOTLINE_LEN              256
#define NVRAM_BOARD_ID_STRING_LEN       16
#define NVRAM_MAC_ADDRESS_LEN           6
#define NVRAM_GPON_SERIAL_NUMBER_LEN    13
#define NVRAM_GPON_PASSWORD_LEN         11
#define NVRAM_WLAN_PARAMS_LEN           256
#define NVRAM_WPS_DEVICE_PIN_LEN        8
#define NP_TOTAL                        5

typedef struct
{
    unsigned long ulVersion;
    char szBootline[NVRAM_BOOTLINE_LEN];
    char szBoardId[NVRAM_BOARD_ID_STRING_LEN];
    unsigned long ulMainTpNum;
    unsigned long ulPsiSize;
    unsigned long ulNumMacAddrs;
    unsigned char ucaBaseMacAddr[NVRAM_MAC_ADDRESS_LEN];
    char pad;
    char backupPsi;  /**< if 0x01, allocate space for a backup PSI */
    unsigned long ulCheckSumV4;
    char gponSerialNumber[NVRAM_GPON_SERIAL_NUMBER_LEN];
    char gponPassword[NVRAM_GPON_PASSWORD_LEN];
    char wpsDevicePin[NVRAM_WPS_DEVICE_PIN_LEN];
    char wlanParams[NVRAM_WLAN_PARAMS_LEN];
    unsigned long ulSyslogSize; /**< number of KB to allocate for persistent syslog */
    unsigned long ulNandPartOfsKb[NP_TOTAL];
    unsigned long ulNandPartSizeKb[NP_TOTAL];
    char szVoiceBoardId[NVRAM_BOARD_ID_STRING_LEN];
    unsigned long afeId[2];
    unsigned short opticRxPwrReading;   // optical initial rx power reading
    unsigned short opticRxPwrOffset;    // optical rx power offset
    unsigned short opticTxPwrReading;   // optical initial tx power reading
    unsigned char ucUnused2[58];
    unsigned char ucFlashBlkSize;
    unsigned char ucAuxFSPercent;
    unsigned long ulBoardStuffOption;   // board options. bit0-3 is for DECT    
    char chUnused[290];
    unsigned long ulCheckSum;
} NVRAM_DATA, *PNVRAM_DATA;

/*
* Assigned ITEM OFFSET(ADDRESS) and LENGTH
*/
#define NVRAM_DATA_OFFSET       0x0580
#define offset(para)            ((unsigned int)&(((NVRAM_DATA*)0x0580)->para))
#define PID_OFFSET	        (0x1FFF1 - PID_LEN) /* from .par file */

#define SC_FLASH_MAC_OFFSET 	offset(ucaBaseMacAddr)
#define SC_FLASH_MAC_LENGTH     6	
#define SC_FLASH_DECINIT_LENGTH 1
#define SC_PROTECT_DATA_MTD_PATH         "/dev/mtd0"
#define SC_FLASH_CONF_OFFSET    0x3EB0 
#define SC_FLASH_SN_OFFSET 	SC_FLASH_CONF_OFFSET + 0x00
#define SC_FLASH_SN_LENGTH 	16
#define SC_FLASH_PIN_OFFSET 	SC_FLASH_CONF_OFFSET + 0x10
#define SC_FLASH_PIN_LENGTH 	12
#define SC_FLASH_REGION_OFFSET 	SC_FLASH_CONF_OFFSET + 0x20
#define SC_FLASH_REGION_LENGTH 	2
#define SC_FLASH_LANG_OFFSET 	SC_FLASH_CONF_OFFSET + 0x30
#define SC_FLASH_LANG_LENGTH 	2
#define SC_FLASH_DOMAIN_OFFSET 	SC_FLASH_CONF_OFFSET + 0x40
#define SC_FLASH_DOMAIN_LENGTH 	4
#define SC_FLASH_PCBASN_OFFSET  0
#define SC_FLASH_PCBASN_LENGTH  16
#define SC_FLASH_CSN_OFFSET 	SC_FLASH_CONF_OFFSET + 0x60
#define SC_FLASH_CSN_LENGTH 	42
#define SC_FLASH_SSID_OFFSET 	SC_FLASH_CONF_OFFSET + 0x90
#define SC_FLASH_SSID_LENGTH 	20
#define SC_FLASH_WPAKEY_OFFSET 	SC_FLASH_CONF_OFFSET + 0xB0
#define SC_FLASH_WPAKEY_LENGTH 	64
#define SC_FLASH_HWV_OFFSET 	(0x3fc1)
#define SC_FLASH_HWV_LENGTH 	(0x04)

#define SC_FLASH_PSN_OFFSET     (0x3EE60)
#define SC_FLASH_PSN_LENGTH     (0x10)
#define SC_FLASH_PID_OFFSET     (0x1FFF1 - 0x46)
#define SC_FLASH_PID_LENGTH     (0x46)
#define SC_FLASH_FWV_LENGTH      16
#define SC_FLASH_MAC_ADDR       (SC_FLASH_BASE_ADDR+SC_FLASH_MAC_OFFSET)

#endif /* End Of _SC_FLASH_PARAM_H_ */



