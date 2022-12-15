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
 *	@(#)dynipclient.h	2.0 (CanWeb) 2/7/97		 *
 *	$Id: dynipclient.h,v 2.0 1997/7/2 18:13:33 $		 *
 */

#include <stdio.h>

#ifdef SUNOS
#include <sys/filio.h>
#endif

#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>

#if defined (LINUX) || defined (SUNOS) || defined (OSF1)
#include <sys/time.h>
#endif

#ifndef TRUE
#define TRUE			1
#define FALSE			!TRUE
#endif

#define CONF_FILE		"dynip.cfg"
#define PID_FILE		"dynipclient.pid"

#define MAXADDRESS		80
#define MAXHOSTNAME		80
#define MAXTEMP			80
#define MAXFILENAMELEN		80
#define MAXBUFFER		512

typedef unsigned char BOOL;

typedef struct tagPortmap
	{
	KEEPALIVE	ka;
	u_short		portmap[DYNIP_MAXPORTMAP];
	} Portmap;

static  struct sockaddr_in	sockKA;
static 	struct sockaddr_in	sockSI;

static  int			socketKA, socketSI;
static  int			wait_time;
static  int			pid;

static 	char			achInitFile[MAXFILENAMELEN];
static  char			achPIDFile[MAXFILENAMELEN];
static  char			achPortmapFile[MAXFILENAMELEN];
static  Portmap			portmap;
static  u_int			ulKeyID1, ulKeyID2;

static  BOOL			bActive, bPortmap, bSilent;

/* function prototypes */
static BOOL		FileExist(char *);
static BOOL		SendKeepAlivePacket(BOOL);
static BOOL		InitializeClient(char *);
static BOOL		SendPortmap(void);

static u_int		getpidfromfile(char *);
static u_short		FindClientPort(u_short);

static void		closeclient(int);
static void		terminate(int);
static void		writePID(char *,u_int);
static void		SMPProcessor(int);
static void		usage(char *);

static int		writeMessage(char *, ...);


static void terminate(int reglist)
{
if (bActive)
	{
	SendKeepAlivePacket(FALSE);
	SendKeepAlivePacket(FALSE);

	sleep(1);
	}

close(socketSI);
close(socketKA);

profSetEntryInt("ClientPID",0, achInitFile);

closeclient(0);
}

static void SMPProcessor(int reglist)
{
u_int	lRet;
SMP	smp;
struct	sockaddr sock;
int	namelen, oldblock;

#if defined (FREEBSD) || defined (LINUX)
oldblock = sigblock(~0L);
#endif

if ((ioctl(socketSI, FIONREAD, (u_int *)&lRet, 0)) != -1 && lRet >= sizeof(SMP))
	{
	recvfrom(socketSI, (char *)&smp.usVersion, sizeof(SMP), 0,(struct sockaddr *)&sock, &namelen); 

	if (ntohl(smp.ulKeyID1) == ulKeyID1 && ntohl(smp.ulKeyID2) == ulKeyID2)
		switch (ntohs(smp.usCommand))
			{
			case DYNIP_SMP_STOPUPDATE:
				syslog(LOG_ERR,"Registration period expired; server told us to shutup");
				profSetEntryString("DomainActive","No",achInitFile);
				bActive    = FALSE;
				terminate(0);
				break;

			case DYNIP_SMP_EXIT:
				terminate(0);
				break;

			case DYNIP_SMP_SETINTERVAL:
				wait_time = ntohl(smp.ulReserved);
				break;
			}
	}

#if defined (FREEBSD) || defined (LINUX)
sigblock(oldblock);
#endif
}

static void writePID(char *pFile, u_int pids)
{
FILE *fp;

if ((fp = fopen(pFile,"w")) == NULL)
	return ;

#ifdef FREEBSD
fprintf(fp,"%ld", (u_int)pids);
#endif

#if defined (LINUX) || defined (SUNOS) || defined (OSF1)
fprintf(fp,"%ld\n", (u_int)pids);
#endif

fclose(fp);
}

