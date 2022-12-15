/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "fmt_priv.h"


int fmt_parser_init( fmt_t *p, uint32_t size )
{
	return LIBFMT_ERR_NONE;
}

int fmt_object( fmt_t *res )
{
	return fmt_new( "{}", 2, FMT_TYPE_OBJECT, res );
}

fmt_t *fmt_object_alloc( void )
{
	return fmt_new_alloc( "{}", 2, FMT_TYPE_OBJECT );
}

int fmt_array( fmt_t *res )
{
	return fmt_new( "[]", 2, FMT_TYPE_ARRAY, res );
}

fmt_t *fmt_array_alloc( void )
{
	return fmt_new_alloc( "[]", 2, FMT_TYPE_ARRAY );
}

fmt_t *fmt_string( const char *s )
{
	if ( !s )
		return NULL;

	int len = strlen(s) + 2 + 1;
	if ( len < 4 )
		return NULL;

	fmt_t *res = fmt_new_alloc( s, len, FMT_TYPE_STRING );

	return res;
}

fmt_t *fmt_stringf( const char *format, ... )
{
	if ( !format )
		return NULL;

	char *s = NULL;
	int len = 0;

	va_list args;
	va_start( args, format );
	len = vasprintf( &s, format, args );
	va_end( args );

	if ( len < 0 ) {
		free(s);
		return NULL;
	}

	len = len + 2 + 1;

	fmt_t *res = fmt_new_alloc( s, len, FMT_TYPE_STRING );

	free(s);
	return res;
}

fmt_t *fmt_primitive( const char *prim, int len, fmt_type_t type )
{
	return fmt_new_alloc( prim, len, type );
}

fmt_t *fmt_null( void )
{
	return fmt_primitive( "null", 4, FMT_TYPE_NULL );
}

fmt_t *fmt_bool( int b )
{
	int len = 0;
	char *value = NULL;

	if ( b == LIBFMT_TRUE )
		len = 4;
	else
		len = 5;

	value = (char *)malloc( len );
	if ( b == LIBFMT_TRUE )
		memcpy( value, "true", len );
	else
		memcpy( value, "false", len );

	fmt_t *res = fmt_primitive( value, len, FMT_TYPE_BOOL );

	free( value );
	return res;
}

fmt_t *fmt_copy_dup( fmt_t *from, fmt_tok_t *where )
{
	fmt_t *res = (fmt_t *)malloc( sizeof(fmt_t) );
	if ( res == NULL )
		return NULL;

	if ( fmt_tok_to_fmt( from, where, res ) ) {
		fmt_free( res );
		return NULL;
	}

	res->type = FMT_TYPE_COPY;

	return res;
}

int fmt_copy( fmt_t *from, fmt_t *to )
{
	return fmt_tok_to_fmt( from, NULL, to );
}

int fmt_tok_to_fmt( fmt_t *obj, fmt_tok_t *from, fmt_t *to )
{
	if ( !obj || !obj->js || !obj->tok || !to )
		return LIBFMT_ERR_OBJ_INVALID;

	fmt_tok_t *tmp_tok;

	if ( fmt_tok_valid( from ) == LIBFMT_TRUE )
		tmp_tok = from;
	else
		tmp_tok = obj->tok;

	int i = 0;
	int len = tmp_tok->end - tmp_tok->start;
	fmt_tok_t *ext_mem = NULL;

	ext_mem = (fmt_tok_t *)malloc( sizeof(fmt_tok_t) );
	if ( !ext_mem )
		return LIBFMT_ERR_MALLOC;

	to->tok = ext_mem;
	to->tok->type  = tmp_tok->type;
	to->tok->start = 0;
	to->tok->end   = len;
	to->tok->size  = tmp_tok->size;

	to->num_tokens = 0;
	to->type = FMT_TYPE_UNDEF;

	/* copy all tokens information */
	for ( i = 0; i < obj->num_tokens; i++ ) {
		if ( obj->tok[i].end > tmp_tok->end ||
				obj->tok[i].start < tmp_tok->start )
			continue;

		to->num_tokens++;
		ext_mem = (fmt_tok_t *)realloc( to->tok,
					to->num_tokens * sizeof(fmt_tok_t) );
		if ( !ext_mem )
			return LIBFMT_ERR_REALLOC_TOK;
		to->tok = ext_mem;

		memcpy( &to->tok[to->num_tokens - 1],
					obj->tok + i, sizeof(fmt_tok_t) );
	}

	/* adjust copied tokens boundaries and parents */
	int old_parent = 0;
	if ( to->num_tokens > 1 )
		old_parent = to->tok[1].parent;
	for ( i = 0; i < to->num_tokens; i++ ) {
		to->tok[i].start  -= tmp_tok->start;
		to->tok[i].end    -= tmp_tok->start;
		to->tok[i].parent -= old_parent;
	}
	to->tok->parent = -1;

	if ( fmt_tok_is_string( tmp_tok ) )
		to->js = strndup((const char *)obj->js + tmp_tok->start - 1,
								len + 2);
	else
		to->js = strndup((const char *)obj->js + tmp_tok->start, len);

	if ( to->js == NULL )
		return LIBFMT_ERR_STRNDUP;

	if ( fmt_tok_is_string( tmp_tok ) ) {
		to->tok->start += 1;
		to->tok->end += 1;
		to->js[to->tok->end + 1] = '\0';
	} else {
		to->js[to->tok->end] = '\0';
	}

	mark_parser_unused( to );
	return LIBFMT_ERR_NONE;
}

