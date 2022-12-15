/**
 * @file   sercomm.h
 * @owner  Denny Zhang
 * 
 *
 **version  who     when          what
 * 0.1      Denny   2010-09-15    init version
 *
 * @copyright 2010 SerComm Corporation. All Rights Reserved.
 */
#ifndef _SERCOMM_H_
#define _SERCOMM_H_
#include <asm/types.h>
#include <net/qos_cls.h>

#define SERCOMM_HEADER_LEN	    20

typedef struct sercomm_head {
    
    unsigned int		mark;
    
/* Reuse mark to set 802.1p,DSCP,guess access and multiwan
 *
 * 0      7 8     15 16    23 24    31
 * +------+ +------+ +------+ +------+
 * 00000000 00Pppppp pYyyyXxx xxxxzzzz
 * +------+ +------+ +------+ +------+
 * 
 * P      --- egress rule priority flag
 * pppppp --- egress rule priority, 0 means highest priority
 * X      --- enable/disable DSCP remark feature
 * xxxxxx --- DSCP   (0~63)
 * Y      --- enable/disable 802.1P remark feature
 * yyy    --- 802.1P (0~7)
 * zzzz   --- egress mark   (0~15)
 */
#define HQC_MARK_EGRESS_SHIFT   0
#define HQC_MARK_EGRESS_BITS    4 

#define HQC_MARK_DSCP_SHIFT         (HQC_MARK_EGRESS_SHIFT+HQC_MARK_EGRESS_BITS)
#define HQC_MARK_DSCP_BITS          (6)
#define HQC_MARK_DSCP_FLAG_SHIFT    (HQC_MARK_DSCP_SHIFT+HQC_MARK_DSCP_BITS)
#define HQC_MARK_DSCP_FLAG_BITS     (1)

#define HQC_MARK_ETHP_SHIFT         (HQC_MARK_DSCP_FLAG_SHIFT+HQC_MARK_DSCP_FLAG_BITS)
#define HQC_MARK_ETHP_BITS          (3)
#define HQC_MARK_ETHP_FLAG_SHIFT    (HQC_MARK_ETHP_SHIFT+HQC_MARK_ETHP_BITS)
#define HQC_MARK_ETHP_FLAG_BITS     (1)

#define HQC_MARK_PRIO_SHIFT         (HQC_MARK_ETHP_FLAG_SHIFT+HQC_MARK_ETHP_FLAG_BITS)
#define HQC_MARK_PRIO_BITS          (6)
#define HQC_MARK_PRIO_FLAG_SHIFT    (HQC_MARK_PRIO_SHIFT+HQC_MARK_PRIO_BITS)
#define HQC_MARK_PRIO_FLAG_BITS     (1)

    unsigned int 		egress_mark;
    


/* Bit define for ingress classify
 *
 * 0          7 8         15 16       23 24      31
 * +------+ +------+ +------+ +------+
 * 00000000  00000000 00000000  00yxzzzz
 * +------+ +------+ +------+ +------+
 *
 * y    --- ingress classify confirmed flag
 * x    --- ingress classified flag
 * zzzz   --- ingress mark   (0~15)
 */
#define HQC_MARK_INGRESS_SHIFT              (0)
#define HQC_MARK_INGRESS_BITS               (4)
#define HQC_MARK_INGRESS_FLAG_SHIFT         (HQC_MARK_INGRESS_SHIFT+HQC_MARK_INGRESS_BITS)
#define HQC_MARK_INGRESS_FLAG_BITS          (1)

#define HQC_MARK_INGRESS_CONFIRM_FLAG_SHIFT (HQC_MARK_INGRESS_FLAG_SHIFT+HQC_MARK_INGRESS_FLAG_BITS)
#define HQC_MARK_INGRESS_CONFIRM_FLAG_BITS  (1)

    unsigned int        ingress_mark;


/* Bit define for netfilter mark
 *
 * 0          7 8         15 16       23 24      31
 * +------+ +------+ +------+ +------+
 * 00000000  00000000 00000000  000zYyyx
 * +------+ +------+ +------+ +------+
 * Y   --- packet priority valid bit
 * yy  --- packet priority
 * x    --- fragment packet flag
 * z    --- wlan session
 */
#define SC_PKT_FRAGMENT_FLAG_SHIFT      (0)
#define SC_PKT_FRAGMENT_FLAG_BITS       (1)

#define SC_PKT_PRIO_SHIFT               (SC_PKT_FRAGMENT_FLAG_BITS+SC_PKT_FRAGMENT_FLAG_SHIFT)
#define SC_PKT_PRIO_BITS                (2)

#define SC_PKT_PRIO_VALID_FLAG_SHIFT    (SC_PKT_PRIO_SHIFT+SC_PKT_PRIO_BITS)
#define SC_PKT_PRIO_VALID_FLAG_BITS     (1)

#define SC_PKT_WLAN_SESSION_SHIFT       (SC_PKT_PRIO_VALID_FLAG_SHIFT+SC_PKT_PRIO_VALID_FLAG_BITS)
#define SC_PKT_WLAN_SESSION_BITS        (1)

   unsigned int        nf_mark;
    
    struct net_device   *saved_dev;
}sercomm_head_t;

