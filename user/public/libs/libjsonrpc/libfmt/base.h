/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <pthread.h>

#include "macros.h"

#define LIBASE_ERR_NONE			0
#define LIBASE_ERR_GENERIC		-1
#define LIBASE_ERR_LOCK_CLOSE		-10
#define LIBASE_ERR_LOCK_UNLOCK		-11
#define LIBASE_ERR_LOCK_LOCK		-12
#define LIBASE_ERR_LOCK_WOULDBLOCK	-13

#define LIBASE_LOCK_BLOCKING		-1
#define LIBASE_LOCK_RETRY_DEF		3
#define LIBASE_LOCK_RETRY_MAX		100
#define LIBASE_LOCK_TIMEOUT_DEF		100     // usec
#define LIBASE_LOCK_TIMEOUT_MAX		1000000 // usec
#define LIBASE_LOCK_ACCESS_MODE		0640

#ifndef O_CLOEXEC
#define O_CLOEXEC	02000000
#endif

enum {
	FILE_LOCK_FILE,
	FILE_LOCK_SEM,
	FILE_LOCK_FLOCK
};

typedef struct lock_t {
	int fd;
	pthread_mutex_t *mutex;
} lock_t;

int lock_init( lock_t *lock, pthread_mutex_t *lock_mutex );

/* Close locked file */
int close_l( int fd, lock_t *lock );
/* Open file with locking, by default it uses nonblocking mode
 * but blocking mode can be enabled giving LIBASE_LOCK_BLOCKING as retry */
int open_l( const char *path, int flags, mode_t mode,
					int retry, unsigned int timeout,
					lock_t *lock );

int fclose_l( FILE *fp, lock_t *lock );
FILE *fopen_l( const char *path, const char *mode,
					int retry, unsigned int timeout,
					lock_t *lock );

void *mgrow(void *ptr, size_t *size);

/* SipHash is a family of pseudorandom functions
 * see https://131002.net/siphash/siphash.pdf for details */
uint64_t siphash24( const void *buf, unsigned long len, const char key[16] );

#endif