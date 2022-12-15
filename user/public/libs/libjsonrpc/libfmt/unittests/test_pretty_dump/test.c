/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <assert.h>
#include <libfmt.h>

#define A(x) assert((x) >= 0)

int main()
{
	fmt_t p;

	A( fmt_load_file("file.json", &p, 0) );

	A( fmt_dump_file(&p, "result", LIBFMT_PRETTY_DUMP) );

	A( fmt_free(&p) );

	return 0;
}
