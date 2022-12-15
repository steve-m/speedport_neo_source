#include "version.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <limits.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
#include <pwd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <dirent.h>
#include <sys/sysinfo.h>
#include "scutil.h"
#include "md5.h"
#include "http_auth.h"
#if 0
#include "cal/cal_user_account.h"
#include "cal/cal_mgmt.h"
#endif

#ifndef AUTH_FILE
#define AUTH_FILE ".htpasswd"
#endif /* AUTH_FILE */

#ifndef _SC_BUILD_
#define _SC_BUILD_
#endif

extern SAVETIME;

extern char* remoteuser;
extern char* aclevel;
extern char* query;
extern char* cookie;
extern char cwd[MAXPATHLEN];
extern int  web_timeout; /* timeout */
extern time_t last_access_time; /* last access time*/
extern int someone_in_use;  /*1=someone in use, 0=nobody*/
extern char remote_ip[256]; /* current user's ip */
extern char last_remote_ip[256]; /*lastest user's ip*/
extern char *rondir;
extern int not_auth;

extern void send_error( int s, char* title, char* extra_header, char* text );
extern void send_error_body( int s, char* title, char* text );
extern int send_error_file( char* filename );
extern int b64_decode( const char* str, unsigned char* space, int size );
extern void send_authenticate( char* realm );

extern char* hu_get(const char *name);
extern void hu_set(const char* name,const char* value);
extern void hu_flush(void);
extern void hu_show(void);

//#define DEBUG_MODE

#ifdef DEBUG_MODE
void print2console(const char *format, ...)
{
    char buf[4096];
    char buf2[4096];
    va_list arg;
	  memset(buf,'\0',4096);
	  memset(buf2,'\0',4096);

    va_start(arg, format);
    vsnprintf(buf,4096, format, arg);
    va_end(arg);

    // add time info
//  sprintf(buf2,"/bin/cat /proc/uptime > /dev/console; /bin/echo \"%s\" > /dev/console", buf);
    sprintf(buf2,"/bin/echo \"%s\" > /dev/console", buf);

    system (buf2);
    usleep(1);
}
#else
#define print2console(format, ...)
#endif

/************************Implemented for Digest **********************************************/
static long Time_Get();

#define SYSTIME Time_Get()
#define INT32 signed   long

/***the nonce_check_s may be needed when blocking the attack*********/
//typedef struct nonce_check_s{
//    char *username;
//    char ipaddr[16];
//    char nextnonce[HASHLEN+1];
//	  DWORD nc_value;
//}nonce_check_s;
//struct nonce_check_s all_nonces[MAX_DIGEST_USERS];
static char *digest_str_db[DI_ENUM_SIZE]={
	"username","realm","nonce","uri","algorithm","qop","nc","cnonce",
	"response","opaque",0};
char digest_value_db[DI_ENUM_SIZE][MAX_URL_STRING_LENGTH];
static CHAR md5_string[]="md5";
/********************************End Implemented for Digest ***********************************/

static void dump_digest_value_db(void)
{
    print2console("####digest_value_db####\n");
    print2console("DI_USERNAME=<%s>\n", digest_value_db[DI_USERNAME]);
    print2console("DI_REALM=<%s>\n", digest_value_db[DI_REALM]);
    print2console("DI_NONCE=<%s>\n", digest_value_db[DI_NONCE]);
    print2console("DI_URI=<%s>\n", digest_value_db[DI_URI]);
    print2console("DI_ALGORITHM=<%s>\n", digest_value_db[DI_ALGORITHM]);
    print2console("DI_QOP=<%s>\n", digest_value_db[DI_QOP]);
    print2console("DI_NC=<%s>\n", digest_value_db[DI_NC]);
    print2console("DI_CNONCE=<%s>\n", digest_value_db[DI_CNONCE]);
    print2console("DI_RESPONSE=<%s>\n", digest_value_db[DI_RESPONSE]);
    print2console("DI_OPAQUE=<%s>\n", digest_value_db[DI_OPAQUE]);
    print2console("DI_NONE=<%s>\n", digest_value_db[DI_NONE]);
}

