/*
 * fsm.c - {Link, IP} Control Protocol Finite State Machine.
 *
 * Copyright (c) 1984-2000 Carnegie Mellon University. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The name "Carnegie Mellon University" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For permission or any legal
 *    details, please contact
 *      Office of Technology Transfer
 *      Carnegie Mellon University
 *      5000 Forbes Avenue
 *      Pittsburgh, PA  15213-3890
 *      (412) 268-4387, fax: (412) 268-7395
 *      tech-transfer@andrew.cmu.edu
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by Computing Services
 *     at Carnegie Mellon University (http://www.cmu.edu/computing/)."
 *
 * CARNEGIE MELLON UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO
 * THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS, IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE
 * FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define RCSID	"$Id: fsm.c,v 1.23 2004/11/13 02:28:15 paulus Exp $"

/*
 * TODO:
 * Randomize fsm id on link/init.
 * Deal with variable outgoing MTU.
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#ifdef SC_DT_SUPPORT
#include <syslog.h>
#include "log_api.h"
#endif

#include "pppd.h"
#include "fsm.h"

static const char rcsid[] = RCSID;

static void fsm_timeout __P((void *));
#ifdef SC_DT_SUPPORT
static void sc_sconfreq_retry __P((void *));
static void sc_ipcp_penalty __P((void *));
#endif
static void fsm_rconfreq __P((fsm *, int, u_char *, int));
static void fsm_rconfack __P((fsm *, int, u_char *, int));
static void fsm_rconfnakrej __P((fsm *, int, int, u_char *, int));
static void fsm_rtermreq __P((fsm *, int, u_char *, int));
static void fsm_rtermack __P((fsm *));
static void fsm_rcoderej __P((fsm *, u_char *, int));
static void fsm_sconfreq __P((fsm *, int));

#define PROTO_NAME(f)	((f)->callbacks->proto_name)

int peer_mru[NUM_PPP];


/*
 * fsm_init - Initialize fsm.
 *
 * Initialize fsm state.
 */
void
fsm_init(f)
    fsm *f;
{
#ifdef SC_DT_DEBUG
    mybug("%s entry [%s].\n", __FUNCTION__, PROTO_NAME(f));
#endif
    f->state = INITIAL;
    f->flags = 0;
    f->id = 0;				/* XXX Start with random id? */
    f->timeouttime = DEFTIMEOUT;
    f->maxconfreqtransmits = DEFMAXCONFREQS;
    f->maxtermtransmits = DEFMAXTERMREQS;
    f->maxnakloops = DEFMAXNAKLOOPS;
    f->term_reason_len = 0;
}


/*
 * fsm_lowerup - The lower layer is up.
 */
void
fsm_lowerup(f)
    fsm *f;
{
    switch( f->state ){
    case INITIAL:
	f->state = CLOSED;
	break;

    case STARTING:
	if( f->flags & OPT_SILENT )
	    f->state = STOPPED;
	else {
	    /* Send an initial configure-request */
	    fsm_sconfreq(f, 0);
	    f->state = REQSENT;
	}
	break;

    default:
	FSMDEBUG(("%s: Up event in state %d!", PROTO_NAME(f), f->state));
    }
}


/*
 * fsm_lowerdown - The lower layer is down.
 *
 * Cancel all timeouts and inform upper layers.
 */
void
fsm_lowerdown(f)
    fsm *f;
{
    switch( f->state ){
    case CLOSED:
	f->state = INITIAL;
	break;

    case STOPPED:
	f->state = STARTING;
	if( f->callbacks->starting )
	    (*f->callbacks->starting)(f);
	break;

    case CLOSING:
	f->state = INITIAL;
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	break;

    case STOPPING:
    case REQSENT:
    case ACKRCVD:
    case ACKSENT:
	f->state = STARTING;
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	break;

    case OPENED:
	if( f->callbacks->down )
	    (*f->callbacks->down)(f);
	f->state = STARTING;
	break;

    default:
	FSMDEBUG(("%s: Down event in state %d!", PROTO_NAME(f), f->state));
    }
}


/*
 * fsm_open - Link is allowed to come up.
 */
