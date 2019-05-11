/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : base.h
Description: 主要实现数据类型重定义，方便使用
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-05-14
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef __BASE_H__
#define __BASE_H__

#include "lpc17xx_libcfg_default.h"
#include <stdbool.h>

#define			debug				//打印系统所有调试信息
#define			debugprintf			//打印系统特定调试信息
#define			debugprint			//打印精简版调试信息


typedef float  f32;
typedef double f64;

typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t  sc8;   /*!< Read Only */

//typedef __IO int32_t  vs32;
//typedef __IO int16_t  vs16;
//typedef __IO int8_t   vs8;

//typedef __I int32_t vsc32;  /*!< Read Only */
//typedef __I int16_t vsc16;  /*!< Read Only */
//typedef __I int8_t  vsc8;   /*!< Read Only */

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t  uc8;   /*!< Read Only */

//typedef __IO uint32_t vu32;
//typedef __IO uint16_t vu16;
//typedef __IO uint8_t  vu8;

//typedef __I uint32_t vuc32;  /*!< Read Only */
//typedef __I uint16_t vuc16;  /*!< Read Only */
//typedef __I uint8_t  vuc8;   /*!< Read Only */

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
