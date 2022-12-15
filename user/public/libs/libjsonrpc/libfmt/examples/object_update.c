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
	fmt_t p=FMT_NULL;
	fmt_parser_init( &p, 1 );

	char *obj = NULL;
	char *json = "{\"result\":{\"key\":\"value\"}}";

	if (fmt_load_string( json, strlen(json), &p ) < 0) {
		printf("cannot load json string\n");
		fmt_free( &p );
		exit(EXIT_FAILURE);
	}

	fmt_t j=FMT_NULL;
	if ( !fmt_get( &p, NULL, "result", &j ) ){
		fmt_dump_string( &j, NULL, &obj );
		printf("%s\n", obj);
		free(obj);
		fmt_set_new( &j, "new", fmt_string("newobj") );
		fmt_dump_string( &j, NULL, &obj );
		printf("%s\n", obj);
		free(obj);
	}

	if ( fmt_update( &j, "key", fmt_string("updated") ) )
		printf("couldn't update object\n");
	fmt_dump_string( &j, NULL, &obj );
	printf("%s\n", obj);
	free(obj);

	fmt_stats_t stat;
	fmt_stats( &j, &stat );
	printf( "\nObject stats:\n" );
	printf( "  token count: %i\n", stat.tok_count );
	printf( "  used tokens: %i\n", stat.tok_used );
	printf( "  used memory: %i\n", stat.memsize );
	printf( "  json length: %i\n", stat.dumplen );

	fmt_free( &p );

	exit(EXIT_SUCCESS);
}
