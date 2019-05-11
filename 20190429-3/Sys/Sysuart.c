/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Sysuart.c
Description		: 主要实现系统串口初始化配置流程及dma配置
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-25
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Sysuart.h"
#include "Memory.h"
#include "Sysgpio.h"
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;

UartDMA_t Uart1DMA;
UartDMA_t Uart3DMA;

/*******************************************************************************
* @Function		:void MX_USART1_UART_Init(void)
* @Description	:系统串口初始化
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void MX_USART1_UART_Init(void)
{

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}

	//开启dma接收
//	HAL_UART_Receive_DMA(&huart1, Uart1DMA.RX_pData,RX_LEN);  
//	//开启串口中断
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
}

/*******************************************************************************
* @Function		:void MX_USART3_UART_Init(void)
* @Description	:系统串口初始化
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void MX_USART3_UART_Init(void)
{

	huart3.Instance = USART3;
	huart3.Init.BaudRate = 38400;
	huart3.Init.WordLength = UART_WORDLENGTH_9B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_EVEN;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_Handler();
	}
	//开启dma接收
//	HAL_UART_Receive_DMA(&huart3, Uart3DMA.RX_pData,RX_LEN);  
//	//开启串口中断
//	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);

	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
	__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
}

/*******************************************************************************
* @Function		:void MX_DMA_Init(void)
* @Description	:初始系统dma中断
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void MX_DMA_Init(void) 
{
//	/* DMA controller clock enable */
//	__HAL_RCC_DMA1_CLK_ENABLE();

//	/* DMA interrupt init */
//	/* DMA1_Channel2_3_IRQn interrupt configuration */
//	HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 3, 0);
//	HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
//	/* DMA1_Channel4_5_6_7_IRQn interrupt configuration */
//	HAL_NVIC_SetPriority(DMA1_Channel4_5_6_7_IRQn, 3, 0);
//	HAL_NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn);

}

/**
  * @brief This function handles DMA1 channel 2 and 3 interrupts.
  */
//void DMA1_Channel2_3_IRQHandler(void)
//{
//	HAL_DMA_IRQHandler(&hdma_usart3_tx);
//	HAL_DMA_IRQHandler(&hdma_usart3_rx);
//}


//void DMA1_Channel4_5_6_7_IRQHandler(void)
//{
//	HAL_DMA_IRQHandler(&hdma_usart1_tx);
//	HAL_DMA_IRQHandler(&hdma_usart1_rx);
//}

typedef enum{
	UART_RX_STATE_READY,
	UART_RX_STATE_START
}_uartRxState;
_uartRxState uart1RxState=UART_RX_STATE_READY;
_uartRxState uart3RxState=UART_RX_STATE_READY;
void user_Uart1Handler()
{
	u8 temp=0;
	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)!=RESET))
	{
		temp = (uint8_t)(huart1.Instance->RDR);
		if(uart1RxState == UART_RX_STATE_READY)
		{
			uart1RxState = UART_RX_STATE_START;
			Uart1DMA.RX_Size = 0;
			Uart1DMA.RX_pData[Uart1DMA.RX_Size++] = temp;
		}
		else if(uart1RxState == UART_RX_STATE_START) 
		{
			Uart1DMA.RX_pData[Uart1DMA.RX_Size++] = temp;
		}
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);
	}
	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)!=RESET))
	{
		//TogglePin(LED2);
		fifo_puts(&WifiFifo,Uart1DMA.RX_pData,Uart1DMA.RX_Size);
		uart1RxState = UART_RX_STATE_READY;
		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_IDLE);
	}
}
void USART1_IRQHandler(void)//wifi
{
	user_Uart1Handler();

//	HAL_UART_Receive_IT(&huart1,Uart1DMA.RX_pData,10);
//	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE) != RESET))  
//	{
//		fifo_puts(&WifiFifo,Uart1DMA.RX_pData,10);
//		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
//		TogglePin(LED2);
//	}
//	HAL_UART_IRQHandler(&huart1);
//	 u16 temp;
//	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE) != RESET))  
//	{
//		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
//		HAL_UART_DMAStop(&huart1);
//		temp = huart1.hdmarx->Instance->CNDTR;
//		Uart1DMA.RX_Size =  RX_LEN - temp;
//		HAL_UART_Receive_DMA(&huart1,Uart1DMA.RX_pData,RX_LEN);
//		fifo_puts(&WifiFifo,Uart1DMA.RX_pData,Uart1DMA.RX_Size);
//		TogglePin(LED2);
//	}
//	HAL_UART_IRQHandler(&huart1);

}
void user_Uart3Handler()
{
	u8 temp=0;
	if((__HAL_UART_GET_FLAG(&huart3,UART_FLAG_RXNE)!=RESET))
	{
		temp = (uint8_t)(huart3.Instance->RDR);
		if(uart3RxState == UART_RX_STATE_READY)
		{
			uart3RxState = UART_RX_STATE_START;
			Uart3DMA.RX_Size = 0;
			Uart3DMA.RX_pData[Uart3DMA.RX_Size++] = temp;
		}
		else if(uart3RxState == UART_RX_STATE_START) 
		{
			Uart3DMA.RX_pData[Uart3DMA.RX_Size++] = temp;
		}
		__HAL_UART_CLEAR_FLAG(&huart3,UART_FLAG_RXNE);
	}
	if((__HAL_UART_GET_FLAG(&huart3,UART_FLAG_IDLE)!=RESET))
	{
		//TogglePin(LED4);
		fifo_puts(&TagCacheFifo,Uart3DMA.RX_pData,Uart3DMA.RX_Size);
		uart3RxState = UART_RX_STATE_READY;
		__HAL_UART_CLEAR_FLAG(&huart3,UART_FLAG_IDLE);
	}
}
void USART3_4_IRQHandler(void)//232
{
	user_Uart3Handler();
//	u16 temp;  
//	if((__HAL_UART_GET_FLAG(&huart3,UART_FLAG_IDLE) != RESET))  
//	{
//		__HAL_UART_CLEAR_IDLEFLAG(&huart3);
//		HAL_UART_DMAStop(&huart3);
//		temp = huart3.hdmarx->Instance->CNDTR;
//		Uart3DMA.RX_Size =  RX_LEN - temp;
//		HAL_UART_Receive_DMA(&huart3,Uart3DMA.RX_pData,RX_LEN);
//		fifo_puts(&TagCacheFifo,Uart3DMA.RX_pData,Uart3DMA.RX_Size);
//		//TogglePin(LED4);
//	}
//	HAL_UART_IRQHandler(&huart3);
}


