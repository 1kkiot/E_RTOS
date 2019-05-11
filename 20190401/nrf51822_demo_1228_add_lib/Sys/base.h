/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : base.h
Description: 数据类型定义头文件 
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef __BASE_H__
#define __BASE_H__
 
#include <stdbool.h>
#include "nrf.h"

#define debug

#define TRUE                      		(1)
#define FALSE                     		(0)

#ifndef NULL
#define NULL                      		((void*)(0))
#endif

#define CLEAR                       	(0xFF)

//#define offsetof(TYPE, MEMBER) 			((u32) &((TYPE *)0)->MEMBER)
#define NB_DIM(array_) 					(sizeof(array_) / sizeof((array_)[0]))
#define NUM_ROUND(a,b)					(((a)/(b))+ ((0==((a)%(b)))?(0):(1)))

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
//typedef signed long    s32;
typedef signed short   s16;
typedef signed char    s8;

typedef volatile unsigned int   vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned int  const vuc32;  /* Read Only */
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */

typedef float  f32;
typedef double f64;

#define		uint32_t				u32
#define		uint8_t					u8
#define U8_MAX     UINT8_MAX
#define S8_MAX     INT8_MAX
#define S8_MIN     INT8_MIN
#define U16_MAX    UINT16_MAX
#define S16_MAX    INT16_MAX
#define S16_MIN    INT16_MIN
#define U32_MAX    UINT32_MAX
#define S32_MAX    INT32_MAX
#define S32_MIN    INT32_MIN

#endif
