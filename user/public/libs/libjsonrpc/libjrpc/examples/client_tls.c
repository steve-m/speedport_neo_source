#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* if you want to define some other proto for communications, e.g. SCTP */
#include <netinet/in.h>

#include <libjrpc.h>

int main( int argc, char **argv )
{
	int err = 0;
	fmt_t res = FMT_NULL;
	fmt_t tmp = FMT_NULL;
	fmt_t *params = NULL;
	char *reply = NULL;

	if ( argc < 4 ) {
		printf("Usage: %s <method> <params> <hostip> <psk>\n", argv[0] );
		exit(EXIT_FAILURE);
	}

    if ( !fmt_load_string( argv[2], strlen(argv[2]), &tmp ) )
        params = &tmp;
    else
        params = fmt_string(argv[2]);

	jrpc_req_t rpc_req = JRPC_CLIENT_DEFAULT;
	rpc_req.conn.proto = IPPROTO_TCP;
	rpc_req.conn.host  = argv[3];
	rpc_req.conn.port  = 47238;
	rpc_req.method     = argv[1];
	rpc_req.params     = params;
	rpc_req.res        = &res;

    if(argc > 4)
    {
        rpc_req.conn.flags |= JRPC_FLAG_TLS;
        rpc_req.conn.psk  = argv[4];
    }

	err = jrpc_request( &rpc_req );
	if ( err < 0 ) {
		printf( "jrpc_request() error: %i (%m)\n", err );
		exit(EXIT_FAILURE);
	}

	if ( err == JRPC_ERR_USER )
		printf( "Received some error!\n" );
	else
		printf( "Received some result!\n" );

	if ( fmt_dump_string( &res, NULL, &reply ) ) {
		printf( "fmt_dump_string() error: %i (%m)\n", err );
		exit(EXIT_FAILURE);
	}

	printf( "%s\n", reply );

	free( reply );
	fmt_free( &res );
	fmt_free( &tmp );

	exit(EXIT_SUCCESS);
}
