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
Description: ��Ҫʵ��memory���弰��ʼ��
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


void Init_memory()
{
	fifo_init(&UartATFifo,UartATBuf,UartATLen);
}









