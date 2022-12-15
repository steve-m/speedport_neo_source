/* 
   Unix SMB/Netbios implementation.
   Version 1.9.
   SMB parameters and setup
   Copyright (C) Andrew Tridgell 1992-1998
   Modified by Jeremy Allison 1995.
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#define DEBUG(a,b) ;

extern int DEBUGLEVEL;

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "smbbyteorder.h"
#include "smbdes.h"
#include "smbencrypt.h"
#include "smbmd4.h"

#ifndef _AIX
typedef unsigned char uchar;
typedef signed short int16;
#endif
typedef int BOOL;
#define False 0
#define True  1

/****************************************************************************
 Like strncpy but always null terminates. Make sure there is room!
 The variable n should always be one less than the available size.
****************************************************************************/

static char *StrnCpy(char *dest,const char *src, size_t n)
{
  char *d = dest;
  if (!dest) return(NULL);
  if (!src) {
    *dest = 0;
    return(dest);
  }
  while (n-- && (*d++ = *src++)) ;
  *d = 0;
  return(dest);
}

static size_t skip_multibyte_char(char c)
{
    (void)c;
    return 0;
}


/*******************************************************************
safe string copy into a known length string. maxlength does not
include the terminating zero.
********************************************************************/

static void strupper(char *s)
{
while (*s)
  {
    {
    size_t skip = skip_multibyte_char( *s );
    if( skip != 0 )
      s += skip;
    else
      {
      if (islower((unsigned char)*s))
	*s = toupper((unsigned char)*s);
      s++;
      }
    }
  }
}

extern void SMBOWFencrypt(uchar passwd[16], uchar *c8, uchar p24[24]);

/*
 This implements the X/Open SMB password encryption
 It takes a password, a 8 byte "crypt key" and puts 24 bytes of 
 encrypted password into p24 
 */

void SMBencrypt(uchar *passwd, uchar *c8, uchar *p24)
  {
  uchar p14[15], p21[21];
  
  memset(p21,'\0',21);
  memset(p14,'\0',14);
  StrnCpy((char *)p14,(char *)passwd,14);
  
  strupper((char *)p14);
  E_P16(p14, p21); 
  
  SMBOWFencrypt(p21, c8, p24);
  
#ifdef DEBUG_PASSWORD
  DEBUG(100,("SMBencrypt: lm#, challenge, response\n"));
  dump_data(100, (char *)p21, 16);
  dump_data(100, (char *)c8, 8);
  dump_data(100, (char *)p24, 24);
#endif
  }

/* Routines for Windows NT MD4 Hash functions. */
static int _my_wcslen(int16 *str)
{
	int len = 0;
	while(*str++ != 0)
		len++;
	return len;
}

/*
 * Convert a string into an NT UNICODE string.
 * Note that regardless of processor type 
 * this must be in intel (little-endian)
 * format.
 */
 
static int _my_mbstowcs(int16 *dst, uchar *src, int len)
{
	int i;
	int16 val;
 
	for(i = 0; i < len; i++) {
		val = *src;
		SSVAL(dst,0,val);
		dst++;
		src++;
		if(val == 0)
			break;
	}
	return i;
}

/* 
 * Creates the MD4 Hash of the users password in NT UNICODE.
 */
 
static void E_md4hash(uchar *passwd, uchar *p16)
{
	int len;
	int16 wpwd[129];
	
	/* Password cannot be longer than 128 characters */
	len = strlen((char *)passwd);
	if(len > 128)
		len = 128;
	/* Password must be converted to NT unicode */
	_my_mbstowcs(wpwd, passwd, len);
	wpwd[len] = 0; /* Ensure string is null terminated */
	/* Calculate length in bytes */
	len = _my_wcslen(wpwd) * sizeof(int16);

	mdfour(p16, (unsigned char *)wpwd, len);
}

/* Does the des encryption from the NT or LM MD4 hash. */
void SMBOWFencrypt(uchar passwd[16], uchar *c8, uchar p24[24])
{
	uchar p21[21];
 
	memset(p21,'\0',21);
 
	memcpy(p21, passwd, 16);    
	E_P24(p21, c8, p24);
}

/* Does the NT MD4 hash then des encryption. */
 
void SMBNTencrypt(uchar *passwd, uchar *c8, uchar *p24)
{
	uchar p21[21];
 
	memset(p21,'\0',21);
 
	E_md4hash(passwd, p21);    
	SMBOWFencrypt(p21, c8, p24);

#ifdef DEBUG_PASSWORD
	DEBUG(100,("SMBNTencrypt: nt#, challenge, response\n"));
	dump_data(100, (char *)p21, 16);
	dump_data(100, (char *)c8, 8);
	dump_data(100, (char *)p24, 24);
#endif
}

#if 0

BOOL make_oem_passwd_hash(char data[516], const char *passwd, uchar old_pw_hash[16], BOOL unicode)
{
	int new_pw_len = strlen(passwd) * (unicode ? 2 : 1);

	if (new_pw_len > 512)
	{
		DEBUG(0,("make_oem_passwd_hash: new password is too long.\n"));
		return False;
	}

	/*
	 * Now setup the data area.
	 * We need to generate a random fill
	 * for this area to make it harder to
	 * decrypt. JRA.
	 */
	generate_random_buffer((unsigned char *)data, 516, False);
	if (unicode)
	{
		struni2( &data[512 - new_pw_len], passwd);
	}
	else
	{
		fstrcpy( &data[512 - new_pw_len], passwd);
	}
	SIVAL(data, 512, new_pw_len);

#ifdef DEBUG_PASSWORD
	DEBUG(100,("make_oem_passwd_hash\n"));
	dump_data(100, data, 516);
#endif
	SamOEMhash( (unsigned char *)data, (unsigned char *)old_pw_hash, True);

	return True;
}

#endif
