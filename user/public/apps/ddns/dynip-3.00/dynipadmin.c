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

/*
 *	@(#)dynipadmin.c	3.0 (CanWeb) 24/7/97		 *
 *	$Id: dynipadmin.c,v 3.00 1998/04/02 12:01:44 $	 	 *  
 */

/*

	rev	who			what

	3.00	stephan@canweb.ca	Removed portmap feature

                                        Added caching of primary DDNS
                                        server.

					Improved option argument scanning					

	2.01	stephan@canweb.ca	Look for configuration files
					in user specified directory.


	2.0b5	stephan@canweb.ca	first version to keep track
					of changes!

*/

#include "dynipgbl.h"
#include "prof.h"
#include "opt.h"
#include "dynipadmin.h"
#include "log.h"

#ifndef lint
static char copyright[]="@(#) Copyright (c) 1998\n\
	CanWeb Internet Services Ltd. All Rights Reserved.\n";
static char sccsid[] = "@(#)dynipadmin.c    3.00 (CanWeb) 02/04/98";
#endif

static char achHeader[]={
"DynIP(sm) Domain Administration Client V3.00\n\
DynIP, a division of CanWeb Internet Services Ltd.\n\
Copyright (C) 1997-1998, All Rights Reserved.\n\
This program may be freely copied and distributed.\n\
NO WARRANTY of any kind; see man pages for additional details.\n"
};

static char dynip_hostname[64] = "";

void show_request_error(int code)
{
	switch (code)
	{
		case REQ_NOHOST:
            show_my_message(ERR_DOMAIN_NAME_INVALID);
			break;

		case REQ_NOHOSTENTRY:
		case REQ_SOCKETERROR:
		case REQ_CONNECTERROR:
		case REQ_SENDERROR:
            show_my_message(ERR_INTERNET_ERROR);
			break;

        case REQ_OK:
            break;

		default:
            show_my_message(ERR_UNKNOWN_ERROR);
			break;
	}
}

void show_response_error(int code)
{
    switch (code)
	{
    	case DYNIP_RESPONSE_HOSTNAME_REGISTERED: // action succesful
    	case DYNIP_RESPONSE_HOSTNAME_REMOVED:
    	case DYNIP_RESPONSE_REFRESH:
    		show_my_message(ERR_UPGRADE_OK);
    		break;
    
    	case DYNIP_RESPONSE_HOSTNAME_RESERVED: // hostname or domain name error
    	case DYNIP_RESPONSE_HOSTNAME_INUSE:
        case DYNIP_RESPONSE_INVALID_DOMAIN:
        case DYNIP_RESPONSE_INVALID_NAME:
            show_my_message(ERR_DOMAIN_NAME_INVALID);
    		break;
    
    	case DYNIP_RESPONSE_PERIOD_EXPIRED: // registration key error
    	case DYNIP_RESPONSE_ALREADY_REGISTERED:
        case DYNIP_RESPONSE_NOT_REGISTERED:
        case DYNIP_RESPONSE_REGRESTRICT:
            show_my_message(ERR_KEY_INVALID);
    		break;
    
    	case DYNIP_RESPONSE_INTERNAL_SERVER_ERROR: // dynip server or client error
    	case DYNIP_RESPONSE_VERSION:
    	case DYNIP_RESPONSE_MALFORMED_REQUEST:
            show_my_message(ERR_INTERNAL_ERROR);
    		break;
    
    	default:
            show_my_message(ERR_UNKNOWN_CODE);
    		break;
	}
}

