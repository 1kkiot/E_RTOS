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
File name  : uart_irq.h
Description: 主要实现uart irq相关定义
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-03-15
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _uart_irq_h
#define _uart_irq_h
#include "stm32f2xx_hal.h"
#include "uart.h"
#include "arm_base_define.h"

#define		RX_LEN		1024

#pragma pack(push,1)
typedef struct
{
	u8  RX_Data[RX_LEN];//DMA receive buffer
	u16 RX_Size;		//receive length
}UartDMA_t;  
#pragma pack(pop)

extern UartDMA_t UartAT;

#endif

