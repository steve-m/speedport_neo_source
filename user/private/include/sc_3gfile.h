/*
 * All file names including application path, config file path and temp file path
 */
#ifndef _FILE_NAMES_H_
#define _FILE_NAMES_H_
 

/*********************************************************
 *                  Application Path                     *
 *********************************************************/
#define BIN_LN          "/usr/sbin/ln -sf"

/*********************************************************
 *                  Config File Path                     *
 *********************************************************/

/* 3G */
#define T3G_CONFIG              "/etc/gsmtd.conf"
#define DONGLE_PPPD_WANUP       "/etc/ppp/wan_uptime"
#define DONGLE_PPPD_SCRIPT      "/etc/ppp/peers/3g"
#define DONGLE_CHAT_SCRIPT      "/etc/ppp/scripts/3g.chat"
#define DONGLE_IP_UP_SCRIPT     "/etc/ppp/scripts/up"
#define DONGLE_IP_DOWN_SCRIPT   "/etc/ppp/scripts/down"


/* for EVG2000Dv2 */
#define USBDEV1 "/sys/bus/usb/devices/1-1"
#define USBDEV2 "/sys/bus/usb/devices/1-2"

#define FAILOVER_DAEMON_NAME      "failover"
#define FAILOVER_INTERFACE_ID 9
#define FAILOVER_DETECT_TABLE 200
#define FAILOVER_PKT_TOS      8  // must not use 0x08, getoption32 in busybox can't recognize

/* XXX below files are also used by $(ROOT)/Makefile, $(ROOT)/apps/etc/xdsl.sh.
 * so be careful if filenames are changed. */

/* 3g/choose_wan rc needs abouts 5-30s to finish,
 * use this two files to make rc run exclusively:
 * 1) rc must create RUNNING_RC_3G/RUNNING_RC_CHOOSEWAN when rc choose_wan/3g run,
 * and delete them when rc exit.
 * 2) also need apply RUNNING_RC_CHOOSEWAN to root Makefile, check DGN1000_DEV's root Makefile as example. */
#define RUNNING_RC_3G              "/var/run/rc.3g.run"
#define RUNNING_RC_CHOOSEWAN       "/var/run/rc.choose_wan.run"

/* created/deleted by rc choose_wan, used by xdsl.sh and cgi. */
#define FAILOVER_3GONLY            "/tmp/failover_3gonly"
/* created/deleted by failover daemon, used by xdsl.sh, rc adsldetectiface, cgi. */
#define FAILOVERING                "/tmp/failovering"
/* created/updated by rc adsldetectiface, udhcpc.failover.script, ip-up9.
 * deleted by failover daemon, used by rc adsldetectrule.. */
#define FAILOVER_GW_DNS            "/tmp/failovering_gw_dns"

/* created/deleted by failover daemon, used by cgi. */
#define FAILOVER2ADSLING          "/tmp/failover2adsling"
/* created/deleted by failover daemon, used by cgi. */
#define ADSL2FAILOVERING           "/tmp/adsl2failovering"

#define FAILOVER_NULL_FILE         "/dev/null"

#ifdef _ZIP_3G_
#define EX_MONITOR              "/tmp/dongle-bin/dongle_monitor"
#define EX_MGNT                 "/tmp/dongle-bin/dongle_mgnt"
#define EX_MODULE               "/tmp/dongle-bin/usbserial.ko"

#define LO_MONITOR              "/usr/sbin/dongle_monitor"
#define LO_MGNT                 "/usr/sbin/dongle_mgnt"
#define LO_MODULE               "/lib/modules/usbserial.ko"

#define DONGLE_MONITOR          "/var/usbmodem/dongle_monitor"
#define DONGLE_MGNT             "/var/usbmodem/dongle_mgnt"
#define USBSERIAL_KO            "/var/usbmodem/usbserial.ko"
#else
#define DONGLE_MONITOR          "/usr/sbin/dongle_monitor"
#define DONGLE_MGNT             "/usr/sbin/dongle_mgnt"
#define USBSERIAL_KO            "/lib/modules/usbserial.ko"
#endif

/*********************************************************
 *                   Other Files Path                    *
 *********************************************************/

// SYSTEM
#define RESOLV_CONF     "/etc/resolv.conf"

//CSRF
#define CSRF_SESSION_FILE "/tmp/SessionFile"
 
#endif /* _FILE_NAMES_H_ */