void
fsm_open(f)
    fsm *f;
{
#ifdef SC_DT_DEBUG
    mybug("%s entry [%s]. state [%d]\n", __FUNCTION__, PROTO_NAME(f), f->state);
#endif
    switch( f->state ){
    case INITIAL:
	f->state = STARTING;
        if(f->protocol == PPP_LCP)
        {
            f->id = 0;
#ifdef SC_DT_DEBUG
            mybug("%s, LCP id reinit.\n", __FUNCTION__);
#endif
        }
	if( f->callbacks->starting )
	    (*f->callbacks->starting)(f);
	break;

    case CLOSED:
	if( f->flags & OPT_SILENT )
	    f->state = STOPPED;
	else {
#ifdef SC_DT_SUPPORT
            if(f->protocol == PPP_IPCP || f->protocol == PPP_IPV6CP)
            {
                f->id = 0;
                f->sc_retry = 0;
                s_cnt++;
#ifdef SC_DT_DEBUG
                mybug("%s,%d [%s] s_cnt=%d\n", __FUNCTION__, __LINE__, PROTO_NAME(f), s_cnt);
#endif
                //warn("SC_DT_SUPPORT: protocol %d fsm_open entry and s_cnt++ is %d", f->protocol, s_cnt);
            }
            else if(f->protocol == PPP_LCP)
            {
                f->id = 0;
#ifdef SC_DT_DEBUG
                mybug("%s, LCP id reinit.\n", __FUNCTION__);
#endif
            }
#endif
	    /* Send an initial configure-request */
	    fsm_sconfreq(f, 0);
	    f->state = REQSENT;
	}
	break;

    case CLOSING:
	f->state = STOPPING;
	/* fall through */
    case STOPPED:
    case OPENED:
	if( f->flags & OPT_RESTART ){
	    fsm_lowerdown(f);
	    fsm_lowerup(f);
	}
	break;
    }
}

#ifdef SC_DT_SUPPORT
static int
sc_get_ncp_active_state(f)
    fsm *f;
{
    int need_send_terminate = 1;

    if(f->protocol == PPP_IPCP)
        need_send_terminate = ipv4_active_flag;
    else if(f->protocol == PPP_IPV6CP)
        need_send_terminate = ipv6_active_flag;

    return need_send_terminate;
}
#endif /* SC_DT_SUPPORT */
/*
 * terminate_layer - Start process of shutting down the FSM
 *
 * Cancel any timeout running, notify upper layers we're done, and
 * send a terminate-request message as configured.
 */
static void
terminate_layer(f, nextstate)
    fsm *f;
    int nextstate;
{
    if( f->state != OPENED )
    {
#ifdef SC_DT_SUPPORT
        UNTIMEOUT(sc_sconfreq_retry, f);
#endif
        UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
    }
    else if( f->callbacks->down )
	(*f->callbacks->down)(f);	/* Inform upper layers we're down */

#ifdef SC_DT_DEBUG
    mybug("%s, [%s] send config terminate req\n", __FUNCTION__, PROTO_NAME(f));
#endif
    /* Init restart counter and send Terminate-Request */
    f->retransmits = f->maxtermtransmits;
    fsm_sdata(f, TERMREQ, f->reqid = ++f->id,
	      (u_char *) f->term_reason, f->term_reason_len);

    if (f->retransmits == 0) {
	/*
	 * User asked for no terminate requests at all; just close it.
	 * We've already fired off one Terminate-Request just to be nice
	 * to the peer, but we're not going to wait for a reply.
	 */
	f->state = nextstate == CLOSING ? CLOSED : STOPPED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	return;
    }

    TIMEOUT(fsm_timeout, f, f->timeouttime);
    --f->retransmits;

    f->state = nextstate;
}

/*
 * fsm_close - Start closing connection.
 *
 * Cancel timeouts and either initiate close or possibly go directly to
 * the CLOSED state.
 */
void
fsm_close(f, reason)
    fsm *f;
    char *reason;
{
    f->term_reason = reason;
    f->term_reason_len = (reason == NULL? 0: strlen(reason));
    switch( f->state ){
    case STARTING:
	f->state = INITIAL;
	break;
    case STOPPED:
	f->state = CLOSED;
	break;
    case STOPPING:
	f->state = CLOSING;
	break;

    case REQSENT:
    case ACKRCVD:
    case ACKSENT:
    case OPENED:
	terminate_layer(f, CLOSING);
	break;
    }
}


/*
 * fsm_timeout - Timeout expired.
 */