int fmt_free( fmt_t *obj )
{
	if ( !obj )
		return LIBFMT_ERR_NONE;

	if ( obj->type == FMT_TYPE_FREED )
		return LIBFMT_ERR_NONE;

	free( obj->js );
	free( obj->tok );

	obj->js         = NULL;
	obj->tok        = NULL;
	obj->num_tokens = 0;

	if(  obj->type == FMT_TYPE_STRING ||
	     obj->type == FMT_TYPE_NULL   ||
	     obj->type == FMT_TYPE_BOOL   ||
	     obj->type == FMT_TYPE_ARRAY  ||
	     obj->type == FMT_TYPE_OBJECT ||
	     obj->type == FMT_TYPE_COPY   ||
	     obj->type == FMT_TYPE_NUMBER )
	{
		obj->type = FMT_TYPE_FREED;
		free(obj);
		obj = NULL;
	}

	return LIBFMT_ERR_NONE;
}

int fmt_get_tok( fmt_t *obj, fmt_tok_t *where, const char *key, fmt_tok_t *res )
{
	if ( !obj || !obj->js || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !key )
		return LIBFMT_ERR_KEY_INVALID;

	if ( !res )
		return LIBFMT_ERR_TOK_INVALID;

	int i = 0;
	int start = obj->tok->start;
	size_t keysize = strlen(key);

	if ( where ) {
		start = where->start;
		i = lookup_token_idx( obj, where );
	}

	if ( i < 0 )
		return i;

	for (; i < get_used_token_count(obj); i++) {
		if ( start > obj->tok[i].start )
			continue;

		if ( where && where->end <= obj->tok[i].end )
			continue;

		if ( !fmt_tok_is_string(&obj->tok[i]) )
			continue;

		if ( obj->tok[i].end - obj->tok[i].start == keysize &&
		     !strncmp((const char *)&obj->js[obj->tok[i].start],
			      key, keysize) )
		{
			/* NOTE: If we used references instead of copies,
			   parsing would get a bit more efficient (see
			   lookup_token_idx) */
			i++;
			memcpy( res, obj->tok + i, sizeof(fmt_tok_t) );
			return LIBFMT_ERR_NONE;
		}
		/* fast forward */
		if ( obj->num_tokens > i + 1 )
			start = obj->tok[i+1].end + 1;
	}

	/* not found */
	return LIBFMT_ERR_GENERIC;
}

int fmt_get_tok_path( fmt_t *obj, fmt_tok_t *where,
					const char **path, fmt_tok_t *res )
{
	int i;
	fmt_tok_t *tmp_tok = where;

	if ( !path )
		return LIBFMT_ERR_KEY_INVALID;


	for ( i = 0; path[i]; i++ ) {
		if ( fmt_get_tok( obj, tmp_tok, path[i], res ) )
			return LIBFMT_ERR_GENERIC;

		if ( fmt_tok_is_array(res) && path[i+1] )
			return LIBFMT_ERR_GENERIC;

		tmp_tok = res;
	}

	return LIBFMT_ERR_NONE;
}

