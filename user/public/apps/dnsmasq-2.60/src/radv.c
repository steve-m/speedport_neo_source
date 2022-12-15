/* dnsmasq is Copyright (c) 2000-2012 Simon Kelley

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 dated June, 1991, or
   (at your option) version 3 dated 29 June, 2007.
 
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
     
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


/* NB. This code may be called during a DHCPv4 or transaction which is in ping-wait
   It therefore cannot use any DHCP buffer resources except outpacket, which is
   not used by DHCPv4 code. This code may also be called when DHCP 4 or 6 isn't
   active, so we ensure that outpacket is allocated here too */

#include "dnsmasq.h"

#ifdef HAVE_DHCP6

#include <netinet/icmp6.h>

struct ra_param {
  int ind, managed, found_context, first;
  char *if_name;
  struct in6_addr link_local;
};

struct search_param {
  time_t now; int iface;
};

static void send_ra(int iface, char *iface_name, struct in6_addr *dest);
static int add_prefixes(struct in6_addr *local,  int prefix,
			int scope, int if_index, int dad, void *vparam);
static int iface_search(struct in6_addr *local,  int prefix,
			int scope, int if_index, int dad, void *vparam);
static int add_lla(int index, unsigned int type, char *mac, size_t maclen, void *parm);

static int hop_limit;
static time_t ra_short_period_start;

void ra_init(time_t now)
{
  struct icmp6_filter filter;
  int fd;
#if defined(IP_TOS) && defined(IPTOS_CLASS_CS6)
  int class = IPTOS_CLASS_CS6;
#endif
  int val = 255; /* radvd uses this value */
  socklen_t len = sizeof(int);

  /* ensure this is around even if we're not doing DHCPv6 */
  expand_buf(&daemon->outpacket, sizeof(struct dhcp_packet));

  ICMP6_FILTER_SETBLOCKALL(&filter);
  ICMP6_FILTER_SETPASS(ND_ROUTER_SOLICIT, &filter);
  ICMP6_FILTER_SETPASS(ND_ROUTER_ADVERT, &filter);
  
  if ((fd = socket(PF_INET6, SOCK_RAW, IPPROTO_ICMPV6)) == -1 ||
      getsockopt(fd, IPPROTO_IPV6, IPV6_UNICAST_HOPS, &hop_limit, &len) ||
#if defined(IP_TOS) && defined(IPTOS_CLASS_CS6)
      setsockopt(fd, IPPROTO_IPV6, IPV6_TCLASS, &class, sizeof(class)) == -1 ||
#endif
      !fix_fd(fd) ||
      !set_ipv6pktinfo(fd) ||
      setsockopt(fd, IPPROTO_IPV6, IPV6_UNICAST_HOPS, &val, sizeof(val)) ||
      setsockopt(fd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &val, sizeof(val)) ||
      setsockopt(fd, IPPROTO_ICMPV6, ICMP6_FILTER, &filter, sizeof(filter)) == -1)
    die (_("cannot create ICMPv6 socket: %s"), NULL, EC_BADNET);
  
   daemon->icmp6fd = fd;
   
   ra_start_unsolicted(now);
}

void ra_start_unsolicted(time_t now)
{   
   struct dhcp_context *context;
   
   /* init timers so that we do ra's for all soon. some ra_times will end up zeroed
     if it's not appropriate to advertise those contexts.
     This gets re-called on a netlink route-change to re-do the advertisement
     and pick up new interfaces */

   /* range 0 - 5 */
   for (context = daemon->ra_contexts; context; context = context->next)
     context->ra_time = now + (rand16()/13000);

   /* re-do frequently for a minute or so, in case the first gets lost. */
   ra_short_period_start = now;
}

void icmp6_packet(void)
{
  char interface[IF_NAMESIZE+1];
  ssize_t sz; 
  int if_index = 0;
  struct cmsghdr *cmptr;
  struct msghdr msg;
  union {
    struct cmsghdr align; /* this ensures alignment */
    char control6[CMSG_SPACE(sizeof(struct in6_pktinfo))];
  } control_u;
  struct sockaddr_in6 from;
  unsigned char *p;
  char *mac = "";
  struct iname *tmp;
  struct dhcp_context *context;

  /* Note: use outpacket for input buffer */
  msg.msg_control = control_u.control6;
  msg.msg_controllen = sizeof(control_u);
  msg.msg_flags = 0;
  msg.msg_name = &from;
  msg.msg_namelen = sizeof(from);
  msg.msg_iov = &daemon->outpacket;
  msg.msg_iovlen = 1;
  
  if ((sz = recv_dhcp_packet(daemon->icmp6fd, &msg)) == -1 || sz < 8)
    return;
  
  for (cmptr = CMSG_FIRSTHDR(&msg); cmptr; cmptr = CMSG_NXTHDR(&msg, cmptr))
    if (cmptr->cmsg_level == IPPROTO_IPV6 && cmptr->cmsg_type == daemon->v6pktinfo)
      {
	union {
	  unsigned char *c;
	  struct in6_pktinfo *p;
	} p;
	p.c = CMSG_DATA(cmptr);
        
	if_index = p.p->ipi6_ifindex;
      }
  
  if (!indextoname(daemon->icmp6fd, if_index, interface))
    return;
    
  if (!iface_check(AF_LOCAL, NULL, interface))
    return;
  
  for (tmp = daemon->dhcp_except; tmp; tmp = tmp->next)
    if (tmp->name && (strcmp(tmp->name, interface) == 0))
      return;
 
  /* weird libvirt-inspired access control */
  for (context = daemon->dhcp6; context; context = context->next)
    if (!context->interface || strcmp(context->interface, interface) == 0)
      break;
  
  if (!context)
    return;

  p = (unsigned char *)daemon->outpacket.iov_base;
  
  if (p[0] != ICMP6_ROUTER_SOLICIT || p[1] != 0)
    return;
  
  /* look for link-layer address option for logging */
  if (sz >= 16 && p[8] == ICMP6_OPT_SOURCE_MAC && (p[9] * 8) + 8 <= sz)
    {
      print_mac(daemon->namebuff, &p[10], (p[9] * 8) - 2);
      mac = daemon->namebuff;
    }
  
  my_syslog(MS_DHCP | LOG_INFO, "RTR-SOLICIT(%s) %s", interface, mac);
  
  send_ra(if_index, interface, &from.sin6_addr);
}

