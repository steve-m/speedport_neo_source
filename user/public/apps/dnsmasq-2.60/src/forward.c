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

#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>

#ifdef __SC_BUILD__
#include "syslog.h"
#include "log_api.h"
#include "log_errcode_de.h"
#include "dnsmasq_sc.h"
#endif
#include "dnsmasq.h"
#include "dod.h"

static struct frec *lookup_frec(unsigned short id, unsigned int crc);
static struct frec *lookup_frec_by_sender(unsigned short id,
					  union mysockaddr *addr,
					  unsigned int crc);
static unsigned short get_id(unsigned int crc);
static void free_frec(struct frec *f);
static struct randfd *allocate_rfd(int family);

#ifdef __SC_BUILD__
extern char lan_ip_subnet[32];
extern unsigned int retry_interval;
extern char *dhcp_server_domain;
static time_t p008_last_syslog_time = 0;
static int p008_ipv6_syslog_count = 0;
#endif

/* when IPv6 DNS server response error or no response, print syslog P008 */
#ifdef __SC_BUILD__
static void ipv6_p008_syslog(int recode, char* ipv6server, time_t now)
{
    if(p008_ipv6_syslog_count%P008_IPV6_SYSLOG_NUM == 0 || ((now - p008_last_syslog_time) > P008_SYSLOG_TIME_INTERVAL))
    {
        char reply_code[64] = "";
        p008_ipv6_syslog_count = 0;
        p008_last_syslog_time = now;
        switch(recode)
        {
        case FORMERR:
            snprintf(reply_code, sizeof(reply_code), "Format Error(%d)", recode);
            break;
        case SERVFAIL:
            snprintf(reply_code, sizeof(reply_code), "Server Failure(%d)", recode);
            break;
        case NXDOMAIN:
            snprintf(reply_code, sizeof(reply_code), "Non Existent Domain(%d)", recode);
            break;
        case NOTIMP:
            snprintf(reply_code, sizeof(reply_code), "Not Implemented(%d)", recode);
            break;
        case REFUSED:
            snprintf(reply_code, sizeof(reply_code), "Query Refused(%d)", recode);
            break;
        }
        syslog(LOG_INFO,"%s"LOG_ERRCODE_P008, log_type_db[GENERAL_LOG], ipv6server, reply_code);
    }
   p008_ipv6_syslog_count ++;
}

static void p008_sysylog_timeout(struct frec *f, struct timeval now)
{
    char ipv6_buf[2][64];
    struct server *server = NULL;
    memset(ipv6_buf, 0 , sizeof(ipv6_buf));
    for (server = daemon->servers; server; server = server->next)
    {
        if(server->s_type == 1)
            inet_ntop(AF_INET6, &server->addr.in6.sin6_addr, ipv6_buf[0], (socklen_t)sizeof(ipv6_buf[0]));
        else if(server->s_type == 2)
        {
            inet_ntop(AF_INET6, &server->addr.in6.sin6_addr, ipv6_buf[1], (socklen_t)sizeof(ipv6_buf[1]));
            break;
        } 
    }
    if(f->dnsv6_pri_reply == 0 || f->dnsv6_sec_reply == 0)
    {
        char ipv6_server_temp[128] = {0};
        if(f->dnsv6_pri_reply != 0)
            sprintf(ipv6_server_temp, "%s", ipv6_buf[1]);
        else if(f->dnsv6_sec_reply != 0)
            sprintf(ipv6_server_temp, "%s", ipv6_buf[0]);
        else
            sprintf(ipv6_server_temp,"%s,%s",ipv6_buf[0],ipv6_buf[1]);

        ipv6_p008_syslog(SERVFAIL, ipv6_server_temp, now.tv_sec);
    }
       
    f->dnsv6_pri_reply = 0;
    f->dnsv6_sec_reply = 0;
    f->ipv6_flag =0;

}
#endif

/* Send a UDP packet with its source address set as "source" 
   unless nowild is true, when we just send it with the kernel default */
void send_from(int fd, int nowild, char *packet, size_t len, 
	       union mysockaddr *to, struct all_addr *source,
	       unsigned int iface)
{
  struct msghdr msg;
  struct iovec iov[1]; 
  union {
    struct cmsghdr align; /* this ensures alignment */
#if defined(HAVE_LINUX_NETWORK)
    char control[CMSG_SPACE(sizeof(struct in_pktinfo))];
#elif defined(IP_SENDSRCADDR)
    char control[CMSG_SPACE(sizeof(struct in_addr))];
#endif
#ifdef HAVE_IPV6
    char control6[CMSG_SPACE(sizeof(struct in6_pktinfo))];
#endif
  } control_u;
  
  iov[0].iov_base = packet;
  iov[0].iov_len = len;

  msg.msg_control = NULL;
  msg.msg_controllen = 0;
  msg.msg_flags = 0;
  msg.msg_name = to;
  msg.msg_namelen = sa_len(to);
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;
  
  if (!nowild)
    {
      struct cmsghdr *cmptr;
      msg.msg_control = &control_u;
      msg.msg_controllen = sizeof(control_u);
      cmptr = CMSG_FIRSTHDR(&msg);

      if (to->sa.sa_family == AF_INET)
	{
#if defined(HAVE_LINUX_NETWORK)
	  struct in_pktinfo p;
	  p.ipi_ifindex = 0;
	  p.ipi_spec_dst = source->addr.addr4;
	  memcpy(CMSG_DATA(cmptr), &p, sizeof(p));
	  msg.msg_controllen = cmptr->cmsg_len = CMSG_LEN(sizeof(struct in_pktinfo));
	  cmptr->cmsg_level = IPPROTO_IP;
	  cmptr->cmsg_type = IP_PKTINFO;
#elif defined(IP_SENDSRCADDR)
	  memcpy(CMSG_DATA(cmptr), &(source->addr.addr4), sizeof(source->addr.addr4));
	  msg.msg_controllen = cmptr->cmsg_len = CMSG_LEN(sizeof(struct in_addr));
	  cmptr->cmsg_level = IPPROTO_IP;
	  cmptr->cmsg_type = IP_SENDSRCADDR;
#endif
	}
      else
#ifdef HAVE_IPV6
	{
	  struct in6_pktinfo p;
	  p.ipi6_ifindex = iface; /* Need iface for IPv6 to handle link-local addrs */
	  p.ipi6_addr = source->addr.addr6;
	  memcpy(CMSG_DATA(cmptr), &p, sizeof(p));
	  msg.msg_controllen = cmptr->cmsg_len = CMSG_LEN(sizeof(struct in6_pktinfo));
	  cmptr->cmsg_type = daemon->v6pktinfo;
	  cmptr->cmsg_level = IPPROTO_IPV6;
	}
#else
      (void)iface; /* eliminate warning */
#endif
    }
  
 retry:
  if (sendmsg(fd, &msg, 0) == -1)
    {
      /* certain Linux kernels seem to object to setting the source address in the IPv6 stack
	 by returning EINVAL from sendmsg. In that case, try again without setting the
	 source address, since it will nearly alway be correct anyway.  IPv6 stinks. */
      if (errno == EINVAL && msg.msg_controllen)
	{
	  msg.msg_controllen = 0;
	  goto retry;
	}
      
      if (retry_send())
	goto retry;
      
      my_syslog(LOG_ERR, _("failed to send packet: %s"), strerror(errno));
    }
}
          
static unsigned int search_servers(time_t now, struct all_addr **addrpp, 
				     unsigned int qtype, char *qdomain, int *type, char **domain, int *norebind)
			      
