/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libfmt.h>

#define TEST_FILE	"test.json"
#define RESULT_FILE	"result"
#define A(x)		assert((x) >= 0)

void test()
{
	int err = 0;
	fmt_t p, *g1 = NULL, *g2 = NULL;
	fmt_checksum_t cs = FMT_ZEROCS;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) != 0 ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	g1 = fmt_object_alloc();
	A( fmt_set_new( g1, "a", fmt_string("b") ) );

	g2 = fmt_object_alloc();
	A( fmt_set_new( g2, "a", fmt_string("c") ) );

	fprintf( fp, "Testing good checksum: " );
	/* calculate checksum */
	A( fmt_checksum( &p, &cs ) );
	/* verify checksum with the one saved earlier */
	A( fmt_checksum( &p, &cs ) );
	/* verify checksum of generated object */
	A( fmt_checksum( g1, &cs ) );

	fprintf( fp, "0x%08jx ", cs.siphash );

	fprintf( fp, "OK\n" );

	fprintf( fp, "Testing bad checksum: " );
	err = fmt_checksum( g2, &cs );
	if ( err )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );

exit:
	A( fmt_free( g1 ) );
	A( fmt_free( g2 ) );
	A( fmt_free( &p ) );
	fclose( fp );
}

int main( int argc, char *argv[] )
{
	test();
	return 0;
}
