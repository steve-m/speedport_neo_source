/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/param.h>

#include "base.h"
#include "ezjson.h"

static const ezjson_helper_t ezjson_helper; /* Definition at the bottom */

enum {REF_NAME = 0, REF_IDX};

static __thread struct {
	int            initialized;

	struct {
		int       ref_type;
		fmt_tok_t tok;

		/* for REF_NAME: */
		char      name[EZJSON_MAX_TAG_LEN];

		/* for REF_IDX: */
		int       idx;
		fmt_tok_t iter_tok;
		int       iter_idx;
	} objs[EZJSON_MAX_DEPTH];

	int            resolved_level;
	int            next_level;

	/* ^^^ clean_meta() boundary ^^^ */

	int            err_code;
	char          *err_str;
	int            err_str_len;

	fmt_t **object;
} meta;


static void mark_iter_invalid(int idx)
{
	if (idx < EZJSON_MAX_DEPTH)
		meta.objs[idx].iter_idx = -1;
}

static void mark_all_iters_invalid(void)
{
	int i;
	for (i = 0; i < EZJSON_MAX_DEPTH; i++)
		meta.objs[i].iter_idx = -1;
}

static void init_meta_defaults(void)
{
	meta.resolved_level = -1;
	mark_all_iters_invalid();

	meta.initialized = 1;
}

static void clean_meta(void)
{
	/* Resets fields until 'error_code' exclusive */
	memset(&meta, 0, (void *)&meta.err_code - (void *)&meta);

	init_meta_defaults();
}

static void full_reset_meta(void)
{
	if (meta.err_str)
		free(meta.err_str);
	memset(&meta, 0, sizeof(meta));

	init_meta_defaults();
}

static void add_to_err_buf(char *fmt, ...)
{
	if (!meta.err_str)
		meta.err_str = malloc(EZJSON_ERRBUF_LEN + 1);

	if (meta.err_str) {
		va_list ap;
		va_start(ap, fmt);
		meta.err_str_len +=
			vsnprintf(meta.err_str      + meta.err_str_len,
			          EZJSON_ERRBUF_LEN - meta.err_str_len + 1,
			          fmt, ap);
		va_end(ap);
	}
}

static void add_err_path(int first_idx, int last_idx)
{
	for (; first_idx >= 0 && first_idx <= last_idx; first_idx++) {
		if (meta.objs[first_idx].ref_type == REF_NAME)
			add_to_err_buf("%s", meta.objs[first_idx].name);
		else
			add_to_err_buf("#%d", meta.objs[first_idx].idx + 1);


		if (first_idx + 1 <= last_idx)
			add_to_err_buf("->");
	}
}

static void clean_err(void)
{
	if (meta.err_code == EZJSON_ERR_TOO_DEEP)
		return;         /* Fatal errors are not cleaned */

	free(meta.err_str);
	meta.err_str     = NULL;
	meta.err_str_len = 0;
	meta.err_code    = 0;
}

static void regerr_not_found(int last_level)
{
	if (meta.err_code)
		return;

	meta.err_code = EZJSON_ERR_OBJ_NOT_FOUND;

	add_err_path(0, last_level);
	if (last_level >= 0)
		add_to_err_buf("->");
	add_to_err_buf(" !");
	add_err_path(last_level + 1, last_level + 1);
	add_to_err_buf("!");
}

static void reg_err_too_deep(void)
{
	if (meta.err_code)
		return;

	meta.err_code = EZJSON_ERR_TOO_DEEP;

	int i;
	for (i = 0; i < 1 + EZJSON_MAX_DEPTH; i++)
		add_to_err_buf("{");
	for (i = 0; i < 1 + EZJSON_MAX_DEPTH; i++)
		add_to_err_buf("}");
	add_to_err_buf(" > %d", EZJSON_MAX_DEPTH);
}

static const ezjson_helper_t *err(int *code, char **str)
{
	if (meta.err_code) {
		if (str)
			*str = strdup(meta.err_str);

		if (code)
			*code = meta.err_code;

		clean_err();
	} else {
		if (str)
			*str = NULL;

		if (code)
			*code = 0;
	}

	return &ezjson_helper;
}