static void send_ra(int iface, char *iface_name, struct in6_addr *dest)
{
  struct ra_packet *ra;
  struct ra_param parm;
  struct ifreq ifr;
  struct sockaddr_in6 addr;
  struct dhcp_context *context;
 
  save_counter(0);
  ra = expand(sizeof(struct ra_packet));
  
  ra->type = ICMP6_ROUTER_ADVERT;
  ra->code = 0;
  ra->hop_limit = hop_limit;
  ra->flags = 0;
  ra->lifetime = htons(1800); /* AdvDefaultLifetime*/
  ra->reachable_time = 0;
  ra->retrans_time = 0;

  parm.ind = iface;
  parm.managed = 0;
  parm.found_context = 0;
  parm.if_name = iface_name;
  parm.first = 1;

  for (context = daemon->ra_contexts; context; context = context->next)
    context->flags &= ~CONTEXT_RA_DONE;
  
  if (!iface_enumerate(AF_INET6, &parm, add_prefixes) ||
      !parm.found_context)
    return;

  strncpy(ifr.ifr_name, iface_name, IF_NAMESIZE);
  
  if (ioctl(daemon->icmp6fd, SIOCGIFMTU, &ifr) != -1)
    {
      put_opt6_char(ICMP6_OPT_MTU);
      put_opt6_char(1);
      put_opt6_short(0);
      put_opt6_long(ifr.ifr_mtu);
    }
     
  iface_enumerate(AF_LOCAL, &iface, add_lla);
  
  /* RDNSS, RFC 6106 */
  put_opt6_char(ICMP6_OPT_RDNSS);
  put_opt6_char(3);
  put_opt6_short(0);
  put_opt6_long(1800); /* lifetime - twice RA retransmit */
  put_opt6(&parm.link_local, IN6ADDRSZ);


  /* set managed bits unless we're providing only RA on this link */
  if (parm.managed)
    ra->flags = 0xc0; 

  /* decide where we're sending */
  memset(&addr, 0, sizeof(addr));
#ifdef HAVE_SOCKADDR_SA_LEN
  addr.sin6_len = sizeof(struct sockaddr_in6);
#endif
  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(IPPROTO_ICMPV6);
  if (dest)
    {
      memcpy(&addr.sin6_addr, dest, sizeof(struct in6_addr));
      if (IN6_IS_ADDR_LINKLOCAL(dest) ||
	  IN6_IS_ADDR_MC_LINKLOCAL(dest))
	addr.sin6_scope_id = iface;
    }
  else
    inet_pton(AF_INET6, ALL_HOSTS, &addr.sin6_addr); 
  
  send_from(daemon->icmp6fd, 0, daemon->outpacket.iov_base, save_counter(0),
	    (union mysockaddr *)&addr, (struct all_addr *)&parm.link_local, iface); 
  
}

