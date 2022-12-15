/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#ifndef LIBFMT_H
#define LIBFMT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <jsmn.h>

#define LIBFMT_VERSION		"0.4.8"
#define LIBFMT_FILE_READ_BLOCK	1024
#define LIBFMT_LOCK_DONTUSE	0x01
#define LIBFMT_PRETTY_DUMP	0x02 /* pretty dump */
#define LIBFMT_DUMP_COMPACT	0x04 /* compact pretty dump */
#define LIBFMT_TOK_COUNT_MIN	3 /* minimal json would be e.g.*/
#define LIBFMT_TOK_COUNT_MAX	2097152 /* 32MiB + 28 bytes + json string itself */

#define LIBFMT_TRUE			1
#define LIBFMT_FALSE			0
#define LIBFMT_ERR_NONE			0
#define LIBFMT_ERR_GENERIC		-1
#define LIBFMT_ERR_MALLOC		-2
#define LIBFMT_ERR_REALLOC_JS		-3
#define LIBFMT_ERR_REALLOC_TOK		-4
#define LIBFMT_ERR_STRNDUP		-5
#define LIBFMT_ERR_NULLMET		-6
#define LIBFMT_ERR_PARSER		-9
#define LIBFMT_ERR_TOK_INVALID		-10
#define LIBFMT_ERR_OBJ_INVALID		-11
#define LIBFMT_ERR_KEY_INVALID		-12
#define LIBFMT_ERR_TYPE_INVALID		-13
#define LIBFMT_ERR_FILE_OPEN		-20
#define LIBFMT_ERR_FILE_CLOSE		-21
#define LIBFMT_ERR_FILE_SEEK		-22

typedef jsmn_parser fmt_parser;
typedef jsmntok_t   fmt_tok_t;
// typedef struct fmt_tok_t {
// 	jsmntok_t tok;
// 	int       idx;
// } fmt_tok_t;

typedef enum {
	FMT_TYPE_UNDEF,
	FMT_TYPE_OBJECT,
	FMT_TYPE_ARRAY,
	FMT_TYPE_STRING,
	FMT_TYPE_NUMBER,
	FMT_TYPE_NULL,
	FMT_TYPE_BOOL,
	FMT_TYPE_PARSER,
	FMT_TYPE_COPY,
	FMT_TYPE_FREED = 0xdeadbeef
} fmt_type_t;

typedef struct fmt_t {
	fmt_parser parser;
	char      *js;
	fmt_tok_t *tok;
	uint32_t   num_tokens;
	fmt_type_t type;
} fmt_t;

typedef struct fmt_stats_t {
	uint32_t tok_count;
	uint32_t tok_used;
	size_t   memsize;
	size_t   dumplen;
} fmt_stats_t;

typedef struct fmt_checksum_t {
	size_t buflen;
	uint32_t tok_used;
	uint64_t siphash;
	uint32_t crc;
} fmt_checksum_t;

#ifdef __cplusplus

#define FMT_ZEROCS { 0, 0, 0, 0 }
#define FMT_NULL { { 0, 0, 0 }, NULL, NULL, 0, FMT_TYPE_UNDEF }
#define FMT_TOK_NULL { (jsmntype_t)-1, -1, -1, -1, -1 }

#else // #ifdef __cplusplus

#define FMT_ZEROCS {			\
	.buflen   = 0,			\
	.tok_used = 0,			\
	.siphash  = 0,			\
	.crc      = 0			\
}

#define FMT_NULL {			\
	.js         = NULL,		\
	.tok        = NULL,		\
	.num_tokens = 0,		\
	.type       = FMT_TYPE_UNDEF	\
}

#define FMT_TOK_NULL {			\
	.type   = -1,			\
	.start  = -1,			\
	.end    = -1,			\
	.size   = -1,			\
	.parent = -1			\
}

#endif // #ifdef __cplusplus

#include "ezjson.h"


int fmt_parser_init( fmt_t *p, uint32_t size )__attribute__((deprecated));

