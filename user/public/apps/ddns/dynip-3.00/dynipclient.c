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
 *	@(#)dynipclient.c	3.00 (CanWeb) 02/04/98		 *
 *	$Id: dynipclient.c,v 2.01 1998/04/02 12:50:23 $		 *
 */

#include "dynipgbl.h"
#include "dynipclient.h"
#include "opt.h"
#include "log.h"

#ifndef lint
static char sccsid[] = "@(#)dynipclient.c      3.00 (CanWeb) 02/04/98";
static char copyright[] = "@(#) Copyright (c) 1998\n\
	CanWeb Internet Services Ltd. All Rights Reserved.\n";
#endif

void main(int argc, char *argv[])
{
int		ret;
BOOL		bKill;
char		achTemp[MAXTEMP];
OPTION		option;

#if defined (LINUX) || defined (SUNOS) || defined (OSF1)
int		nfds;
fd_set		fds;
struct timeval	tv;
#endif

strcpy(achInitFile, CFGDIR);
		
if (achInitFile[strlen(achInitFile)-1] != '/')
	strcat(achInitFile,"/");
strcat(achInitFile, CONF_FILE);		

bKill 	= FALSE;
bSilent = FALSE;

switch (optInitialize(argc, argv, "-k-f:-n"))
	{
	case OPT_ERROR_NONE:
	case OPT_ERROR_NOOPTIONS:
		break;

	case OPT_ERROR_OPTION_NOTDEFINED:
		puts("Invalid option specified.\n");
		usage(argv[0]); /* never returns */
		break;	

	case OPT_ERROR_MISSING_ARGUMENTS:
		puts("Missing arguments for specified option.\n");
	/* fall through */
	default:
		usage(argv[0]); /* never returns */
		break;
	}

while (optGetOption(&option) != OPT_ERROR_EOF)
	switch (option.cOption)
		{
		case 'k':
			bKill = TRUE;
			break;

		case 'f':
			strcpy(achInitFile,option.args[0]);
			break;

		case 'n':
			bSilent = TRUE;
			break;

		default:
			break;
		}

optShutdown();
logOpen(argv[0], bSilent ? MODLOG_OPTION_SYSLOG : MODLOG_OPTION_SYSLOG|MODLOG_OPTION_TTY);

if (!FileExist(achInitFile))
	{
	logWrite("ERROR: Unable to open configuration file '%s'\n",achInitFile);
	exit(1);
	}

logWrite("Using client configuration file '%s'\n", achInitFile);

profInit();	/* initialize prof module */
	
if (bKill)
	{
	ret = 1;

	profGetEntryString("ClientPIDDirectory", achTemp, sizeof(achTemp), "/tmp", achInitFile);
	if (achTemp[strlen(achTemp)-1] != '/')
		strcat(achTemp,"/");
	strcat(achTemp, PID_FILE);

	if (!FileExist(achTemp))
		{
		logWrite("ERROR: %s file does not exist; cannot terminate the DynIP Client.\n", achTemp);
		closeclient(1);
		}

	pid = getpidfromfile(achTemp);
	
	if ((ret = kill(pid, SIGHUP)) == 0)
		{
		logWrite("Kill signal sent to DynIP client process %d\n", pid);
		unlink(achTemp);
		}
	else 	logWrite("Kill signal NOT sent to DynIP client");

	closeclient((ret != 0) ? 1 : 0);
	}

if ((ulKeyID1 = profGetEntryInt("RegCode1", 0L, achInitFile)) == 0L)
	{
	logWrite("ERROR: No registration key pair defined. Please run the dynipadmin program first to register a sub-domain name.");
	closeclient(1);
	}

if ((ulKeyID2 = profGetEntryInt("RegCode2", 0L, achInitFile)) == 0L)
	{
	logWrite("ERROR: No registration key pair defined. Please run the dynipadmin program first to register a sub-domain name.");
	closeclient(1);
	}

if (profGetEntryInt("IPAddress", 0L, achInitFile) != 0L)
	{
	logWrite("ERROR: You have registered a domain that points to a static IP address.\nYou do not need to run the dynipclient program.");
	closeclient(1);
	}

profGetEntryString("ClientPIDdirectory",achPIDFile,sizeof(achPIDFile),"/tmp",achInitFile);
if (achPIDFile[strlen(achPIDFile)-1] != '/')
	strcat(achPIDFile,"/");
strcat(achPIDFile,PID_FILE);

if ((bActive = profGetEntryInt("DomainActive", 0, achInitFile)) == 0)
	{
	logWrite("ERROR: You must first register a valid domain using dynipadmin");

	closeclient(1);
	}

if (!InitializeClient(achInitFile))
	{
	logWrite("ERROR: Unable to initialize DynIP Client program.");
	closeclient(1);
	}

signal(SIGHUP, terminate);
signal(SIGTERM, terminate);	/* in case we go to single-user */

if (fork() != 0)
	exit(0);

pid = getpid();
if ((profSetEntryInt("ClientPID",pid, achInitFile)) == -1)
	logWrite("WARNING! unable to set PID in '%s'; no permission.\n", achInitFile);

/* At the original time of this writing, Linux did not support asynchronous I/O */
#ifdef FREEBSD 

fcntl(socketSI, F_SETOWN, pid);

signal(SIGIO, SMPProcessor);

if ((fcntl(socketSI, F_SETFL, O_ASYNC)) == -1)
	closeclient(1);

#endif

/* !!!!!!!! NOTE !!!!!!!!
   DO NOT REDUCE THIS VALUE!
   The DynIP server will block all subsequent traffic from
   our IP address if we send more than 2 packets per minute
   to the DynIP server.
*/
wait_time	= 120;		/* just to be safe */

writePID(achPIDFile,(u_int)pid);

logWrite("active");

SendKeepAlivePacket(TRUE);

sleep(15);

SendKeepAlivePacket(TRUE);

/* just to make sure it got there */

#if defined (LINUX) || defined (SUNOS) || defined (OSF1)
nfds = socketSI + 1;
#endif


for ( ; ; )	/* loop until killed */
	{

#if defined (LINUX) || defined (SUNOS) || defined (OSF1)

	tv.tv_sec	= wait_time;
	tv.tv_usec	= 0;

	FD_ZERO(&fds);
	FD_SET(socketSI, &fds);

	if ((select(nfds, &fds, (fd_set *)0, (fd_set *)0,(struct timeval *)&tv)) == 1)
		SMPProcessor(0); 
	else
#else
	sleep(wait_time);
#endif

	SendKeepAlivePacket(TRUE);
	}
}

static BOOL InitializeClient(char *pFile)
{
char		achHostName[MAXHOSTNAME];
char		achAddress[MAXADDRESS];
struct hostent	*hent;
struct in_addr	in;
u_short		usPort;
u_long		lAddr;

if (!profGetEntryString("DDNSServerDefault",achHostName,sizeof(achHostName),"",pFile))
	return (FALSE);

if ((hent = gethostbyname(achHostName)) == (struct hostent *)NULL)
	{
	/* host lookup failed; use cached version instead */

	if (!profGetEntryString("DDNSServer-Cache", achAddress, sizeof(achAddress), "", pFile))
		lAddr = inet_addr(achAddress);
	else	return (FALSE);
	}
else	{
	lAddr = *(u_int *)hent->h_addr;
	in.s_addr = lAddr;

	strcpy(achAddress, (char *)inet_ntoa(in));

	/* update our cache in case the IP address has changed */
	profSetEntryString("DDNSServer-Cache", achAddress, pFile);
	}

if ((socketKA = socket(AF_INET, SOCK_DGRAM,0)) == -1)
	return (FALSE);

if ((socketSI = socket(AF_INET, SOCK_DGRAM,0)) == -1)
	{
	close (socketKA);
	return (FALSE);
	}

sockKA.sin_family 	= AF_INET;
sockKA.sin_port   	= htons(DYNIP_KA_PORT);
sockKA.sin_addr.s_addr	= lAddr;

usPort = profGetEntryInt("SMPPort", DYNIP_CLIENT_PORT, achInitFile);
usPort = FindClientPort(usPort);

sockSI.sin_family	= AF_INET;
sockSI.sin_port		= htons(usPort);
sockSI.sin_addr.s_addr	= INADDR_ANY;

if (bind(socketSI, (struct sockaddr *)&sockSI, sizeof(sockSI)) == -1)
	{
	close (socketKA);
	close (socketSI);

	return (FALSE);
	}

return (TRUE);
}

static BOOL SendKeepAlivePacket(BOOL bActive)
{
KEEPALIVE	ka;

ka.ulSignature		= ntohl(DYNIP_KA_SIGNATURE);
ka.usVersion		= htons(DYNIP_VERSION);

ka.us.ss.usType		= bActive ? DYNIP_TYPE_KA : DYNIP_TYPE_CLOSE; 
ka.us.ss.usPortmap	= 0;
ka.us.ss.usTCPPortCount	= 0;
ka.us.ss.usUDPPortCount	= 0;
ka.us.ss.usReserved	= 1;

ka.us.usDummy		= htons(ka.us.usDummy);

ka.usSMPPort		= sockSI.sin_port;
ka.usReserved		= 0; 

ka.ulKeyID1		= htonl(ulKeyID1);
ka.ulKeyID2		= htonl(ulKeyID2);

if ((sendto(socketKA, (char *)&ka.ulSignature, sizeof(ka), 0, (struct sockaddr *)&sockKA, sizeof(sockKA))) == sizeof(ka))
	return (TRUE);

return (FALSE);
}

static BOOL FileExist(char *pFile)
{
return (close(open(pFile,O_RDONLY,0)) == -1 ? FALSE : TRUE);
}

static void usage(char *pname)
{
printf("Usage: %s [-k] [-n] [-f <configuration file>]\n", pname);
exit(1);
}
	
static void closeclient(int ret)
{
profShutdown();
logClose(); 	/* close message logger */
exit(ret);
}

static u_int getpidfromfile(char *pFile)
{
FILE	*fp;
char	achTemp[MAXTEMP];

if ((fp = fopen(pFile,"r")) == NULL)
	return (-1);

fgets(achTemp, sizeof(achTemp), fp);

fclose(fp);

return ((u_int)atoi(achTemp));
}

static u_short FindClientPort(u_short usStartPort)
{
int			s;
struct sockaddr_in	sin;
u_int			usPort;

if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	return (-1);

for (usPort = usStartPort; usPort < DYNIP_MAXCLIENTPORT; usPort++)
	{
	sin.sin_family		= AF_INET;
	sin.sin_port		= htons(usPort);
	sin.sin_addr.s_addr	= INADDR_ANY;

	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) == 0)
		{
		close(s);
		return (usPort);
		}
	}

close(s);

return (-1);
}
