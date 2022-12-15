#ifndef _SC_DNS_H_
#define _SC_DNS_H_

#include <stdio.h>
#include <stdint.h>

/* Define the domain type */
#define DOMAIN_TYPE_UNKNOWN  (0x0000)
#define DOMAIN_TYPE_DATA     (0x0001)
#define DOMAIN_TYPE_TR069    (0x0002)
#define DOMAIN_TYPE_NTP      (0x0004)
#define DOMAIN_TYPE_VOIP     (0x0008)
#define DOMAIN_TYPE_IPTV     (0x0010)

/*
 * Description:
 *  Add domain to DNRD domain list
 * Parameter:
 *  dytpe    - Domain type
 *  dns_ip   - DNS server IP[Format(192.168.0.1)]
 *  ip_pri   - Priority of DNS server IP[0(highest) ~ 4]
 *  inf_name - WAN interface name
 *  inf_pri  - Priority of WAN infterface[0(highest) ~ 8]
 *  domain   - Domain name (Can be NULL)
 *  time_out - Time out of this DNS server
 * */
int dns_add_domain_by_dnsip(int dtype, char *dns_ip, int ip_priv, 
                            char *inf_name, int inf_pri, char * domain,
                            int time_out);

/*
 * Description:
 *  Add domain to DNRD domain list
 * Parameter:
 *  dytpe    - Domain type
 *  wan_id   - WAN interface ID
 *  inf_pri  - Priority of WAN infterface of this wan ID [0(highest) ~ 8]
 *  domain   - Domain name (Can be NULL)
 *  time_out - Time out of this DNS server
 * */
int dns_add_domain_by_wanid(int dtype, int wan_id, int inf_pri, char * domain,
                            int time_out);


/*
 * Description:
 *  Delete domain from domain list by WAN ID
 * Parameter:
 *  wan_id   - WAN interface ID
 * */
int dns_del_domain_by_wanid(int wan_id);

/*
 * Description:
 *  Delete domain from domain list by doman name
 * Parameter:
 *  dtype    - Domain type
 *  wan_id   - WAN interface ID
 *  domain   - Domain name
 * */
int dns_del_domain_by_domain(int dtype, int wan_id, char *domain);

/*
 * Description:
 *  Delete domain from domain list by doman type
 * Parameter:
 *  dtype    - Domain type
 * */
int dns_del_domain_by_dtype(int dtype);

/*
 * Description:
 *  Add domain type in the hostname
 * Parameter:
 *  name    - Domain name
 *  dtype   - Domain type
 * */
struct hostent *sc_gethostbyname(const char *name, int dtype);

int sc_gethostbyname_r(const char *name, int dtype, struct hostent *ret, 
                     char *buf, size_t buflen, struct hostent **result, 
                     int h_errnop);

#endif /*End Of _SC_DNS_H_*/
