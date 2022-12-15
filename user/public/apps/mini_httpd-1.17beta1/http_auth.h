#ifndef _HTTPD_AUTH_
#define _HTTPD_AUTH_

void auth_check( char* dirname );
int check_timeout(void);
void handle_chdir( int sig );
void handle_logout( int sig );

#ifndef HTTP_LOGIN_COOKIE

void digest_auth_check( char* dirname );
void set_http_tout(int sec);
void set_auth_flag(char *ips);
CHAR *ServerNotAuth(VOID);

#define MAX_HTML_NAME_LENGTH 63
#define MAX_USER_NAME_LENGTH 63
#define MAX_USER_PASSWORD_LENGTH 44
#define ACC_STR_TOKEN '-'
#define HTTP_ACCOUNT_TOKEN1 0X01
#define HTTP_ACCOUNT_TOKEN2 0X02
#define MAX_USER_NUM 10

typedef struct user_info_tab{
        char username[MAX_USER_NAME_LENGTH+1];
        char userpwd[MAX_USER_PASSWORD_LENGTH+1];
        char user_type;
}user_info_tab;

typedef enum
{
    BASIC_AUTH_TYPE,
    DIGEST_AUTH_TYPE
} HTTP_AUTH_TYPE_E;

#define MAX_DIGEST_USERS     10
#define HASHLEN 16
#define HASHHEXLEN 32
#define MAX_URL_STRING_LENGTH 100
typedef CHAR HASH[HASHLEN];
typedef CHAR HASHHEX[HASHHEXLEN+1];

enum{
	DI_USERNAME,
	DI_REALM,
	DI_NONCE,
	DI_URI,
	DI_ALGORITHM,
	DI_QOP,
	DI_NC,
	DI_CNONCE,
	DI_RESPONSE,
	DI_OPAQUE,
	DI_NONE,
	DI_ENUM_SIZE
};

#endif

#endif
