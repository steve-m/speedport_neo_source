/* $Id: libsrv.c,v 1.4 2002/10/02 13:28:11 vanrein Exp $
 *
 * libsrv.c --- Make a connection to a service described with SRV records.
 *
 * A simple library to quickly allocate a socket on either side of a network
 * connection.  Much simpler than classical sockets, and much better too.
 * Tries IN SRV records first, continues to IN A if none defined.
 *
 * By default, it even forks a new server process for every server connection!
 * This can be overridden, and manual accept() and handling can then be done.
 * Do not expect too much -- for a more complex solution, consider RULI,
 *	http://ruli.sourceforge.net
 *
 * From: Rick van Rein <admin@FingerHosting.com>
 */


/* EXAMPLE USE:
 *
 *	In your DNS config, setup SRV records for a service, say:
 *		_hello._tcp.vanrein.org IN SRV 1234 0 0 bakkerij.orvelte.nep.
 *	Meaning:
 *	 - The hello protocol runs over tcp
 *	 - The server is on port 1234 of host bakkerij.orvelte.nep
 *	 - The zeroes are for load balancing
 *
 *	A hello client starting for this domain looks up the above record and
 *	returns a socket of a network client when invoked as follows:
 *		insrv_client ("finger", "tcp", "vanrein.org");
 *
 *	A hello server started on the server host looks up the same record
 *	and starts service for hello over TCP when it finds one of its names
 *	in the record; a client-connected socket is returned from:
 *		insrv_server ("finger", "tcp", "vanrein.org");
 *	Unless told otherwise, this routine forks off for every connection
 *	to the server.  So, the server can process the request on the
 *	returned socket, close it and exit.
 *
 *	When both calls have completed, they are connected and can start
 *	running the Jabber protocol over their respective sockets.
 */

#define BIND_4_COMPAT

//#include <arpa/srvname.h>
#include "./include/arpa/srvname.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>

#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <syslog.h>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h>
#include "libsrv.h"
#include <stdbool.h>
#include <sys/stat.h>
#include <bits/uClibc_mutex.h>
#include <ctype.h>

/*#define __USE_DMALLOC__     1 */
#ifdef __USE_DMALLOC__
#include "dmalloc.h"
#endif

#define TCP_DNS_SUPPORT 1

#undef DEBUG
/*#define DEBUG*/

/*louis add*/
typedef union sockaddr46_t {
	struct sockaddr sa;
	struct sockaddr_in sa4;
	struct sockaddr_in6 sa6;

} sockaddr46_t;

#include <sys/syscall.h>

#define USE_SELECT

extern pthread_mutex_t __resolv_lock;
#define BIGLOCK	    pthread_mutex_lock(&__resolv_lock);
#define BIGUNLOCK   pthread_mutex_unlock(&__resolv_lock);

/* Protected by __resolv_lock */
void (*__res_sync)(void);
/*uint32_t __resolv_opts; */
uint8_t __resolv_timeout = RES_TIMEOUT;
uint8_t __resolv_attempts = RES_DFLRETRY;
unsigned __nameservers;
unsigned __searchdomains;
sockaddr46_t *__nameserver;
char **__searchdomain;
const struct sockaddr_in __local_nameserver = {
	.sin_family = AF_INET,
	.sin_port = NAMESERVER_PORT,
};

void __close_nameservers(void);
void __open_nameservers(void);

/*louis end*/

/* Melinda, 2014/06/26
Format of SRV RR Record:
Item            Length      Offset
Query Name      random (use dn_skipname to skip it)
-----------------------------------------------------
Type            2           0
Class           2           2
TTL             4           4
Data Length     2           8
-----------------------------------------------------
Cost            2           10 (RRFIXEDSZ+0)
Weight          2           12 (RRFIXEDSZ+2)
Port            2           14 (RRFIXEDSZ+4)
Target Server   random      16 (RRFIXEDSZ+6)

*/

/* Common offsets into an SRV RR */
#define SRV_TYPE    0
#define SRV_CLASS   2
#define SRV_TTL     4
#define SRV_DLEN    8
#define SRV_COST    (RRFIXEDSZ+0)
#define SRV_WEIGHT  (RRFIXEDSZ+2)
#define SRV_PORT    (RRFIXEDSZ+4)
#define SRV_SERVER  (RRFIXEDSZ+6)
#define SRV_FIXEDSZ (RRFIXEDSZ+6)

#define TCP_PACKETSZ    1490
/* Data structures */
typedef struct
{
    unsigned char buf [TCP_PACKETSZ];
	int len;
}
iobuf;
typedef unsigned char name [TCP_PACKETSZ];
#define MAXNUM_SRV 30
#define MY_BUFFER_LENGTH    250

#ifdef DEBUG
#define DPRINTF(X,args...) fprintf(stderr, X, ##args)
#else
#define DPRINTF(X,args...)
#endif /* DEBUG */

/* Global variable for #listeners (no OS implements it, but let's play along) */
int _listen_nr = 10;

/* Local variable for SRV options */
static unsigned long int srv_flags = 0L;
char *sfile = "/tmp/SRVrecords.txt";
FILE *sfile_fd = NULL;

int __tcp_dns_lookup(const char *name, int id,
        int type,
        unsigned char **outpacket,
        struct resolv_answer *a);
        
int sc_tcp_dns_lookup(const char *name,
		int type,
		unsigned char **outpacket,
		struct resolv_answer *a);
		
int tcp_res_query(const char *dname, int id,int class, int type,
        unsigned char *answer, int anslen);

int __encode_question(const struct resolv_question *q,
        unsigned char *dest,
        int maxlen);
void  __decode_header(unsigned char *data,
        struct resolv_header *h);
static int __length_question(const unsigned char *data, int maxlen);
static int __decode_answer(const unsigned char *message, /* packet */
        int offset,
        int len, /* total packet len */
        struct resolv_answer *a);


/* Setup the SRV options when initialising -- invocation optional */
void insrv_init (unsigned long flags) {
	srv_flags = flags;
	res_init ();
}


/* Test the given SRV options to see if all are set */
int srv_testflag (unsigned long flags) {
	return ((srv_flags & flags) == flags) ? 1 : 0;
}


/* Compare two SRV records by priority and by (scattered) weight */
static int srvcmp (const void *left, const void *right) {
	int lcost = ntohs (((unsigned short **) left ) [0][5]);
	int rcost = ntohs (((unsigned short **) right) [0][5]);
	if (lcost == rcost) {
		lcost = -ntohs (((unsigned short **) left ) [0][6]);
		rcost = -ntohs (((unsigned short **) right) [0][6]);
	}
	if (lcost < rcost) {
		return -1;
	} else if (lcost > rcost) {
		return +1;
	} else {
		return  0;
	}
}
/* Melinda, limited stack size so use global variables */
iobuf query, names;
// Storage for fallback SRV list, constructed when DNS gives no SRV
unsigned char fallbacksrv [2*(MAXCDNAME+SRV_FIXEDSZ+MAXCDNAME)];
unsigned char *srv[MAXNUM_SRV];
name srvname;	/* size: 1025 */

//#define TEST    1
#ifdef TEST	        
int add_test_srv(char *domain, pDnsSrv *slist, int *no,int *normal_dns);   
#endif                 

 /* 2015/06/16, Melinda, remove server and proto parameters */
static int insrv_lookup (char *domain, pDnsSrv *slist, int maxno, int *no,int query_flag,int *family);
pthread_t query_thread_id;
typedef struct{
    char domain[MY_BUFFER_LENGTH];
    pDnsSrv *slist;
    int maxno;
    int no;
    int query_flag;
    int ret;
    int query_done;    
    int family;
}query_data;
query_data my_query_data;

/* Melinda, 2013/02/22 */
int query_ip_by_name(char *domain,int query_flag,char *ip,int ip_size,int *family)
{
    int rc;
    struct addrinfo hints, *res=NULL;	
    int ipv6_ok = 0, ipv4_ok = 0;
	
    //get ip from hostname
    if(!domain || !ip || !ip_size || !family){
        printf("$@@$ - %s Invalid input domain=%p ip=%s size=%d family=%p\n",__FUNCTION__,domain,ip,ip_size,family);
        return -1;
    }
    *family=AF_INET;  /* use ipv4 as default */
    memset(&hints, 0x00, sizeof(hints));
    /* Shannon 2013/10/21, always perform quad A and A query but we only save the results when we really have corresponding IP address */
    //printf("$@@$ - %s DNS SRV for domain %s query_flag=%d getaddrinfo IPv6\n",__FUNCTION__,domain,query_flag);
    hints.ai_family = AF_INET6;
    rc = getaddrinfo(domain, NULL, &hints, &res);
    if (rc == 0 && res) {
        if (query_flag & QUERY_FLAG_IPV6) {
            void *ptr;
            *family=hints.ai_family;
       	    memset(ip,0,ip_size);
       	    ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
            inet_ntop (res->ai_family, ptr, ip, ip_size);
            ipv6_ok = 1;
        }
        freeaddrinfo(res);
    }

    //printf("$@@$ - %s DNS SRV for domain %s query_flag=%d getaddrinfo IPv4\n",__FUNCTION__,domain,query_flag);
    hints.ai_family = AF_INET;
    rc = getaddrinfo(domain, NULL, &hints, &res);
     if (rc == 0 && res) {
        if (query_flag & QUERY_FLAG_IPV4) {
            if (ipv6_ok == 0) {
                void *ptr;
                *family=hints.ai_family;
       	        memset(ip,0,ip_size);
       	        ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
                inet_ntop (res->ai_family, ptr, ip, ip_size);
                ipv4_ok = 1;
            }
        }
        freeaddrinfo(res);
    }

    //printf("$@@$ - %s DNS SRV for domain %s query results IPv4=%d IPv6=%d\n",__FUNCTION__,domain,ipv4_ok,ipv6_ok);
    if (ipv4_ok == 0 && ipv6_ok == 0)
        return -1;
    return 0;
        
}

