/*
 * Generic port triggering for iptables xtension framework
 *
 * Copyright (C) 2010 Broadlight Ltd.. All rights reserved.
 *
 * Contact: KT <kirill@broadlight.com>
 *
 */

#include <linux/module.h>
#include <linux/inetdevice.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/list.h>
#include <linux/tcp.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <net/checksum.h>
#include <net/route.h>

#include <net/netfilter/nf_conntrack.h>
#ifdef CONFIG_NF_NAT_NEEDED
#include <net/netfilter/nf_nat_rule.h>
#else
#include <linux/netfilter_ipv4/ip_nat_rule.h>
#endif
#include <linux/netfilter_ipv4.h>

#include <linux/netfilter/x_tables.h>
#include <linux/netfilter/xt_PORTTRIG.h>

MODULE_AUTHOR("KT <kirill@broadlight.com>");
MODULE_LICENSE("NON GPL");
MODULE_DESCRIPTION("iptables port triggering target module");
MODULE_ALIAS("ipt_PORTTRIG");

DEFINE_RWLOCK(ip_conntrack_lock);
EXPORT_SYMBOL_GPL(ip_conntrack_lock);

#if 0
#define DEBUGP(args...) printk(KERN_CRIT "$$$:PTRG | " args);
#define DEBUGP_ERR(args...) printk(KERN_CRIT "$$$:PTRG | " args);
#define DEBUGP2(args...) printk(KERN_CRIT ">->:PTRG | " args);
#else
#define DEBUGP(args...)
#define DEBUGP_ERR(args...)
#define DEBUGP2(args...)
#endif

#ifdef CONFIG_NETFILTER_DEBUG
#define IP_NF_ASSERT(x)					\
do {								\
	if (!(x))						\
		printk("ARP_NF_ASSERT: %s:%s:%u\n",		\
		       __func__, __FILE__, __LINE__);	\
} while(0)
#else
#define IP_NF_ASSERT(x)
#endif

LIST_HEAD(porttrig_list);

#ifdef _SC_BUILD_
#define TRIGGER_TIMEOUT 300
#else
#define TRIGGER_TIMEOUT 20 		/* 20 Sec, same as the firewall rule lifetime - good idea to keep them the same */
#endif

#define IPPROTO_ALL 	0xFE	/* Dummy value for ALL protocols: ALL means TCP+UDP */


#ifdef CONFIG_NF_BL_EXT
extern int (*rgw_add_firewall_rule_handler)(
	__be32 user_rule_index,
	__be32 type,
	__be32 dstip,
	__be16 portrange[2],
	__be32 protocol,
	__be32 srcip,
	__be32 *p_mw_rule_index);

int (*rgw_refresh_firewall_rule_timer_handler)(
	__be32 mw_rule_index);

int (*rgw_remove_firewall_rule_by_index_handler)(
	__be32 mw_rule_index);


EXPORT_SYMBOL(rgw_refresh_firewall_rule_timer_handler);
EXPORT_SYMBOL(rgw_remove_firewall_rule_by_index_handler);
#endif /* CONFIG_NF_BL_EXT */

static void trigger_print(
	char* action,
	const char* routine,
	xt_porttrig *trig)
{
	DEBUGP2("%s trig(%p) list(%p)\n", routine, trig, (trig?&trig->list:0));

	DEBUGP("[%s] srcip:[%u.%u.%u.%u] --> dstip:[%u.%u.%u.%u:%d...%d] tproto:[%d] rport:[%d...%d] fw_rule_active:[%s]\n",
		action,
		NIPQUAD(trig->srcip),
		NIPQUAD(trig->dstip),
		trig->trig_first_port,
		trig->trig_last_port,
		trig->trig_proto,
		trig->related_first_port,
		trig->related_last_port,
		(trig->fw_rule_active?"YES":"NO"));
}

