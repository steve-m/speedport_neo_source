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
	const char *path_default[] = { "default", "sensors", NULL };
	const char *path_default1[] = { "default", "sensors1", NULL };
	const char *path_other[] = { "other", "sensors", NULL };
	fmt_t p;
	fmt_tok_t group;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Input:\n%s\n", tmp );
	free( tmp );

	fprintf( fp, "Trying to delete 'sensors' from 'other': " );
	A( fmt_get_tok( &p, NULL, "group", &group ) );
	A( fmt_del_path( &p, &group, path_other ) );
	fprintf( fp, "OK\n" );
	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Result:\n%s\n", tmp );
	free( tmp );

	fprintf( fp, "Trying to delete 'sensors' from 'default': " );
	A( fmt_del_path( &p, &group, path_default ) );
	fprintf( fp, "OK\n" );
	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Result:\n%s\n", tmp );
	free( tmp );

	fprintf( fp, "Trying to delete 'sensors1' from 'default': " );
	A( fmt_del_path( &p, &group, path_default1 ) );
	fprintf( fp, "OK\n" );
	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Result:\n%s\n", tmp );
	free( tmp );
exit:
	A( fmt_free( &p ) );
	fclose( fp );
}

int main( int argc, char *argv[] )
{
	test();
	return 0;
}