void *query_thread(void *arg)
{
    int ret=0;
    query_data *pdata=(query_data *)arg;
#ifdef TEST
    int normal_dns;    
    if(strcmp(pdata->domain,"mytest.com.tw")==0)
        add_test_srv(pdata->domain, pdata->slist, &pdata->no,&normal_dns);
    else{
        /* 2015/06/16, Melinda, remove server and proto parameters */
        ret = insrv_lookup (pdata->domain, pdata->slist, pdata->maxno, &pdata->no,pdata->query_flag,&pdata->family);  
        #if 0
        printf("$@@$ - %s %s %d simulate lookup timeout==10 second...\n",__FILE__,__FUNCTION__,__LINE__,pdata->ret); 
        sleep(10);
        #endif
    }
    
    /*sleep(DNS_SRV_TIMEOUT+1); */ /* wait for alarm to trigger */
#else    
    /* 2015/06/16, Melinda, remove server and proto parameters */
    ret = insrv_lookup (pdata->domain, pdata->slist, pdata->maxno, &pdata->no,pdata->query_flag,&pdata->family);  
#endif    
    pdata->ret=ret;
    //printf("$@@$ - %s %s %d insrv_lookup ret=%d\n",__FILE__,__FUNCTION__,__LINE__,pdata->ret);    
    pdata->query_done=1;    
    return NULL;
    
    
}
void alarm_wakeup (int signum, siginfo_t* siginfo, void* context)
{
   //printf("$@@$ - alarm_wakeup: call pthread_cancel of query_thread_id query_done=%d\n",my_query_data.query_done);
   if(!my_query_data.query_done){
        pthread_cancel(query_thread_id);
        my_query_data.query_done=2;
   }
   return;
}

/* Setup a client socket for the named service over the given protocol under
 * the given domain name.
 * Input:
 *		domain  - domain name to query (include service and protocol, e.g. _sip._udp.tel.t-online.de)
 * Output:
 * 		slist - buffer to save pDnsSrv pointer array (provide by caller)
 *		maxno  - slist array detph
 *		no - how many items we get and copy to slist
 */
