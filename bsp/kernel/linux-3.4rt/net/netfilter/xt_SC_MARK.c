/*
 *	xt_MARK - Netfilter module to modify the NFMARK field of an skb
 *
 *	(C) 1999-2001 Marc Boucher <marc@mbsi.ca>
 *	Copyright © CC Computer Consultants GmbH, 2007 - 2008
 *	Jan Engelhardt <jengelh@computergmbh.de>
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License version 2 as
 *	published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <net/checksum.h>
#ifdef _SC_BUILD_
#include <linux/sercomm.h>
#endif
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter/xt_MARK.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marc Boucher <marc@mbsi.ca>");
MODULE_DESCRIPTION("Xtables: packet mark modification");
MODULE_ALIAS("ipt_SC_MARK");
MODULE_ALIAS("ip6t_SC_MARK");

static unsigned int
sc_mark_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_mark_tginfo2 *info = par->targinfo;
#ifdef _SC_BUILD_
        /* check rule priority id firstly */
{
        struct sercomm_head *psh; 
#if 1   /*Used for fon public traffic filter out*/
        psh = (struct sercomm_head *)&((skb)->sercomm_header[0]);
        psh->mark = info->mark;
#else        
        int r1 = get_egress_rule_prio((skb)->sercomm_header);
        int r2 = get_generic_value_flag(info->mark, _RULEPRIO_FLAGBITS_, _RULEPRIO_FLAGSHIFT_, _RULEPRIO_VALUEBITS_, _RULEPRIO_VALUESHIFT_);

        //already marked by higher priority rule
        if((r1 >= 0) && (r1 < r2))
        {
            return XT_CONTINUE;
        }
        psh = (struct sercomm_head *)&((skb)->sercomm_header[0]);
        psh->egress_mark = (psh->egress_mark & ~info->mask) ^ info->mark;
#endif
}
#endif
	return XT_CONTINUE;
}

static struct xt_target sc_mark_tg_reg __read_mostly = {
	.name           = "SC_MARK",
	.revision       = 2,
	.family         = NFPROTO_UNSPEC,
	.target         = sc_mark_tg,
	.targetsize     = sizeof(struct xt_mark_tginfo2),
	.me             = THIS_MODULE,
};

static int __init sc_mark_tg_init(void)
{
	return xt_register_target(&sc_mark_tg_reg);
}

static void __exit sc_mark_tg_exit(void)
{
	xt_unregister_target(&sc_mark_tg_reg);
}

module_init(sc_mark_tg_init);
module_exit(sc_mark_tg_exit);
