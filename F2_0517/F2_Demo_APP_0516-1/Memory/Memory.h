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
Description: ��Ҫʵ��memory��ض���
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

#define		UartATLen			1024+1//���ڴ���ͨ�����ݻ���

extern FIFO_t	UartATFifo;
extern u8 UartATBuf[];

void Init_memory(void);
#endif