/* 2015/06/16, Melinda, remove server and proto parameters */
static int insrv_lookup (char *domain, pDnsSrv *slist, int maxno, int *no,int query_flag,int *family) {
	/* 1. try connecting to all answers in turn
	   2. if no SRV records exist, lookup A record and AAAA record to connect to on stdport
	   3. return connection socket or error code */

	int error=0,rc=0;
	int ctr;
	int n=0,i;
	HEADER *nameshdr;
	unsigned char *here;
	int num_srv=0;
	char *srvip;
	struct addrinfo hints, *res=NULL;
	char   tmp_addr[MY_BUFFER_LENGTH];
	int query_ipv4 = 1;
    
	if(!slist || maxno<=0 || !no || !family || !domain)
		return -EINVAL;

        //printf("$@@$ %s domain=%s query_flag=%d\n", __FUNCTION__, domain, query_flag);
        *family = -1;
	memset(slist,0,maxno*2*sizeof(pDnsSrv)); /* Shannon 2013/08/22, we must store both IPv4 and IPv6 address, so need double of MaxSipSrv */
	srv_flags &= ~SRV_GOT_MASK;
	srv_flags |=  SRV_GOT_SRV;

	// Note that SRV records are only defined for class IN
	names.len=res_query (domain, C_IN, T_SRV, names.buf, PACKETSZ);
	
	if (names.len < 0) {
	    //printf("$@@$ - errno=%d %s\n",errno,strerror(errno));
	    error = -ENOENT;
		goto fallback;
	}
	nameshdr=(HEADER *) names.buf;

#ifdef TCP_DNS_SUPPORT

    if (nameshdr->tc)
    {     /*dns response is truncated, send TCP request*/
        iobuf names_tcp;

        // Note that SRV records are only defined for class IN
        DPRINTF("start tcp_res_query\n");
        names_tcp.len=tcp_res_query (domain, nameshdr->id+1,C_IN, T_SRV, names_tcp.buf, TCP_PACKETSZ);

        if(names_tcp.len < 0) {
	    error = -ENOENT;
	    DPRINTF("ERROR: tcp_res_query return -1\n");
            goto fallback;            
        }
        
        if (names_tcp.len > HFIXEDSZ)
        {
            memset(names.buf,0x00,names.len);
            names.len = names_tcp.len;
            DPRINTF("receive dns tcp response len=%d, dns data len=%d\n",names_tcp.len,names.len);
            memcpy(names.buf,names_tcp.buf,names_tcp.len);
        }
    }
#endif

	here=names.buf + HFIXEDSZ;
#if 0
	rnd=nameshdr->id; 	// Heck, gimme one reason why not!
#endif

    if (names.len < HFIXEDSZ)
    { /*Jacky 20150325, #56110, tmp solution. if ((names.len < HFIXEDSZ) || nameshdr->tc) {*/
        DPRINTF("ERROR: EMSGSIZE\n");
	error = -EMSGSIZE;
    }
	switch (nameshdr->rcode) {
		case 1:
			error = -EFAULT;
			goto fallback;
		case 2:
			error = -EAGAIN;
			goto fallback;
		case 3:
			error = -ENOENT;
			goto fallback;
		case 4:
			error = -ENOSYS;
			goto fallback;
		case 5:
			error = -EPERM;
			goto fallback;
		default:
			break;
	}
	if (ntohs (nameshdr->ancount) == 0) {
		error = -ENOENT;
		goto fallback;
	}
	if (ntohs (nameshdr->ancount) > MAXNUM_SRV) {
		error = -ERANGE;
		goto fallback;
	}
	for (ctr=ntohs (nameshdr->qdcount); ctr>0; ctr--) {
		int strlen=dn_skipname (here, names.buf+names.len);
		here += strlen + QFIXEDSZ;
	}
	for (ctr=ntohs (nameshdr->ancount); ctr>0; ctr--) {
		int strlen=dn_skipname (here, names.buf+names.len);


		here += strlen;
		srv [num_srv++] = here;
		here += SRV_FIXEDSZ;
		here += dn_skipname (here, names.buf+names.len);
	}

	//printf("num_srv=%d\n",num_srv);
	// In case an error occurred, there are no SRV records.
	// Fallback strategy now is: construct two. One with the domain name,
	// the other with the /standard/ service name prefixed.
	// Note: Assuming a domain without the service name prefixed!
fallback:
	if (error) {
		return error; // First error returned
	}
	// End of fallback construction, making sure that variables are defined
	// srv[] points to the SRV RR, num_srv counts the number of entries.
	// Every SRV RR has at least cost, weight, port and servername set.

#ifdef DEBUG
	for (ctr=0; ctr<num_srv; ctr++) {


		if (ns_name_ntop (srv [ctr]+SRV_SERVER, (char *)srvname, MAXDNAME) < 0) {
			continue;
		}
		
		printf ("$@@$ - Considering SRV server cost=%d w=%d port=%d TTL=%lu %s\n",
				ns_get16 (srv [ctr]+SRV_COST),
				ns_get16 (srv [ctr]+SRV_WEIGHT),
				ns_get16 (srv [ctr]+SRV_PORT),
				ns_get32(srv [ctr]+SRV_TTL),
                                (char *)srvname
			);
	}
	printf("\n");
#endif

#if 0
	// Overwrite weight with rnd-spread version to divide load over weights
	for (ctr=0; ctr<num_srv; ctr++) {
		*(unsigned short *)(srv [ctr]+SRV_WEIGHT)
			= rnd % (1+ns_get16 (srv [ctr]+SRV_WEIGHT));
	}
#endif
	qsort (srv, num_srv, sizeof (*srv), srvcmp);

        if(num_srv>=maxno) {
	    printf("$@@$ - query_sipsrv: num_srv=%d  exceed maxno=%d set to %d\n",num_srv,maxno,maxno);
	    num_srv=maxno;
	}
	
#ifdef DEBUG
	printf("$@@$ - After sorting:\n");
	for (ctr=0; ctr<num_srv; ctr++) {


		if (ns_name_ntop (srv [ctr]+SRV_SERVER, (char *)srvname, MAXDNAME) < 0) {
			continue;
		}
		printf ("$@@$ - server %d %d %d TTL=%lu %s\n",
				ns_get16 (srv [ctr]+SRV_COST),
				ns_get16 (srv [ctr]+SRV_WEIGHT),
				ns_get16 (srv [ctr]+SRV_PORT),
				ns_get32(srv [ctr]+SRV_TTL),
				(char *)srvname
			);
	}
	printf("\n");

#endif
	sfile_fd = fopen(sfile, "w+");
	/* Shannon 2013/08/05 DT on-site debug patch
	   change lists:
	   1. If DUT can't send SIP registration to IPv6 SIP server, we must try to send SIP registration to IPv4 SIP server
	   2. SIP server priority
	      -- priority 0 IPv6 SIP server (Highest)
	      -- priority 1 IPv6 SIP server
	      -- priority 0 IPv4 SIP server
	      -- priority 1 IPv4 SIP server (Lowest)
	   3. Remove printf for endurance test
	*/
	for (ctr=0; ctr<num_srv; ctr++) {
		pDnsSrv p;
		int len;
		#if 0 /* IPv4 only */
		struct hostent *host;
		#endif

		if (ns_name_ntop (srv [ctr]+SRV_SERVER, (char *)srvname, MAXDNAME) < 0) {
			continue;  /* ignore this item */
		}
		//get ip from hostname
		memset(&hints, 0x00, sizeof(hints));
		//if (query_flag) {
		/* Shannon 2013/10/20, change request from DT, always perform quad A and A query.
		   But we only save the results into slist when we really have corresponding IP address,
		   otherwise the SIP registration process will be in the "TX_TRANSPORTERR" loop.
		 */
		if (1) {
		    //printf("$@@$ - %s DNS SRV for domain %s index %d %s getaddrinfo IPv6\n",__FUNCTION__,domain,ctr,srvname);
		    hints.ai_family = AF_INET6;
      	            rc = getaddrinfo((char *)srvname, NULL, &hints, &res);
      	            if (rc == 0) {
      	                if (res) {
      	                    void *ptr;
      	                    int res_family = res->ai_family;
      	                    /*if (*family == -1) {
                                *family = res->ai_family;
                            }*/
                            memset(tmp_addr,0,MY_BUFFER_LENGTH);
        	            ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
        	            inet_ntop(res->ai_family, ptr, tmp_addr, MY_BUFFER_LENGTH);
        	            freeaddrinfo(res);
        	            if (tmp_addr[0] != 0 && query_flag&QUERY_FLAG_IPV6) {
		                srvip = tmp_addr;
		                len = sizeof(DnsSrv)+strlen(srvip)+1;
		                //printf("i=%d srvip_len=%d len=%d\n",ctr,strlen(srvip),len);
		                p = (pDnsSrv)malloc(len);
		                //printf("malloc %d bytes p=%lx\n",len,p);
		                if (p == 0) {
			            printf("$@@$ - query_sipsrv malloc failed\n");
			            error=-ENOMEM;
			            break;
		                }
		                if (*family == -1) {
                                    *family = res_family;
                                }
		                memset(p,0,len);
		                p->priority=ns_get16 (srv [ctr]+SRV_COST);
		                p->weight=ns_get16 (srv [ctr]+SRV_WEIGHT);
		                p->port=ns_get16 (srv [ctr]+SRV_PORT);
		                p->ttl=(int)ns_get32(srv [ctr]+SRV_TTL); /* Melinda, 2014/06/26 */
		                //printf("Copy srvname %s %s to target\n",srvname,srvip);
		                strcpy(p->target,srvip);
		                //printf("Set slist %d == %lx\n",n,p);
		                slist[n++]=p;
		                fprintf(sfile_fd, "Set SRV server i=%d srvname=%s, srvip=%s TTL=%lu\n",ctr,srvname,srvip,p->ttl);
#ifdef DEBUG
				printf("$@@$ - Set SRV server slist=%p, slist[%d]=%p prio=%d w=%d TTL=%lu %s\n",slist,n-1,p,
				        p->priority,
				        p->weight,
				        p->ttl,
				        &p->target[0]);
#endif
      	                    }
      	                }
      	            }
		}
        }
        for (ctr=0; ctr<num_srv; ctr++) {
		pDnsSrv p;
		int len;
		#if 0 /* IPv4 only */
		struct hostent *host;
		#endif

		if (ns_name_ntop (srv [ctr]+SRV_SERVER, (char*)srvname, MAXDNAME) < 0) {
			continue;  /* ignore this item */
		}
		//get ip from hostname
		memset(&hints, 0x00, sizeof(hints));
        	if (query_ipv4) { /* Try IPv4 */
                    //printf("$@@$ - %s DNS SRV for domain %s index %d %s getaddrinfo IPv4\n",__FUNCTION__,domain,ctr,srvname);		    
         	    hints.ai_family = AF_INET;
        	    rc = getaddrinfo((char*)srvname, NULL, &hints, &res);
        	    if (rc == 0) {
      	                if (res) {
      	                    void *ptr;
      	                    int res_family = res->ai_family;
      	                    /*if (*family == -1) {
                                *family = res->ai_family;
                            }*/
                            memset(tmp_addr,0,MY_BUFFER_LENGTH);
        	            ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
        	            inet_ntop(res->ai_family, ptr, tmp_addr, MY_BUFFER_LENGTH);
        	            freeaddrinfo(res);
        	            if (tmp_addr[0] != 0 && query_flag&QUERY_FLAG_IPV4) {
		                srvip = tmp_addr;
		                len = sizeof(DnsSrv)+strlen(srvip)+1;
		                //printf("i=%d srvip_len=%d len=%d\n",ctr,strlen(srvip),len);
		                p = (pDnsSrv)malloc(len);
		                //printf("malloc %d bytes p=%lx\n",len,p);
		                if (p == 0) {
			            printf("$@@$ - query_sipsrv malloc failed\n");
			            error=-ENOMEM;
			            break;
		                }
		                if (*family == -1) {
                                    *family = res_family;
                                }
		                memset(p,0,len);
		                p->priority=ns_get16 (srv [ctr]+SRV_COST);
		                p->weight=ns_get16 (srv [ctr]+SRV_WEIGHT);
		                p->port=ns_get16 (srv [ctr]+SRV_PORT);
		                p->ttl=(int)ns_get32(srv [ctr]+SRV_TTL); /* Melinda, 2014/06/26 */
		                //printf("Copy srvname %s %s to target\n",srvname,srvip);
		                strcpy(p->target,srvip);
		                //printf("Set slist %d == %lx\n",n,p);
		                slist[n++]=p;
		                fprintf(sfile_fd, "Set SRV server i=%d srvname=%s, srvip=%s TTL=%lu\n",ctr,srvname,srvip,p->ttl);
#ifdef DEBUG
				printf("$@@$ - Set SRV server slist=%p, slist[%d]=%p prio=%d w=%d TTL=%lu %s\n",slist,n-1,p,
				        p->priority,
				        p->weight,
				        p->ttl,
				        &p->target[0]);
#endif
      	                    }
      	                }//res
      	            }//rc==0
        	}//query_ipv4
        }

	if(error)	{
		for(i=0;i<n;i++){
		   if(slist[i])
		   	free(slist[i]);
		}
	}
	*no=n;
    fclose(sfile_fd);
    sfile_fd = NULL;
    /* Shannon 2013/06/05, we must return error when *no is 0,
	   otherwise it may causes vgw crash
	 */
    if (*no == 0)
        error = -2;

	return error;

}

