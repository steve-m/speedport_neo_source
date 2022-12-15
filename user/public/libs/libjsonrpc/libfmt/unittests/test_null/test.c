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

int main( int argc, char *argv[] )
{
	fmt_t p;
	fmt_tok_t null, not_null;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) != 0 ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	fprintf( fp, "Testing null (parsed): " );
	A( fmt_get_tok( &p, NULL, "testme", &null ) );
	if ( fmt_is_null( &p, &null ) )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );

	fprintf( fp, "Testing not null (parsed): " );
	A( fmt_get_tok( &p, NULL, "not_null", &not_null ) );
	if ( !fmt_is_null( &p, &not_null ) )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );

	fprintf( fp, "Testing null (new): " );
	fmt_t *new_null = fmt_null();
	if ( fmt_is_null( new_null, NULL ) )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );
	A( fmt_free( new_null ) );

	fprintf( fp, "Testing not null (new): " );
	fmt_t *new_not_null = fmt_string("null");
	if ( !fmt_is_null( new_not_null, NULL ) )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );
	A( fmt_free( new_not_null ) );

exit:
	A( fmt_free( &p ) );
	fclose( fp );

	return 0;
}