static void trigger_refresh(
	xt_porttrig *trig,
	unsigned long extra_jiffies)
{
    trigger_print("TRIG REFRESH", __FUNCTION__, trig);

    write_lock_bh(&ip_conntrack_lock);

    /* Need del_timer for race avoidance (may already be dying). */
    if (del_timer(&trig->timeout)) {
    	trig->timeout.expires = jiffies + extra_jiffies;
    	add_timer(&trig->timeout);
    }

#ifdef CONFIG_NF_BL_EXT
	if (nf_conntrack_bl_fast_path_enabled &&
		rgw_refresh_firewall_rule_timer_handler &&
		trig->fw_rule_active) {
		int retCode     			= 0;

		/* Call back to fi_bl_add_firewall_rule() */
		retCode = rgw_refresh_firewall_rule_timer_handler(
			trig->fw_rule_index									/* IN: fw rule index     */
		);

		if (retCode) {
			KPRINTERR("rgw_refresh_firewall_rule_timer_handler() returned ERROR=%d", retCode);
		}
	}
#endif /* CONFIG_NF_BL_EXT */

    write_unlock_bh(&ip_conntrack_lock);
}

static void trigger_delete(
	xt_porttrig *trig)
{
	trigger_print("TRIG DELETE", __FUNCTION__, trig);

#ifdef CONFIG_NF_BL_EXT
	if (nf_conntrack_bl_fast_path_enabled &&
		rgw_remove_firewall_rule_by_index_handler &&
		trig->fw_rule_active) {
		int retCode     			= 0;

		/* Call back to fi_bl_remove_firewall_rule() */
		retCode = rgw_remove_firewall_rule_by_index_handler(
			trig->fw_rule_index									/* IN: fw rule index     */
		);

		if (retCode) {
			KPRINTERR("rgw_remove_firewall_rule_by_index_handler() returned ERROR=%d", retCode);
		}
	}
#endif /* CONFIG_NF_BL_EXT */

#ifdef _SC_BUILD_
        list_del(&trig->master_ct);
#else 
        del_timer(&trig->timeout);
#endif

        /* delete from list */
        list_del(&trig->list);
        kfree(trig);
}

void trigger_timeout(unsigned long ul_trig)
{
        xt_porttrig *trig= (void *) ul_trig;

        trigger_print("TRIG TIEMOUT", __FUNCTION__, trig);

        write_lock_bh(&ip_conntrack_lock);
        trigger_delete(trig);
        write_unlock_bh(&ip_conntrack_lock);
}
EXPORT_SYMBOL(trigger_timeout);