int add_default_srv(char *domain, pDnsSrv *slist, int *no,int *normal_dns,int port) /* Melinda, 2015/12/04, add parameter port */
{
    pDnsSrv p;
	int len;

    /* Shannon 2013/06/09 */
    if (*no > 0) {
        //printf("$@@$ - %s %s %d - free slist no=%d\n",__FILE__,__FUNCTION__,__LINE__,*no);
        free_sipsrv(slist,*no);
    }

    len=sizeof(DnsSrv)+strlen(domain)+1;
	//printf("i=%d srvip_len=%d len=%d\n",ctr,strlen(srvip),len);
	p=(pDnsSrv)malloc(len);
	//printf("malloc %d bytes p=%lx\n",len,p);
	if(p==0){
			printf("$@@$ - add_default_srv malloc failed\n");
			*no=0;
			return -1;
	}
	memset(p,0,len);
	p->priority=0;
	p->weight=0;
	p->port=port; /* Melinda, 2015/12/04, add parameter port */
	//printf("$@@$ - add_default_srv domain=%s to slist=%p slist[0]=%p\n",domain,slist,p);
	strcpy(p->target,domain);	
	//printf("Set slist %d == %lx, %s:%d\n",n,p,p->target,p->port);	
	slist[0]=p;
	*no=1;
	*normal_dns=1;
	return 0;
}
#ifdef TEST	
#define TotalSrvNo  2
int add_test_srv(char *domain, pDnsSrv *slist, int *no,int *normal_dns)
{
    pDnsSrv p;
	int len;
    char ip[3][80]={"192.168.1.222","192.168.1.222","192.168.1.101"};
    int i;	
	
	
    for(i=0;i<TotalSrvNo;i++){
        len=sizeof(DnsSrv)+strlen(ip[i])+1;
	//printf("i=%d srvip_len=%d len=%d\n",ctr,strlen(srvip),len);
	p=(pDnsSrv)malloc(len);
	//printf("malloc %d bytes p=%lx\n",len,p);
	if(p==0){
			printf("$@@$ - add_test_srv malloc failed\n");
			*no=0;
			return -1;
	}
	memset(p,0,len);
	p->priority=0;
	p->weight=0;
	p->port=5060;
	p->ttl=120;
	printf("$@@$ - add_test_srv domain=%s ip[%d]=%s:5060 to slist=%p slist[%d]=%p\n",domain,i,ip[i],slist,i,p);
	strcpy(p->target,ip[i]);	
	//printf("Set slist %d == %lx\n",n,p);	
	slist[i]=p;
    }
    *no=TotalSrvNo;
	*normal_dns=0;
	return 0;
}
#endif
int is_a_domain_name(char *domain,int *family,char *ret_ip,int ret_ip_size)
{
    char   *a,*leftc=0,*rightc=0;
    struct in6_addr serveraddr;
    char   tmp_addr[MY_BUFFER_LENGTH];
    int    rc;

    *family=-1;
    strncpy(tmp_addr,domain,MY_BUFFER_LENGTH);
    tmp_addr[MY_BUFFER_LENGTH-1]=0;
    a=&tmp_addr[0];
    leftc = strchr(a,'[');
	if(leftc)
		rightc= strchr(a,']');
	if(leftc && rightc){
		*rightc=0;
		leftc++;
		a=leftc;
		
	}
	rc = inet_pton(AF_INET, a, &serveraddr);
    if (rc == 1)    /* valid IPv4 text address? */
    {        
           *family=AF_INET;
           if(ret_ip)
                snprintf(ret_ip,ret_ip_size,"%s",a);
           //printf("$@@$ - domain=%s is a IPv4 address\n",domain);   
           return 0;
    }
    else
    {
           rc = inet_pton(AF_INET6, a, &serveraddr);
           if (rc == 1) /* valid IPv6 text address? */
           {
            *family=AF_INET6;
            if(ret_ip)
                snprintf(ret_ip,ret_ip_size,"%s",a);
            //printf("$@@$ - domain=%s is a IPv6 address\n",domain); 
            return 0;
           }
     }
     //printf("$@@$ - domain=%s len=%d is a domain name\n",domain,strlen(domain)); 
     return 1;
}
/*************************************************************************
 * Purpose: query sip server by domain
 * Input:
 *		domain  - domain name to query
 *      *normal_dns - if equals to 0xff then will do autodetect dns srv and normal dns
 * Output:
 * 		slist - buffer to save pDnsSrv pointer array (provide by caller)
 *		slist[0]	----> pointer to sip server 1
 *		slist[1]	----> pointer to sip server 2
 *		...
 *		slist[no-1]--> pointer to sip server no
 *
 *		maxno  - slist array detph
 *		no - how many items we get and copy to slist
 *      normal_dns - When dns srv query fail we will put the domain into
 *                   slist[0] and set this flag to 1
 *      family     - Return family of server
 *      port       - default port number of server
 *      Melinda, 2012/12/07 DT request autodetect dns srv and normal dns
 *      Add normal_dns to meet DT's request
 *      query_flag - =bit 0, query ipv6
 *                   =bit 1, query ipv4
 *************************************************************************/
int query_sipsrv(char *domain, pDnsSrv *slist, int maxno, int *no,int *normal_dns,int query_flag,int *family,int port) /* Melinda, 2015/12/04, add parameter port */
{
    
  
	int ret=1,auto_detect=0;
	struct itimerval tout_val;
	static pthread_mutex_t DnsSrvMutex = PTHREAD_MUTEX_INITIALIZER; /* Melinda, 2015/11/18 */


	//printf("$@@$ - Enter %s - domain=%s no=%d query_flag=%d normal_dns=%x\n",__FUNCTION__,domain,*no,query_flag,*normal_dns);
	if(*normal_dns==0xff)
	    auto_detect=1;
	*normal_dns=0;
	
	if(*no>0){ //free previous slist
	    //printf("$@@$ - %s %s %d - free slist no=%d\n",__FILE__,__FUNCTION__,__LINE__,*no);
	    free_sipsrv(slist,*no);
	    
	}
	*no=0;
    if (is_a_domain_name(domain,family,NULL,0)) {/* Melinda, 2012/12/27, if not a domain name then skip dns srv query */
            struct sigaction act, oact;
            sigset_t set, oset;
            
            pthread_mutex_lock(&DnsSrvMutex); /* Melinda, 2015/11/18 */
            strncpy(my_query_data.domain,domain,MY_BUFFER_LENGTH);
            my_query_data.domain[MY_BUFFER_LENGTH-1]=0;
            my_query_data.slist=slist;
            my_query_data.maxno=maxno;
            my_query_data.no=0; /* will set in pthread */
            my_query_data.query_flag=query_flag;
            my_query_data.ret=-1;
            my_query_data.query_done=0;
  
            tout_val.it_interval.tv_sec = 0;
            tout_val.it_interval.tv_usec = 0;
            tout_val.it_value.tv_sec = DNS_SRV_TIMEOUT; 
            tout_val.it_value.tv_usec = 0;
            setitimer(ITIMER_REAL, &tout_val,0);

            
            act.sa_sigaction = alarm_wakeup;
	        sigemptyset(&act.sa_mask);
	        act.sa_flags = SA_SIGINFO;
	        sigaction(SIGALRM, &act, &oact);    /* set the Alarm signal capture */
            
            
            pthread_create(&query_thread_id,NULL,(void *)query_thread,(void *)&my_query_data);
            //printf("$@@$ - After query_thread create\n");
            pthread_join(query_thread_id,NULL);
        if (my_query_data.query_done == 2) {
            int i;
            /* Shannon 2015/09/22, free allocated resource when query timeout */
            if (sfile_fd) {
                ftruncate(fileno(sfile_fd), 0);
                fclose(sfile_fd);
                sfile_fd = NULL;
            }
            for (i=0; i<maxno*2; i++) {
                if (slist[i]) {
                    free(slist[i]);
                    slist[i] = NULL;
                }
            }
        }
            
            tout_val.it_interval.tv_sec = 0;
            tout_val.it_interval.tv_usec = 0;
            tout_val.it_value.tv_sec = 0; 
            tout_val.it_value.tv_usec = 0;
            setitimer(ITIMER_REAL, &tout_val,0);
            
            sigemptyset(&set);
		    sigaddset(&set, SIGALRM);
		    sigprocmask(SIG_UNBLOCK, &set, &oset);
        
            /*act.sa_handler = SIG_IGN;
	        act.sa_flags = 0; */
	        sigaction(SIGALRM, &oact, NULL);
        
            //printf("$@@$ - After query_thread join, query_done=%d ret=%d no=%d\n",my_query_data.query_done,my_query_data.ret,my_query_data.no);	    
            ret=my_query_data.ret;
            *no=my_query_data.no;
            if(my_query_data.family!=-1)
                *family=my_query_data.family;
            else
                *family=AF_INET; /* use ipv4 as default */
            pthread_mutex_unlock(&DnsSrvMutex); /* Melinda, 2015/11/18 */
	    
        
	}
	else {
	    /*auto_detect=1; */ /* Melinda, 2013/01/14, Input is not domain name set it to first slist */
	    /* Shannon 2015/02/26 */
	    ret=add_default_srv(domain, slist, no,normal_dns,port); /* Melinda, 2015/12/04, add parameter port */
	}
#if 0 /* Melinda, 2015/02/25, DT always use dns srv */	    
	if(ret && auto_detect){
	    ret=add_default_srv(domain, slist, no,normal_dns,port); /* Melinda, 2015/12/04, add parameter port */
	}
#endif	
	//printf("$@@$ - Exit %s - domain=%s no=%d normal_dns=%d ret=%d\n",__FUNCTION__,domain,*no,*normal_dns,ret);
	return ret;

}

int free_sipsrv(pDnsSrv *slist,int no)
{
	int i;

	if(slist==0 || no<=0)
		return -1;
	for(i=0;i<no;i++){
		if(slist[i]){
#ifdef DEBUG
			printf("$@@$ - free_sipsrv: slist=%p no=%d free slist[%d]=%p\n",slist,no,i,slist[i]);
#endif
		   	free(slist[i]);
		}
	}

	return 0;

}


/*
 * $Log: libsrv.c,v $
 * Revision 1.4  2002/10/02 13:28:11  vanrein
 * Added include file <sys/time.h> that is needed on Linux.
 *
 * Revision 1.3  2002/09/14 20:29:24  vanrein
 * Adapted libsrv to detect + shoot zombie child processes.  HTTPproxy adapted.
 *
 * Revision 1.2  2002/09/13 11:07:34  vanrein
 * Added more include-files to support portability to other Unices than Linux.
 *
 * Revision 1.1  2002/09/12 05:44:44  vanrein
 * The first checkin of libsrv -- this compiles to a good .so
 * The hello demo works properly.
 * Due to resolver differences, this only compiles on Linux for now.
 *
 */
void melinda_test_fun(void)
{
	printf("just for testing\n");
}



#ifdef TCP_DNS_SUPPORT

