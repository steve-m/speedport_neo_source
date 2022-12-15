/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libfmt.h>

int main( void )
{
	char *b="{ \"rfc\":\"list_show\",\
		\"T0\":{\
		\"T1\":[\
			{ \"r\":\"none\", \"qwe\":[ \"sdf\", \"sdfsdg\" ] },\
			{ \"r\":\"qwesdg\" },\
			{ \"r\":\"dsfsdgsd\" },\
			{ \"r\":\"sdsdgsdg\" },\
			{ \"r\":\"sdfsdsdf\" }\
		]}, \"aaa\":\"bbb\"\
	}";
	fmt_t obj=FMT_NULL;
	fmt_tok_t q0, q1, iter;
	char *x = NULL;
	int err = 0;

	fmt_parser_init( &obj, 0 );
	if ( fmt_load_string( b, strlen( b ), &obj ) ) {
		printf( "failed to load string: %s\n", b );
		fmt_free( &obj );
		exit(EXIT_FAILURE);
	}
	fmt_stats_t stat;
	fmt_stats( &obj, &stat );
	printf( "\nObject stats:\n" );
	printf( "  token count: %i\n", stat.tok_count );
	printf( "  used tokens: %i\n", stat.tok_used );
	printf( "  used memory: %i\n", stat.memsize );
	printf( "  json length: %i\n", stat.dumplen );

	err = fmt_get_tok( &obj, NULL, "T0", &q0 );
	printf("err = %i\n", err);
	err = fmt_get_tok( &obj, &q0, "T1", &q1 );
	printf("err = %i\n", err);

	while( fmt_array_next( &obj, &q1, &iter ) > 0 ) {
		fmt_dump_string( &obj, &iter, &x );
		printf( "dumped iter: %s\n", x );
		free( x );
		fmt_get_string( &obj, &iter, "r", &x );
		printf( "r: %s\n", x );
		free( x );
	}

	fmt_dump_string( fmt_string( "a" ), NULL, &x );
	printf("%s\n", x);
	free( x );
	if ( !fmt_string_value( fmt_string( "a" ), NULL, &x ) ) {
		printf("%s\n", x);
		free( x );
	}

	fmt_free( &obj );

	exit(EXIT_SUCCESS);
}
