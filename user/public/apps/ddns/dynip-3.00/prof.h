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
 *	@(#)prof.h	1.0 (CanWeb) 2/7/97			 *
 *	$Id: prof.h,v 1.0 1997/7/2 18:13:33 sae Exp $	 	 *
 */

#ifndef __PROF
#define __PROF

#define PROF_CH_TAB		(char)9
#define PROF_CH_SPACE		(char)32
#define PROF_CH_COMMENT		(char)'#'
#define PROF_CH_NEWLINE		(char)'\12'
#define PROF_CH_DQUOTE		(char)'"'
#define PROF_CH_SQUOTE		(char)'\''

#define PROF_TYPE_PLAIN		1
#define PROF_TYPE_CONF		0

#define PROF_MAXNAME		80
#define PROF_MAXLINE		256

#define PROF_ERROR_NONE		0
#define PROF_ERROR_OPENFILE	1
#define PROF_ERROR_WRITEFILE	2
#define PROF_ERROR_ENTRYNOTFND	3
#define PROF_ERROR_ENTRYFORMAT	4
#define PROF_ERROR_NOTINIT	5

u_int profGetEntryInt(char *, u_int, char *);
u_int profSetEntryInt(char *, u_int, char *);
u_int profGetEntryString(char *, char *, u_short,char *, char *);
u_int profSetEntryString(char *, char *, char *);
u_int profGetLine(u_short,char *, u_short, char *);
u_int profGetLastError(void);

u_int profInit(void);		/* just stubs for now */
u_int profShutdown(void);

#endif