static const ezjson_helper_t *err_str(char **str)
{
	if (meta.err_code) {
		if (str)
			*str = strdup(meta.err_str);
		clean_err();
	} else {
		if (str)
			*str = NULL;
	}

	return &ezjson_helper;
}

static const ezjson_helper_t *err_code(int *code)
{
	if (meta.err_code) {
		if (code)
			*code = meta.err_code;
		clean_err();
	} else {
		if (code)
			*code = 0;
	}

	return &ezjson_helper;
}

static const ezjson_helper_t *r(void)
{
	clean_meta();
	return &ezjson_helper;
}

/* Increases level by n */
static void incr_level(int n)
{
	meta.next_level += n;

	if (meta.next_level < 0)
		meta.next_level = 0;

	if (meta.next_level >= EZJSON_MAX_DEPTH)
		meta.next_level = EZJSON_MAX_DEPTH - 1;
}

static const ezjson_helper_t *p(int levels)
{
	if (levels < 0)
		incr_level(-EZJSON_MAX_DEPTH); /* Sets to root level */
	else
		incr_level(-levels);

	return &ezjson_helper;
}

/* Returns -1 if we are at the deepest nesting level, 0 otherwise.*/
static int check_nesting(void)
{
	if (meta.next_level + 1 == EZJSON_MAX_DEPTH &&
	    meta.err_code != EZJSON_ERR_TOO_DEEP) {
		reg_err_too_deep();
		/* NOTE: this is a fatal error we do not recover from. Further
		   calls will fail. Solution: fix your code (or
		   EZJSON_MAX_DEPTH). */
		clean_meta();
		return -1;
	}

	return 0;
}

static const ezjson_helper_t *c(const char *name)
{
	if (check_nesting() < 0)
		return &ezjson_helper;

	char new_name[EZJSON_MAX_TAG_LEN];
	snprintf(new_name, EZJSON_MAX_TAG_LEN, "%s", name);

	char *current_name = meta.objs[meta.next_level].name;

	int resolved = 1;

	if (meta.resolved_level < meta.next_level)
		resolved = 0;

	if (resolved && strcmp(current_name, new_name) != 0)
		resolved = 0;   /* Different name */

	if (meta.resolved_level >= meta.next_level && !resolved)
		meta.resolved_level = meta.next_level - 1; /* Not resolved */

	if (!resolved) {
		strcpy(current_name, new_name);
		/* Mark child iter invalid */
		mark_iter_invalid(meta.next_level + 1);
	}

	incr_level(+1);

	return &ezjson_helper;
}

static const ezjson_helper_t *n(int item_idx)
{
	if (check_nesting() < 0)
		return &ezjson_helper;

	int resolved = 1;

	if (meta.resolved_level < meta.next_level)
		resolved = 0;

	if (meta.objs[meta.next_level].ref_type != REF_IDX)
		resolved = 0;   /* REF_NAME does not leave correct idx */

	if (meta.objs[meta.next_level].idx != item_idx)
		resolved = 0;   /* Different index */

	meta.objs[meta.next_level].ref_type = REF_IDX;
	meta.objs[meta.next_level].idx      = item_idx;

	if (meta.resolved_level >= meta.next_level && !resolved)
		meta.resolved_level = meta.next_level - 1;

	if (!resolved)
		mark_iter_invalid(meta.next_level + 1); /* Child iter invalid */

	incr_level(+1);

	return &ezjson_helper;
}


static int is_array_child(int idx)
{
	idx--;                      /* Ascend to the parent */

	fmt_tok_t *tok;

	if (idx < 0)
		tok = (*meta.object)->tok;
	else
		tok = &meta.objs[idx].tok;

	if (fmt_tok_is_array(tok))
		return 1;               /* Array child */
	else
		return 0;               /* Non-array child */
}

