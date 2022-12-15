/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include <string.h>
#include <limits.h>
#include <sys/param.h>

#include "base.h"
#include "fmt_priv.h"

inline void mark_parser_unused( fmt_t *obj )
{
	if ( obj )
		obj->parser.toknext = -1;
}

inline void mark_token_unused( fmt_tok_t *tok, int count )
{
	if ( !tok )
		return;

	if ( count > 1 )
		memset( tok, -1, count * sizeof(fmt_tok_t) );
	else
		memset( tok, -1, sizeof(fmt_tok_t) );
}

/* TODO: merge with get_used_token_count() ? */
inline int find_first_unused_token( fmt_t *obj )
{
	if ( !obj || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	/* exact value */
	if ( fmt_parser_valid( obj ) == LIBFMT_TRUE )
		return obj->parser.toknext;

	/* search from the end is much faster as there are
	 * only few unused tokens at most */
	int i = obj->num_tokens;
	for ( ; i > 0; i-- ) {
		if ( fmt_tok_valid( &obj->tok[i - 1] ) )
			return i;
	}

	return obj->num_tokens;
}

/* Returns object token count excluding the possible token reserve when a parser
   is used */
inline int get_used_token_count( fmt_t *obj )
{
	int count = find_first_unused_token( obj );

	if ( count < 0 )	/* weird, invalid obj pointer? */
		return 0;
	else
		return count;
}

/*
  This searches for a token index in a token list in an efficient way. Return
  value is -1 or token index depending on success.
*/
static int cmp_token( const void *t1, const void *t2 )
{
	int start_1 = ((fmt_tok_t *)t1)->start;
	int start_2 = ((fmt_tok_t *)t2)->start;

	if (start_1 < 0)
		start_1 = INT_MAX;
	if (start_2 < 0)
		start_2 = INT_MAX;

	return start_1 - start_2;
}

int lookup_token_idx( fmt_t *obj, fmt_tok_t *token )
{
	if ( !obj || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !token )
		return LIBFMT_ERR_TOK_INVALID;

	/* If we are dealing with a token from our own token array, we can
	   return the index straight away and go O(1) */
	if ( &obj->tok[0]                 <= token &&
	     &obj->tok[obj->num_tokens-1] >= token )
		return token - &obj->tok[0];

	/*
	  Future optimization possibility: recursive implementation together
	  with loop unwinding (to compromise library size over speed).
	*/
	int token_count = get_used_token_count( obj );

	token = bsearch( token, obj->tok, token_count,
	 		 sizeof(fmt_tok_t), cmp_token );
	if ( !token )
	 	return LIBFMT_ERR_TOK_INVALID;

	return token - &obj->tok[0];
}

inline int dump_add_char( char **buf, size_t *sz, int *pos, char c )
{
	/* If necessary, grow the buffer */
	if ( *sz < *pos + 1 ) {
		*buf = mgrow( *buf, sz );
		if (!*buf)
			return LIBFMT_ERR_REALLOC_JS;
	}

	(*buf)[(*pos)++] = c;	/* Add the char */

	return LIBFMT_ERR_NONE;
}

static inline int dump_add_string( char **buf, size_t *sz, int *pos, char *str )
{
	for ( ; *str; str++ ) {
		int rc = dump_add_char( buf, sz, pos, *str );
		if (rc < 0)
			return rc;
	}
	return LIBFMT_ERR_NONE;
}

static inline int newline( char **buf, size_t *sz, int *pos, int level,
							char *indent )
{
	int rc = dump_add_string( buf, sz, pos, "\r\n" );

	for ( ; rc == 0 && level > 0; level-- )
		rc = dump_add_string( buf, sz, pos, indent );
	return rc;
}

inline int dump_newline( char **buf, size_t *sz, int *pos, int level )
{
	return newline( buf, sz, pos, level, PRETTYDUMP_INDENT );
}

inline int dump_newline_v2( char **buf, size_t *sz, int *pos, int level )
{
	return newline( buf, sz, pos, level, PRETTYDUMP2_INDENT );
}

inline int dump_get_array_size( char *ptr, int level )
{
	char *loc_ptr = ptr;
	int counter = 0;

	while ( *loc_ptr != ']' ) {
		loc_ptr++;
		counter++;
	}

	if ( (PRETTYDUMP2_ARR_SIZE_LIMIT - counter - (8*level)) > 0 )
		return 1;

	return 0;
}

inline int dump_get_obj_size( char *ptr, int level )
{
	char *loc_ptr = ptr;
	int counter = 0;
	int escape = -1;
	int inquotes = 0;

	while ( *loc_ptr != '}' ) {
		loc_ptr++;
		counter++;
		if ( *loc_ptr == '\"' ) {
			if ( (counter - escape) != 1 )
				inquotes = !inquotes;
			continue;
		}
		if ( *loc_ptr == '\\' ) {
			escape = counter; /* position of the counter */
			continue;
		}
		if ( (*loc_ptr == '{') || (*loc_ptr == ',') ) {
			if ( !inquotes )
				return 0;
		}
	}

	if ( (PRETTYDUMP2_ARR_SIZE_LIMIT - counter - (8*level)) > 0 )
		return 1;

	return 0;
}

/*
  This function deals with unarranged token list after setting (adding) a new
  object.
*/
void fix_tokens_after_append( fmt_t *obj,
				int prev_idx, int parent_idx, int pos,
				size_t added_count, size_t added_size,
				int with_key )
{
	if ( !obj )
		return;

	int new_parent_idx = prev_idx + 1 + with_key;
	int new_parent_idx_off = with_key;
	/* Adjust the newly added tokens */
	int i;
	for ( i = prev_idx + 1 + with_key;
		i < prev_idx + 1 + with_key + added_count;
		i++ )
	{
		obj->tok[i].start  += pos;
		obj->tok[i].end    += pos;
		if ( new_parent_idx_off > 0 )
			new_parent_idx_off--;
		else
			obj->tok[i].parent += new_parent_idx;
	}

	/* Adjust all tokens after the token where addition took place */
	for ( ; i < obj->num_tokens; i++ ) {
		/* don't touch unused tokens */
		if ( !fmt_tok_valid( &obj->tok[i]) )
			continue;
		obj->tok[i].start += added_size;
		obj->tok[i].end   += added_size;
		/* fix parents if needed */
		if ( obj->tok[i].parent > parent_idx )
			obj->tok[i].parent += added_count + with_key;
	}

	/* Adjust all parent tokens */
	/* O(n) :( */
	for ( i = 0; parent_idx > 0 && i < parent_idx; i++ )
		if ( obj->tok[i].start < obj->tok[parent_idx].start &&
		     obj->tok[i].end   > obj->tok[parent_idx].end )
			obj->tok[i].end += added_size;

	/* Adjust the token where addition took place */
	obj->tok[parent_idx].end  += added_size;
	obj->tok[parent_idx].size += with_key + 1; /* key + value */

	/* update parser index if any */
	if ( fmt_parser_valid( obj ) == LIBFMT_TRUE )
		obj->parser.toknext += added_count + with_key;

}

/*
  Returns last subtoken index of a parent token. For empty parent tokens it is
  the parent token itself.
*/
int find_last_subtok( fmt_t *obj, int parent_idx )
{
	int idx;

	/* O(n) :( */
	for ( idx = parent_idx; idx < obj->num_tokens; idx++ )
		if ( obj->tok[parent_idx].start > obj->tok[idx].start ||
		     obj->tok[parent_idx].end   < obj->tok[idx].end )
			break;

	return MAX(0, idx - 1);
}

int parser_init( fmt_t *obj, uint32_t size )
{
	if ( !obj )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( size < LIBFMT_TOK_COUNT_MIN )
		size = LIBFMT_TOK_COUNT_MIN;

	if ( size > LIBFMT_TOK_COUNT_MAX )
		size = LIBFMT_TOK_COUNT_MAX;

	obj->js = NULL;
	obj->num_tokens = size;
	obj->type = FMT_TYPE_PARSER;

	obj->tok = (fmt_tok_t *)malloc( obj->num_tokens * sizeof(fmt_tok_t) );
	if ( obj->tok == NULL )
		return LIBFMT_ERR_MALLOC;

	/* initialize tokens, otherwise valgrind complains */
	mark_token_unused( obj->tok, obj->num_tokens );

	jsmn_init( &obj->parser );

	return LIBFMT_ERR_NONE;
}

int fmt_load_normalized_new(char *iobuf, size_t size)
{
	int i, shift = 0, inq = 0, escape = 0;
	char symb;

	if(!iobuf || size < 1)
		return LIBFMT_ERR_GENERIC;

	for(i = 0; i < size; i++)
	{
		symb = *iobuf;

		if(symb == '\\')
			escape = 1; // escape set

		if(symb == '"' && !escape)
			inq = !inq;

		if(symb == '\0') {
			if(inq)
				return LIBFMT_ERR_NULLMET;
			else
				break;
		}

		if((symb == '\n' ||
		    symb == '\r' ||
		    symb == '\t' ||
		    symb == ' ') && !inq)
		{
			shift++;
			goto next;
		}

		// else add simbol
		*(iobuf - shift) = symb;

		if(symb != '\\')
			escape = 0; // escape reset
next:
		iobuf++;
	}
	*(iobuf - shift) = 0;

	return LIBFMT_ERR_NONE;
}

int fmt_new( const char *s, int len, fmt_type_t type, fmt_t *res )
{
	if ( !res )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !s || len < 1 )
		return LIBFMT_ERR_GENERIC;

	res->tok = (fmt_tok_t *)malloc( sizeof(fmt_tok_t) );
	if ( res->tok == NULL )
		return LIBFMT_ERR_MALLOC;

	res->js = (char *)malloc( len + 1 );
	if ( res->js == NULL ) {
		free( res->tok );
		return LIBFMT_ERR_MALLOC;
	}

	if ( type == FMT_TYPE_STRING )
		fmt_escape_string( s, &res->js, &len );
	else
		memcpy( res->js, s, len );

	res->num_tokens  = 1;
	res->type        = FMT_TYPE_UNDEF;

	switch (type) {
		case FMT_TYPE_OBJECT:
			res->tok->type = JSMN_OBJECT;
			break;
		case FMT_TYPE_ARRAY:
			res->tok->type = JSMN_ARRAY;
			break;
		case FMT_TYPE_STRING:
			res->tok->type = JSMN_STRING;
			break;
		case FMT_TYPE_NUMBER:
		case FMT_TYPE_NULL:
		case FMT_TYPE_BOOL:
			res->tok->type = JSMN_PRIMITIVE;
			break;
		default:
			free( res->tok );
			free( res->js );
			return LIBFMT_ERR_GENERIC;
	}

	res->tok->start  = type == FMT_TYPE_STRING? 1: 0;
	res->tok->end    = len;
	res->tok->size   = 0;
	res->tok->parent = -1;

	if ( type == FMT_TYPE_STRING )
		res->js[res->tok->end +1] = '\0';
	else
		res->js[res->tok->end] = '\0';

	mark_parser_unused( res );
	return LIBFMT_ERR_NONE;
}