void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//    /* USART1 DMA Init */
//    /* USART1_RX Init */
//    hdma_usart1_rx.Instance = DMA1_Channel5;
//    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
//    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
//    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
//    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
//    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
//    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
//    {
//      Error_Handler();
//    }

//    __HAL_DMA_REMAP_CHANNEL_ENABLE(DMA_REMAP_USART1_RX_DMA_CH5);

//    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

//	/* USART1_TX Init */
//	hdma_usart1_tx.Instance = DMA1_Channel4;
//	hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
//	hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
//	hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
//	hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//	hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//	hdma_usart1_tx.Init.Mode = DMA_NORMAL;
//	hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
//	if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
//	{
//	  Error_Handler();
//	}

//	__HAL_DMA_REMAP_CHANNEL_ENABLE(DMA_REMAP_USART1_TX_DMA_CH4);

//	__HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//    /* USART3 DMA Init */
//    /* USART3_RX Init */
//    hdma_usart3_rx.Instance = DMA1_Channel3;
//    hdma_usart3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
//    hdma_usart3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
//    hdma_usart3_rx.Init.MemInc = DMA_MINC_ENABLE;
//    hdma_usart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//    hdma_usart3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//    hdma_usart3_rx.Init.Mode = DMA_NORMAL;
//    hdma_usart3_rx.Init.Priority = DMA_PRIORITY_LOW;
//    if (HAL_DMA_Init(&hdma_usart3_rx) != HAL_OK)
//    {
//      Error_Handler();
//    }

//    __HAL_DMA_REMAP_CHANNEL_ENABLE(DMA_REMAP_USART3_DMA_CH32);

//    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart3_rx);

//    /* USART3_TX Init */
//    hdma_usart3_tx.Instance = DMA1_Channel2;
//    hdma_usart3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
//    hdma_usart3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
//    hdma_usart3_tx.Init.MemInc = DMA_MINC_ENABLE;
//    hdma_usart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//    hdma_usart3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//    hdma_usart3_tx.Init.Mode = DMA_NORMAL;
//    hdma_usart3_tx.Init.Priority = DMA_PRIORITY_LOW;
//    if (HAL_DMA_Init(&hdma_usart3_tx) != HAL_OK)
//    {
//      Error_Handler();
//    }

//    __HAL_DMA_REMAP_CHANNEL_ENABLE(DMA_REMAP_USART3_DMA_CH32);

//    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart3_tx);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_4_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(USART3_4_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_4_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
} 










