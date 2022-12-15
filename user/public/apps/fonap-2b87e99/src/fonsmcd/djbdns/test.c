#include "dns.h"

int main () {
	stralloc out ={0};
	stralloc sa ={0};
	char ip[4] ={127,0,0,1};
	char *dn =0;
	char *dn0 =0;
	
	stralloc_copys(&sa, "example.org");

	dns_ip4(&out, &sa);
	dns_ip4_qualify(&out, &sa, &sa);
	dns_name4(&out, ip);
	dns_mx(&out, &sa);
	dns_txt(&out, &sa);

	if (!dns_domain_fromdot(&dn, sa.s, sa.len)) return 1;
	dns_domain_length(dn);
	if (!dns_domain_copy(&dn0, dn)) return 1;
	dns_domain_equal(dn0, dn);
	dns_domain_free(&dn);
	dns_domain_free(&dn0);

	return 0;
}