{
  /* If the query ends in the domain in one of our servers, set
     domain to point to that name. We find the largest match to allow both
     domain.org and sub.domain.org to exist. */
  
  unsigned int namelen = strlen(qdomain);
  unsigned int matchlen = 0;
  struct server *serv;
  unsigned int flags = 0;
  
  for (serv = daemon->servers; serv; serv=serv->next)
    /* domain matches take priority over NODOTS matches */
    if ((serv->flags & SERV_FOR_NODOTS) && *type != SERV_HAS_DOMAIN && !strchr(qdomain, '.') && namelen != 0)
      {
	unsigned int sflag = serv->addr.sa.sa_family == AF_INET ? F_IPV4 : F_IPV6; 
	*type = SERV_FOR_NODOTS;
	if (serv->flags & SERV_NO_ADDR)
	  flags = F_NXDOMAIN;
	else if (serv->flags & SERV_LITERAL_ADDRESS) 
	  { 
	    if (sflag & qtype)
	      {
		flags = sflag;
		if (serv->addr.sa.sa_family == AF_INET) 
		  *addrpp = (struct all_addr *)&serv->addr.in.sin_addr;
#ifdef HAVE_IPV6
		else
		  *addrpp = (struct all_addr *)&serv->addr.in6.sin6_addr;
#endif 
	      }
	    else if (!flags || (flags & F_NXDOMAIN))
	      flags = F_NOERR;
	  } 
      }
    else if (serv->flags & SERV_HAS_DOMAIN)
      {
	unsigned int domainlen = strlen(serv->domain);
	char *matchstart = qdomain + namelen - domainlen;
	if (namelen >= domainlen &&
	    hostname_isequal(matchstart, serv->domain) &&
	    (domainlen == 0 || namelen == domainlen || *(matchstart-1) == '.' ))
	  {
	    if (serv->flags & SERV_NO_REBIND)	
	      *norebind = 1;
	    else
	      {
		unsigned int sflag = serv->addr.sa.sa_family == AF_INET ? F_IPV4 : F_IPV6;
		/* implement priority rules for --address and --server for same domain.
		   --address wins if the address is for the correct AF
		   --server wins otherwise. */
		if (domainlen != 0 && domainlen == matchlen)
		  {
		    if ((serv->flags & SERV_LITERAL_ADDRESS))
		      {
			if (!(sflag & qtype) && flags == 0)
			  continue;
		      }
		    else
		      {
			if (flags & (F_IPV4 | F_IPV6))
			  continue;
		      }
		  }
		
		if (domainlen >= matchlen)
		  {
		    *type = serv->flags & (SERV_HAS_DOMAIN | SERV_USE_RESOLV | SERV_NO_REBIND);
		    *domain = serv->domain;
		    matchlen = domainlen;
		    if (serv->flags & SERV_NO_ADDR)
		      flags = F_NXDOMAIN;
		    else if (serv->flags & SERV_LITERAL_ADDRESS)
		      {
			if (sflag & qtype)
			  {
			    flags = sflag;
			    if (serv->addr.sa.sa_family == AF_INET) 
			      *addrpp = (struct all_addr *)&serv->addr.in.sin_addr;
#ifdef HAVE_IPV6
			    else
			      *addrpp = (struct all_addr *)&serv->addr.in6.sin6_addr;
#endif
			  }
			else if (!flags || (flags & F_NXDOMAIN))
			  flags = F_NOERR;
		      }
		    else
		      flags = 0;
		  } 
	      }
	  }
      }
  
  if (flags == 0 && !(qtype & F_QUERY) && 
      option_bool(OPT_NODOTS_LOCAL) && !strchr(qdomain, '.') && namelen != 0)
    /* don't forward A or AAAA queries for simple names, except the empty name */
    flags = F_NOERR;
  
  if (flags == F_NXDOMAIN && check_for_local_domain(qdomain, now))
    flags = F_NOERR;

  if (flags)
    {
      int logflags = 0;
      
      if (flags == F_NXDOMAIN || flags == F_NOERR)
	logflags = F_NEG | qtype;
  
      log_query(logflags | flags | F_CONFIG | F_FORWARD, qdomain, *addrpp, NULL);
    }
  else if ((*type) & SERV_USE_RESOLV)
    {
      *type = 0; /* use normal servers for this domain */
      *domain = NULL;
    }
  return  flags;
}

static int forward_check(char *local_name, int local_type)
{
	char *ptr = NULL;
	char local_addr[5]={0};
	int int_addr = 0;
	int i = 0, j = 0;

	ptr = strstr(local_name, ".ip6.arpa");
	if (local_type == T_PTR && ptr != NULL) {
		/* D.C.B.A.ip6.arpa --> ABCD */
		for (i = 0; i < 4; i++) {
			local_addr[i] = *(ptr - (2 * i + 1));
		}
		int_addr = strtol(local_addr, NULL, 16);
		/* fe80 = 65152
		 * febf = 65215
		 * fcXX = 64512~64767
		 * fdxx = 64768~65023
		 * prefix with fe80~febf is local scope, should not forward to wan
		 * prefix with fcXX is unique local scope, should not forward to wan
		 */
		if ((int_addr >= 65152 && int_addr <= 65215) || (int_addr >= 64512 && int_addr <= 65023)) {
			return 1;
		}
	}
	return 0;
}

static int forward_query(int udpfd, union mysockaddr *udpaddr,
			 struct all_addr *dst_addr, unsigned int dst_iface,
			 struct dns_header *header, size_t plen, time_t now, struct frec *forward)
{
  char *domain = NULL;
  int dns_type = 0, type = 0, norebind = 0, send_num = 0, local_flag = 0;
  struct all_addr *addrp = NULL;
  unsigned short local_type = 0;
  unsigned int crc = questions_crc(header, plen, daemon->namebuff);
  unsigned int flags = 0;
  unsigned int gotname = extract_request(header, plen, daemon->namebuff, &local_type);
  struct server *start = NULL;
 
#ifndef __SC_BUILD__
  /* 
   * Fixed HPQC-14504
   * 1. DNS Proxy will transparently pass the AD Flag of a DNS query to upstream DNS servers
   * 2. DNS Proxy will does not validate the response so AG must not set the AD Flag in the dns response to LAN hosts 
   */ 
  /* RFC 4035: sect 4.6 para 2 */
  header->hb4 &= ~HB4_AD;
#endif
  
  /* may be no servers available. */
  if (!daemon->servers)
    forward = NULL;
  else if (forward || (forward = lookup_frec_by_sender(ntohs(header->id), udpaddr, crc)))
    {
        /* If resend dns time interval more than 0.9,the next retry will be sent from this funtion */
       return 0;
      /* retry on existing query, send to all available servers  */
      domain = forward->sentto->domain;
      forward->sentto->failed_queries++;
      if (!option_bool(OPT_ORDER))
	{
	  forward->forwardall = 1;
	  daemon->last_server = NULL;
	}
      type = forward->sentto->flags & SERV_TYPE;
      if (!(start = forward->sentto->next))
	start = daemon->servers; /* at end of list, recycle */
      header->id = htons(forward->new_id);
#ifdef __SC_BUILD__
      resume_domain(header, plen, forward->new_name);
#endif
	
    }
  else 
    {
      if (gotname) {
	flags = search_servers(now, &addrp, gotname, daemon->namebuff, &type, &domain, &norebind);
    local_flag = forward_check(daemon->namebuff, local_type);
    if (local_flag) {
      goto Local_exit;
    }
      }
      
      if (!flags && !(forward = get_new_frec(now, NULL)))
	/* table full - server failure. */
	flags = F_NEG;
      
      if (forward)
	{
	  forward->source = *udpaddr;
	  forward->dest = *dst_addr;
	  forward->iface = dst_iface;
	  forward->orig_id = ntohs(header->id);
	  forward->new_id = get_id(crc);
	  forward->fd = udpfd;
	  forward->crc = crc;
	  forward->forwardall = 0;
	  if (norebind)
	    forward->flags |= FREC_NOREBIND;
	  if (header->hb4 & HB4_CD)
	    forward->flags |= FREC_CHECKING_DISABLED;

#ifdef __SC_BUILD__
      daemon->id = forward->new_id;
      sprintf(forward->orig_name, "%s", daemon->namebuff);
      sprintf(forward->new_name, "%s", daemon->namebuff);
      memset(forward->retry_new_id, 0, sizeof(forward->retry_new_id));
      //sc_transcation_id_dump("init", forward);
      create_newname_follow_bit20(forward->new_name);
      resume_domain(header, plen, forward->new_name);
      strcpy(daemon->namebuff, forward->new_name);
      my_syslog(LOG_INFO, "%s#%d,receive %s,change = %s", __func__, __LINE__, forward->orig_name, forward->new_name);
      /* backup infomation for feedback station server fail when all retry is timeout */
      forward->orig_addrp = addrp;
      forward->orig_size = plen;
      forward->pppv4_send = 0;
      memset(forward->dns_server,0,sizeof(forward->dns_server));
      forward->ipv6_flag = 0;
      /* lastserverflag is used for everyserver reponse but error */
      forward->lastserverflag = 0;
      forward->err_code = SERVFAIL;
      forward->hash = sc_fqdn_hash(forward->orig_name);
#endif
	  header->id = htons(forward->new_id);
	  
	  /* In strict_order mode, always try servers in the order 
	     specified in resolv.conf, if a domain is given 
	     always try all the available servers,
	     otherwise, use the one last known to work. */
	  
	  if (type == 0)
	    {
	      if (option_bool(OPT_ORDER))
		start = daemon->servers;
	      else if (!(start = daemon->last_server) ||
		       daemon->forwardcount++ > FORWARD_TEST ||
		       difftime(now, daemon->forwardtime) >= FORWARD_TIME)
		{
		  start = daemon->servers;
		  forward->forwardall = 1;
		  daemon->forwardcount = 0;
		  daemon->forwardtime = now;
		}
	    }
	  else
	    {
	      start = daemon->servers;
	      if (!option_bool(OPT_ORDER))
		forward->forwardall = 1;
	    }
	}
    }

  /* check for send errors here (no route to host) 
     if we fail to send to all nameservers, send back an error
     packet straight away (helps modem users when offline)  */
  