/**
 * @brief Load parser, reading data from string
 *
 * @param  buf  pointer to string containing the data to be parsed
 * @param  size data length in bytes
 * @param  p    pointer to \ref fmt_t parser structure to load
 *              the string into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_load_string( char *buf, size_t size, fmt_t *p );

/**
 * @brief Load parser, reading data from a file pointer
 *
 * @param  fp previously initialized file pointer
 * @param  p  pointer to \ref fmt_t parser structure
 *            to load the data into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_load_fp( FILE **fp, fmt_t **p );

/**
 * @brief Load parser, reading data from a file
 *
 * @param  file  pointer to a string containing path to a data file
 * @param  p     pointer to \ref fmt_t parser structure
 *               to load the data into
 * @param  flags flags bitmask
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_load_file( const char *file, fmt_t *p, uint32_t flags );

/**
 * @brief Create empty JSON object
 *
 * Initializes given \ref fmt_t structure and creates empty object.
 * res must be freed with \ref fmt_free()
 *
 * @param  res pointer to \ref fmt_t structure to initialize
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_object( fmt_t *res );

/**
 * @brief Create empty JSON object
 *
 * Allocates memory in heap, initializes it and creates empty object.
 * Returned value must be freed with \ref fmt_free()
 *
 * @return pointer to \ref fmt_t on success, NULL otherwise
 */
fmt_t *fmt_object_alloc( void );

/**
 * @brief Create empty JSON array
 *
 * Initializes given \ref fmt_t structure and creates empty array.
 * res must be freed with \ref fmt_free()
 *
 * @param  res pointer to \ref fmt_t structure to initialize
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_array( fmt_t *res );

/**
 * @brief Create empty JSON array
 *
 * Allocates memory in heap, initializes it and creates empty array.
 * Returned value must be freed with \ref fmt_free()
 *
 * @return pointer to \ref fmt_t on success, NULL otherwise
 */
fmt_t *fmt_array_alloc( void );

/**
 * @brief Create string JSON object
 *
 * Returns a pointer to \ref fmt_t containing given string.
 * Result must be freed with \ref fmt_free()
 *
 * @param  s pointer to string to put into the object
 *
 * @return pointer to \ref fmt_t on success, NULL otherwise
 */
fmt_t *fmt_string( const char *s );

/**
 * @brief Create string JSON object
 *
 * Returns a pointer to \ref fmt_t containing given string.
 * Result must be freed with \ref fmt_free
 *
 * @param format pointer to string containing format (see printf for example)
 * @param ...    format arguments (see `man fprintf' for reference)
 *
 * @return pointer to \ref fmt_t on success, NULL otherwise
 */
fmt_t *fmt_stringf( const char *format, ... );

fmt_t *fmt_primitive( const char *prim, int len, fmt_type_t type );

/**
 * @brief Create JSON null object
 *
 * Returns a pointer to \ref fmt_t containing JSON null.
 * Result must be freed with \ref fmt_free()
 *
 * @return pointer to \ref fmt_t on success, NULL otherwise
 */
fmt_t *fmt_null( void );

/**
 * @brief Create JSON bool object
 *
 * Returns a pointer to \ref fmt_t containing JSON true or false.
 * Result must be freed with \ref fmt_free()
 *
 * @param  b bool valie, one of LIBFMT_TRUE or LIBFMT_FALSE
 *
 * @return pointer to \ref fmt_t on success, NULL otherwise
 */
fmt_t *fmt_bool( int b );

/**
 * @brief Extract a token data from given, previously parsed or generated JSON
 *
 * Extraction means creating a \ref fmt_t filled with token data and
 * correctly filled subtoken data, so that the result can further be used as
 * any other parsed or created JSON. The result contains all the needed data,
 * including the string itself, so the previous \ref fmt_t structure
 * can safely be freed if needed.
 *
 * @param  p    pointer to \ref fmt_t parser structure
 *              to extract the data from
 * @param  from pointer to \ref fmt_tok_t structure to translate from, may be
 *              NULL or any type of JSON token
 * @param  to   pointer to \ref fmt_t structure to translate to
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_tok_to_fmt( fmt_t *p, fmt_tok_t *from, fmt_t *to );

/**
 * @brief Copy data from given, previously parsed or generated JSON
 *
 * @param  from pointer to \ref fmt_t structure to copy data from
 * @param  to   pointer to \ref fmt_t structure to copy data to
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_copy( fmt_t *from, fmt_t *to );

/**
 * @brief Copy data from given, previously parsed or generated JSON
 *        allocating needed memory.
 *
 * Returns a pointer to \ref fmt_t containing copied object.
 * Result must be freed with \ref fmt_free()
 *
 * @param  from  pointer to \ref fmt_t structure to copy data from
 * @param  where pointer to \ref fmt_tok_t structure to copy data from
 *
 * @return pointer to \ref fmt_t on success, NULL otherwise
 */
