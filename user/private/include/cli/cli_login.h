/** 
* @file   cli_login.h. 
* @module SERCOMM CLI
* @author Miracle Wang
* @version V1.00 
*
* 
* @copyright 2011 SerComm Corporation. All Rights Reserved. */

#ifndef _CLI_LOGIN_H
#define _CLI_LOGIN_H

#include <sys/types.h>
#include <pwd.h>
#include "cal/cal_user_account.h"

//#define SC_CRYPT_SALT           "$1$SERCOMM$"
#define MAXHOSTNAMELEN          256 
#define CLI_PASSWD_FILE         "/etc/passwd"
#define ROOT_GID                UA_ADMIN_GROUP_ID
#define SUPPORT_GID             UA_SUPPORT_GROUP_ID
#define USER_GID                UA_USER_GROUP_ID

struct passwd* cli_login_auth(int argc, char **argv);


#endif