static void
fsm_timeout(arg)
    void *arg;
{
    fsm *f = (fsm *) arg;

    switch (f->state) {
    case CLOSING:
    case STOPPING:
	if( f->retransmits <= 0 ){
	    /*
	     * We've waited for an ack long enough.  Peer probably heard us.
	     */
	    f->state = (f->state == CLOSING)? CLOSED: STOPPED;
	    if( f->callbacks->finished )
		(*f->callbacks->finished)(f);
#ifdef SC_DT_SUPPORT
            if(f->state == CLOSED && (f->protocol==PPP_IPCP || f->protocol==PPP_IPV6CP))
            {
                if(f->protocol==PPP_IPCP && ipv4_idle_flag==1)
                {
                    //warn("SC_DT_SUPPORT(fsm_timeout): ipcp terminate ack recv and ipv4_idle_flag==1");
                    ipv4_idle_flag = 2;
                }

                if(f->protocol==PPP_IPCP && ipv4_idle_flag==2)
                {
                    ;
                }
                else
                {
                    s_cnt--;
                    if(s_cnt>0)
                    {
                        int timer=0;

                        if (f->protocol == PPP_IPCP || (ipv6_terminate_flag == 0 && f->protocol == PPP_IPV6CP)) {
                            f->sc_penalty++;
                            if(f->sc_penalty < f->sc_maxpenalty)
                                timer = 1<<(f->sc_penalty-1);
                            else 
                                timer = 600;
                        }
                        //warn("SC_DT_SUPPORT(fsm_timeout): S_CONT:%d > 0 so %d Penalty apply and delay %d\n", s_cnt, f->protocol, timer);
                        if(timer > 0)
                            TIMEOUT(sc_ipcp_penalty, f, timer);
                    }
                    else
                        lcp_close(0, "ipcp or ipv6cp penalty req to session close");
                }
            }
#endif
	} else {
	    /* Send Terminate-Request */
	    fsm_sdata(f, TERMREQ, f->reqid = ++f->id,
		      (u_char *) f->term_reason, f->term_reason_len);
	    TIMEOUT(fsm_timeout, f, f->timeouttime);
	    --f->retransmits;
	}
	break;

    case REQSENT:
    case ACKRCVD:
    case ACKSENT:
	if (f->retransmits <= 0) {
	    warn("%s: timeout sending Config-Requests\n", PROTO_NAME(f));
	    f->state = STOPPED;
	    if( (f->flags & OPT_PASSIVE) == 0 && f->callbacks->finished )
		(*f->callbacks->finished)(f);

	} else {
	    /* Retransmit the configure-request */
	    if (f->callbacks->retransmit)
		(*f->callbacks->retransmit)(f);

#ifdef SC_DT_SUPPORT
            if(f->protocol!=PPP_LCP && f->protocol!=PPP_IPCP && f->protocol!=PPP_IPV6CP)
#endif
	    fsm_sconfreq(f, 1);		/* Re-send Configure-Request */
	    if( f->state == ACKRCVD )
		f->state = REQSENT;
	}
	break;

    default:
	FSMDEBUG(("%s: Timeout event in state %d!", PROTO_NAME(f), f->state));
    }
}

#ifdef SC_DT_SUPPORT
/*
 * sc_sconfreq_retry - Timeout expired.
 */
static void
sc_sconfreq_retry(arg)
    void *arg;
{
    fsm *f = (fsm *) arg;

    switch (f->state) {
    case REQSENT:
    case ACKRCVD:
    case ACKSENT:
        if(f->sc_retry <= f->sc_maxretry && (f->protocol==PPP_LCP || f->protocol==PPP_IPCP || f->protocol==PPP_IPV6CP))
        {
            //warn("SC_DT_SUPPORT: timeout sending %d Config-Requests, do retry\n", f->protocol);
            if(f->protocol==PPP_LCP)
                syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0023, log_type_db[GENERAL_LOG], "LCP");
            else if(f->protocol==PPP_IPCP)
                syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0023, log_type_db[GENERAL_LOG], "IPCP");
            else if(f->protocol==PPP_IPV6CP)
                syslog(LOG_INFO, "%s"LOG_ERRCODE_INTDSL_R0023, log_type_db[GENERAL_LOG], "IPV6CP");

            sal_wan_set_con_error_log_code_t(wan_id, "R023");
            fsm_sconfreq(f, f->sc_transmitflag);
            if( f->state == ACKRCVD )
		f->state = REQSENT;
        }
        else
        {
            //warn("SC_DT_SUPPORT: timeout sending %d Config-Requests, do f->finished\n", f->protocol);
            f->state = STOPPED;
            if(f->protocol==PPP_IPCP || f->protocol==PPP_IPV6CP)
            {
                if(sc_get_ncp_active_state(f))
                    terminate_layer(f, CLOSING);
                else
                    f->state=CLOSED;
                if(f->state == CLOSED)
                {
                    s_cnt--;
                    if(s_cnt>0)
                    {
                        int timer=0;

                        if (f->protocol == PPP_IPCP || (ipv6_terminate_flag == 0 && f->protocol == PPP_IPV6CP)) {
                            f->sc_penalty++;
                            if(f->sc_penalty < f->sc_maxpenalty)
                                timer = 1<<(f->sc_penalty-1);
                            else 
                                timer = 600;
                        }
                        //warn("SC_DT_SUPPORT(sc_sconfreq_retry): S_CONT > 0 so %d Penalty apply and delay %d\n", f->protocol, timer);
                        if(timer > 0)
                            TIMEOUT(sc_ipcp_penalty, f, timer);
                    }
                    else
                        lcp_close(0, "ipcp or ipv6cp penalty req to session close");
                }
            }
            else
            {
                if( (f->flags & OPT_PASSIVE) == 0 && f->callbacks->finished )
                    (*f->callbacks->finished)(f);
            }
        }
        break;
    default:
	FSMDEBUG(("SC_DT_SUPPORT: Timeout event in state %d!", f->state));
    }
}

