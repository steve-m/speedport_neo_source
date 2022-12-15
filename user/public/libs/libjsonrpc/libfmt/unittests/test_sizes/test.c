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
	int size = 0;
	fmt_t p, array;
	fmt_tok_t array_tok;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) != 0 ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	fprintf( fp, "Testing array size (parsed,object): " );
	A( fmt_get( &p, NULL, "array", &array ) );
	A( size = fmt_array_size( &array, NULL ) );
	if ( size == 4 )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );

	size = 0;

	fprintf( fp, "Testing array size (parsed,token): " );
	A( fmt_get_tok( &p, NULL, "array", &array_tok ) );
	A( size = fmt_array_size( &p, &array_tok ) );
	if ( size == 4 )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );

exit:
	A( fmt_free( &p ) );
	A( fmt_free( &array ) );
	fclose( fp );
}

int main( int argc, char *argv[] )
{
	test();
	return 0;
}
