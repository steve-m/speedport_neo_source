/*
 *	xt_mark - Netfilter module to match NFMARK value
 *
 *	(C) 1999-2001 Marc Boucher <marc@mbsi.ca>
 *	Copyright © CC Computer Consultants GmbH, 2007 - 2008
 *	Jan Engelhardt <jengelh@medozas.de>
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License version 2 as
 *	published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/skbuff.h>

#ifdef _SC_BUILD_
#include <linux/sercomm.h>
#endif

#include <linux/netfilter/xt_mark.h>
#include <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marc Boucher <marc@mbsi.ca>");
MODULE_DESCRIPTION("Xtables: packet mark match");
MODULE_ALIAS("ipt_sc_mark");
MODULE_ALIAS("ip6t_sc_mark");

static bool
sc_mark_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
    const struct xt_mark_mtinfo1 *info = par->matchinfo;
#ifdef _SC_BUILD_
    unsigned int *mark;
    struct sercomm_head *psh;
#endif 
#ifdef _SC_BUILD_
    psh = (struct sercomm_head *)&skb->sercomm_header[0];
    mark = &psh->mark;
    return (((*mark) & info->mask) == info->mark) ^ info->invert;
#else
	return ((skb->mark & info->mask) == info->mark) ^ info->invert;
#endif
}

static struct xt_match sc_mark_mt_reg __read_mostly = {
	.name           = "sc_mark",
	.revision       = 1,
	.family         = NFPROTO_UNSPEC,
	.match          = sc_mark_mt,
	.matchsize      = sizeof(struct xt_mark_mtinfo1),
	.me             = THIS_MODULE,
};

static int __init sc_mark_mt_init(void)
{
	return xt_register_match(&sc_mark_mt_reg);
}

static void __exit sc_mark_mt_exit(void)
{
	xt_unregister_match(&sc_mark_mt_reg);
}

module_init(sc_mark_mt_init);
module_exit(sc_mark_mt_exit);
