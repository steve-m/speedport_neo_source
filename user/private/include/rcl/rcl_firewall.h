#ifndef _RCL_FIREWALL_H_
#define _RCL_FIREWALL_H_
#define _SC_SPI_FIREWALL_ 1
/*--------------- COMMON -------------*/
#ifdef _SC_SPI_FIREWALL_
int rcl_init_spi_env(void);
int rcl_fw_start_sc_fw(int argc, char** argv);
int rcl_fw_stop_sc_fw(int argc, char** argv);
#endif
int rcl_fw_start_input_mgnt_lan(int argc, char** argv);
int rcl_fw_stop_input_mgnt_lan(int argc, char** argv);

int rcl_fw_start_ping2wan(int argc, char** argv);
int rcl_fw_stop_ping2wan(int argc, char** argv);

/* alg */
int rcl_fw_start_alg_h323(int argc, char** argv);
int rcl_fw_stop_alg_h323(int argc, char** argv);
int rcl_fw_start_alg_sip(int argc, char** argv);
int rcl_fw_stop_alg_sip(int argc, char** argv);
int rcl_fw_start_alg_rtsp(int argc, char** argv);
int rcl_fw_stop_alg_rtsp(int argc, char** argv);
int rcl_fw_start_alg_iperf(int argc, char** argv);
int rcl_fw_stop_alg_iperf(int argc, char** argv);

/* vpn passthrough */
int rcl_fw_start_vps_ipsec(int argc, char** argv);
int rcl_fw_stop_vps_ipsec(int argc, char** argv);
int rcl_fw_start_vps_pptp(int argc, char** argv);
int rcl_fw_stop_vps_pptp(int argc, char** argv);
int rcl_fw_start_vps_l2tp(int argc, char** argv);
int rcl_fw_stop_vps_l2tp(int argc, char** argv);

int rcl_fw_start_policy_lan(int argc, char** argv);
int rcl_fw_stop_policy_lan(int argc, char** argv);

int rcl_fw_start_pctrl(int argc, char** argv);
int rcl_fw_stop_pctrl(int argc, char** argv);

int rcl_fw_start_trule(int argc, char** argv);
int rcl_fw_stop_trule(int argc, char** argv);

int rcl_fw_start_protect_lan(int argc, char** argv);
int rcl_fw_stop_protect_lan(int argc, char** argv);

/*---------------- WAN ---------------*/
int rcl_fw_start_input_mgnt_wan(int wan_id, int argc, char** argv);
int rcl_fw_stop_input_mgnt_wan(int wan_id, int argc, char** argv);

int rcl_fw_start_nat(int wan_id, int argc, char** argv);
int rcl_fw_stop_nat(int wan_id, int argc, char** argv);

int rcl_fw_start_spi(int wan_id, int argc, char** argv);
int rcl_fw_stop_spi(int wan_id, int argc, char** argv);

int rcl_fw_start_spi_lan(int argc, char** argv);
int rcl_fw_stop_spi_lan(int argc, char** argv);

int rcl_fw_start_dns(int wan_id, int argc, char** argv);
int rcl_fw_stop_dns(int wan_id, int argc, char** argv);
int rcl_fw_start_mss(int argc, char** argv);
int rcl_fw_stop_mss(int argc, char** argv);


int rcl_fw_start_dmz(int wan_id, int argc, char** argv);
int rcl_fw_stop_dmz(int wan_id, int argc, char** argv);

int rcl_fw_start_port_trg(int wan_id, int argc, char** argv);
int rcl_fw_stop_port_trg(int wan_id, int argc, char** argv);

int rcl_fw_start_port_map(int wan_id, int argc, char** argv);
int rcl_fw_stop_port_map(int wan_id, int argc, char** argv);

int rcl_fw_start_policy_wan(int wan_id, int argc, char** argv);
int rcl_fw_stop_policy_wan(int wan_id, int argc, char** argv);

int rcl_fw_start_protect_wan(int wan_id, int argc, char** argv);
int rcl_fw_stop_protect_wan(int wan_id, int argc, char** argv);

int rcl_fw_start_port_filter(int wan_id, int argc, char** argv);
int rcl_fw_stop_port_filter(int wan_id, int argc, char** argv);

int rcl_fw_start_abuse_dect(int wan_id, int argc, char** argv);
int rcl_fw_stop_abuse_dect(int wan_id, int argc, char** argv);

int rcl_fw_stop_pppoefwd(int wanid, int argc, char** argv);
int rcl_fw_start_pppoefwd(int wanid, int argc, char** argv);

int rcl_fw_ipv6_start_abuse_dect(int wan_id, int argc, char** argv);
int rcl_fw_ipv6_stop_abuse_dect(int wan_id, int argc, char** argv);
#endif