void set_http_tout(int sec)
{
    char ts[16] = {0};

    sprintf(ts, "%d", sec);
    hu_set("http_tout", ts);
}

static int get_http_tout(void)
{
    char *ptout = hu_get("http_tout");
    int i;

    i = atoi(ptout);
    free(ptout);

    return i;
}

static void refresh_or_add_user(char *ips)
{
	struct sysinfo info;
	char timeout[16] = {0};
	char *p = hu_get(ips);
	int tout = get_http_tout();

	sysinfo(&info);

    if((*p == '0'))
        syslog(LOG_INFO, "[System] User '%s' logged in successfully from %s.", digest_value_db[DI_USERNAME], remote_ip);

	if((*p == '0')
	    || ((atol(p) > info.uptime)
	        && (atol(p) < info.uptime + tout)))
    {
    	sprintf(timeout, "%lu", info.uptime + tout);
    	hu_set(ips, timeout);
    }

	free(p);
}

static int is_user_need_login(char *ips)
{
	struct sysinfo info;
	int ret = 1;
	char *p;

	sysinfo(&info);
	p = hu_get(ips);

	if(*p && (atol(p) > info.uptime))
	    ret = 0;

    free(p);
	return ret;
}

static void user_need_login(char *ips)
{
	hu_set(ips, "");
}

void set_auth_flag(char *ips)
{
	hu_set(ips, "0");
}

static int get_auth_flag(char *ips)
{
    int ret = 0;
    char *p = hu_get(ips);

    if(*p == '0')
        ret = 1;

	free(p);

	return ret;
}

void handle_chdir( int sig )
{
    chdir(rondir?:"/www");    
    (void) getcwd( cwd, sizeof(cwd) - 1 );
    if ( cwd[strlen( cwd ) - 1] != '/' )
	(void) strcat( cwd, "/" );
}

void handle_logout( int sig )
{
	user_need_login(remote_ip);
}

static int name_cmp(char *s1, char *s2)
{
    char c1, c2;

    if(strlen(s1) == strlen(s2))
    {
        while(*s1)
        {
            if((*s1 >= 'A') && (*s1 <= 'Z'))
                c1 = 'a' + (*s1 - 'A');
            else
                c1 = *s1;

            if((*s2 >= 'A') && (*s2 <= 'Z'))
                c2 = 'a' + (*s2 - 'A');
            else
                c2 = *s2;

            if(c1 != c2)
                return 0;

            s1++;
            s2++;
        }
    }
    else
    {
        return 0;
    }

    return 1;
}

extern int auth_type;
static struct passwd *is_pwd_ok(char *uname, char *pwd)
{
    print2console("<%s %d>uname=%s pwd=%s\n", __func__, __LINE__, uname, pwd);
    int authcheck = 0;
    int i = 0;
    struct passwd* pw = NULL;

#if 0
    pw = cal_UA_getpwnam(HTTP_PASSWD_FILE, uname);
    if(!pw)
#endif       
        return NULL;

    if(auth_type == BASIC_AUTH_TYPE)
    {
        if(!strcmp(pw->pw_passwd, pwd))
        {
            authcheck = 1;
        }
    }
    else
    {
        authcheck = 1;
    }

    if(authcheck != 1)
    {
        if(*uname==0)
            syslog(LOG_INFO, "[System] User login failed from %s.", remote_ip);
        else if(strcmp(uname, "test"))
            syslog(LOG_INFO, "[System] User '%s' login failed from %s.", uname, remote_ip);
        print2console("[%s]ret=0\n", __FUNCTION__);            
        return NULL;
    }
    
    print2console("[%s]ret=1\n", __FUNCTION__);
    return pw;
}

extern char *http_realm;
extern char* file;
extern int method;
extern METHOD_POST;
extern char* request;
extern size_t request_size, request_len, request_idx;
extern char* authorization;

