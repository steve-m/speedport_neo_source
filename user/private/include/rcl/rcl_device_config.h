/**
 * @file   rcl_user_account.h
 * @author Denny_Zhang@sdc.sercomm.com
 * @date   2011-12-14
 * @brief  account RC API
 *
 * Copyright - 2010 SerComm Corporation. All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document without notice.
 * SerComm Corporation makes no warranty, representation or guarantee regarding the suitability
 * of its products for any particular purpose. SerComm Corporation assumes no liability arising
 * out of the application or use of any product or circuit. SerComm Corporation specifically
 * disclaims any and all liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of others.
 */

#ifndef _RCL_DEVICE_CONFIG_H_
#define _RCL_DEVICE_CONFIG_H_

int rcl_backup_cfg(char *path);

int rcl_restore_cfg(char* path);

#endif