static int resolve_array_child_by_idx(int idx)
{
	int rc = 0;

	fmt_tok_t *parent = idx ? &meta.objs[idx-1].tok : NULL;
	fmt_tok_t *iter   = &meta.objs[idx].iter_tok;
	int *iter_idx     = &meta.objs[idx].iter_idx;
	int *item_idx     = &meta.objs[idx].idx;


	/* Subsequent? */
	if (*item_idx && *item_idx - 1 == *iter_idx) {
		rc = fmt_array_next(*meta.object, parent, iter);
		if (rc > 0)
			*iter_idx = *item_idx;
	} else {
		if (*iter_idx > *item_idx)      /* If greater than us, */
			mark_iter_invalid(idx); /* start from begnning */

		while (*iter_idx < *item_idx) {
			if (*iter_idx < 0 && parent)
				memcpy(iter, parent, sizeof(fmt_tok_t));

			rc = fmt_array_next(*meta.object, parent, iter);

			if (rc > 0)
				(*iter_idx)++;
			else
				break;
		}
	}

	if (rc > 0)
		meta.objs[idx].tok = *iter;

	if (rc <= 0)
		rc = MIN(rc, -1);       /* Not found */

	return rc;
}

static int resolve_object_child_by_idx(int idx)
{
	char *key;
	int rc = 0;

	fmt_tok_t *parent = idx ? &meta.objs[idx-1].tok : NULL;
	fmt_tok_t *iter   = &meta.objs[idx].iter_tok;
	int *iter_idx     = &meta.objs[idx].iter_idx;
	int *item_idx     = &meta.objs[idx].idx;

	/* Subsequent? */
	if (*item_idx && *item_idx - 1 == *iter_idx) {
		rc = fmt_object_next(*meta.object, parent, iter, &key);
		if (rc > 0) {
			*iter_idx = *item_idx;
			snprintf(meta.objs[idx].name,
			         EZJSON_MAX_TAG_LEN, "%s", key);
			free(key);
		}
	} else {
		if (*iter_idx > *item_idx)  /* If greater than us, */
			mark_iter_invalid(idx); /* start from begnning */

		while (*iter_idx < *item_idx) {
			if (*iter_idx < 0)
				memset(iter, 0, sizeof(fmt_tok_t));

			rc = fmt_object_next(*meta.object, parent, iter, &key);

			if (rc > 0) {
				(*iter_idx)++;
				snprintf(meta.objs[idx].name,
				         EZJSON_MAX_TAG_LEN, "%s", key);
				free(key);
			} else {
				break;
			}
		}
	}

	if (rc > 0)
		meta.objs[idx].tok = *iter;

	if (rc <= 0)
		rc = MIN(rc, -1); /* Not found */

	return rc;
}

static int resolve_item(int idx)
{
	int rc = -1;
	if (!meta.object || !*meta.object)
		return rc;

	fmt_tok_t *prev_tok = NULL;
	if (idx > 0)
		prev_tok = &meta.objs[idx-1].tok;

	switch(meta.objs[idx].ref_type) {
	case REF_NAME:
		rc = fmt_get_tok(*meta.object, prev_tok,
		                    meta.objs[idx].name, &meta.objs[idx].tok);
		break;
	case REF_IDX:
	{
		if (is_array_child(idx))
			rc = resolve_array_child_by_idx(idx);
		else
			rc = resolve_object_child_by_idx(idx);
	}
	}

	return rc;
}

static int resolve_path(void)
{
	if (!*meta.object)
		return -1;

	int i;
	for (i = 0; i < meta.next_level; i++) {
		if (i <= meta.resolved_level)
			continue;

		if (resolve_item(i) < 0)
			break;
		else
			meta.resolved_level = i;
	}

	i--;
	return i;
}

/* This returns an libfmt tok or NULL in case of error. It also registers
   errors */
static fmt_tok_t *resolve_and_get(void)
{
	int last_level = -1; /* Last resolved level */

	if (meta.next_level == 0) {              /* First level object? */
		if (meta.object && *meta.object) /* Object exists? */
			return &((*meta.object)->tok[0]); /* Can be returned
			                                     straight away */
	}
	else {
		last_level = resolve_path();
		if (last_level == meta.next_level - 1) /* Resolve sucess? */
			return &meta.objs[meta.next_level - 1].tok;
	}

	regerr_not_found(last_level);
	return NULL;
}

