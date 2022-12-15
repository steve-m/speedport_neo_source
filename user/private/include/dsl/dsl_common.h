#ifndef __DSL_COMMON_H__
#define __DSL_COMMON_H__

typedef struct adsl_info_s{
	char 	status[128];
	int	down_stream;
	int	up_stream;
	int	down_currstream;
	int	up_currstream;
	unsigned int last_change;
	unsigned int t_blocks;
	unsigned int r_blocks;
	unsigned int crc_errs;
	unsigned int hec_errs;
	unsigned int fec_errs;
	unsigned int show_crc_errs;
	unsigned int show_fec_errs;
	char 	c_profile[16];
	char 	down_attenuation[16];
	char 	up_attenuation[16];
	char 	down_power[16];
	char 	up_power[16];
	char 	u_trell[16];
	char 	d_trell[16];
	char 	down_snrmpb[16];
	char 	up_snrmpb[16];
	char 	standard[16];
	char 	annex[16];
	char 	tps_tc[16];
}adsl_info_t;

int start_adsl(void);
int start_dsl_if(int wan_id);
int stop_dsl_if(int wan_id);
int get_adsl_info(adsl_info_t *adsl);
#endif