#ifndef METHOD_POST
#define METHOD_POST 3
#endif

void
auth_check( char* dirname )
{
    char authpath[10000];
    struct stat sb;
    char authinfo[500];
    char* authpass;
    char* colon;
    static char line[10000];
    int l;
    FILE* fp;
    char* cryp;

#ifndef _SC_BUILD_
    /* Construct auth filename. */
    if ( dirname[strlen(dirname) - 1] == '/' )
	(void) snprintf( authpath, sizeof(authpath), "%s%s", dirname, AUTH_FILE );
    else
	(void) snprintf( authpath, sizeof(authpath), "%s/%s", dirname, AUTH_FILE );

    /* Does this directory have an auth file? */
    if ( stat( authpath, &sb ) < 0 ){
	/* Ron */
	/* Nope, let the request go through. */
	return;
    }
#endif

    not_auth=0;

    /* these files not need auth check */
    if(file
        && (strstr(file, ".jpg")
            || strstr(file, ".JPG")
            || strstr(file, ".bmp")
            || strstr(file, ".png")
            || strstr(file, ".css")
            || strstr(file, ".gif")
            || strstr(file, ".js")))
        return;

    /* process user click 'cancel' when he is asked to input password */
    if((method == METHOD_POST)
        && get_auth_flag(remote_ip)
        && (strstr(&request[request_idx], "todo=timeout")))
    {
        user_need_login(remote_ip);
        send_error( 403, "Forbidden", "", "File is protected." );
        return;
    }

    /* Does this request contain authorization info? */
    if ( authorization == (char*) 0 ){
//        if(is_user_need_login(remote_ip))
//        {print2console("<%s %d>\n", __func__, __LINE__);
            not_auth=1;
        	/* Nope, return a 401 Unauthorized. */
        	send_authenticate(dirname);
//        }
//        else
//        {
//            print2console("<%s %d>\n", __func__, __LINE__);
//            refresh_or_add_user(remote_ip);
//            return;
//        }
    }

    /* Basic authorization info? */
    if ( strncmp( authorization, "Basic ", 6 ) != 0 ){
	send_authenticate(dirname);
    }

    /* Decode it. */
    l = b64_decode(
	&(authorization[6]), (unsigned char*) authinfo, sizeof(authinfo) - 1 );
    authinfo[l] = '\0';
    /* Split into user and password. */
    authpass = strchr( authinfo, ':' );
    if ( authpass == (char*) 0 )
	/* No colon?  Bogus auth info. */
	send_authenticate(dirname);
    *authpass++ = '\0';
    /* If there are more fields, cut them off. */
    colon = strchr( authpass, ':' );
    if ( colon != (char*) 0 )
	*colon = '\0';

#ifdef _SC_BUILD_
    struct passwd *pw;
    pw = is_pwd_ok(authinfo, authpass);
    if(!pw)
    {
        not_auth = 1;
        syslog(LOG_INFO, "One user login fail - IP:%s", remote_ip);
        send_authenticate(dirname);
    }
    else
    {
        if(is_user_need_login(remote_ip)
                && (!get_auth_flag(remote_ip)))
        {
            not_auth = 1;
            send_authenticate(dirname);
        }
        else
        {
            /*Pass authentication, check permission to request file*/
            /*Denny Zhang, Wed Jan  4 10:02:24 CST 2012*/
            refresh_or_add_user(remote_ip);
        }
        return;
    }

#else
    /* Open the password file. */
    fp = fopen( authpath, "r" );
    if ( fp == (FILE*) 0 )
	{
	/* The file exists but we can't open it?  Disallow access. */
#ifdef SYSLOG
	syslog(
	    LOG_ERR, "%.80s auth file %.80s could not be opened - %m",
	    ntoa( &client_addr ), authpath );
#endif
	send_error( 403, "Forbidden", "", "File is protected." );
	}

    /* Read it. */
    while ( fgets( line, sizeof(line), fp ) != (char*) 0 )
	{
    	/* Nuke newline. */
    	l = strlen( line );
    	if ( line[l - 1] == '\n' )
    	    line[l - 1] = '\0';
    	/* Split into user and encrypted password. */
    	cryp = strchr( line, ':' );
    	if ( cryp == (char*) 0 )
    	    continue;
    	*cryp++ = '\0';
    	/* Is this the right user? */
    	if ( strcmp( line, authinfo ) == 0 )
        {
    		    struct sysinfo info;
    		    sysinfo(&info);
    	    /* Yes. */
    	    (void) fclose( fp );
    	    /* So is the password right? */
    /*Ron*/
        	/* OK !*/
        	if ( strcmp(authpass, cryp ) == 0){
        	    if(is_user_need_login(remote_ip)
        	        && (!get_auth_flag(remote_ip)))
                {
                    send_authenticate(dirname);
                }
                else
                {
                    refresh_or_add_user(remote_ip);
                }

        		remoteuser = line;
        		return;
        	}else{
        		/* No. */
            	not_auth=1;
            	syslog(LOG_INFO, "One user login fail - IP:%s", remote_ip);
        		send_authenticate(dirname);
        	}
        }
	}
#endif

    /* Didn't find that user.  Access denied. */
    (void) fclose( fp );
    send_authenticate(dirname);
}

