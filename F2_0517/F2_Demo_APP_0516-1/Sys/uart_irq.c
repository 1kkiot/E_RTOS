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
_uartRxState uart1RxState = UART_RX_STATE_READY;

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
//	u8 temp=0;
//	if((__HAL_UART_GET_FLAG(&huart6,UART_FLAG_RXNE)!=RESET))
//	{
//		temp = (uint8_t)(huart6.Instance->DR);
//		if(uart1RxState == UART_RX_STATE_READY)
//		{
//			uart1RxState = UART_RX_STATE_START;
//			UartAT.RX_Size = 0;
//			UartAT.RX_Data[UartAT.RX_Size++] = temp;
//		}
//		else if(uart1RxState == UART_RX_STATE_START) 
//		{
//			UartAT.RX_Data[UartAT.RX_Size++] = temp;
//		}
//		__HAL_UART_CLEAR_FLAG(&huart6,UART_FLAG_RXNE);
//	}
//	if((__HAL_UART_GET_FLAG(&huart6,UART_FLAG_IDLE)!=RESET))
//	{
//		//TogglePin(LED2);
//		fifo_puts(&UartATFifo,UartAT.RX_Data,UartAT.RX_Size);
//		uart1RxState = UART_RX_STATE_READY;
//		__HAL_UART_CLEAR_FLAG(&huart6,UART_FLAG_IDLE);
//	}
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