fmt_t *fmt_copy_dup( fmt_t *from, fmt_tok_t *where );

/**
 * @brief Free \ref fmt_t structure
 *
 * Deallocates any type of \ref fmt_t created by \ref fmt_object()
 * or other means. May safely be called on an already freed object.
 *
 * @param  obj pointer to \ref fmt_t structure to free
 *
 * @return LIBFMT_ERR_NONE only (always successful)
 */
int fmt_free( fmt_t *obj );

/**
 * @brief Find a key in an object
 *
 * Finds a given key in an object in a given, previously loaded \ref fmt_t
 *
 * @param  p     pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t, where to look for given key (may be NULL)
 * @param  key   pointer to a string containing key name to search for
 * @param  res   pointer to \ref fmt_tok_t structure to save found token into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_get_tok( fmt_t *p, fmt_tok_t *where, const char *key, fmt_tok_t *res );

/**
 * @brief Find a key path in an object
 *
 * Finds keys from path recursively in an object in a given,
 * previously loaded \ref fmt_t
 *
 * @param  p     pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t, where to look for given key (may be NULL)
 * @param  path  pointer to an array of strings containing key names
 *               to search for, must be null terminated
 * @param  res   pointer to \ref fmt_tok_t structure to save found token into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_get_tok_path( fmt_t *p, fmt_tok_t *where,
					const char **path, fmt_tok_t *res );

/**
 * @brief Find a key in an object
 *
 * Finds a given key in an object in a given, previously loaded \ref fmt_t
 * and creates a copy of data found and all subtokens information
 *
 * @param  p     pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t, where to look for given key (may be NULL)
 * @param  key   pointer to a string containing key name to search for
 * @param  res   pointer to \ref fmt_t structure to save found
 *               data and subtokens into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_get( fmt_t *p, fmt_tok_t *where, const char *key, fmt_t *res );

/**
 * @brief Find a key path in an object
 *
 * Finds keys from path recursively in an object in a given,
 * previously loaded \ref fmt_t and creates a copy of data found
 * and all subtokens information
 *
 * @param  p     pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t, where to look for given key (may be NULL)
 * @param  path  pointer to an array of strings containing key names
 *               to search for, must be null terminated
 * @param  res   pointer to \ref fmt_t structure to save found
 *               data and subtokens into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_get_path( fmt_t *p, fmt_tok_t *where, const char **path, fmt_t *res );

/**
 * @brief Find a key representing a string in an object
 *
 * Finds a given key in an object in a given, previously loaded, \ref fmt_t.
 * Returns error if key is not a string.
 *
 * @param  p     pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t, where to look for given key (may be NULL)
 * @param  key   pointer to a string containing key name to search for
 * @param  res   pointer to char to save the result into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_get_string( fmt_t *p, fmt_tok_t *where, const char *key, char **res );

/**
 * @brief Find a key path representing a string in an object
 *
 * Finds a given key path in an object in a given,
 * previously loaded, \ref fmt_t. Returns error if key is not a string.
 *
 * @param  p     pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t, where to look for given key (may be NULL)
 * @param  path  pointer to an array of strings containing key names
 *               to search for, must be null terminated
 * @param  res   pointer to char to save the result into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_get_string_path( fmt_t *p, fmt_tok_t *where,
					const char **path, char **res );

/**
 * @brief Find a key in an object and delete it
 *
 * Deletes a given key and all associated data and token information
 * from a given object.
 *
 * @param  obj   pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t, where to look for given key (may be NULL)
 * @param  key   pointer to char containing key name
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_del( fmt_t *obj, fmt_tok_t *where, const char *key );

/**
 * @brief Find a key path in an object and delete the last one
 *
 * Deletes the last key from a given key path and all associated data
 * and token information from a given object.
 *
 * @param  obj   pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t, where to look for given key (may be NULL)
 * @param  path  pointer to an array of strings containing key names
 *               to search for, must be null terminated
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_del_path( fmt_t *obj, fmt_tok_t *where,	const char **path );

/**
 * @brief Verify if token is JSON object
 *
 * @param  tok pointer to \ref fmt_tok_t structure to verify
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_tok_is_object( fmt_tok_t *tok );

/**
 * @brief Verify if \ref fmt_t object is JSON object
 *
 * @param  obj pointer to \ref fmt_t structure to verify
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_is_object( fmt_t *obj );

/**
 * @brief Verify if token is JSON array
 *
 * @param  tok pointer to \ref fmt_tok_t structure to verify
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_tok_is_array( fmt_tok_t *tok );

/**
 * @brief Verify if \ref fmt_t object is JSON array
 *
 * @param  obj pointer to \ref fmt_t structure to verify
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_is_array( fmt_t *obj );

/**
 * @brief Verify if token is JSON string
 *
 * @param  tok pointer to \ref fmt_tok_t structure to verify
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_tok_is_string( fmt_tok_t *tok );

/**
 * @brief Verify if \ref fmt_t object is JSON string
 *
 * @param  obj pointer to \ref fmt_t structure to verify
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_is_string( fmt_t *obj );

/**
 * @brief Verify if token from a given \ref fmt_t is JSON null
 *
 * @param  p   pointer to \ref fmt_t structure,
 *             previously loaded with data via parser or generator
 * @param  tok pointer to \ref fmt_tok_t structure to verify (may be NULL)
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_is_null( fmt_t *p, fmt_tok_t *obj );

/**
 * @brief Verify if token from a given \ref fmt_t is JSON true or false
 *
 * @param  p   pointer to \ref fmt_t structure,
 *             previously loaded with data via parser or generator
 * @param  tok pointer to \ref fmt_tok_t structure to verify (may be NULL)
 * @param  tf  LIBFMT_TRUE or LIBFMT_FALSE - bool value to be compared with
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_is_bool( fmt_t *p, fmt_tok_t *obj, int tf );

/**
 * @brief Verify if token from a given \ref fmt_t is JSON primitive
 *
 * JSON primitive is a bool, null or a number.
 *
 * @param  obj pointer to \ref fmt_t structure,
 *             previously loaded with data via parser or generator
 * @param  tok pointer to \ref fmt_tok_t structure to verify (may be NULL)
 * @param  val pointer to a string to compare with primitive (may be NULL)
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_is_primitive( fmt_t *obj, fmt_tok_t *tok, const char *val );

/**
 * @brief Validate token structure
 *
 * @param  tok pointer to \ref fmt_tok_t structure to validate
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_tok_valid( fmt_tok_t *tok );

/**
 * @brief Validate parser
 *
 * @param  obj pointer to \ref fmt_t structure to validate
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
extern int fmt_parser_valid( fmt_t *obj );

/**
 * @brief Find token parent
 *
 * @param  obj   pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  child pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t
 * @param  res   pointer to \ref fmt_tok_t structure to save found
 *               parent token data to
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_get_tok_parent( fmt_t *obj, fmt_tok_t *child, fmt_tok_t *res );

/**
 * @brief Calculate \ref fmt_t statistics
 *
 * Calculate memory and token usage and JSON string length
 * of given \ref fmt_t
 *
 * @param  obj   pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  res   pointer to \ref fmt_stats_t structure to save statistics
 *               data to
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_stats( fmt_t *obj, fmt_stats_t *res );

int fmt_checksum( fmt_t *obj, fmt_checksum_t *cs );

/**
 * @brief Get JSON object key count
 *
 * @param  obj   pointer to \ref fmt_t structure representing an object
 * @param  where pointer to object \ref fmt_tok_t structure to count keys in
 *               (may be NULL)
 *
 * @return object key count on success, negative error code otherwise
 */