/*********************************************************************************************/
/************************Implemented for Digest **********************************************/
static long Time_Get()
{
    struct sysinfo info;
	  sysinfo(&info);
	  return info.uptime;
}
static VOID CvtHex(HASH Bin,HASHHEX Hex)
{
    WORD i;
    BYTE j;
    for (i = 0; i < HASHLEN; i++) {
        j = (Bin[i] >> 4) & 0xf;
        if (j <= 9)
            Hex[i*2] = (j + '0');
         else
            Hex[i*2] = (j + 'a' - 10);
        j = Bin[i] & 0xf;
        if (j <= 9)
            Hex[i*2+1] = (j + '0');
         else
            Hex[i*2+1] = (j + 'a' - 10);
    }
    Hex[HASHHEXLEN] = '\0';
}

/*calculate A1, which used by digest*/
static VOID DigestCalcHA1(CHAR *psAlg,CHAR *psUserName,CHAR *psRealm,CHAR *psPassword,
		CHAR *psNonce,CHAR *psCNonce,HASHHEX SessionKey)
{
	  MD5_CTX Md5Ctx;
  	HASH HA1;
    memset(HA1, 0, sizeof(HA1));
  	MD5_Init(&Md5Ctx);
  	MD5_Update(&Md5Ctx, psUserName, strlen(psUserName));
  	MD5_Update(&Md5Ctx, ":", 1);
  	MD5_Update(&Md5Ctx, psRealm, strlen(psRealm));
  	MD5_Update(&Md5Ctx, ":", 1);
  	MD5_Update(&Md5Ctx, psPassword, strlen(psPassword));
  	MD5_Final((unsigned char *)HA1, &Md5Ctx);
  	if (strcasecmp(psAlg, "md5-sess") == 0)
  	{
	      MD5_Init(&Md5Ctx);
        MD5_Update(&Md5Ctx, HA1, HASHLEN);
        MD5_Update(&Md5Ctx, ":", 1);
        MD5_Update(&Md5Ctx, psNonce, strlen(psNonce));
        MD5_Update(&Md5Ctx, ":", 1);
        MD5_Update(&Md5Ctx, psCNonce, strlen(psCNonce));
        MD5_Final((unsigned char *)HA1, &Md5Ctx);
  	}
  	CvtHex(HA1, SessionKey);
}

