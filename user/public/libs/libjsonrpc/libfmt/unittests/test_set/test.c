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
	char *tmp = NULL;
	const char *path[] = { "group", "other", NULL };
	fmt_t p = FMT_NULL;
	fmt_tok_t other = FMT_TOK_NULL;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Input:\n%s\n", tmp );
	free( tmp );

	fprintf( fp, "Get token via path: " );
	A( fmt_get_tok_path( &p, NULL, path, &other ) );
	fprintf( fp, "OK\n" );

	fprintf( fp, "Trying to insert into 'other': " );
	A( fmt_set_new_at( &p, &other, "string", fmt_string("asdf") ) );
	fprintf( fp, "OK\n" );
	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Result:\n%s\n", tmp );
	free( tmp );

exit:
	A( fmt_free( &p ) );
	fclose( fp );
}

int main ( int argc, char **argv )
{
	test();
	return 0;
}