static unsigned int trigger_new(
	xt_porttrig *trig,
	struct sk_buff **pskb,
	const struct net_device *out,
	const void *targinfo)
{
#ifdef CONFIG_NF_BL_EXT
    const struct xt_porttrig_target_info *ptinfo = targinfo;
#endif
    xt_porttrig *new = NULL;

    DEBUGP2("%s: TRIG NEW IN\n", __FUNCTION__);

    write_lock_bh(&ip_conntrack_lock);

    new = (xt_porttrig *) kmalloc(sizeof(xt_porttrig), GFP_ATOMIC);

    if (!new) {
    	write_unlock_bh(&ip_conntrack_lock);
		DEBUGP_ERR("%s: OOM allocating trigger list\n", __FUNCTION__);
		return -ENOMEM;
    }

    memset(new, 0, sizeof(xt_porttrig));
    INIT_LIST_HEAD(&new->list);
    memcpy(new, trig, sizeof(xt_porttrig));

    trigger_print("TRIG NEW", __FUNCTION__, trig);

    DEBUGP2("%s: TRIG NEW: porttrig_list(%p) new(%p)\n", __FUNCTION__, &porttrig_list, new);

    /* add to global table of trigger */
    list_add(&new->list, &porttrig_list);

#ifdef _SC_BUILD_
        /*
         * Link this triggered rules to related conntrack, make it's life time
         * same as conntrack.
         */
        {
                enum ip_conntrack_info ctinfo;
                struct nf_conn *ct;
                INIT_LIST_HEAD(&new->master_ct);
                ct = nf_ct_get(*pskb, &ctinfo);
                if(ct) {
                        list_add(&new->master_ct, &ct->port_triggers);
                }
        }
#else
        /* add and start timer if required */
        init_timer(&new->timeout);

        new->timeout.data = (unsigned long) new;
        new->timeout.function = trigger_timeout;
        new->timeout.expires = jiffies + (TRIGGER_TIMEOUT * HZ);

        add_timer(&new->timeout);
#endif

#ifdef CONFIG_NF_BL_EXT
	if (nf_conntrack_bl_fast_path_enabled &&
		rgw_add_firewall_rule_handler) {
		u_int16_t fwPortRange[2]	= {0, 0};
		int retCode     			= 0;
#ifdef CONFIG_NF_NAT_NEEDED
		struct nf_conn_nat *nat;
#endif

		struct nf_conn *ct;

		enum ip_conntrack_info ctinfo;
		struct rtable *rt;
		__be32 newsrc;

		ct = nf_ct_get(*pskb, &ctinfo);

#ifdef CONFIG_NF_NAT_NEEDED
		if (ct) {
			nat = nfct_nat(ct);
		}
#endif

		rt = skb_rtable(*pskb);
		newsrc = inet_select_addr(out, rt->rt_gateway, RT_SCOPE_UNIVERSE);
		if (!newsrc) {
			KPRINTERR("PORTTRIG-MASQUERADE: %s ate my IP address", out->name);
			return NF_ACCEPT;
		}

		DEBUGP("PORTTRIG FW RULE (%p):  [%u.%u.%u.%u:%d...%d] --> [%u.%u.%u.%u:%d...%d] + proto[%d] + strict_src[%s]\n",
			ct,
			NIPQUAD(new->dstip),
			ntohs(new->trig_first_port),
			ntohs(new->trig_last_port),
			NIPQUAD(newsrc),
			ntohs(new->related_first_port),
			ntohs(new->related_last_port),
			new->trig_proto,
			(ptinfo->strict_src?"YES":"NO"));

		fwPortRange[0]     	= ntohs(new->related_first_port);
		fwPortRange[1]     	= ntohs(new->related_last_port);

		/* Call back to fi_bl_add_firewall_rule() */
		retCode = rgw_add_firewall_rule_handler(
			(int) new,											/* IN : user_rule_index    */
			en_fw_rule_dynamic,									/* IN : rule type          */
			ntohl(newsrc),										/* IN : xi_dst_ip_subnet   */
			fwPortRange, 										/* IN : xi_port_range      */
#ifdef _SC_BUILD_
			ntohl(new->rel_proto), 								/* IN : xi_protocol        */
#else
			ntohl(new->trig_proto), 							/* IN : xi_protocol        */
#endif
			(ptinfo->strict_src?new->dstip:0),					/* IN : xi_src_ip          */
			&new->fw_rule_index									/* OUT: new rule index     */
		);

		if (retCode) {
			KPRINTERR("rgw_add_firewall_rule_handler() returned ERROR=%d", retCode);
		}

		new->fw_rule_active = 1;
	} else
		KPRINTERR("RGW module with rgw_add_firewall_rule_handler() is not loaded: 0x%x", (int) rgw_add_firewall_rule_handler);
#endif /* CONFIG_NF_BL_EXT */

    write_unlock_bh(&ip_conntrack_lock);

    DEBUGP2("%s: TRIG NEW IN -OUT-\n", __FUNCTION__);

    return 0;
}

static xt_porttrig* trigger_find_entry(
	struct iphdr  *iph,
	struct tcphdr *tcph,
        const struct xt_porttrig_target_info *ptinfo)
{
	struct list_head *p;

    DEBUGP2("%s:TRIG FIND ENTRY IN: iph.proto:[%d] tcph->dest_port:[%d]\n", __FUNCTION__,
    	iph->protocol,
    	tcph->dest);

	list_for_each_prev(p, &porttrig_list) {
		xt_porttrig *found = (xt_porttrig *) p;

		if ((found->trig_proto == iph->protocol) &&
			(((__be16) found->trig_first_port)  >= tcph->dest) &&
			(((__be16) found->trig_last_port)   <= tcph->dest)
			) {

                        if((found->rel_proto == ptinfo->related_proto) &&
                           (found->related_first_port == ptinfo->related_first_port) &&
                          (found->related_last_port == ptinfo->related_last_port)) {

                            trigger_print("TRIG ENTRY FOUND", __FUNCTION__, found);

                            return found;
                        }
		}
	}

	DEBUGP2("%s:TRIG not Found\n", __FUNCTION__);

	return NULL;
}

