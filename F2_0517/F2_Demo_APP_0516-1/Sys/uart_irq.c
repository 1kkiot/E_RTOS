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
File name  : uart_irq.c
Description: 主要实现uart中断处理
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-05-15
Modify	   : 
Modify Time: 
******************************************************************************/
#include "uart_irq.h"
#include "Memory.h"
UartDMA_t UartAT;
void DMA2_Stream1_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_usart6_rx);
}


void DMA2_Stream6_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_usart6_tx);
}


void USART6_IRQHandler(void)
{
	u16 tmp;
	HAL_UART_IRQHandler(&huart6);
	if(__HAL_UART_GET_FLAG(&huart6,UART_FLAG_IDLE) != RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart6);
		HAL_UART_DMAStop(&huart6);
		tmp = huart6.hdmarx->Instance->NDTR;
		UartAT.RX_Size =  RX_LEN - tmp;
		HAL_UART_Receive_DMA(&huart6,UartAT.RX_Data,RX_LEN);
		fifo_puts(&UartATFifo,UartAT.RX_Data,UartAT.RX_Size);
	}
}













