/**
 * @file   vendor_action.c
 * @author Martin Huang <martin_huang@sdc.sercomm.com>
 * @date   2009-11-24
 * @brief  support multiple actions basing on client vendor ID.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <time.h>
#include <sys/time.h>

#include "debug.h"
#include "dhcpd.h"
#include "socket.h"
#include "options.h"
#include "files.h"
#include "packet.h"
#include "serverpacket.h"

#include "option_action.h"


static int do_vendor_action(
	unsigned char state,
	int vif,
	unsigned char *keyword,
	unsigned char *value,
	unsigned int value_len,
	unsigned char *mac
);
static int do_client_action(
	unsigned char state,
	int vif,
	unsigned char *keyword,
	unsigned char *value,
	unsigned int value_len,
	unsigned char *mac
);
static int do_user_class_action(
	unsigned char state,
	int vif,
	unsigned char *keyword,
	unsigned char *value,
	unsigned int value_len,
	unsigned char *mac
);


typedef struct option_attribute_s{
	unsigned int  id;
	unsigned char *keyword;
	int (*handler)(unsigned char state, int vif, unsigned char *keyword, unsigned char *value, unsigned int value_len, unsigned char *mac);
}option_attribute;

static option_attribute opt_attr_table[] = {
	{DHCP_VENDOR, "vendor_id", do_vendor_action},
	{DHCP_CLIENT_ID,  "client_id", do_client_action},
	{DHCP_USER_CLASS_ID,   "user_class_id", do_user_class_action},
	{-1, NULL, NULL}
};

/* return:
	0  	open file error or there is same one
	1	write into file
*/
static int write_option_file(
	unsigned char 	*file,
	unsigned char 	*mac,
	unsigned char 	*keyword,
	unsigned char 	*value
)
{
	FILE *fp;
	char new_mac[20];
	char buf[200];
	char *p;
	char *q;

	fp = fopen(file, "a+");
	if (!fp)
		return 0;

	sprintf(new_mac, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	fseek(fp, 0, SEEK_SET);
	while (fgets(buf, 200, fp))
	{
		p = strstr(buf, new_mac);
		if (p)
		{
			q = strstr(buf, keyword);
			if (q)
			{
				fclose(fp);
				return 0;
			}
		}
	}

	fseek(fp, 0, SEEK_END);
	sprintf(buf, "%s %s %s", new_mac, keyword, value);
	fprintf(fp, "%s\n", buf);
	fclose(fp);
	return 1;
}

static int execute_script(struct option_script_s *script)
{
	struct option_arg_s *arg;
	char cmd[500] = "";

	sprintf(cmd, "/bin/sh %s", script->file);
	if (0 == script->arg_num)
		goto done;

	arg = script->arg;
	while (arg)
	{
		sprintf(cmd, "%s %s", cmd, arg->value);
		arg = arg->next;
	}
done:
	sprintf(cmd, "%s&", cmd);
	system(cmd);

	return 0;
}

static int refresh_option_module(
	struct client_option_s 	*cp,
	unsigned char *keyword,
	unsigned char *value,
	unsigned char *mac
)
{
	struct client_option_s 	*cur;
	unsigned char *opt_value;
	int updated = 0;
	int rv = 0;

	cur = cp;
	while (cur)
	{
		opt_value = cur->opt_value;
		if (opt_value)
		{
			if (strstr(value, opt_value) || *opt_value == '*')
			{
				if (cur->offer && *cur->offer == 0)
					rv = 1;
				updated = 0;
				if (cur->file)
					updated = write_option_file(cur->file, mac, keyword, value);
				if (updated && strcmp("none", cur->script.file) != 0)
					execute_script(&cur->script);
			}
		}
		cur = cur->next;
	}
	return rv;
}

static int do_vendor_action(
	unsigned char state,
	int vif,
	unsigned char *keyword,
	unsigned char *value,
	unsigned int value_len,
	unsigned char *mac
)
{
	struct client_option_s 	*cp = NULL;
	int rv = 0;

	cp = vendor_header;
	if (!cp)
		return 0;

	rv = refresh_option_module(cp, keyword, value, mac);
	return rv;
}

static int do_client_action(
	unsigned char state,
	int vif,
	unsigned char *keyword,
	unsigned char *value,
	unsigned int value_len,
	unsigned char *mac
)
{
	struct client_option_s 	*cp = NULL;
	int rv = 0;
	int i;
	char client_id[100] = "";

	cp = client_header;
	if (!cp)
		return 0;

	for (i = 0; i < value_len; i++)
	{
		if (0 == i)
			sprintf(client_id, "%02x", value[i]);
		else
			sprintf(client_id, "%s:%02x", client_id, value[i]);
	}
	rv = refresh_option_module(cp, keyword, client_id, mac);
	return rv;
}

static int do_user_class_action(
	unsigned char state,
	int vif,
	unsigned char *keyword,
	unsigned char *value,
	unsigned int value_len,
	unsigned char *mac
)
{
	struct client_option_s 	*cp = NULL;
	int rv = 0;

	cp = user_class_header;
	if (!cp)
		return 0;

	rv = refresh_option_module(cp, keyword, value, mac);
	return rv;
}

int do_option_action(unsigned char state, struct dhcpMessage *packet, int vif)
{
	int rv = 0;
	unsigned int len;
	unsigned char *opt_id = NULL;
	char value[256];
	option_attribute *opt;

	for(opt = opt_attr_table; opt->keyword; opt++)
	{
		opt_id = get_option(packet, opt->id);
		if (opt_id)
		{
			len = *(opt_id-1);
			memcpy(value, opt_id, len);
			rv = (*opt->handler)(state, vif, opt->keyword, value, len, packet->chaddr);
		}
		opt_id = NULL;
	}
	return rv;
}
