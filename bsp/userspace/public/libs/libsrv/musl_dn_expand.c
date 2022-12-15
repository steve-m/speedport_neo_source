#include "libsrv.h"

/*
  The below code is taken from "musl" C standard library, file

        musl/src/network/dn_expand.c

  in the musl source tree. For more information on this project, point your
  web browser at http://www.musl-libc.org/. Official repository URL:

        git://git.musl-libc.org/musl

  Last change in the above file by commit

        commit 49d2c8c6bcf8c926e52c7f510033b6adc31355f5
        Author: Szabolcs Nagy <nsz@port70.net>
        Date:   Thu Sep 4 18:29:16 2014 +0200

            fix dn_expand empty name handling and offsets to 0

  The "COPYRIGHT" file file under root of the source treee specifies the
  following license in general and indicates no exception for this portion
  of the library:


     musl  as a whole is licensed under the following standard MIT license:

     ----------------------------------------------------------------------
     Copyright © 2005-2014 Rich Felker, et al.

     Permission is hereby granted, free of charge, to any person obtaining
     a copy of this software and associated documentation files (the
     "Software"), to deal in the Software without restriction, including
     without limitation the rights to use, copy, modify, merge, publish,
     distribute, sublicense, and/or sell copies of the Software, and to
     permit persons to whom the Software is furnished to do so, subject to
     the following conditions:

     The above copyright notice and this permission notice shall be
     included in all copies or substantial portions of the Software.

     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
     EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
     SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
int musl__dn_expand(const unsigned char *base, const unsigned char *end, const unsigned char *src, char *dest, int space)
{
	const unsigned char *p = src;
	char *dend, *dbegin = dest;
	int len = -1, i, j;
	if (p==end || space <= 0) return -1;
	dend = dest + (space > 254 ? 254 : space);
	/* detect reference loop using an iteration counter */
	for (i=0; i < end-base; i+=2) {
		/* loop invariants: p<end, dest<dend */
		if (*p & 0xc0) {
			if (p+1==end) return -1;
			j = ((p[0] & 0x3f) << 8) | p[1];
			if (len < 0) len = p+2-src;
			if (j >= end-base) return -1;
			p = base+j;
		} else if (*p) {
			if (dest != dbegin) *dest++ = '.';
			j = *p++;
			if (j >= end-p || j >= dend-dest) return -1;
			while (j--) *dest++ = *p++;
		} else {
			*dest = 0;
			if (len < 0) len = p+1-src;
			return len;
		}
	}
	return -1;
}
