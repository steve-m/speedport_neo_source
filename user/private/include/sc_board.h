#ifndef _SC_BOARD_H_
#define _SC_BOARD_H_

#include "sc_gpio.h"

#ifdef SUPPORT_DUALIMAGE
#include "dualimage/sc_hw.h"
#else
#include "flash.h"
#endif


/*
* Sercomm PID structure
*/

#define HW_ID_LEN   32
typedef  struct  VCI  {
    unsigned short    VerControl;
    unsigned short    DownControl;
    unsigned char     Hid[HW_ID_LEN];
    unsigned short    Hver;
    unsigned short    ProdID;
    unsigned short    ProdIDmask;
    unsigned short    ProtID;
    unsigned short    ProtIDmask;
    unsigned short    FuncID;
    unsigned short    FuncIDmask;
    unsigned short    Fver;
    unsigned short    Cseg;
    unsigned short    Csize;
} __attribute__((packed)) VCI_TABLE;

#define  VCI_LEN         56

#define 	HEX_PIDOFF_HWID 			8
#define     HEX_PIDOFF_HWVER            72
#define     HEX_PIDOFF_PRODUCTID      	76  
#define 	HEX_PIDOFF_SWVERSION		100
#define 	HEX_HWID_LEN				12
#define     HEX_PRODUCTID_LEN        	4

/*
*  Domain Mapping
*/
#define SKU_US  0x10
#define SKU_AU  0x35
#define SKU_BR  0x51
#define SKU_CN  0x70
#define SKU_G5  0x80
#define SKU_LA  0x50

#endif /* _SC_BOARD_H_ */
