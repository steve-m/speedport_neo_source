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
#include <sys/sysinfo.h>
#include "sal/sal_ipv6.h"

/*
 * Sends an advertisement for all specified clients of this interface
 * (or via broadcast, if there are no restrictions configured).
 *
 * If a destination address is given, the RA will be sent to the destination
 * address only, but only if it was configured.
 *
 */
int
send_ra_forall(struct Interface *iface, struct in6_addr *dest)
{
	struct Clients *current;

	/* If no list of clients was specified for this interface, we broadcast */
	if (iface->ClientList == NULL)
		return send_ra(iface, dest);

	/* If clients are configured, send the advertisement to all of them via unicast */
	for (current = iface->ClientList; current; current = current->next)
	{
		char address_text[INET6_ADDRSTRLEN];
		memset(address_text, 0, sizeof(address_text));
		if (get_debuglevel() >= 5)
			inet_ntop(AF_INET6, &current->Address, address_text, INET6_ADDRSTRLEN);

                /* If a non-authorized client sent a solicitation, ignore it (logging later) */
		if (dest != NULL && memcmp(dest, &current->Address, sizeof(struct in6_addr)) != 0)
			continue;
		dlog(LOG_DEBUG, 5, "Sending RA to %s", address_text);
		send_ra(iface, &(current->Address));

		/* If we should only send the RA to a specific address, we are done */
		if (dest != NULL)
			return 0;
	}
	if (dest == NULL)
		return 0;

        /* If we refused a client's solicitation, log it if debugging is high enough */
	char address_text[INET6_ADDRSTRLEN];
	memset(address_text, 0, sizeof(address_text));
	if (get_debuglevel() >= 5)
		inet_ntop(AF_INET6, dest, address_text, INET6_ADDRSTRLEN);

	dlog(LOG_DEBUG, 5, "Not answering request from %s, not configured", address_text);
	return 0;
}

static void
send_ra_inc_len(size_t *len, int add)
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

static void
decrement_lifetime(const time_t secs, uint32_t *lifetime, struct Interface *iface)
{
	if (secs < 2 * iface->MaxRtrAdvInterval) {
		if (*lifetime > secs) {
			*lifetime -= secs;	
		} else {
			*lifetime = 0;
		}
	}
}

static void cease_adv_pfx_msg(const char *if_name, struct in6_addr *pfx, const int pfx_len)
{
	char pfx_str[INET6_ADDRSTRLEN];

	print_addr(pfx, pfx_str);

	dlog(LOG_DEBUG, 3, "Will cease advertising %s/%u%%%s, preferred lifetime is 0", pfx_str, pfx_len, if_name);

}