fmt_t *fmt_new_alloc( const char *s, int len, fmt_type_t type )
{
	fmt_t *res = (fmt_t *)malloc( sizeof(fmt_t) );
	if ( res == NULL )
		return NULL;

	if ( fmt_new( s, len, type, res ) ) {
		free( res );
		return NULL;
	}

	res->type = type;

	return res;
}

int fmt_escape_string( const char *src, char **dst, int *dstlen )
{
	int newlen = 0;

	**dst = '"';
	newlen++;
	while ( *src != '\0' ) {
		if ( newlen + 1 >= *dstlen )
			*dst = (char *)realloc( *dst, newlen + 1 );
		if ( *src == '"' || *src == '\\' ) {
			*(*dst + newlen) = '\\';
			newlen++;
			if ( newlen + 1 >= *dstlen )
				*dst = (char *)realloc( *dst, newlen + 1 );
		}
		*(*dst + newlen) = *src;
		newlen++;
		src++;
	}

	if ( newlen + 3 > *dstlen )
		*dst = (char *)realloc( *dst, newlen + 3 );
	*(*dst + newlen) = '"';

	*dstlen = newlen;

	return LIBFMT_ERR_NONE;
}

int fmt_unescape_string( const char *src, int srclen, char **dst )
{
	char *tmp = NULL;
	char *dststart = NULL;
	char *tmpstart = NULL;

	*dst = (char *)malloc( srclen + 1 );
	dststart = *dst;

	tmp = strndup( src, srclen );
	tmpstart = tmp;

	while ( *tmp != '\0' ) {
		if ( *tmp == '\\' )
			tmp++;
		**dst = *tmp;
		(*dst)++;
		tmp++;
	}

	**dst = '\0';
	*dst = dststart;
	tmp = tmpstart;

	free(tmp);

	return LIBFMT_ERR_NONE;
}

