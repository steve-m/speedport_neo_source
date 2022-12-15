/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libfmt.h>

#define TEST_FILE	"test.json"
#define RESULT_FILE	"result"

#define A(x) assert((x) >= 0)

int add(fmt_t *parser, char *nm, fmt_t *req, FILE *f)
{
	fprintf(f, "Function <add> called!\n");
	return fmt_set_new_at(parser, NULL, nm, req);
}

int del(fmt_t *parser, char *nm, FILE *f)
{
	fprintf(f, "Function <del> called!\n");
	return fmt_del(parser, NULL, nm);
}

int main (int argc, char *argv[])
{
	char *tmp;
	fmt_t p;

	FILE *fp = fopen(RESULT_FILE,"w");
	assert(fp != NULL);

	/* Load the file */
	A( fmt_load_file(TEST_FILE, &p, 0) );
	A( fmt_dump_string(&p, NULL, &tmp) );
	fprintf(fp, "%s\n", tmp);
	free(tmp);

	/* Delete A */
	A( del(&p, "A", fp) );
	A( fmt_dump_string(&p, NULL, &tmp) );
	fprintf(fp, "%s\n", tmp);
	free(tmp);

	/* Add A back */
	A( add(&p, "A", fmt_string("1"), fp) );
	A( fmt_dump_string(&p, NULL, &tmp) );
	fprintf(fp, "%s\n", tmp);
	free(tmp);

	/* Delete B */
	A( del(&p, "B", fp) );
	A( fmt_dump_string(&p, NULL, &tmp) );
	fprintf(fp, "%s\n", tmp);
	free(tmp);

	/* Add B back */
	A( add(&p, "B", fmt_string("2"), fp) );
	A( fmt_dump_string(&p, NULL, &tmp) );
	fprintf(fp, "%s\n", tmp);
	free(tmp);

	fprintf(fp, "Alles ist gut!\n");
	fclose(fp);
	fmt_free(&p);

	return 0;
}
