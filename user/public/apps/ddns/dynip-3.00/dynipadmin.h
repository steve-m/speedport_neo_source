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
 *	@(#)dynipadmin.h	2.0 (CanWeb) 2/7/97		 *
 *	$Id: dynipadmin.h,v 2.0 1997/7/2 18:13:33 $	 	 *
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define CONF_FILE		"dynip.cfg"
#define DOMAIN_FILE		"dynip.dom"

#define ACTION_REFRESH		1
#define ACTION_DELETE		2
#define ACTION_REGISTER		3
#define ACTION_SETKEY		4

#define MAXDOMAIN		80
#define MAXADDRESS		16
#define MAXTEMP			80
#define MAXFILENAMELEN		80

#define REQ_OK					0
#define REQ_NOHOST				1
#define REQ_NOHOSTENTRY				2
#define REQ_SOCKETERROR				3
#define REQ_CONNECTERROR			4
#define REQ_SENDERROR				5

typedef unsigned char BOOL;

static 	char		achInitFile[MAXFILENAMELEN];
static	char		achDomainFile[MAXFILENAMELEN];

static  REGREF		regInfo;
static  RRHEAD		rrResp;

static  u_int		ulKeyID1;
static  u_int		ulKeyID2;
static  u_int		ulDomainID;
static  u_int		ulIPAddress;

static	BOOL		bActive;

/* function prototypes */
static void		strproper(char *);
static void		adminclose(int);
static void		print_error(int);
static int		strcpymax(char *, char *, int);
static u_long		getDomainID(char *);
static BOOL 		updateDomainFile(char *, u_long);
static BOOL		FileExist(char *);
static BOOL		SendRequest(char *, int,char *, int);
static BOOL		ProcessResponse(int);
static BOOL		isipaddress(char *);

