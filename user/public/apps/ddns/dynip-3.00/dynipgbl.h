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
 *	@(#)dynipgbl.h	1.1 (CanWeb) 24/7/97			 *
 *	$Id: dynipgbl.h,v 1.1 1997/7/24 09:13:16 $	 	 *
 */

#ifndef __DYNIPGBL
#define __DYNIPGBL

#include <sys/types.h>
#include <stdio.h>

#define LOBYTE(a)				(a & 0x0ff)
#define HIBYTE(a)				((a >> 8) & 0x0ff)

#define DYNIP_KA_SIGNATURE			0x1000FFFF

#define DYNIP_CLIENT_PORT			15353
#define DYNIP_REGISTER_PORT			252
#define DYNIP_KA_PORT				53

#define DYNIP_MAXCLIENTPORT			32767
#define DYNIP_MAXPORTMAP			128
#define DYNIP_MAXSUBDOMAIN			80
#define DYNIP_MAXNAME				32
#define DYNIP_MAXEMAIL				80
#define DYNIP_MAXDOMAIN				256

#define DYNIP_TYPE_KA				1
#define DYNIP_TYPE_CLOSE			0

#define DYNIP_SMP_EXIT				1
#define DYNIP_SMP_STOPUPDATE			2
#define DYNIP_SMP_SETINTERVAL			3

#define DYNIP_FLAG_STATIC			'2'
#define DYNIP_FLAG_DYNAMIC			'1'
#define DYNIP_FLAG_INACTIVE			'0'

#define DYNIP_STAT_ACTIVE			'1'
#define DYNIP_STAT_PROBATION			'2'
#define DYNIP_STAT_EXPIRED			'4'

/* different commands that can be sent to the server */
#define DYNIP_COMMAND_REGISTER			1
#define DYNIP_COMMAND_DELETE			2
#define DYNIP_COMMAND_REFRESH			3

/* the current version of the server		*/
#define DYNIP_VERSION_MINOR			0
#define DYNIP_VERSION_MAJOR			3

#define DYNIP_VERSION				((DYNIP_VERSION_MAJOR << 8) | DYNIP_VERSION_MINOR)

/* the response codes from the DDNS server	*/
#define DYNIP_RESPONSE_HOSTNAME_REGISTERED	0x01
#define DYNIP_RESPONSE_HOSTNAME_REMOVED		0x02
#define DYNIP_RESPONSE_REFRESH			0x03

#define DYNIP_RESPONSE_HOSTNAME_RESERVED	0x80
#define DYNIP_RESPONSE_HOSTNAME_INUSE		0x81
#define DYNIP_RESPONSE_PERIOD_EXPIRED		0x82
#define DYNIP_RESPONSE_ALREADY_REGISTERED	0x83
#define DYNIP_RESPONSE_SERVER_DISABLED		0x84
#define DYNIP_RESPONSE_NOT_REGISTERED		0x85
#define DYNIP_RESPONSE_INTERNAL_SERVER_ERROR	0x86
#define DYNIP_RESPONSE_MALFORMED_REQUEST	0x87
#define DYNIP_RESPONSE_VERSION			0x88
#define DYNIP_RESPONSE_INVALID_DOMAIN		0x89
#define DYNIP_RESPONSE_INVALID_NAME		0x8a
#define DYNIP_RESPONSE_REGRESTRICT		0x8b

/* error response codes				*/
#define DYNIP_INVALID_COMMAND			0x8b

#define DYNIPCLIENT "/usr/sbin/dynipclient"
#define DDNS_UPDATE_LOG "/tmp/ddns_update.log"

#define ERR_NO_MESSAGE              1
#define ERR_FIELDS_MUST_EMPTY       2
#define ERR_IP_SAME                 3
#define ERR_SETTING_NULL            4
#define ERR_DNS_QUERY_ERROR         5
#define ERR_DNS_SERVER_ERROR        6
#define ERR_INTERNET_ERROR          7
#define ERR_HTTP_ERROR              8
#define ERR_USER_PSWD_ERROR         9
#define ERR_UPGRADE_OK              10
#define ERR_NO_ERROR                11
#define ERR_WAIT                    12
#define ERR_DOMAIN_NAME_NOT_QUALIFY 13
#define ERR_HOST_NOT_EXIST          14
#define ERR_HOST_NOT_SUPPORT        15
#define ERR_ABUSE                   16
#define ERR_SERVER_HOST_FULL        17
#define ERR_SERVICE_DOWN            18
#define ERR_UNKNOWN_CODE            19
#define ERR_UNKNOWN_ERROR           20
#define ERR_HTTP_SOCKET             21
#define ERR_WAN_IP_NULL             22
#define ERR_DOMAIN_NAME_INVALID     23
#define ERR_KEY_INVALID             24
#define ERR_INTERNAL_ERROR          25

typedef struct tagRRHead
	{
	u_short		usVersion;	/* current version */

	u_char		ucOSType;
	u_char		ucRRCode;

	u_int		ulKeyID1;	/* registration key pair */
	u_int		ulKeyID2;
	} RRHEAD;

typedef struct tagRegRef
	{
	RRHEAD	rrhead;
	
	u_int	ulIPAddress;		/* 0 for dynamic */
	u_int	ulDomainID;		/* 0 for the dynip.com domain */
	
	char	achFirstName[DYNIP_MAXNAME];
	char	achLastName[DYNIP_MAXNAME];
	char	achEmailAddress[DYNIP_MAXEMAIL];
	char	achSubDomainName[DYNIP_MAXSUBDOMAIN];
	} REGREF;

typedef struct tagRegRes
	{
	RRHEAD	rrhead;
	char	achFullDomainName[DYNIP_MAXDOMAIN];
	} REGRES;

typedef struct tagKeepAlive
	{
	u_int	ulSignature;
	u_short	usVersion;

	union 
		{
		u_short	usDummy;
		struct {

#if defined (SUNOS)
			u_short usReserved	:1;
			u_short usUDPPortCount	:6;
			u_short usTCPPortCount	:6;
			u_short usPortmap	:1;
			u_short usType		:2;
#else
			u_short	usType 		:2;	/* type of packet */
			u_short usPortmap	:1;	/* portmap included 0=no, 1=yes */
			u_short usTCPPortCount	:6;	/* how many TCP ports */
			u_short	usUDPPortCount	:6;	/* how many UDP ports */
			u_short	usReserved	:1;	/* reserved, must be 1 */
#endif
			} ss;	/* struct short */
		} us;	/* union short */

	u_short	usSMPPort;
	u_short	usReserved;		/* presently unused */ 

	u_int	ulKeyID1;		/* registration key pair */
	u_int	ulKeyID2;
	} KEEPALIVE;

typedef struct tagServerMessagePacket
	{
	u_short	usVersion;		/* server version */
	u_short usCommand;		
	u_int	ulKeyID1;
	u_int	ulKeyID2;
	u_int	ulReserved;
	} SMP;

#endif
