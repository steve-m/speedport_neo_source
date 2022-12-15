
#ifndef _HAL_FLASH_H_
#define _HAL_FLASH_H_


int hal_flash_store_dhcp_lease_info(char *data_file);
int hal_flash_load_dhcp_lease_info(char *data_file);
int hal_flash_get_dhcp_lease_info_max_size(void);


#endif /* _HAL_FLASH_H_ */