static xt_porttrig* trigger_find_reply_entry(
	struct iphdr  *iph,
	struct tcphdr *tcph)
{
	struct list_head *p;

    DEBUGP2("%s:TRIG FIND REPLY ENTRY IN: iph.proto:[%d] tcph->dest_port:[%d]\n", __FUNCTION__,
    	iph->protocol,
    	tcph->dest);

	list_for_each_prev(p, &porttrig_list) {
		xt_porttrig *found = (xt_porttrig *) p;

  
#ifdef _SC_BUILD_
		if ((found->rel_proto == iph->protocol)
#else
		if ((found->trig_proto == iph->protocol)
#endif
			&& (((__be16) found->related_first_port) <= tcph->dest)
			&& (((__be16) found->related_last_port)  >= tcph->dest)) {

			trigger_print("TRIG REPLY FOUND", __FUNCTION__, found);

			return found;
		}
	}

	DEBUGP2("%s:TRIG REPLY not Found\n", __FUNCTION__);

	return NULL;
}

static unsigned int trigger_out(
	struct sk_buff **pskb,
	unsigned int hooknum,
	const struct net_device *in,
	const struct net_device *out,
	const struct xt_target *target,
	const void *targinfo)
{
    const struct xt_porttrig_target_info *ptinfo = targinfo;
    xt_porttrig trig, *found;
    const struct iphdr *iph = ip_hdr(*pskb);
    struct tcphdr *tcph 	= (void *)iph + iph->ihl*4;

    DEBUGP2("%s:TRIG_OUT IN: from IF:[%s] to IF:[%s] \n", __FUNCTION__, in->name, out->name);

   /* Only TCP, UDP and ALL protocols are supported */
	if ((iph->protocol != IPPROTO_TCP) &&
		(iph->protocol != IPPROTO_UDP))
		return XT_CONTINUE;

	/* TCP case */
	if ((iph->protocol != IPPROTO_TCP) && (ptinfo->trigger_proto == IPPROTO_TCP))
		return XT_CONTINUE;

	/* UDP case */
	if ((iph->protocol != IPPROTO_UDP) && (ptinfo->trigger_proto == IPPROTO_UDP))
		return XT_CONTINUE;

	if ((ptinfo->trigger_first_port <= ((unsigned int) tcph->dest)) &&
		(ptinfo->trigger_last_port >= ((unsigned int) tcph->dest))
	   ) { /* Check destination triggering port */

		DEBUGP("TARGET:[%s] MATCHED OK: target-ports&tcph->dest:[%d...%d&%d]\n",
			target->name, ptinfo->trigger_first_port, ptinfo->trigger_last_port, tcph->dest);

		if (ptinfo->trigger_proto != IPPROTO_ALL) /* If protocol is matter - check it */
			if (ptinfo->trigger_proto != iph->protocol) /* If protocol is not matching - continue */
				return XT_CONTINUE;
	} else
		return XT_CONTINUE;

    found = trigger_find_entry((struct iphdr*) iph, (struct tcphdr*) tcph, ptinfo);

    if (found) { /* Refresh */

    	DEBUGP2("%s:TRIG ENTRY FOUND - Refresh. IP:[0x%x] proto:[%d]\n", __FUNCTION__, found->srcip, found->trig_proto);

		trigger_refresh(found, TRIGGER_TIMEOUT * HZ);

		/* Multiple hosts can use the same port range */
		if (found->reply)
			found->srcip = iph->saddr;
    }
    else { /* New */

		memset(&trig, 0, sizeof(trig));

		trig.srcip 				= iph->saddr;
		trig.dstip 				= iph->daddr;
		trig.trig_first_port    = ptinfo->trigger_first_port;
		trig.trig_last_port     = ptinfo->trigger_last_port;
		trig.trig_proto 		= ptinfo->trigger_proto;
#ifdef _SC_BUILD_
		trig.rel_proto 			= ptinfo->related_proto;
#else
		trig.rel_proto 			= ptinfo->trigger_proto;
#endif
		trig.related_first_port = ptinfo->related_first_port;
		trig.related_last_port  = ptinfo->related_last_port;

		trigger_print("ADDING NEW TRIGGER", __FUNCTION__, &trig);

		trigger_new(&trig, pskb, out, targinfo);
    }
    return XT_CONTINUE;
}

static unsigned int trigger_in(
	struct sk_buff **pskb,
	unsigned int hooknum,
	const struct net_device *in,
	const struct net_device *out,
	const struct xt_target *target,
	const void *targinfo)
{
 //   const struct xt_porttrig_target_info *ptinfo = targinfo;
    xt_porttrig *found;
    const struct iphdr *iph = ip_hdr(*pskb);
    struct tcphdr *tcph 	= (void *)iph + iph->ihl*4;

	DEBUGP2("%s:TRIG_IN IN: from IF:[%s] to IF:[%s] \n", __FUNCTION__, in->name, out->name);

	DEBUGP2("TARGET:[%s] target-ports&proto:[%d...%d&%d] tcph->dest&proto:[%d&%d] rel_port[%d...%d]\n",
		target->name,
		ptinfo->trigger_first_port, ptinfo->trigger_last_port, ptinfo->trigger_proto,
		tcph->dest, iph->protocol,
		ptinfo->related_first_port, ptinfo->related_last_port);

    found = trigger_find_reply_entry((struct iphdr*) iph, (struct tcphdr*) tcph);

    if (found) {
		struct nf_conn *ct;

		enum ip_conntrack_info ctinfo;
		struct nf_nat_ipv4_range range1;

    	DEBUGP("%s:TRIG REPLY ENTRY FOUND. IP:[%u.%u.%u.%u] proto:[%d]\n", __FUNCTION__,
    		NIPQUAD(found->srcip), found->trig_proto);

		//trigger_refresh(found, TRIGGER_TIMEOUT * HZ);

		ct = nf_ct_get(*pskb, &ctinfo);
		IP_NF_ASSERT(ct && (ctinfo == IP_CT_NEW));

		DEBUGP2("1:TRIG REPLY CONN(%p) ORIG: %u.%u.%u.%u:%d --proto[%d]-->  %u.%u.%u.%u:%d\n",
		   ct,
		   NIPQUAD(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip),
		   ntohs(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u.tcp.port),
		   ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum,
		   NIPQUAD(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u3.ip),
		   ntohs(ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.u.tcp.port));

		DEBUGP2("1:TRIG REPLY CONN(%p) REPLY: %u.%u.%u.%u:%d -proto[%d]-->  %u.%u.%u.%u:%d\n",
		   ct,
		   NIPQUAD(ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip),
		   ntohs(ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u.tcp.port),
		   ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.protonum,
		   NIPQUAD(ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip),
		   ntohs(ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u.tcp.port));

		/* Manual DNAT/SNAT manipulation for unexpected, but desired reply connection */
		/* Fix the destination address of the original request */
		range1.flags = NF_NAT_RANGE_MAP_IPS;
		range1.min_ip = range1.max_ip = found->srcip;

		/* hook doesn't matter, but it has to do destination manip */
		nf_nat_setup_info(ct, &range1, NF_NAT_MANIP_DST);

#if 0
                /*
                 * didn't delete the trigger rule, or the trigger rule will
                 * accept once only.
                 */
                 write_lock_bh(&ip_conntrack_lock);
                 trigger_delete(found);
                 write_unlock_bh(&ip_conntrack_lock);
#endif

		return NF_ACCEPT; /* Accept it, or the incoming packet could be dropped in the FORWARD chain */
	}
	return XT_CONTINUE; /* Our job is the interception */
}

static unsigned int
porttrig_target(struct sk_buff *skb,
	 const struct xt_action_param *par)
{
	const struct xt_porttrig_target_info *ptinfo = NULL;
	const struct iphdr *iph = NULL;
	struct tcphdr *tcph 	= NULL;

	if (skb) {
		iph  = ip_hdr(skb);
		tcph = (void*) iph + iph->ihl*4;
	} else {
		DEBUGP_ERR("porttrig_target(): *pskb is NULL\n");
		return XT_CONTINUE;
	}

	if (par) {
		ptinfo = (struct xt_porttrig_target_info*) par->targinfo;
	} else {
		DEBUGP_ERR("porttrig_target(): targinfo is NULL\n");
		return XT_CONTINUE;
	}

	DEBUGP2("TARGET:[%s] Hook:[%s] target-ports&proto:[%d...%d&%d] tcph->dest&proto:[%d&%d]\n",
		par->target->name,
		(par->hooknum==NF_INET_PRE_ROUTING?"NF_INET_PRE_ROUTING":(par->hooknum==NF_INET_POST_ROUTING?"NF_INET_PRE_ROUTING":"Unknown Hook")),
		ptinfo->trigger_first_port, ptinfo->trigger_last_port,
		ptinfo->trigger_proto,
		tcph->dest,
		iph->protocol);

    if (par->out && par->out->name) {
    	DEBUGP2("%s:TRIG OUTGOING. IP:[0x%x] proto:[%d]\n", __FUNCTION__, tcph->source, ptinfo->trigger_proto);

    	return trigger_out(&skb, par->hooknum, par->in, par->out, par->target, par->targinfo);
    } else {
    	if (par->in && par->in->name) {
    		DEBUGP2("%s:TRIG INCOMING. IP:[0x%x] proto:[%d]\n", __FUNCTION__, tcph->source, ptinfo->trigger_proto);

    		return trigger_in(&skb, par->hooknum, par->in, par->out, par->target, par->targinfo);
    	} else {
    		DEBUGP2("%s:TRIG UNKNOWN DIRECTION. IP:[0x%x] proto:[%d]\n", __FUNCTION__, tcph->source, ptinfo->trigger_proto);
    	}
    }
    return XT_CONTINUE;
}

static int
porttrig_checkentry(const struct xt_tgchk_param *par)
{
	const struct xt_porttrig_target_info *ptinfo = par->targinfo;

	DEBUGP("%s: IN: tr.name:[%s] trig-ports:[%d...%d] trig_proto:[%d] rel-ports:[%d...%d] strict source:[%s]\n", __FUNCTION__,
		par->target->name,
		ptinfo->trigger_first_port,
		ptinfo->trigger_last_port,
		ptinfo->trigger_proto,
		ptinfo->related_first_port,
		ptinfo->related_last_port,
		(ptinfo->strict_src?"YES":"NO"));

	if ((ptinfo->trigger_proto != IPPROTO_TCP) &&
		(ptinfo->trigger_proto != IPPROTO_UDP) &&
    	(ptinfo->trigger_proto != IPPROTO_ALL)) {

		DEBUGP_ERR("%s: PORT TRIGGERING ERROR: only TCP and UDP are supported in --trigger-proto[%d]\n",
			__FUNCTION__, ptinfo->trigger_proto);
		return 1;
	}

	DEBUGP2("%s: OUT:OK\n", __FUNCTION__);
	return 0;
}

/*static void porttrig_destroy(
	const struct xt_target *target,
	void *targinfo)
{
//	const struct xt_porttrig_target_info *ptinfo = targinfo;

	DEBUGP2("%s: IN\n", __FUNCTION__);
}*/

static struct xt_target xt_porttrig_target[] = {
	{
		.name 		= "PORTTRIG",
		.family		= AF_INET,
		.checkentry	= porttrig_checkentry,	/* Validation */
		.target 	= porttrig_target,		/* Per packet check */
//		.destroy 	= porttrig_destroy,		/* Destroy the target */
		.targetsize	= sizeof(struct xt_porttrig_target_info),
		.table		= "nat",
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				      (1 << NF_INET_POST_ROUTING),
		.me 		= THIS_MODULE,
	}
};

static int __init xt_porttrig_init(void)
{
	return xt_register_targets(xt_porttrig_target,
				   ARRAY_SIZE(xt_porttrig_target));
}

static void __exit xt_porttrig_fini(void)
{
	xt_unregister_targets(xt_porttrig_target,
			      ARRAY_SIZE(xt_porttrig_target));
}

module_init(xt_porttrig_init);
module_exit(xt_porttrig_fini);