int fmt_object_size( fmt_t *obj, fmt_tok_t *where );

/**
 * @brief Get JSON array element count
 *
 * @param  arr pointer to \ref fmt_tok_t structure representing an array
 *
 * @return array element count on success, negative error code otherwise
 */
int fmt_array_size( fmt_t *obj, fmt_tok_t *arr );

/**
 * @brief Get next token from JSON array
 *
 * @param  obj  pointer to \ref fmt_t structure,
 *              previously loaded with data via parser or generator
 * @param  arr  pointer to \ref fmt_tok_t structure representing an array
 *              to get next element from (may be NULL)
 * @param  next pointer to \ref fmt_tok_t structure to save next element to
 *
 * @return 1 on success (something is saved in next),
 *         0 if there is nothing to save (empty object or end of array),
 *        -1 on error
 */
int fmt_array_next( fmt_t *obj, fmt_tok_t *arr, fmt_tok_t *next );

/**
 * @brief Get next key value token from JSON object
 *
 * @param  obj   pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t structure representing an object
 *               to get next element from (may be NULL)
 * @param  next  pointer to \ref fmt_tok_t structure to save next key vaue to
 * @param  key   double pointer to a string to save key name into
 *
 * @return 1 on success (something is saved in next),
 *         0 if there is nothing to save (empty object or end of object),
 *        -1 on error
 */
