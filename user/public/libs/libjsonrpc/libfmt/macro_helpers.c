/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <stdlib.h>
#include "macros.h"

void __disp_arr_free(void *p)
{
	struct {
		const int nmemb;
		void     *a;
	} *arr_p = p;

	int i;
	for (i = 0; i < arr_p->nmemb; i++) {
		char **a = (char **)(&arr_p->a + i);
		free(*a);
	}
}