void main(int argc, char **argv)
{
int 	action_flag;
char	achTemp[MAXTEMP];
int 	ret, ch;
u_int	lval;
OPTION	option;
int arg_num = 0;

puts(achHeader);

ulDomainID = 0L;

strcpy(achInitFile, CFGDIR);

if (achInitFile[strlen(achInitFile)-1] != '/')
	strcat(achInitFile,"/");

sprintf(achDomainFile,"%s%s", achInitFile, DOMAIN_FILE);
strcat(achInitFile, CONF_FILE);

profInit();	/* initialize profiling module */
switch (optInitialize(argc, argv, "+p+d+s*@+r****@@"))
	{
	case OPT_ERROR_NONE:
		break;

	case OPT_ERROR_MISSING_ARGUMENTS:
		puts("dynipadmin: missing arguments\n");
		/* fall through */
	default:
		puts("Usage: dynipadmin -[d|p]|[-r <firstname> <lastname> <email> <hostname> [domain id] [ip addr]]|[-s <registration key> [hostname]]");
		exit(1);
	}	

while (optGetOption(&option) != OPT_ERROR_EOF)
	{
	switch (option.cOption)
		{
		case	'p':
			action_flag = ACTION_REFRESH;
			break;

		case	'd':
			action_flag = ACTION_DELETE;
			break;

		case	's':
			action_flag = ACTION_SETKEY;
            arg_num = option.cArguments;
			break;

		case	'r':
			action_flag = ACTION_REGISTER;

			strproper(option.args[0]);
	                strproper(option.args[1]);

        	        strcpy(regInfo.achFirstName,            option.args[0]);
                	strcpy(regInfo.achLastName,             option.args[1]);
 			strcpy(regInfo.achEmailAddress,         option.args[2]);
        	        strcpy(regInfo.achSubDomainName,        option.args[3]);

			ulIPAddress 	= 0;
			ulDomainID 	= 0;

			switch (option.cArguments)
				{
				case	6:
					if (isipaddress(option.args[5]))
						ulIPAddress = inet_addr(option.args[5]);
					else	if ((ulDomainID = getDomainID(option.args[5])) == -1)
							{
							printf("dynipadmin: the domain name '%s' does not appear in the '%s' file.\n", option.args[5], achDomainFile);
							exit(1);
							}
					/* fall through */
	
				case	5:	/* check if domain ID, domain name or IP address */		
					if (isipaddress(option.args[4]))
						ulIPAddress = inet_addr(option.args[4]);
					else	if ((ulDomainID = getDomainID(option.args[4])) == -1) 
							{
							printf("dynipadmin: the domain name '%s' does not appear in the '%s' file.\n", option.args[4], achDomainFile);
							exit(1);
							}
					break;

				default:
					break;
				}
			break;
		}
	optReleaseOption(&option);
	}		

optShutdown();

if (!FileExist(achInitFile))
	{
	printf("ERROR: Unable to open configuration file '%s'; file does not exist, or no permission to read/write.\n", achInitFile);
	exit(1);
	}

printf("Using configuration file '%s'.\n", achInitFile);

ulKeyID1 = profGetEntryInt("RegCode1",0L, achInitFile);
ulKeyID2 = profGetEntryInt("RegCode2",0L, achInitFile);

if (ulKeyID1 || ulKeyID2)
	printf("Registration key %u-%u\n", ulKeyID1,ulKeyID2);

bActive = profGetEntryInt("DomainActive", 0, achInitFile);

show_my_message(ERR_WAIT);
switch (action_flag)
	{
	case ACTION_DELETE:
		{
		if (!ulKeyID1 && !ulKeyID2)
			{
			puts("You must first register a valid Internet Name using the '-r' option.");
			adminclose(1);
			}

		puts("Deleting existing Internet Name registration.");

		regInfo.rrhead.usVersion	= htons(DYNIP_VERSION);
		regInfo.rrhead.ucRRCode		= DYNIP_COMMAND_DELETE;
		regInfo.rrhead.ucOSType		= DYNIP_OSTYPE;
		regInfo.rrhead.ulKeyID1		= htonl(ulKeyID1);
		regInfo.rrhead.ulKeyID2		= htonl(ulKeyID2);

        ret = SendRequest((char *)&regInfo,sizeof(regInfo),(char *)&rrResp, sizeof(rrResp));
        show_request_error(ret);
		switch (ret)
			{
			default:
				printf("Unexpected error %d.\n", ret);
				break;

			case REQ_NOHOST:
				puts("No DDNS hostname has been specified.");
				break;

			case REQ_NOHOSTENTRY:
				puts("The DDNS Server could not be resolved.");
				break;

			case REQ_SOCKETERROR:
				puts("Unable to open TCP socket.");
				break;

			case REQ_CONNECTERROR:
				puts("Unable to connect to DDNS Server; try again later."); 
				break;

			case REQ_SENDERROR:
				puts("Failed to send request; try the operation again.");
				break;

			case REQ_OK:
				if (rrResp.ucRRCode == DYNIP_RESPONSE_HOSTNAME_REMOVED)
					if ((ret = profSetEntryString("DomainActive","No",achInitFile)) == -1)
						print_error(ret);
				ProcessResponse(rrResp.ucRRCode);
				break;
			}
		}
		break;

	case ACTION_SETKEY:
		{
		char 	*pCode1, *pCode2;
		char	achKey[MAXTEMP];

		strcpymax(achKey, argv[2], sizeof(achKey));
		if ((pCode1 = strtok(argv[2],"-")) == NULL)
			{
			printf("%s is not a valid registration key.\n",argv[2]);
			adminclose(1);
			}

		printf("Setting new registration key to %s...", achKey);

		pCode2 = strtok(NULL,"\0");

		ulKeyID1 = (u_int)strtoul(pCode1, NULL, 10);
		ulKeyID2 = (u_int)strtoul(pCode2, NULL, 10);

		if ((ret = profSetEntryInt("RegCode1", ulKeyID1, achInitFile)) == -1)
			{
			print_error(ret);
			adminclose(1);
			}
							
		if ((ret = profSetEntryInt("RegCode2", ulKeyID2, achInitFile)) == -1)
			{
			print_error(ret);
			adminclose(1);
			}

        if(arg_num == 2)
		    strcpymax(dynip_hostname, argv[3], sizeof(dynip_hostname));
        
		puts("Done");
		}	/* fall through and perform a refresh */

	case ACTION_REFRESH:
		{
		if (!ulKeyID1 && !ulKeyID2)
			{
			puts("You must first register a valid Internet Name using the '-r' option.");
			adminclose(1);
			}

		puts("Reloading Internet Name registration information");

		regInfo.rrhead.usVersion	= htons(DYNIP_VERSION);
		regInfo.rrhead.ucOSType		= DYNIP_OSTYPE;
		regInfo.rrhead.ucRRCode		= DYNIP_COMMAND_REFRESH;
		regInfo.rrhead.ulKeyID1		= htonl(ulKeyID1);
		regInfo.rrhead.ulKeyID2		= htonl(ulKeyID2);
		regInfo.ulIPAddress		= 0;
		regInfo.ulDomainID		= 0;

        ret = SendRequest((char *)&regInfo, sizeof(regInfo), (char *)&regInfo, sizeof(regInfo));
        show_request_error(ret);
		switch (ret)
			{
			case REQ_NOHOST:
				puts("No DDNS hostname has been specified.");
				break;

			case REQ_NOHOSTENTRY:
				puts("The DDNS Server could not be resolved.");
				break;

			case REQ_SOCKETERROR:
				puts("Unable to open TCP socket.");
				break;

			case REQ_CONNECTERROR:
				puts("Unable to connect to DDNS Server; try again later.");
				break;

			case REQ_SENDERROR:
				puts("Failed to send request; try the operation again.");
				break;

			case REQ_OK:
				if (regInfo.rrhead.ucRRCode == DYNIP_RESPONSE_REFRESH)
				{
					if ((ret = profSetEntryString("LastName",regInfo.achLastName,achInitFile)) == -1)
						{
						print_error(ret);
						adminclose(1);
						}

					profSetEntryString("FirstName",regInfo.achFirstName,achInitFile);
					profSetEntryString("EmailAddress",regInfo.achEmailAddress,achInitFile);
					profSetEntryString("SubDomainName",regInfo.achSubDomainName,achInitFile);
					profSetEntryString("DomainActive","Yes",achInitFile);

					profSetEntryInt("DomainID",ntohl(regInfo.ulDomainID),achInitFile);
					profSetEntryInt("IPAddress",ntohl(regInfo.ulIPAddress),achInitFile);

                    if(strcmp(dynip_hostname,regInfo.achSubDomainName) != 0 && strlen(dynip_hostname) > 0)
                    {
                        char tmp[128] = "";

                        sprintf(tmp,"/usr/sbin/dynipadmin -r %s %s %s %s %d &",
                            regInfo.achFirstName,
                            regInfo.achLastName,
                            regInfo.achEmailAddress,
                            dynip_hostname,
                            ntohl(regInfo.ulDomainID));

                        system(tmp);
                
                        exit(0);
                    }

                    show_my_message(ERR_UPGRADE_OK);
                    if(ntohl(regInfo.ulIPAddress) == 0)
					    system(DYNIPCLIENT" &");
				}

				ProcessResponse(regInfo.rrhead.ucRRCode);
				break;

			default:
				printf("Unexpected error %d.\n", ret);
				break;
			}
		}
		break;

	case ACTION_REGISTER:
		{
		REGRES	regRes;

		printf("Registering hostname '%s'", regInfo.achSubDomainName);

		if (ulDomainID)
			printf(", domain ID %u", ulDomainID);

		if (ulIPAddress)
			{
			struct in_addr	in;

			in.s_addr = ulIPAddress;

			printf(", static IP address %s\n", (char *)inet_ntoa(in));
			}
		else	putchar('\n');

		regInfo.rrhead.usVersion	= htons(DYNIP_VERSION);
		regInfo.rrhead.ucRRCode		= DYNIP_COMMAND_REGISTER;
		regInfo.rrhead.ucOSType		= DYNIP_OSTYPE;

		regInfo.rrhead.ulKeyID1		= htonl(ulKeyID1);
		regInfo.rrhead.ulKeyID2		= htonl(ulKeyID2);

		regInfo.ulDomainID		= htonl(ulDomainID);
		regInfo.ulIPAddress		= htonl(ulIPAddress);

        ret = SendRequest((char *)&regInfo,sizeof(regInfo), (char *)&regRes, sizeof(regRes));
        show_request_error(ret);
		switch (ret)
			{
			case REQ_NOHOST:
				puts("No DDNS hostname has been specified.");
				break;

			case REQ_NOHOSTENTRY:
				puts("The DDNS Server could not be resolved");
				break;

			case REQ_SOCKETERROR:
				puts("Unable to open TCP socket");
				break;

			case REQ_CONNECTERROR:
				puts("Unable to connect to DDNS Server; try again later");
				break;

			case REQ_SENDERROR:
				puts("Failed to send registration information; try the operation again");
				break;

			case REQ_OK:
				ProcessResponse(regRes.rrhead.ucRRCode);

				if (regRes.rrhead.ucRRCode == DYNIP_RESPONSE_HOSTNAME_REGISTERED)
					{
					if ((u_char)LOBYTE(DYNIP_VERSION) < (u_char)LOBYTE(ntohs(regRes.rrhead.usVersion)))
						puts("DynIP Client upgrade available");

					if ((ret = profSetEntryString("LastName", regInfo.achLastName, achInitFile)) == -1)
						{
						print_error(ret);
						adminclose(1);
						}

					profSetEntryString("FirstName",regInfo.achFirstName,achInitFile);
					profSetEntryString("EmailAddress",regInfo.achEmailAddress,achInitFile);
					profSetEntryString("SubDomainName",regInfo.achSubDomainName,achInitFile);
					profSetEntryString("DomainActive","Yes",achInitFile);
		
					profSetEntryInt("DomainID",ntohl(regInfo.ulDomainID),achInitFile);
					profSetEntryInt("IPAddress",ntohl(regInfo.ulIPAddress),achInitFile);
	
					sprintf(achTemp,"%ld",ntohl(regRes.rrhead.ulKeyID1));
					profSetEntryString("RegCode1",achTemp,achInitFile);
					
					sprintf(achTemp,"%ld",ntohl(regRes.rrhead.ulKeyID2));
					profSetEntryString("RegCode2",achTemp,achInitFile);
					printf("You are now known to the Internet as '%s'\n", regRes.achFullDomainName);
					
					updateDomainFile(regRes.achFullDomainName, ntohl(regInfo.ulDomainID));

                    show_my_message(ERR_UPGRADE_OK);
                    if(ntohl(regInfo.ulIPAddress) == 0)
					    system(DYNIPCLIENT" &");
					}
				break;

			default:
				printf("Unexpected error %d.\n", ret);
				break;
			}
		}
		break;
	}
adminclose(0);
}

