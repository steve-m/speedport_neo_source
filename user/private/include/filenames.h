/*
 * All file names including application path, config file path and temp file path
 */
#ifndef _FILE_NAMES_H_
#define _FILE_NAMES_H_


/*********************************************************
 *                  Application Path                     *
 *********************************************************/
#define VCONFIG         "/sbin/vconfig"
#define ECHO            "/bin/echo"
#define CAT             "/bin/cat"
#define IFCONFIG        "/sbin/ifconfig"
#define KILLALL         "/usr/bin/killall"
#define INSMOD          "/sbin/insmod"
#define RMMOD           "/sbin/rmmod"
#define BRCTL           "/usr/sbin/brctl"
#define ROBOCFG         "/usr/sbin/robocfg"
#define WLCTL           "/usr/sbin/wl"
#define SENDARP         "/sbin/sendarp"
#define NAS             "/sbin/nas"
#define PPPD            "/usr/sbin/pppd"
#define PPTP            "/usr/sbin/pptp"
#define ATMARP          "/usr/sbin/atmarp"
#define ATMARPD          "/usr/sbin/atmarpd"
#define BR2684CTL       "/usr/sbin/br2684ctl"
//#define ATMCTL          "/usr/sbin/atmctl"
#define RT2684D         "/usr/sbin/rt2684d"
#define DHCPD_APP       "/usr/sbin/udhcpd"
#define NVRAM           "/usr/sbin/nvram"
#define TC              "/usr/sbin/tc"
#define LED_APP         "/usr/sbin/led_app"
#define PING            "/bin/ping"
#define BIN_LN          "/usr/sbin/ln -sf"
#define SYS_UPNP	    "/usr/sbin/miniupnpd"
#define CP              "/bin/cp"
#define EBTABLES        "/usr/sbin/ebtables"
#define RC              "/usr/sbin/rc"
#define IPTABLES        "/usr/sbin/iptables "
#define NETGEAR_NTP     "/usr/sbin/netgear_ntp"
#define DHCPC_APP       "/usr/sbin/udhcpc"
#define PPPOE_APP       "/usr/sbin/pppoe"
#define ET              "/usr/sbin/et"
#define BCMNVRAM        "/usr/sbin/bcmnvram"

/* gordon changed */
#define ADSLCTL 		"/usr/sbin/adslctl"
#define ATMCTL 			"/usr/sbin/xtmctl"
#define UDHCPC 			"/usr/sbin/udhcpc"
#define LN 				"/bin/ln"
#define IP 				"/usr/sbin/ip"

/*********************************************************
 *                  Config File Path                     *
 *********************************************************/
#define FTPD_CONF       "/var/bftpd.conf"
#define FTPD_PASSWD     "/var/ftpdpassword"

/* dhcp */
#define DHCPD_CONF      "/var/udhcpd.conf"
#define DHCPD_LEASES    "/var/udhcpd.leases"
#define DHCPD_RESERVED_INFO     "/etc/udhcpd.reserved_info"

/* httpd */
#define HTTPD_CONF      "/etc/htpasswd"
#define GUI_VERSION     "/etc/gui_version"
#define NEW_GUI_VERSION "/etc/new_gui_version"

/* 3G */
#define T3G_CONFIG              "/etc/gsmtd.conf"
#define DONGLE_PPPD_WANUP       "/etc/ppp/wan_uptime"
#define DONGLE_PPPD_SCRIPT      "/etc/ppp/peers/3g"
#define DONGLE_CHAT_SCRIPT      "/etc/ppp/scripts/3g.chat"
#define DONGLE_IP_UP_SCRIPT     "/etc/ppp/scripts/up"
#define DONGLE_IP_DOWN_SCRIPT   "/etc/ppp/scripts/down"

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
#define DONGLE_MGN              "/usr/sbin/dongle_mgnt"
#define USBSERIAL_KO            "/lib/modules/usbserial.ko"
#endif

/*********************************************************
 *                   Other Files Path                    *
 *********************************************************/
#define WAN_CMD_BASE    "/var/run/wan_cmd"
#define WAN_IF_BASE     "/var/run/wan_if"
#define WAN_IPADDR      "/tmp/wan_ipaddr"
#define WAN_UPTIME_BASE "/tmp/wan_uptime"
#define WAN_INTO_BASE   "/tmp/wan_info"
#define PPPOAE_NOT_START_BASE  "/tmp/PPPOAE_not_start_WAN"
/* CSRF Protection session file*/
#define CSRF_SESSION_FILE "/tmp/SessionFile"
/* WPS running flag file */
#define WPS_RUNNING_FLAG "/tmp/wps_is_running"
// dhcpc
#define DHCPC_SCRIPT            "/etc/udhcpc.script"
#define DHCPC_FIX_SCRIPT        "/etc/udhcpc.fix.script"
#define DHCPC_WIZARD_SCRIPT     "/etc/udhcpc.wizard.script"
#define DHCPC_PPTPC_SCRIPT      "/etc/udhcpc.pptpc.script"
#define DHCPC_ROUTE_RELATED_OPTIONS_DEL	"/tmp/dhcpc_route_related_options_del"
/*
 * Show dhcpc lease info
 * format of this file:
 *  <WAN DHCP Server IP Address>
 *  <Lease Time>
 *  <Uptime when get IP Address>
 */
