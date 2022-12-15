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

void print_tokens( fmt_t *obj )
{
	if ( !obj )
		return;

	int i = 0;
	for ( i = 0; i < obj->num_tokens; i++ ) {
		printf
		(
			"token %i (of %i): type: %i, start: %i, end: %i, size: %i, parent: %i\n",
			i, obj->num_tokens,
			obj->tok[i].type,
			obj->tok[i].start,
			obj->tok[i].end,
			obj->tok[i].size,
			obj->tok[i].parent
		);
	}
}

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

int main ( int argc, char **argv )
{
	int err = 0;
	char *tmp = NULL;
	const char *path_default[] = { "default", "sensors", NULL };
	const char *path_other[] = { "other", "sensors", NULL };
	fmt_t p, sensors_default, sensors_other;
	fmt_tok_t group, other, def;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Input:\n%s\n", tmp );
	free( tmp );

	A( fmt_get_tok( &p, NULL, "group", &group ) );
//	printf("group ");
//	print_token( &group );

	fprintf( fp, "Saving 'sensors' from 'other': " );
	A( fmt_get_path( &p, &group, path_other, &sensors_other ) );
	fprintf( fp, "OK\n" );
//	print_tokens( &sensors_other );

	fprintf( fp, "Saving 'sensors' from 'default': " );
	A( fmt_get_path( &p, &group, path_default, &sensors_default ) );
	fprintf( fp, "OK\n" );
//	print_tokens( &sensors_default );

	fprintf( fp, "Trying to delete 'sensors' from 'other': " );
	A( fmt_get_tok( &p, NULL, "group", &group ) );
	err = fmt_del_path( &p, &group, path_other );
	A( err );
	fprintf( fp, "OK\n" );
	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Result:\n%s\n", tmp );
	free( tmp );

	fprintf( fp, "Trying to insert 'sensors' from 'default' to 'other': " );
	A( fmt_get_tok( &p, NULL, "group", &group ) );
// 	printf("group ");
// 	print_token( &group );
	A( fmt_get_tok( &p, &group, "other", &other ) );
	A( fmt_set_new_at( &p, &other, "sensors", &sensors_default ) );
	fprintf( fp, "OK\n" );
//	printf("after fmt_set_new_at()\n");
//	print_tokens( &p );
	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Result:\n%s\n", tmp );
	free( tmp );

	fprintf( fp, "Trying to delete 'sensors' from 'default': " );
	/* update group because it has changes after first deletion */
	A( fmt_get_tok( &p, NULL, "group", &group ) );
// 	printf("group ");
// 	print_token( &group );
	err = fmt_del_path( &p, &group, path_default );
//	printf("after fmt_del_path()\n");
//	print_tokens( &p );
	A( err );
	fprintf( fp, "OK\n" );
	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Result:\n%s\n", tmp );
	free( tmp );

	fprintf( fp, "Trying to insert 'sensors' from 'other' to 'default': " );
	A( fmt_get_tok( &p, NULL, "group", &group ) );
// 	printf("group ");
// 	print_token( &group );
	A( fmt_get_tok( &p, &group, "default", &def ) );
	A( fmt_set_new_at( &p, &def, "sensors", &sensors_other ) );
	fprintf( fp, "OK\n" );
//	printf("after fmt_set_new_at()\n");
//	print_tokens( &p );
	A( fmt_dump_string( &p, NULL, &tmp ) );
	fprintf( fp, "Result:\n%s\n", tmp );
	free( tmp );
exit:
	A( fmt_free( &p ) );
	A( fmt_free( &sensors_other ) );
	fclose( fp );

	return 0;
}