/************************************ local functions **********************************/

static BOOL ProcessResponse(int code)
{
switch (code)
	{
	case DYNIP_RESPONSE_HOSTNAME_RESERVED:
		puts("The Internet Name that you have selected is reserved;\nplease specify an alternate name and try the operation again.");
		break;

	case DYNIP_RESPONSE_HOSTNAME_INUSE:
		puts("The Internet Name that you have selected is already in use by another user;\nplease specify an alternate name and try again.");
		break;

	case DYNIP_RESPONSE_HOSTNAME_REGISTERED:
		puts("Your Internet Name has been registered.");
		break;

	case DYNIP_RESPONSE_PERIOD_EXPIRED:
		puts("Your registration period has expired; please visit our website at http://www.dynip.com for payment options.");
		break;

	case DYNIP_RESPONSE_ALREADY_REGISTERED:
		puts("You already have an active domain registration; use the refresh option\nto update your configuration file.");
		break;

	case DYNIP_RESPONSE_INTERNAL_SERVER_ERROR:
		puts("There was an internal server error; please retry the operation or\nreport the problem to support@dynip.com.");
		break;

	case DYNIP_RESPONSE_HOSTNAME_REMOVED:
		puts("Your Internet Name has been succesfully deleted; you may now register a new name.");
		break;

	case DYNIP_RESPONSE_VERSION:
		puts("You are using an unsupported version of the DynIP Client Software; please visit our website at http://www.dynip.com to obtain an updated version.");
		break;

	case DYNIP_RESPONSE_MALFORMED_REQUEST:
		puts("The server received a malformed request.");
		break;

	case DYNIP_RESPONSE_REFRESH:
		puts("Refresh information received; updating configuration file.");
		break;

	case DYNIP_RESPONSE_NOT_REGISTERED:
		puts("You do not have an active domain registration.");
		break;

	case DYNIP_RESPONSE_INVALID_DOMAIN:
		puts("The domain ID specified is not valid.");
		break;

	case DYNIP_RESPONSE_INVALID_NAME:
		puts("You have specified an invalid name for the hostname.");
		break;

	case DYNIP_RESPONSE_REGRESTRICT:
		puts("You cannot request another registration key-pair.");
		break;

	default:
		printf("Unknown response code received from server: %x\n",code);
		break;
	}

    show_response_error(code);

return (0);
}