  if (!flags && forward)
    {
      struct server *firstsentto = start;
      int forwarded = 0;

      dns_type = start->s_type;


      if (udpaddr && option_bool(OPT_ADD_MAC))
	plen = add_mac(header, plen, ((char *) header) + PACKETSZ, udpaddr);
      
      while (1)
	{ 
	  /* only send to servers dealing with our domain.
	     domain may be NULL, in which case server->domain 
	     must be NULL also. */
	  
	  if (type == (start->flags & SERV_TYPE) &&
	      (type != SERV_HAS_DOMAIN || hostname_isequal(domain, start->domain)) &&
	      !(start->flags & SERV_LITERAL_ADDRESS))
	    {
	      int fd;

	      /* find server socket to use, may need to get random one. */
	      if (start->sfd)
		fd = start->sfd->fd;
	      else 
		{
#ifdef HAVE_IPV6
		  if (start->addr.sa.sa_family == AF_INET6)
		    {
		      if (!forward->rfd6 &&
			  !(forward->rfd6 = allocate_rfd(AF_INET6)))
			break;
		      daemon->rfd_save = forward->rfd6;
		      fd = forward->rfd6->fd;
		    }
		  else
#endif
		    {
		      if (!forward->rfd4 &&
			  !(forward->rfd4 = allocate_rfd(AF_INET)))
			break;
		      daemon->rfd_save = forward->rfd4;
		      fd = forward->rfd4->fd;
		    }

#ifdef HAVE_CONNTRACK
		  /* Copy connection mark of incoming query to outgoing connection. */
		  if (option_bool(OPT_CONNTRACK))
		    {
		      unsigned int mark;
		      if (get_incoming_mark(udpaddr, dst_addr, 0, &mark))
			setsockopt(fd, SOL_SOCKET, SO_MARK, &mark, sizeof(unsigned int));
		    }
#endif
		}
              if (sendto(fd, (char *)header, plen, 0,
			 &start->addr.sa,
			 sa_len(&start->addr)) != -1)
		{
		  /* Keep info in case we want to re-send this packet */
		  daemon->srv_save = start;
		  daemon->packet_len = plen;
		  
		  if (!gotname)
		    strcpy(daemon->namebuff, "query");
		  if (start->addr.sa.sa_family == AF_INET)
		    log_query(F_SERVER | F_IPV4 | F_FORWARD, daemon->namebuff, 
			      (struct all_addr *)&start->addr.in.sin_addr, NULL); 
#ifdef HAVE_IPV6
		  else
		    log_query(F_SERVER | F_IPV6 | F_FORWARD, daemon->namebuff, 
			      (struct all_addr *)&start->addr.in6.sin6_addr, NULL);
#endif 


		  start->queries++;
		  forwarded = 1;
		  forward->sentto = start;
		  if (!forward->forwardall) 
		    break;
		  forward->forwardall++;
		  forward->s_type = start->s_type;
		  forward->single_dns = 0;
		  forward->plen = plen;
		  memcpy(forward->header, header, plen);
          gettimeofday(&forward->tv,NULL);

          send_num++;
          if(dns_type == 1 || send_num == 2)//1st pppv6_pri || 5th dhcpv4_sec
          {
              if(dns_type==1)
              {
                    forward->retry_new_id[0][0] = header->id;
                    forward->ipv6_flag = 1;
              }
              else
                    forward->retry_new_id[1][3] = header->id;
              if (!(start->next))
                  forward->lastserverflag = 1;
              break;
          }
          else if(dns_type == 3)//3th pppv4_pri
          {
              forward->retry_new_id[0][3] = header->id;
              if (!(start->next))
                  forward->lastserverflag = 1;
              forward->pppv4_send = 1;
              break;
          }
          else//5th dhcpv4_pri
          {
              //backup 5th dhcpv4_pri transcation id
              forward->retry_new_id[1][2] = header->id;
              header->id = get_id(crc);
          }

		}
              else
                  my_syslog(LOG_INFO, _("sent to fail")); 
	    } 
	  
	  if (!(start = start->next))
 	    start = daemon->servers;

#ifdef __SC_BUILD__
          sprintf(forward->orig_name, "%s", daemon->namebuff);
          sprintf(forward->new_name, "%s", daemon->namebuff);
          /* change the domain name */
          create_newname_follow_bit20(forward->new_name);
          /* put the changed domain name to the pocket */
          resume_domain(header, plen, forward->new_name);
          strcpy(daemon->namebuff, forward->new_name);
          my_syslog(LOG_INFO, "%s#%d,receive %s,change = %s", __func__, __LINE__, forward->orig_name, forward->new_name);
          /* backup infomation for feedback station server fail when all retry is timeout */
          forward->orig_addrp = addrp;
          forward->orig_size = plen;
#endif
	  if (start == firstsentto)
	    break;
	}
      
      if (forwarded)
          return 1;
      
      /* could not send on, prepare to return */ 
      header->id = htons(forward->orig_id);
      free_frec(forward); /* cancel */
    }	  
  
Local_exit:
  /* could not send on, return empty answer or address if known for whole domain */
  if (udpfd != -1)
    {
      plen = setup_reply(header, plen, addrp, flags, daemon->local_ttl);
      send_from(udpfd, option_bool(OPT_NOWILD), (char *)header, plen, udpaddr, dst_addr, dst_iface);
    }

  return 0;
}

#ifdef __SC_BUILD__
static size_t process_reply(struct dns_header *header, time_t now, 
			    struct server *server, size_t n, int check_rebind, int checking_disabled, int tcp, int qtype)
#else
static size_t process_reply(struct dns_header *header, time_t now, 
			    struct server *server, size_t n, int check_rebind, int checking_disabled)