/*
 * sc_ipcp_penalty - Timeout expired.
 */
static void
sc_ipcp_penalty(arg)
    void *arg;
{
    fsm *f = (fsm *) arg;

    switch (f->state) {
    case CLOSED:
    case STOPPED:
        if(f->protocol==PPP_IPCP || f->protocol==PPP_IPV6CP)
        {
            //warn("SC_DT_SUPPORT: timeout %d Penalty, do ipcp retry\n", f->protocol);
            f->sc_retry = 0;
            fsm_open(f);
        }
        break;
    default:
	warn("SC_DT_SUPPORT(sc_ipcp_penalty): Timeout event in state %d!", f->state);
    }
}
#endif /* SC_DT_SUPPORT */

/*
 * fsm_input - Input packet.
 */
void
fsm_input(f, inpacket, l)
    fsm *f;
    u_char *inpacket;
    int l;
{
    u_char *inp;
    u_char code=0, id=0;
    int len=0;
    
    /*
     * Parse header (code, id and length).
     * If packet too short, drop it.
     */
    inp = inpacket;
    if (l < HEADERLEN) {
	FSMDEBUG(("fsm_input(%x): Rcvd short header.", f->protocol));
	return;
    }
    GETCHAR(code, inp);
    GETCHAR(id, inp);
    GETSHORT(len, inp);
    if (len < HEADERLEN) {
	FSMDEBUG(("fsm_input(%x): Rcvd illegal length.", f->protocol));
	return;
    }
    if (len > l) {
	FSMDEBUG(("fsm_input(%x): Rcvd short packet.", f->protocol));
	return;
    }
    len -= HEADERLEN;		/* subtract header length */

    if( f->state == INITIAL || f->state == STARTING ){
	FSMDEBUG(("fsm_input(%x): Rcvd packet in state %d.",
		  f->protocol, f->state));
	return;
    }

    /*
     * Action depends on code.
     */
    switch (code) {
    case CONFREQ:
	fsm_rconfreq(f, id, inp, len);
	break;
    
    case CONFACK:
	fsm_rconfack(f, id, inp, len);
	break;
    
    case CONFNAK:
    case CONFREJ:
	fsm_rconfnakrej(f, code, id, inp, len);
	break;
    
    case TERMREQ:
	fsm_rtermreq(f, id, inp, len);
	break;
    
    case TERMACK:
	fsm_rtermack(f);
	break;
    
    case CODEREJ:
	fsm_rcoderej(f, inp, len);
	break;
    
    default:
	if( !f->callbacks->extcode
	   || !(*f->callbacks->extcode)(f, code, id, inp, len) )
	    fsm_sdata(f, CODEREJ, ++f->id, inpacket, len + HEADERLEN);
	break;
    }
}


/*
 * fsm_rconfreq - Receive Configure-Request.
 */
