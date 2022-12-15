/*************************************************************************
 * Copyright (c) <2013, 2014>  SAF TEHNIKA JSC (www.saftehnika.com)
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * For any questions or requests please contact: SW_LIC (at) SAFTEHNIKA.COM
 */

#ifndef MACROS_H
#define MACROS_H

/* Compile time assertions */
#define STATIC_ASSERT(cond,name) \
    typedef char static_assertion_##name[(!!(cond))*2-1]

/* Argument counting macro
   Source: http://newsgroups.derkeiler.com/Archive/Comp/comp.std.c/2006-01/msg00072.html */
#define PP_NARG(...)                            \
	PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...)                           \
	PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(					\
	_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,		\
	_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,	\
	_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,	\
	_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,	\
	_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,	\
	_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,	\
	_61,_62,_63,N,...) N
#define PP_RSEQ_N() 63,62,61,60,		\
		59,58,57,56,55,54,53,52,51,50,	\
		49,48,47,46,45,44,43,42,41,40,	\
		39,38,37,36,35,34,33,32,31,30,	\
		29,28,27,26,25,24,23,22,21,20,	\
		19,18,17,16,15,14,13,12,11,10,	\
		9,8,7,6,5,4,3,2,1,0

/* Concatenate */
#define CAT(A, B)  CAT2(A, B)
#define CAT2(A, B) A ## B

/*
  Disposable strings (and possibly other structures).
*/
void __disp_arr_free(void *p);

/* Gives either 1/2/N depending on parameter count */
#define DISP_PARAM_TYPE(...)					\
	PP_NARG_(__VA_ARGS__,					\
		 N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,	\
		 N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,	\
		 N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,	\
		 N,2,1)

#define __DISP_ARR_S(type, name, len)			\
	struct {					\
		const int nmemb;                        \
		union {                                 \
			type *a[len];			\
			type *v;			\
		};                                      \
	} name						\
	__attribute__((cleanup(__disp_arr_free)))

#define DSTR_N(name, len, ...)                  \
	__DISP_ARR_S(char, name, len)		\
	= {len, {{__VA_ARGS__}}}

#define DSTR_2(name, len) DSTR_N(name, len, NULL)
#define DSTR_1(name)      DSTR_N(name, 1,   NULL)
#define DSTR(...) CAT(DSTR_,DISP_PARAM_TYPE(__VA_ARGS__))(__VA_ARGS__)

/* Repetition */
#define REP_1(str) str
#define REP_2(str)  str REP_1(str)
#define REP_3(str)  str REP_2(str)
#define REP_4(str)  str REP_3(str)
#define REP_5(str)  str REP_4(str)
#define REP_6(str)  str REP_5(str)
#define REP_7(str)  str REP_6(str)
#define REP_8(str)  str REP_7(str)
#define REP_9(str)  str REP_8(str)
#define REP_10(str) str REP_9(str)
#define REP_11(str) str REP_10(str)
#define REP_12(str) str REP_11(str)
#define REP_13(str) str REP_12(str)
#define REP_14(str) str REP_13(str)
#define REP_15(str) str REP_14(str)
#define REP_16(str) str REP_15(str)
#define REP_17(str) str REP_16(str)
#define REP_18(str) str REP_17(str)
#define REP_19(str) str REP_18(str)
#define REP_20(str) str REP_19(str)
#define REP_21(str) str REP_20(str)
#define REP_22(str) str REP_21(str)
#define REP_23(str) str REP_22(str)
#define REP_24(str) str REP_23(str)
#define REP_25(str) str REP_24(str)
#define REP_26(str) str REP_25(str)
#define REP_27(str) str REP_26(str)
#define REP_28(str) str REP_27(str)
#define REP_29(str) str REP_28(str)
#define REP_30(str) str REP_29(str)
#define REP_31(str) str REP_30(str)
#define REP_32(str) str REP_31(str)
#define REP(str, n) CAT(REP_,n)(str)

#define PRINT_BIN_DEBUG_TABLE_COLUMNS		16
#define PRINT_BIN( buff, len, x, y )				\
	x = 0;							\
	y = -1;							\
	printf( "\n" );						\
	for ( x = 0; x < len; x++ ) {				\
		y++;						\
		if ( y == PRINT_BIN_DEBUG_TABLE_COLUMNS ) {	\
			printf( "\n" );				\
			y = 0;					\
		}						\
		printf( "%02X ", buff[x] );			\
	}							\
	printf( "\n\n" );

#define CUTE_FREE( x ) free( x ); x = NULL

#endif
