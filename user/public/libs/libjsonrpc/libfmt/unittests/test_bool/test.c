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
	fmt_tok_t true, false, not_true;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) != 0 ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	fprintf( fp, "Testing true (parsed): " );
	A( fmt_get_tok( &p, NULL, "testme_true", &true ) );
	if ( fmt_is_bool( &p, &true, LIBFMT_TRUE ) )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );

	fprintf( fp, "Testing true (parsed,path): " );
	const char *path[] = { "testme_true", NULL };
	A( fmt_get_tok_path( &p, NULL, path, &true ) );
	if ( fmt_is_bool( &p, &true, LIBFMT_TRUE ) )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );

	fprintf( fp, "Testing false (parsed): " );
	A( fmt_get_tok( &p, NULL, "testme_false", &false ) );
	if ( fmt_is_bool( &p, &false, LIBFMT_FALSE ) )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );

	fprintf( fp, "Testing not true (parsed): " );
	A( fmt_get_tok( &p, NULL, "not_true", &not_true ) );
	if ( !fmt_is_bool( &p, &not_true, LIBFMT_TRUE ) )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );

	fprintf( fp, "Testing true (new): " );
	fmt_t *new_true = fmt_bool(LIBFMT_TRUE);
	if ( fmt_is_bool( new_true, NULL, LIBFMT_TRUE ) )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );
	A( fmt_free( new_true ) );

	fprintf( fp, "Testing not true (new): " );
	fmt_t *new_not_true = fmt_string("true");
	if ( !fmt_is_bool( new_not_true, NULL, LIBFMT_TRUE ) )
		fprintf( fp, "OK\n" );
	else
		fprintf( fp, "FAIL\n" );
	A( fmt_free( new_not_true ) );

exit:
	A( fmt_free( &p ) );
	fclose( fp );

	return 0;
}
