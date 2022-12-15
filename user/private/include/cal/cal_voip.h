
#ifndef _CAL_VOIP_H_
#define _CAL_VOIP_H_

typedef enum
{
    CAL_VOIP_PROFILE_DEFAULT = 1,
} CAL_VOIP_PROFILE;

typedef enum
{
    CAL_VOIP_LINE_ID_1 = 1,
    CAL_VOIP_LINE_ID_2,
    CAL_VOIP_LINE_ID_END
} CAL_VOIP_LINE_ID;

typedef enum
{
    CAL_VOIP_TONE_ID_DIAL = 1,
    CAL_VOIP_TONE_ID_BUSY,
    CAL_VOIP_TONE_ID_REORDER,
    CAL_VOIP_TONE_ID_ALTER,
    CAL_VOIP_TONE_ID_CALLWAITING,
    CAL_VOIP_TONE_ID_RINGBACK,
    CAL_VOIP_TONE_ID_END
} CAL_VOIP_TONE_ID;

typedef enum
{
    CAL_VOIP_CODEC_ID_G711MULAW = 1,
    CAL_VOIP_CODEC_ID_G711ALAW,
    CAL_VOIP_CODEC_ID_G726,
    CAL_VOIP_CODEC_ID_G729,
    CAL_VOIP_CODEC_ID_END
} CAL_VOIP_CODEC_ID;

/* The CAL_VOIP_RETURN_TYPE is just used in the cal_voip_get_xxx func. */
typedef enum
{
    CAL_VOIP_RETURN_TYPE_NORMAL = 0,    /* return the original value */
    CAL_VOIP_RETURN_TYPE_APPCONF,       /* voip application config file use */
} CAL_VOIP_RETURN_TYPE;


typedef enum
{
    CAL_VOIP_LOG_LEVEL_LOW = 0,
    CAL_VOIP_LOG_LEVEL_MID = 2,
    CAL_VOIP_LOG_LEVEL_HIGH = 4,
    CAL_VOIP_LOG_LEVEL_OFF = 6,
} CAL_VOIP_LOG_LEVEL;


#define CAL_VOIP_CONFIG_LEN_MAX     256


/*****************************************************************************

Function: cal_voip_get_xxx()
          Return: 1) NULL -- get error
                  2) A static buffer pointer, which include the value string.

Function: cal_voip_set_xxx()
          Return: 1) 0  -- success
                  2) !0 -- fail
                  
Parameters:
          int prof      -- defined in enum CAL_VOIP_PROFILE
                           This parameter is for functional extention in the future.
                           Maybe it is used to identify different type config(flash/ram).
                           Now there is just one value, and no practical use.
                           
          int line_id   -- defined in enum CAL_VOIP_LINE_ID
          
          int tone_id   -- defined in enum CAL_VOIP_TONE_ID
          
          int codec_id  -- defined in enum CAL_VOIP_CODEC_ID
          
          int ret_type  -- defined in enum CAL_VOIP_RETURN_TYPE
                           This parameter is just used in the cal_voip_get_xxx func.
          
******************************************************************************/
char *cal_voip_get_dtmf_method(int prof, int ret_type);
int   cal_voip_set_dtmf_method(int prof, char *value);
char *cal_voip_get_digit_map(int prof);
int   cal_voip_set_digit_map(int prof, char *value);
char *cal_voip_get_fax_mode(int prof, int ret_type);
int   cal_voip_set_fax_mode(int prof, char *value);

