/*
 * Access and get random values from /dev/urandom
 *
 * This file is part of FONUCS. Copyright (C) 2007 Fon Wireless Ltd.
 *
 * Created: 20070407 Pablo Martín Medrano <pablo@fon.com>
 * 
 * $Id: urandom.h 312 2007-04-18 09:15:19Z pablo.martin $
 */
#ifndef __URANDOM_H__
#define __URANDOM_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	UR_OK = 0,
	UR_OPEN = 1,
	UR_READ = 2,
	UR_OVERFLOW = 3
} UR_ERROR;

typedef void * UR_HANDLE;

UR_HANDLE UR_start();
UR_ERROR UR_get(UR_HANDLE handle, char *buffer, size_t size); 
UR_ERROR UR_stop(UR_HANDLE handle);

#ifdef __cplusplus
}
#endif
#endif