static const ezjson_helper_t *get(char **value)
{
	*value = NULL;

	if (meta.err_code) {
		incr_level(-1);
		return &ezjson_helper;
	}

	fmt_tok_t *tok = resolve_and_get();
	incr_level(-1);

	if (!tok)
		return &ezjson_helper;

	if (fmt_tok_is_string(tok) == 1) {
		if (fmt_string_value(*meta.object, tok, value) != 0) {
			/* FIXME: register error */
			*value = NULL;
			printf("Err: %d\n", __LINE__);
		}
		return &ezjson_helper;
	}

	if (fmt_is_null(*meta.object, tok) == 1) {
		*value = NULL;
		return &ezjson_helper;
	}
	/* FIXME: register error */
	printf("Err: %d\n", __LINE__);

	return &ezjson_helper;
}

static const ezjson_helper_t *geti(int *value)
{
	DSTR(strvalue);

	get(&strvalue.v);
	if (meta.err_code)
		return &ezjson_helper;

	if (!strvalue.v) {
		;                       /* FIXME: register error */
		return &ezjson_helper;
	}

	if (sscanf(strvalue.v, "%d", value) != 1) {
		;                       /* FIXME: register error */
		return &ezjson_helper;
	}

	return &ezjson_helper;
}

static const ezjson_helper_t *key(char **value)
{
	if (meta.next_level <= meta.resolved_level) {
		*value = strdup(meta.objs[meta.next_level].name);
	}
	else {
		*value = NULL;
		/* TODO: register error */
	}

	return &ezjson_helper;
}

static fmt_t *create_item(int idx, const char *value)
{
	if (idx > meta.next_level) {
		printf("%d > %d. Not implemented yet. Sorry.\n",
		       idx, meta.next_level);
		exit(0);
	}

	if (idx == meta.next_level) {    /* Is leaf? */
		if (!value)
			return fmt_null();
		else
			return fmt_string(value);
	}

	/* Create the child item */
	fmt_t *child_item = create_item(idx + 1, value); /* Recurse */

	/* Create the parent item */
	fmt_t *item = NULL;

	switch(meta.objs[idx].ref_type)
	{
	case REF_NAME:
		item = fmt_object_alloc();
		break;
	case REF_IDX:
		item = fmt_array_alloc();
		break;
	}
	/* Check creation success */
	if (!child_item || !item) {
		if (!meta.err_code) { /* Error not registered? */
			printf("E: %d\n", __LINE__);
			/* TODO: register error */
		}

		fmt_free(child_item);
		fmt_free(item);
		return NULL;
	}

	int rc = 0;
	/* Append the child item */
	switch(meta.objs[idx].ref_type) {
	case REF_NAME:
		rc = fmt_set_new(item, meta.objs[idx].name, child_item);
		break;
	case REF_IDX:
		rc = fmt_array_add_new(item, child_item);
		break;
	}

	/* Check append errors */
	if (rc < 0 && !meta.err_code) {
		printf("E: %d\n", __LINE__);
		/* TODO: register error */
	}

	return item;
}

static void create_path(int last_resolved_level, const char *value)
{
	fmt_t *child_root = create_item(last_resolved_level
	                                       + 1  /* Resolved */
	                                       + 1, /* Child root */
	                                       value);

	/* Safety checks */
	if (!child_root) {
		/* TODO: register error -- OOM */
		printf("E: %d\n", __LINE__);
		goto cleanup;
	}

	if (last_resolved_level < 0 && /* Creation at the root level? */
	    !*meta.object) {
		switch(meta.objs[0].ref_type) {
		case REF_NAME:
			*meta.object = fmt_object_alloc();
			break;
		case REF_IDX:
			*meta.object = fmt_array_alloc();
			break;
		}
		if (!*meta.object) {
			printf("E: %d\n", __LINE__);
			/* TODO: register error -- OOM */
			goto cleanup;
		}
	}

	fmt_tok_t *last_resolved = NULL;
	if (last_resolved_level >= 0)
		last_resolved = &meta.objs[last_resolved_level].tok;

	int rc = -1;
	switch(meta.objs[last_resolved_level+1].ref_type) {
	case REF_NAME:
		rc = fmt_set_at(*meta.object, last_resolved,
		                       meta.objs[last_resolved_level + 1].name,
		                       child_root);
		break;
	case REF_IDX:
		rc = fmt_array_add_at(*meta.object, last_resolved, child_root);
		break;
	}

	if (rc < 0) {
		printf("E: %d\n", __LINE__);
		/* TODO: register error */
	}

cleanup:
	fmt_free(child_root);
}