char *cal_voip_get_proxy_server(int prof);
int   cal_voip_set_proxy_server(int prof, char *value);
char *cal_voip_get_proxy_server_port(int prof);
int   cal_voip_set_proxy_server_port(int prof, char *value);
char *cal_voip_get_sec_proxy_server(int prof);
int   cal_voip_set_sec_proxy_server(int prof, char *value);
char *cal_voip_get_sec_proxy_server_port(int prof);
int   cal_voip_set_sec_proxy_server_port(int prof, char *value);
char *cal_voip_get_user_agent_domain(int prof);
int   cal_voip_set_user_agent_domain(int prof, char *value);
char *cal_voip_get_sec_user_agent_domain(int prof);
int   cal_voip_set_sec_user_agent_domain(int prof, char *value);
char *cal_voip_get_user_agent_port(int prof);
int   cal_voip_set_user_agent_port(int prof, char *value);
char *cal_voip_get_outbound_proxy_enable(int prof);
int   cal_voip_set_outbound_proxy_enable(int prof, char *value);
char *cal_voip_get_outbound_proxy(int prof);
int   cal_voip_set_outbound_proxy(int prof, char *value);
char *cal_voip_get_outbound_proxy_port(int prof);
int   cal_voip_set_outbound_proxy_port(int prof, char *value);
char *cal_voip_get_dns_srv_enable(int prof);
int   cal_voip_set_dns_srv_enable(int prof, char *value);
char *cal_voip_get_register_expires(int prof);
int   cal_voip_set_register_expires(int prof, char *value);
char *cal_voip_get_reg_retry_interval(int prof);
int   cal_voip_set_reg_retry_interval(int prof, char *value);
char *cal_voip_get_sip_dscp_mark(int prof, int ret_type);
int   cal_voip_set_sip_dscp_mark(int prof, char *value);
char *cal_voip_get_session_timers_enable(int prof);
int   cal_voip_set_session_timers_enable(int prof, char *value);
char *cal_voip_get_session_expires(int prof);
int   cal_voip_set_session_expires(int prof, char *value);
char *cal_voip_get_min_session_expires(int prof);
int   cal_voip_set_min_session_expires(int prof, char *value);

char *cal_voip_get_rtp_local_port_min(int prof);
int   cal_voip_set_rtp_local_port_min(int prof, char *value);
char *cal_voip_get_rtp_dscp_mark(int prof, int ret_type);
int   cal_voip_set_rtp_dscp_mark(int prof, char *value);

char *cal_voip_get_cptone_freq_1(int prof, int tone_id);
int   cal_voip_set_cptone_freq_1(int prof, int tone_id, char *value);
char *cal_voip_get_cptone_power_1(int prof, int tone_id);
int   cal_voip_set_cptone_power_1(int prof, int tone_id, char *value);
char *cal_voip_get_cptone_freq_2(int prof, int tone_id);
int   cal_voip_set_cptone_freq_2(int prof, int tone_id, char *value);
char *cal_voip_get_cptone_power_2(int prof, int tone_id);
int   cal_voip_set_cptone_power_2(int prof, int tone_id, char *value);
char *cal_voip_get_cptone_duration_on_1(int prof, int tone_id);
int   cal_voip_set_cptone_duration_on_1(int prof, int tone_id, char *value);
char *cal_voip_get_cptone_duration_off_1(int prof, int tone_id);
int   cal_voip_set_cptone_duration_off_1(int prof, int tone_id, char *value);
char *cal_voip_get_cptone_duration_on_2(int prof, int tone_id);
int   cal_voip_set_cptone_duration_on_2(int prof, int tone_id, char *value);
char *cal_voip_get_cptone_duration_off_2(int prof, int tone_id);
int   cal_voip_set_cptone_duration_off_2(int prof, int tone_id, char *value);

char *cal_voip_get_faxT38_high_speed_redundancy(int prof);
int   cal_voip_set_faxT38_high_speed_redundancy(int prof, char *value);
char *cal_voip_get_faxT38_low_speed_redundancy(int prof);
int   cal_voip_set_faxT38_low_speed_redundancy(int prof, char *value);