static void
fsm_rconfreq(f, id, inp, len)
    fsm *f;
    u_char id;
    u_char *inp;
    int len;
{
    int code, reject_if_disagree;
#ifdef SC_DT_DEBUG
    mybug("rx [%s] config requset. state [%d]\n", PROTO_NAME(f), f->state);
#endif
    switch( f->state ){
    case CLOSED:
	/* Go away, we're closed */
	fsm_sdata(f, TERMACK, id, NULL, 0);
	return;
    case CLOSING:
    case STOPPING:
	return;

    case OPENED:
#ifdef SC_DT_DEBUG
        mybug("rx [%s] config requset. server request to reconfig and dut try to reestablish\n", PROTO_NAME(f));
#endif
	/* Go down and restart negotiation */
	if( f->callbacks->down )
	    (*f->callbacks->down)(f);	/* Inform upper layers */
	fsm_sconfreq(f, 0);		/* Send initial Configure-Request */
	f->state = REQSENT;
	break;

    case STOPPED:
	/* Negotiation started by our peer */
	fsm_sconfreq(f, 0);		/* Send initial Configure-Request */
	f->state = REQSENT;
	break;
    }

    /*
     * Pass the requested configuration options
     * to protocol-specific code for checking.
     */
    if (f->callbacks->reqci){		/* Check CI */
	reject_if_disagree = (f->nakloops >= f->maxnakloops);
	code = (*f->callbacks->reqci)(f, inp, &len, reject_if_disagree);
#ifdef SC_DT_DEBUG
        mybug("rx [%s] config requset. callbacks->reqci %d %d\n", PROTO_NAME(f), code, reject_if_disagree);
#endif
    } else if (len){
	code = CONFREJ;			/* Reject all CI */
#ifdef SC_DT_DEBUG
        mybug("rx [%s] config requset. feedback server for config reject\n", PROTO_NAME(f));
#endif
    }else
	code = CONFACK;

    /* send the Ack, Nak or Rej to the peer */
    fsm_sdata(f, code, id, inp, len);

    if (code == CONFACK) {
	if (f->state == ACKRCVD) {
	    UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	    f->state = OPENED;
	    if (f->callbacks->up)
		(*f->callbacks->up)(f);	/* Inform upper layers */
	} else
	    f->state = ACKSENT;
	f->nakloops = 0;

    } else {
	/* we sent CONFACK or CONFREJ */
	if (f->state != ACKRCVD)
	    f->state = REQSENT;
	if( code == CONFNAK )
	    ++f->nakloops;
    }
}


/*
 * fsm_rconfack - Receive Configure-Ack.
 */
static void
fsm_rconfack(f, id, inp, len)
    fsm *f;
    int id;
    u_char *inp;
    int len;
{
#ifdef SC_DT_DEBUG
    mybug("rx [%s] config ack.\n", PROTO_NAME(f));
#endif

    if (id != f->reqid || f->seen_ack)		/* Expected id? */
	return;					/* Nope, toss... */
    if( !(f->callbacks->ackci? (*f->callbacks->ackci)(f, inp, len):
	  (len == 0)) ){
	/* Ack is bad - ignore it */
	error("Received bad configure-ack: %P", inp, len);
	return;
    }
    f->seen_ack = 1;
    f->rnakloops = 0;

    switch (f->state) {
    case CLOSED:
    case STOPPED:
	fsm_sdata(f, TERMACK, id, NULL, 0);
	break;

    case REQSENT:
	f->state = ACKRCVD;
	f->retransmits = f->maxconfreqtransmits;
#ifdef SC_DT_SUPPORT
        if(f->protocol==PPP_LCP || f->protocol==PPP_IPCP || f->protocol==PPP_IPV6CP)
        {
            //warn("SC_DT_SUPPORT: recv %d Config-Ack and cleanup timer\n", f->protocol);
            f->sc_retry = 0;		/* retry count clean up */
            UNTIMEOUT(sc_sconfreq_retry, f);
            if(f->protocol==PPP_IPCP || f->protocol==PPP_IPV6CP)
                UNTIMEOUT(sc_ipcp_penalty, f);
        }
#endif
        break;

    case ACKRCVD:
	/* Huh? an extra valid Ack? oh well... */
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	fsm_sconfreq(f, 0);
	f->state = REQSENT;
	break;

    case ACKSENT:
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	f->state = OPENED;
	f->retransmits = f->maxconfreqtransmits;
	if (f->callbacks->up)
	    (*f->callbacks->up)(f);	/* Inform upper layers */
	break;

    case OPENED:
	/* Go down and restart negotiation */
	if (f->callbacks->down)
	    (*f->callbacks->down)(f);	/* Inform upper layers */
	fsm_sconfreq(f, 0);		/* Send initial Configure-Request */
	f->state = REQSENT;
	break;
    }
}


/*
 * fsm_rconfnakrej - Receive Configure-Nak or Configure-Reject.
 */
