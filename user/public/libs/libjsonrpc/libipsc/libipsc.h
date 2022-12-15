/**
 * This file is part of libipsc library code.
 *
 * Copyright (C) 2014 Roman Yeryomin <roman@advem.lv>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENCE.txt file for more details.
 */
#ifndef _LIBIPSC_H_
#define _LIBIPSC_H_

#include <arpa/inet.h>
#include <sys/socket.h>
#include <openssl/ssl.h>

#define IPSC_HOST_LOCAL		NULL
#define IPSC_MAX_QUEUE		65535
#define IPSC_MAX_QUEUE_DEFAULT	16
/* ipsc connection flags */
#define IPSC_FLAG_SERVER	0x01
#define IPSC_FLAG_LOCAL		0x02
#define IPSC_FLAG_TLS		0x04

typedef struct ipsc_tls_t {
	SSL_CTX *ctx;
	SSL *data;
} ipsc_tls_t;

typedef struct ipsc_t {
	int sd;			/* socket descriptor */
	int maxq;		/* max queue */
	int flags;		/* flags */
	int alen;		/* size of address structure pointed by addr */
	struct sockaddr *addr;	/* address */
	void *cb_args;		/* ipsc_epoll_wait() callback args */
	ipsc_tls_t *tls;
} ipsc_t;

#ifdef __SC_BUILD__
int ipsc_tls_init( ipsc_t *ipsc, char *psk);
#else
int ipsc_tls_init( ipsc_t *ipsc, char *cert, char *key, char *ca );
#endif
ipsc_t *ipsc_listen( int st, int proto, char *host, uint16_t port, int maxq );
ipsc_t *ipsc_accept( ipsc_t *ipsc );
int ipsc_accept_tls( ipsc_t *sipsc, ipsc_t *cipsc );
ipsc_t *ipsc_connect( int st, int proto, char *host, uint16_t port );
int ipsc_connect_tls( ipsc_t *ipsc );
ssize_t ipsc_send( ipsc_t *ipsc, const void *buf, size_t buflen );
ssize_t ipsc_recv( ipsc_t *ipsc, void *buf,
		   size_t buflen, unsigned int timeout );
int ipsc_epoll_init( ipsc_t *ipsc );
int ipsc_epoll_wait( ipsc_t *ipsc, int epfd, ssize_t (*cb)(ipsc_t *ipsc) );
void ipsc_close( ipsc_t *ipsc );

#endif /* _LIBIPSC_H_ */
