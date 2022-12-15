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
	char *file = argv[1];
	if (argc > 2)
		count = atoi(argv[2]);

	for (i = 1; i <= count; i++) {
		fmt_t p=FMT_NULL;
		/*
		 * Here parser size is expected json token count, no matter of what size.
		 * Every key, string, object, array or their element counts as a token.
		 * Parser performs better when it's size is smaller.
		 */
		fmt_parser_init( &p, 11 );

		if (fmt_load_file( file, &p, 0 ) < 0) {
			printf("cannot load file\n");
			fmt_free( &p );
			exit(EXIT_FAILURE);
		}

		printf( "file '%s' loaded successfully\n", file );

		fmt_tok_t module, status, null;
		fmt_get_tok( &p, NULL, "i2c", &module );
		fmt_get_tok( &p, NULL, "null", &null );
		if ( fmt_is_null( &p, &null ) )
			printf("null is null\n");
		else
			printf("null is not null\n");
		fmt_get_tok( &p, &module, "Status", &status );

		fmt_t module_obj=FMT_NULL;
		if ( !fmt_tok_to_fmt( &p, &module, &module_obj ) )
			printf( "module object string: '%s'\n", module_obj.js );

		fmt_t string=FMT_NULL;
		const char *newstring_path[] = {"String", 0};
		if ( fmt_get_path( &p, NULL, newstring_path, &string ) )
			printf( "string object: '%s'\n", string.js );
		int err = fmt_set_new( &p, "newstring", &string );
		if ( err ) {
			printf("failed to add 'newstring' object: %i\n", err);
			exit(EXIT_FAILURE);
		}

		char *s = NULL;
		fmt_get_string( &p, &status, "TemperatureSystem", &s );
		printf("\r%s: %i", s, i);
		free(s);
		printf("\n");

		const char *path[] = {"i2c", "Status", "TemperaturePVG", 0};
		if (!fmt_get_string_path( &p, NULL, path, &s )) {
			printf("%s: %i", s, i);
			free(s);
		}
		printf("\n");

		char *z = NULL;
		fmt_dump_string( &p, NULL, &z);
//		printf("%s\n", z);
		free(z);
		fmt_del( &p, NULL, "arr");
		fmt_dump_string( &p, NULL, &z);
//		printf("%s\n", z);
		free(z);

		fmt_set_new( &p, "new", fmt_stringf("%s %i", "a", 42));
		fmt_dump_string( &p, NULL, &z);
		printf("%s\n", z);

		int objc = fmt_object_size( &p , NULL );
		printf("keys in object: %i\n", objc);

//		z[strlen(z)-1] = '\0';
//		printf("%s\n", z);
		fmt_t newp=FMT_NULL;
		fmt_parser_init( &newp, 100 );
		printf("Trying to load incomplete json\n");
		err = fmt_load_string( z, strlen(z)-2, &newp );
		printf("err: %i\n", err);
		if (err < 0)
			printf("cant parse string\n");
		free(z);

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

/*
		fmt_tok_t array, iter;
		fmt_get_tok( &p, NULL, "arr", &array );
		iter = array;
		int arr_size = fmt_array_size( &array );
		printf("array size: %i\n",arr_size);
		if (arr_size > 0) {
			while (fmt_array_next( &p, &array, &iter ) > 0) {
				printf("next element: ");
				if (fmt_tok_is_string(&iter)) {
					char *a = NULL;
					fmt_string_value( &p, &iter, &a );
					printf("%s\n",a);
					free(a);
				} else {
					printf("not a string\n");
				}
			}
		}
*/
		fmt_free( &p );
		fmt_free( &newp );
	}
	printf("\n");

	exit(EXIT_SUCCESS);
}