static void
fsm_rconfnakrej(f, code, id, inp, len)
    fsm *f;
    int code, id;
    u_char *inp;
    int len;
{
    int ret;
    int treat_as_reject;
#ifdef SC_DT_DEBUG
    mybug("rx [%s] config nak/reject.\n", PROTO_NAME(f));
#endif
    if (id != f->reqid || f->seen_ack)	/* Expected id? */
	return;				/* Nope, toss... */

    if (code == CONFNAK) {
	++f->rnakloops;
	treat_as_reject = (f->rnakloops >= f->maxnakloops);
	if (f->callbacks->nakci == NULL
	    || !(ret = f->callbacks->nakci(f, inp, len, treat_as_reject))) {
	    error("Received bad configure-nak: %P", inp, len);
	    return;
	}
    } else {
	f->rnakloops = 0;
	if (f->callbacks->rejci == NULL
	    || !(ret = f->callbacks->rejci(f, inp, len))) {
	    error("Received bad configure-rej: %P", inp, len);
	    return;
	}
    }

    f->seen_ack = 1;

    switch (f->state) {
    case CLOSED:
    case STOPPED:
	fsm_sdata(f, TERMACK, id, NULL, 0);
	break;

    case REQSENT:
    case ACKSENT:
	/* They didn't agree to what we wanted - try another request */
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
#ifdef SC_DT_SUPPORT
        if(f->protocol==PPP_LCP || f->protocol==PPP_IPCP || f->protocol==PPP_IPV6CP)
        {
            //warn("SC_DT_SUPPORT: recv %d Config-Nak and do retry\n", f->protocol);
            if (ret < 0)    //special reason to jump out retry flow
            {
                f->state = STOPPED;		        /* kludge for stopping CCP */
                f->sc_retry = 0;                       /* reset ipcp retry and waiting re sconfreq */
                UNTIMEOUT(sc_sconfreq_retry, f);	/* Cancel timeout */
            }
            else
            {
                if(f->sc_retry > f->sc_maxretry)
                {
                    f->state = STOPPED;
                    UNTIMEOUT(sc_sconfreq_retry, f);
                    if(f->protocol==PPP_IPCP || f->protocol==PPP_IPV6CP)
                    {
                        if(sc_get_ncp_active_state(f))
                            terminate_layer(f, CLOSING);
                        else
                            f->state=CLOSED;
                        if(f->state == CLOSED)
                        {
                            s_cnt--;
                            if(s_cnt>0)
                            {
                                int timer=0;

                                if (f->protocol == PPP_IPCP || (ipv6_terminate_flag == 0 && f->protocol == PPP_IPV6CP)) {
                                    f->sc_penalty++;
                                    if(f->sc_penalty < f->sc_maxpenalty)
                                        timer = 1<<(f->sc_penalty-1);
                                    else 
                                        timer = 600;
                                }
                                //warn("SC_DT_SUPPORT(fsm_rconfnakrej): S_CONT > 0 so %d Penalty apply and delay %d\n", f->protocol, timer);
                                if(timer > 0)
                                    TIMEOUT(sc_ipcp_penalty, f, timer);
                            }
                            else
                                lcp_close(0, "ipcp or ipv6cp penalty req to session close");
                        }
                    }
                }
                else
                {
                    f->sc_transmitflag = 0;
                    //warn("SC_DT_SUPPORT: *************************%d wait*************************\n", f->protocol);
                }
            }
        }
        else
        {
            if (ret < 0)
                f->state = STOPPED;		/* kludge for stopping CCP */
            else
                fsm_sconfreq(f, 0);		/* Send Configure-Request */
        }
#else
        if (ret < 0)
	    f->state = STOPPED;		/* kludge for stopping CCP */
	else
	    fsm_sconfreq(f, 0);		/* Send Configure-Request */
#endif
        break;

    case ACKRCVD:
	/* Got a Nak/reject when we had already had an Ack?? oh well... */
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	fsm_sconfreq(f, 0);
	f->state = REQSENT;
	break;

    case OPENED:
	/* Go down and restart negotiation */
	if (f->callbacks->down)
	    (*f->callbacks->down)(f);	/* Inform upper layers */
	fsm_sconfreq(f, 0);		/* Send initial Configure-Request */
	f->state = REQSENT;
	break;
    }
}


/*
 * fsm_rtermreq - Receive Terminate-Req.
 */
