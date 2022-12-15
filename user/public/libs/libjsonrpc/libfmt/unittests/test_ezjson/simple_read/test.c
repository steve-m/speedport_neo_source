/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <base.h>
#include <ezjson.h>
#include <string.h>

#define A(x) assert((x) >= 0)

FILE *result_fd;

__attribute__ ((format (printf, 1, 2)))
void resultf(const char *fmt, ...)
{
	if (!result_fd)
		result_fd = fopen("result", "w+");
	assert(result_fd != NULL);

	va_list ap;
	va_start(ap, fmt);
#if 0
	A( vprintf(fmt, ap) );
#else
	A( vfprintf(result_fd, fmt, ap) );
#endif
	va_end(ap);
}

__attribute__((destructor))
void cleanup()
{
	fclose(result_fd);
}

void read_car_data(fmt_t **obj)
{
	DSTR(back_seat);
	DSTR(front_seat);
	DSTR(road);
	DSTR(err_str);
	DSTR(wheels, 4);

	int temperature;

	ezjson(obj)->r()
		->c("car")
		->    c("seats")
		->        c("back") ->get(&back_seat.v)
		->        c("front")->get(&front_seat.v)->r()
		->c("road")->get(&road.v)
		->c("temp")->geti(&temperature);

	ezjson(obj)->r()->c("car")->c("wheels");

	int i;
	for (i = 0; i < 4; i++)
		ezjson(obj)->n(i)->get(&wheels.a[i]);

	ezjson(obj)->err_str(&err_str.v);
	if (err_str.v) {
		resultf("%-15s: %s\n", "Error", err_str.v);
		return;
	}

	resultf("%-15s: %s\n", "Back", back_seat.v);
	resultf("%-15s: %s\n", "Front", front_seat.v);
	resultf("%-15s: %s\n", "Road", road.v);
	resultf("%-15s: %d\n", "Temperature", temperature);

	for (i = 0; i < 4; i++)
		resultf("Wheel %-9d: %s\n", i, wheels.a[i]);
}

void read_unknow_stuff(fmt_t **obj)
{
	DSTR(err_str);
	DSTR(values, 3);
	DSTR(keys,   3);

	ezjson(obj)->r()->c("unknown-stuff");

	int i;
	for (i = 0; i < 3; i++)
		ezjson(obj)->n(i)->get(&values.a[i])->key(&keys.a[i]);

	ezjson(obj)->err_str(&err_str.v);
	if (err_str.v) {
		resultf("%-15s: %s\n", "Error", err_str.v);
		return;
	}

	for (i = 0; i < 3; i++)
		resultf("%-15s: %s\n", keys.a[i], values.a[i]);
}

void read_dangers(fmt_t **obj)
{
	DSTR(err_str);
	DSTR(first,  5);
	DSTR(second, 2);

	ezjson(obj)->r()->c("world")->c("dangers");

	int i;

	ezjson(obj)->n(0);
	for (i = 0; i < 5; i++)
		ezjson(obj)->n(i)->get(&first.a[i]);

	ezjson(obj)->p(1)->n(1);
	for (i = 0; i < 2; i++)
		ezjson(obj)->n(i)->get(&second.a[i]);


	ezjson(obj)->err_str(&err_str.v);

	if (err_str.v) {
		resultf("%-15s: %s\n", "Error", err_str.v);
		return;
	}

	for (i = 0; i < 5; i++)
		resultf("%-15s: %s\n", "First  array", first.a[i]);

	for (i = 0; i < 2; i++)
		resultf("%-15s: %s\n", "Second array", second.a[i]);

}

int main(int argc, char *argv[])
{
	fmt_t p, *pp = &p;

	A( fmt_load_file("file.json", &p, 0) );

	/* These are supposed to succeed: */
	read_car_data(&pp);

	resultf("\n");
	read_unknow_stuff(&pp);

	resultf("\n");
	read_dangers(&pp);

	/* These are supposed to generate errors: */
	/* TODO: ... */

	A( fmt_free(&p) );
	return 0;
}
