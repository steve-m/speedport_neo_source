/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <libfmt.h>

int main( int argc, char **argv )
{
	int i, count = 100;
	int err = 0;
	char *file = argv[1];
	if (argc > 2)
		count = atoi(argv[2]);

	for (i = 1; i <= count; i++) {
		fmt_t p = FMT_NULL;
		fmt_tok_t obj_iter;

		/* test if init macro worked */
		fmt_free( &p );

		fmt_parser_init( &p, 1 );

		if ( (err = fmt_load_file( file, &p, 0 )) < 0) {
			printf("cannot load file: %i\n", err);
			fmt_free( &p );
			exit(EXIT_FAILURE);
		}

		printf( "file '%s' loaded successfully\n", file );

		if ( fmt_tok_is_array( p.tok ) ) {
			char *x = NULL;
			printf( "array!\n" );
			while( fmt_array_next( &p, NULL, &obj_iter ) > 0 ) {
				fmt_dump_string( &p, &obj_iter, &x );
				printf( "dumped iter: %s\n", x );
				free( x );
			}
			fmt_free( &p );
			exit(EXIT_SUCCESS);
		}

		fmt_tok_t res, *tmp = NULL;
		if ( !fmt_get_tok( &p, NULL, "result", &res ) )
			tmp = &res;

		char *obj = NULL;
		char *key = NULL;
		int iter = 0;
		memset( &obj_iter, 0, sizeof(fmt_tok_t) );
		printf("iter start\n");
		while ( (iter = fmt_object_next( &p, tmp, &obj_iter, &key )) > 0) {
			fmt_dump_string( &p, &obj_iter, &obj );
			printf("'%s' : '%s'\n", key, obj);
			free(obj);
			free(key);
		}
		printf("iter stop\n");

		fmt_stats_t stat;
		fmt_stats( &p, &stat );
		printf( "\nObject stats:\n" );
		printf( "  token count: %i\n", stat.tok_count );
		printf( "  used tokens: %i\n", stat.tok_used );
		printf( "  used memory: %i\n", stat.memsize );
		printf( "  json length: %i\n", stat.dumplen );

		fmt_free( &p );
	}
	printf("\n");

	exit(EXIT_SUCCESS);
}