int fmt_get( fmt_t *obj, fmt_tok_t *where, const char *key, fmt_t *res )
{
	fmt_tok_t tmp = FMT_TOK_NULL;
	if ( fmt_get_tok( obj, where, key, &tmp ) )
		return LIBFMT_ERR_GENERIC;

	if ( fmt_tok_to_fmt( obj, &tmp, res ) )
		return LIBFMT_ERR_GENERIC;

	return LIBFMT_ERR_NONE;
}

int fmt_get_path( fmt_t *obj, fmt_tok_t *where, const char **path, fmt_t *res )
{
	fmt_tok_t tmp = FMT_TOK_NULL;
	if ( fmt_get_tok_path( obj, where, path, &tmp ) )
		return LIBFMT_ERR_GENERIC;

	if ( fmt_tok_to_fmt( obj, &tmp, res ) )
		return LIBFMT_ERR_GENERIC;

	return LIBFMT_ERR_NONE;
}

int fmt_string_value( fmt_t *obj, fmt_tok_t *tok, char **res )
{
	if ( !obj || !obj->js || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !tok ) {
		if ( !fmt_tok_is_string( obj->tok ) )
			return LIBFMT_ERR_GENERIC;
		if ( fmt_unescape_string( (const char *)&obj->js[obj->tok->start],
					obj->tok->end - obj->tok->start, res ) )
			return LIBFMT_ERR_GENERIC;
	} else {
		if ( !fmt_tok_is_string( tok ) )
			return LIBFMT_ERR_GENERIC;
		if ( fmt_unescape_string( (const char *)&obj->js[tok->start],
					tok->end - tok->start, res ) )
			return LIBFMT_ERR_GENERIC;
	}

	return LIBFMT_ERR_NONE;
}

int fmt_get_string( fmt_t *obj, fmt_tok_t *where, const char *key, char **res )
{
	fmt_tok_t tmp = FMT_TOK_NULL;

	if ( fmt_get_tok( obj, where, key, &tmp ) )
		return LIBFMT_ERR_GENERIC;

	if ( fmt_string_value( obj, &tmp, res ) )
		return LIBFMT_ERR_GENERIC;

	return LIBFMT_ERR_NONE;
}

int fmt_get_string_path( fmt_t *obj, fmt_tok_t *where,
					const char **path, char **res )
{
	fmt_tok_t tmp;

	if ( fmt_get_tok_path( obj, where, path, &tmp ) )
		return LIBFMT_ERR_GENERIC;

	if ( fmt_string_value( obj, &tmp, res ) )
		return LIBFMT_ERR_GENERIC;

	return LIBFMT_ERR_NONE;
}

