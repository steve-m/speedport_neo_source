/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <libfmt.h>

#define A(x) assert((x) >= 0)

__attribute__ ((format (printf, 1, 2)))
void resultf(const char *fmt, ...)
{
    static FILE *result_fd;
    if (!result_fd)
        result_fd = fopen("result", "w+");
    assert(result_fd != NULL);

    va_list ap;
    va_start(ap, fmt);
    A( vfprintf(result_fd, fmt, ap) );
    va_end(ap);
}


int tok_arr_size[] = {0, 1, 9, 10, 11, /* Some small values */
		      25, 26, 27,      /* Some values around actual count */
		      100, 1000,       /* Some great values */
		      LIBFMT_TOK_COUNT_MAX};


void parse(int size)
{
	resultf("Parser size: %d\n", size);

	fmt_t p;
	A( fmt_load_file("file.json", &p, 0) );

	fmt_tok_t tok_T0, tok_T1, iter;

	A( fmt_get_tok(&p, NULL,    "T0", &tok_T0) );
	A( fmt_get_tok(&p, &tok_T0, "T1", &tok_T1) );

	memset(&iter, 0, sizeof(fmt_tok_t));
	while(fmt_array_next(&p, &tok_T1, &iter) > 0) {
		char *str;
		A( fmt_dump_string(&p, &iter, &str) );
		resultf("%s\n", str);
		free(str);
	}

	A( fmt_free(&p) );
}

int main()
{
	int i;
	for (i = 0; i < sizeof(tok_arr_size) / sizeof(int); i++)
		parse(tok_arr_size[i]);

	return 0;
}