/* calculate request-digest/response-digest as per HTTP Digest spec */
static VOID DigestCalcResponse(
    HASHHEX HA1,           /* H(A1) */
    CHAR * psNonce,       /* nonce from server */
    CHAR * psNonceCount,  /* 8 hex digits */
    CHAR * psCNonce,      /* client nonce */
    CHAR * psQop,         /* qop-value: "", "auth", "auth-int" */
    CHAR * psMethod,      /* method from the request */
    CHAR * psDigestUri,   /* requested URL */
    HASHHEX HEntity,       /* H(entity body) if qop="auth-int" */
    HASHHEX Response      /* request-digest or response-digest */
    )
{
      MD5_CTX Md5Ctx;
      HASH HA2;
      HASH RespHash;
       HASHHEX HA2Hex;

      // calculate H(A2)
      MD5_Init(&Md5Ctx);
      MD5_Update(&Md5Ctx, psMethod, strlen(psMethod));
      MD5_Update(&Md5Ctx, ":", 1);
      MD5_Update(&Md5Ctx, psDigestUri, strlen(psDigestUri));
      if (psQop && strcasecmp(psQop, "auth-int") == 0) {
            MD5_Update(&Md5Ctx, ":", 1);
            MD5_Update(&Md5Ctx, HEntity, HASHHEXLEN);
      };
      MD5_Final((unsigned char *)HA2, &Md5Ctx);
      CvtHex(HA2, HA2Hex);

      // calculate response
      MD5_Init(&Md5Ctx);
      MD5_Update(&Md5Ctx, HA1, HASHHEXLEN);
      MD5_Update(&Md5Ctx, ":", 1);
      MD5_Update(&Md5Ctx, psNonce, strlen(psNonce));
      MD5_Update(&Md5Ctx, ":", 1);
      if (*psQop) {
			MD5_Update(&Md5Ctx, psNonceCount, strlen(psNonceCount));
          MD5_Update(&Md5Ctx, ":", 1);
          MD5_Update(&Md5Ctx, psCNonce, strlen(psCNonce));
          MD5_Update(&Md5Ctx, ":", 1);
          MD5_Update(&Md5Ctx, psQop, strlen(psQop));
          MD5_Update(&Md5Ctx, ":", 1);
      };
      MD5_Update(&Md5Ctx, HA2Hex, HASHHEXLEN);
      MD5_Final((unsigned char *)RespHash, &Md5Ctx);
      CvtHex(RespHash, Response);
}

static VOID NonceStr(CHAR *OutNonce)
{
	  MD5_CTX Md5Ctx;
    CHAR tmpNonce[16],Source[16];

    sprintf(Source,"%lx",SYSTIME);
    MD5_Init(&Md5Ctx);
    MD5_Update(&Md5Ctx, Source, strlen(Source));
    MD5_Update(&Md5Ctx, ":", 1);

    sprintf(&Source[8],"%lx",SYSTIME);
    MD5_Update(&Md5Ctx, &Source[8], strlen(&Source[8]));
    MD5_Final((unsigned char *)tmpNonce, &Md5Ctx);
    CvtHex(tmpNonce, OutNonce);
}

static INT16 is_string_end(CHAR c)
{
	return (c=='\0'||c==' '||c=='\''||c=='\"'||c==',')?1:0;
}
static INT16 CheckDigest(VOID)
{
    char basic_realm[10] = {0};
  
    //get_module_number(basic_realm,sizeof(basic_realm));
	if(http_realm==NULL)
	    http_realm=basic_realm;
    print2console("[%s]http_realm=<%s>\n", __FUNCTION__, http_realm ? : "");	
    dump_digest_value_db();            
	if(/*strcmp(digest_value_db[DI_REALM],http_realm)==0
	&&*/(digest_value_db[DI_ALGORITHM][0] == '\0' || strcasecmp(digest_value_db[DI_ALGORITHM],"md5")==0||strcasecmp(digest_value_db[DI_ALGORITHM],"md5-sess")==0)
	&&digest_value_db[DI_OPAQUE][0]==0)
	{
		return 1;
  }
	return 0;
}

