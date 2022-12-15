/***************************************************************
*             Copyright (C) 2007 by SerComm Corp.
*                    All Rights Reserved.
*
*      Use of this software is restricted to the terms and
*      conditions of SerComm's software license agreement.
*
*                        www.sercomm.com
****************************************************************/

#define EXPORT_SYMTAB

#if defined(CONFIG_MODVERSIONS) && !defined(MODVERSIONS)
#define MODEVERSIONS
#endif

#ifdef MODVERSIONS
#include <linux/modversions.h>
#endif
#include <linux/module.h>

#include <sc/sc_led.h>

//sc: add for led control
INT8 (*sc_led_on_hook)(UINT8 led_id)=NULL;
INT8 (*sc_led_off_hook)(UINT8 led_id)=NULL;
INT8 (*sc_led_blink_hook)(UINT8 led_id,UINT8 blink_count,UINT8 on_time,UINT8 off_time)=NULL;
INT8 (*sc_led_blink_alt_hook)(UINT8 led_id1,UINT8 led_id2,UINT8 blink_count,UINT8 on_time,UINT8 off_time)=NULL;
INT8 (*sc_led_blink_always_hook)(UINT8 led_id, UINT8 blink_count,UINT8 on_time,UINT8 off_time, INT8 blink_interval)=NULL;
INT8 wps_running;
INT8 wifi_mode;

//sc: add for led control
EXPORT_SYMBOL(sc_led_on_hook);
EXPORT_SYMBOL(sc_led_off_hook);
EXPORT_SYMBOL(sc_led_blink_hook);
EXPORT_SYMBOL(sc_led_blink_alt_hook);
EXPORT_SYMBOL(sc_led_blink_always_hook);
EXPORT_SYMBOL(wps_running);
EXPORT_SYMBOL(wifi_mode);

/*sc:
Description:
	used to hook sercomm led driver to control LED


Key Word:
	[led_control]

File List to add led_control hook:
	- add. include/sc/sc_led.h
	
	- net/core/dev.c
		1. add #include <sc/sc_led.h>
		2. dev_queue_xmit()
		3. netif_receive_skb()
		
	- bcmdrivers/broadcom/char/atmapi/impl1/atmoslinux.c			
		1. add #include <sc/sc_led.h>
		2. AtmOsBlinkLed()
		
	- bcmdrivers/broadcom/char/adsl/impl1_A2x020a/adsl.c	
		1. add #include <sc/sc_led.h>
		2. BcmAdsl_Status()
		
	- bcmdrivers/broadcom/char/adsl/impl1_A2x020e/adsl.c
		1. add #include <sc/sc_led.h>
		2. BcmAdsl_Status()
		
*/
