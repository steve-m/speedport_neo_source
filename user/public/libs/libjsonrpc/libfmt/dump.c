/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <string.h>
#include <unistd.h>

#include "base.h"
#include "fmt_priv.h"


inline size_t fmt_dump_len( fmt_t *obj )
{
	if ( !obj || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	size_t len = obj->tok->end;

	if ( obj->tok->type == JSMN_STRING )
		len++;

	return len;
}

int fmt_dump_string( fmt_t *obj, fmt_tok_t *tok, char **res )
{
	if ( !obj || !obj->js )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !tok )
		*res = strndup( obj->js, fmt_dump_len( obj ) );
	else
		*res = strndup((const char *)&obj->js[tok->start],
						tok->end - tok->start);
	return LIBFMT_ERR_NONE;
}

int fmt_dump_file( fmt_t *obj, const char *path, uint32_t flags )
{
	int err, new_js = 0;
	char *js = NULL;
	FILE *f;
	lock_t lock;
	size_t js_len, wb;

	if ( !obj || !obj->js || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !path )
		return LIBFMT_ERR_FILE_OPEN;

	if ( flags & LIBFMT_PRETTY_DUMP ) {
		if ( fmt_pretty_dump( obj, NULL, &js ) < 0 )
			return LIBFMT_ERR_GENERIC;
		js_len = strlen(js);
		new_js = 1;
	/* Under development.
	   Do not use LIBFMT_DUMP_COMPACT & LIBFMT_DUMP_COMPACT_NL */
	} else if ( flags & LIBFMT_DUMP_COMPACT ) {
		if ( fmt_pretty_dump_v2( obj, NULL, &js ) < 0 )
			return LIBFMT_ERR_GENERIC;
		js_len = strlen(js);
		new_js = 1;
	} else {
		js     = obj->js;
		js_len = fmt_dump_len(obj);
	}

	lock_init( &lock, NULL );

	if ( flags & LIBFMT_LOCK_DONTUSE )
		f = fopen( path, "w" );
	else
		f = fopen_l( path, "w", LIBASE_LOCK_RETRY_DEF,
					LIBASE_LOCK_TIMEOUT_DEF, &lock );

	if ( !f ) {
		if (new_js)
		free(js);
		return LIBFMT_ERR_FILE_OPEN;
	}

	wb = fwrite(js, 1, js_len, f);
	if( fsync( fileno( f)))
		wb = 0;

	if (new_js)
		free(js);

	if ( flags & LIBFMT_LOCK_DONTUSE )
		err = fclose( f );
	else
		err = fclose_l( f, &lock );

	/* either fclose() failed or lock couldn't be released */
	if ( err )
		return LIBFMT_ERR_FILE_CLOSE;

	/* couldn't write all data to file */
	if ( obj->tok->end > wb )
		return LIBFMT_ERR_GENERIC;

	return LIBFMT_ERR_NONE;
}

