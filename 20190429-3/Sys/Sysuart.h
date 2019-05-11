/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Sysuart.h
Description		: 主要实现系统串口相关定义流程
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-25
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _sys_uart_h
#define _sys_uart_h
#include "arm_base_define.h"
#include "stm32f0xx_hal_uart.h"
#include "Debugprintf.h"
#include "Fifo.h"

#define RX_LEN		1024

#pragma pack(push,1)
typedef struct
{
	u8 flag;
	u16 RX_Size;          //receive length
	u8  RX_pData[RX_LEN]; //DMA receive buffer
}UartDMA_t;  
#pragma pack(pop)

extern UartDMA_t Uart1DMA;
extern UartDMA_t Uart3DMA;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);
void MX_DMA_Init(void);


#endif

