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

void add_to_results(const char *str)
{
	static FILE *result_fd;
	if (!result_fd)
		result_fd = fopen("result", "w+");
	assert(result_fd != NULL);

	fprintf(result_fd, "%s\n", str);
}

int main()
{
	fmt_t p;
	int rc;

	A(fmt_load_file("file.json", &p, 0));

	fmt_tok_t
		tok_Lorem,
		tok_ipsum,
		tok_magna,
		tok_ad,
		tok_aliquam;
	A( fmt_get_tok(&p, NULL, "Lorem", &tok_Lorem) );

	/* Get ipsum value */
	A( fmt_get_tok(&p, &tok_Lorem, "ipsum", &tok_ipsum) );
	char *val;
	A( fmt_string_value(&p, &tok_ipsum, &val) );
	add_to_results(val); free(val);

	A( fmt_get_tok(&p, &tok_Lorem, "magna", &tok_magna) );

	/* Get ad array values */
	A( fmt_get_tok(&p, &tok_magna, "ad", &tok_ad) );

	fmt_tok_t tok_iter = tok_ad;
	for (rc = 1; ; ) {
		rc = fmt_array_next(&p, &tok_ad, &tok_iter);
		A( rc );
		if (rc == 0)
			break;

		A( fmt_string_value(&p, &tok_iter, &val) );
		add_to_results(val); free(val);
	}


	/* Get keys and values from aliquam*/
	A( fmt_get_tok(&p, &tok_magna, "aliquam", &tok_aliquam) );

	memset(&tok_iter, 0, sizeof(fmt_tok_t)); /* FIXME: Is that right? */
	for (rc = 1; ; ) {
		char *key;
		rc = fmt_object_next(&p, &tok_aliquam, &tok_iter, &key);
		A( rc );
		if (rc == 0)
			break;

		add_to_results(key);
		free(key);

		A( fmt_string_value(&p, &tok_iter, &val) );
		add_to_results(val);
		free(val);
	}

	fmt_free(&p);

	return 0;
}