/* This is a char-by-char pretty-printer */
int fmt_pretty_dump( fmt_t *obj, fmt_tok_t *tok, char **res )
{
	if ( !obj || !obj->js || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !res )
		return LIBFMT_ERR_GENERIC;

	*res = NULL;

	if ( !tok )
		tok = obj->tok;

	char  *start    = &obj->js[tok->start];
	char  *end      = &obj->js[tok->end];

	char  *dst      = NULL;
	size_t dst_sz   = 0;
	int    dst_pos  = 0;

	int    level    = 0;
	int    escape   = 0;
	int    inquotes = 0;
	int    skipnewl = 1;

	int    rc       = 0;
	char  *c;
	for ( c = start; c != end && rc == 0; c++ ) {
		rc = 0;

		/* Put indentation & new line before special characters */
		switch (*c)
		{
		case '}':
		case ']':
			if (inquotes)
				break;
			level--;
			skipnewl = 0;
		case '{':
		case '[':
			if (skipnewl || inquotes)
				break;

			rc += dump_newline(&dst, &dst_sz, &dst_pos, level);
			skipnewl = 1;
		}

		/* Process quotation mark */
		if (*c == '\"' && !escape)
			inquotes = !inquotes;

		/* Process escape character */
		if ((*c == '\\') != escape)
			escape = !escape;

		/* Add current character */
		rc += dump_add_char(&dst, &dst_sz, &dst_pos, *c);

		/* Put indentation & new line after special characters */
		switch (*c)
		{
		case '{':
		case '[':
			if (inquotes)
				break;
			level++;
			skipnewl = 0;
		case ',':
			if (inquotes)
				break;
			skipnewl = 0;
		case '}':
		case ']':
			if (skipnewl || inquotes)
				break;

			rc += dump_newline(&dst, &dst_sz, &dst_pos, level);
			skipnewl = 1;
			break;

		default:
			skipnewl = 0;
		}

	}

	rc += dump_newline(&dst, &dst_sz, &dst_pos, level);
	rc += dump_add_char(&dst, &dst_sz, &dst_pos, '\0');

	if (rc == 0) {
		*res = dst;
		return 0;
	}

	return LIBFMT_ERR_GENERIC;
}

/* This is a char-by-char pretty-printer v2 */
int fmt_pretty_dump_v2( fmt_t *obj, fmt_tok_t *tok, char **res )
{
	if ( !obj || !obj->js || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !res )
		return LIBFMT_ERR_GENERIC;

	*res = NULL;

	if ( !tok )
		tok = obj->tok;

	char  *start  = &obj->js[tok->start];
	char  *end    = &obj->js[tok->end];
	char  *dst    = NULL;
	size_t dst_sz = 0;

	int dst_pos   = 0;
	int level     = 0;
	int escape    = -1;
	int inquotes  = 0;
	int nl_after  = 0;
	int nl_before = 0;
	int inc_level = 0;
	int counter   = 0;
	int br_flag   = 0;
	int br_oflag  = 0;

	char *c;
	int  rc       = 0;
	for ( c = start; c != end && rc == 0; c++ ) {
		rc = 0;
		switch (*c) {
			case '{':
				if ( inquotes )
					break;
				inc_level = 1;
				/* 1 - if field is good */
				br_oflag = dump_get_obj_size( c, level );
				if ( br_oflag )
					break;
				nl_after = 1;
				break;
			case '}':
				if ( inquotes )
					break;
				level--;
				if ( br_oflag ) {
					br_oflag = 0;
					break;
				}
				nl_before = 1;
				break;
			case '[':
				if ( inquotes )
					break;
				/* 1 - if field is good */
				br_flag = dump_get_array_size( c, level );
				if ( br_flag )
					break;
				inc_level = 1;
				nl_after = 1;
				break;
			case ']':
				if ( inquotes )
					break;
				if ( br_flag ) {
					br_flag = 0;
					break;
				}
				level--;
				nl_before = 1;
				break;
			case ',':
				if ( inquotes || br_flag || br_oflag )
					break;
				nl_after = 1;
				break;
			case '\"':
				if ( (counter - escape) != 1 )
					inquotes = !inquotes;
				break;
			case '\\':
				escape = counter; // position of the counter
				break;
		}

		if ( nl_before )
			rc += dump_newline_v2( &dst, &dst_sz, &dst_pos, level );

		rc += dump_add_char( &dst, &dst_sz, &dst_pos, *c );

		if ( inc_level )
			level++;

		if ( nl_after )
			rc += dump_newline_v2( &dst, &dst_sz, &dst_pos, level );

		inc_level = 0;
		nl_after  = 0;
		nl_before = 0;
		counter++;
	}

	rc += dump_newline_v2( &dst, &dst_sz, &dst_pos, level );
	rc += dump_add_char( &dst, &dst_sz, &dst_pos, '\0' );

	if ( rc == 0 ) {
		*res = dst;
		return 0;
	}

	return LIBFMT_ERR_GENERIC;
}
