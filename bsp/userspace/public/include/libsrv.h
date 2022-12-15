#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>

#ifndef _LIBSRV_H_
#define _LIBSRV_H_

#define     DNS_SRV_TIMEOUT     5   /* seconds */
#define MAXLEN_searchdomain 128

typedef struct dns_srv_item{
	unsigned short priority; /* smaller value has the higher priority */
	unsigned short weight;   /* larger value has the higher priority */
	unsigned short port;
	unsigned long ttl;      /* Melinda, 2014/06/26, TTL for this target */
	char target[1];		/* target ip address or host name */ 
}DnsSrv;

typedef DnsSrv *pDnsSrv;

/* Structs */
struct resolv_header {
	int id;
	int qr, opcode, aa, tc, rd, ra, rcode;
	int qdcount;
	int ancount;
	int nscount;
	int arcount;
};

struct resolv_question {
	char *dotted;
	int qtype;
	int qclass;
};

struct resolv_answer {
	char *dotted;
	int atype;
	int aclass;
	int ttl;
	int rdlength;
	const unsigned char *rdata;
	int rdoffset;
	char* buf;
	int buflen;
	int add_count;
};

#define QUERY_FLAG_IPV6    1
#define QUERY_FLAG_IPV4    2

/************************************************************************* 
 * Purpose: query sip server by domain
 * Input: 
 *		domain  - domain name to query
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
int query_sipsrv(char *domain, pDnsSrv *slist, int maxno, int *no,int *normal_dns,int query_flag,int *family,int port); /* Melinda, 2015/12/04, add parameter port */

int sc_res_query(const char *dname, int class, int type,unsigned char *answer, int anslen);

/************************************************************************* 
 * Purpose: free sip server list
 * Input: 
 *		slist  - server list point array, the contains are returned by
 *			    query_sipsrv()
 *		no - the total item number of slist which is return by query_sipsrv
 *************************************************************************/
int free_sipsrv(pDnsSrv *slist,int no);


int add_default_srv(char *domain, pDnsSrv *slist, int *no,int *normal_dns,int port); /* Melinda, 2012/01/07, Mantis 35215 */ /* Melinda, 2015/12/04, add parameter port */

/* Melinda, 2013/02/22 */
int is_a_domain_name(char *domain,int *family,char *ret_ip,int ret_ip_size); 


void melinda_test_fun(void);

/* dn_expand(3) from musl libc */
int musl__dn_expand(const unsigned char *base, const unsigned char *end, const unsigned char *src, char *dest, int space);


#endif