static BOOL SendRequest(char *pMsg, int msgsize, char *pResult, int maxresult)
{
struct 	hostent 	*hent;
struct  sockaddr_in	sock;
long			lAddr;
RRHEAD			*rrhead;
struct 	in_addr		in;
int			s,len,ret;
char			achAddress[MAXADDRESS];
char			achHostName[MAXDOMAIN];

if (!profGetEntryString("DDNSServerDefault",achHostName,sizeof(achHostName),"",achInitFile))
	return (REQ_NOHOST);

printf("Resolving host '%s'...", achHostName);

if ((hent = gethostbyname(achHostName)) == (struct hostent *)NULL)
	{
	/* could not do hostname lookup, use cached version in 
           configuration file
        */
	
	if (!profGetEntryString("DDNSServer-Cache", achAddress, sizeof(achAddress), NULL, achInitFile))
		return (REQ_NOHOSTENTRY); /* no cache present */

	lAddr = inet_addr(achAddress);
	
	printf("(using cache)..");
	}
else	{
	lAddr = *(u_long *)hent->h_addr_list[0];

	/* update our cache */

	in.s_addr = lAddr;
	strcpy(achAddress, (char *)inet_ntoa(in)); 

	if ((ret = profSetEntryString("DDNSServer-Cache", achAddress, achInitFile)) == -1)
		print_error(ret);	/* don't exit */
	}

puts("Done.");

if ((s = socket(AF_INET, SOCK_STREAM,0)) ==  -1)
	return (REQ_SOCKETERROR);

sock.sin_family 	= AF_INET;
sock.sin_port		= htons(DYNIP_REGISTER_PORT);
sock.sin_addr.s_addr	= lAddr;
in.s_addr		= lAddr;

printf("Connecting to %s (%s)...", achHostName, inet_ntoa(in));

if ((connect(s, (struct sockaddr *)&sock, sizeof(sock))) == -1)
	{
	close(s);
	return (REQ_CONNECTERROR);
	}

puts("Connected.");

/* we are connected */
/* send the header and wait */

printf("Negotiating protocol...");
if ((send(s, pMsg, msgsize, 0)) != msgsize)
	{
	close(s);
	return (REQ_SENDERROR);
	}

puts("Handshake OK");

if ((len = recv(s, (char *)pResult, sizeof(RRHEAD), 0)) != sizeof(RRHEAD))
	{
	close(s);
	return (REQ_SENDERROR);
	}

rrhead = (RRHEAD *)pResult;

maxresult -= len;

if (!(rrhead->ucRRCode & 0x80))
	if ((len = recv(s, (char *)&pResult[len], maxresult, 0)) != maxresult)
		{
		close (s);
		return (REQ_SENDERROR);
		}

puts("Response received; closing.");

close(s);
return (REQ_OK);
}