int __encode_header(struct resolv_header *h, unsigned char *dest, int maxlen)
{
    if (maxlen < HFIXEDSZ)
        return -1;

    dest[0] = (h->id & 0xff00) >> 8;
    dest[1] = (h->id & 0x00ff) >> 0;
    dest[2] = (h->qr ? 0x80 : 0) |
            ((h->opcode & 0x0f) << 3) |
            (h->aa ? 0x04 : 0) |
            (h->tc ? 0x02 : 0) |
            (h->rd ? 0x01 : 0);
    dest[3] = (h->ra ? 0x80 : 0) | (h->rcode & 0x0f);
    dest[4] = (h->qdcount & 0xff00) >> 8;
    dest[5] = (h->qdcount & 0x00ff) >> 0;
    dest[6] = (h->ancount & 0xff00) >> 8;
    dest[7] = (h->ancount & 0x00ff) >> 0;
    dest[8] = (h->nscount & 0xff00) >> 8;
    dest[9] = (h->nscount & 0x00ff) >> 0;
    dest[10] = (h->arcount & 0xff00) >> 8;
    dest[11] = (h->arcount & 0x00ff) >> 0;

    return HFIXEDSZ;
}
/* On entry:
 *  a.buf(len) = auxiliary buffer for IP addresses after first one
 *  a.add_count = how many additional addresses are there already
 *  outpacket = where to save ptr to raw packet? can be NULL
 * On exit:
 *  ret < 0: error, all other data is not valid
 *  ret >= 0: length of reply packet
 *  a.add_count & a.buf: updated
 *  a.rdlength: length of addresses (4 bytes for IPv4)
 *  *outpacket: updated (packet is malloced, you need to free it)
 *  a.rdata: points into *outpacket to 1st IP addr
 *      NB: don't pass outpacket == NULL if you need to use a.rdata!
 *  a.atype: type of query?
 *  a.dotted: which name we _actually_ used. May contain search domains
 *      appended. (why the filed is called "dotted" I have no idea)
 *      This is a malloced string. May be NULL because strdup failed.
 */
int __tcp_dns_lookup(const char *name, int id,
        int type,
        unsigned char **outpacket,
        struct resolv_answer *a)
{
    /* Protected by __resolv_lock: */
    int i, j, fd, rc;
    int packet_len;
    int name_len;
    struct timeval tv;
    fd_set fds;
    struct resolv_header h;
    struct resolv_question q;
    struct resolv_answer ma;
    unsigned char first_answer = 1;
    unsigned char *packet = malloc(TCP_PACKETSZ);
    char *lookup;
    /*unsigned char ends_with_dot;*/
    struct sockaddr_in sa;
    int pos,size,recv_len;
    unsigned char c1,c2;

    fd = -1;
    lookup = NULL;
    name_len = strlen(name);
    if ((unsigned)name_len >= MAXDNAME - MAXLEN_searchdomain - 2)
        goto fail; /* paranoia */
    lookup = malloc(name_len + 1/*for '.'*/ + MAXLEN_searchdomain + 1);
    if (!packet || !lookup || !name[0])
        goto fail;
    /*ends_with_dot = (name[name_len - 1] == '.');*/
    /* no strcpy! paranoia, user might change name[] under us */
    memcpy(lookup, name, name_len);
#ifdef DEBUG

    printf("Looking up type %d answer for '%s'\n", type, name);
#endif



    /* Mess with globals while under lock */
    /* NB: even data *pointed to* by globals may vanish
     * outside the locks. We should assume any and all
     * globals can completely change between locked
     * code regions. OTOH, this is rare, so we don't need
     * to handle it "nicely" (do not skip servers,
     * search domains, etc), we only need to ensure
     * we do not SEGV, use freed+overwritten data
     * or do other Really Bad Things. */
    //__open_nameservers();

    lookup[name_len] = '\0';

    memset(packet, 0, TCP_PACKETSZ);
    memset(&h, 0, sizeof(h));

    /* encode header */
    h.id = id;
    h.qdcount = 1;
    h.rd = 1;
    DPRINTF("encoding header\n");
    i = __encode_header(&h, packet, TCP_PACKETSZ);
    if (i < 0)
        goto fail;

    /* encode question */
    q.dotted = lookup;
    q.qtype = type;
    q.qclass = C_IN; /* CLASS_IN */
    j = __encode_question(&q, packet+i, TCP_PACKETSZ-i);
    if (j < 0)
        goto fail;
    packet_len = i + j;
    c1 = (packet_len & 0xFF00)>>8;
    c2 = (packet_len & 0x00FF);
    /* send packet */
#ifdef DEBUG

    printf("\ntcp request send %d bytes,h.id=%d\n ",packet_len,h.id);
    for (i=0;i<packet_len;i++)
    {
        printf("%02x ",*(packet+i));
        if (i!=0&&i%16 == 0)
            printf("\n");
    }
#endif
    sa.sin_family = AF_INET;
    sa.sin_port = htons(53);
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (fd < 0) /* paranoia */
        goto fail1;
    rc = connect(fd, (struct sockaddr *)&sa, sizeof(sa));
    if (rc < 0)
    {
        /*if (errno == ENETUNREACH) { */
        /* routing error, presume not transient */
        printf("%d:routing error\n",__LINE__);
        /*} */
        /*For example, what transient error this can be? Can't think of any */
        /* retry */
        /*continue; */
    }
    printf("Xmit tcp packet len:%d id:%d qr:%d\n", packet_len, h.id, h.qr);
    /* no error check - if it fails, we time out on recv */
    rc = send(fd, &c1, 1, 0);
    rc |= send(fd, &c2, 1, 0);
    rc |= send(fd, packet, packet_len, 0);
    if (rc < 0)
        printf("send error =%d\n",errno);

wait_again:
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    if (select(fd + 1, &fds, NULL, NULL, &tv) <= 0)
    {
        DPRINTF("Timeout\n");
        /* timed out, so retry send and receive
         * to next nameserver */
        goto fail1;
    }
    /* the reply from dns proxy contain 3 part, c1 , c2 and packet,
       so we need call recv 3 times to collect all the data.
    */
    memset(packet,0x00,packet_len+2);
    c1 = c2 = rc = 0;
    recv_len = packet_len = 0;
    rc = recv(fd, &c1, 1, MSG_DONTWAIT);
    if (rc < 0)
        printf("%d:recv error =%d\n",__LINE__,errno);
    