static INT16 save_digest(CHAR *name, CHAR *value)
{
	INT16 i, len;
//	if(!name||!value||!*name||!*value)
	if(!name||!*name)
		return 0;
	for(i=0;i<DI_NONE;i++)
		if(!strcasecmp(digest_str_db[i],name))
			{
			  len = strlen(value);
			  len = len>MAX_URL_STRING_LENGTH?MAX_URL_STRING_LENGTH:len;
				strncpy(digest_value_db[i],value,len);
				digest_value_db[i][len]='\0';
				return 1;
			}
	return 0;
}
static VOID ReadDigest(CHAR *auth_str)
{
	CHAR *p,*q,*name,*value, *ptr;
	if(auth_str==NULL)
		return;

	memset(digest_value_db,0,sizeof(digest_value_db));
	q=auth_str;
	for(;*q;)
	{
		name=q;
		if((value=strchr(name,'=')))
			*value++='\0';
		else
			return;

		if(*value == '\"' && *(value+1) != '\"')
    {
        while(is_string_end(*value))
        {
            *value++='\0';
        }
    }

		if((p=strchr(value,',')))
		{
			if(*(p-1)=='\"')
				*(p-1)='\0';
			while(is_string_end(*p))
				*p++='\0';
			q=p;
		}
		ptr = value;
    while(!is_string_end(*ptr))
        ptr++;
    if(is_string_end(*ptr))
        *ptr = '\0';
		if(!save_digest(name,value))
			return;

		if(!p)*q='\0';
	}
}

CHAR *ServerNotAuth(VOID)
{
	static CHAR Realm[500];
	static CHAR nonce[HASHHEXLEN+1];
	char basic_realm[10] = {0};
	
	//get_module_number(basic_realm,sizeof(basic_realm));
	if(http_realm==NULL)
	    http_realm=basic_realm;

	memset(Realm,'\0',500);
	strcpy(Realm,"qop=\"auth\", ");
	strcat(Realm,"realm=\"");
	strcat(Realm,http_realm);
	strcat(Realm,"\", ");
	strcat(Realm,"algorithm=\"md5\", ");
	NonceStr(nonce);
	nonce[HASHHEXLEN]='\0';
	strcat(Realm,"nonce=\"");
	strcat(Realm,nonce);
	strcat(Realm,"\"");
	return Realm;
}
/* may be used when block the attack*/
/*static CHAR *ServerInfo()
{
	static CHAR Realm[500];
	static CHAR nonce[HASHHEXLEN+1];

	memset(Realm,'\0',sizeof(Realm));
	NonceStr(nonce);
	print2console("<%s %d>nonce=%s\n", __func__, __LINE__, nonce);
	nonce[HASHHEXLEN]='\0';
//	strcpy(all_nonces[0].nextnonce,nonce);//store nextnonce

	strcpy(Realm,"nextnonce=\"");
	strcat(Realm,nonce);
	strcat(Realm,"\", qop=\"auth\", ");
	strcat(Realm,"cnonce=\"");
	strcat(Realm,digest_value_db[DI_CNONCE]);
	strcat(Realm,"\", nc=");
	strcat(Realm,digest_value_db[DI_NC]);
	strcat(Realm,", rspauth=\"");
	strcat(Realm,digest_value_db[DI_RESPONSE]);
	strcat(Realm,"\"");
	return Realm;
}*/
INT16 char2hex(CHAR * str, BYTE len, INT32 * value)
{
	CHAR ch;
	BYTE i;
	INT32 result=0;

	for(i=0;(i<len)&&(str[i]);i++) {
		if(str[i]==' ') continue;
		result *= 16;
		ch = str[i];
		if((ch<='9') && (ch>='0')) result += (INT32)ch - '0';
		else if((ch<='F') && (ch>='A')) result += (INT32)ch - 'A' + 10;
		else if((ch<='f') && (ch>='a')) result += (INT32)ch - 'a' + 10;
		else return -1;
	}
	*value = result;

	return 0;
}