static void
fsm_rtermreq(f, id, p, len)
    fsm *f;
    int id;
    u_char *p;
    int len;
{
#ifdef SC_DT_DEBUG
    mybug("rx [%s] terminate request.\n", PROTO_NAME(f));
#endif
    switch (f->state) {
    case ACKRCVD:
    case ACKSENT:
	f->state = REQSENT;		/* Start over but keep trying */
	break;

    case OPENED:
	if (len > 0) {
	    info("%s terminated by peer (%0.*v)", PROTO_NAME(f), len, p);
	} else
	    info("%s terminated by peer", PROTO_NAME(f));
#ifdef SC_DT_SUPPORT
        if(f->protocol==PPP_IPCP)
        {
            char tmp[8];
            ip_version_type &= ~IP_VER_TYPE_V4;
            sprintf(tmp, "%d", ip_version_type);
            sal_wan_set_con_ip_ver_type_t(1, tmp);       
	    f->state = CLOSING;
        }
        else if(f->protocol==PPP_IPV6CP)
        {
            char tmp[8];
            ip_version_type &= ~IP_VER_TYPE_V6;
            sprintf(tmp, "%d", ip_version_type);
            sal_wan_set_con_ip_ver_type_t(1, tmp);   
            sal_wan_set_con_ipv6_pri_mode_t(1, "0");
	    f->state = CLOSING;
        }
        else
	    f->state = STOPPING;
#endif
	f->retransmits = 0;
#ifndef SC_DT_SUPPORT
	f->state = STOPPING;
#endif
	if (f->callbacks->down)
	    (*f->callbacks->down)(f);	/* Inform upper layers */
	TIMEOUT(fsm_timeout, f, f->timeouttime);
	break;
    }
    fsm_sdata(f, TERMACK, id, NULL, 0);
}


/*
 * fsm_rtermack - Receive Terminate-Ack.
 */
static void
fsm_rtermack(f)
    fsm *f;
{
#ifdef SC_DT_DEBUG
    mybug("rx [%s] terminate ack.\n", PROTO_NAME(f));
#endif
    switch (f->state) {
    case CLOSING:
	UNTIMEOUT(fsm_timeout, f);
	f->state = CLOSED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
#ifdef SC_DT_SUPPORT
        if(f->protocol==PPP_IPCP || f->protocol==PPP_IPV6CP)
        {
            if(f->protocol==PPP_IPCP && ipv4_idle_flag==1)
            {
                //warn("SC_DT_SUPPORT(fsm_rtermack): ipcp terminate ack recv and ipv4_idle_flag==1");
                ipv4_idle_flag = 2;
            }

            if(f->protocol==PPP_IPCP && ipv4_idle_flag==2)
            {
                ;
            }
            else
            {
                UNTIMEOUT(sc_sconfreq_retry, f);
                s_cnt--;
                if(s_cnt>0)
                {
                    int timer=0;

                    if (f->protocol == PPP_IPCP || (ipv6_terminate_flag == 0 && f->protocol == PPP_IPV6CP)) {
                        f->sc_penalty++;
                        if(f->sc_penalty < f->sc_maxpenalty)
                            timer = 1<<(f->sc_penalty-1);
                        else 
                            timer = 600;
                    }
                    //warn("SC_DT_SUPPORT(fsm_rtermack): S_CONT > 0 so %d Penalty apply and delay %d\n", f->protocol, timer);
                    if(timer > 0)
                        TIMEOUT(sc_ipcp_penalty, f, timer);
                }
                else
                    lcp_close(0, "ipcp or ipv6cp penalty req to session close");

            }
        }
#endif
	break;
    case STOPPING:
	UNTIMEOUT(fsm_timeout, f);
	f->state = STOPPED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	break;

    case ACKRCVD:
	f->state = REQSENT;
	break;

    case OPENED:
	if (f->callbacks->down)
	    (*f->callbacks->down)(f);	/* Inform upper layers */
	fsm_sconfreq(f, 0);
	f->state = REQSENT;
	break;
    }
}


/*
 * fsm_rcoderej - Receive an Code-Reject.
 */
static void
fsm_rcoderej(f, inp, len)
    fsm *f;
    u_char *inp;
    int len;
{
    u_char code, id;
#ifdef SC_DT_DEBUG
    mybug("rx [%s] code reject.\n", PROTO_NAME(f));
#endif
    if (len < HEADERLEN) {
	FSMDEBUG(("fsm_rcoderej: Rcvd short Code-Reject packet!"));
	return;
    }
    GETCHAR(code, inp);
    GETCHAR(id, inp);
    warn("%s: Rcvd Code-Reject for code %d, id %d", PROTO_NAME(f), code, id);

    if( f->state == ACKRCVD )
	f->state = REQSENT;
}


/*
 * fsm_protreject - Peer doesn't speak this protocol.
 *
 * Treat this as a catastrophic error (RXJ-).
 */
void
fsm_protreject(f)
    fsm *f;
{
#ifdef SC_DT_DEBUG
    mybug("rx [%s] protocol reject.\n", PROTO_NAME(f));
#endif
    switch( f->state ){
    case CLOSING:
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	/* fall through */
    case CLOSED:
	f->state = CLOSED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	break;

    case STOPPING:
    case REQSENT:
    case ACKRCVD:
    case ACKSENT:
	UNTIMEOUT(fsm_timeout, f);	/* Cancel timeout */
	/* fall through */
    case STOPPED:
	f->state = STOPPED;
	if( f->callbacks->finished )
	    (*f->callbacks->finished)(f);
	break;

    case OPENED:
	terminate_layer(f, STOPPING);
	break;

    default:
	FSMDEBUG(("%s: Protocol-reject event in state %d!",
		  PROTO_NAME(f), f->state));
    }
}