#endif
{
  unsigned char *pheader, *sizep;
  int munged = 0, is_sign;
  size_t plen; 

  /* If upstream is advertising a larger UDP packet size
     than we allow, trim it so that we don't get overlarge
     requests for the client. We can't do this for signed packets. */

  if ((pheader = find_pseudoheader(header, n, &plen, &sizep, &is_sign)) && !is_sign)
    {
      unsigned short udpsz;
      unsigned char *psave = sizep;
      
      GETSHORT(udpsz, sizep);
      if (udpsz > daemon->edns_pktsz)
	PUTSHORT(daemon->edns_pktsz, psave);
    }

  /* RFC 4035 sect 4.6 para 3 */
  if (!is_sign && !option_bool(OPT_DNSSEC))
     header->hb4 &= ~HB4_AD;

  if (OPCODE(header) != QUERY || (RCODE(header) != NOERROR && RCODE(header) != NXDOMAIN))
    return n;
  
  /* Complain loudly if the upstream server is non-recursive. */
  if (!(header->hb4 & HB4_RA) && RCODE(header) == NOERROR && ntohs(header->ancount) == 0 &&
      server && !(server->flags & SERV_WARNED_RECURSIVE))
    {
      prettyprint_addr(&server->addr, daemon->namebuff);
      my_syslog(LOG_WARNING, _("nameserver %s refused to do a recursive query"), daemon->namebuff);
      if (!option_bool(OPT_LOG))
	server->flags |= SERV_WARNED_RECURSIVE;
    }  
    
  if (daemon->bogus_addr && RCODE(header) != NXDOMAIN &&
      check_for_bogus_wildcard(header, n, daemon->namebuff, daemon->bogus_addr, now))
    {
      munged = 1;
      SET_RCODE(header, NXDOMAIN);
      header->hb3 &= ~HB3_AA;
    }
  else 
    {
      if (RCODE(header) == NXDOMAIN && 
	  extract_request(header, n, daemon->namebuff, NULL) &&
	  check_for_local_domain(daemon->namebuff, now))
	{
	  /* if we forwarded a query for a locally known name (because it was for 
	     an unknown type) and the answer is NXDOMAIN, convert that to NODATA,
	     since we know that the domain exists, even if upstream doesn't */
	  munged = 1;
	  header->hb3 |= HB3_AA;
	  SET_RCODE(header, NOERROR);
	}
#ifdef __SC_BUILD__
      if (tcp)
      {
          int m = resize_packet(header, n, pheader, plen);
          do {
              int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
              if(fd == -1)
                  break;
              struct sockaddr_un cmd_addr;
              cmd_addr.sun_family = AF_UNIX;
              strcpy(cmd_addr.sun_path, SC_CMD_SOCK_PATH);
              int cmd_size = m + sizeof(struct sc_cmd_dns_cache) + 1;
              char *dnsmasq_cmd = (char*)malloc(cmd_size);
              if(!dnsmasq_cmd) {
                  close(fd);
                  break;
              }
              memset(dnsmasq_cmd, 0, cmd_size);
              dnsmasq_cmd[0] = SC_CMD_DNS_CACHE;
              struct sc_cmd_dns_cache *pinfo = (struct sc_cmd_dns_cache *)(dnsmasq_cmd+1);
              pinfo->pid = getpid();
              pinfo->qlen = n;
              strncpy(pinfo->name, daemon->namebuff, sizeof(pinfo->name)-1);
              pinfo->now = now;
              pinfo->is_sign = is_sign;
              pinfo->check_rebind = check_rebind;
              pinfo->checking_disabled = checking_disabled;
              pinfo->qtype = qtype;
              memcpy(pinfo->header, header, m);
              sendto(fd, dnsmasq_cmd, cmd_size, 0, (struct sockaddr *)&cmd_addr, sizeof(cmd_addr));
              close(fd);
              free(dnsmasq_cmd);
          } while(0);

          return m;
      }
#endif

      if (extract_addresses(header, n, daemon->namebuff, now, is_sign, check_rebind, checking_disabled))
	{
	  my_syslog(LOG_WARNING, _("possible DNS-rebind attack detected: %s"), daemon->namebuff);
	  munged = 1;
	}
    }
 
#ifdef __SC_BUILD__
  /* 
   * Fixed HPQC-14504
   * 1. DNS Proxy will transparently pass the AD Flag of a DNS query to upstream DNS servers
   * 2. DNS Proxy will does not validate the response so AG must not set the AD Flag in the dns response to LAN hosts 
   */
  /* RFC 4035: sect 4.6 para 2 */
  header->hb4 &= ~HB4_AD;
#endif

  /* do this after extract_addresses. Ensure NODATA reply and remove
     nameserver info. */
  
  if (munged)
    {
      header->ancount = htons(0);
      header->nscount = htons(0);
      header->arcount = htons(0);
    }
  
  /* the bogus-nxdomain stuff, doctor and NXDOMAIN->NODATA munging can all elide
     sections of the packet. Find the new length here and put back pseudoheader
     if it was removed. */
      return resize_packet(header, n, pheader, plen);
}
/* sets new last_server */
void reply_query(int fd, int family, time_t now)
{
  /* packet from peer server, extract data for cache, and send to
     original requester */

  struct dns_header *header;
  union mysockaddr serveraddr;
  struct frec *forward;
  socklen_t addrlen = sizeof(serveraddr);
  ssize_t n = recvfrom(fd, daemon->packet, daemon->edns_pktsz, 0, &serveraddr.sa, &addrlen);
  size_t nn;
  struct server *server;
  int i;
  
  /* packet buffer overwritten */
  daemon->srv_save = NULL;
  
  /* Determine the address of the server replying  so that we can mark that as good */
  serveraddr.sa.sa_family = family;
#ifdef HAVE_IPV6
  if (serveraddr.sa.sa_family == AF_INET6)
    serveraddr.in6.sin6_flowinfo = 0;
#endif
  
  /* spoof check: answer must come from known server, */
  for (server = daemon->servers; server; server = server->next)
    if (!(server->flags & (SERV_LITERAL_ADDRESS | SERV_NO_ADDR)) &&
	sockaddr_isequal(&server->addr, &serveraddr))
      break;
   
  header = (struct dns_header *)daemon->packet;

    my_syslog(LOG_INFO, _("reply query function:header id is %x ,daemon name is %s\n"), header->id,daemon->namebuff); 
    if (!server ||
      n < (int)sizeof(struct dns_header) || !(header->hb3 & HB3_QR) ||
      !(forward = lookup_frec(ntohs(header->id), questions_crc(header, n, daemon->namebuff))))
        return;


#ifdef __SC_BUILD__
  resume_domain(header, n, forward->orig_name);
#endif
  
  server = forward->sentto;
  
#ifdef __SC_BUILD__
  if ((RCODE(header) != NOERROR) &&
      !option_bool(OPT_ORDER) &&
      forward->forwardall == 0)
#else
  if ((RCODE(header) == SERVFAIL || RCODE(header) == REFUSED) &&
      !option_bool(OPT_ORDER) &&
      forward->forwardall == 0)
#endif
    /* for broken servers, attempt to send to another one. */
    {
      unsigned char *pheader;
      size_t plen;
      int is_sign;
      
      /* recreate query from reply */
      pheader = find_pseudoheader(header, (size_t)n, &plen, NULL, &is_sign);
      if (!is_sign)
	{
	  header->ancount = htons(0);
	  header->nscount = htons(0);
	  header->arcount = htons(0);
	  if ((nn = resize_packet(header, (size_t)n, pheader, plen)))
	    {
	      header->hb3 &= ~(HB3_QR | HB3_TC);
	      forward_query(-1, NULL, NULL, 0, header, nn, now, forward);
	      return;
	    }
	}
    }   
  
  if ((forward->sentto->flags & SERV_TYPE) == 0)
    {
#ifdef __SC_BUILD__
      if (RCODE(header) != NOERROR)
#else
      if (RCODE(header) == SERVFAIL || RCODE(header) == REFUSED)
#endif
	server = NULL;
      else
	{
	  struct server *last_server;
	  
	  /* find good server by address if possible, otherwise assume the last one we sent to */ 
	  for (last_server = daemon->servers; last_server; last_server = last_server->next)
	    if (!(last_server->flags & (SERV_LITERAL_ADDRESS | SERV_HAS_DOMAIN | SERV_FOR_NODOTS | SERV_NO_ADDR)) &&
		sockaddr_isequal(&last_server->addr, &serveraddr))
	      {
		server = last_server;
		break;
	      }
	} 
      if (!option_bool(OPT_ALL_SERVERS))
	daemon->last_server = server;
    }
#ifdef __SC_BUILD__
 if (serveraddr.sa.sa_family == AF_INET6)
  {
      if (RCODE(header) != NOERROR)
      {
          char ipv6_server[64] = {0};
          struct server *p008_syslog_server;
          inet_ntop(AF_INET6, &serveraddr.in6.sin6_addr, ipv6_server, (socklen_t)sizeof(ipv6_server));
          ipv6_p008_syslog(RCODE(header),ipv6_server,now);
          for (p008_syslog_server = daemon->servers; p008_syslog_server; p008_syslog_server = p008_syslog_server->next)
          {
              if (sockaddr_isequal(&p008_syslog_server->addr, &serveraddr))
              {
                  if(p008_syslog_server->s_type == 1)
                      forward->dnsv6_pri_reply = 1;
                  else if(p008_syslog_server->s_type == 2)
                      forward->dnsv6_sec_reply = 2;
                  break;
              }
          }
      }
  }
#endif 
  /* If the answer is an error, keep the forward record in place in case
     we get a good reply from another server. Kill it when we've
     had replies from all to avoid filling the forwarding table when
     everything is broken */
#ifdef __SC_BUILD__
  if(RCODE(header) != NOERROR && RCODE(header) != NXDOMAIN)
    forward->err_code = RCODE(header);

  if (forward->forwardall == 0 || ( forward->lastserverflag == 1 && --forward->forwardall == 1) ||
      (RCODE(header) == NOERROR || RCODE(header) == NXDOMAIN))
#else
  if (forward->forwardall == 0 || --forward->forwardall == 1 || 
      (RCODE(header) != REFUSED && RCODE(header) != SERVFAIL))
#endif
    {
      int check_rebind = !(forward->flags & FREC_NOREBIND);

      if (!option_bool(OPT_NO_REBIND))
	check_rebind = 0;
      
#ifdef __SC_BUILD__
      do {
          daemon->qry_in_abuse = 0;

          if((g_ea_flag & SC_EA_DO_V4) == 0 &&
             (g_ea_flag & SC_EA_DO_V6) == 0)
              break;

          struct ea_hnode *tmp;
          for(tmp = g_ea_wlist[forward->hash]; tmp; tmp = tmp->next) {
              if(strcasecmp(forward->orig_name, tmp->fqdn) == 0) {
                  daemon->qry_in_abuse = 1;
                  break;
              }
          }
      } while(0);
#endif
#ifdef __SC_BUILD__
      if ((nn = process_reply(header, now, server, (size_t)n, check_rebind, forward->flags & FREC_CHECKING_DISABLED, 0, -1)))
#else
      if ((nn = process_reply(header, now, server, (size_t)n, check_rebind, forward->flags & FREC_CHECKING_DISABLED)))
#endif
      {
          header->id = htons(forward->orig_id);
          header->hb4 |= HB4_RA; /* recursion if available */
#ifdef __SC_BUILD__
          /* check response pocket type, if just have a cname, we will change the flags to NXDOMAIN  */
          int q = ntohs(header->ancount);
          if (q == 1)
          {
              unsigned char *p, *p1;
              int qtype, res;
              char name[50] = {0};
              p = (unsigned char *)(header+1);
              if (!(p1 = skip_questions(header, n)))
                  return 0;
              if (!(res = extract_name(header, n, &p1, name, 0, 10)))
                  return 0; 

              GETSHORT(qtype, p1);
              if(qtype == T_CNAME)
              {
                  SET_RCODE(header, REFUSED);
                  header->ancount = htons(0);
              } 
          } 
#endif
          send_from(forward->fd, option_bool(OPT_NOWILD), daemon->packet, nn, 
		    &forward->source, &forward->dest, forward->iface);
	}
      free_frec(forward); /* cancel */
    }
}

static uint32_t get_if_addr(char *ifname)
{
    struct ifreq ifr;
    int fd;

    strcpy(ifr.ifr_name, ifname);

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(ioctl(fd, SIOCGIFADDR, &ifr) != 0) {
        return 0;
    }
    close(fd);

    return ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr;
}