int fmt_del( fmt_t *obj, fmt_tok_t *where, const char *key )
{
	if ( !obj || !obj->js || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !key )
		return LIBFMT_ERR_KEY_INVALID;

	if ( where && !fmt_tok_is_object( where ) )
		return LIBFMT_ERR_TOK_INVALID;

	if ( !where && !fmt_is_object( obj ) )
		return LIBFMT_ERR_OBJ_INVALID;

	int i = 0;
	int start = obj->tok->start;

	fmt_tok_t hole = FMT_TOK_NULL;
	hole.start = 0;
	hole.end = 0;
	/* we are always deleting 2 tokens - key and it's value */
	hole.size = 2;
	int hole_start_off = 0;
	int hole_end_off = 0;
	size_t keysize = strlen(key);

	i = 0;
	if ( where ) {
		start = where->start;
		i = lookup_token_idx( obj, where );
	}

	if (i < 0)
		return i;

	for (; i < get_used_token_count(obj); i++) {
		/* skip root index and updated next index */
		if ( start > obj->tok[i].start )
			continue;

		/* key must be string obviously */
		if ( !fmt_tok_is_string(&obj->tok[i]) )
			continue;

		/* skip keys of different size and update next index */
		if ( obj->tok[i].end - obj->tok[i].start != keysize ) {
			start = obj->tok[i+1].end;
			continue;
		}

		if (!strncmp((const char *)&obj->js[obj->tok[i].start],
							key, keysize))
		{
			hole.start = obj->tok[i].start - 1;
			if ( obj->js[hole.start - 1] == ',' ) {
				hole_start_off++;
				hole.start--;
			}

			i++;
			hole.end = obj->tok[i].end;

			if ( fmt_tok_is_string(&obj->tok[i]) ) {
				hole_end_off++;
				hole.end++;
			}

			if ( obj->js[hole.end] == ',' &&
					obj->js[hole.start] != ',' ) {
				hole_end_off++;
				hole.end++;
			}

			break;
		}
		/* fast forward */
		if ( obj->num_tokens > i + 1 )
			start = obj->tok[i+1].end + 1;
	}

	if ( hole.end == 0 ) /* key not found in given boundaries */
		return LIBFMT_ERR_GENERIC;

	int hs = hole.end - hole.start;

	/* go backwards, search for parents and resize them */
	int j = i;
	int parent_size_set = 0;
	while( j > 0 ) {
		if( obj->tok[j].start < hole.start &&
			obj->tok[j].end > hole.end &&
			fmt_tok_is_object(&obj->tok[j]) )
		{
			if(obj->tok[j].size > 1 && !parent_size_set) {
				obj->tok[j].size -= hole.size;
				parent_size_set = 1;
			}

			obj->tok[j].end -= hs;
		}
		j--;
	}

	/* this is safe only if there are no unused tokens in the middle */
	int first_unused = find_first_unused_token(obj);
	if ( first_unused < 0 )
		first_unused = obj->num_tokens;

	fmt_tok_t hole_idx = FMT_TOK_NULL;
	hole_idx.start = 0;
	hole_idx.end = 0;
	hole_idx.parent = obj->tok[i].parent;

	/* go forward, delete tokens and adjust boundaries */
	for ( i--; i < first_unused; i++ ) {
		/* update hole indexes */
		if ( obj->tok[i].start == hole.start ||
				obj->tok[i].start == hole.start +
						     hole_start_off + 1 )
			hole_idx.start = i;

		if ( obj->tok[i].end < hole.end )
			hole_idx.end = i;

		/* skip tokens which will be deleted */
		if ( obj->tok[i].start >= hole.start &&
					obj->tok[i].end <= hole.end )
			continue;

		/* adjust token boundaries */
		obj->tok[i].start -= hs;
		obj->tok[i].end -= hs;
	}

	/* move tokens */
	hole_idx.size = hole_idx.end - hole_idx.start + 1;

	for(i = hole_idx.start; i <= first_unused - hole_idx.size; i++)
	{
		if ( i + hole_idx.size < obj->num_tokens )
			memcpy( obj->tok + i, obj->tok + i + hole_idx.size,
							sizeof(fmt_tok_t) );
		/* fix parents if needed */
		if ( obj->tok[i].parent > hole_idx.parent )
			obj->tok[i].parent -= hole_idx.size;
	}

	/* mark remaining tokens unused/deleted */
	mark_token_unused(&obj->tok[first_unused - hole_idx.size],
			  obj->num_tokens - first_unused + hole_idx.size);

	/* actually move the block */
	memmove( obj->js + hole.start,
	         obj->js + hole.end,
	         obj->tok[0].end - hole.end);

	/* shrink root object */
	if( !parent_size_set )
		obj->tok[0].size -= hole.size;
	obj->tok[0].end -= hs;
	obj->js[obj->tok[0].end] = '\0';

	/* shrink where token if any */
	if( fmt_tok_valid( where ) ) {
		where->size -= hole.size;
		where->end  -= hs;
	}

	/* update parser index if any */
	if( fmt_parser_valid( obj ) == LIBFMT_TRUE )
		obj->parser.toknext -= hole_idx.size;

	return LIBFMT_ERR_NONE;
}

int fmt_del_path( fmt_t *obj, fmt_tok_t *where,	const char **path )
{
	if ( !path )
		return LIBFMT_ERR_KEY_INVALID;

	fmt_tok_t tok = FMT_TOK_NULL, parent = FMT_TOK_NULL;
	int err = LIBFMT_ERR_NONE;

	err = fmt_get_tok_path( obj, where, path, &tok );
	if ( err )
		return err;

	err = fmt_get_tok_parent( obj, &tok, &parent );
	if ( err )
		return err;

	char *key = NULL;
	while ( *path ) {
		key = (char *)*path;
		path++;
	}

	err = fmt_del( obj, &parent, key );
	if ( err )
		return err;

	return LIBFMT_ERR_NONE;
}

