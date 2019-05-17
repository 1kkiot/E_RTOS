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
File name  : uart.c
Description: 主要实现uart初始化
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-05-13
Modify	   : 
Modify Time: 
******************************************************************************/
#include "uart.h"
#include "MyFinsh.h"
#include "uart_irq.h"

UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart6_rx;
DMA_HandleTypeDef hdma_usart6_tx;

/*******************************************************************************
* @Function		:void MX_USART6_UART_Init(void)
* @Description	:实现串口初始化功能
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void MX_USART6_UART_Init(void)
{
	huart6.Instance = USART6;
	huart6.Init.BaudRate = 115200;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK)
	{
		;//Error_Handler();
	}
	//开启dma接收
	HAL_UART_Receive_DMA(&huart6, UartAT.RX_Data,RX_LEN);  
	//开启串口中断
	__HAL_UART_ENABLE_IT(&huart6, UART_IT_IDLE);

}

void MX_DMA_Init(void) 
{

	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
	/* DMA2_Stream6_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(uartHandle->Instance==USART2)
	{
		__HAL_RCC_USART2_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART2 GPIO Configuration    
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
	else if(uartHandle->Instance==USART6)
	{
		__HAL_RCC_USART6_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**USART6 GPIO Configuration    
		PC6     ------> USART6_TX
		PC7     ------> USART6_RX 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* USART6 DMA Init */
		/* USART6_RX Init */
		hdma_usart6_rx.Instance = DMA2_Stream1;
		hdma_usart6_rx.Init.Channel = DMA_CHANNEL_5;
		hdma_usart6_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_usart6_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart6_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart6_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart6_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart6_rx.Init.Mode = DMA_NORMAL;
		hdma_usart6_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_usart6_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_usart6_rx) != HAL_OK)
		{
			;//Error_Handler();
		}

		__HAL_LINKDMA(uartHandle,hdmarx,hdma_usart6_rx);

		/* USART6_TX Init */
		hdma_usart6_tx.Instance = DMA2_Stream6;
		hdma_usart6_tx.Init.Channel = DMA_CHANNEL_5;
		hdma_usart6_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart6_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart6_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart6_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart6_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart6_tx.Init.Mode = DMA_NORMAL;
		hdma_usart6_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_usart6_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_usart6_tx) != HAL_OK)
		{
			;//Error_Handler();
		}

		__HAL_LINKDMA(uartHandle,hdmatx,hdma_usart6_tx);

		/* USART6 interrupt Init */
		HAL_NVIC_SetPriority(USART6_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(USART6_IRQn);
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

	if(uartHandle->Instance==USART2)
	{
		__HAL_RCC_USART2_CLK_DISABLE();

		/**USART2 GPIO Configuration    
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX 
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);
	}
	else if(uartHandle->Instance==USART6)
	{
		__HAL_RCC_USART6_CLK_DISABLE();

		/**USART6 GPIO Configuration    
		PC6     ------> USART6_TX
		PC7     ------> USART6_RX 
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

		/* USART6 DMA DeInit */
		HAL_DMA_DeInit(uartHandle->hdmarx);
		HAL_DMA_DeInit(uartHandle->hdmatx);

		/* USART6 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART6_IRQn);
	}
}





