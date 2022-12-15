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
#include <assert.h>
#include <libfmt.h>

#define A(x) assert((x) >= 0)


static FILE *result_fd;

void add_to_results(const char *str)
{
	if (!result_fd)
		result_fd = fopen("result", "w+");
	assert(result_fd != NULL);

	fprintf(result_fd, "%s\n", str);
}

int main()
{
	fmt_t p;
	int rc;

	A( fmt_load_file("file.json", &p, 0) );

	char *val;
	fmt_tok_t tok_iter;
	memset(&tok_iter, 0, sizeof(fmt_tok_t));

	for (rc = 1; ; ) {
		rc = fmt_array_next(&p, NULL, &tok_iter);
		A( rc );
		if (rc == 0)
			break;

		A( fmt_string_value(&p, &tok_iter, &val) );
		add_to_results(val); free(val);
	}

	fmt_free(&p);

	return 0;
}