int fmt_get_tok_parent( fmt_t *obj, fmt_tok_t *child, fmt_tok_t *res )
{
	if ( !obj || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !child || !res )
		return LIBFMT_ERR_TOK_INVALID;

	*res = obj->tok[child->parent];

	return LIBFMT_ERR_NONE;
}

int fmt_stats( fmt_t *obj, fmt_stats_t *res )
{
	if ( !obj || !fmt_is_object( obj ) )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !res )
		return LIBFMT_ERR_GENERIC;

	res->dumplen   = fmt_dump_len( obj );
	res->tok_count = obj->num_tokens;
	res->tok_used  = find_first_unused_token( obj );
	res->memsize   = res->tok_count * sizeof(fmt_tok_t) +
						sizeof(fmt_t) +
						res->dumplen;
	return LIBFMT_ERR_NONE;
}

int fmt_object_size( fmt_t *obj, fmt_tok_t *where )
{
	if ( !obj )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !where && fmt_is_object( obj ) )
		return obj->tok->size / 2;

	if ( fmt_tok_is_object( where ) )
		return where->size / 2;

	return LIBFMT_ERR_GENERIC;
}

int fmt_array_size( fmt_t *obj, fmt_tok_t *arr )
{
	if ( !obj )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !arr && fmt_is_array( obj ) )
		return obj->tok->size;

	if ( fmt_tok_is_array( arr ) )
		return arr->size;

	return LIBFMT_ERR_GENERIC;
}

int fmt_array_next( fmt_t *obj, fmt_tok_t *arr, fmt_tok_t *next )
{
	return fmt_next( obj, arr, next, NULL, FMT_TYPE_ARRAY );
}

int fmt_object_next( fmt_t *obj, fmt_tok_t *where, fmt_tok_t *next, char **key )
{
	return fmt_next( obj, where, next, key, FMT_TYPE_OBJECT );
}

