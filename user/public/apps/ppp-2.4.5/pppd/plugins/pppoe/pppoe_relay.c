/* PPPoE support library "libpppoe"
 *
 * Copyright 2000 Michal Ostrowski <mostrows@styx.uwaterloo.ca>,
 *		  Jamal Hadi Salim <hadi@cyberus.ca>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version
 *  2 of the License, or (at your option) any later version.
 */

#include "pppoe.h"

static unsigned int pcid=0;

static int relay_init_disc(struct session* ses,
			   struct pppoe_packet *p_in,
			   struct pppoe_packet **p_out){

    ses->state = 0;
    ses->retransmits = -1 ;
    ses->retries = -1;

    (*p_out) = NULL;
    return 0;
}


static int relay_rcv_padi(struct session* ses,
			  struct pppoe_packet *p_in,
			  struct pppoe_packet **p_out){
    char tag_buf[32];
    struct pppoe_con *newpc = NULL;
    struct pppoe_tag *tag = (struct pppoe_tag *) tag_buf;


    
    /* only receive PADI from lan interface */
    if(p_in->addr.sll_ifindex != ses->local.sll_ifindex)
    {
    	return -1;
   	}
    tag->tag_type = PTT_RELAY_SID;
    tag->tag_len  = htons(ETH_ALEN + sizeof(pcid));

    memcpy(tag->tag_data, p_in->addr.sll_addr, ETH_ALEN);
    memcpy(tag->tag_data + ETH_ALEN, &pcid, sizeof(pcid));
    ++pcid;

    if(! p_in->tags[TAG_RELAY_SID] ){
	copy_tag(p_in, tag);
    }


    poe_dbglog(ses, "Recv'd PADI: %P",p_in);
    poe_dbglog(ses, "Recv'd packet: %P",p_in);
    newpc = get_con( ntohs(tag->tag_len), tag->tag_data );
    if(!newpc){
	
	newpc = (struct pppoe_con *) malloc(sizeof(struct pppoe_con));
	memset(newpc , 0, sizeof(struct pppoe_con));
	
	//newpc->id = pcid++;
	
	newpc->key_len = ntohs(p_in->tags[TAG_RELAY_SID]->tag_len);
	memcpy(newpc->key, p_in->tags[TAG_RELAY_SID]->tag_data, newpc->key_len);
	memcpy(newpc->client, p_in->addr.sll_addr, ETH_ALEN);
	
	memcpy(newpc->server, MAC_BCAST_ADDR, ETH_ALEN);
	
	store_con(newpc);
	
    }

    ++newpc->ref_count;

    memset(p_in->addr.sll_addr, 0xff, ETH_ALEN);

    p_in->addr.sll_ifindex = ses->remote.sll_ifindex;

    send_disc(ses, p_in);
    return 0;
}

static int relay_rcv_pkt(struct session* ses,
			 struct pppoe_packet *p_in,
			 struct pppoe_packet **p_out){
    struct pppoe_con *pc;
    struct pppoe_tag *tag = p_in->tags[TAG_RELAY_SID];

     /* Only receive PADO from wan interface */
    if(p_in->hdr->code== PADO_CODE && p_in->addr.sll_ifindex == ses->local.sll_ifindex)
    {
    	return 0;
   	}
   
    /* Only receive PADR from lan interface */
    if(p_in->hdr->code== PADR_CODE && p_in->addr.sll_ifindex != ses->local.sll_ifindex)
    {
    	return 0;
   	}
    
    /* Only receive PADS from wan interface */
    if(p_in->hdr->code== PADS_CODE && p_in->addr.sll_ifindex == ses->local.sll_ifindex)
    {
    	return 0;
   	}

    if( tag )
        pc = get_con(ntohs(tag->tag_len),tag->tag_data);
    else if (p_in->hdr->sid)
        pc = get_con2(p_in->addr.sll_addr, ntohs(p_in->hdr->sid));
    else
        return 0;

    if( !pc ) return 0;

    poe_dbglog(ses, "Recv'd packet: %P",p_in);

    if( memcmp(pc->client , p_in->addr.sll_addr , ETH_ALEN ) == 0 ){
	
	memcpy(p_in->addr.sll_addr, pc->server, ETH_ALEN);
	p_in->addr.sll_ifindex = ses->remote.sll_ifindex;
	
    }else{
	if( memcmp(pc->server, MAC_BCAST_ADDR, ETH_ALEN) == 0 ){
	    memcpy(pc->server, p_in->addr.sll_addr, ETH_ALEN);
	
	}else if( memcmp(pc->server, p_in->addr.sll_addr, ETH_ALEN) !=0){
	    return 0;
	}
	
	memcpy(p_in->addr.sll_addr, pc->client, ETH_ALEN);
	p_in->addr.sll_ifindex = ses->local.sll_ifindex;
	
	
    }


    send_disc(ses, p_in);
    return 0;
}

