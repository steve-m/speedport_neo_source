/*
 *****************************************************************
 *                                                               *
 *    Copyright (c) DynIP,  a division of                        *
 *    CanWeb Internet Services Ltd., 1997-1998                   *
 *								 *
 * Redistribution and use in source and binary forms, with or	 * 
 * without modification, are permitted provided that the 	 *
 * following conditions are met:				 *
 *								 *
 * 1. Redistributions of source code must retain the above	 * 
 *    copyright notice, this list of conditions and the 	 *
 *    following disclaimer.					 *
 *								 *
 * 2. Redistributions in binary form must reproduce the above 	 *
 *    copyright notice, this list of conditions and the 	 *
 *    following disclaimer in the documentation and/or other 	 *
 *    materials provided with the distribution.			 *
 *								 *
 * 3. All advertising materials mentioning features or use of 	 *
 *    this software must display the following acknowledgement:	 *
 *								 *
 *    ``This product includes software developed by CanWeb	 *
 *      Internet Services Ltd.''				 *
 *								 *
 * 4. Neither CanWeb Internet Services Ltd., DynIP,              *
 *    or the developers of this software product may be used     *
 *    to endorse or promote products derived from this           *
 *    software without specific prior written permission.	 *
 *								 *
 * THIS SOFTWARE IS PROVIDED BY CANWEB INTERNET SERVICES LTD.	 *
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, 	 *
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY *
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO 	 *
 * EVENT SHALL CANWEB INTERNET SERVICES LTD. BE LIABLE FOR ANY 	 *
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 	 *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 	 *
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 	 *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 	 *
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT	 *
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING*
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF*
 * THE POSSIBILITY OF SUCH DAMAGE.				 *
 *								 *
 *****************************************************************
 */

#include "log.h"
#include <unistd.h>
#include <syslog.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "dynipgbl.h"

static int  iOptions, iLastError, iInitialize = 0;
static char achProgram[MODLOG_MAXTEMP];

int logOpen(char *pArgv, int options)
{
char	*pProgName;

if (iInitialize)
	return (iLastError = MODLOG_ERROR_INIT);

iOptions = options;

if ((pProgName = strrchr(pArgv, '/')) != NULL)
       	pProgName++;
else	pProgName = &pArgv[0];

if (iOptions & MODLOG_OPTION_SYSLOG)
	openlog(pProgName, LOG_PID, LOG_ERR);

sprintf(achProgram,"%s[%d]: ", pProgName, getpid());

iInitialize = 1;
return (iLastError = MODLOG_ERROR_NONE);
}

int logClose(void)
{
if (!iInitialize)
	return (iLastError = MODLOG_ERROR_INIT);

if (iOptions & MODLOG_OPTION_SYSLOG)
	closelog();

iInitialize = 0;
return (iLastError = MODLOG_ERROR_NONE);
}

int logWrite(char *pString, ...)
{
va_list va;
char    achBuffer[MODLOG_MAXBUFFER];

if (!iInitialize)
	return (iLastError = MODLOG_ERROR_INIT);

va_start(va, pString);

vsprintf(achBuffer, pString, va);

va_end(va);

if (iOptions & MODLOG_OPTION_TTY)
        printf("%s%s", achProgram,achBuffer);

if (iOptions & MODLOG_OPTION_SYSLOG)
	syslog(LOG_ERR,achBuffer);

return (iLastError = MODLOG_ERROR_NONE);
}

int logGetLastError(void)
{
int	iError;

iError 		= iLastError;
iLastError 	= MODLOG_ERROR_NONE;

return (iError);
}

int logSetLastError(int iError)
{
iLastError = iError;

return (MODLOG_ERROR_NONE);
}

void show_my_message(int code)
{
  FILE *fp;
  char buf[16] = "";

  sprintf(buf,"%d\n",code);

  fp=fopen(DDNS_UPDATE_LOG,"w");
  if(fp){
  	fputs(buf,fp);
	fclose(fp);
  }
  openlog( "syslog", 0 , LOG_SYSLOG );
  switch(code){
	 case ERR_NO_MESSAGE:
  		syslog(LOG_NOTICE,"(DDNS)No message.");
		break;
	 case ERR_FIELDS_MUST_EMPTY:
  		syslog(LOG_NOTICE,"(DDNS)These fields must not be empty");
		break;
	 case ERR_IP_SAME:
  		syslog(LOG_NOTICE,"(DDNS)IP address is the same, and does not need to be updated!");
		break;
	 case ERR_SETTING_NULL:
  		syslog(LOG_NOTICE,"(DDNS)one NULL in username password or hostname");
		break;
	 case ERR_DNS_QUERY_ERROR:
  		syslog(LOG_NOTICE,"(DDNS)DNS query error");
		break;
	 case ERR_DNS_SERVER_ERROR:
  		syslog(LOG_NOTICE,"(DDNS)DNS server error");
		break;
	 case ERR_INTERNET_ERROR:
  		syslog(LOG_NOTICE,"(DDNS)No DNS server response or Internet can't connect");
		break;
	 case ERR_HTTP_ERROR:
  		syslog(LOG_NOTICE,"(DDNS)HTTP cannot connected");
		break;
	 case ERR_USER_PSWD_ERROR:
  		syslog(LOG_NOTICE,"(DDNS)Username or password error");
		break;
	 case ERR_UPGRADE_OK:
     case ERR_NO_ERROR:
  		syslog(LOG_NOTICE,"(DDNS)Update OK: good");
		break;
     case ERR_WAIT:
//  		syslog(LOG_NOTICE,"(DDNS)Please wait");
		break;
     case ERR_DOMAIN_NAME_NOT_QUALIFY:
  		syslog(LOG_NOTICE,"(DDNS)Not Fully Qualified Domain Name: notfqdn");
		break;
     case ERR_HOST_NOT_EXIST:
  		syslog(LOG_NOTICE,"(DDNS)The host doesn't exist: nohost");
		break;
     case ERR_HOST_NOT_SUPPORT:
  		syslog(LOG_NOTICE,"(DDNS)The host is not managed by you");
		break;
	 case ERR_ABUSE:
  		syslog(LOG_NOTICE,"(DDNS)Blocked due to abuse: abuse");
		break;
	 case ERR_SERVER_HOST_FULL:
  		syslog(LOG_NOTICE,"(DDNS)DynDNS server error:numhost");
		break;
  	 case ERR_SERVICE_DOWN:
  		syslog(LOG_NOTICE,"(DDNS)Service has been shut down");
		break;
	 case ERR_UNKNOWN_CODE:
  		syslog(LOG_NOTICE,"(DDNS)Unknown return code received!");
		break;
	 default:
	 case ERR_UNKNOWN_ERROR:
  		syslog(LOG_NOTICE,"(DDNS)Unknown error occurred!");
		break;
	 case ERR_HTTP_SOCKET:
  		syslog(LOG_NOTICE,"(DDNS)Can't open HTTP socket");
		break;
	 case ERR_WAN_IP_NULL:
  		syslog(LOG_NOTICE,"(DDNS)WAN IP address is NULL");
		break;
	 case ERR_DOMAIN_NAME_INVALID:
  		syslog(LOG_NOTICE,"(DDNS)Domain Name is invalid");
		break;
	 case ERR_KEY_INVALID:
  		syslog(LOG_NOTICE,"(DDNS)Registration Key is invalid");
		break;
	 case ERR_INTERNAL_ERROR:
  		syslog(LOG_NOTICE,"(DDNS)Dynip server or client internal error");
		break;
  }
  closelog();
}