static inline int get_egress_qid(char *sercommHeader)
{
    if(!sercommHeader)
        return -1;

    return get_generic_value(((sercomm_head_t *)sercommHeader)->egress_mark, HQC_MARK_EGRESS_BITS, HQC_MARK_EGRESS_SHIFT);        
}

static inline void set_egress_qid(char *sercommHeader, int id)
{
    if(sercommHeader)
        set_generic_value(&(((sercomm_head_t *)sercommHeader)->egress_mark), id, HQC_MARK_EGRESS_BITS, HQC_MARK_EGRESS_SHIFT);
}

static inline int get_egress_8021p(char *sercommHeader)
{
    if(!sercommHeader)
        return -1;
        
    return get_generic_value_flag(((sercomm_head_t *)sercommHeader)->egress_mark, HQC_MARK_ETHP_FLAG_BITS, HQC_MARK_ETHP_FLAG_SHIFT, HQC_MARK_ETHP_BITS, HQC_MARK_ETHP_SHIFT);
}

static inline void set_egress_8021p(char *sercommHeader, int new_pbit)
{
    if(sercommHeader)
        set_generic_value_flag(&(((sercomm_head_t *)sercommHeader)->egress_mark), new_pbit, HQC_MARK_ETHP_FLAG_BITS, HQC_MARK_ETHP_FLAG_SHIFT, HQC_MARK_ETHP_BITS, HQC_MARK_ETHP_SHIFT);
}

static inline int get_egress_dscp(char *sercommHeader)
{
    if(!sercommHeader)
        return -1;

    return get_generic_value_flag(((sercomm_head_t *)sercommHeader)->egress_mark, HQC_MARK_DSCP_FLAG_BITS, HQC_MARK_DSCP_FLAG_SHIFT, HQC_MARK_DSCP_BITS, HQC_MARK_DSCP_SHIFT);
}

static inline void set_egress_dscp(char *sercommHeader, int new_dscp)
{
    if(sercommHeader)
        set_generic_value_flag(&(((sercomm_head_t *)sercommHeader)->egress_mark), new_dscp, HQC_MARK_DSCP_FLAG_BITS, HQC_MARK_DSCP_FLAG_SHIFT, HQC_MARK_DSCP_BITS, HQC_MARK_DSCP_SHIFT);
}

static inline int get_egress_rule_prio(char *sercommHeader)
{
    if(!sercommHeader)
        return -1;

    return get_generic_value_flag(((sercomm_head_t *)sercommHeader)->egress_mark, HQC_MARK_PRIO_FLAG_BITS, HQC_MARK_PRIO_FLAG_SHIFT, HQC_MARK_PRIO_BITS, HQC_MARK_PRIO_SHIFT);        
}

static inline void set_egress_rule_prio(char *sercommHeader, int prio)
{
    if(sercommHeader)
        set_generic_value_flag(&(((sercomm_head_t *)sercommHeader)->egress_mark), prio, HQC_MARK_PRIO_FLAG_BITS, HQC_MARK_PRIO_FLAG_SHIFT, HQC_MARK_PRIO_BITS, HQC_MARK_PRIO_SHIFT);
}

static inline int get_ingress_classify_flag(char *sercommHeader)
{
    if(!sercommHeader)
        return -1;

    return get_generic_value(((sercomm_head_t *)sercommHeader)->ingress_mark, HQC_MARK_INGRESS_FLAG_BITS, HQC_MARK_INGRESS_FLAG_SHIFT);        
}