static u_long getDomainID(char *pDomainID)
{
int	cnt,len;

/* check if the domain ID is a number or a reference to an actual domain name */

len = strlen(pDomainID) - 1;
while (isdigit(pDomainID[len]) && len >= 0) 
	len--;

if (len == -1) /* we reached the beginning and found only digits */
	return (strtoul(pDomainID, NULL, 10));

return (profGetEntryInt(pDomainID, -1, achDomainFile));
}

static void strproper(char *pStr)
{
int cnt;
int len;

len = strlen(pStr);

*pStr = toupper( *pStr );

for (cnt = 1; cnt < len; cnt++)
	{
	if (pStr[cnt] == 32 && (cnt+1) < len)
		pStr[++cnt] = toupper(pStr[cnt]);
	}
}


static void adminclose(int ret)
{
profShutdown();

exit(ret);
}

static void print_error(int error)
{
switch (error)
	{
	case PROF_ERROR_OPENFILE:
		puts("ERROR: Unable to open configuration file.");
		break;

	case PROF_ERROR_WRITEFILE:
		puts("ERROR: Unable to update entry; no permission.");
		break;

	default:
		puts("ERROR: Internal error.");
		break;
	}
}

static BOOL FileExist(char *pFile)
{
return (close(open(pFile,O_RDWR,0)) == -1 ? 0 : 1);
}

