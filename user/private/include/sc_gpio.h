#ifndef _SC_GPIO_H_
#define _SC_GPIO_H_

#if defined(MiniGPON)

#define GPIO_RESET_BUTTON   	(4)     /* Push Button RST gpio */
#define GPIO_STATUS_LED         (17)
#define GPIO_GPON_LED           (19)    /* GPON Link led gpio */
#define GPIO_POWER_LED     	    (20)
#define GPIO_DYING_GASP     	(24)    /* GPON dying gasp*/
#define GPIO_PHY_RST		    (50)	/* PHY IP1001 RST gpio */

#elif defined(RFT610)

#define GPIO_RESET_BUTTON   	(4)     /* Push Button RST gpio */
#define GPIO_PHY_RST            (9)	    /* PHY RTL8021 RST gpio */
#define GPIO_POWER_LED     	    (17)
#define GPIO_GPON_LED           (19)    /* GPON Link led gpio */
#define GPIO_STATUS_LED         (20)
#define GPIO_VGW_PRESENT     	(23)    /* VoIP module detect*/
#define GPIO_WIFI_PRESENT     	(24)    /* Wifi module detect*/
#define GPIO_SWITCH_RST		    (50)    /* Marvel 88E6171 RST gpio */

#elif defined(FR1019BL)

#define GPIO_RESET_BUTTON   	(4)     /* Push Button RST gpio */
#define GPIO_DYING_GASP     	(6)     /* GPON dying gasp*/
#define GPIO_TEL2_LED     	    (8)     /* Tel 2 led gpio*/
#define GPIO_PHY_RST            (9)	    /* PHY RTL8021 RST gpio */
#define GPIO_TEL1_LED     	    (14)    /* Tel 1 led gpio*/
#define GPIO_SLIC2_RST     	    (15)    /* SLIC 2 RST gpio*/
#define GPIO_SLIC1_RST     	    (16)    /* SLIC 1 RST gpio*/
#define GPIO_WIFI_LED     	    (17)    /* WIFI LED gpio*/
#define GPIO_WIFI_RST     	    (18)    /* WIFI RST gpio*/
#define GPIO_GPON_LED           (19)    /* GPON Link led gpio */
#define GPIO_POWER_LED          (20)    /* Alarm led gpio */
#define GPIO_STATUS_LED         (20)    /* Alarm led gpio */
#define GPIO_TRAFFIC_LED        (21)    /* Traffic led gpio */
#define GPIO_SWITCH_RST		    (50)    /* Marvel 88E6171 RST gpio */

#elif defined(F620Gv2)

//#define GPIO_POWER_LED                  /* Hw control*/

#define GPIO_SWITCH_RST		    (0)     /* RTL8367M RST gpio */
#define GPIO_SLAC_RST 		    (1)
#define GPIO_PROTECT_CLK 	    (19)    /*GMII*/
#define GPIO_SMI_SCL 		    (24)
#define GPIO_SMI_SDA 		    (25)

#define GPIO_DYING_GASP     	(0)     /* GPON dying gasp*/
#define GPIO_RESET_BUTTON   	(3)     /* Push Button RST gpio */
#define GPIO_WIFI_BUTTON       (56)     /* wifi RST gpio */
#define GPIO_OP_TXPWR 		    (2)
#define GPIO_CATVPWR 		    (57)
#define GPIO_WDI                (47)    /*Watch dog*/
#define GPIO_SFF_RST            (59)

#define GPIO_GPON_LED           (39)     /* GPON Link led gpio */
#define GPIO_LOS_LED   	        (5)     /* GPON LOS led gpio */
#define GPIO_BATTERY_LED        (37)
#define GPIO_INTERNET_LED       (48)
#define GPIO_LAN_LED            (58)
#define GPIO_WIFI_LED           (32)
#define GPIO_WPS_LED            (36)
#define GPIO_PHONE_LED          (38)
#define GPIO_USB_LED            (81) /* No this gpio, just mark */
#define GPIO_RF_LED             (82) /* No this gpio, just mark */


#endif

#endif /* _SC_GPIO_H_ */
