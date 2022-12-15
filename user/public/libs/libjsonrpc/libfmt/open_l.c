/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>
#include <errno.h>

#include "base.h"

int lock_init( lock_t *lock, pthread_mutex_t *lock_mutex )
{
	if ( !lock )
		return LIBASE_ERR_GENERIC;

	lock->mutex = lock_mutex;

	return LIBASE_ERR_NONE;
}

inline int file_lock_flock_nonblock( int retry, unsigned int timeout,
								lock_t *lock )
{
	int i;
	int err = LIBASE_ERR_GENERIC;

	for ( i = 0; i < retry; i++ ) {
		if ( lock->mutex ) {
			err = pthread_mutex_trylock( lock->mutex );
			if ( err ) {
				usleep(timeout);
				continue;
			}
		}
		err = flock( lock->fd, LOCK_EX | LOCK_NB );
		if ( err ) {
			if ( lock->mutex )
				pthread_mutex_unlock( lock->mutex );
			usleep(timeout);
			continue;
		}
		break;
	}

	if ( err ) {
		if ( lock->mutex )
			pthread_mutex_unlock( lock->mutex );
		flock( lock->fd, LOCK_UN );
		errno = EWOULDBLOCK;
		return LIBASE_ERR_LOCK_WOULDBLOCK;
	}

	return LIBASE_ERR_NONE;
}

inline int file_lock_flock( lock_t *lock )
{
	int err = LIBASE_ERR_GENERIC;

	if ( lock->mutex ) {
		err = pthread_mutex_lock( lock->mutex );
		if ( err )
			return LIBASE_ERR_LOCK_LOCK;
	}

	err = flock( lock->fd, LOCK_EX );
	if ( err ) {
		if ( lock->mutex )
			pthread_mutex_unlock( lock->mutex );
		return LIBASE_ERR_LOCK_LOCK;
	}

	return LIBASE_ERR_NONE;
}

int file_lock( int retry, unsigned int timeout, lock_t *lock )
{
	if ( !lock )
		return LIBASE_ERR_GENERIC;

	if ( retry < 0 )
		return file_lock_flock( lock );

	if ( retry < 1 )
		retry = LIBASE_LOCK_RETRY_DEF;

	if ( retry > LIBASE_LOCK_RETRY_MAX )
		retry = LIBASE_LOCK_RETRY_MAX;

	if ( timeout < 1 )
		timeout = LIBASE_LOCK_TIMEOUT_DEF;

	if ( timeout > LIBASE_LOCK_TIMEOUT_MAX )
		timeout = LIBASE_LOCK_TIMEOUT_MAX;

	return file_lock_flock_nonblock( retry, timeout, lock );
}

int file_unlock( lock_t *lock )
{
	if ( !lock )
		return LIBASE_ERR_GENERIC;

	/* flock is released automagically on close */
	if ( lock->fd > 0 )
		// flock( lock->fd, LOCK_UN );
		close( lock->fd );

	if ( lock->mutex )
		pthread_mutex_unlock( lock->mutex );

	return LIBASE_ERR_NONE;
}

int open_l( const char *path, int flags, mode_t mode,
					int retry, unsigned int timeout,
					lock_t *lock )
{
	if ( !path || !lock )
		return LIBASE_ERR_GENERIC;

	int lockflags = flags;
	if ( flags & O_TRUNC )
		lockflags = flags & ~O_TRUNC;

	lock->fd = open( path, lockflags, mode );
	if ( lock->fd < 0 )
		return LIBASE_ERR_GENERIC;

	int err = file_lock( retry, timeout, lock );
	if ( err ) {
		close( lock->fd );
		return err;
	}

	if ( flags & O_TRUNC ) {
		if ( lseek( lock->fd, 0, SEEK_SET ) < 0 ) {
			file_unlock( lock );
			return LIBASE_ERR_GENERIC;
		}
		err = ftruncate( lock->fd, 0 );
		if ( err < 0 ) {
			file_unlock( lock );
			return LIBASE_ERR_GENERIC;
		}
	}

	return lock->fd;
}

int close_l( int fd, lock_t *lock )
{
	if ( fd < 0 || !lock )
		return LIBASE_ERR_GENERIC;

	int err = close( fd );

	lock->fd = -1;
	if ( file_unlock( lock ) )
		return LIBASE_ERR_LOCK_UNLOCK;

	if ( err )
		return LIBASE_ERR_LOCK_CLOSE;

	return LIBASE_ERR_NONE;
}

FILE *fopen_l( const char *path, const char *mode,
					int retry, unsigned int timeout,
					lock_t *lock )
{
	if ( !path || !mode || !lock )
		return NULL;

	int flags = O_RDONLY;
	/* TODO: read umask and calculate correct lockmode */
	mode_t lockmode = 0640;

	if ( mode[1] == '+' )
		flags = O_RDWR;

	if ( mode[0] == 'w' ) {
		if ( mode[1] != '+' )
			flags = O_WRONLY;
		flags |= O_CREAT;
	} else if ( mode[0] == 'a' ) {
		if ( mode[1] != '+' )
			flags = O_WRONLY;
		flags |= O_APPEND | O_CREAT;
	}

	flags |= O_CLOEXEC;

	lock->fd = open( path, flags, lockmode );
	if ( lock->fd < 0 )
		return NULL;

	int err = file_lock( retry, timeout, lock );
	if ( err ) {
		close( lock->fd );
		return NULL;
	}

	if ( mode[0] == 'w' ) {
		lseek( lock->fd, 0, SEEK_SET );
		err = ftruncate( lock->fd, 0 );
		if ( err < 0 ) {
			file_unlock( lock );
			return NULL;
		}
	}// else if ( mode[0] == 'a' )
	//	lseek( lock->fd, 0, SEEK_END );

	FILE *truefp = fdopen( lock->fd, mode );
	if ( !truefp ) {
		file_unlock( lock );
		return NULL;
	}

	return truefp;
}

int fclose_l( FILE *fp, lock_t *lock )
{
	if ( !fp || !lock )
		return LIBASE_ERR_GENERIC;

	int err = fclose( fp );

	lock->fd = -1;
	if ( file_unlock( lock ) )
		return LIBASE_ERR_LOCK_UNLOCK;

	if ( err )
		return LIBASE_ERR_LOCK_CLOSE;

	return LIBASE_ERR_NONE;
}

/*
 * This functions grows (reallocs) a buffer in an efficient way described here:
 * http://doc.qt.digia.com/4.6/containers.html#growth-strategies
 *
 * It also cares about allocation failures: the previous buffer is freed (and
 * gone) in case the reallocation fails.
 */
void *mgrow(void *ptr, size_t *size)
{
	if (*size <= 16)
		*size += 4;
	else if (*size < 4084)
		*size *= 2;
	else
		*size += 2048;

	void *new_ptr = realloc(ptr, *size);
	if (!new_ptr) {
		free(ptr);
		*size = 0;
	}

	return new_ptr;
}
