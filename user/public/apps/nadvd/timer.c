/*
 *
 *   Authors:
 *    Pedro Roque		<roque@di.fc.ul.pt>
 *    Lars Fenneberg		<lf@elemental.net>
 *
 *   This software is Copyright 1996-2000 by the above mentioned author(s),
 *   All Rights Reserved.
 *
 *   The license which is distributed with this software in the file COPYRIGHT
 *   applies to this software. If your distribution is missing this file, you
 *   may request it from <pekkas@netcore.fi>.
 *
 */

#include "radvd.h"

struct timespec
next_timespec(double next)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	ts.tv_sec += (int)next;
	ts.tv_nsec += 1000000000 * (next - (int)next);
	return ts;
}

int
timespecdiff(struct timespec const *a, struct timespec const *b)
{
	int msec;
	msec = (a->tv_sec - b->tv_sec) * 1000;
	msec += (a->tv_nsec - b->tv_nsec) / 1000000;
	return msec;
}

/* Returns when the next time should expire in milliseconds. */
int
next_time_msec_na(struct Interface const * iface)
{
	struct timespec ts;
	int retval;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	retval = timespecdiff(&iface->next_multicast_na, &ts);
	return retval >= 1? retval : 1;
}

int
expired(struct Interface const * iface)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	if(timespecdiff(&iface->next_multicast, &ts) > 0)
		return 0;
	return 1;
}