static void get_if_addr6(char *ifname, char *ip6_addr)
{
  FILE *fp = NULL;
  char addr6p[8][5];
  char addr6[128], devname[20];
  int if_idx, scope, plen, dad_status;
  struct in6_addr if_addr6;

  fp = fopen("/proc/net/if_inet6", "r");
  if (fp != NULL) {
    memset(addr6, 0, 128);
    while (fscanf(fp, "%4s%4s%4s%4s%4s%4s%4s%4s %02x %02x %02x %02x %20s\n",
            addr6p[0], addr6p[1], addr6p[2], addr6p[3], addr6p[4],
            addr6p[5], addr6p[6], addr6p[7], &if_idx, &plen, &scope,
            &dad_status, devname) != EOF) {
      if (strcmp(ifname, devname) == 0 && scope == 0x20) {
        sprintf(addr6, "%s:%s:%s:%s:%s:%s:%s:%s",
                addr6p[0], addr6p[1], addr6p[2], addr6p[3],
                addr6p[4], addr6p[5], addr6p[6], addr6p[7]);
        inet_pton(AF_INET6, addr6, &if_addr6);
        inet_ntop(AF_INET6, &if_addr6, ip6_addr, INET6_ADDRSTRLEN);
        break;
      }
    }
    fclose(fp);
  }
  return;
}

void receive_query(struct listener *listen, time_t now)
{
  struct dns_header *header = (struct dns_header *)daemon->packet;
  union mysockaddr source_addr;
  unsigned short type;
  struct all_addr dst_addr;
  struct in_addr netmask, dst_addr_4;
  size_t m;
  ssize_t n;
  int if_index = 0;
  struct iovec iov[1];
  struct msghdr msg;
  struct cmsghdr *cmptr;

  union {
    struct cmsghdr align; /* this ensures alignment */
#ifdef HAVE_IPV6
    char control6[CMSG_SPACE(sizeof(struct in6_pktinfo))];
#endif
#if defined(HAVE_LINUX_NETWORK)
    char control[CMSG_SPACE(sizeof(struct in_pktinfo))];
#elif defined(IP_RECVDSTADDR) && defined(HAVE_SOLARIS_NETWORK)
    char control[CMSG_SPACE(sizeof(struct in_addr)) +
		 CMSG_SPACE(sizeof(unsigned int))];
#elif defined(IP_RECVDSTADDR)
    char control[CMSG_SPACE(sizeof(struct in_addr)) +
		 CMSG_SPACE(sizeof(struct sockaddr_dl))];
#endif
  } control_u;
  /* packet buffer overwritten */
  daemon->srv_save = NULL;
  
  if (listen->family == AF_INET && option_bool(OPT_NOWILD))
    {
      dst_addr_4 = listen->iface->addr.in.sin_addr;
      netmask = listen->iface->netmask;
    }
  else
    {
      dst_addr_4.s_addr = 0;
      netmask.s_addr = 0;
    }

  iov[0].iov_base = daemon->packet;
  iov[0].iov_len = daemon->edns_pktsz;
    
  msg.msg_control = control_u.control;
  msg.msg_controllen = sizeof(control_u);
  msg.msg_flags = 0;
  msg.msg_name = &source_addr;
  msg.msg_namelen = sizeof(source_addr);
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;
  
  if ((n = recvmsg(listen->fd, &msg, 0)) == -1)
    return;
  
  if (n < (int)sizeof(struct dns_header) || 
      (msg.msg_flags & MSG_TRUNC) ||
      (header->hb3 & HB3_QR))
    return;

  /* Clear buffer beyond request to avoid risk of
     information disclosure. */
  memset(daemon->packet + n, 0, daemon->edns_pktsz - n);
  
  source_addr.sa.sa_family = listen->family;
#ifdef HAVE_IPV6
  if (listen->family == AF_INET6)
    source_addr.in6.sin6_flowinfo = 0;
#endif

  if (!option_bool(OPT_NOWILD))
    {
      struct ifreq ifr;

      if (msg.msg_controllen < sizeof(struct cmsghdr))
	return;

#if defined(HAVE_LINUX_NETWORK)
      if (listen->family == AF_INET)
	for (cmptr = CMSG_FIRSTHDR(&msg); cmptr; cmptr = CMSG_NXTHDR(&msg, cmptr))
	  if (cmptr->cmsg_level == IPPROTO_IP && cmptr->cmsg_type == IP_PKTINFO)
	    {
	      union {
		unsigned char *c;
		struct in_pktinfo *p;
	      } p;
	      p.c = CMSG_DATA(cmptr);
	      dst_addr_4 = dst_addr.addr.addr4 = p.p->ipi_spec_dst;
	      if_index = p.p->ipi_ifindex;
	    }
#elif defined(IP_RECVDSTADDR) && defined(IP_RECVIF)
      if (listen->family == AF_INET)
	{
	  for (cmptr = CMSG_FIRSTHDR(&msg); cmptr; cmptr = CMSG_NXTHDR(&msg, cmptr))
	    {
	      union {
		unsigned char *c;
		unsigned int *i;
		struct in_addr *a;
#ifndef HAVE_SOLARIS_NETWORK
		struct sockaddr_dl *s;
#endif
	      } p;
	       p.c = CMSG_DATA(cmptr);
	       if (cmptr->cmsg_level == IPPROTO_IP && cmptr->cmsg_type == IP_RECVDSTADDR)
		 dst_addr_4 = dst_addr.addr.addr4 = *(p.a);
	       else if (cmptr->cmsg_level == IPPROTO_IP && cmptr->cmsg_type == IP_RECVIF)
#ifdef HAVE_SOLARIS_NETWORK
		 if_index = *(p.i);
#else
  	         if_index = p.s->sdl_index;
#endif
	    }
	}
#endif
      
#ifdef HAVE_IPV6
      if (listen->family == AF_INET6)
	{
	  for (cmptr = CMSG_FIRSTHDR(&msg); cmptr; cmptr = CMSG_NXTHDR(&msg, cmptr))
	    if (cmptr->cmsg_level == IPPROTO_IPV6 && cmptr->cmsg_type == daemon->v6pktinfo)
	      {
		union {
		  unsigned char *c;
		  struct in6_pktinfo *p;
		} p;
		p.c = CMSG_DATA(cmptr);
		  
		dst_addr.addr.addr6 = p.p->ipi6_addr;
		if_index = p.p->ipi6_ifindex;
	      }
	}
#endif
      
      /* enforce available interface configuration */
      
      if (!indextoname(listen->fd, if_index, ifr.ifr_name) ||
	  !iface_check(listen->family, &dst_addr, ifr.ifr_name))
	return;
      
      if (listen->family == AF_INET && option_bool(OPT_LOCALISE))
	{
	  struct irec *iface;
	  
	  /* get the netmask of the interface whch has the address we were sent to.
	     This is no neccessarily the interface we arrived on. */
	  
	  for (iface = daemon->interfaces; iface; iface = iface->next)
	    if (iface->addr.sa.sa_family == AF_INET &&
		iface->addr.in.sin_addr.s_addr == dst_addr_4.s_addr)
	      break;
	  
	  /* interface may be new */
	  if (!iface)
	    enumerate_interfaces(); 
	  
	  for (iface = daemon->interfaces; iface; iface = iface->next)
	    if (iface->addr.sa.sa_family == AF_INET &&
		iface->addr.in.sin_addr.s_addr == dst_addr_4.s_addr)
	      break;
	  
	  /* If we failed, abandon localisation */
	  if (iface)
	    netmask = iface->netmask;
	  else
	    dst_addr_4.s_addr = 0;
	}
    }

  if (extract_request(header, (size_t)n, daemon->namebuff, &type))
    {
      char types[20];

      querystr(types, type);
      
      if (listen->family == AF_INET) 
	log_query(F_QUERY | F_IPV4 | F_FORWARD, daemon->namebuff, 
		  (struct all_addr *)&source_addr.in.sin_addr, types);
#ifdef HAVE_IPV6
      else
	log_query(F_QUERY | F_IPV6 | F_FORWARD, daemon->namebuff, 
		  (struct all_addr *)&source_addr.in6.sin6_addr, types);
#endif
    }

#ifdef __SC_BUILD__

#define P_DOMAIN   "speedport.ip"
  /*
   * Inform ppp daemon to bring ppp connection up when we receive a DSN query
   * from lan.
   */
  do {
      if(!dod_is_ready())
          break;

      if(listen->family == AF_INET) {
          static struct in_addr local_addr;

          if(local_addr.s_addr == 0)
              local_addr.s_addr = get_if_addr("br0");
          if((source_addr.in.sin_addr.s_addr != local_addr.s_addr) && (strcmp(daemon->namebuff,P_DOMAIN) != 0))
              dod_up();
      }
      else if (listen->family == AF_INET6) {
          char local_addr6[INET6_ADDRSTRLEN];
          char source_addr6[INET6_ADDRSTRLEN];

          memset(local_addr6, 0, sizeof(local_addr6));
          get_if_addr6("br0", local_addr6);
          if (inet_ntop(AF_INET6, &(source_addr.in6.sin6_addr), source_addr6, 
                        INET6_ADDRSTRLEN) && strlen(local_addr6) != 0) {
              if ((strcmp(source_addr6, local_addr6) != 0) && 
                  (strcmp(daemon->namebuff, P_DOMAIN) != 0))
              {
                  dod_up();
              }
          }
      }
      else {
      }
  } while(0);

#endif

#ifdef __SC_BUILD__
  /* when lan pc send lan PTR dns request, we will drop it */
  if(type == T_PTR)
  {
      if(strlen(lan_ip_subnet) != 0)
      {
          if(strstr(daemon->namebuff, lan_ip_subnet) != NULL)
          {
              m = answer_request (header, ((char *) header) + PACKETSZ, (size_t)n, 
                                  dst_addr_4, netmask, now);

              if (m >= 1)
              {
                  send_from(listen->fd, option_bool(OPT_NOWILD), (char *)header, 
                            m, &source_addr, &dst_addr, if_index);
                  daemon->local_answer++;
              }
             else 
              {
                  unsigned char *ansp;
                  ansp = skip_questions(header, (size_t)n);
                  if(ansp) {
                      header->hb3 |= HB3_QR; 
                      SET_RCODE(header, SERVFAIL);
                      send_from(listen->fd, option_bool(OPT_NOWILD), (char *)header, 
                                ansp - (unsigned char *)header, &source_addr, &dst_addr, if_index);
                      daemon->local_answer++;
                  }
              }
             return;
          }
      }
  }
#endif

  m = answer_request (header, ((char *) header) + PACKETSZ, (size_t)n, 
                     dst_addr_4, netmask, now);
  if (m >= 1)
    {
      send_from(listen->fd, option_bool(OPT_NOWILD), (char *)header, 
		m, &source_addr, &dst_addr, if_index);
      daemon->local_answer++;
    }
#ifdef __SC_BUILD__
  else if ( dhcp_server_domain && strstr(daemon->namebuff, dhcp_server_domain) != NULL)
  {
      unsigned char *ansp;
      ansp = skip_questions(header, (size_t)n);
      if(ansp) {
          header->hb3 |= HB3_QR; 
          SET_RCODE(header, SERVFAIL);
          send_from(listen->fd, option_bool(OPT_NOWILD), (char *)header, 
                    ansp - (unsigned char *)header, &source_addr, &dst_addr, if_index);
          daemon->local_answer++;
      }
  }
#endif
  else if (OPCODE(header) != 2 && forward_query(listen->fd, &source_addr, &dst_addr, if_index,
                        header, (size_t)n, now, NULL))
    daemon->queries_forwarded++;
  else
    daemon->local_answer++;
}

