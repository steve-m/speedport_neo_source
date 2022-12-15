#ifndef CAL_USER_ACCOUNT_H
#define CAL_USER_ACCOUNT_H
#include <pwd.h>

enum
{
    UA_ACCOUNT_FULL_NAME = 0,
    UA_ACCOUNT_USER_NAME,
    UA_ACCOUNT_PASSWORD,
    UA_ACCOUNT_GROUP,
    UA_ACCOUNT_LANGUAGE,
    UA_ACCOUNT_PERMISSION
};

enum UA_encrypt
{
    UA_ENCRYPT_NONE = 0,
    UA_ENCRYPT_MD5,
    UA_ENCRYPT_CRYPT_MD5
};

enum UA_Service
{
    UA_SERVICE_WEB = 0,
    UA_SERVICE_CLI
};

typedef struct 
{
    char username[256];
    char passwd[128];
}UA_info;

#define UA_Servive_str_web  "web"
#define UA_Servive_str_cli  "cli"

#define UA_VALID_USER_ID_BEGIN      1 
#define UA_MAX_USER_NUM             32
#define UA_ROOT_ID                  1
#define UA_ADMIN_GROUP              "admin"
#define UA_USER_GROUP               "user"
#define UA_ADMIN_GROUP_ID           0
#define UA_SUPPORT_GROUP_ID         2002
#define UA_USER_GROUP_ID            2003
#define UA_ADMIN_ID_BASE            0 
#define UA_SUPPORT_ID_BASE          0 
#define UA_USER_ID_BASE             1000

int cal_UA_get_entry_index_list(int** index_array);
char *cal_UA_get_account_details(int id, int element);
int cal_UA_get_service_accounts(char *service, UA_info ** info_arr);
/* --------------------------------------------------------------------------*/
/**
 * @brief     set account details according to element
 *
 * @Param    id
 * @Param    value
 *
 * @Returns  0 success, else fail.  
 */
/* ----------------------------------------------------------------------------*/
int cal_UA_set_account_details(int id, int element, char *value);
int cal_UA_delete_account(int id);
int cal_UA_add_account();
int cal_UA_get_user_index(int element, const char *match);

int cal_UA_generate_passwd_file(char *service, char *path, int encrypt);
struct passwd *cal_UA_getpwnam(char *path, const char * name);

int cal_UA_get_gui_permission(const char *name, int groupID);


#endif