void digest_auth_check( char* dirname )
{
    if(file && (strstr(file, ".jpg")
            || strstr(file, ".JPG")
            || strstr(file, ".bmp")
            || strstr(file, ".png")
            || strstr(file, ".css")
            || strstr(file, ".gif")
            || strstr(file, ".js")))
        return;

    /* process user click 'cancel' when he is asked to input password */
    if((method == METHOD_POST)
        && get_auth_flag(remote_ip)
        && (strstr(&request[request_idx], "todo=timeout")))
    {
        user_need_login(remote_ip);
        send_error( 403, "Forbidden", "", "File is protected." );
        return;
    }
    if ( authorization == (char*) 0 ){
        not_auth=1;
        send_authenticate(dirname);
    }
    if( strncmp( authorization, "Digest ", 7 ) != 0 ){
	        send_authenticate(dirname);
    }
    char *authinfo = authorization;
    int ret = 0;
    authinfo = authinfo+strlen("Digest ");
    ReadDigest(authinfo);
    HASHHEX HA1;
    HASHHEX HA2 = "";
    HASHHEX Response;
    DWORD nc_value;
    struct passwd *pw;
    pw = is_pwd_ok(digest_value_db[DI_USERNAME], "");
    if(!pw)
    {
        not_auth = 1;
        syslog(LOG_INFO, "One user login fail - IP:%s", remote_ip);
        send_authenticate(dirname);
        return;
    }
    else
    {
        if(is_user_need_login(remote_ip)
	        && (!get_auth_flag(remote_ip)))
        {
            not_auth = 1;
           send_authenticate(dirname);
        }
    }
    if(CheckDigest())
    {
        DigestCalcHA1(
    		  (*digest_value_db[DI_ALGORITHM]==0)?md5_string:digest_value_db[DI_ALGORITHM],
	  		  digest_value_db[DI_USERNAME],
              digest_value_db[DI_REALM],
              pw->pw_passwd,
    		  digest_value_db[DI_NONCE],
    		  digest_value_db[DI_CNONCE],
    		  HA1);
	      DigestCalcResponse(HA1,
    			digest_value_db[DI_NONCE],
    			digest_value_db[DI_NC],
    			digest_value_db[DI_CNONCE],
	    		digest_value_db[DI_QOP],
    			method==METHOD_POST?"POST":"GET",
    			digest_value_db[DI_URI],
    			HA2,
	    		Response);
	    print2console("<%s %d>URI=%s DI_RESPONSE=%s  response=%s", __func__, __LINE__, digest_value_db[DI_URI], digest_value_db[DI_RESPONSE], Response);
    	char2hex(digest_value_db[DI_NC],strlen(digest_value_db[DI_NC]),&nc_value);
	  	{
 	  	  if(memcmp(Response,digest_value_db[DI_RESPONSE],HASHLEN)==0)
    		{
                hu_set("LOGIN_USERNAME", digest_value_db[DI_USERNAME]);  
                remoteuser = digest_value_db[DI_USERNAME];
                print2console("<%s %d>Authentication success", __func__, __LINE__);
                /*Pass authentication, check permission to request file*/
                /*Denny Zhang, Wed Jan  4 10:02:24 CST 2012*/

                refresh_or_add_user(remote_ip);
                return ;
            }
            else
            {
                print2console("<%s %d>Authentication fail", __func__, __LINE__);
                if(strcmp(digest_value_db[DI_USERNAME], "test"))
                    syslog(LOG_INFO, "[System] User '%s' login failed from %s.", digest_value_db[DI_USERNAME], remote_ip);
                send_authenticate(dirname);
            }
        }
    }
    else
    {
        not_auth = 1;
        print2console("<%s %d>Authentication fail", __func__, __LINE__);
        syslog(LOG_INFO, "One user login fail - IP:%s", remote_ip);
        send_authenticate(dirname);
    }
}
/********************************End Implemented for Digest ***********************************/

