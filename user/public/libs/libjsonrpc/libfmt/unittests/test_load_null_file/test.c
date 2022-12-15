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

static void add_to_results(const char *str)
{
	static FILE *result_fd;
	if (!result_fd)
		result_fd = fopen("result", "w");
	assert(result_fd != NULL);

	fprintf(result_fd, "%s", str);
}

int main()
{
	fmt_t p = FMT_NULL;
	fmt_load_file("result", &p, 0);
	fmt_free(&p);
	add_to_results("");
	return 0;
}
