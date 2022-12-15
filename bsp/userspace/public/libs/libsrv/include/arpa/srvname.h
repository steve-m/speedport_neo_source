/* $Id: srvname.h,v 1.2 2002/09/13 11:07:38 vanrein Exp $
 *
 * arpa/srvname.h --- Definitions involving SRV RR in DNS.
 *
 * A simple library to quickly allocate a socket on either side of a network
 * connection.  Much simpler than classical sockets, and much better too.
 * Tries IN SRV records first, continues to IN A if none defined.
 *
 * By default, it even forks a new server process for every server connection!
 * This can be overridden, and manual accept() and handling can then be done.
 * Do not expect too much -- for a more advanced solution, consider RULI,
 *	http://ruli.sourceforge.net
 *
 * From: Rick van Rein <admin@FingerHosting.com>
 */


#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>

#ifndef _ARPA_SRVNAME_H_
#define _ARPA_SRVNAME_H_

#include <sys/types.h>


/* EXAMPLE USE:
 *
 *	In your DNS config, setup SRV records for a service, say:
 *		_hello._tcp.vanrein.org IN SRV 1234 0 0 bakkerij.orvelte.nep.
 *	Meaning:
 *	 - The hello protocol runs over tcp
 *	 - The server is on port 1234 of host bakkerij.orvelte.nep
 *	 - The zeroes are for load balancing
 *
 *	A hello client starting for this domain looks up the above record and
 *	returns a socket of a network client when invoked as follows:
 *		insrv_client ("finger", "tcp", "vanrein.org");
 *
 *	A hello server started on the server host looks up the same record
 *	and starts service for hello over TCP when it finds one of its names
 *	in the record; a client-connected socket is returned from:
 *		insrv_server ("finger", "tcp", "vanrein.org");
 *	Unless told otherwise, this routine forks off for every connection
 *	to the server.  So, the server can process the request on the
 *	returned socket, close it and exit.
 *
 *	When both calls have completed, they are connected and can start
 *	running the Jabber protocol over their respective sockets.
 */


#define SRV_NO_ACCEPT	0x0001L
#define SRV_NO_INA		0x0002L
#define SRV_FLAGS_MASK	0x000fL
#define SRV_GOT_MASK	0x00f0L
#define SRV_GOT_SRV		0x0010L
#define SRV_GOT_A		0x0020L


/* Setup the SRV options when initialising -- invocation optional */
void insrv_init (unsigned long flags);

/* Test the given SRV options to see if all are set */
int srv_testflag (unsigned long flags);


/* The global variable holding the number of pending connections on a server
 * socket; defaults to a reasonable number.
 */
extern int _listen_nr;


/* Setup a client socket for the named service over the given protocol under
 * the given domain name.
 */
int insrv_client (char *service, char *proto, char *domain, char *cnxhost, size_t cnxhlen, int *cnxport);


/* Setup a server socket for the named service over the given protocol under
 * the given domain name.
 */
int insrv_server (char *service, char *proto, char *domain, char *cnxhost, size_t cnxhlen, int *cnxport);


#endif // _ARPA_SRVNAME_H
