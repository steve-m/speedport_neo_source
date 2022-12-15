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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include <sys/un.h>
#include <sys/epoll.h>
#include <netinet/tcp.h>

#include "libipsc.h"

#define IPSC_SOCKET_FILE	"/tmp/ipsc-%i.sock"

extern inline int ipsc_set_nonblock( ipsc_t *ipsc );
extern inline int ipsc_set_recv_timeout( ipsc_t *ipsc, unsigned int to );
extern int ipsc_addr_un( ipsc_t **ipsc, uint16_t port );
extern int ipsc_addr_in( ipsc_t **ipsc, char *host, uint16_t port );
extern int ipsc_addr( ipsc_t **ipsc, char *host, uint16_t port );
extern ipsc_t *ipsc_init( int st, int proto, char *host, uint16_t port );
extern int ipsc_bind( ipsc_t *ipsc );
extern int ipsc_epoll_newfd( ipsc_t *ipsc, int epfd );
