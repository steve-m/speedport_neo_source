/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <assert.h>
#include <base.h>
#include <ezjson.h>

#define A(x) assert((x) >= 0)

int main(int argc, char *argv[])
{
	int err = 0;
	fmt_t *q = NULL;

	ezjson(&q)
		/* Simple nesting */
		->c("one")->c("two")
		->    c("aa")->set("value-x")
		->    c("bb")->set("value-y")
		->    c("cc")
		->        c("stuff-a")->seti(58)
		->        c("stuff-b")->seti(21)->p(1)
		->    c("dd")

		/* Object in array */
		->        n(0)->c("lemon") ->setf("abc-%d", 0)->p(1)
		->        n(1)->c("orange")->setf("abc-%d", 1)->p(1)
		->        n(2)->c("apple") ->setf("abc-%d", 2)->p(1)
		->        n(3)->c("butter")->setf("abc-%d", 3)->p(2)
		->c("ee")

		/* Array in array double level nesting */
		->    n(0)->n(0)->set("one-one")
		->          n(1)->set("one-two")->p(1)

		/* Tripple level nesting */
		->    n(1)->n(0)->n(0)->set("two-one-one")->p(1)
		->          n(1)->n(0)->set("two-two-one")
		->                n(1)->set("two-two-two")
		->                n(2)->set("two-two-three")

		->err_code(&err);

	assert(q);
	assert(err == 0);

	A( fmt_dump_file(q, "result", LIBFMT_PRETTY_DUMP) );

	A( fmt_free(q) );

	return 0;
}
