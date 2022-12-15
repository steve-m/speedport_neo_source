#ifndef _LED_ACTION_H_
#define _LED_ACTION_H_
#include "filenames.h"
/*
 * Define ALL LED ACTION here.
 * I hate so many hard codeed 20/30/90....
 */

#define LED_TURN_ON                 " on "
#define LED_TURN_OFF                " off "
#define LED_BLINK                   " blink "
#define LED_BLINKALWAYS             " blink_always "
#define LED_BLINKALT                " blink_alt "
#define LED_BLINKTM                 " blink_tm "
#define LED_REBOOT                  " reboot "
#define LED_WPS                     " wps "


#define LED_POWER_GREEN_ID          " 70 "
#define LED_POWER_AMBER_ID          " 71 "
#define LED_WLAN_ID                 " 40 "
#define LED_WAN_GREEN_ID            " 20 "
#define LED_WAN_AMBER_ID            " 30 "
#define LED_WPS_ID                  " 14 "
#define LED_USB                     " 60 "
#define LED_WARN_ID                 " 80 "

/*  when booting */
#define LED_ACTION_BOOTING()        do { system(LED_APP LED_TURN_OFF LED_POWER_GREEN_ID); system(LED_APP LED_TURN_ON LED_POWER_AMBER_ID); } while(0)

/* Boot finished */
#define LED_ACTION_BOOT_FINISH()    do { system(LED_APP LED_TURN_OFF LED_POWER_AMBER_ID); system(LED_APP LED_TURN_ON LED_POWER_GREEN_ID); } while(0)

/* Wireless is initialized */
#define LED_ACTION_WIFI_ON()        do { system(LED_APP LED_TURN_ON LED_WLAN_ID); } while(0)

/* Wireless is disabled */
#define LED_ACTION_WIFI_OFF()       do { system(LED_APP LED_TURN_OFF LED_WLAN_ID); } while(0)

/* WAN physical link is down */
#define LED_ACTION_PHY_DOWN()       do {system(LED_APP LED_TURN_OFF LED_WAN_GREEN_ID);\
                                        system(LED_APP LED_TURN_OFF LED_WAN_AMBER_ID);} while(0)

/* Internet is connected */
#define LED_ACTION_WAN_UP()         do { system(LED_APP LED_TURN_OFF LED_WAN_AMBER_ID); system(LED_APP LED_TURN_ON LED_WAN_GREEN_ID);} while(0)

/* Internet is NOT connected */
/*spec 2.0: If only the physical link is up (e.g. connected to a switch or 
modem) but there is no IP address acquired, the LED is AMBER*/
#define ADSL_SHOWTIME   "/tmp/adsl_showtime"
#define LED_ACTION_WAN_DOWN()       do {system(LED_APP LED_TURN_OFF LED_WAN_GREEN_ID);\
                                        system(LED_APP LED_TURN_OFF LED_WAN_AMBER_ID);\
                                        if(access(ADSL_SHOWTIME,F_OK)==0)\
                                         system(LED_APP LED_TURN_ON LED_WAN_AMBER_ID);} while(0)

/* wan is bridge mode, turn off internet led. */
#define LED_ACTION_WAN_OFF()       do {system(LED_APP LED_TURN_OFF LED_WAN_GREEN_ID);\
                                        system(LED_APP LED_TURN_OFF LED_WAN_AMBER_ID);\
                                       } while(0)

/* Reset button pressed */
#define LED_ACTION_RST_BT_PRESSED   LED_ACTION_BOOTING

/* Do Restore to default */
#define LED_ACTION_RESTORE()        do { system(LED_APP LED_BLINK LED_POWER_AMBER_ID" 10 250 750"); } while(0)

/* Reboot in seconds */
#define LED_ACTION_REBOOT(sec)      do { system(LED_APP LED_REBOOT #sec); } while(0)

/* Firmware upgrading */
#define LED_ACTION_UPGRADING()      do { system(LED_APP LED_BLINKALWAYS LED_WARN_ID" 1 250 750 0"); } while(0)

/* Traffic Meter limit reached */
#define LED_ACTION_TM_LIMIT()       do { system(LED_APP LED_BLINKTM LED_WAN_GREEN_ID LED_WAN_AMBER_ID " 1 250 250 0"); } while(0)

/* Turn ON WPS LEDs */
#define LED_ACTION_WPS_ON()         do { system(LED_APP LED_WPS_ID LED_TURN_ON); } while(0)

/* Turn OFF WPS LEDs */
#define LED_ACTION_WPS_OFF()        do { system(LED_APP LED_WPS_ID LED_TURN_OFF); } while(0)

/*fast blink for 5 seconds*/
#define LED_ACTION_WPS_FAST_BLINK_5SEC()         do { system(LED_APP LED_BLINK LED_WPS_ID" 25 100 100"); } while(0)
#define LED_ACTION_WPS_FAST_BLINK_ALWAYS()         do { system(LED_APP LED_BLINKALWAYS LED_WPS_ID" 1 100 100 0"); } while(0)

#define LED_ACTION_TM_GREEN_OFF()        do { system(LED_APP LED_TURN_OFF LED_WAN_GREEN_ID); } while(0)
#define LED_ACTION_TM_GREEN_ON()         do { system(LED_APP LED_TURN_ON  LED_WAN_GREEN_ID); } while(0)
#define LED_ACTION_TM_AMBER_OFF()        do { system(LED_APP LED_TURN_OFF LED_WAN_AMBER_ID); } while(0)
#define LED_ACTION_TM_AMBER_ON()         do { system(LED_APP LED_TURN_ON  LED_WAN_AMBER_ID); } while(0)

#define LED_ACTION_USB_OFF()        do { system(LED_APP LED_TURN_OFF LED_USB); } while(0)
#define LED_ACTION_USB_ON()         do { system(LED_APP LED_TURN_ON  LED_USB); } while(0)

#define LED_ACTION_WIFIA_ON()
#define LED_ACTION_WIFIA_OFF()


#endif /* _LED_ACTION_H_ */