int fmt_object_next( fmt_t *obj, fmt_tok_t *where,
						fmt_tok_t *next, char **key );

/**
 * @brief Add a key to JSON object
 *
 * Appends new key to given object. Doesn't search for existing keys.
 *
 * @param  obj pointer to \ref fmt_t structure,
 *             previously loaded with data via parser or generator
 * @param  key pointer to a string containing new key name
 * @param  val pointer to an object containing value for a new key
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_set( fmt_t *obj, const char *key, fmt_t *val );

/**
 * @brief Add a key to JSON object at certain location
 *
 * Appends new key to given object. Doesn't search for existing keys.
 *
 * @param  obj   pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t, where to append the key (may be NULL)
 * @param  key   pointer to a string containing new key name
 * @param  val   pointer to an object containing value for a new key
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_set_at( fmt_t *obj, fmt_tok_t *where, const char *key, fmt_t *val );

/**
 * @brief Add a key to JSON object freeing added key value
 *
 * Appends new key to given object and frees appended key value.
 * Doesn't search for existing keys.
 *
 * @param  obj  pointer to \ref fmt_t structure,
 *              previously loaded with data via parser or generator
 * @param  key  pointer to a string containing new key name
 * @param  val  pointer to an object containing value for a new key
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_set_new( fmt_t *obj, const char *key, fmt_t *val );

/**
 * @brief Add a key to JSON object at certain location freeing added key value
 *
 * Appends new key to given object at certain location and frees
 * appended key value. Doesn't search for existing keys.
 *
 * @param  obj   pointer to \ref fmt_t structure,
 *               previously loaded with data via parser or generator
 * @param  where pointer to \ref fmt_tok_t object, previously found in given
 *               \ref fmt_t, where to append the key (may be NULL)
 * @param  key   pointer to a string containing new key name
 * @param  val   pointer to an object containing value for a new key
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_set_new_at( fmt_t *obj, fmt_tok_t *where, const char *key, fmt_t *val );

/**
 * @brief Update a key in JSON object with new value
 *
 * Updates given key in an object with new value.
 *
 * @param  obj    pointer to \ref fmt_t structure,
 *                previously loaded with data via parser or generator
 * @param  key    pointer to a string containing new key name
 * @param  newval pointer to an object containing value for a new key, it is
 *                freed after successfull update
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_update( fmt_t *obj, const char *key, fmt_t *newval );

/**
 * @brief Update a key in JSON object with new value
 *
 * Updates given key in an object with new value.
 *
 * @param  obj    pointer to \ref fmt_t structure,
 *                previously loaded with data via parser or generator
 * @param  where  pointer to \ref fmt_tok_t object, previously found in given
 *                \ref fmt_t, where to append the key (may be NULL)
 * @param  key    pointer to a string containing new key name
 * @param  newval pointer to an object containing value for a new key, it is
 *                freed after successfull update
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_update_at( fmt_t *obj, fmt_tok_t *where, const char *key, fmt_t *newval );

/**
 * @brief Add new element to JSON array
 *
 * @param  arr pointer to \ref fmt_t structure representing JSON array
 *             to append new element into
 * @param  el  pointer to \ref fmt_t structure containing value
 *             for a new element
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_array_add( fmt_t *arr, fmt_t *el );

/**
 * @brief Add new element to JSON array in JSON object
 *
 * @param  obj pointer to \ref fmt_t structure,
 *             previously loaded with data via parser or generator
 * @param  arr pointer to \ref fmt_tok_t structure representing JSON array
 *             to append new element into
 * @param  el  pointer to \ref fmt_t structure containing value
 *             for a new element
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_array_add_at( fmt_t *obj, fmt_tok_t *arr, fmt_t *el );

/**
 * @brief Add new element to JSON array, freeing added value
 *
 * @param  arr pointer to \ref fmt_t structure representing JSON array
 *             to append new element into
 * @param  el  pointer to \ref fmt_t structure containing value
 *             for a new element
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_array_add_new( fmt_t *arr, fmt_t *el );

/**
 * @brief Add new element to JSON array in JSON object, freeing added value
 *
 * @param  obj pointer to \ref fmt_t structure,
 *             previously loaded with data via parser or generator
 * @param  arr pointer to \ref fmt_tok_t structure representing JSON array
 *             to append new element into
 * @param  el  pointer to \ref fmt_t structure containing value
 *             for a new element
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_array_add_new_at( fmt_t *obj, fmt_tok_t *arr, fmt_t *el );

/**
 * @brief Get string value from JSON string
 *
 * @param  obj pointer to \ref fmt_t structure,
 *             previously loaded with data via parser or generator
 * @param  tok pointer to \ref fmt_tok_t object, previously found in given
 *             \ref fmt_t, representing JSON string (may be NULL)
 * @param  res pointer to a string to write the result into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_string_value( fmt_t *obj, fmt_tok_t *tok, char **res );

/**
 * @brief Get string representation of any JSON object
 *
 * @param  obj pointer to \ref fmt_t structure,
 *             previously loaded with data via parser or generator
 * @param  tok pointer to \ref fmt_tok_t object, previously found in given
 *             \ref fmt_t (may be NULL)
 * @param  res pointer to a string to write the result into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_pretty_dump( fmt_t *p, fmt_tok_t *obj, char **res );
/**
 * @brief Alternative version of fmt_pretty_dump()
 *        which generates more compact output.
 */
