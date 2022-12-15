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

void dump_tokens(fmt_t *p)
{
	if (!result_fd)
		result_fd = fopen("result", "w+");
	fprintf(result_fd, " --- Token dump ---\n");
	int i;
	for (i = 0; i < p->parser.toknext; i++) {
		char *token = strndup(p->js + p->tok[i].start,
				      p->tok[i].end - p->tok[i].start);
		assert(token);
		fprintf(result_fd,
			"%2d: start:%4d   end:  %4d   size: %4d   %s\n",
		       i, p->tok[i].start, p->tok[i].end, p->tok[i].size,
		       token);
		free(token);
	}
}


void add_to_results(const char *str)
{
	if (!result_fd)
		result_fd = fopen("result", "w+");
	assert(result_fd != NULL);

	fprintf(result_fd, "|%s|\n", str);
}

int main()
{
	fmt_t p;

	A( fmt_load_file("file.json", &p, 0) );

	char *test_value;

	A( fmt_get_string(&p, NULL, "", &test_value) );
	add_to_results(test_value);
	free(test_value);

	A( fmt_get_string(&p, NULL, "empty", &test_value) );
	add_to_results(test_value);
	free(test_value);

	fmt_tok_t tok;
	char *key;
	memset(&tok, 0, sizeof(fmt_tok_t)); /* FIXME: is this correct? */
	A( fmt_object_next(&p, NULL, &tok, NULL) );
	A( fmt_object_next(&p, NULL, &tok, NULL) );
	A( fmt_object_next(&p, NULL, &tok, &key) );

	add_to_results(key);
	free(key);

	A( fmt_string_value(&p, &tok, &test_value) );
	add_to_results(test_value);
	free(test_value);

	dump_tokens(&p);

	fmt_free(&p);

	return 0;
}