    FD_SET(fd, &fds);
    tv.tv_sec = 0;
    tv.tv_usec = 500;
    if (select(fd + 1, &fds, NULL, NULL, &tv) <= 0)
    {
        DPRINTF("Timeout\n");
        /* timed out, so retry send and receive
         * to next nameserver */
        goto fail1;
    }
    rc = recv(fd, &c2, 1, MSG_DONTWAIT);
    if (rc < 0)
        printf("%d:recv error =%d\n",__LINE__,errno);
    size = c1 <<8 | c2;
#ifdef DEBUG
        printf("Recv tcp c1=%d c2=%d,size=%d \n ",c1,c2,size);
#endif 
    while (size > 0) {
        FD_SET(fd, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 500;
        if (select(fd + 1, &fds, NULL, NULL, &tv) <= 0)
        {
            DPRINTF("Timeout\n");
            /* timed out, so retry send and receive
            * to next nameserver */
            goto fail1;
        }
        recv_len = recv(fd, packet+packet_len, TCP_PACKETSZ-packet_len, MSG_DONTWAIT);
      
        if (recv_len < 0) {
            printf("%d:recv error =%d\n",__LINE__,errno);
            break;
        }
        packet_len +=recv_len;
        size -=recv_len;
#ifdef DEBUG
        printf("Recv tcp packet len=%d,recv_len=%d\n ",packet_len,recv_len);
#endif  
    }
#ifdef DEBUG
    printf("packet recv: %02x %02x %02x %02x\n",*packet,*(packet+1),*(packet+2),*(packet+3));
#endif  
    if (packet_len < HFIXEDSZ)
    {
        /* too short!
         * If the peer did shutdown then retry later,
         * try next peer on error.
         * it's just a bogus packet from somewhere */
bogus_packet:
        if (packet_len >= 0 )
            goto wait_again;
        goto fail1;
    }
    __decode_header(packet, &h);

    if (h.id != id || !h.qr)
    {
        /* unsolicited */
        printf("Error: id is not the same, response id=%x ,request  id=%x\n",h.id,id);
        goto bogus_packet;
    }

    /* Insert other non-fatal errors here, which do not warrant
     * switching to next nameserver */

    /* Strange error, assuming this nameserver is feeling bad */
    if (h.rcode != 0)
        goto fail1;

    /* Code below won't work correctly with h.ancount == 0, so... */
    if (h.ancount <= 0)
    {
        h_errno = NO_DATA; /* [is this correct code to check for?] */
        goto fail1;
    }
    pos = HFIXEDSZ;
    for (j = 0; j < h.qdcount; j++)
    {
        DPRINTF("Skipping question %d at %d\n", j, pos);
        i = __length_question(packet + pos, packet_len - pos);
        if (i < 0)
        {
            DPRINTF("Packet'question section "
                    "is truncated, trying next server\n");
            goto fail1;
        }
        pos += i;
        DPRINTF("Length of question %d is %d\n", j, i);
    }
    DPRINTF("Decoding answer at pos %d\n", pos);

    first_answer = 1;
    for (j = 0; j < h.ancount; j++)
    {
        i = __decode_answer(packet, pos, packet_len, &ma);
        if (i < 0)
        {
            DPRINTF("failed decode %d\n", i);
            /* If the message was truncated but we have
             * decoded some answers, pretend it's OK */
        }
        pos += i;

        if (first_answer)
        {
            ma.buf = a->buf;
            ma.buflen = a->buflen;
            ma.add_count = a->add_count;
            memcpy(a, &ma, sizeof(ma));
            if (a->atype != T_SIG && (NULL == a->buf || (type != T_A && type != T_AAAA)))
                break;
            if (a->atype != type)
                continue;
            a->add_count = h.ancount - j - 1;
            if ((a->rdlength + sizeof(struct in_addr*)) * a->add_count > a->buflen)
                break;
            a->add_count = 0;
            first_answer = 0;
        }
        else
        {
            free(ma.dotted);
            if (ma.atype != type)
                continue;
            if (a->rdlength != ma.rdlength)
            {
                free(a->dotted);
                DPRINTF("Answer address len(%u) differs from original(%u)\n",
                        ma.rdlength, a->rdlength);
                goto fail1;
            }
            memcpy(a->buf + (a->add_count * ma.rdlength), ma.rdata, ma.rdlength);
            ++a->add_count;
        }
    }

    /* Success! */
    if (fd != -1)
        close(fd);
    if (outpacket)
        *outpacket = packet;
    else
        free(packet);
    free(lookup);
    return packet_len;

fail:
    h_errno = NETDB_INTERNAL;
fail1:
    if (fd != -1)
        close(fd);
    free(lookup);
    free(packet);
    return -1;
}

int tcp_res_query(const char *dname, int id,int class, int type,
        unsigned char *answer, int anslen)
{
    int i;
    unsigned char *packet = NULL;
    struct resolv_answer a;

    if (!dname || class != 1 /* CLASS_IN */)
    {
        h_errno = NO_RECOVERY;
        return -1;
    }

    memset(&a, '\0', sizeof(a));
    i = __tcp_dns_lookup(dname, id,type, &packet, &a);
    if (i < 0)
    {
        if (!h_errno) /* TODO: can this ever happen? */
            h_errno = TRY_AGAIN;
        DPRINTF("%d: ret error TRY_AGAIN\n",__LINE__);    
        return -1;
    }

    free(a.dotted);

    if (a.atype == type)
    { /* CNAME */
        if (i > anslen)
            i = anslen;
        memcpy(answer, packet, i);
    }
    free(packet);
    return i;
}

/* Encode a dotted string into nameserver transport-level encoding.
   This routine is fairly dumb, and doesn't attempt to compress
   the data */
int __encode_dotted(const char *dotted, unsigned char *dest, int maxlen)
{
    unsigned used = 0;

    while (dotted && *dotted)
    {
        char *c = strchr(dotted, '.');
        int l = c ? c - dotted : strlen(dotted);

        /* two consecutive dots are not valid */
        if (l == 0)
            return -1;

        if (l >= (maxlen - used - 1))
            return -1;

        dest[used++] = l;
        memcpy(dest + used, dotted, l);
        used += l;

        if (!c)
            break;
        dotted = c + 1;
    }

    if (maxlen < 1)
        return -1;

    dest[used++] = 0;

    return used;
}

/* Decode a dotted string from nameserver transport-level encoding.
   This routine understands compressed data. */
int __decode_dotted(const unsigned char *packet,
        int offset,
        int packet_len,
        char *dest,
        int dest_len)
{
    unsigned b;
    unsigned char measure = 1;
    unsigned total = 0;
    unsigned used = 0;

    if (!packet)
        return -1;

    while (1)
    {
        if (offset >= packet_len)
            return -1;
        b = packet[offset++];
        if (b == 0)
            break;

        if (measure)
            total++;

        if ((b & 0xc0) == 0xc0)
        {
            if (offset >= packet_len)
                return -1;
            if (measure)
                total++;
            /* compressed item, redirect */
            offset = ((b & 0x3f) << 8) | packet[offset];
            measure = 0;
            continue;
        }

        if (used + b + 1 >= dest_len)
            return -1;
        if (offset + b >= packet_len)
            return -1;
        memcpy(dest + used, packet + offset, b);
        offset += b;
        used += b;

        if (measure)
            total += b;

        if (packet[offset] != 0)
            dest[used++] = '.';
        else
            dest[used++] = '\0';
    }

    /* The null byte must be counted too */
    if (measure)
        total++;

    DPRINTF("Total decode len = %d\n", total);

    return total;
}

int __encode_question(const struct resolv_question *q,
        unsigned char *dest,
        int maxlen)
{
    int i;

    i = __encode_dotted(q->dotted, dest, maxlen);
    if (i < 0)
        return i;

    dest += i;
    maxlen -= i;

    if (maxlen < 4)
        return -1;

    dest[0] = (q->qtype & 0xff00) >> 8;
    dest[1] = (q->qtype & 0x00ff) >> 0;
    dest[2] = (q->qclass & 0xff00) >> 8;
    dest[3] = (q->qclass & 0x00ff) >> 0;

    return i + 4;
}

void __decode_header(unsigned char *data,
        struct resolv_header *h)
{
    h->id = (data[0] << 8) | data[1];
    h->qr = (data[2] & 0x80) ? 1 : 0;
    h->opcode = (data[2] >> 3) & 0x0f;
    h->aa = (data[2] & 0x04) ? 1 : 0;
    h->tc = (data[2] & 0x02) ? 1 : 0;
    h->rd = (data[2] & 0x01) ? 1 : 0;
    h->ra = (data[3] & 0x80) ? 1 : 0;
    h->rcode = data[3] & 0x0f;
    h->qdcount = (data[4] << 8) | data[5];
    h->ancount = (data[6] << 8) | data[7];
    h->nscount = (data[8] << 8) | data[9];
    h->arcount = (data[10] << 8) | data[11];
}

static int __length_question(const unsigned char *data, int maxlen)
{
    const unsigned char *start;
    unsigned b;

    if (!data)
        return -1;

    start = data;
    while (1)
    {
        if (maxlen <= 0)
            return -1;
        b = *data++;
        if (b == 0)
            break;
        if ((b & 0xc0) == 0xc0)
        {
            /* It's a "compressed" name. */
            data++; /* skip lsb of redirected offset */
            maxlen -= 2;
            break;
        }
        data += b;
        maxlen -= (b + 1); /* account for data++ above */
    }
    /* Up to here we were skipping encoded name */

    /* Account for QTYPE and QCLASS fields */
    if (maxlen < 4)
        return -1;
    return data - start + 2 + 2;
}

static int __decode_answer(const unsigned char *message, /* packet */
        int offset,
        int len, /* total packet len */
        struct resolv_answer *a)
{
    char temp[256];
    int i;

    DPRINTF("decode_answer(start): off %d, len %d\n", offset, len);
    i = __decode_dotted(message, offset, len, temp, sizeof(temp));
    if (i < 0)
        return i;

    message += offset + i;
    len -= i + RRFIXEDSZ + offset;
    if (len < 0)
    {
        DPRINTF("decode_answer: off %d, len %d, i %d\n", offset, len, i);
        return len;
    }

    /* TODO: what if strdup fails? */
    a->dotted = strdup(temp);
    a->atype = (message[0] << 8) | message[1];
    message += 2;
    a->aclass = (message[0] << 8) | message[1];
    message += 2;
    a->ttl = (message[0] << 24) |
            (message[1] << 16) | (message[2] << 8) | (message[3] << 0);
    message += 4;
    a->rdlength = (message[0] << 8) | message[1];
    message += 2;
    a->rdata = message;
    a->rdoffset = offset + i + RRFIXEDSZ;

    DPRINTF("i=%d,rdlength=%d\n", i, a->rdlength);

    if (len < a->rdlength)
        return -1;
    return i + RRFIXEDSZ + a->rdlength;
}

#endif

#ifdef TEST
#define TotalSrvNo  2
int add_test_srv(char *domain, pDnsSrv *slist, int *no,int *normal_dns)
{
    pDnsSrv p;
    int len;
    char ip[3][80]={"192.168.1.222","192.168.1.222","192.168.1.101"};
    int i;


    for(i=0;i<TotalSrvNo;i++)
    {
        len=sizeof(DnsSrv)+strlen(ip[i])+1;
        //printf("i=%d srvip_len=%d len=%d\n",ctr,strlen(srvip),len);
        p=(pDnsSrv)malloc(len);
        //printf("malloc %d bytes p=%lx\n",len,p);
        if(p==0)
        {
            printf("$@@$ - add_test_srv malloc failed\n");
            *no=0;
            return -1;
        }
        memset(p,0,len);
        p->priority=0;
        p->weight=0;
        p->port=5060;
        p->ttl=120;
        printf("$@@$ - add_default_srv domain=%s ip[%d]=%s to slist=%p slist[%d]=%p\n",domain,i,ip[i],slist,i,p);
        strcpy(p->target,ip[i]);
        //printf("Set slist %d == %lx\n",n,p);
        slist[i]=p;
    }
    *no=TotalSrvNo;
    *normal_dns=0;
    return 0;
}
#endif

static char *skip_nospace(char *p)
{
	while (*p != '\0' && !isspace(*p)) {
		if (*p == '\n') {
			*p = '\0';
			break;
		}
		p++;
	}
	return p;
}

static char *skip_and_NUL_space(char *p)
{
	/* NB: '\n' is not isspace! */
	while (1) {
		char c = *p;
		if (c == '\0' || !isspace(c))
			break;
		*p = '\0';
		if (c == '\n' || c == '#')
			break;
		p++;
	}
	return p;
}

int sc_dns_lookup(const char *name,
		int type,
		unsigned char **outpacket,
		struct resolv_answer *a)
{
	/* Protected by __resolv_lock: */
	static int last_ns_num = 0;
	static uint16_t last_id = 1;