static int strcpymax(char *pDest, char *pSrc, int maxdest)
{
register len;

len = strlen(pSrc);
len = (len > maxdest-1) ? maxdest-1 : len;

memcpy(pDest, pSrc, len);
pDest[len] = '\0';

return (len);
}

static BOOL isipaddress(char *pString)
{
int	len,cnt,dotcnt;

len 	= strlen(pString);
dotcnt	= 0;

for (cnt = 0; cnt < len; cnt++)
	if (pString[cnt] == '.' && cnt)
		++dotcnt;
	else	if (!isdigit(pString[cnt]))
			return (0);
	
return ((dotcnt == 3) ? 1 : 0);
}


static BOOL updateDomainFile(char *pFQDN, u_long ulDomainID)
{
char	*ptr;
char	achResult[MAXTEMP];

if ((ptr = strchr(pFQDN, '.')) != NULL)
	{
	++ptr;

	if (!profGetEntryString(ptr, achResult, sizeof(achResult), NULL, achDomainFile))
		{
		sprintf(achResult,"%ul", ulDomainID);
		if (profSetEntryString(ptr, achResult, achDomainFile))
			printf("dynipadmin: unable to update domain database file '%s'; no write permission.\n", achDomainFile);
		return (1);
		}
	}

return (0);
}