static int fmt_append( fmt_t *obj, fmt_tok_t *parent, const char *key, fmt_t *val )
{
	if ( !obj || !obj->js || !obj->tok || !val || !val->js || !val->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	/* number of tokens in new object to be inserted */
	/* NOTE: using just val->num_tokens can include unused tokes also
	   what results in invalid tokens in the middle of nowhere */
	int valtokens = find_first_unused_token( val );
	if ( !valtokens )	/* weird, no valid tokens */
		return LIBFMT_ERR_OBJ_INVALID;
	if ( valtokens < 0 )	/* assume all tokens are used */
		valtokens = val->num_tokens;

	if ( !parent )
		parent = &obj->tok[0];

	/* parent token index */
	int parent_idx = lookup_token_idx( obj, parent );
	if ( parent_idx < 0 )	/* Invalid token? */
		return parent_idx;

	/* Addition commences after prev_idx token */
	int prev_idx = find_last_subtok(obj, parent_idx);

	int    	  pos     	= parent->end - 1;
	size_t 	  keysize 	= key ? strlen(key) : 0;
	const int keysize_extra = key ? 3           : 0; /* strlen("":) */
	size_t 	  valsize 	= fmt_dump_len( val );   /* strlen(val->js) */
	size_t 	  addsize 	= valsize + keysize + keysize_extra;
	int       continuation  = 0;

	if (parent->size > 0) {	/* Continuation? */
		addsize++;
		pos++;
		continuation = 1;
	}

	/* First reallocate JSON string and token list */
	void *ext_mem = NULL;
	ext_mem = realloc(obj->js, strlen(obj->js) + addsize + 1);
	if ( !ext_mem ) {
		fmt_free(obj);
		return LIBFMT_ERR_REALLOC_JS;
	}
	obj->js = ext_mem;

	ext_mem = realloc(obj->tok, sizeof(fmt_tok_t) *
			  (obj->num_tokens + (key ? 1 : 0) + valtokens));
	if ( !ext_mem ) {
		fmt_free(obj);
		return LIBFMT_ERR_REALLOC_TOK;
	}
	obj->tok = ext_mem;

	/* Safe monkeying with the reallocated buffers further on */

	if (continuation)
		obj->js[pos-1] = ','; /* replace '}' with ',' */

	/* Move the rest of the contents to the end */
	memmove(obj->js + pos + addsize, obj->js + pos,
		obj->tok[0].end - pos);

	/* Put the new contents in */
	obj->js[pos] = '\0';
	if (key)
		sprintf(obj->js + pos, "\"%s\":", key);
	strcat(obj->js + pos, val->js);
	obj->js[pos + addsize - continuation] =
		key ? '}' : ']'; /* de-null-terminates */

	/* Null-terminate whole thing */
	obj->js[obj->tok[0].end + addsize] = '\0';

	/* Move the rest of the tokens to the end */
	memmove(&obj->tok[prev_idx + 1 + (key ? 1 : 0) + valtokens],
		&obj->tok[prev_idx + 1],
		sizeof(fmt_tok_t) * (obj->num_tokens - prev_idx - 1));

	/* Deal with the newly added object tokens */
	int key_tok_idx = prev_idx + 1;
	int val_tok_idx = (key ? key_tok_idx : prev_idx) + 1;
	obj->num_tokens += (key ? 1 : 0) + valtokens;

	/* Set up key token */
	if (key) {
		obj->tok[key_tok_idx].type   = JSMN_STRING;
		obj->tok[key_tok_idx].start  = pos + 1;
		obj->tok[key_tok_idx].end    = pos + 1 + keysize;
		obj->tok[key_tok_idx].size   = 0;
		obj->tok[key_tok_idx].parent = parent_idx;
	}

	/* Put in value tokens */
	memcpy( &obj->tok[val_tok_idx], val->tok,
		valtokens * sizeof(fmt_tok_t) );
	obj->tok[val_tok_idx].parent = parent_idx;

	/* Fix unarranged token list */
	fix_tokens_after_append(obj, prev_idx, parent_idx,
				pos + (key ? keysize + keysize_extra : 0),
				valtokens, addsize, key ? 1 : 0);

	return LIBFMT_ERR_NONE;
}

int fmt_set_at( fmt_t *obj, fmt_tok_t *where, const char *key, fmt_t *val )
{
	if ( !obj )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !key )
		return LIBFMT_ERR_KEY_INVALID;

	if ( where && !fmt_tok_is_object( where ) )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !where && !fmt_is_object( obj ) )
		return LIBFMT_ERR_OBJ_INVALID;

	return fmt_append( obj, where, key, val );
}

int fmt_set( fmt_t *obj, const char *key, fmt_t *val )
{
	return fmt_set_at( obj, NULL, key, val );
}

int fmt_set_new_at( fmt_t *obj, fmt_tok_t *where, const char *key, fmt_t *val )
{
	int err = fmt_set_at( obj, where, key, val );

	fmt_free( val );

	if ( err != LIBFMT_ERR_NONE )
		return err;

	return LIBFMT_ERR_NONE;
}

int fmt_set_new( fmt_t *obj, const char *key, fmt_t *val )
{
	return fmt_set_new_at( obj, NULL, key, val );
}

int fmt_array_add_at( fmt_t *arr, fmt_tok_t *where, fmt_t *el )
{
	if ( where && !fmt_tok_is_array(where) )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !where && !fmt_tok_is_array(arr->tok) )
		return LIBFMT_ERR_OBJ_INVALID;

	return fmt_append( arr, where, NULL, el );
}

int fmt_array_add( fmt_t *arr, fmt_t *el )
{
	return fmt_array_add_at( arr, NULL, el );
}

int fmt_array_add_new_at( fmt_t *arr, fmt_tok_t *where, fmt_t *el )
{
	int err = fmt_array_add_at( arr, where, el );

	fmt_free( el );

	if ( err != LIBFMT_ERR_NONE )
		return err;

	return LIBFMT_ERR_NONE;
}

int fmt_array_add_new( fmt_t *arr, fmt_t *el )
{
	return fmt_array_add_new_at( arr, NULL, el );
}