static uint64_t hash64( const char *buf, size_t len )
{
	/* http://www.random.org/cgi-bin/randbyte?nbytes=16&format=h */
	char key[16] = { 0xf5, 0x7c, 0x53, 0x74, 0x92, 0x23, 0x39, 0x7c,
			 0xcd, 0xe9, 0x05, 0xfb, 0xc0, 0xf1, 0x3a, 0xc6 };

	return siphash24( buf, len, key );
}

static uint32_t crc32( const char *buf, size_t len )
{
	return 0xef87ef98;
}

int fmt_cscmp( fmt_checksum_t *cs1, fmt_checksum_t *cs2 )
{
	if ( !cs1 || !cs2 )
		return LIBFMT_ERR_GENERIC;

	if ( cs1->buflen   != cs2->buflen   ||
	     cs1->tok_used != cs2->tok_used ||
	     cs1->siphash  != cs2->siphash  ||
	     cs1->crc      != cs2->crc )
		return LIBFMT_ERR_GENERIC;

	return LIBFMT_ERR_NONE;
}

int fmt_cscalc( fmt_t *obj, fmt_checksum_t *res )
{
	if ( !obj || !obj->js || !res )
		return LIBFMT_ERR_OBJ_INVALID;

	fmt_stats_t stats;
	if ( fmt_stats( obj, &stats ) )
		return LIBFMT_ERR_GENERIC;

	res->buflen   = stats.dumplen;
	res->tok_used = stats.tok_used;
	res->siphash  = hash64( obj->js, stats.dumplen );
	res->crc      = crc32( obj->js, stats.dumplen );

	/* TODO: per pair (key:value) recursive hashing and then mix (xor?)
	 * them all to enable object location independent checksum */

	return LIBFMT_ERR_NONE;
}