static inline int get_ingress_classify_confirm_flag(char *sercommHeader)
{
    if(!sercommHeader)
        return -1;

    return get_generic_value(((sercomm_head_t *)sercommHeader)->ingress_mark, HQC_MARK_INGRESS_CONFIRM_FLAG_BITS, HQC_MARK_INGRESS_CONFIRM_FLAG_SHIFT);        
}

static inline void set_ingress_classify_confirm_flag(char *sercommHeader)
{
    if(sercommHeader)
        set_generic_value(&(((sercomm_head_t *)sercommHeader)->ingress_mark), 1, HQC_MARK_INGRESS_CONFIRM_FLAG_BITS, HQC_MARK_INGRESS_CONFIRM_FLAG_SHIFT);
}

static inline int get_ingress_qidx(char *sercommHeader)
{
    if(!sercommHeader)
        return -1;
        
    return get_generic_value_flag(((sercomm_head_t *)sercommHeader)->ingress_mark, HQC_MARK_INGRESS_FLAG_BITS, HQC_MARK_INGRESS_FLAG_SHIFT, HQC_MARK_INGRESS_BITS, HQC_MARK_INGRESS_SHIFT);
}

static inline void set_ingress_qidx(char *sercommHeader, int id)
{
    if(sercommHeader)
        set_generic_value_flag(&(((sercomm_head_t *)sercommHeader)->ingress_mark), id, HQC_MARK_INGRESS_FLAG_BITS, HQC_MARK_INGRESS_FLAG_SHIFT, HQC_MARK_INGRESS_BITS, HQC_MARK_INGRESS_SHIFT);
}

static inline int get_sercomm_mark(char *sercommHeader)
{
    struct sercomm_head *sercommH = (struct sercomm_head *)sercommHeader;
    
    return sercommH->mark;
}

static inline int get_pkt_fragment_flag(char *sercommHeader)
{
    if(!sercommHeader)
        return -1;

    return get_generic_value(((sercomm_head_t *)sercommHeader)->nf_mark, SC_PKT_FRAGMENT_FLAG_BITS, SC_PKT_FRAGMENT_FLAG_SHIFT);        
}

static inline void set_pkt_fragment_flag(char *sercommHeader)
{
    if(sercommHeader)
        set_generic_value(&(((sercomm_head_t *)sercommHeader)->nf_mark), 1, SC_PKT_FRAGMENT_FLAG_BITS, SC_PKT_FRAGMENT_FLAG_SHIFT);
}

enum{
    SC_PKT_PRIO_FIRST = 0,
    SC_PKT_PRIO_NORMAL = SC_PKT_PRIO_FIRST,
    SC_PKT_PRIO_HIGH = 1,
    SC_PKT_PRIO_LAST = SC_PKT_PRIO_HIGH
};

static inline int get_sc_pkt_prio(char *sercommHeader)
{
    if(!sercommHeader)
        return -1;

    return get_generic_value_flag(((sercomm_head_t *)sercommHeader)->nf_mark, SC_PKT_PRIO_VALID_FLAG_BITS, SC_PKT_PRIO_VALID_FLAG_SHIFT, SC_PKT_PRIO_BITS, SC_PKT_PRIO_SHIFT);
}

static inline void set_sc_pkt_prio(char *sercommHeader, int prio)
{
    if((prio < SC_PKT_PRIO_FIRST) || (prio > SC_PKT_PRIO_LAST))
        return;

    if(sercommHeader)
        set_generic_value_flag(&(((sercomm_head_t *)sercommHeader)->nf_mark), prio, SC_PKT_PRIO_VALID_FLAG_BITS, SC_PKT_PRIO_VALID_FLAG_SHIFT, SC_PKT_PRIO_BITS, SC_PKT_PRIO_SHIFT);
}

static inline int get_pkt_wlan_session(char *sercommHeader)
{
    if(!sercommHeader)
        return -1;

    return get_generic_value(((sercomm_head_t *)sercommHeader)->nf_mark, SC_PKT_WLAN_SESSION_BITS, SC_PKT_WLAN_SESSION_SHIFT);
}

static inline void set_pkt_wlan_session(char *sercommHeader)
{
    if(sercommHeader)
        set_generic_value(&(((sercomm_head_t *)sercommHeader)->nf_mark), 1, SC_PKT_WLAN_SESSION_BITS, SC_PKT_WLAN_SESSION_SHIFT);
}

#endif  /*_SERCOMM_H_*/
