#ifndef CRC32_H
#define CRC32_H

/* $Id: crc32.h,v 1.6 2005/11/07 11:15:09 gleixner Exp $ */

#include <stdint.h>

extern const uint32_t crc32_table[256];

/* Return a 32-bit CRC of the contents of the buffer. */

static inline uint32_t
crc32(uint32_t val, const void *ss, int len)
{
	const unsigned char *s = ss;
        while (--len >= 0)
                val = crc32_table[(val ^ *s++) & 0xff] ^ (val >> 8);
        return val;
}

#endif
