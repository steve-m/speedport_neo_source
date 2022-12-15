/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#ifndef EZJSON_H
#define EZJSON_H

#include <stdlib.h>

#include "base.h"
#include "libfmt.h"

#define EZJSON_MAX_TAG_LEN   32
#define EZJSON_MAX_DEPTH     8
#define EZJSON_ERRBUF_LEN    384

enum {
	EZJSON_ERR_OBJ_NOT_FOUND  = -100,
	EZJSON_ERR_PARSE_VALUE,
	EZJSON_ERR_CANNOT_SET,
	EZJSON_ERR_TOO_DEEP,
};

/*
  Position manipulation functions:

  r()                 -- moves up to the root level (and resets meta data)
  c("str")            -- moves to child element
  p(n)                -- moves n levels up
  n(i)                -- moves to i-th child element
                         (if does not exist, creates an element)
  set*(),get*(),del() -- moves one level up


  Object manipulation functions:

  set("str")          -- set string
  seti(i)             -- set signed integer
  setf("fmt", ...)    -- set formatted
  get(&str)           -- get string
  geti(&i)            -- get signed integer
  getf("fmt", ...)    -- get formatted
  del()               -- delete object
  key(&str)           -- get key


  Error manipulation functions:

  err(&str)           -- clears error, stores err in pstr (if any)
  erri(&i)            -- clears error, stores err in i (if any)
  err_set_log(0/1)    -- sets auto error logging
  err_get_log(0/1)    -- sets auto error logging
  err_fwd(0/1)        -- sets auto error reporting

  TODO: cleanup on error!
*/

typedef struct ezjson_helper_s ezjson_helper_t;
struct ezjson_helper_s {
	const ezjson_helper_t *(*err)(int *code, char **str);
	const ezjson_helper_t *(*err_str)(char **str);
	const ezjson_helper_t *(*err_code)(int *code);
	const ezjson_helper_t *(*r)();
	const ezjson_helper_t *(*p)(int levels);
	const ezjson_helper_t *(*c)(const char *name);
	const ezjson_helper_t *(*n)(int idx);
	const ezjson_helper_t *(*get)(char **value);
//    const ezjson_helper_t *(*getf)(const char *fmt, ...);
	const ezjson_helper_t *(*geti)(int *value);
	const ezjson_helper_t *(*key)(char **value);
	const ezjson_helper_t *(*set)(const char *value);
	const ezjson_helper_t *(*setf)(const char *fmt, ...)
		__attribute__ ((format (printf, 1, 2)));;
	const ezjson_helper_t *(*seti)(int ivalue);
	const ezjson_helper_t *(*dump)(char **value, int pretty);
};

const ezjson_helper_t *ezjson(fmt_t **object);


#endif
