/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <string.h>
#include <sys/stat.h>

#include "base.h"

#include "fmt_priv.h"
#include "libfmt.h"


int fmt_load_string( char *buf, size_t size, fmt_t *obj )
{
	int err = 0;
	int add_tokens = 2;

	if(!buf || !obj || (size < 2))
		return LIBFMT_ERR_GENERIC;

	obj->js = NULL; // seg.fault protection

	err = parser_init( obj, LIBFMT_TOK_COUNT_MIN );
	if( err )
		return err;

	/* TODO: move memory allocation to fmt_load_normalized() ? */
	obj->js = (char *)malloc(size + 1);
	if( obj->js == NULL ) {
		err = LIBFMT_ERR_MALLOC;
		goto error;
	}

	memcpy(obj->js, buf, size);
	err = fmt_load_normalized_new(obj->js, size);
	if(err)
		goto error;

	/* try to parse */
	while((err = jsmn_parse(&obj->parser, obj->js,
	       obj->tok, obj->num_tokens)) == JSMN_ERROR_NOMEM)
	{
		/* allocate more tokens and try to parse again */
		obj->num_tokens += add_tokens;
		obj->tok = (fmt_tok_t *)realloc( obj->tok,
					obj->num_tokens * sizeof(fmt_tok_t) );
		if ( obj->tok == NULL ) {
			err = LIBFMT_ERR_REALLOC_TOK;
			goto error;
		}

		/* initialize tokens, otherwise valgrind complains */
		mark_token_unused( obj->tok + obj->num_tokens - add_tokens,
								add_tokens );
	}

	if( err != JSMN_SUCCESS ) {
		obj->js[0] = '\0';
		err =  LIBFMT_ERR_PARSER;
		goto error;
	}

	/* jsmn doesn't return an error when parsing empty string/file */
	if( fmt_dump_len( obj ) < 2 ) {
		obj->js[0] = '\0';
		err = LIBFMT_ERR_PARSER;
		goto error;
	}

	if( obj->js[0] != '[' && obj->js[0] != '{' ) {
		err = LIBFMT_ERR_PARSER;
		goto error;
	}

	if( obj->js[0] == '[' )
		obj->tok->type = JSMN_ARRAY;
	else
		obj->tok->type = JSMN_OBJECT;

	return LIBFMT_ERR_NONE;
error:
	fmt_free(obj);
	return err;
}

int fmt_load_fp( FILE **fp, fmt_t **obj )
{
	if( *fp == NULL )
		return LIBFMT_ERR_GENERIC;

	int rb;
	long long acc = 0;
	int add_tokens = 2;
	int err = 0;
	char buf[LIBFMT_FILE_READ_BLOCK] = {0};

	err = parser_init(*obj, LIBFMT_TOK_COUNT_MIN);
	if(err)
		return err;

	(*obj)->js = NULL;
	while((rb = fread(buf, 1, LIBFMT_FILE_READ_BLOCK, *fp)) > 0)
	{
		(*obj)->js = (char *)realloc( (*obj)->js, acc + rb + 1);

		if( (*obj)->js == NULL ) {
			err = LIBFMT_ERR_REALLOC_JS;
			break;
		}

		memcpy((*obj)->js + acc, buf, rb);

		acc += (long long )rb;
	}

	if(acc < 2) {
		err = LIBFMT_ERR_PARSER;
		goto error;
	}

	err = fmt_load_normalized_new((*obj)->js, acc);
	if(err)
		goto error;

	if(err < 0 && err != LIBFMT_ERR_NULLMET)
		goto error;

	/* try to parse */
	while((err = jsmn_parse( &(*obj)->parser, (*obj)->js, (*obj)->tok,
				(*obj)->num_tokens )) == JSMN_ERROR_NOMEM)
	{
		/* allocate more tokens and try to parse again */
		(*obj)->num_tokens += add_tokens;
		(*obj)->tok = (fmt_tok_t *)realloc((*obj)->tok,
				(*obj)->num_tokens * sizeof(fmt_tok_t));

		if((*obj)->tok == NULL) {
			err = LIBFMT_ERR_REALLOC_TOK;
			goto error;
		}

		/* initialize tokens, otherwise valgrind complains */
		mark_token_unused((*obj)->tok + (*obj)->num_tokens - add_tokens,
								add_tokens);
	}
	if( err != JSMN_SUCCESS ) {
		(*obj)->js[0] = '\0';
		err = LIBFMT_ERR_PARSER;
		goto error;
	}

	/* jsmn doesn't return an error when parsing empty string/file */
	if( fmt_dump_len( *obj ) < 2 ) {
		(*obj)->js[0] = '\0';
		err =  LIBFMT_ERR_PARSER;
		goto error;
	}

	if((*obj)->js[0] == '[')
		(*obj)->tok->type = JSMN_ARRAY;
	else
		(*obj)->tok->type = JSMN_OBJECT;

	return LIBFMT_ERR_NONE;
error:
	fmt_free(*obj);
	return err;
}

int fmt_load_file( const char *file, fmt_t *obj, uint32_t flags )
{
	if ( !file )
		return LIBFMT_ERR_FILE_OPEN;

	struct stat statbuf;
	if ( !stat( file, &statbuf ) && !S_ISREG( statbuf.st_mode ) )
		return LIBFMT_ERR_FILE_OPEN;

	FILE *f;
	int err = 0;
	int perr = 0;

	lock_t lock;
	lock_init( &lock, NULL );

	int lockinuse = !( flags & LIBFMT_LOCK_DONTUSE );

	if ( lockinuse )
		f = fopen_l( file, "r", LIBASE_LOCK_RETRY_DEF,
					LIBASE_LOCK_TIMEOUT_DEF, &lock );
	else
		f = fopen( file, "r" );

	if ( !f )
		return LIBFMT_ERR_FILE_OPEN;

	perr = fmt_load_fp( &f, &obj );

	if ( lockinuse )
		err = fclose_l( f, &lock );
	else
		err = fclose(f);

	if ( perr )
		return perr;

	if ( err )
		return LIBFMT_ERR_FILE_CLOSE;

	return LIBFMT_ERR_NONE;
}
