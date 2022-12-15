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

void print_token( fmt_tok_t *tok )
{
	if ( !tok )
		return;

	printf
	(
		"token: type: %i, start: %i, end: %i, size: %i, parent: %i\n",
		tok->type,
		tok->start,
		tok->end,
		tok->size,
		tok->parent
	);
}

int main( int argc, char *argv[] )
{
	int err = 0;
	char *tmp = NULL;
	fmt_t p, t1_obj;
	fmt_tok_t t0, t1, iter;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Input:\n%s\n", tmp );
	free( tmp );

	A( fmt_get_tok( &p, NULL, "T0", &t0 ) );
	A( fmt_get_tok( &p, &t0, "T1", &t1 ) );

	/* valgrind will complain if iter will not be initialized */
	memset( &iter, 0, sizeof(fmt_tok_t) );
	while( (err = fmt_array_next( &p, &t1, &iter )) > 0 ) {
		A( fmt_dump_string( &p, &iter, &tmp ) );
		fprintf( fp, "next element: %s\n", tmp );
		free( tmp );
		A( fmt_get_string( &p, &iter, "r", &tmp ) );
		fprintf( fp, "value of 'r': %s\n", tmp );
		free( tmp );
	}

	A( fmt_get( &p, &t0, "T1", &t1_obj ) );
	A( fmt_dump_string( &t1_obj, NULL, &tmp ) );
	fprintf( fp, "array 'T1':\n%s\n", tmp );
	free( tmp );

	/* drop iter back to 0 */
	memset( &iter, 0, sizeof(fmt_tok_t) );
	while( (err = fmt_array_next( &t1_obj, NULL, &iter )) > 0 ) {
		A( fmt_dump_string( &t1_obj, &iter, &tmp ));
		fprintf( fp, "next element: %s\n", tmp );
		free( tmp );
		A( fmt_get_string( &t1_obj, &iter, "r", &tmp ) );
		fprintf( fp, "value of 'r': %s\n", tmp );
		free( tmp );
	}

exit:
	A( fmt_free( &p ) );
	A( fmt_free( &t1_obj ) );
	fclose( fp );

	return 0;
}
