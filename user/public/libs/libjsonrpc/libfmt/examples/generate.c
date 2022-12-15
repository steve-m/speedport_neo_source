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
		fmt_t root=FMT_NULL, i2c=FMT_NULL, status=FMT_NULL;

		fmt_object( &status );
		if (fmt_set_new( &status, "TemperatureSystem",
						fmt_stringf("%i", 34) ) < 0)
			exit(EXIT_FAILURE);

		if (fmt_set_new( &status, "TemperaturePVG",
						fmt_stringf("%i", 64) ) < 0)
			exit(EXIT_FAILURE);

		fmt_object( &i2c );
		fmt_set_new( &i2c, "Status", &status );
		fmt_set_new( &i2c, "TimeStamp",
						fmt_string("0918\\\"\"\"4892") );
		fmt_set_new( &i2c, "Flag", fmt_string("true") );

		fmt_object( &root );

		fmt_t arr=FMT_NULL;
		fmt_array( &arr );
		fmt_array_add_new( &arr, fmt_stringf( "%s", "dew\"dwe" ) );
		fmt_array_add_new( &arr, fmt_stringf( "%i", 0 ) );
		fmt_array_add_new( &arr, fmt_stringf( "%i", 1 ) );
		fmt_array_add( &arr, &i2c );
		fmt_set_new( &root, "test", &arr );

		fmt_set_new( &root, "i2c", &i2c );

		char *str = NULL;
		fmt_dump_string( &root, NULL, &str );
		printf("%s\n", str);
		free(str);

		if ( fmt_dump_file( &root, file, 0 ) )
			printf( "fmt_dump_file() error: %m" );

		fmt_free( &root );
	}
	printf("\n");

	exit(EXIT_SUCCESS);
}