/*
 * fsm_sconfreq - Send a Configure-Request.
 */
static void
fsm_sconfreq(f, retransmit)
    fsm *f;
    int retransmit;
{
    u_char *outp;
    int cilen;

    if( f->state != REQSENT && f->state != ACKRCVD && f->state != ACKSENT ){
	/* Not currently negotiating - reset options */
	if( f->callbacks->resetci )
	    (*f->callbacks->resetci)(f);
	f->nakloops = 0;
	f->rnakloops = 0;
    }

    if( !retransmit ){
	/* New request - reset retransmission counter, use new ID */
	f->retransmits = f->maxconfreqtransmits;
	f->reqid = ++f->id;
    }

    f->seen_ack = 0;

    /*
     * Make up the request packet
     */
    outp = outpacket_buf + PPP_HDRLEN + HEADERLEN;
    if( f->callbacks->cilen && f->callbacks->addci ){
	cilen = (*f->callbacks->cilen)(f);
	if( cilen > peer_mru[f->unit] - HEADERLEN )
	    cilen = peer_mru[f->unit] - HEADERLEN;
	if (f->callbacks->addci)
	    (*f->callbacks->addci)(f, outp, &cilen);
    } else
	cilen = 0;

    /* send the request to our peer */
    fsm_sdata(f, CONFREQ, f->reqid, outp, cilen);

    /* start the retransmit timer */
    --f->retransmits;
#ifdef SC_DT_SUPPORT
    /* reset lcp/ipcp/ipv6cp retransmit flag */
    f->sc_transmitflag = 1;

    if(f->protocol==PPP_LCP || f->protocol==PPP_IPCP || f->protocol==PPP_IPV6CP)
    {
        unsigned int timer=0;
        if(f->sc_retry<2)
            timer = 0;
        else
            timer = f->sc_retry-1;
        TIMEOUT(sc_sconfreq_retry, f, 1<<timer);
        f->sc_retry++;
        //warn("SC_DT_SUPPORT: %d CONF REQ sent %d times", f->protocol, f->sc_retry);
#ifdef SC_DT_DEBUG
        mybug("tx [%s] config request [id=%02x,cnt=%d].\n", PROTO_NAME(f), f->reqid, f->sc_retry);
#endif
    }
    else
        TIMEOUT(fsm_timeout, f, f->timeouttime);
#else
    TIMEOUT(fsm_timeout, f, f->timeouttime);
#endif
}


/*
 * fsm_sdata - Send some data.
 *
 * Used for all packets sent to our peer by this module.
 */
void
fsm_sdata(f, code, id, data, datalen)
    fsm *f;
    u_char code, id;
    u_char *data;
    int datalen;
{
    u_char *outp;
    int outlen;
#ifdef SC_DT_DEBUG
    if(code == CONFREQ)
        mybug("tx [%s] config request.\n", PROTO_NAME(f));
    else if(code == TERMREQ)
        mybug("tx [%s] terminate request.\n", PROTO_NAME(f));
    else if(code == TERMACK)
        mybug("tx [%s] terminate ack.\n", PROTO_NAME(f));
    else if(code == CONFACK)
        mybug("tx [%s] config ack.\n", PROTO_NAME(f));
    else
    {
        if(f->protocol==PPP_LCP && (code == 9 || code == 10))//do not print lcp-echo-req and lcp-echo-rsp
            ;
        else
            mybug("tx [%s] %d.\n", PROTO_NAME(f), code);
    }
#endif
    /* Adjust length to be smaller than MTU */
    outp = outpacket_buf;
    if (datalen > peer_mru[f->unit] - HEADERLEN)
	datalen = peer_mru[f->unit] - HEADERLEN;
    if (datalen && data != outp + PPP_HDRLEN + HEADERLEN)
	BCOPY(data, outp + PPP_HDRLEN + HEADERLEN, datalen);
    outlen = datalen + HEADERLEN;
    MAKEHEADER(outp, f->protocol);
    PUTCHAR(code, outp);
    PUTCHAR(id, outp);
    PUTSHORT(outlen, outp);
    output(f->unit, outpacket_buf, outlen + PPP_HDRLEN);
}
