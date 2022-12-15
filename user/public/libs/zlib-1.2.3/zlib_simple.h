
#ifndef _ZLIB_SIMPLE_H_
#define _ZLIB_SIMPLE_H_
#include "zconf.h"

/*
typedef unsigned char  Byte;  // 8 bits 
typedef unsigned int   uInt;  // 16 bits or more 
typedef unsigned long  uLong; // 32 bits or more 
*/

/* Return codes for the compression/decompression functions. Negative
 * values are errors, positive values are used for special but normal events.
 */
#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO        (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR   (-3)
#define Z_MEM_ERROR    (-4)
#define Z_BUF_ERROR    (-5)
#define Z_VERSION_ERROR (-6)



int compress (Bytef * dest, uLongf * destLen, const Bytef * source, uLong sourceLen);
int uncompress (Bytef * dest, uLongf * destLen, const Bytef * source, uLong sourceLen);


#endif // _ZLIB_SIMPLE_H_

