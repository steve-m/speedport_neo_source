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

int main()
{
	fmt_t *p = fmt_object_alloc();
	assert(p);

	/* Formally, a key could also contain quote chracters. We do not test it
	   here. */
	A( fmt_set_new(p, "a key", fmt_string("value \"quoted\"")) );
	A( fmt_dump_file(p, "result", 0) );
	A( fmt_free(p) );
	return 0;
}
