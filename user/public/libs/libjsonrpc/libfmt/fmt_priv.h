/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#include "libfmt.h"

#define PRETTYDUMP_INDENT		"    "
#define PRETTYDUMP2_INDENT		"\t"
#define PRETTYDUMP2_ARR_SIZE_LIMIT	160

typedef struct fmt_norm_t {
	int size;
	int last;
} fmt_norm_t;


extern void mark_parser_unused( fmt_t *obj );
extern void mark_token_unused( fmt_tok_t *tok, int count );
extern int find_first_unused_token( fmt_t *obj );
extern int get_used_token_count( fmt_t *obj );

int lookup_token_idx( fmt_t *obj, fmt_tok_t *token );

extern int dump_add_char( char **buf, size_t *sz, int *pos, char c );
extern int dump_newline( char **buf, size_t *sz, int *pos, int level );

extern int dump_newline_v2( char **buf, size_t *sz, int *pos, int level );
extern int dump_get_array_size( char *ptr, int level );
extern int dump_get_obj_size( char *ptr, int level );

void fix_tokens_after_append( fmt_t *obj,
				int prev_idx, int parent_idx, int pos,
				size_t added_count, size_t added_size,
				int with_key );
int find_last_subtok( fmt_t *obj, int parent_idx );

/**
 * @brief Initialize JSON parser
 *
 * This function creates an object \ref fmt_t which must be freed
 * with \ref fmt_free().
 *
 * @param  p     pointer to \ref fmt_t structure to be used as parser
 * @param  size  parser configuration
 *             - initial token count parser will be able to process
 *               without excess memory reallocation. If defined token count
 *               is not enough to parse json string/file more tokens
 *               will be allocated dynamically. One may want to use 0
 *               to optimize memory usage.
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int parser_init( fmt_t *p, uint32_t size );
int fmt_load_normalized_new(char *iobuf, size_t size);

int fmt_new( const char *s, int len, fmt_type_t type, fmt_t *res );
fmt_t *fmt_new_alloc( const char *s, int len, fmt_type_t type );

int fmt_escape_string( const char *src, char **dst, int *dstlen );
int fmt_unescape_string( const char *src, int srclen, char **dst );

int fmt_cscmp( fmt_checksum_t *cs1, fmt_checksum_t *cs2 );
int fmt_cscalc( fmt_t *obj, fmt_checksum_t *res );

int fmt_next( fmt_t *obj, fmt_tok_t *tok, fmt_tok_t *next,
				char **key, fmt_type_t type );