#define DHCPC_LEASE             "/tmp/dhcpc.lease"
#define DHCPC_SERVER             "/tmp/dhcpc.server"

//pppd
//#define LCP_FILE        "/tmp/lcp"
//#define PPPD_FAIL       "/tmp/pppd.fail"
#define IP_DOWN_ACT     "/tmp/ip-down-act"
#define PPP_IPUP_DEMAND_BAK     "/usr/etc/ppp/ip-up-demand"
#define PPP_IPUP_BAK    "/usr/etc/ppp/ip-up"
#define PPP_IPUP        "/etc/ppp/ip-up"
#define PPTPC_GATEWAY   "/tmp/gateway"
#define PPP_MANUAL_CONNECT "/tmp/ppp_manual_connect"
//gordon
#define WAN_INFO_BASE "/tmp/w/info_"
#define LCP_FILE "/tmp/w/lcp_"
#define PPPD_FAIL "/tmp/w/pppd_fail_"
#define DEMAND_FILE "/tmp/w/demand_"

#define PPP_DEBUG    "logfile /tmp/ppp_log debug"
#define DEBUG_TMP  "/tmp/debug"


// ipoa
#define IPOA_SERV       "/tmp/ipoa_server"
#define ATMARPD_CHECK   "/tmp/atmarpd.dep"
#define ATM_DEV_CHECK   "/proc/sys/net/ipv4/conf/atm"

#define DEBUG_TMP       "/tmp/debug"

//Firewall
#define FW_RULE_BASE    "/tmp/rules"

//QOS
#define FW_QOS_GX		"/tmp/qos"

// TI ENV
#define TI_ENV          "/proc/ticfg/env"
#define ANNEX_VERSION   "/etc/version"

// VLAN
#define PROC_VLAN       "/proc/vlan"

// DNRD
#define BLANK_STATE    "/tmp/blank_state.out"

// NTP
#define NTP_START       "/tmp/ntp_start"

// SYSLOG
#define ALERT_FILE      "/var/log/alert"
#define MESSAGE_FILE    "/var/log/messages"
#define FIRST_LOG_FLAG  "/var/log/first"
#define LOG_SENT_BY_CGI "/var/log/log_sent_by_cgi"     /* use this flag to show log is sent by CGI */

// SYSTEM
#define PROC_IP_FWD     "/proc/sys/net/ipv4/ip_forward"
#define RESOLV_CONF     "/etc/resolv.conf"
#define PROC_SIP_ENABLE "/proc/sip_enable"
#define PROC_ARPTABLE   "/proc/net/arp"
#define PROC_WLAN_STATISTICS_ENTRY "/proc/wifi_statistics"

//WIZARD
#define WIZARD_PID              "/var/run/wizard.pid"
#define WIZARD_OUT              "/tmp/wizard.out"
#define DETECTOUT_PC            "/tmp/detect_dhcp_pc"
#define DETECTOUT_LOCAL         "/tmp/detect_dhcp_local"
#define DETECTOUT_PPTP          "/tmp/detect_pptp"
#define DETECTOUT_PPPOE         "/tmp/detect_pppoe"

//PPTP
#define PPTP_PHYGATEWAY         "/tmp/gateway"          /* be use by "udhcpc.pptpc.script" "pptp" */
#define PPTP_PHYIP              "/tmp/pptpc_phyip"

/*UPnP port rules file */
#define UPNP_TAB                "/tmp/upnptab"

//WIRELESS FILE  (RTL)
#define WPS_IS_UNCONFIGED       "/var/is_unconfiged"
#define WLAN_RESTART            "/var/wlan_restart"

//define file for USB related
#define USB_ADVANCED_CONF		"/etc/usb_httpd.conf"
/* Green Download */
#define USB_PLUS_SYSFILE1        "/sys/bus/usb/devices/1-1"
#define USB_PLUS_SYSFILE2        "/sys/bus/usb/devices/1-2"


/*********************************************************
 *                   GUI Files names                     *
 *********************************************************/
#define MODEM_LAN_PG              "modem_lan.htm"


#define LAN_LAN_PG              "LAN_lan.htm"
#define LAN_RSV_ADD_PG          "LAN_reserv_add.htm"
#define LAN_RSV_EDIT_PG         "LAN_reserv_edit.htm"

