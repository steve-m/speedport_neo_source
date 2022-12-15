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
 *	@(#)prof.c	1.1 (CanWeb) 2/7/97			 *
 *	$Id: prof.c,v 1.1 1997/7/2 18:13:33 sae Exp $	 	 *
 */

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

static   u_int		profError;
static 	 u_int		profInitFlag;

#include "prof.h"

/* local (internal) functions */
static u_short copyfile(FILE *, FILE *, u_int);
static u_short findOffset(FILE *, char *, u_short *);
static u_short _getline(FILE *, char *, u_short, u_short);
static u_short strcpymax(char *, char *, u_short);

u_int profGetLine(u_short lineno, char *pLine, u_short maxline, char *pFile)
{
FILE 	*fp;
u_int	ret;

if (!profInitFlag)
	{
	profError = PROF_ERROR_NOTINIT;
	return (-1);
	}

profError = PROF_ERROR_NONE;

if ((fp = fopen(pFile, "r")) == NULL)
	{
	profError = PROF_ERROR_OPENFILE;
	return (-1);
	}

ret = 0;
while (lineno--)
	ret = (u_int)_getline(fp, pLine, maxline, PROF_TYPE_PLAIN);

fclose(fp);

if (!ret)
	profError = PROF_ERROR_ENTRYNOTFND;

return ( (ret != 0) ? ret : -1 );
}

u_int profGetEntryInt(char *pEntry, u_int uiDef, char *pFile)
{
char	achLine[PROF_MAXLINE];

if (!profInitFlag)
	{
	profError = PROF_ERROR_NOTINIT;
	return (-1);
	}

/* profError already set by profGetEntryString */

if (!profGetEntryString(pEntry, achLine, sizeof(achLine), "", pFile))
	return (uiDef);

if ((strcasecmp(achLine,"no")) == 0)
	return (0);

if ((strcasecmp(achLine,"yes")) == 0)
	return (1);

if (!isdigit(achLine[0]) && achLine[0] != '-')
	{
	profError = PROF_ERROR_ENTRYFORMAT;
	return (uiDef);
	}

return (atoi(achLine));
}

u_int profSetEntryInt(char *pEntry, u_int uiValue, char *pFile)
{
char	achValue[PROF_MAXNAME];

if (!profInitFlag)
	{
	profError = PROF_ERROR_NOTINIT;
	return (-1);
	}

profError = PROF_ERROR_NONE;

sprintf(achValue,"%ld", uiValue);

return (profSetEntryString(pEntry, achValue, pFile) );
}

u_int profGetEntryString(char *pEntry, char *pResult, u_short maxresult,char *pDefault, char *pFile)
{
FILE 	*fp;
int 	 cnt;
char	achLine[PROF_MAXLINE];
char	*ptr;

if (!profInitFlag)
	{
	profError = PROF_ERROR_NOTINIT;
	return (-1);
	}

profError = PROF_ERROR_NONE;

if ((fp = fopen(pFile,"r")) == NULL)
	{
	profError = PROF_ERROR_OPENFILE;
	return ( strcpymax(pResult, pDefault, maxresult) );
	}

cnt = 1;
while (cnt != 0)
	if ((cnt = _getline(fp, achLine, sizeof(achLine),PROF_TYPE_CONF)) != 0)
		{
		ptr = strtok(achLine, "=");

		if ((strcasecmp(ptr, pEntry)) == 0)
			{
			fclose(fp);

			ptr = strtok(NULL,"\0");

			return (strcpymax(pResult, (ptr == (char *)NULL) ? pDefault : ptr, maxresult));
			}
		}

profError = PROF_ERROR_ENTRYNOTFND;
fclose(fp);
return ( strcpymax(pResult, pDefault, maxresult) );
}

u_int profSetEntryString(char *pEntry, char *pString, char *pFile)
{
FILE 	*fp, *fpTemp;
int  	offs;
char	*pName;
char	achName[PROF_MAXNAME];
char	achSearch[PROF_MAXNAME];
u_short slen;

if (!profInitFlag)
	{
	profError = PROF_ERROR_NOTINIT;
	return (-1);
	}

profError = PROF_ERROR_NONE;

if ((fp = fopen(pFile,"r")) == NULL)
	{
	profError = PROF_ERROR_OPENFILE;
	return (-1);
	}

strcpy(achName,"/tmp/prof.XXXXXXX");
pName = mktemp(achName);

if ((fpTemp = fopen(pName,"w")) == NULL)
	{
	profError = PROF_ERROR_WRITEFILE;
	fclose(fp);
	return (-1);
	}

sprintf(achSearch,"%s=", pEntry);
offs = findOffset(fp, achSearch, &slen);

rewind(fp);

copyfile(fpTemp, fp, offs);
fprintf(fpTemp,"%s=\"%s\"", pEntry, pString);

fseek(fp, slen, SEEK_CUR);

if (!copyfile(fpTemp, fp, -1))
	fputc('\n', fpTemp);

fclose(fp);
fclose(fpTemp);

if ((fp = fopen(pFile,"w")) == NULL)
	{
	profError = PROF_ERROR_WRITEFILE;
	return (-1);
	}

if ((fpTemp = fopen(pName,"r")) == NULL)
	{
	profError = PROF_ERROR_OPENFILE;
	fclose(fp);
	return (-1);
	}

copyfile(fp, fpTemp, -1);

fclose(fp);
fclose(fpTemp);

unlink(pName);

return (0);
}

u_int profGetLastError(void)
{
register u_int profErrorTemp;

profErrorTemp = profError;
profError     = 0;

return (profErrorTemp);
}

/* We are enforcing that profInit() is called before
   any other module function, eventhough the profInit()
   and profShutdown() are merely stubs. This may change
   in the future when we may use memory to update
   configuration files instead of using expensive
   disk I/O.
*/
u_int profInit(void)
{
profInitFlag = 1;
return (0);
}

u_int profShutdown(void)
{
if (!profInitFlag)
	{
	profError = PROF_ERROR_NOTINIT;
	return (-1);
	}

profInitFlag = 0;

return (0);
}


/* local (internal) functions */
static u_short copyfile(FILE *fpDest, FILE *fpSrc, u_int len)
{
int 	ch;
int	count;

/* simple, but works.
   may want to substitute something more efficient later
*/

count = 0;
while ((ch = fgetc(fpSrc)) != EOF && len--)
	{
	++count;
	fputc(ch, fpDest);
	}

return (count);
}

static u_short findOffset(FILE *fp, char *pString, u_short *slen)
{
char	achLine[PROF_MAXLINE];
char	achTemp[PROF_MAXLINE];
int	cnt, len, count, ch;

cnt 	= 0;
count	= 0;
len 	= strlen(pString);

while ((ch = fgetc(fp)) != EOF)
	{
	if (cnt < len)
		achLine[cnt++] = ch;
	else	{
		/* a crude FIFO queue */
		memcpy(&achTemp[0], &achLine[1], len-1);
		memcpy(&achLine[0], &achTemp[0], len-1);

		achLine[len-1] = ch;
		achLine[len] = '\0';

		if ((strcasecmp(achLine, pString)) == 0)
			{
			*slen = len + 1;
			while ((ch = fgetc(fp)) != PROF_CH_DQUOTE && ch != PROF_CH_SQUOTE)
				(*slen)++;
			while ((ch = fgetc(fp)) != PROF_CH_DQUOTE && ch != PROF_CH_SQUOTE)
				(*slen)++;

			return (count - len + 1);
			}
		}
	++count;
	}

return (-1);
}

static u_short strcpymax(char *pDest, char *pSource, u_short maxlen)
{
u_short	srclen, len;

if (pSource == (char *)NULL)
	return (0);

srclen = strlen(pSource);
len    = (srclen < maxlen) ? srclen : maxlen;

strncpy(pDest, pSource, len);
pDest[len] = '\0';

return (len);
}

static u_short _getline(FILE *fp, char *pBuffer, u_short usBuflen, u_short type)
{
int	ch;
u_short	cnt;
int	flag;
int	sflag;

cnt 	= 0;
flag 	= 0;
sflag   = 1;

while ((ch = fgetc(fp)) != EOF)
	{
	switch (ch)
		{
		case PROF_CH_TAB:
		case PROF_CH_SPACE:
			if (flag || (type && sflag))
				{
				sflag = 0;
				if (cnt < usBuflen)
					pBuffer[cnt++] = PROF_CH_SPACE;
				}
			else	{
				while ((ch = fgetc(fp)) == PROF_CH_TAB || ch == PROF_CH_SPACE)
					;

				if (ch != EOF)
					ungetc(ch, fp);
				sflag = 1;
				}
			break;

		case PROF_CH_DQUOTE:
		case PROF_CH_SQUOTE:
			flag = !flag;
			break;

		case PROF_CH_COMMENT:
			while ((ch = fgetc(fp)) != PROF_CH_NEWLINE && ch != EOF)
					;
			if (ch != EOF)
				ungetc(ch, fp);
			break;

		case PROF_CH_NEWLINE:
			if (cnt)
				{
				pBuffer[cnt] = '\0';
				return (cnt);
				}

			break;

		case EOF:
			break;

		default:
			if (cnt < usBuflen)
				pBuffer[cnt++] = ch;
			break;
		}
	}
pBuffer[cnt] = '\0';

return (cnt);
}
