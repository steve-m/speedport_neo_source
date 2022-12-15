#ifndef _UTIL_BRD_H_
#define _UTIL_BRD_H_


int util_read_board_info_to_ram(void);

int util_get_hw_mac(char *buf, int buf_len);
int util_get_hw_sn(char *buf, int buf_len);
int util_get_hw_version(char *buf, int buf_len);
int util_get_hw_pid(char *buf, int buf_len);

#define HW_ID_LEN 			32
int util_get_hw_id(char *buf, int buf_len);
int util_get_hw_boot_version(char *buf, int buf_len);

int util_set_hw_mac(char *value);
int util_set_hw_sn(char *value);
int util_set_hw_version(char *value);


#endif /* _UTIL_BRD_H_ */