	int i, j, fd, rc;
	int packet_len;
	int name_len;
#ifdef USE_SELECT
	struct timeval tv;
	fd_set fds;
#else
	struct pollfd fds;
#endif
	struct resolv_header h;
	struct resolv_question q;
	struct resolv_answer ma;
	bool first_answer = 1;
	int retries_left;
	unsigned char *packet = malloc(PACKETSZ);
	char *lookup;
	int variant = -1;  /* search domain to append, -1: none */
	int local_ns_num = -1; /* Nth server to use */
	int local_id = local_id; /* for compiler */
	int sdomains;
	bool ends_with_dot;
	sockaddr46_t sa;

	fd = -1;
	lookup = NULL;
	name_len = strlen(name);
	if ((unsigned)name_len >= MAXDNAME - MAXLEN_searchdomain - 2)
		goto fail; /* paranoia */
	lookup = malloc(name_len + 1/*for '.'*/ + MAXLEN_searchdomain + 1);
	if (!packet || !lookup || !name[0])
		goto fail;
	ends_with_dot = (name[name_len - 1] == '.');
	/* no strcpy! paranoia, user might change name[] under us */
	memcpy(lookup, name, name_len);

	DPRINTF("Looking up type %d answer for '%s'\n", type, name);
	retries_left = 0; /* for compiler */
	do {
		int pos;
		unsigned reply_timeout;

		if (fd != -1) {
			close(fd);
			fd = -1;
		}

		/* Mess with globals while under lock */
		/* NB: even data *pointed to* by globals may vanish
		 * outside the locks. We should assume any and all
		 * globals can completely change between locked
		 * code regions. OTOH, this is rare, so we don't need
		 * to handle it "nicely" (do not skip servers,
		 * search domains, etc), we only need to ensure
		 * we do not SEGV, use freed+overwritten data
		 * or do other Really Bad Things. */
		BIGLOCK;
		__open_nameservers();
		sdomains = __searchdomains;
		lookup[name_len] = '\0';
		if ((unsigned)variant < sdomains) {
			/* lookup is name_len + 1 + MAXLEN_searchdomain + 1 long */
			/* __searchdomain[] is not bigger than MAXLEN_searchdomain */
			lookup[name_len] = '.';
			strcpy(&lookup[name_len + 1], __searchdomain[variant]);
		}
		/* first time? pick starting server etc */
		if (local_ns_num < 0) {
			local_id = last_id;
/*TODO: implement /etc/resolv.conf's "options rotate"
 (a.k.a. RES_ROTATE bit in _res.options)
			local_ns_num = 0;
			if (_res.options & RES_ROTATE) */
				local_ns_num = last_ns_num;
			retries_left = __nameservers * __resolv_attempts;
		}
		retries_left--;
		if (local_ns_num >= __nameservers)
			local_ns_num = 0;
		local_id++;
		local_id &= 0xffff;
		/* write new values back while still under lock */
		last_id = local_id;
		last_ns_num = local_ns_num;
		/* struct copy */
		/* can't just take a pointer, __nameserver[x]
		 * is not safe to use outside of locks */
		sa = __nameserver[local_ns_num];

		BIGUNLOCK;

		memset(packet, 0, PACKETSZ);
		memset(&h, 0, sizeof(h));

		/* encode header */
		h.id = local_id;
		h.qdcount = 1;
		h.rd = 1;
		DPRINTF("encoding header\n");
		i = __encode_header(&h, packet, PACKETSZ);
		if (i < 0)
			goto fail;

		/* encode question */
		DPRINTF("lookup name: %s\n", lookup);
		q.dotted = lookup;
		q.qtype = type;
		q.qclass = C_IN; /* CLASS_IN */
		j = __encode_question(&q, packet+i, PACKETSZ-i);
		if (j < 0)
			goto fail;
		packet_len = i + j;

		/* send packet */
#ifdef DEBUG
		{
			const socklen_t plen = sa.sa.sa_family == AF_INET ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN;
			char *pbuf = malloc(plen);
			if (pbuf == NULL) ;/* nothing */

			else if (sa.sa.sa_family == AF_INET6)
				pbuf = (char*)inet_ntop(AF_INET6, &sa.sa6.sin6_addr, pbuf, plen);


			else if (sa.sa.sa_family == AF_INET)
				pbuf = (char*)inet_ntop(AF_INET, &sa.sa4.sin_addr, pbuf, plen);

			DPRINTF("On try %d, sending query to %s, port %d\n",
				retries_left, pbuf, NAMESERVER_PORT);
			free(pbuf);
		}
#endif
		fd = socket(sa.sa.sa_family, SOCK_DGRAM, IPPROTO_UDP);
		if (fd < 0) /* paranoia */
			goto try_next_server;
		rc = connect(fd, &sa.sa, sizeof(sa));
		if (rc < 0) {
			/*if (errno == ENETUNREACH) { */
				/* routing error, presume not transient */
				goto try_next_server;
			/*} */
/*For example, what transient error this can be? Can't think of any */
			/* retry */
			/*continue; */
		}
		DPRINTF("Xmit packet len:%d id:%d qr:%d\n", packet_len, h.id, h.qr);
		/* no error check - if it fails, we time out on recv */
		send(fd, packet, packet_len, 0);

#ifdef USE_SELECT
		reply_timeout = __resolv_timeout;
 wait_again:
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		tv.tv_sec = reply_timeout;
		tv.tv_usec = 0;
		if (select(fd + 1, &fds, NULL, NULL, &tv) <= 0) {
			DPRINTF("Timeout\n");
			/* timed out, so retry send and receive
			 * to next nameserver */
			goto try_next_server;
		}
		reply_timeout--;
#else /* !USE_SELECT */
		reply_timeout = __resolv_timeout * 1000;
 wait_again:
		fds.fd = fd;
		fds.events = POLLIN;
		if (poll(&fds, 1, reply_timeout) <= 0) {
			DPRINTF("Timeout\n");
			/* timed out, so retry send and receive
			 * to next nameserver */
			goto try_next_server;
		}
/*TODO: better timeout accounting?*/
		reply_timeout -= 1000;
#endif /* USE_SELECT */

/* vda: a bogus response seen in real world (caused SEGV in uclibc):
 * "ping www.google.com" sending AAAA query and getting
 * response with one answer... with answer part missing!
 * Fixed by thorough checks for not going past the packet's end.
 */
#ifdef DEBUG
		{
			static const char test_query[32] = "\0\2\1\0\0\1\0\0\0\0\0\0\3www\6google\3com\0\0\34\0\1";
			static const char test_respn[32] = "\0\2\201\200\0\1\0\1\0\0\0\0\3www\6google\3com\0\0\34\0\1";
			pos = memcmp(packet + 2, test_query + 2, 30);
		packet_len = recv(fd, packet, PACKETSZ, MSG_DONTWAIT);
			if (pos == 0) {
				packet_len = 32;
				memcpy(packet + 2, test_respn + 2, 30);
			}
		}
#else
		packet_len = recv(fd, packet, PACKETSZ, MSG_DONTWAIT);
#endif

		if (packet_len < HFIXEDSZ) {
			/* too short!
			 * If the peer did shutdown then retry later,
			 * try next peer on error.
			 * it's just a bogus packet from somewhere */
 bogus_packet:
			if (packet_len >= 0 && reply_timeout)
				goto wait_again;
			goto try_next_server;
		}
		__decode_header(packet, &h);
		DPRINTF("len:%d id:%d qr:%d\n", packet_len, h.id, h.qr);
		if (h.id != local_id || !h.qr) {
			/* unsolicited */
			goto bogus_packet;
		}

		DPRINTF("Got response (i think)!\n");
		DPRINTF("qrcount=%d,ancount=%d,nscount=%d,arcount=%d\n",
				h.qdcount, h.ancount, h.nscount, h.arcount);
		DPRINTF("opcode=%d,aa=%d,tc=%d,rd=%d,ra=%d,rcode=%d\n",
				h.opcode, h.aa, h.tc, h.rd, h.ra, h.rcode);

		/* bug 660 says we treat negative response as an error
		 * and retry, which is, eh, an error. :)
		 * We were incurring long delays because of this. */
		if (h.rcode == NXDOMAIN || h.rcode == SERVFAIL) {
			/* if possible, try next search domain */
			if (!ends_with_dot) {
				DPRINTF("variant:%d sdomains:%d\n", variant, sdomains);
				if (variant < sdomains - 1) {
					/* next search domain */
					variant++;
					continue;
				}
				/* no more search domains to try */
			}
			/* dont loop, this is "no such host" situation */
			h_errno = HOST_NOT_FOUND;
			goto fail1;
		}
		/* Insert other non-fatal errors here, which do not warrant
		 * switching to next nameserver */

		/* Strange error, assuming this nameserver is feeling bad */
		if (h.rcode != 0)
			goto try_next_server;

		/* Code below won't work correctly with h.ancount == 0, so... */
		if (h.ancount <= 0) {
			h_errno = NO_DATA; /* [is this correct code to check for?] */
			goto fail1;
		}
		pos = HFIXEDSZ;
		for (j = 0; j < h.qdcount; j++) {
			DPRINTF("Skipping question %d at %d\n", j, pos);
			i = __length_question(packet + pos, packet_len - pos);
			if (i < 0) {
				DPRINTF("Packet'question section "
					"is truncated, trying next server\n");
				goto try_next_server;
			}
			pos += i;
			DPRINTF("Length of question %d is %d\n", j, i);
		}
		DPRINTF("Decoding answer at pos %d\n", pos);

		first_answer = 1;
		a->dotted = NULL;
		for (j = 0; j < h.ancount; j++) {
			i = __decode_answer(packet, pos, packet_len, &ma);
			if (i < 0) {
				DPRINTF("failed decode %d\n", i);
				/* If the message was truncated but we have
				 * decoded some answers, pretend it's OK */
				if (j && h.tc)
					break;
				goto try_next_server;
			}
			pos += i;

			if (first_answer) {
				ma.buf = a->buf;
				ma.buflen = a->buflen;
				ma.add_count = a->add_count;
				free(a->dotted);
				memcpy(a, &ma, sizeof(ma));
				if (a->atype != T_SIG && (NULL == a->buf || (type != T_A && type != T_AAAA)))
					break;
				if (a->atype != type)
					continue;
				a->add_count = h.ancount - j - 1;
				if ((a->rdlength + sizeof(struct in_addr*)) * a->add_count > a->buflen)
					break;
				a->add_count = 0;
				first_answer = 0;
			} else {
				free(ma.dotted);
				if (ma.atype != type)
					continue;
				if (a->rdlength != ma.rdlength) {
					free(a->dotted);
					DPRINTF("Answer address len(%u) differs from original(%u)\n",
							ma.rdlength, a->rdlength);
					goto try_next_server;
				}
				memcpy(a->buf + (a->add_count * ma.rdlength), ma.rdata, ma.rdlength);
				++a->add_count;
			}
		}

		/* Success! */
		DPRINTF("Answer name = |%s|\n", a->dotted);
		DPRINTF("Answer type = |%d|\n", a->atype);
		if (fd != -1)
			close(fd);
		if (outpacket)
			*outpacket = packet;
		else
			free(packet);
		free(lookup);
		return packet_len;

 try_next_server:
		/* Try next nameserver */
		local_ns_num++;
		variant = -1;
	} while (retries_left > 0);