/* The daemon forks before calling this: it should deal with one connection,
   blocking as neccessary, and then return. Note, need to be a bit careful
   about resources for debug mode, when the fork is suppressed: that's
   done by the caller. */
unsigned char *tcp_request(int confd, time_t now,
			   union mysockaddr *local_addr, struct in_addr netmask)
{
  size_t size = 0;
  int norebind = 0;
  int checking_disabled;
  size_t m;
  unsigned short qtype, gotname;
  unsigned char c1, c2;
  /* Max TCP packet + slop */
  unsigned char *packet = whine_malloc(65536 + MAXDNAME + RRFIXEDSZ);
  unsigned char *payload = NULL;
  struct dns_header *header;
  struct server *last_server;
  struct in_addr dst_addr_4;
  union mysockaddr peer_addr;
  socklen_t peer_len = sizeof(union mysockaddr);

  if (getpeername(confd, (struct sockaddr *)&peer_addr, &peer_len) == -1)
    return packet;

  while (1)
    {
#ifdef __SC_BUILD__
        do {
            fd_set rfds;

            FD_ZERO(&rfds);
            FD_SET(confd, &rfds);

            struct timeval tv;
            tv.tv_sec = 2;
            tv.tv_usec = 0;
            if(select(confd+1, &rfds, NULL, NULL, &tv) <= 0 || !FD_ISSET(confd, &rfds))
                return packet;

        } while(0);
#endif
      if (!packet ||
	  !read_write(confd, &c1, 1, 1) || !read_write(confd, &c2, 1, 1) ||
	  !(size = c1 << 8 | c2) ||
	  !read_write(confd, packet, size, 1))
       	return packet; 
  
      if (size < (int)sizeof(struct dns_header))
	continue;

      /* Clear buffer beyond request to avoid risk of
	 information disclosure. */
      payload = &packet[2];
      memset(payload + size, 0, 65536 - size);
      
      header = (struct dns_header *)packet;

      /* save state of "cd" flag in query */
      checking_disabled = header->hb4 & HB4_CD;
       
#ifndef __SC_BUILD__
      /* 
       * Fixed HPQC-14504
       * 1. DNS Proxy will transparently pass the AD Flag of a DNS query to upstream DNS servers
       * 2. DNS Proxy will does not validate the response so AG must not set the AD Flag in the dns response to LAN hosts 
       */
      /* RFC 4035: sect 4.6 para 2 */
      header->hb4 &= ~HB4_AD;
#endif
      
      if ((gotname = extract_request(header, (unsigned int)size, daemon->namebuff, &qtype)))
	{
	  char types[20];
	  
	  querystr(types, qtype);
	  
	  if (peer_addr.sa.sa_family == AF_INET) 
	    log_query(F_QUERY | F_IPV4 | F_FORWARD, daemon->namebuff, 
		      (struct all_addr *)&peer_addr.in.sin_addr, types);
#ifdef HAVE_IPV6
	  else
	    log_query(F_QUERY | F_IPV6 | F_FORWARD, daemon->namebuff, 
		      (struct all_addr *)&peer_addr.in6.sin6_addr, types);
#endif
	}
      
      if (local_addr->sa.sa_family == AF_INET)
	dst_addr_4 = local_addr->in.sin_addr;
      else
	dst_addr_4.s_addr = 0;
      
      /* m > 0 if answered from cache */
      m = answer_request(header, ((char *) header) + 65536, (unsigned int)size, 
			 dst_addr_4, netmask, now);

      /* Do this by steam now we're not in the select() loop */
      check_log_writer(NULL); 
      
      if (m == 0)
	{
	  unsigned int flags = 0;
	  struct all_addr *addrp = NULL;
	  int type = 0;
	  char *domain = NULL;
	   
	  if (option_bool(OPT_ADD_MAC))
	    size = add_mac(header, size, ((char *) header) + 65536, &peer_addr);
	          
	  if (gotname)
	    flags = search_servers(now, &addrp, gotname, daemon->namebuff, &type, &domain, &norebind);
	  
	  if (type != 0  || option_bool(OPT_ORDER) || !daemon->last_server)
	    last_server = daemon->servers;
	  else
	    last_server = daemon->last_server;
      
	  if (!flags && last_server)
	    {
	      struct server *firstsendto = NULL;
	      unsigned int crc = questions_crc(header, (unsigned int)size, daemon->namebuff);

	      /* Loop round available servers until we succeed in connecting to one.
	         Note that this code subtley ensures that consecutive queries on this connection
	         which can go to the same server, do so. */
	      while (1) 
 		{
		  if (!firstsendto)
		    firstsendto = last_server;
		  else
		    {
		      if (!(last_server = last_server->next))
			last_server = daemon->servers;
		      
		      if (last_server == firstsendto)
			break;
		    }
	      
		  /* server for wrong domain */
		  if (type != (last_server->flags & SERV_TYPE) ||
		      (type == SERV_HAS_DOMAIN && !hostname_isequal(domain, last_server->domain)))
		    continue;

		  if (last_server->tcpfd == -1)
		    {
		      if ((last_server->tcpfd = socket(last_server->addr.sa.sa_family, SOCK_STREAM, 0)) == -1)
			continue;
		      
		      if ((!local_bind(last_server->tcpfd,  &last_server->source_addr, last_server->interface, 1) ||
			   connect(last_server->tcpfd, &last_server->addr.sa, sa_len(&last_server->addr)) == -1))
			{
			  close(last_server->tcpfd);
			  last_server->tcpfd = -1;
			  continue;
			}

#ifdef HAVE_CONNTRACK
		      /* Copy connection mark of incoming query to outgoing connection. */
		      if (option_bool(OPT_CONNTRACK))
			{
			  unsigned int mark;
			  struct all_addr local;
#ifdef HAVE_IPV6		      
			  if (local_addr->sa.sa_family == AF_INET6)
			    local.addr.addr6 = local_addr->in6.sin6_addr;
			  else
#endif
			    local.addr.addr4 = local_addr->in.sin_addr;
			  
			  if (get_incoming_mark(&peer_addr, &local, 1, &mark))
			    setsockopt(last_server->tcpfd, SOL_SOCKET, SO_MARK, &mark, sizeof(unsigned int));
			}
#endif	
		    }

		  c1 = size >> 8;
		  c2 = size;
		  
		  if (!read_write(last_server->tcpfd, &c1, 1, 0) ||
		      !read_write(last_server->tcpfd, &c2, 1, 0) ||
		      !read_write(last_server->tcpfd, packet, size, 0) ||
		      !read_write(last_server->tcpfd, &c1, 1, 1) ||
		      !read_write(last_server->tcpfd, &c2, 1, 1))
		    {
		      close(last_server->tcpfd);
		      last_server->tcpfd = -1;
		      continue;
		    } 
		  
		  m = (c1 << 8) | c2;
		  if (!read_write(last_server->tcpfd, packet, m, 1))
		    return packet;
		  
		  if (!gotname)
		    strcpy(daemon->namebuff, "query");
		  if (last_server->addr.sa.sa_family == AF_INET)
		    log_query(F_SERVER | F_IPV4 | F_FORWARD, daemon->namebuff, 
			      (struct all_addr *)&last_server->addr.in.sin_addr, NULL); 
#ifdef HAVE_IPV6
		  else
		    log_query(F_SERVER | F_IPV6 | F_FORWARD, daemon->namebuff, 
			      (struct all_addr *)&last_server->addr.in6.sin6_addr, NULL);
#endif 
		  
		  /* There's no point in updating the cache, since this process will exit and
		     lose the information after a few queries. We make this call for the alias and 
		     bogus-nxdomain side-effects. */
		  /* If the crc of the question section doesn't match the crc we sent, then
		     someone might be attempting to insert bogus values into the cache by 
		     sending replies containing questions and bogus answers. */
		  if (crc == questions_crc(header, (unsigned int)m, daemon->namebuff))
#ifdef __SC_BUILD__
		    m = process_reply(header, now, last_server, (unsigned int)m, 
				      option_bool(OPT_NO_REBIND) && !norebind, checking_disabled, 1, qtype);
#else
		    m = process_reply(header, now, last_server, (unsigned int)m, 
				      option_bool(OPT_NO_REBIND) && !norebind, checking_disabled);
#endif
		  
		  break;
		}
	    }
	  
	  /* In case of local answer or no connections made. */
	  if (m == 0)
	    m = setup_reply(header, (unsigned int)size, addrp, flags, daemon->local_ttl);
	}

      check_log_writer(NULL);
      
      c1 = m>>8;
      c2 = m;
      if (!read_write(confd, &c1, 1, 0) ||
	  !read_write(confd, &c2, 1, 0) || 
	  !read_write(confd, packet, m, 0))
	return packet;
    }
}

