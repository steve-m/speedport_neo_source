/***************************************************************
*             Copyright (C) 2007 by SerComm Corp.
*                    All Rights Reserved.
*
*      Use of this software is restricted to the terms and
*      conditions of SerComm's software license agreement.
*
*                        www.sercomm.com
****************************************************************/

#ifndef _SC_LED_H_
#define _SC_LED_H_


#ifndef UINT8
#define UINT8 unsigned char
#endif

#ifndef INT8
#define INT8 signed char
#endif

extern INT8 (*sc_led_on_hook)(UINT8 led_id);
extern INT8 (*sc_led_off_hook)(UINT8 led_id);
extern INT8 (*sc_led_blink_hook)(UINT8 led_id,UINT8 blink_count,UINT8 on_time,UINT8 off_time);
extern INT8 (*sc_led_blink_alt_hook)(UINT8 led_id1,UINT8 led_id2,UINT8 blink_count,UINT8 on_time,UINT8 off_time);
extern INT8 (*sc_led_blink_always_hook)(UINT8 led_id, UINT8 blink_count,UINT8 on_time,UINT8 off_time, INT8 blink_interval);


#endif // _SC_LED_H_

