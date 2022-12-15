/* =============================================================================      
 *         Copyright (C) 2006, Sercomm Corporation,  All Rights Reserved
 * =============================================================================    
 * The Header File Of Dual Image Module
 * 
 * [ Revise History ]:
 *  v1.00     init      Jim Yang
 * =============================================================================
 */

#ifndef _DUAL_IMAGE_CONTROL_BLOCK_H_
#define _DUAL_IMAGE_CONTROL_BLOCK_H_

#include <stdio.h>

#define SC_DCBH_MGWORD      ("ScMgWoRd")
#define SC_DCBH_MGWORD_LEN	(8)
#define SC_DCBH_LG_BIT      (0x02)
#define SC_DCBH_WD_BIT      (0x01)

typedef struct SC_DCBH
{
	unsigned char  ctrl_flag;   /* Now only use the last two bit, others don't use and fill it with 1
        	                       7  6  5  4  3  2  1  0
        	                       1  1  1  1  1  1 LGB WDB 
        	                       LGB - Logic Good Bit
        	                       WDB - Write Done Bit
        	            */
	unsigned char  reserved;    /* Reserve bit fill it with 0xFF */
	unsigned short checksum;
	unsigned long  content_len;
	unsigned char  magic_word[SC_DCBH_MGWORD_LEN];
}DCB, *PDCB;

#define SC_DCBH_LEN (sizeof(DCB))
#define xchgs(x) (unsigned short)((((unsigned short)((unsigned short)x)&0x0ff)<<8)|(((unsigned short)((unsigned short)x)&0x0ff00)>>8))
#define xchgl(x) (unsigned long)((((unsigned long)x)<<24)|((((unsigned long)x)<<8)&0x00ff0000)|((((unsigned long)x)>>8)&0x0000ff00)|(((unsigned long)x)>>24))

#define SC_FW_BOOT_OK			(1)
#define SC_FW_BOOT_FAIL			(0)
#define SC_FW_PART				(0)
#define SC_CONFIG_PART			(1)
#define SC_CHECK_PART_FAIL		(0)
#define SC_CHECK_PART_OK		(1)
#define SC_UPGRADE_FAIL		    (0)
#define SC_UPGRADE_OK	    	(1)
#define SC_CONFIG_UPGRADE_FAIL	(0)
#define SC_CONFIG_UPGRADE_OK	(1)
#define SC_ERASE_MTD_FAIL       (0)
#define SC_ERASE_MTD_OK         (1)
#define SC_DCB_RESERVED         (0x10)
#define SC_DCB_BL_RESERVED      SC_DCB_RESERVED
#define SC_DCB_FW_RESERVED      (SC_DCB_RESERVED + 0x20)

#endif /* End Of _DUAL_IMAGE_CONTROL_BLOCK_H_ */