int fmt_next( fmt_t *obj, fmt_tok_t *tok, fmt_tok_t *next,
				char **key, fmt_type_t type )
{
	if ( !obj || !obj->js || !obj->tok )
		return LIBFMT_ERR_OBJ_INVALID;

	if ( !next )
		return LIBFMT_ERR_TOK_INVALID;

	if ( next->end > obj->tok->end )
		return LIBFMT_ERR_TOK_INVALID;

	if ( type != FMT_TYPE_OBJECT && type != FMT_TYPE_ARRAY )
		return LIBFMT_ERR_TYPE_INVALID;

	int i = 0;
	int size = 0;
	int parent = 0;
	fmt_tok_t *o;

	if ( !tok )
		o = obj->tok;
	else
		o = tok;

	if ( type == FMT_TYPE_OBJECT )
		size = fmt_object_size( obj, o );
	else
		size = fmt_array_size( obj, o );

	/* check for invalid object/array */
	if ( size < 0 )
		return LIBFMT_ERR_GENERIC;

	/* return early if object/array is empty */
	if ( size < 1 )
		return LIBFMT_ERR_NONE;

	/* initialize next if it's not sane */
	/* NOTE: if next is not initialized then valgrind complains here
	   e.g.: Uninitialised value was created by a stack allocation */
	if ( !fmt_tok_valid( next ) )
		memcpy( next, o, sizeof(fmt_tok_t) );

	if ( tok )
		i = lookup_token_idx( obj, tok );

	if ( i < 0 )
		return i;

	parent = i;
	for ( ; i < get_used_token_count( obj ); i++ ) {
		/* fast forward, works even better than saving start
		 * position and doesn't break array iteration */
		/* FIXME: ezjson uses fmt_array_next() and somehow
		 * breaks here so check if we work with object for now */
		if ( type == FMT_TYPE_OBJECT && parent != obj->tok[i].parent )
		 	continue;

		/* ensure we don't look at tokens which
		   start outside our object/array or end before it */
		if ( obj->tok[i].start > o->end )
			break;
		if ( obj->tok[i].end < o->start )
			continue;

		/* skip object/array itself too */
		if ( obj->tok[i].start == o->start || obj->tok[i].end == o->end )
			continue;

		/* skip next initialized as object/array and tokens already seen */
		if ( obj->tok[i].start <= next->start )
			continue;

		if ( (obj->tok[i].start < next->end) &&
						(o->start != next->start) )
			continue;

		/* we have only token type to rely on in case of object */
		if ( type == FMT_TYPE_OBJECT ) {
			if ( !fmt_tok_is_string(&obj->tok[i]) )
				continue;
			if ( key && fmt_dump_string( obj, &obj->tok[i], key ) < 0 )
				return LIBFMT_ERR_GENERIC;
			i++;	/* advance to value */
		}

		/* ok, seems we found it */
		memcpy( next, obj->tok + i, sizeof(fmt_tok_t) );
		return 1;
	}

	return LIBFMT_ERR_NONE;
}
