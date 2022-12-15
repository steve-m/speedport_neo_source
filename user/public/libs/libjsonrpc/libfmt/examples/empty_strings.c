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
	fmt_parser_init( &p, 10 );

	char *sss = "{\"key\":\"\",\"key2\":\"\"}";
	if (fmt_load_string( sss, strlen(sss), &p ) < 0) {
		printf("cannot load string\n");
		fmt_free( &p );
		exit(EXIT_FAILURE);
	}

	printf( "string loaded: '%s'\n", p.js );

	char *obj = NULL;
	char *key = NULL;
	int iter = 0;
	fmt_tok_t obj_iter;
	memset( &obj_iter, 0, sizeof(fmt_tok_t) );
	printf("iter start\n");
	while ( (iter = fmt_object_next( &p, NULL, &obj_iter, &key )) > 0) {
		fmt_dump_string( &p, &obj_iter, &obj );
		printf("'%s' : '%s'\n", key, obj);
		free(obj);
		free(key);
	}
	printf("iter stop\n");

	char *string;
	const char *newstring_path[] = {"key", 0};
	if ( !fmt_get_string_path( &p, NULL, newstring_path, &string ) ) {
		printf( "string object: '%s'\n", string );
		free(string);
	}

	fmt_free( &p );
	printf("\n");

	exit(EXIT_SUCCESS);
}

