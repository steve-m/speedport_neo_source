#ifndef _SCRIPT_H
#define _SCRIPT_H

void run_script(struct dhcpMessage *packet, const char *name);
int sc_option121(struct dhcpMessage *packet);
#endif
