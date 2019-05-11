#ifndef _sys_uart_h
#define _sys_uart_h
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_usart.h"
#include "arm_base_define.h"
#include "Memory.h"

#define RX_LEN		1024

#pragma pack(push,2)
typedef struct
{
	u16 RX_Size;          //receive length
	u8  RX_pData[RX_LEN]; //DMA receive buffer
}UartDMA_t;  
#pragma pack(pop)

extern UartDMA_t Uart1DMA;
extern UartDMA_t Uart2DMA;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;

void MX_DMA_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle);
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle);
void UsartReceive_IDLE(UART_HandleTypeDef *huart);

#endif



