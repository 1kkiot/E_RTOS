/************Copyright(C) Kaikai Technology 2018-05-14***********************
     **  **        **  **         ****         ****          ******    
     **  **        **  **          **         **  **           **      
     ** **         ** **           **         **  **           **      
     ** **         ** **           **         **  **           **      
     ****          ****            **         **  **           **      
     ** **         ** **           **         **  **           **      
     ** **         ** **           **         **  **           **      
     **  **        **  **          **         **  **           **      
     **  **        **  **         ****         ****            **       
*****************************************************************************
File name  : arm_base_define.h
Description: stm32系列宏定义，方便软件开发和移植
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-03-15
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _arm_base_define_
#define _arm_base_define_

#include "stm32f4xx_hal.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef TRUE
#define	TRUE							1
#endif
#ifndef FALSE
#define	FALSE							0
#endif
#ifndef NULL
#define NULL							((void*)(0))
#endif

typedef unsigned int   					u32;
typedef unsigned short 					u16;
typedef unsigned char  					u8;
typedef signed long    					s32;
typedef signed short   					s16;
typedef signed char    					s8;

typedef volatile unsigned int   		vu32;
typedef volatile unsigned short 		vu16;
typedef volatile unsigned char  		vu8;
typedef volatile unsigned int  const 	vuc32;  /* Read Only */
typedef volatile unsigned short const 	vuc16;  /* Read Only */
typedef volatile unsigned char  const 	vuc8;   /* Read Only */

//输出字符串
#define STR(s) 							#s 
//得到指定地址上的一个u8或u16
#define  MEM_U8( x )  					( *( (u8 *) (x) ) )
#define  MEM_U16( x )  					( *( (u16 *) (x) ) )
//获取最大值和最小值
//#define  MAX( x, y ) 					( ((x) > (y)) ? (x) : (y) )
#define  MAX(X,Y)						({ \
											typeof (X) x_ = (X); \
											typeof (Y) y_ = (Y); \
											(x_ > y_) ? x_ : y_; })
//#define  MIN( x, y ) 					( ((x) < (y)) ? (x) : (y) )
#define  MIN(X,Y)						({ \
											typeof (X) x_ = (X); \
											typeof (Y) y_ = (Y); \
											(x_ < y_) ? x_ : y_; })//增加容错
//将一个字母转换为大写
#define  UPCASE( c ) 					( ((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c) )
//获取数组元素的个数
#define  ARR_SIZE( a )  				( sizeof( (a) ) / sizeof( (a[0]) ) )

//获取一个field在结构体(struct)中的偏移量
#define FPOS( type, field ) 			( (u32) &(( type *) 0)-> field ) 
//获取一个结构体中field所占用的字节数
#define FSIZ( type, field ) 			sizeof( ((type *) 0)->field )


//对于IO空间映射在存储空间的结构，输入输出处理
#define inpu8(port)         			(*((volatile u8 *) (port)))
#define inpu16(port)        			(*((volatile u16 *)(port)))
#define inpu32(port)       				(*((volatile u32 *)(port)))
#define outpu8(port, val)   			(*((volatile u8 *) (port)) = ((u8) (val)))
#define outpu16(port, val)  			(*((volatile u16 *) (port)) = ((u16) (val)))
#define outpu32(port, val) 				(*((volatile u32 *) (port)) = ((u32) (val)))








#endif//_arm_base_define_






/*
//判断mcu是大端模式还是小端模式
	union w
	{
		u32 a;  //4 bytes
		u8 b; //1 byte
	} c;
	c.a=1;
	if (c.b==1)
		printf("It is Little_endian!\n");
	else
		printf("It is Big_endian!\n");
	//另外一种判断方式
	int x=1; // 0x00000001 
	if (*(char*)&x){ 
	// little endian. memory image 01 00 00 00  
	}else{ 
	// big endian. memory image 00 00 00 01  
	} 
*/









