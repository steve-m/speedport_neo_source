/* $Id: hash.h 312 2007-04-18 09:15:19Z pablo.martin $ */
#ifndef _INCLUDED_HASH_H
#define _INCLUDED_HASH_H
#ifdef __cplusplus
extern "C" {
#endif
unsigned int hash(unsigned char *k, unsigned int length, unsigned int initval);
#ifdef __cplusplus
}
#endif
#endif