static struct frec *allocate_frec(time_t now)
{
  struct frec *f;
  
  if ((f = (struct frec *)whine_malloc(sizeof(struct frec))))
    {
      f->s_type = 0;
      f->next = daemon->frec_list;
      f->time = now;
      f->sentto = NULL;
      f->rfd4 = NULL;
      f->flags = 0;
      f->plen = 0;
      f->s_type = 0;
#ifdef __SC_BUILD__
      f->new_id = 0;
      f->err_code = SERVFAIL;
      memset(f->retry_new_id, 0, sizeof(f->retry_new_id));
      //sc_transcation_id_dump("new", f);
#endif
#ifdef HAVE_IPV6
      f->rfd6 = NULL;
#endif
      gettimeofday(&f->tv,NULL);
      memset(f->header, 0, sizeof(*f->header));
      daemon->frec_list = f;
    }

  return f;
}

static struct randfd *allocate_rfd(int family)
{
  static int finger = 0;
  int i;

  /* limit the number of sockets we have open to avoid starvation of 
     (eg) TFTP. Once we have a reasonable number, randomness should be OK */

  for (i = 0; i < RANDOM_SOCKS; i++)
    if (daemon->randomsocks[i].refcount == 0)
      {
	if ((daemon->randomsocks[i].fd = random_sock(family)) == -1)
	  break;
      
	daemon->randomsocks[i].refcount = 1;
	daemon->randomsocks[i].family = family;
	return &daemon->randomsocks[i];
      }

  /* No free ones or cannot get new socket, grab an existing one */
  for (i = 0; i < RANDOM_SOCKS; i++)
    {
      int j = (i+finger) % RANDOM_SOCKS;
      if (daemon->randomsocks[j].refcount != 0 &&
	  daemon->randomsocks[j].family == family && 
	  daemon->randomsocks[j].refcount != 0xffff)
	{
	  finger = j;
	  daemon->randomsocks[j].refcount++;
	  return &daemon->randomsocks[j];
	}
    }

  return NULL; /* doom */
}

static void free_frec(struct frec *f)
{
  if (f->rfd4 && --(f->rfd4->refcount) == 0)
    close(f->rfd4->fd);
  
  f->rfd4 = NULL;
  f->sentto = NULL;
  f->flags = 0;
  f->plen = 0;
  f->s_type = 0;
#ifdef __SC_BUILD__
  f->new_id = 0;
  f->err_code = SERVFAIL;
  memset(f->retry_new_id, 0, sizeof(f->retry_new_id));
  //sc_transcation_id_dump("free", f);
#endif
  memset(f->header, 0, sizeof(*f->header));

#ifdef HAVE_IPV6
  if (f->rfd6 && --(f->rfd6->refcount) == 0)
    close(f->rfd6->fd);
    
  f->rfd6 = NULL;
#endif
}

/* if wait==NULL return a free or older than TIMEOUT record.
   else return *wait zero if one available, or *wait is delay to
   when the oldest in-use record will expire. Impose an absolute
   limit of 4*TIMEOUT before we wipe things (for random sockets) */
struct frec *get_new_frec(time_t now, int *wait)
{
  struct frec *f, *oldest, *target;
  int count;
  
  if (wait)
    *wait = 0;

  for (f = daemon->frec_list, oldest = NULL, target =  NULL, count = 0; f; f = f->next, count++)
    if (!f->sentto)
      target = f;
    else 
      {
	if (difftime(now, f->time) >= 4*TIMEOUT)
	  {
	    free_frec(f);
	    target = f;
	  }
	
	if (!oldest || difftime(f->time, oldest->time) <= 0)
	  oldest = f;
      }

  if (target)
    {
      target->time = now;
      return target;
    }
  
  /* can't find empty one, use oldest if there is one
     and it's older than timeout */
  if (oldest && ((int)difftime(now, oldest->time)) >= TIMEOUT)
    { 
      /* keep stuff for twice timeout if we can by allocating a new
	 record instead */
      if (difftime(now, oldest->time) < 2*TIMEOUT && 
	  count <= daemon->ftabsize &&
	  (f = allocate_frec(now)))
	return f;

      if (!wait)
	{
	  free_frec(oldest);
	  oldest->time = now;
	}
      return oldest;
    }
  
  /* none available, calculate time 'till oldest record expires */
  if (count > daemon->ftabsize)
    {
      if (oldest && wait)
	*wait = oldest->time + (time_t)TIMEOUT - now;
      return NULL;
    }
  
  if (!(f = allocate_frec(now)) && wait)
    /* wait one second on malloc failure */
    *wait = 1;

  return f; /* OK if malloc fails and this is NULL */
}
 
#if 0
void sc_transcation_id_dump(char *str, struct frec *f)
{
   my_syslog(LOG_INFO, "<%s, %s>%04x-%04x-%04x-%04x - %04x-%04x-%04x-%04x\n", __FUNCTION__, str,  
             f->retry_new_id[0][0], f->retry_new_id[0][1], f->retry_new_id[0][2],
             f->retry_new_id[0][3], f->retry_new_id[1][0], f->retry_new_id[1][1], 
             f->retry_new_id[1][2], f->retry_new_id[1][3]);
}
#endif

static int sc_transcation_id_check(unsigned short id, struct frec *f)
{
#if 0
   my_syslog(LOG_INFO, "<%s>%04x,%04x,%04x,%04x - %04x,%04x,%04x,%04x\n", __FUNCTION__, 
             f->retry_new_id[0][0], f->retry_new_id[0][1], f->retry_new_id[0][2],
             f->retry_new_id[0][3], f->retry_new_id[1][0], f->retry_new_id[1][1], 
             f->retry_new_id[1][2], f->retry_new_id[1][3]);
#endif
   if(f->retry_new_id[0][0]==id || 
      f->retry_new_id[0][1]==id ||
      f->retry_new_id[0][2]==id ||
      f->retry_new_id[0][3]==id ||
      f->retry_new_id[1][0]==id ||   
      f->retry_new_id[1][1]==id ||
      f->retry_new_id[1][2]==id || 
      f->retry_new_id[1][3]==id) 
       return 1;
   else
       return 0;
}

/* crc is all-ones if not known. */
static struct frec *lookup_frec(unsigned short id, unsigned int crc)
{
  struct frec *f;

  for(f = daemon->frec_list; f; f = f->next)
  {
    if (f->sentto && (f->new_id == id || sc_transcation_id_check(id, f)) && 
	(f->crc == crc || crc == 0xffffffff))
    {
      return f;
    }
  }
     
  return NULL;
}

static struct frec *lookup_frec_by_sender(unsigned short id,
					  union mysockaddr *addr,
					  unsigned int crc)
{
  struct frec *f;

  for(f = daemon->frec_list; f; f = f->next)
    if (f->sentto &&
	f->orig_id == id && 
	f->crc == crc &&
	sockaddr_isequal(&f->source, addr))
      return f;
   
  return NULL;
}

/* A server record is going away, remove references to it */
void server_gone(struct server *server)
{
  struct frec *f;
  
  for (f = daemon->frec_list; f; f = f->next)
    if (f->sentto && f->sentto == server)
      free_frec(f);
  
  if (daemon->last_server == server)
    daemon->last_server = NULL;

  if (daemon->srv_save == server)
    daemon->srv_save = NULL;
}

