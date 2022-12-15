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
	fmt_t p;
	fmt_t copy, *copy2;
	char *s = NULL;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) != 0 ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	A( fmt_dump_string( &p, NULL, &s ) );
	fprintf( fp, "%s\n", s );
	free( s );

	A( fmt_copy( &p, &copy ) );
	A( fmt_dump_string( &copy, NULL, &s ) );
	fprintf( fp, "%s\n", s );
	free( s );

	copy2 = fmt_copy_dup( &copy, NULL );
	A( fmt_dump_string( copy2, NULL, &s ) );
	fprintf( fp, "%s\n", s );
	free( s );

	A( fmt_free( &copy ) );
	A( fmt_free( copy2 ) );

exit:
	A( fmt_free( &p ) );
	fclose( fp );
}

int main( int argc, char *argv[] )
{
	test();
	exit(0);
}