#define UPNP_UPNP_PG            "UPNP_upnp.htm"

#define BKS_KEYWORD_PG          "BKS_keyword.htm"
#define BKS_SERVICE_PG          "BKS_service.htm"
#define BKS_SERVICE_ADD_PG      "BKS_service_add.htm"

#define FW_REMOTE_PG            "FW_remote.htm"
#define FW_SCHEDULE_PG          "FW_schedule.htm"
#define FW_EMAIL_PG             "FW_email.htm"
#define FW_LOG_PG               "FW_log.htm"
#define FW_FORWARD_PG           "FW_forward.htm"
#define FW_FORWARD_SRV_PG       "FW_forward_service.htm"
#define FW_PT_PG                "FW_pt.htm"
#define FW_PT_SRV_PG            "FW_pt_service.htm"

#define STR_ROUTES_PG           "STR_routes.htm"
#define STR_ADD_PG              "STR_add.htm"

#define BAS_BASIC_PG            "BAS_basic.htm"
#define BAS_ETHER_PG            "BAS_ether.htm"
#define BAS_PPPOE_PG            "BAS_pppoe.htm"
#define BAS_PPPOA_PG            "BAS_pppoa.htm"
#define BAS_PPTP_PG             "BAS_pptp.htm"

#define WIZ_SEL_PG              "BRS_WIZ_sel.htm"
#define WIZ_CFM_PG              "WIZ_cfm.htm"
#define WIZ_PH_FAIL_PG          "WIZ_ph_fail.htm"
#define WIZ_DETWAN_PG           "WIZ_detwan.htm"
#define WIZ_DETWAN_FIX_PG       "WIZ_detwan_fix.htm"
#define WIZ_DETWAN_DYN_PG       "WIZ_detwan_dyn.htm"
#define WIZ_DETWAN_PPPOE_PG     "WIZ_detwan_pppoe.htm"
#define WIZ_DETWAN_PPPOA_PG     "WIZ_detwan_pppoa.htm"
#define WIZ_DETWAN_PPTP_PG      "WIZ_detwan_pptp.htm"
#define WIZ_FIX_PG              "WIZ_fix.htm"
#define WIZ_DYN_PG              "WIZ_dyn.htm"
#define WIZ_PPPOE_PG            "WIZ_pppoe.htm"
#define WIZ_PPPOA_PG            "WIZ_pppoa.htm"
#define WIZ_PPTP_PG             "WIZ_pptp.htm"
#define WIZ_CIP_PG              "wiz_cip.htm"
#define WIZ_DETWAN_NONE_PG       "wiz_none.htm"

#define WAN_WAN_PG              "WAN_wan.htm"

#define WLG_WIRELESS_PG         "WLG_wireless.htm"
#define WLG_WIRELESS1_PG        "WLG_wireless1.htm"
#define WLG_WIRELESS2_PG        "WLG_wireless2.htm"
#define WLG_WIRELESS3_PG        "WLG_wireless3.htm"
#define WLG_WIRELESS4_PG        "WLG_wireless4.htm"
#define WLG_WIRELESS_GUEST_PG   "WLG_wireless_guest.htm"
#define WLG_WIRELESS_GUEST1_PG  "WLG_wireless_guest1.htm"
#define WLG_WIRELESS_GUEST2_PG  "WLG_wireless_guest2.htm"
#define WLG_WIRELESS_GUEST3_PG  "WLG_wireless_guest3.htm"
#define WLG_ADV_PG              "WLG_adv.htm"
#define WLG_ACL_PG              "WLG_acl.htm"
#define WLG_ACL_EDIT_PG         "WLG_acl_edit.htm"
#define WLG_WDS_PG              "WLG_wds.htm"


#define WPS_PG                  "WPS.htm"
#define WPS_PIN_PG              "WPS_PIN.htm"

#define DNS_DDNS_PG             "DNS_ddns.htm"

#define QOS_MAIN_PG             "QOS_main.htm"
#define QOS_LIST_PG             "QOS_list.htm"

#define TRAFFIC_METER_PG        "traffic_meter.htm"

#define RST_STATUS_PG           "RST_status.htm"
#define RST_ST_DHCP_PG          "RST_st_dhcp.htm"
#define RST_ST_FIXIP_PG         "RST_st_fix.htm"
#define RST_ST_POE_PG           "RST_st_poe.htm"
#define RST_ST_PPTP_PG          "RST_st_pptp.htm"


