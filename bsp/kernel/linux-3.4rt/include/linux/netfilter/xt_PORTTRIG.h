#ifndef _XT_PORTTRIG_TARGET
#define _XT_PORTTRIG_TARGET

struct xt_porttrig_target_info
{
	unsigned short trigger_first_port;
	unsigned short trigger_last_port;
	unsigned short trigger_proto;
#ifdef _SC_BUILD_
	unsigned short related_proto;
#endif
	unsigned short related_first_port;
	unsigned short related_last_port;
	unsigned short strict_src;
};

#endif /* _XT_PORTTRIG_TARGET */
