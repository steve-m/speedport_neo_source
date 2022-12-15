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

static void process_rs(struct Interface *, unsigned char *msg,
		       int len, struct sockaddr_in6 *);
static void process_ra(struct Interface *, unsigned char *msg, int len,
	struct sockaddr_in6 *);
static int  addr_match(struct in6_addr *a1, struct in6_addr *a2,
	int prefixlen);

void
process(struct Interface *ifacel, unsigned char *msg, int len,
	struct sockaddr_in6 *addr, struct in6_pktinfo *pkt_info, int hoplimit)
{
	struct Interface *iface;
	struct icmp6_hdr *icmph;
	char addr_str[INET6_ADDRSTRLEN];

	print_addr(&addr->sin6_addr, addr_str);

	if ( ! pkt_info )
	{
		flog(LOG_WARNING, "received packet with no pkt_info from %s!", addr_str );
		return;
	}

	/*
	 * can this happen?
	 */

	if (len < sizeof(struct icmp6_hdr))
	{
		flog(LOG_WARNING, "received icmpv6 packet with invalid length (%d) from %s",
			len, addr_str);
		return;
	}

	icmph = (struct icmp6_hdr *) msg;

	if (icmph->icmp6_type != ND_NEIGHBOR_SOLICIT &&
	    icmph->icmp6_type != ND_NEIGHBOR_ADVERT)
	{
		/*
		 *	We just want to listen to NSs and NAs
		 */

		flog(LOG_ERR, "icmpv6 filter failed");
		return;
	}

	if (icmph->icmp6_type == ND_NEIGHBOR_ADVERT)
	{
		if (len < sizeof(struct nd_neighbor_advert)) {
			flog(LOG_WARNING, "received icmpv6 NA packet with invalid length (%d) from %s",
				len, addr_str);
			return;
		}

		if (!IN6_IS_ADDR_LINKLOCAL(&addr->sin6_addr)) {
			flog(LOG_WARNING, "received icmpv6 NA packet with non-linklocal source address from %s", addr_str);
			return;
		}
	}

	if (icmph->icmp6_type == ND_NEIGHBOR_SOLICIT)
	{
		if (len < sizeof(struct nd_neighbor_solicit)) {
			flog(LOG_WARNING, "received icmpv6 NS packet with invalid length (%d) from %s",
				len, addr_str);
			return;
		}
	}

	if (icmph->icmp6_code != 0)
	{
		flog(LOG_WARNING, "received icmpv6 NS/NA packet with invalid code (%d) from %s",
			icmph->icmp6_code, addr_str);
		return;
	}

	dlog(LOG_DEBUG, 4, "if_index %u", pkt_info->ipi6_ifindex);

	/* get iface by received if_index */

	for (iface = ifacel; iface; iface=iface->next)
	{
		if (iface->if_index == pkt_info->ipi6_ifindex)
		{
			break;
		}
	}

	if (iface == NULL)
	{
		dlog(LOG_DEBUG, 2, "received packet from unknown interface: %d",
			pkt_info->ipi6_ifindex);
		return;
	}

	if (hoplimit != 255)
	{
		print_addr(&addr->sin6_addr, addr_str);
		flog(LOG_WARNING, "received NS or NA with invalid hoplimit %d from %s",
			hoplimit, addr_str);
		return;
	}

	if (!iface->AdvSendAdvert)
	{
		dlog(LOG_DEBUG, 2, "AdvSendAdvert is off for %s", iface->Name);
		return;
	}

	dlog(LOG_DEBUG, 4, "found Interface: %s", iface->Name);

	if (icmph->icmp6_type == ND_NEIGHBOR_SOLICIT)
	{
		dlog(LOG_DEBUG, 4, "received NS from %s", addr_str);
	}
	else if (icmph->icmp6_type == ND_NEIGHBOR_ADVERT)
	{
		dlog(LOG_DEBUG, 4, "received NA from %s", addr_str);
	}
}

static int
addr_match(struct in6_addr *a1, struct in6_addr *a2, int prefixlen)
{
	unsigned int pdw;
	unsigned int pbi;

	pdw = prefixlen >> 0x05;  /* num of whole uint32_t in prefix */
	pbi = prefixlen &  0x1f;  /* num of bits in incomplete uint32_t in prefix */

	if (pdw)
	{
		if (memcmp(a1, a2, pdw << 2))
			return 0;
	}

	if (pbi)
	{
		uint32_t w1, w2;
		uint32_t mask;

		w1 = *((uint32_t *)a1 + pdw);
		w2 = *((uint32_t *)a2 + pdw);

		mask = htonl(((uint32_t) 0xffffffff) << (0x20 - pbi));

		if ((w1 ^ w2) & mask)
			return 0;
	}

	return 1;
}