static void resolve_and_set(const char *value)
{
	if (meta.next_level) {
		create_path(resolve_path(), value);
	}
	else    /* We are doing set() at the root level -- nothing to resolve */
	{
		/* Delete previous object */
		fmt_free(*meta.object);

		if (value)
			*meta.object = fmt_string(value);
		else
			*meta.object = fmt_null();

		if (!*meta.object)
			;                   /* TODO: register OOM error */
	}


	meta.resolved_level = -1;          /* Mark all tokens as unresolved */
	mark_all_iters_invalid();
}

static const ezjson_helper_t *set(const char *value)
{
	if (meta.err_code)
		return &ezjson_helper;

	resolve_and_set(value);

	incr_level(-1);

	return &ezjson_helper;
}

static const ezjson_helper_t *setf(const char *fmt, ...)
{
	/* Format and store value */
	char *value;
	va_list ap;
	va_start(ap, fmt);
	int rc = vasprintf(&value, fmt, ap);
	va_end(ap);

	if (rc < 0) {
		/* TODO: register OOM error */
		//SERR(LOG, -1);
		return &ezjson_helper;
	}

	set(value);
	free(value);

	return &ezjson_helper;
}

static const ezjson_helper_t *seti(int ivalue)
{
	/* Format and store value */
	char *value;
	if (asprintf(&value, "%d", ivalue) < 0) {
		/* TODO: register OOM error */
		//SERR(LOG, -1);
		return &ezjson_helper;
	}

	set(value);
	free(value);

	return &ezjson_helper;
}


static const ezjson_helper_t *dump(char **value, int pretty)
{
	*value = NULL;

	if (meta.err_code) {
		incr_level(-1);
		return &ezjson_helper;
	}

	fmt_tok_t *tok = resolve_and_get();
	incr_level(-1);

	if (!tok)
		return &ezjson_helper;

	int rc;
	if (pretty)
		rc = fmt_pretty_dump(*meta.object, tok, value);
	else
		rc = fmt_dump_string(*meta.object, tok, value);

	incr_level(+1);

	if (rc < 0) {
		*value = NULL;
		/* FIXME: register error */
		printf("E: %d\n", __LINE__);
	}

	return &ezjson_helper;
}

const ezjson_helper_t *ezjson(fmt_t **object)
{
	/* Safety checks */
	if (!meta.initialized ||        /* meta first use? */
	    !meta.object || !*object)   /* No object? */
		full_reset_meta();

	meta.object = object;

	return &ezjson_helper;
}

static const ezjson_helper_t ezjson_helper = {
	.err      = err,
	.err_str  = err_str,
	.err_code = err_code,
	.r        = r,
	.p        = p,
	.c        = c,
	.n        = n,
	.get      = get,
	.geti     = geti,
	.key      = key,
	.set      = set,
	.setf     = setf,
	.seti     = seti,
	.dump     = dump,
};

#if 0
#define EZJSON_PROFILE
#endif

#ifdef EZJSON_PROFILE
static
__attribute__((unused))
__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *func, void *caller)
{
	int *frame = __builtin_frame_address(1);

	if (func == resolve_item) {
		int idx = frame[2*4-1]; /* x86 */
		printf(">> resolve_item: %d: %s\n", idx, meta.objs[idx].name);
	}
}
#endif
