/************Copyright(C) Kaikai Technology *********************************
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
File name  : Memory.h
Description: 主要实现memory相关定义
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-05-13
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _memory_h
#define _memory_h

#include "arm_base_define.h"
#include "Fifo.h"

#define		UartATLen			1024+1//用于串口通信数据缓存
#define		TAGLen				1024*3+1//用于缓存标签信息
#define		TAGLen1				1024*2+1//用于缓存标签信息
#define		cmpylen				3000


extern FIFO_t	UartATFifo;
extern u8 UartATBuf[];
extern FIFO_t TAGFifo;
extern u8 TAGBuf[];
extern FIFO_t TAGFifo1;
extern u8 TAGBuf1[];


void Init_memory(void);
#endif



