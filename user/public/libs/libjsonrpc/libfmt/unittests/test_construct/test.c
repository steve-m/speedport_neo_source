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

void dump_tokens(FILE *f, fmt_t *p)
{
	fprintf(f, " --- Token dump ---\n");
	int i;
	for (i = 0; i < p->num_tokens; i++) {
		char *token = strndup(p->js + p->tok[i].start,
				      p->tok[i].end - p->tok[i].start);
		assert(token);
		fprintf(f, "%2d: start:%4d   end:  %4d   size: %4d   %s\n",
		       i, p->tok[i].start, p->tok[i].end, p->tok[i].size,
		       token);
		free(token);
	}
}

void put_in_some_values_a(fmt_t *p)
{
	/* Create a */
	fmt_t *a = fmt_object_alloc();
	assert(a);

	/* Put in some values */
	A( fmt_set_new(a, "key1", fmt_string("value1")) );
	A( fmt_set_new(a, "key2", fmt_string("value2")) );
	A( fmt_set_new(a, "key3", fmt_string("value3")) );

	A( fmt_set_new(a, "tstarr", fmt_array_alloc()) );

	/* Add a to the root object */
	A( fmt_set_new(p, "a", a) );
}

void put_in_some_values_b(fmt_t *p)
{
	/* Create b */
	fmt_t *b = fmt_object_alloc();
	assert(b);

	/* Create nested1 */
	fmt_t *nested1 = fmt_object_alloc();
	assert(nested1);

	/* Put in some values in nested1 */
	A( fmt_set_new(nested1, "null-key", fmt_null()) );
	A( fmt_set_new(nested1, "key-aaa", fmt_string("aaa")) );

	/* Add nested1 to b */
	A( fmt_set_new(b, "nested1", nested1) );

	/* Create nested2 */
	fmt_t *nested2 = fmt_object_alloc();
	assert(nested2);

	/* Add nested2 to b */
	A( fmt_set_new(b, "nested2", nested2) );

	/* Put in some values in b */
	A( fmt_set_new(b, "keyx", fmt_string("valuex")) );
	A( fmt_set_new(b, "keyy", fmt_string("valuey")) );

	/* Add b to the root object */
	A( fmt_set_new(p, "b", b) );
}

void put_in_some_other_a_values(fmt_t *p)
{
	fmt_tok_t a;

	fmt_t *str;

	/* put in some other values */
	str = fmt_string("other-1");
	A( fmt_get_tok(p, NULL, "a", &a) );
	A( fmt_set_at(p, &a, "other-key-1", str) );
	fmt_free(str);

	str = fmt_string("other-2");
	A( fmt_get_tok(p, NULL, "a", &a) );
	A( fmt_set_at(p, &a, "other-key-2", str) );
	fmt_free(str);
}

void put_in_some_other_values_b_nested1(fmt_t *p)
{
	fmt_tok_t nested1;

	fmt_t *val;

	const char *path[] = {"b", "nested1", NULL};

	/* put in some other values */
	val = fmt_string("nested1-other-1");
	A( fmt_get_tok_path(p, NULL, path, &nested1) );
	A( fmt_set_at(p, &nested1, "nested1-other-key-1", val) );
	fmt_free(val);

	val = fmt_string("nested1-other-2");
	A( fmt_get_tok_path(p, NULL, path, &nested1) );
	A( fmt_set_at(p, &nested1, "nested1-other-key-2", val) );
	fmt_free(val);

	val = fmt_string("nested1-other-3");
	A( fmt_get_tok_path(p, NULL, path, &nested1) );
	A( fmt_set_at(p, &nested1, "nested1-other-key-3", val) );
	fmt_free(val);
}

void put_in_some_values_b_nested2(fmt_t *p)
{
	fmt_tok_t nested2;

	fmt_t *val;

	const char *path[] = {"b", "nested2", NULL};

	/* put in some other values */
	val = fmt_string("nested2-other-1");
	A( fmt_get_tok_path(p, NULL, path, &nested2) );
	A( fmt_set_at(p, &nested2, "nested1-other-key-1", val) );
	fmt_free(val);

	val = fmt_null();
	A( fmt_get_tok_path(p, NULL, path, &nested2) );
	A( fmt_set_at(p, &nested2, "nested1-other-key-2", val) );
	fmt_free(val);
}

void put_in_some_array_values_a(fmt_t *p)
{
	fmt_tok_t arr;

	fmt_t *val;

	const char *path[] = {"a", "tstarr", NULL};

	int i;
	for (i = 0; i < 32; i++) {
		A( fmt_get_tok_path(p, NULL, path, &arr) );

		char val_str[64];
		sprintf(val_str, "test-val-%d", i);
		val = fmt_string(val_str);
		fmt_array_add_at(p, &arr, val);
		fmt_free(val);
	}
}

int main()
{
	fmt_t *p = fmt_object_alloc();
	assert(p);

	put_in_some_values_a(p);
	put_in_some_values_b(p);
	put_in_some_other_a_values(p);
	put_in_some_other_values_b_nested1(p);
	put_in_some_values_b_nested2(p);
	put_in_some_array_values_a(p);


	FILE *f = fopen("result", "w+");
	assert(f != NULL);

	dump_tokens(f, p);
	char *str;
	fmt_dump_string(p, NULL, &str);
	fprintf(f, " --- JSON dump ---\n%s", str);
	free(str);

	fmt_free(p);
	return 0;
}
