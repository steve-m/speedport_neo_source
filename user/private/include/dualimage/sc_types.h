/* =============================================================================      
 *         Copyright (C) 2006, Sercomm Corporation,  All Rights Reserved
 * =============================================================================    
 * The Header File Of Sercomm Type
 * 
 * [ Revise History ]:
 *  v1.00     init      Jim Yang
 * =============================================================================
 */

#ifndef _SC_TYPE_H_
#define _SC_TYPE_H_

/* Defination for Sercomm, if you have defind this type, Modify it for fix your environment */

typedef signed char  int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed long  int32;
typedef unsigned long uint32;

#ifndef NULL
    #define NULL 0
#endif

#ifndef TRUE
    #define TRUE  1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#define HIBYTE(x) (uint8)((uint16)(x)>>8)
#define LOBYTE(x) (uint8)((uint16)(x) & 0x00ff)

#endif /* End Of _SC_TYPE_H_ */