int fmt_pretty_dump_v2( fmt_t *p, fmt_tok_t *obj, char **res );

/**
 * @brief Calculate the length of normalized JSON
 *
 * Normalized means without any whitespaces
 * and other special symbols as \n or \r
 *
 * @param  obj pointer to \ref fmt_t structure,
 *             previously loaded with data via parser or generator
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
extern size_t fmt_dump_len( fmt_t *obj );

/**
 * @brief Dump any JSON object or it's part into a string
 *
 * @param  obj pointer to \ref fmt_t structure,
 *             previously loaded with data via parser or generator
 * @param  tok pointer to \ref fmt_tok_t object, previously found in given
 *             \ref fmt_t (may be NULL)
 * @param  res pointer to a string to write the result into
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_dump_string( fmt_t *obj, fmt_tok_t *tok, char **res );

/**
 * @brief Dump object into a file
 *
 * @param obj   pointer to an object to dump
 * @param res   pointer to a string containing file path to save
 *              given object string representation into
 * @param flags flags bitmask
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_dump_file( fmt_t *obj, const char *path, uint32_t flags );

/**
 * @brief Add 'fmt_u' to 'fmt' at 'path'. If path doesn't exist or
 * 		exist partially, function will recreate this path
 *
 * @param fmt	pointer to fmt object to addit
 * @param path	path to recreate
 * @param fmt_u	fmt object to add. Will be freed on any condition
 *
 * @return LIBFMT_ERR_NONE on success, negative error code otherwise
 */
int fmt_update_create_path_new(fmt_t *fmt, char **path, fmt_t *fmt_u);

/**
 * @brief Check: is object initilaized ?
 *
 * @param obj   pointer to an object to check
 *
 * @return LIBFMT_TRUE on success, LIBFMT_FALSE otherwise
 */
int fmt_is_initialized( fmt_t *obj );

#ifdef __cplusplus
} //close extern "C"
#endif

#endif /* LIBFMT_H */