static int add_prefixes(struct in6_addr *local,  int prefix,
			int scope, int if_index, int dad, void *vparam)
{
  struct dhcp_context *context, *tmp;
  struct ra_param *param = vparam;
  struct prefix_opt *opt;

  (void)scope; /* warning */
  (void)dad;

  if (if_index == param->ind)
    {
      if (IN6_IS_ADDR_LINKLOCAL(local))
	param->link_local = *local;
      else if (!IN6_IS_ADDR_LOOPBACK(local) &&
	       !IN6_IS_ADDR_LINKLOCAL(local) &&
	       !IN6_IS_ADDR_MULTICAST(local))
	{
	  for (context = daemon->ra_contexts; context; context = context->next)
	    if (prefix == context->prefix &&
		is_same_net6(local, &context->start6, prefix) &&
		is_same_net6(local, &context->end6, prefix))
	      {
		if (!(context->flags & CONTEXT_RA_ONLY))
		  {
		    /* don't do RA for non-ra-only unless --enable-ra is set */
		    if (!option_bool(OPT_RA))
		      continue;
		    param->managed = 1;
		  }

		if (context->flags & CONTEXT_RA_DONE)
		  continue;
		
		/* subsequent prefixes on the same interface don't need timers */
		if (!param->first)
		  context->ra_time = 0;
		param->first = 0;
		param->found_context = 1;
		context->flags |= CONTEXT_RA_DONE;

		/* mark this subnet and duplicates: as done. */
		for (tmp = context->next; tmp; tmp = tmp->next)
		  if (tmp->prefix == prefix &&
		      is_same_net6(local, &tmp->start6, prefix) &&
		      is_same_net6(local, &tmp->end6, prefix))
		    {
		      tmp->flags |= CONTEXT_RA_DONE;
		      context->ra_time = 0;
		    }

		if ((opt = expand(sizeof(struct prefix_opt))))
		  {
		    u64 addrpart = addr6part(&context->start6);
		    u64 mask = (prefix == 64) ? (u64)-1LL : (1LLU << (128 - prefix)) - 1LLU;
		    unsigned int time = context->lease_time;

		    /* lifetimes must be min 2 hrs, by RFC 2462 */
		    if (time < 7200)
		      time = 7200;

		    opt->type = ICMP6_OPT_PREFIX;
		    opt->len = 4;
		    opt->prefix_len = prefix;
		    /* autonomous only is we're not doing dhcp */
		    opt->flags = (context->flags & CONTEXT_RA_ONLY) ? 0xc0 : 0x00;
		    opt->valid_lifetime = opt->preferred_lifetime = htonl(time);
		    opt->reserved = 0;
		    
		    opt->prefix = context->start6;
		    setaddr6part(&opt->prefix, addrpart & ~mask);
		    
		    inet_ntop(AF_INET6, &opt->prefix, daemon->addrbuff, ADDRSTRLEN);
		    my_syslog(MS_DHCP | LOG_INFO, "RTR-ADVERT(%s) %s", param->if_name, daemon->addrbuff); 		    
		  }
	      }
	}
    }          
  return 1;
}

static int add_lla(int index, unsigned int type, char *mac, size_t maclen, void *parm)
{
  (void)type;

  if (index == *((int *)parm))
    {
      /* size is in units of 8 octets and includes type and length (2 bytes)
	 add 7 to round up */
      int len = (maclen + 9) >> 3;
      unsigned char *p = expand(len << 3);
      memset(p, 0, len << 3);
      *p++ = ICMP6_OPT_SOURCE_MAC;
      *p++ = len;
      memcpy(p, mac, maclen);

      return 0;
    }

  return 1;
}

time_t periodic_ra(time_t now)
{
  struct search_param param;
  struct dhcp_context *context;
  time_t next_event;
  char interface[IF_NAMESIZE+1];
  
  param.now = now;

  while (1)
    {
      /* find overdue events, and time of first future event */
      for (next_event = 0, context = daemon->ra_contexts; context; context = context->next)
	if (context->ra_time != 0)
	  {
	    if (difftime(context->ra_time, now) < 0.0)
	      break; /* overdue */
	    
	    if (next_event == 0 || difftime(next_event, context->ra_time + 2) > 0.0)
	      next_event = context->ra_time + 2;
	  }
      
      /* none overdue */
      if (!context)
	break;
      
      /* There's a context overdue, but we can't find an interface
	 associated with it, because it's for a subnet we dont 
	 have an interface on. Probably we're doing DHCP on
	 a remote subnet via a relay. Zero the timer, since we won't
	 ever be able to send ra's and satistfy it. */
      if (iface_enumerate(AF_INET6, &param, iface_search))
	context->ra_time = 0;
      else if (indextoname(daemon->icmp6fd, param.iface, interface))
	send_ra(param.iface, interface, NULL); 
    }
  
  return next_event;
}

static int iface_search(struct in6_addr *local,  int prefix,
			int scope, int if_index, int dad, void *vparam)
{
  struct search_param *param = vparam;
  struct dhcp_context *context;

  (void)scope;
  (void)dad;
 
  for (context = daemon->ra_contexts; context; context = context->next)
    if (prefix == context->prefix &&
	is_same_net6(local, &context->start6, prefix) &&
	is_same_net6(local, &context->end6, prefix))
      if (context->ra_time != 0 && difftime(context->ra_time, param->now) < 0.0)
	{
	  /* found an interface that's overdue for RA determine new 
	     timeout value and zap other contexts on the same interface 
	     so they don't timeout independently .*/
	  param->iface = if_index;
	  
	  if (difftime(param->now, ra_short_period_start) < 60.0)
	    /* range 5 - 20 */
	    context->ra_time = param->now + 5 + (rand16()/4400);
	  else
	    /* range 450 - 600 */
	    context->ra_time = param->now + 450 + (rand16()/440);
	  
	  return 0; /* found, abort */
	}
  
  return 1; /* keep searching */
}

#endif
