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
 *      @(#)opt.c      1.0 (CanWeb) 19/6/98                      *
 *      $Id: opt.c,v 1.0 1998/6/19 13:15:01 sae Exp $            *
 */

/*
Option string can consist of the following characters:

-<option>	Indicates that the argument <option> can be
		used in conjunction with other arguments
+<option>	Indicates that this argument can only be used
		by itself
:		Indicates that an option requires one additional
		argument
::		Indicates that an option may have one additional
		argument

*		Indicates that an option may have one ore more
		required additional arguments. Use one '*' for
		each required argument.

@		Indicates that an option may have one or more
		optional arguments.

<+|-><option>

For example,

+r*****@@@	Indicates that the '-r' option can only occur
		by itself (i.e., no other options are permitted)
		and has 5 mandatory arguments and up to three
		optional arguments.
*/

#include <stdio.h>
#include <string.h>
#include "opt.h"

static int	optindex;
static int	argcount;
static int	init = 0;
static int	argc;

static char	**argv;
static char	*optstring;

static int	optionSearch(char, char *, int *, int *);

int optInitialize(int ac, char **av, char *optstr)
{
OPTION	option;
int	ret;

if (init)
	return (OPT_ERROR_INIT);

argc		= ac;
argv		= av;
argcount	= 0;
optstring       = optstr;
init		= 1;
optindex	= 1;

/* we should be checking if the arguments are valid */

do {
   ret = optGetOption(&option);
   optReleaseOption(&option);
   } while (ret == OPT_ERROR_NONE);

argcount	= 0;
optindex	= 1;

return ((ret == OPT_ERROR_EOF) ? (argc == 1) ? OPT_ERROR_NOOPTIONS : OPT_ERROR_NONE : ret);
}

int optGetOption(OPTION *pOption)
{
int	cnt,count,ret,reqArgs,optArgs;
char	*ptr;

if (pOption == (OPTION *)NULL)
	return (OPT_ERROR_INPUTVAL);

pOption->cArguments = 0;

for (cnt = 0; cnt < OPT_MAXARGUMENTS; cnt++)
	pOption->args[cnt] = NULL;

if (optindex < argc)
	{
	/* check if it has a leading dash (-) */
	if (argv[optindex][0] != '-')
		{
		pOption->cOption =  argv[optindex][0];

		++optindex;
		return (OPT_ERROR_FORMAT);
		}

	/* check if it appears in our option string */
	if ((ret = optionSearch(argv[optindex][1], optstring, &reqArgs, &optArgs)) == -1)
		{
		pOption->cOption = argv[optindex][1];

		++optindex;
		return (OPT_ERROR_OPTION_NOTDEFINED);
		}

	if ((argc - optindex) < reqArgs)
		{
		pOption->cOption = optstring[ret];

		++optindex;
		return (OPT_ERROR_MISSING_ARGUMENTS);
		}

	count		    = 0;
	pOption->cArguments = 0;
	pOption->cOption    = optstring[ret];

	for (cnt = 0; cnt < reqArgs; cnt++)
		if (++optindex < argc && argv[optindex][0] != '-')
			{
			if (count < OPT_MAXARGUMENTS)
				if ((ptr = (char *)malloc(strlen(argv[optindex])+1)) != NULL)
					{
					strcpy(ptr, argv[optindex]);
					pOption->args[count++] = ptr;
					pOption->cArguments++;
					}
			}
		else return (OPT_ERROR_MISSING_ARGUMENTS);

	for (cnt = 0; cnt < optArgs; cnt++)
		if (++optindex < argc && argv[optindex][0] != '-')
			{
			if (count < OPT_MAXARGUMENTS)
				if ((ptr = (char *)malloc(strlen(argv[optindex])+1)) != NULL)
					{
					strcpy(ptr, argv[optindex]);
					pOption->args[count++] = ptr;
					pOption->cArguments++;
					}
			}

	if (optstring[ret-1] == '+')
		{ /* no other arguments allowed */
		if (argcount)
			return (OPT_ERROR_EXCLUSIVE_OPTION);

		for (cnt = optindex+1; cnt < argc; cnt++)
			if (argv[cnt][0] == '-')
				return (OPT_ERROR_EXCLUSIVE_OPTION);
		}

	++optindex;
	++argcount;

	return (OPT_ERROR_NONE);
	}

return (OPT_ERROR_EOF);
}

int optReleaseOption(OPTION *pOption)
{
int	cnt;

if (pOption == (OPTION *)NULL)
	return (OPT_ERROR_INPUTVAL);

for (cnt = 0; cnt < pOption->cArguments; cnt++)
	if (pOption->args[cnt] != NULL)
		{
		free(pOption->args[cnt]);
		pOption->args[cnt] = NULL;
		}

pOption->cArguments = 0;

return (OPT_ERROR_NONE);
}

static int optionSearch(char cOption, char *pOptStr, int *iRequiredArgs, int *iOptionalArgs)
{
int	cnt,count,len;

len = strlen(pOptStr);
cnt = 0;

if (iRequiredArgs != NULL)
	*iRequiredArgs = 0;

if (iOptionalArgs != NULL)
	*iOptionalArgs = 0;

for (cnt = 0; cnt < len; cnt++)
	if (pOptStr[cnt] == cOption)
		{
		count = cnt;
		cnt++;

		while (cnt < len && pOptStr[cnt] != '+' && pOptStr[cnt] != '-')
			switch (pOptStr[cnt++])
				{
				case ':':
					if (pOptStr[cnt] == ':')
						{
						if (iOptionalArgs != NULL)
							(*iOptionalArgs)++;
						}
					else	{
						if (iRequiredArgs != NULL)
							(*iRequiredArgs)++;
						}
					break;

				case '*':
					if (iRequiredArgs != NULL)
						(*iRequiredArgs)++;
					break;

				case '@':
					if (iOptionalArgs != NULL)
						(*iOptionalArgs)++;
					break;

				default:
					break;
				}
		return (count);
		}
return (-1);
}

int optShutdown(void)
{
if (!init)
	return (OPT_ERROR_INIT);

init		= 0;
return (OPT_ERROR_NONE);
}