char *cal_voip_get_line_enable(int prof, int line_id, int ret_type);
int   cal_voip_set_line_enable(int prof, int line_id, char *value);
char *cal_voip_get_line_directory_number(int prof, int line_id);
int   cal_voip_set_line_directory_number(int prof, int line_id, char *value);
char *cal_voip_get_line_auth_username(int prof, int line_id);
int   cal_voip_set_line_auth_username(int prof, int line_id, char *value);
char *cal_voip_get_line_auth_password(int prof, int line_id);
int   cal_voip_set_line_auth_password(int prof, int line_id, char *value);
char *cal_voip_get_line_call_forward_activate(int prof, int line_id);
int   cal_voip_set_line_call_forward_activate(int prof, int line_id, char *value);
char *cal_voip_get_line_call_forward_mode(int prof, int line_id, int ret_type);
int   cal_voip_set_line_call_forward_mode(int prof, int line_id, char *value);
char *cal_voip_get_line_call_forward_number(int prof, int line_id);
int   cal_voip_set_line_call_forward_number(int prof, int line_id, char *value);
char *cal_voip_get_line_call_forward_no_answer_time(int prof, int line_id);
int   cal_voip_set_line_call_forward_no_answer_time(int prof, int line_id, char *value);
char *cal_voip_get_line_anoncall_block_activate(int prof, int line_id);
int   cal_voip_set_line_anoncall_block_activate(int prof, int line_id, char *value);
char *cal_voip_get_line_anoncall_block_enable(int prof, int line_id);
int   cal_voip_set_line_anoncall_block_enable(int prof, int line_id, char *value);
char *cal_voip_get_line_caller_id_block_activate(int prof, int line_id);
int   cal_voip_set_line_caller_id_block_activate(int prof, int line_id, char *value);
char *cal_voip_get_line_caller_id_block_enable(int prof, int line_id);
int   cal_voip_set_line_caller_id_block_enable(int prof, int line_id, char *value);
char *cal_voip_get_line_call_waiting_activate(int prof, int line_id);
int   cal_voip_set_line_call_waiting_activate(int prof, int line_id, char *value);
char *cal_voip_get_line_call_waiting_enable(int prof, int line_id);
int   cal_voip_set_line_call_waiting_enable(int prof, int line_id, char *value);
char *cal_voip_get_line_dnd_activate(int prof, int line_id);
int   cal_voip_set_line_dnd_activate(int prof, int line_id, char *value);
char *cal_voip_get_line_dnd_enable(int prof, int line_id);
int   cal_voip_set_line_dnd_enable(int prof, int line_id, char *value);
char *cal_voip_get_line_call_transfer_activate(int prof, int line_id);
int   cal_voip_set_line_call_transfer_activate(int prof, int line_id, char *value);
char *cal_voip_get_line_call_return_activate(int prof, int line_id);
int   cal_voip_set_line_call_return_activate(int prof, int line_id, char *value);
char *cal_voip_get_line_repeat_dial_activate(int prof, int line_id);
int   cal_voip_set_line_repeat_dial_activate(int prof, int line_id, char *value);