 fail:
	h_errno = NETDB_INTERNAL;
 fail1:
	if (fd != -1)
		close(fd);
	free(lookup);
	free(packet);
	return -1;
}

void __open_nameservers(void)
{
	static uint32_t resolv_conf_mtime;

	char szBuffer[MAXLEN_searchdomain];
	FILE *fp;
	int i;
	sockaddr46_t sa;

	if (!__res_sync) {
		/* Reread /etc/resolv.conf if it was modified.  */
	    struct stat sb;
	    
	    if (stat("/etc/resolv.conf", &sb) != 0)
	        sb.st_mtime = 0;
	    if (resolv_conf_mtime != (uint32_t)sb.st_mtime) {
	        resolv_conf_mtime = sb.st_mtime;
		__close_nameservers(); /* force config reread */
	    }
	}

	if (__nameservers)
		goto sync;

	__resolv_timeout = RES_TIMEOUT;
	__resolv_attempts = RES_DFLRETRY;

	fp = fopen("/etc/resolv.conf", "r");
#if 0	
#ifdef FALLBACK_TO_CONFIG_RESOLVCONF
	if (!fp) {
		/* If we do not have a pre-populated /etc/resolv.conf then
		   try to use the one from /etc/config which exists on numerous
		   systems ranging from some uClinux to IRIX installations and
		   may be the only /etc dir that was mounted rw.  */
		fp = fopen("/etc/config/resolv.conf", "r");
	}
#endif
#endif
	if (fp) {
		while (fgets(szBuffer, sizeof(szBuffer), fp) != NULL) {
			void *ptr;
			char *keyword, *p;

			keyword = p = skip_and_NUL_space(szBuffer);
			/* skip keyword */
			p = skip_nospace(p);
			/* find next word */
			p = skip_and_NUL_space(p);

			if (strcmp(keyword, "nameserver") == 0) {
				/* terminate IP addr */
				*skip_nospace(p) = '\0';
				memset(&sa, 0, sizeof(sa));
				if (0) /* nothing */;

				else if (inet_pton(AF_INET6, p, &sa.sa6.sin6_addr) > 0) {
					sa.sa6.sin6_family = AF_INET6;
					sa.sa6.sin6_port = htons(53);
				}


				else if (inet_pton(AF_INET, p, &sa.sa4.sin_addr) > 0) {
					sa.sa4.sin_family = AF_INET;
					sa.sa4.sin_port = htons(53);
				}

				else
					continue; /* garbage on this line */
				ptr = realloc(__nameserver, (__nameservers + 1) * sizeof(__nameserver[0]));
				if (!ptr)
					continue;
				__nameserver = ptr;
				__nameserver[__nameservers++] = sa; /* struct copy */
				continue;
			}
			if (strcmp(keyword, "domain") == 0 || strcmp(keyword, "search") == 0) {
				char *p1;

				/* free old domains ("last 'domain' or 'search' wins" rule) */
				while (__searchdomains)
					free(__searchdomain[--__searchdomains]);
				/*free(__searchdomain);*/
				/*__searchdomain = NULL; - not necessary */
 next_word:
				/* terminate current word */
				p1 = skip_nospace(p);
				/* find next word (maybe) */
				p1 = skip_and_NUL_space(p1);
				/* add it */
				ptr = realloc(__searchdomain, (__searchdomains + 1) * sizeof(__searchdomain[0]));
				if (!ptr)
					continue;
				__searchdomain = ptr;
				/* NB: strlen(p) <= MAXLEN_searchdomain) because szBuffer[] is smaller */
				ptr = strdup(p);
				if (!ptr)
					continue;
				DPRINTF("adding search %s\n", (char*)ptr);
				__searchdomain[__searchdomains++] = (char*)ptr;
				p = p1;
				if (*p)
					goto next_word;
				continue;
			}
			/* if (strcmp(keyword, "sortlist") == 0)... */
			if (strcmp(keyword, "options") == 0) {
				char *p1;
				uint8_t *what;

				if (p == NULL || (p1 = strchr(p, ':')) == NULL)
					continue;
				*p1++ = '\0';
				if (strcmp(p, "timeout") == 0)
					what = &__resolv_timeout;
				else if (strcmp(p, "attempts") == 0)
					what = &__resolv_attempts;
				else
					continue;
				*what = atoi(p1);
				DPRINTF("option %s:%d\n", p, *what);
			}
		}
		fclose(fp);
	}
	if (__nameservers == 0) {
		/* Have to handle malloc failure! What a mess...
		 * And it's not only here, we need to be careful
		 * to never write into __nameserver[0] if it points
		 * to constant __local_nameserver, or free it. */
		__nameserver = malloc(sizeof(__nameserver[0]));
		if (__nameserver)
			memcpy(__nameserver, &__local_nameserver, sizeof(__local_nameserver));
		else
			__nameserver = (void*) &__local_nameserver;
		__nameservers++;
	}
	if (__searchdomains == 0) {
		char buf[256];
		char *p;
		i = gethostname(buf, sizeof(buf) - 1);
		buf[sizeof(buf) - 1] = '\0';
		if (i == 0 && (p = strchr(buf, '.')) != NULL && p[1]) {
			p = strdup(p + 1);
			if (!p)
				goto err;
			__searchdomain = malloc(sizeof(__searchdomain[0]));
			if (!__searchdomain) {
				free(p);
				goto err;
			}
			__searchdomain[0] = p;
			__searchdomains++;
 err: ;
		}
	}
	DPRINTF("nameservers = %d\n", __nameservers);

 sync:
	if (__res_sync)
		__res_sync();
}

void __close_nameservers(void)
{
	if (__nameserver != (void*) &__local_nameserver)
		free(__nameserver);
	__nameserver = NULL;
	__nameservers = 0;
	while (__searchdomains)
		free(__searchdomain[--__searchdomains]);
	free(__searchdomain);
	__searchdomain = NULL;
	/*__searchdomains = 0; - already is */
}

int sc_res_query(const char *dname, int class, int type,
              unsigned char *answer, int anslen)
{
	int i;
	unsigned char *packet = NULL;
	struct resolv_answer a;

	if (!dname || class != 1 /* CLASS_IN */) {
		h_errno = NO_RECOVERY;
		return -1;
	}

	memset(&a, '\0', sizeof(a));
	i = sc_dns_lookup(dname, type, &packet, &a);

	if (i < 0) {
		if (!h_errno) /* TODO: can this ever happen? */
			h_errno = TRY_AGAIN;
		return -1;
	}

	free(a.dotted);
#if 1/*If query type don't match answer's type, also need copy data to user for DT naptr query*/
        if (i > anslen)
	    i = anslen;
	memcpy(answer, packet, i);
#else
	if (a.atype == type) { /* CNAME */
		if (i > anslen)
			i = anslen;
		memcpy(answer, packet, i);
	}
#endif	
	free(packet);
	return i;
	
}
