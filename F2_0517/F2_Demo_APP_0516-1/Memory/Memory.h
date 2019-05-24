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
#define		TAGLen				1024*3+1//���ڻ����ǩ��Ϣ
#define		TAGLen1				1024*2+1//���ڻ����ǩ��Ϣ
#define		cmpylen				3000


extern FIFO_t	UartATFifo;
extern u8 UartATBuf[];
extern FIFO_t TAGFifo;
extern u8 TAGBuf[];
extern FIFO_t TAGFifo1;
extern u8 TAGBuf1[];


void Init_memory(void);
#endif



