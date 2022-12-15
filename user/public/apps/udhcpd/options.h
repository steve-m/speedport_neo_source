/* options.h */
#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "packet.h"

#define TYPE_MASK	0x0F

enum {
	OPTION_IP=1,
	OPTION_IP_PAIR,
	OPTION_STRING,
#ifdef __SC_BUILD__
	OPTION_HEX,
#endif
	OPTION_BOOLEAN,
	OPTION_U8,
	OPTION_U16,
	OPTION_S16,
	OPTION_U32,
	OPTION_S32,
#ifdef __SC_BUILD__
	OPTION_ROUTE,
    OPTION_CLROUTE
#endif
};

#define OPTION_REQ	0x10 /* have the client request this option */
#define OPTION_LIST	0x20 /* There can be a list of 1 or more of these */

struct dhcp_option {
#ifdef __SC_BUILD__
	char name[20];
#else
	char name[10];
#endif
	char flags;
	unsigned char code;
};

extern struct dhcp_option options[];
extern int option_lengths[];

unsigned char *get_option(struct dhcpMessage *packet, int code);
#ifdef __SC_BUILD__

unsigned char *get_option_x(struct dhcpMessage *packet, int code, int *len);
unsigned int get_vendor_id(struct dhcpMessage *packet, char *vendor_id, unsigned int id_length);
int is_option_required(char code);
#endif
int end_option(unsigned char *optionptr);
int add_option_string(unsigned char *optionptr, unsigned char *string);
int add_simple_option(unsigned char *optionptr, unsigned char code, u_int32_t data);
struct option_set *find_option(struct option_set *opt_list, char code);
void attach_option(struct option_set **opt_list, struct dhcp_option *option, char *buffer, int length);
#ifdef __SC_BUILD__
int add_options_directly(unsigned char *optionptr, unsigned char code, char *data, unsigned int length);
void  sc_send_client_options(struct dhcpMessage *packet);
#endif

#endif