char *cal_voip_get_keys_of_set_cf_number(int prof);
int   cal_voip_set_keys_of_set_cf_number(int prof, char *value);
char *cal_voip_get_keys_of_enable_cf_all(int prof);
int   cal_voip_set_keys_of_enable_cf_all(int prof, char *value);
char *cal_voip_get_keys_of_disable_cf_all(int prof);
int   cal_voip_set_keys_of_disable_cf_all(int prof, char *value);
char *cal_voip_get_keys_of_enable_cf_on_busy(int prof);
int   cal_voip_set_keys_of_enable_cf_on_busy(int prof, char *value);
char *cal_voip_get_keys_of_enable_cf_on_noanswer(int prof);
int   cal_voip_set_keys_of_enable_cf_on_noanswer(int prof, char *value);
char *cal_voip_get_keys_of_disable_cf_on_busy_and_noanswer(int prof);
int   cal_voip_set_keys_of_disable_cf_on_busy_and_noanswer(int prof, char *value);
char *cal_voip_get_keys_of_xfer_without_consultation(int prof);
int   cal_voip_set_keys_of_xfer_without_consultation(int prof, char *value);
char *cal_voip_get_keys_of_xfer_with_consultation(int prof);
int   cal_voip_set_keys_of_xfer_with_consultation(int prof, char *value);
char *cal_voip_get_keys_of_enable_anoncall_block(int prof);
int   cal_voip_set_keys_of_enable_anoncall_block(int prof, char *value);
char *cal_voip_get_keys_of_disable_anoncall_block(int prof);
int   cal_voip_set_keys_of_disable_anoncall_block(int prof, char *value);
char *cal_voip_get_keys_of_enable_caller_id_block(int prof);
int   cal_voip_set_keys_of_enable_caller_id_block(int prof, char *value);
char *cal_voip_get_keys_of_disable_caller_id_block(int prof);
int   cal_voip_set_keys_of_disable_caller_id_block(int prof, char *value);
char *cal_voip_get_keys_of_enable_call_waiting(int prof);
int   cal_voip_set_keys_of_enable_call_waiting(int prof, char *value);
char *cal_voip_get_keys_of_disable_call_waiting(int prof);
int   cal_voip_set_keys_of_disable_call_waiting(int prof, char *value);
char *cal_voip_get_keys_of_enable_dnd(int prof);
int   cal_voip_set_keys_of_enable_dnd(int prof, char *value);
char *cal_voip_get_keys_of_disable_dnd(int prof);
int   cal_voip_set_keys_of_disable_dnd(int prof, char *value);
char *cal_voip_get_keys_of_call_return(int prof);
int   cal_voip_set_keys_of_call_return(int prof, char *value);
char *cal_voip_get_keys_of_redial(int prof);
int   cal_voip_set_keys_of_redial(int prof, char *value);

char *cal_voip_get_tx_gain(int prof);
int   cal_voip_set_tx_gain(int prof, char *value);
char *cal_voip_get_rx_gain(int prof);
int   cal_voip_set_rx_gain(int prof, char *value);
char *cal_voip_get_slic_tx_gain(int prof);
int   cal_voip_set_slic_tx_gain(int prof, char *value);
char *cal_voip_get_slic_rx_gain(int prof);
int   cal_voip_set_slic_rx_gain(int prof, char *value);

char *cal_voip_get_first_digit_timer(int prof);
int   cal_voip_set_first_digit_timer(int prof, char *value);
char *cal_voip_get_inter_digit_timer(int prof);
int   cal_voip_set_inter_digit_timer(int prof, char *value);
char *cal_voip_get_flash_hook_min_time(int prof);
int   cal_voip_set_flash_hook_min_time(int prof, char *value);
char *cal_voip_get_flash_hook_max_time(int prof);
int   cal_voip_set_flash_hook_max_time(int prof, char *value);
char *cal_voip_get_caller_id_detection_type(int prof, int ret_type);
int   cal_voip_set_caller_id_detection_type(int prof, char *value);
char *cal_voip_get_region(int prof, int ret_type);
int   cal_voip_set_region(int prof, char *value);

char *cal_voip_get_codec_vad(int prof);
int   cal_voip_set_codec_vad(int prof, char *value);
char *cal_voip_get_codec_packetization_period(int prof, int codec_id);
int   cal_voip_set_codec_packetization_period(int prof, int codec_id, char *value);
char *cal_voip_get_codec_enable(int prof, int codec_id);
int   cal_voip_set_codec_enable(int prof, int codec_id, char *value);
char *cal_voip_get_codec_priority(int prof, int codec_id);
int   cal_voip_set_codec_priority(int prof, int codec_id, char *value);

char *cal_voip_get_log_level(int prof, int ret_type);
int   cal_voip_set_log_level(int prof, char *value);

char *cal_voip_get_network_interface(int prof);
int   cal_voip_set_network_interface(int prof, char *value);

#endif  /* _CAL_VOIP_H_ */

