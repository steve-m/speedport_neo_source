/* files.h */
#ifndef _FILES_H
#define _FILES_H


#ifdef __SC_BUILD__
#include "packet.h"
#define MAX_INTERFACES	4
//#define MAX_KEYWORDS	(19 + 1 + 1 + 3)//add  static lease + wanid + client option (3)
#ifdef __SC_CONDITIONAL_SERVING_PER_IF__
#define MAX_KEYWORDS    34
#else
#define MAX_KEYWORDS    30
#endif
#else
#define MAX_KEYWORDS	18
#endif

struct config_keyword {
	char keyword[14];
	int (*handler)(char *line, void *var);
	void *var;
	char def[30];
};
#ifdef __SC_BUILD__
struct config_kw_arr {
	struct config_keyword keywords[MAX_KEYWORDS];
};

void reconfig_dhcpd(char *conf_file);
#endif
int read_config(char *file);
#ifdef __SC_BUILD__
void write_leases(int ifid);
void read_leases(char *file, int ifid);
#else
void write_leases(void);
void read_leases(char *file);
#endif
#endif