int fmt_update_at( fmt_t *obj, fmt_tok_t *where, const char *key, fmt_t *newval )
{
	if ( where && !fmt_tok_is_object( where ) )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !where && !fmt_is_object( obj ) )
		return LIBFMT_ERR_OBJ_INVALID;

	fmt_del( obj, where, key );

	return fmt_set_new_at( obj, where, key, newval );
}

int fmt_update( fmt_t *obj, const char *key, fmt_t *newval )
{
	return fmt_update_at( obj, NULL, key, newval );
}

int fmt_diff( fmt_t *obj1, fmt_t *obj2, fmt_t *res, uint32_t strat )
{
	if ( !obj1 || !obj2 || !res )
		return LIBFMT_ERR_OBJ_INVALID;

	int err = 0;
	char *key = NULL;
	fmt_tok_t iter = FMT_TOK_NULL;
	fmt_t newval = FMT_NULL;
	res = fmt_object_alloc();

	/* add only those keys which exist in both obj1 and obj2
	 * but are different */
	while ( fmt_object_next( obj1, NULL, &iter, &key ) > 0 ) {
		/* find key in obj2 */
		err = fmt_get( obj2, NULL, key, &newval );
		if ( err )
			continue;
		fmt_set_new( res, key, &newval );
	}

	return LIBFMT_ERR_NONE;
}

int fmt_checksum( fmt_t *obj, fmt_checksum_t *cs )
{
	fmt_checksum_t tmp;

	if ( !cs )
		return LIBFMT_ERR_GENERIC;

	if ( fmt_cscalc( obj, &tmp ) )
		return LIBFMT_ERR_GENERIC;

	if ( !cs->buflen ) {
		memcpy( cs, &tmp, sizeof(fmt_checksum_t) );
		return LIBFMT_ERR_NONE;
	}

	if ( fmt_cscmp( cs, &tmp ) )
		return LIBFMT_ERR_GENERIC;

	return LIBFMT_ERR_NONE;
}

int fmt_update_create_path_new(fmt_t *fmt, char **path, fmt_t *fmt_u) {
	int i = 0, pos = 0, lim = 0;
	fmt_t *f_p = NULL;
	fmt_tok_t tok_p = FMT_TOK_NULL, tok = FMT_TOK_NULL;
	char *path_n[128];

	i = 0;
	while(path[i] != NULL) {
		fmt_tok_t tk = FMT_TOK_NULL;
		path_n[i] = path[i];
		path_n[i+1] = NULL;

		if(fmt_get_tok_path(fmt, NULL, (const char **)path_n, &tk)) {
			// end of path
			break;
		}
		tok_p = tk;
		pos++;
		i++;
		if(i > 125)
			return LIBFMT_ERR_GENERIC;
	}

	if(pos > 0) {
		fmt_t obj = FMT_NULL;

		fmt_get_tok_parent(fmt, &tok_p, &tok);

		fmt_get(fmt, &tok, path[pos-1], &obj);

		if(!fmt_is_object(&obj)) {
			fmt_free(&obj);
			fmt_free(fmt_u);
			return LIBFMT_ERR_GENERIC;
		}
		fmt_free(&obj);
	}

	// get depth of path
	i = 0;
	while(path[i] != NULL)
		i++;
	lim = i-1;

	f_p = fmt_u;
	if(pos == 0) { // recreate full path
		for(i = lim; i > 0; i--) {
			fmt_t *pp = f_p;
			f_p = fmt_object_alloc();
			fmt_set_new(f_p, path[i], pp);
		}

		fmt_set_new(fmt, path[0], f_p);
	}
	else if(pos == lim) { // single put
		fmt_set_new_at(fmt, &tok_p, path[pos], f_p);
	}
	else if(lim > pos) { // recretae partial path
		for(i = lim; i > pos; i--) {
			fmt_t *pp = f_p;
			f_p = fmt_object_alloc();
			fmt_set_new(f_p, path[i], pp);
		}

		fmt_set_new_at(fmt, &tok_p, path[pos], f_p);
	}

	return LIBFMT_ERR_NONE;
}

int fmt_is_initialized( fmt_t *obj )
{
  if( !obj ||
      obj->type <  FMT_TYPE_UNDEF ||
      obj->type >= FMT_TYPE_FREED ||
      obj->tok == NULL )
    return LIBFMT_FALSE;

  // We checked all what was possible
  return LIBFMT_TRUE;
}
