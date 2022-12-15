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
#include "priv.h"

inline int ipsc_set_nonblock( ipsc_t *ipsc )
{
	int opts = fcntl( ipsc->sd, F_GETFL );
	if ( opts <= 0 )
		return -1;

	opts |= O_NONBLOCK;
	if ( fcntl( ipsc->sd, F_SETFL, opts ) < 0 )
		return -1;

	return 0;
}

inline int ipsc_set_recv_timeout( ipsc_t *ipsc, unsigned int to )
{
	struct timeval tv;

	tv.tv_sec  = to / 1000;
	tv.tv_usec = (to%1000) * 1000;

	if ( setsockopt( ipsc->sd, SOL_SOCKET, SO_RCVTIMEO,
			 (char *)&tv, sizeof tv ) )
		return -1;

	return 0;
}

int ipsc_addr_un( ipsc_t **ipsc, uint16_t port )
{
	(*ipsc)->flags |= IPSC_FLAG_LOCAL;
	(*ipsc)->alen   = sizeof(struct sockaddr_un);
	(*ipsc)->addr   = (struct sockaddr *)malloc( (*ipsc)->alen );
	if ( !(*ipsc)->addr )
		return -1;

	((struct sockaddr_un *)(*ipsc)->addr)->sun_family = AF_LOCAL;
	snprintf( ((struct sockaddr_un *)(*ipsc)->addr)->sun_path,
		  sizeof(((struct sockaddr_un *)(*ipsc)->addr)->sun_path),
		  IPSC_SOCKET_FILE, port );

	return 0;
}

int ipsc_addr_in( ipsc_t **ipsc, char *host, uint16_t port )
{
	in_addr_t ipaddr;
	if ( !inet_aton( host, (struct in_addr *)&ipaddr ) )
		return -1;

	(*ipsc)->alen = sizeof(struct sockaddr_in);
	(*ipsc)->addr = (struct sockaddr *)malloc( (*ipsc)->alen );
	if ( !(*ipsc)->addr )
		return -1;

	((struct sockaddr_in *)(*ipsc)->addr)->sin_family      = AF_INET;
	((struct sockaddr_in *)(*ipsc)->addr)->sin_port        = htons(port);
	((struct sockaddr_in *)(*ipsc)->addr)->sin_addr.s_addr = ipaddr;

	return 0;
}

int ipsc_addr( ipsc_t **ipsc, char *host, uint16_t port )
{
	if ( !host )
		return ipsc_addr_un( ipsc, port );

	return ipsc_addr_in( ipsc, host, port );
}

ipsc_t *ipsc_init( int st, int proto, char *host, uint16_t port )
{
	int on = 1;
	int domain = PF_INET;

	ipsc_t *ipsc = (ipsc_t *)malloc( sizeof(ipsc_t) );
	if ( !ipsc )
		return NULL;

	ipsc->sd      = -1;
	ipsc->maxq    = 0;
	ipsc->flags   = 0;
	ipsc->alen    = 0;
	ipsc->addr    = NULL;
	ipsc->cb_args = NULL;
	ipsc->tls     = NULL;

	if ( ipsc_addr( &ipsc, host, port ) )
		goto exit;

	if ( ipsc->flags & IPSC_FLAG_LOCAL )
		domain = PF_LOCAL;

	ipsc->sd = socket( domain, st, proto );
	if ( ipsc->sd == -1 )
		goto exit;

	if ( !(ipsc->flags & IPSC_FLAG_LOCAL) )
		setsockopt( ipsc->sd, SOL_SOCKET, SO_REUSEADDR,
						&on, sizeof(on) );
	if ( proto == IPPROTO_TCP )
		setsockopt( ipsc->sd, IPPROTO_TCP, TCP_NODELAY,
						&on, sizeof(on) );
	return ipsc;

exit:
	ipsc_close( ipsc );
	return NULL;
}

int ipsc_bind( ipsc_t *ipsc )
{
	if ( !bind( ipsc->sd, ipsc->addr, ipsc->alen ) )
		return 0;

	if ( !(ipsc->flags & IPSC_FLAG_LOCAL) || errno != EADDRINUSE )
		return -1;

	/* is there somebody using that socket already...? */
	if ( !connect( ipsc->sd, ipsc->addr, ipsc->alen) )
		return -1;

	/* ...seems not, nuke it */
	unlink( ((struct sockaddr_un *)ipsc->addr)->sun_path );

	/* try to bind again */
	if ( bind( ipsc->sd, ipsc->addr, ipsc->alen ) )
		return -1;

	return 0;
}

int ipsc_epoll_newfd( ipsc_t *ipsc, int epfd )
{
	struct epoll_event ev;

	ev.data.u64 = 0;
	ev.data.ptr = ipsc;
	ev.events   = EPOLLIN | EPOLLPRI | EPOLLET | EPOLLRDHUP;

	if ( epoll_ctl( epfd, EPOLL_CTL_ADD, ipsc->sd, &ev ) )
		return -1;

	return 0;
}