/* return unique random ids. */
static unsigned short get_id(unsigned int crc)
{
  unsigned short ret = 0;
  
  do 
#ifdef __SC_BUILD__
  {
      unsigned char ran[2] = {0};
      get_random_bytes(ran,sizeof(ran));
      ret = (ran[0] << 8) + ran[1];
  }
  while (lookup_frec(ret, crc) || check_standard_deviation(ret,daemon->id));
  my_syslog(LOG_ERR, _("get transaction id = %04x"), ret);
#else
    ret = rand16();
  while (lookup_frec(ret, crc));
#endif
  return ret;
}

static double difftimeval(struct timeval now, struct timeval tv)
{
    double d;
    time_t s;
    suseconds_t u;

    s = now.tv_sec - tv.tv_sec;
    u = now.tv_usec - tv.tv_usec;

    d = s;
    d *= 1000000.0;
    d += u;

    return d;
}

/* A server record is going away, remove references to it */
void retry_dns_query(void)
{
    struct timeval now;
    struct frec *f;
    char ipv6_buf[50] = {0};
    int dyn_retry_interval = 0;
    gettimeofday(&now,NULL);

    for(f = daemon->frec_list; f; f = f->next)
    {
        //If the last voip server, delay the retry interval to 8s.
        if((f->s_type != 0) && (f->lastserverflag==1) && voip_server_check(f->orig_name, f->hash) == 0)
            dyn_retry_interval = 8000000;
        else
            dyn_retry_interval = retry_interval;

        if (f->s_type != 0 && difftimeval(now, f->tv) >= dyn_retry_interval)
        {
            char *domain = NULL;
            int dns_type = 0, type = 0, send_num = 0, plen = 0;
            struct all_addr *addrp = NULL;
            //unsigned int flags = 0;
            unsigned int gotname = 0;
            struct server *start = NULL;
            union mysockaddr *udpaddr = NULL;
            struct all_addr *dst_addr = NULL;
            struct dns_header *header = (struct dns_header *)(f->header);
            int forwarded = 0;

  
            /* check for send errors here (no route to host) 
               if we fail to send to all nameservers, send back an error
               packet straight away (helps modem users when offline)  */

            if (f->sentto)
            {
                start = f->sentto;
                dns_type = f->s_type;
                if((dns_type != 1 && dns_type != 3) || f->single_dns == 1) 
                {
                    if( start->next && start->next != daemon->servers)
                        start = start->next;
                    else
                    {
                        my_syslog(LOG_INFO, _("free frec for no server ")); 
                        if(f->ipv6_flag == 1)
                        {
                            p008_sysylog_timeout(f, now);
                        }

                        /* add send server fail to station when all of retries are timeout */
                        int udpfd=f->fd;
                        
                        if(udpfd!=-1)
                        {
                            unsigned int flags = F_NEG;

                            /* recover transaction id */
                            header->id = f->orig_id;
                           
                            /* 
                             * Fixed HPQC-14504
                             * 1. DNS Proxy will transparently pass the AD Flag of a DNS query to upstream DNS servers
                             * 2. DNS Proxy will does not validate the response so AG must not set the AD Flag in the dns response to LAN hosts 
                             */ 
                            /* RFC 4035: sect 4.6 para 2 */
                            //header->hb4 &= ~HB4_AD;

                            if(f->err_code == SERVFAIL)
                               flags = F_NEG;
                            else
                               flags = F_REVERSE;

                            /* fix flags=F_NEG means server fail */
                            plen = setup_reply(header, f->orig_size, f->orig_addrp, flags, 86400);
                            /* change domain name to orig name */
                            
                            my_syslog(LOG_INFO, _(" free frec orig name is %s\n"), f->orig_name); 
                            resume_domain(header, plen,f->orig_name);

                            send_from(udpfd, option_bool(OPT_NOWILD), (char *)header, plen, &(f->source), &(f->dest), f->iface);
                        }
                        /* end */
                        free_frec(f); /* cancel */
                        if(f->next == daemon->frec_list)
                            break;
                        else
                            continue;
                    }
                }

                domain = f->sentto->domain;
                udpaddr = &(f->source);
                dst_addr = &(f->dest);
                plen = f->plen;
                my_syslog(LOG_INFO, _("resend dns query when time out")); 
                gotname = extract_request(header, plen, daemon->namebuff, NULL);
                
                header->id = get_id(f->crc);
                f->new_id = header->id;

                /* change DNS pocket domain name */
                create_newname_follow_bit20(f->new_name);
                /* put the changed domain name to the pocket */
                resume_domain(header, plen, f->new_name);
                strcpy(daemon->namebuff, f->new_name);

                while (1)
                { 
                    /* only send to servers dealing with our domain.
                       domain may be NULL, in which case server->domain 
                       must be NULL also. */

                    if (type == (start->flags & SERV_TYPE) &&
                            (type != SERV_HAS_DOMAIN || hostname_isequal(domain, start->domain)) &&
                            !(start->flags & SERV_LITERAL_ADDRESS))
                    {
                        int fd;

                        /* find server socket to use, may need to get random one. */
                        if (start->sfd)
                            fd = start->sfd->fd;
                        else 
                        {
#ifdef HAVE_IPV6
                            if (start->addr.sa.sa_family == AF_INET6)
                            {
                                if (!f->rfd6 &&
                                        !(f->rfd6 = allocate_rfd(AF_INET6)))
                                    break;
                                daemon->rfd_save = f->rfd6;
                                fd = f->rfd6->fd;
                            }
                            else
#endif
                            {
                                if (!f->rfd4 &&
                                        !(f->rfd4 = allocate_rfd(AF_INET)))
                                    break;
                                daemon->rfd_save = f->rfd4;
                                fd = f->rfd4->fd;
                            }

#ifdef HAVE_CONNTRACK
                            /* Copy connection mark of incoming query to outgoing connection. */
                            if (option_bool(OPT_CONNTRACK))
                            {
                                unsigned int mark;
                                if (get_incoming_mark(udpaddr, dst_addr, 0, &mark))
                                    setsockopt(fd, SOL_SOCKET, SO_MARK, &mark, sizeof(unsigned int));
                            }
#endif
                        }
                        if (sendto(fd, (char *)(header), plen, 0,
                                    &start->addr.sa,
                                    sa_len(&start->addr)) != -1)
                        {
                            /* Keep info in case we want to re-send this packet */
                            daemon->srv_save = start;
                            daemon->packet_len = plen;

                            if (!gotname)
                                strcpy(daemon->namebuff, "query");
                            if (start->addr.sa.sa_family == AF_INET)
                                log_query(F_SERVER | F_IPV4 | F_FORWARD, daemon->namebuff, 
                                        (struct all_addr *)&start->addr.in.sin_addr, NULL); 
#ifdef HAVE_IPV6
                            else
                                log_query(F_SERVER | F_IPV6 | F_FORWARD, daemon->namebuff, 
                                        (struct all_addr *)&start->addr.in6.sin6_addr, NULL);
#endif 


                            start->queries++;
                            forwarded = 1;
                            f->sentto = start;
                            f->forwardall++;
                            f->s_type = start->s_type;
                            f->single_dns = 0;
                            gettimeofday(&f->tv,NULL);
                            send_num++;

                            if(send_num == 2)//all of the sec about 2nd, 4th, and 5th 
                            {
                                if(start->s_type==2)//2nd pppv6_sec
                                    f->retry_new_id[0][2] = header->id;
                                else if(start->s_type==4)//4th pppv4_sec
                                    f->retry_new_id[1][1] = header->id;
                                else//5th dhcpv4_sec
                                    f->retry_new_id[1][3] = header->id;
                                if (!(start->next))
                                    f->lastserverflag = 1;
                                break;
                            }
                            else if(f->s_type == 3 && f->pppv4_send == 0)//3th pppv4_pri
                            {
                                f->retry_new_id[0][3] = header->id;
                                f->pppv4_send = 1;
                                if (!(start->next))
                                    f->lastserverflag = 1;
                                break;
                            }
                            else//all of the pri about 2nd, 4th, and 5th
                            {
                                if(start->s_type==1)//2nd pppv6_pri
                                    f->retry_new_id[0][1] = header->id;
                                else if(start->s_type==3)//4th pppv4_pri
                                    f->retry_new_id[1][0] = header->id;
                                else//5th dhcpv4_pri
                                    f->retry_new_id[1][2] = header->id;
                                header->id = get_id(f->crc);
                                if( f->s_type == 3 && f->pppv4_send == 1)
                                    f->pppv4_send = 0;
                            }
                        }
                        else
                            my_syslog(LOG_INFO, _("sent to fail")); 
                    } 

                    if (!(start = start->next))
                        start = daemon->servers;

                    /* change DNS pocket domain name */
                    create_newname_follow_bit20(f->new_name);
                    /* put the changed domain name to the pocket */
                    resume_domain(header, plen, f->new_name);
                    strcpy(daemon->namebuff, f->new_name);

                    if(send_num == 1 && (f->s_type + 1) !=  start->s_type)
                    {
                        f->single_dns = 1;
                        break;
                    }

                    if (start == daemon->servers)
                        break;
                }
            }	  
            if (!forwarded)
            {
                my_syslog(LOG_INFO, _("free frec for forward fail")); 
                free_frec(f); /* cancel */
            }
        }
        if(f->next == daemon->frec_list)
            break;
    }
}
