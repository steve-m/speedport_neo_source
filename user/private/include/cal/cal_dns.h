#ifndef _CFG_dns_H_
#define _CFG_dns_H_

#define DNS_IPV6_ID     1
#define DNS_IPV4_ID     2
#define DNS_DHCP_ID     3

int cal_dns_set_dns_server_type(int server_id, char *dns_type);
int cal_dns_set_dns_server(int server_id, char *dns_buf);
int cal_dns_set_dns_server_interface(int server_id, char *dns_interface);
/*to add here*/
#endif
