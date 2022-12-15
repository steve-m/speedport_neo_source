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
	char *tmp = NULL;
	const char *path[] = { "group", "other", NULL };
	fmt_t p = FMT_NULL;
	fmt_t string = FMT_NULL;
	fmt_t array = FMT_NULL;
	fmt_t object = FMT_NULL;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Input:\n%s\n", tmp );
	free( tmp );

	fprintf( fp, "Testing object_is_object (parsed): " );
	A( fmt_get_path( &p, NULL, path, &object ) );
	A( !fmt_is_object( &object ) );
	fprintf( fp, "OK\n" );
// 	A( fmt_dump_string( &object, NULL, &tmp ) );
// 	fprintf( fp, "%s\n", tmp );
// 	free( tmp );
	fprintf( fp, "Testing object_is_object (new): " );
	fmt_t *object_new = fmt_object_alloc();
	A( !fmt_is_object( object_new ) );
	fprintf( fp, "OK\n" );
	A( fmt_free( object_new ) );

	fprintf( fp, "Testing object_is_string (parsed): " );
	A( fmt_get( &object, NULL, "dsc", &string ) );
	A( !fmt_is_string( &string ) );
	fprintf( fp, "OK\n" );
// 	A( fmt_dump_string( &string, NULL, &tmp ) );
// 	fprintf( fp, "%s\n", tmp );
// 	free( tmp );
	fprintf( fp, "Testing object_is_string (new): " );
	fmt_t *string_new = fmt_stringf("aaa %i", 345);
	A( !fmt_is_string( string_new ) );
	fprintf( fp, "OK\n" );
	A( fmt_free( string_new ) );

	fprintf( fp, "Testing object_is_array (parsed): " );
	A( fmt_get( &object, NULL, "sensors", &array ) );
	A( !fmt_is_array( &array ) );
	fprintf( fp, "OK\n" );
// 	A( fmt_dump_string( &array, NULL, &tmp ) );
// 	fprintf( fp, "%s\n", tmp );
// 	free( tmp );
	fprintf( fp, "Testing object_is_array (new): " );
	fmt_t *array_new = fmt_array_alloc();
	A( !fmt_is_string( array_new ) );
	fprintf( fp, "OK\n" );
	A( fmt_free( array_new ) );

exit:
	A( fmt_free( &p ) );
	A( fmt_free( &string ) );
	A( fmt_free( &array ) );
	A( fmt_free( &object ) );
	fclose( fp );

	return 0;
}
