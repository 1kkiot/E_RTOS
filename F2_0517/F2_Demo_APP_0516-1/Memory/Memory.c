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
File name  : Memory.c
Description: 主要实现memory定义及初始化
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-05-13
Modify	   : 
Modify Time: 
******************************************************************************/
#include "Memory.h"

FIFO_t UartATFifo;
u8 UartATBuf[UartATLen];
FIFO_t TAGFifo;
u8 TAGBuf[TAGLen];
FIFO_t TAGFifo1;
u8 TAGBuf1[TAGLen1];

u8 cmpy_buf[cmpylen];

void Init_memory()
{
	memset(cmpy_buf,0,sizeof(cmpy_buf));
	fifo_init(&UartATFifo,UartATBuf,UartATLen);
	fifo_init(&TAGFifo,TAGBuf,TAGLen);
	fifo_init(&TAGFifo1,TAGBuf1,TAGLen1);
}