//upgrade
#define UPG_CONNECT_PG			"VER_check.htm"
#define UPG_FAIL_PG				"VER_check_error.htm"
#define UPG_NEW_PG				"VER_fw_found.htm"
#define UPG_NONEW_PG			"VER_fw_not_found.htm"
#define UPG_FW_ERROR_PG			"UPG_fw_error.htm"
#define AUTO_UPG_PG				"CheckNewFW.html"
#define AUTO_UPG_NONEW_PG		"CheckNewFW_Success.html"
#define ATUO_UPG_FAIL_PG		"NoInternetConn.htm"
#define ATUO_UPG_DOWNLOADING_PG "CheckNewFW_upgrade_downloading.htm"
#define ATUO_UPG_WRITING_PG		"CheckNewFW_upgrade_writing.htm"
#define UPG_PG					"UPG_upgrade.htm"
#define UPG_WRONG_FILE          "UPG_wrong_file.htm"
#define UPDATE_SETTING_PG       "update_setting.htm"
#define REBOOT_PG               "reboot_pg.htm"
#define UPG_NEW_GUI_PG          "VER_gui_found.htm"
#define CHECK_NEW_LANG_PG       "CheckNewLang.html"
#define CHECK_LANG_NO_CONN_PG   "CheckLangNoInternetConn.htm"
#define UPDATING_GUI_PG         "updating_gui.htm"
#define UPDATING_GUI_ERR_PG     "updating_gui_err.htm"
#define MNU_TOP_PG              "MNU_top.htm"

#ifdef PNPX
#define PNPX_AUTO_UPG_PG        "CheckNewFW_PNPX.html"
#define PNPX_ATUO_UPG_DOWNLOADING_PG  "CheckNewFW_upgrade_downloading_PNPX.htm"
#endif

//ADSL
#define ADSL_SETTING_PG         "adsl_setting.htm"

//USB
#define USB_EDIT_FLD_PG         "usb_edit_fld.htm"
#define USB_NEW_FLD_PG         "usb_new_fld.htm"
#define USB_ADV_PG              "usb_adv.htm"

//restore config
#define BAK_BACKUP_PG            "BAK_backup.htm"
#define BAK_UPDATE_PG            "update_setting.htm"

//Genie Wizard
#define BRS_RESTORE_FAIL_PG         "BRS_03B_haveBackupFile_fileRestore_fail.html"
#define BRS_RESTORE_PG              "BRS_03B_haveBackupFile.html"
#define BRS_RESTORE_REBOOT_PG       "BRS_03B_haveBackupFile_waitReboot.html"
#define BRS_CHECKNET_PING_PG        "BRS_01_checkNet_ping.html"
#define BRS_GENIEHELP_PG            "BRS_02_genieHelp.html"
#define BRS_NOWAN_PG                "BRS_03A_A_noWan.html"
#define BRS_DETWAN_PG               "BRS_03A_detcInetType.html"
#define BRS_WIZMSG_PG               "BRS_03A_detcInetTypeWait.html"
#define BRS_WIZPPPOE_PG             "BRS_03A_B_pppoe.html"
#define BRS_WIZPPPOE_REENT_PG       "BRS_03A_B_pppoe_reenter.html"
#define BRS_WIZPPPOA_PG             "BRS_03A_B_pppoa.html"
#define BRS_WIZPPPOA_REENT_PG       "BRS_03A_B_pppoa_reenter.html"

#if 0
#define BRS_WIZDHCPC_PG             "BRS_04_B_checkNet_ping.html"
#define BRS_WIZDHCPC2_PG            "BRS_04_B_checkNet.html"
#else
#define BRS_WIZDHCPC_PG             "BRS_03A_B_dhcpc.html"

#endif
#define BRS_WIZNONE_PG              "BRS_03A_E_IP_problem.html"
#define BRS_MACCLONE_PG             "BRS_03A_E_IP_problem_staticIP_B_macClone.html"
#define BRS_STATICIP_PG             "BRS_03A_E_IP_problem_staticIP_A_inputIP.html"

#define BRS_NETWORKISSUE_PG         "BRS_05_networkIssue.html"
#define BRS_SUCCESS_PG              "BRS_success.html"
#define BRS_HIJACK_SUCCESS_PG       "BRS_hijack_success.htm"
// change netgear to sercomm
#define BRS_NTGR_SUCCESS_PG         "BRS_sercomm_success.html"
#define BRS_INDEX_PG                "BRS_index.htm"
#define BRS_HIJACK_INDEX_PG         "BRS_hijack_index.htm"
#define BRS_WIZ_SEL_PG              "BRS_WIZ_sel.htm"
#define BRS_MANUAL_PG               "BRS_start.htm"
#define BRS_SHOW_BASIC              "/tmp/show_basic_setting"



// First page
#define RST_RELOAD_PG           "RST_reload.htm"
#define LANG_CHG_PG             "LANG_change.htm"
//#define START_PG                "start.htm"
#define START_PG                "index.htm"
#endif /* _FILE_NAMES_H_ */


