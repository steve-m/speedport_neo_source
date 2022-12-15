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
#include "utility.h"

#ifndef AUTH_FILE
#define AUTH_FILE ".htpasswd"
#endif /* AUTH_FILE */

extern SAVETIME;

extern char* remoteuser;
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
extern void send_return(int type);

static int flag_login=1;
static int still_timeout=0;

#define LOGIN_NAME  "LoginName="
#define LOGIN_PWD   "LoginPWD="
#define SPILT       ";"
#define MAX_SIZE    500

void handle_chdir( int sig )
{
    chdir(rondir?:"/www");    
    (void) getcwd( cwd, sizeof(cwd) - 1 );
    if ( cwd[strlen( cwd ) - 1] != '/' )
	(void) strcat( cwd, "/" );
}

void handle_logout( int sig )
{
	/* logout */
	last_access_time=0;
	still_timeout=0;
	flag_login=1;
}

static int get_name_pwd(char *pwd,char *name)
{
    /* to support safari 5.0 for mac os , the cookie will be "LoginPWD=..., LoginName=..." */
    /* the code should not be bound by the order of  LoginPWD and LoginName */
    
    char *p1=NULL, *p2=NULL, *tmp=NULL;
    char *cookie1 = NULL;
    int l=0;
    
    if (cookie == (char*)0)
        return 0;
    
    cookie1 = strdup(cookie);
    if (cookie1 == NULL)
        return 0;
        
    p1 = strstr(cookie1, LOGIN_NAME);
    p2 = strstr(cookie1, LOGIN_PWD);
    if ( (p1 == NULL) || (p2 == NULL))
    {
        free(cookie1);
        return 0;
    }
    
    tmp = strstr(p1, SPILT);
    if (tmp)
        *tmp = '\0';
    tmp = strstr(p2, SPILT);
    if (tmp)
        *tmp = '\0';
    p1 += strlen(LOGIN_NAME);
    p2 += strlen(LOGIN_PWD);
    
    nsldapi_hex_unescape(p1);
	l = b64_decode(p1, (unsigned char*) name, MAX_SIZE-1 );
    nsldapi_hex_unescape(p2);
	l = b64_decode(p2, (unsigned char*) pwd, MAX_SIZE-1 );

    free(cookie1);
    
    return 1;
}

int check_timeout(void)
{
	struct sysinfo info;
	sysinfo(&info);

	if(strcmp(last_remote_ip,remote_ip)==0 && still_timeout==1){
		usleep(1);
		return 1;
	}
	
	if(last_access_time==0){
		usleep(1);
		return 0;
	}
	else if(((info.uptime-last_access_time)>web_timeout) && web_timeout!=0)
	{
		usleep(1);
		return 1;
	}
	return 0;
}

/*
 * needPassword() -- check if user need input password.
 *
 *      1 ==> Yes, you need input password.
 *      0 ==> No. no need password input.
 */
static int needPassword(char *authpath, char *line) 
{
    FILE *fp ;
    int l;
    char cryp[500] = "";

    if(!authpath) {
        /* no authpath, ofcourse no need password */
        return 0;
    }

    fp = fopen(authpath, "r");
    if(!fp) {
        /* no authpath, ofcourse no need password */
        return 0;
    }

    while ( fgets( line, sizeof(line), fp ) != (char*) 0 ) {
        /* Nuke newline. */
        l = strlen( line );
        if(l > 0)
        {
            while(fgets(cryp, sizeof(cryp), fp) != (char*) 0)
                if(strlen(cryp) > 0)
                {
                    fclose(fp);
                    return 1;
                }
        }
    }
    fclose(fp);
    return 0;
}

void auth_check( char* dirname )
{
    static char line[512];    
    struct passwd *pw;
	char pwd[64],name[64];
	char *cryp;
	struct stat sb;
	int l;

	if(query && strstr(query, "next_file=common/system.xml")==query){
		return;
	}

	/* Does this directory have an auth file? or no need input password*/
    if (!needPassword(authpath, line) )
    {
        /* Ron */
        if(strcmp(last_remote_ip,remote_ip)!=0){
            syslog(LOG_INFO,"[SC][AuthLogin]Authorized Login from %s on Web",remote_ip);
            SAVETIME;
        }else if(check_timeout())
            //LOGOUT;
        {
            send_return(1);
            syslog(LOG_INFO,"[SC][AuthLogin]Authorized Login timeout on Web");
            // send_authenticateTimeout( dirname );
        }
        else
            SAVETIME;
        /* Ron */
        /* Nope, let the request go through. */
        return;
    }
	not_auth=0;
	memset(name,0,sizeof(name));
	memset(pwd,0,sizeof(pwd));

	if(get_name_pwd(pwd,name)==0)
	{
		not_auth=1;
		if(check_timeout()) {
		    char *p;
		    FILE *fp = NULL;
		    p=strstr(query,"next_file=");
		    
		    if(p){
		    	p=p+10;
		    	if(p){
		    		fp = fopen("/tmp/nextpage", "w");
		    		if(fp)
		    		{
		    			if(strstr(p,"h_")){
      	     						p=p+2;
      	     			}
		    			if(p){
		    					fputs(p,fp);
		    			}
		    			fclose(fp);
		    		}
		    	}
		    }
            syslog(LOG_INFO,"[SC][AuthLogin]Authorized Login timeout on Web");
		    send_return(1);
		}
		send_return(0);
    }
    pw = cal_UA_getpwnam(HTTP_PASSWD_FILE, name);
    
    if(pw)
    {
        char *key;

        /* So is the password right? */
        key = crypt(pwd, SC_CRYPT_SALT);
        if ( strcmp(key, pw->pw_passwd) == 0 )
        {
            if(flag_login==1)
            {
                syslog(LOG_INFO, "[System] User '%s' login successfully from %s.", name, remote_ip);
                flag_login=0;
            }
            if((strcmp(last_remote_ip,remote_ip)!=0)){
                ;
                /* Mike@CPU_AP add for send syslog */
                //mBUG("<%s,%d>:authlogin", __FUNCTION__, __LINE__);
                //		syslog(LOG_INFO,"[SC][AuthLogin]Authorized Login from %s",remote_ip);
                /* add end */
                /* if different user must authentication in frist time */
                //		if (last_remote_ip[0]!=0)
                //			send_return(0);
                /*Time out */
            }else if(check_timeout()) {
                syslog(LOG_INFO,"[SC][AuthLogin]Authorized Login timeout on Web");
                char *p;
                FILE *fp = NULL;
                p=strstr(query,"next_file=");

                if(p){
                    p=p+10;
                    if(p){
                        fp = fopen("/tmp/nextpage", "w");
                        if(fp)
                        {
                            if(strstr(p,"h_")){
                                p=p+2;
                            }
                            if(p){
                                fputs(p,fp);
                            }
                            fclose(fp);
                        }
                    }
                }
                send_return(1);
                // send_authenticateTimeout( dirname );
            }
            if(strstr(query,"login.htm")){
                if(access("/tmp/nextpage", A_OK) == 0){
                    send_return(3);
                }
            }
            remoteuser = line;
            //	LOGOUT;
            SAVETIME;
            return;
        }
        else
        {
            syslog(LOG_INFO, "[System] User '%s' login failed from %s.", name, remote_ip);
        }
    }
    not_auth=1;
    syslog(LOG_INFO,"[SC][UnAuthLogin]Unauthorized Login Attempt from %s on Web",remote_ip);
    send_return(0);
    //send_authenticateTimeout( dirname );
}
