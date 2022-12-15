/*
 *
 *   Authors:
 *    Pedro Roque		<roque@di.fc.ul.pt>
 *    Lars Fenneberg		<lf@elemental.net>
 *
 *   This software is Copyright 1996,1997 by the above mentioned author(s),
 *   All Rights Reserved.
 *
 *   The license which is distributed with this software in the file COPYRIGHT
 *   applies to this software. If your distribution is missing this file, you
 *   may request it from <pekkas@netcore.fi>.
 *
 */

#include "config.h"
#include "includes.h"
#include "radvd.h"

/*
 * Sends an advertisement for all specified clients of this interface
 * (or via broadcast, if there are no restrictions configured).
 *
 * If a destination address is given, the RA will be sent to the destination
 * address only, but only if it was configured.
 *
 */

static void
send_rs_inc_len(size_t *len, int add)
{
	*len += add;
	if(*len >= MSG_SIZE_SEND)
	{
		flog(LOG_ERR, "Too many prefixes, routes, rdnss or dnssl to fit in buffer.  Exiting.");
		exit(1);
	}
}

static time_t
time_diff_secs(const struct timespec *time_x, const struct timespec *time_y)
{
	time_t secs_diff;

	secs_diff = time_x->tv_sec - time_y->tv_sec;
	if ((time_x->tv_nsec - time_y->tv_nsec) >= 500000000)
		secs_diff++;

	return secs_diff;
	
}

int
send_rs(struct Interface *iface, struct in6_addr *dest)
{
	uint8_t all_hosts_addr[] = {0xff,0x02,0,0,0,0,0,0,0,0,0,0,0,0,0,2};
	struct sockaddr_in6 addr;
	struct in6_pktinfo *pkt_info;
	struct msghdr mhdr;
	struct cmsghdr *cmsg;
	struct iovec iov;
	char __attribute__((aligned(8))) chdr[CMSG_SPACE(sizeof(struct in6_pktinfo))];
	struct nd_router_solicit *rsolicit;
	struct AdvPrefix *prefix;
	struct AdvRoute *route;
	struct AdvRDNSS *rdnss;
	struct AdvDNSSL *dnssl;
	struct timespec time_now;
	time_t secs_since_last_rs;

	unsigned char buff[MSG_SIZE_SEND];
	size_t buff_dest = 0;
	size_t len = 0;
	ssize_t err;

	/* First we need to check that the interface hasn't been removed or deactivated */
	if(check_device(iface) < 0) {
		if (iface->IgnoreIfMissing)  /* a bit more quiet warning message.. */
			dlog(LOG_DEBUG, 4, "interface %s does not exist, ignoring the interface", iface->Name);
		else {
			flog(LOG_WARNING, "interface %s does not exist, ignoring the interface", iface->Name);
		}
		iface->HasFailed = 1;
		/* not really a 'success', but we need to schedule new timers.. */
		return 0;
	} else {
		/* check_device was successful, act if it has failed previously */
		if (iface->HasFailed == 1) {
			flog(LOG_WARNING, "interface %s seems to have come back up, trying to reinitialize", iface->Name);
			iface->HasFailed = 0;
			/*
			 * return -1 so timer_handler() doesn't schedule new timers,
			 * reload_config() will kick off new timers anyway.  This avoids
			 * timer list corruption.
			 */
			reload_config();
			return -1;
		}
	}

	/* Make sure that we've joined the all-routers multicast group */
	if (check_allrouters_membership(iface) < 0)
		flog(LOG_WARNING, "problem checking all-routers membership on %s", iface->Name);

	dlog(LOG_DEBUG, 3, "sending RS on %s", iface->Name);

	if (dest == NULL)
	{
		dest = (struct in6_addr *)all_hosts_addr;
		clock_gettime(CLOCK_MONOTONIC, &iface->last_multicast);
	}

	clock_gettime(CLOCK_MONOTONIC, &time_now);
	secs_since_last_rs = time_diff_secs(&time_now, &iface->last_rs_time);
	if (secs_since_last_rs < 0) {
		secs_since_last_rs = 0;
		flog(LOG_WARNING, "clock_gettime() went backwards!");
	}
	iface->last_rs_time = time_now;

	memset((void *)&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(IPPROTO_ICMPV6);
	memcpy(&addr.sin6_addr, dest, sizeof(struct in6_addr));

	memset(buff, 0, sizeof(buff));
	rsolicit = (struct nd_router_solicit *) buff;

	send_rs_inc_len(&len, sizeof(struct nd_router_solicit));

	rsolicit->nd_rs_type  = ND_ROUTER_SOLICIT;
	rsolicit->nd_rs_code  = 0;
	rsolicit->nd_rs_cksum = 0;
	rsolicit->nd_rs_reserved = 0;

	/*
	 * add Source Link-layer Address option
	 */

	if (iface->AdvSourceLLAddress && iface->if_hwaddr_len > 0)
	{
		uint8_t *ucp;
		unsigned int i;

		ucp = (uint8_t *) (buff + len);

		send_rs_inc_len(&len, 2 * sizeof(uint8_t));

		*ucp++  = ND_OPT_SOURCE_LINKADDR;
		*ucp++  = (uint8_t) ((iface->if_hwaddr_len + 16 + 63) >> 6);

		i = (iface->if_hwaddr_len + 7) >> 3;

		buff_dest = len;

		send_rs_inc_len(&len, i);

		memcpy(buff + buff_dest, iface->if_hwaddr, i);
	}

	iov.iov_len  = len;
	iov.iov_base = (caddr_t) buff;

	memset(chdr, 0, sizeof(chdr));
	cmsg = (struct cmsghdr *) chdr;

	cmsg->cmsg_len   = CMSG_LEN(sizeof(struct in6_pktinfo));
	cmsg->cmsg_level = IPPROTO_IPV6;
	cmsg->cmsg_type  = IPV6_PKTINFO;

	pkt_info = (struct in6_pktinfo *)CMSG_DATA(cmsg);
	pkt_info->ipi6_ifindex = iface->if_index;
	memcpy(&pkt_info->ipi6_addr, &iface->if_addr, sizeof(struct in6_addr));

#ifdef HAVE_SIN6_SCOPE_ID
	if (IN6_IS_ADDR_LINKLOCAL(&addr.sin6_addr) ||
		IN6_IS_ADDR_MC_LINKLOCAL(&addr.sin6_addr))
			addr.sin6_scope_id = iface->if_index;
#endif

	memset(&mhdr, 0, sizeof(mhdr));
	mhdr.msg_name = (caddr_t)&addr;
	mhdr.msg_namelen = sizeof(struct sockaddr_in6);
	mhdr.msg_iov = &iov;
	mhdr.msg_iovlen = 1;
	mhdr.msg_control = (void *) cmsg;
	mhdr.msg_controllen = sizeof(chdr);

	err = sendmsg(sock, &mhdr, 0);

	if (err < 0) {
		if (!iface->IgnoreIfMissing || !(errno == EINVAL || errno == ENODEV))
			flog(LOG_WARNING, "sendmsg: %s", strerror(errno));
		else
			dlog(LOG_DEBUG, 3, "sendmsg: %s", strerror(errno));
	}

	return 0;
}