int
send_ra(struct Interface *iface, struct in6_addr *dest)
{
	uint8_t all_hosts_addr[] = {0xff,0x02,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	struct sockaddr_in6 addr;
	struct in6_pktinfo *pkt_info;
	struct msghdr mhdr;
	struct cmsghdr *cmsg;
	struct iovec iov;
	char __attribute__((aligned(8))) chdr[CMSG_SPACE(sizeof(struct in6_pktinfo))];
	struct nd_router_advert *radvert;
	struct AdvPrefix *prefix;
	struct AdvRoute *route;
	struct AdvRDNSS *rdnss;
	struct AdvDNSSL *dnssl;
	struct timespec time_now;
	time_t secs_since_last_ra;

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

	dlog(LOG_DEBUG, 3, "sending RA on %s", iface->Name);

	if (dest == NULL)
	{
		dest = (struct in6_addr *)all_hosts_addr;
		clock_gettime(CLOCK_MONOTONIC, &iface->last_multicast);
	}

	clock_gettime(CLOCK_MONOTONIC, &time_now);
	secs_since_last_ra = time_diff_secs(&time_now, &iface->last_ra_time);
	if (secs_since_last_ra < 0) {
		secs_since_last_ra = 0;
		flog(LOG_WARNING, "clock_gettime() went backwards!");
	}
	iface->last_ra_time = time_now;

	memset((void *)&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(IPPROTO_ICMPV6);
	memcpy(&addr.sin6_addr, dest, sizeof(struct in6_addr));

	memset(buff, 0, sizeof(buff));
	radvert = (struct nd_router_advert *) buff;

	send_ra_inc_len(&len, sizeof(struct nd_router_advert));

	radvert->nd_ra_type  = ND_ROUTER_ADVERT;
	radvert->nd_ra_code  = 0;
	radvert->nd_ra_cksum = 0;

	radvert->nd_ra_curhoplimit	= iface->AdvCurHopLimit;
	radvert->nd_ra_flags_reserved	=
		(iface->AdvManagedFlag)?ND_RA_FLAG_MANAGED:0;
	radvert->nd_ra_flags_reserved	|=
		(iface->AdvOtherConfigFlag)?ND_RA_FLAG_OTHER:0;
	/* Mobile IPv6 ext */
	radvert->nd_ra_flags_reserved   |=
		(iface->AdvHomeAgentFlag)?ND_RA_FLAG_HOME_AGENT:0;

	if (iface->cease_adv) {
		radvert->nd_ra_router_lifetime = 0;
	} else {
		/* if forwarding is disabled, send zero router lifetime */
		radvert->nd_ra_router_lifetime	 =  !check_ip6_forwarding() ? htons(iface->AdvDefaultLifetime) : 0;
	}
	radvert->nd_ra_flags_reserved   |=
		(iface->AdvDefaultPreference << ND_OPT_RI_PRF_SHIFT) & ND_OPT_RI_PRF_MASK;

	radvert->nd_ra_reachable  = htonl(iface->AdvReachableTime);
	radvert->nd_ra_retransmit = htonl(iface->AdvRetransTimer);

	prefix = iface->AdvPrefixList;

	/*
	 *	add prefix options
	 */

	while(prefix)
	{
		if( prefix->enabled)
		{
			struct nd_opt_prefix_info *pinfo;
			char prefix_len[9] = "";

			pinfo = (struct nd_opt_prefix_info *) (buff + len);

			send_ra_inc_len(&len, sizeof(*pinfo));

			pinfo->nd_opt_pi_type	     = ND_OPT_PREFIX_INFORMATION;
			pinfo->nd_opt_pi_len	     = 4;
			pinfo->nd_opt_pi_prefix_len  = prefix->PrefixLen;
            
			snprintf(prefix_len, sizeof(prefix_len), "%u", prefix->PrefixLen);
			sal_lan_set_gua_prefix_len_t(prefix_len);

			pinfo->nd_opt_pi_flags_reserved  =
				(prefix->AdvOnLinkFlag)?ND_OPT_PI_FLAG_ONLINK:0;
			pinfo->nd_opt_pi_flags_reserved	|=
				(prefix->AdvAutonomousFlag)?ND_OPT_PI_FLAG_AUTO:0;
			/* Mobile IPv6 ext */
			pinfo->nd_opt_pi_flags_reserved |=
				(prefix->AdvRouterAddr)?ND_OPT_PI_FLAG_RADDR:0;

			if (iface->cease_adv && prefix->DeprecatePrefixFlag) {
				/* RFC4862, 5.5.3, step e) */
				pinfo->nd_opt_pi_valid_time	= htonl(MIN_AdvValidLifetime);
				pinfo->nd_opt_pi_preferred_time = 0;
			} else {
				if (prefix->DecrementLifetimesFlag) {
					//sercomm
					decrement_lifetime(secs_since_last_ra, &prefix->curr_lfttimer, iface);
					if (strcmp(sal_ipv6_get_basic_privacy(), "1") == 0)
                                        {                                        
                                            /* Calculate refresh lan prefix timer when first RA sent to LAN */
                                            if(prefix->refresh_prefix_timer==0)
                                                prefix->refresh_prefix_timer=time_now.tv_sec + prefix->curr_lfttimer;
                                        
                                            if((prefix->refresh_prefix_timer-time_now.tv_sec) <= 120 && (prefix->refresh_prefix_timer-time_now.tv_sec >= 60))
                                            {
                                                system("/bin/touch /tmp/ra_GUA_timeout");
                                                system("/usr/sbin/rc radvd restart");
                                            }
                                        }

					if (prefix->curr_lfttimer == 0)
						cease_adv_pfx_msg(iface->Name, &prefix->Prefix, prefix->PrefixLen);
				}
				pinfo->nd_opt_pi_valid_time	= htonl(prefix->curr_validlft);
				pinfo->nd_opt_pi_preferred_time = htonl(prefix->curr_preferredlft);

			}
			pinfo->nd_opt_pi_reserved2	= 0;

			memcpy(&pinfo->nd_opt_pi_prefix, &prefix->Prefix,
			       sizeof(struct in6_addr));
		}

		prefix = prefix->next;
	}

	route = iface->AdvRouteList;

	/*
	 *	add route options
	 */

	while(route)
	{
		struct nd_opt_route_info_local *rinfo;

		rinfo = (struct nd_opt_route_info_local *) (buff + len);

		send_ra_inc_len(&len, sizeof(*rinfo));

		rinfo->nd_opt_ri_type	     = ND_OPT_ROUTE_INFORMATION;
		/* XXX: the prefixes are allowed to be sent in smaller chunks as well */
		rinfo->nd_opt_ri_len	     = 3;
		rinfo->nd_opt_ri_prefix_len  = route->PrefixLen;

		rinfo->nd_opt_ri_flags_reserved  =
			(route->AdvRoutePreference << ND_OPT_RI_PRF_SHIFT) & ND_OPT_RI_PRF_MASK;
		if (iface->cease_adv && route->RemoveRouteFlag) {
			rinfo->nd_opt_ri_lifetime	= 0;
		} else {
			rinfo->nd_opt_ri_lifetime	= htonl(route->AdvRouteLifetime);
		}

		memcpy(&rinfo->nd_opt_ri_prefix, &route->Prefix,
		       sizeof(struct in6_addr));

		route = route->next;
	}

	rdnss = iface->AdvRDNSSList;

	/*
	 *	add rdnss options
	 */

	while(rdnss)
	{
		struct nd_opt_rdnss_info_local *rdnssinfo;

		rdnssinfo = (struct nd_opt_rdnss_info_local *) (buff + len);

		send_ra_inc_len(&len, sizeof(*rdnssinfo) - (3-rdnss->AdvRDNSSNumber)*sizeof(struct in6_addr));

		rdnssinfo->nd_opt_rdnssi_type	     = ND_OPT_RDNSS_INFORMATION;
		rdnssinfo->nd_opt_rdnssi_len	     = 1 + 2*rdnss->AdvRDNSSNumber;
		rdnssinfo->nd_opt_rdnssi_pref_flag_reserved = 0;

		if (iface->cease_adv && rdnss->FlushRDNSSFlag) {
			rdnssinfo->nd_opt_rdnssi_lifetime	= 0;
		} else {
			rdnssinfo->nd_opt_rdnssi_lifetime	= htonl(rdnss->AdvRDNSSLifetime);
		}

		memcpy(&rdnssinfo->nd_opt_rdnssi_addr1, &rdnss->AdvRDNSSAddr1,
		       sizeof(struct in6_addr));
		memcpy(&rdnssinfo->nd_opt_rdnssi_addr2, &rdnss->AdvRDNSSAddr2,
		       sizeof(struct in6_addr));
		memcpy(&rdnssinfo->nd_opt_rdnssi_addr3, &rdnss->AdvRDNSSAddr3,
		       sizeof(struct in6_addr));

		rdnss = rdnss->next;
	}

	dnssl = iface->AdvDNSSLList;

	/*
	 *	add dnssl options
	 */

	while(dnssl)
	{
		struct nd_opt_dnssl_info_local *dnsslinfo;
		int const start_len = len;
		int i;

		dnsslinfo = (struct nd_opt_dnssl_info_local *) (buff + len);

		send_ra_inc_len(&len, sizeof(dnsslinfo->nd_opt_dnssli_type) + 
			sizeof(dnsslinfo->nd_opt_dnssli_len) +
			sizeof(dnsslinfo->nd_opt_dnssli_reserved) +
			sizeof(dnsslinfo->nd_opt_dnssli_lifetime)
		);

		dnsslinfo->nd_opt_dnssli_type		= ND_OPT_DNSSL_INFORMATION;
		dnsslinfo->nd_opt_dnssli_reserved	= 0;

		if (iface->cease_adv && dnssl->FlushDNSSLFlag) {
			dnsslinfo->nd_opt_dnssli_lifetime	= 0;
		} else {
			dnsslinfo->nd_opt_dnssli_lifetime	= htonl(dnssl->AdvDNSSLLifetime);
		}

		for (i = 0; i < dnssl->AdvDNSSLNumber; i++) {
			char *label;
			int label_len;

			label = dnssl->AdvDNSSLSuffixes[i];

			while (label[0] != '\0') {
				if (strchr(label, '.') == NULL)
					label_len = strlen(label);
				else
					label_len = strchr(label, '.') - label;

				buff_dest = len;
				send_ra_inc_len(&len, 1);
				buff[buff_dest] = label_len;

				buff_dest = len;
				send_ra_inc_len(&len, label_len);
				memcpy(buff + buff_dest, label, label_len);

				label += label_len;

				if (label[0] == '.')
					label++;
				else {
					buff_dest = len;
					send_ra_inc_len(&len, 1);
					buff[buff_dest] = 0;
				}
			}
		}

		dnsslinfo->nd_opt_dnssli_len = (len - start_len) / 8;

		if ( (len - start_len) % 8 != 0 ) {
			send_ra_inc_len(&len, 8 - (len - start_len) % 8);
			++dnsslinfo->nd_opt_dnssli_len;
		}

		dnssl = dnssl->next;
	}

	/*
	 *	add MTU option
	 */

	if (iface->AdvLinkMTU != 0) {
		struct nd_opt_mtu *mtu;
		FILE * fp_mtu = NULL;
		char mtu_value[11] = {0};
		uint32_t mtu_int = 0;
		char *mtu_ptr = NULL;
		char *mtu_str[10] = {0};

		mtu = (struct nd_opt_mtu *) (buff + len);

		send_ra_inc_len(&len, sizeof(*mtu));
		fp_mtu = fopen("/proc/sys/net/ipv6/conf/ppp1/mtu", "r");
		if (fp_mtu != NULL) {
			if (fgets(mtu_value, sizeof(mtu_value), fp_mtu) != NULL) {
				mtu_ptr = strchr(mtu_value, '\n');
				if (mtu_ptr != NULL) {
					*mtu_ptr = '\0';
				}					
				mtu_int = strtoul(mtu_value, NULL, 10);
				if (mtu_int > 131072) {
					iface->AdvLinkMTU = 131072;
					strcpy(mtu_value, "131072");
				} else if (mtu_int < 1280) {
					iface->AdvLinkMTU = 1280;
					strcpy(mtu_value, "1280");
				}
				iface->AdvLinkMTU = mtu_int;
			}
			fclose(fp_mtu);
		}

		mtu->nd_opt_mtu_type     = ND_OPT_MTU;
		mtu->nd_opt_mtu_len      = 1;
                mtu->nd_opt_mtu_reserved = 0;
                mtu->nd_opt_mtu_mtu      = htonl(iface->AdvLinkMTU);
                sprintf(mtu_str, "%d", iface->AdvLinkMTU);
                sal_ipv6_set_lan_ra_mtu(mtu_str);
       
        }

	/*
	 * add Source Link-layer Address option
	 */

	if (iface->AdvSourceLLAddress && iface->if_hwaddr_len > 0)
	{
		uint8_t *ucp;
		unsigned int i;

		ucp = (uint8_t *) (buff + len);

		send_ra_inc_len(&len, 2 * sizeof(uint8_t));

		*ucp++  = ND_OPT_SOURCE_LINKADDR;
		*ucp++  = (uint8_t) ((iface->if_hwaddr_len + 16 + 63) >> 6);

		i = (iface->if_hwaddr_len + 7) >> 3;

		buff_dest = len;

		send_ra_inc_len(&len, i);

		memcpy(buff + buff_dest, iface->if_hwaddr, i);
	}

	/*
	 * Mobile IPv6 ext: Advertisement Interval Option to support
	 * movement detection of mobile nodes
	 */

	if(iface->AdvIntervalOpt)
	{
		struct AdvInterval a_ival;
                uint32_t ival;
                if(iface->MaxRtrAdvInterval < Cautious_MaxRtrAdvInterval){
                       ival  = ((iface->MaxRtrAdvInterval +
                                 Cautious_MaxRtrAdvInterval_Leeway ) * 1000);

                }
                else {
                       ival  = (iface->MaxRtrAdvInterval * 1000);
                }
 		a_ival.type	= ND_OPT_RTR_ADV_INTERVAL;
		a_ival.length	= 1;
		a_ival.reserved	= 0;
		a_ival.adv_ival	= htonl(ival);

		buff_dest = len;
		send_ra_inc_len(&len, sizeof(a_ival));
		memcpy(buff + buff_dest, &a_ival, sizeof(a_ival));
	}

	/*
	 * Mobile IPv6 ext: Home Agent Information Option to support
	 * Dynamic Home Agent Address Discovery
	 */

	if(iface->AdvHomeAgentInfo &&
	   (iface->AdvMobRtrSupportFlag || iface->HomeAgentPreference != 0 ||
	    iface->HomeAgentLifetime != iface->AdvDefaultLifetime))

	{
		struct HomeAgentInfo ha_info;
 		ha_info.type		= ND_OPT_HOME_AGENT_INFO;
		ha_info.length		= 1;
		ha_info.flags_reserved	=
			(iface->AdvMobRtrSupportFlag)?ND_OPT_HAI_FLAG_SUPPORT_MR:0;
		ha_info.preference	= htons(iface->HomeAgentPreference);
		ha_info.lifetime	= htons(iface->HomeAgentLifetime);

		buff_dest = len;
		send_ra_inc_len(&len, sizeof(ha_info));
		memcpy(buff + buff_dest, &ha_info, sizeof(ha_info));
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
	} else if (deprecate_flag == 1) {
		struct sysinfo info;

		sysinfo(&info);   
		if (radvd_deprecate_start_time == 0) {
			radvd_deprecate_start_time = info.uptime;
		}
		if (info.uptime - radvd_deprecate_start_time >= iface->MaxRtrAdvInterval * 2 - 1) {
			/* current ra - 1st ra is approximately 2 MaxRtrAdvInterval(default 60)
			 * because uptime has no decimal number, use 2 MaxRtrAdvInterval - 1*/
			char *pidfile;
			FILE *fp = NULL;
			char tmp[128] = {0};
			char ifname[IFNAMSIZ] = {0};
			char addrbuf[128] = {0};

			pidfile = PATH_RADVD_PID;
			flog(LOG_INFO, "removing %s", conf_file);
			unlink(conf_file);
			flog(LOG_INFO, "removing %s", pidfile);
			unlink(pidfile);
			fp = fopen("/tmp/ipv6/prefix_full.deprecate", "r");
			if (fp) {
				while (fgets(tmp, sizeof(tmp), fp) != NULL) {
					sscanf(tmp, "%s %s %*s %*d\n", ifname, addrbuf);
					sprintf(tmp, "/bin/ip -6 addr del %s dev %s", addrbuf, ifname);
					system(tmp);
				}
				fclose(fp);
				unlink("/tmp/ipv6/prefix_full.deprecate");
			}
			system("/usr/sbin/rc radvd start");
			exit(0);
		}
	}

	return 0;
}
