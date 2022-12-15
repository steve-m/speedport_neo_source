/* Reuse mark to set egress queue id, 802.1p, DSCP, egress rule priority
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
* zzzz   --- MARK(of queue index)   (0~255)
*/
#ifndef _NET_QOS_CLS_H_
#define _NET_QOS_CLS_H_

#define _MARK_VALUESHIFT_           0
#define _MARK_VALUEBITS_            4
#define _MARK_VALUEMASK_            ((1<<_MARK_VALUEBITS_) - 1)

#define GET_MARK_VALUE(t)           (((t)>>_MARK_VALUESHIFT_)&_MARK_VALUEMASK_)

#define _DSCP_VALUESHIFT_           (_MARK_VALUESHIFT_ + _MARK_VALUEBITS_)
#define _DSCP_VALUEBITS_            6
#define _DSCP_VALUEMASK_            ((1<<_DSCP_VALUEBITS_) - 1)

#define _DSCP_TYPESHIFT_            (_DSCP_VALUESHIFT_ + _DSCP_VALUEBITS_)
#define _DSCP_TYPEBITS_             1
#define _DSCP_TYPEMASK_             ((1<<_DSCP_TYPEBITS_) - 1)

#define GET_DSCP_REMARK_FLAG(t)     (((t)>>_DSCP_TYPESHIFT_)&_DSCP_TYPEMASK_)
#define CLR_DSCP_REMARK_FLAG(t)     ((*(t))&(~(_DSCP_TYPEMASK_<<_DSCP_TYPESHIFT_)))
#define GET_DSCP_REMARK_VALUE(t)    (((t)>>_DSCP_VALUESHIFT_)&_DSCP_VALUEMASK_)

#define _8021P_VALUESHIFT_          (_DSCP_TYPESHIFT_ + _DSCP_TYPEBITS_)
#define _8021P_VALUEBITS_           3
#define _8021P_VALUEMASK_           ((1<<_8021P_VALUEBITS_) - 1)

#define _8021P_TYPESHIFT_           (_8021P_VALUESHIFT_ + _8021P_VALUEBITS_)
#define _8021P_TYPEBITS_            1
#define _8021P_TYPEMASK_            ((1<<_8021P_TYPEBITS_) - 1)
							
#define GET_8021P_REMARK_FLAG(t)    (((t)>>_8021P_TYPESHIFT_)&_8021P_TYPEMASK_)
#define CLR_8021P_REMARK_FLAG(t)    ((*(t))&(~(_8021P_TYPEMASK_<<_8021P_TYPESHIFT_)))
#define GET_8021P_REMARK_VALUE(t)   (((t)>>_8021P_VALUESHIFT_)&_8021P_VALUEMASK_)


//egress rule priority
#define _RULEPRIO_VALUESHIFT_       (_8021P_TYPESHIFT_ + _8021P_TYPEBITS_)
#define _RULEPRIO_VALUEBITS_        6
#define _RULEPRIO_VALUEMASK_        ((1<<_RULEPRIO_VALUEBITS_) - 1)

#define _RULEPRIO_FLAGSHIFT_        (_RULEPRIO_VALUESHIFT_ + _RULEPRIO_VALUEBITS_)
#define _RULEPRIO_FLAGBITS_         1
#define _RULEPRIO_FLAGMASK_         ((1<<_RULEPRIO_FLAGBITS_) - 1)

#define GET_RULEPRIO_VALUE(t)       (((t)>>_RULEPRIO_VALUESHIFT_)&_RULEPRIO_VALUEMASK_)
#define GET_RULEPRIO_FLAG(t)        (((t)>>_RULEPRIO_FLAGSHIFT_)&_RULEPRIO_FLAGMASK_)


static inline int get_generic_value(int v, int v_bits, int v_shift)
{
    int value_mask = ((1<<v_bits) - 1)<<v_shift;
    
    return (v&value_mask)>>v_shift;
}

static inline void set_generic_value(int *saved, int v, int v_bits, int v_shift)
{
    int value_mask = ((1<<v_bits) - 1)<<v_shift;
    
    if(!saved)
        return;
    
    if((v < 0) || (v > ((1<<v_bits)-1))) 
        return;

    (*saved) &= ~value_mask;               
    (*saved) |= (v<<v_shift)&value_mask;          
}

static inline int get_generic_value_flag(int v, int f_bits, int f_shift, int v_bits, int v_shift)
{
    int flag_mask = ((1<<f_bits) - 1)<<f_shift;
    int value_mask = ((1<<v_bits) - 1)<<v_shift;
    
    if(!(v&flag_mask))
        return -1;
        
    return (v&value_mask)>>v_shift;
}

static inline void set_generic_value_flag(int *saved, int v, int f_bits, int f_shift, int v_bits, int v_shift)
{
    int flag_mask = ((1<<f_bits) - 1)<<f_shift;
    int value_mask = ((1<<v_bits) - 1)<<v_shift;
    
    if(!saved)
        return;

    if((v < 0) || (v > ((1<<v_bits)-1))) 
        return;
    
    *saved |= (1<<f_shift)&flag_mask;        
    (*saved) &= ~value_mask;               
    *saved |= (v<<v_shift)&value_mask;          
}

#endif