static int relay_rcv_pads(struct session* ses,
			  struct pppoe_packet *p_in,
			  struct pppoe_packet **p_out){

    struct pppoe_con *pc;
    struct pppoe_tag *tag = p_in->tags[TAG_RELAY_SID];
    struct sockaddr_pppox sp_cl= { AF_PPPOX, PX_PROTO_OE,
				   { {p_in->hdr->sid, {0,},{0,}}}};

    struct sockaddr_pppox sp_sv= { AF_PPPOX, PX_PROTO_OE,
				   { {p_in->hdr->sid, {0,},{0,}}}};

    int ret;


    if( !tag ) return 0;

    pc = get_con(ntohs(tag->tag_len),tag->tag_data);

    if( !pc ) return 0;

    if(!pc->connected){
	
	pc->sv_sock = socket( AF_PPPOX, SOCK_DGRAM, PX_PROTO_OE);
	if( pc->sv_sock < 0){
	    poe_fatal(ses,"Cannot open PPPoE socket: %i",errno);
	}
	
	pc->cl_sock = socket( AF_PPPOX, SOCK_DGRAM, PX_PROTO_OE);
	if( pc->cl_sock < 0){
	    poe_fatal(ses,"Cannot open PPPoE socket: %i",errno);
	}
	
	memcpy( sp_sv.sa_addr.pppoe.dev, ses->fwd_name, IFNAMSIZ);
	memcpy( sp_sv.sa_addr.pppoe.remote, pc->server, ETH_ALEN);
	
	ret = connect( pc->sv_sock,
		       (struct sockaddr*)&sp_sv,
		       sizeof(struct sockaddr_pppox));
	if( ret < 0){
	    poe_fatal(ses,"Cannot connect PPPoE socket: %i",errno);
	}
	
	memcpy( sp_cl.sa_addr.pppoe.dev, ses->name, IFNAMSIZ);
	memcpy( sp_cl.sa_addr.pppoe.remote, pc->client, ETH_ALEN);
	
	ret = connect( pc->cl_sock,
		       (struct sockaddr*)&sp_cl,
		       sizeof(struct sockaddr_pppox));
	if( ret < 0){
	    poe_fatal(ses,"Cannot connect PPPoE socket: %i",errno);
	}
	
	
	ret = ioctl( pc->sv_sock, PPPOEIOCSFWD, &sp_cl);
	if( ret < 0){
	    poe_fatal(ses,"Cannot set forwarding on PPPoE socket: %i",errno);
	}
	
	ret = ioctl( pc->cl_sock, PPPOEIOCSFWD, &sp_sv);
	if( ret < 0){
	    poe_fatal(ses,"Cannot set forwarding on PPPoE socket: %i",errno);
	}
	
	pc->connected = 1;
    pc->id = ntohs(p_in->hdr->sid);
    }

    poe_info(ses,"PPPoE relay for %E established to %E (sid=%04x)\n",
	     pc->client,pc->server, p_in->hdr->sid);

    return relay_rcv_pkt(ses,p_in,p_out);
}


static int relay_rcv_padt(struct session* ses,
			  struct pppoe_packet *p_in,
			  struct pppoe_packet **p_out){

    int ret;
    struct pppoe_con *pc;
    struct pppoe_tag *tag = p_in->tags[TAG_RELAY_SID];
#if 0
    char tag_buf[32];
    //struct pppoe_tag *tag = p_in->tags[TAG_RELAY_SID];
    struct pppoe_tag *tag=(struct pppoe_tag *)tag_buf;
    tag->tag_type = PTT_RELAY_SID;
    tag->tag_len  = htons(ETH_ALEN + sizeof(struct session *));
    memcpy(tag->tag_data, p_in->addr.sll_addr, ETH_ALEN);
    memcpy(tag->tag_data + ETH_ALEN, &ses, sizeof(struct session *));
#endif

    if( tag )
        pc = get_con(ntohs(tag->tag_len),tag->tag_data);
    else
        pc = get_con2(p_in->addr.sll_addr, ntohs(p_in->hdr->sid));

    if( !pc ) return 0;

    ret = relay_rcv_pkt(ses,p_in,p_out);


    if(pc->cl_sock>0){
	close(pc->cl_sock);
    pc->cl_sock = -1;
    }

    if(pc->sv_sock>0){
	close(pc->sv_sock);
    pc->sv_sock = -1;
    }

    --pc->ref_count;
    if( pc->ref_count == 0 ){
	delete_con(pc->key_len, pc->key);
	
	free(pc);
    }
    return 0;
}

extern int disc_sock;

int relay_init_ses(struct session *ses, char* from, char* to)
{
    int retval = client_init_ses_relay(ses, from);

    if(retval<0) return retval;

    srand(time(0));
    pcid = rand();

    ses->fwd_sock=-1;
#if 0    
    ses->fwd_sock =  socket(PF_PACKET, SOCK_DGRAM, 0);
    if( ses->fwd_sock < 0 ) {
	poe_fatal(ses,"Cannot create PF_PACKET socket for PPPoE forwarding\n");
    }
#endif    

    /* Verify the device name , construct ses->local */
    retval = get_sockaddr_ll(to, &ses->remote);
    if (retval < 0)
	poe_fatal(ses,"relay_init_ses:get_sockaddr_ll failed %m");

#if 0
    retval = bind( ses->fwd_sock ,
		   (struct sockaddr*)&ses->remote,
		   sizeof(struct sockaddr_ll));

    if( retval < 0 ){
	poe_fatal(ses,"bind to PF_PACKET socket failed: %m");
    }
#endif

    memcpy(ses->fwd_name, to, IFNAMSIZ);
    memcpy(ses->name, from, IFNAMSIZ);


    ses->init_disc = relay_init_disc;
    ses->rcv_padi  = relay_rcv_padi;
    ses->rcv_pado  = relay_rcv_pkt;
    ses->rcv_padr  = relay_rcv_pkt;
    ses->rcv_pads  = relay_rcv_pads;
    ses->rcv_padt  = relay_rcv_padt;
    return 0;
}


