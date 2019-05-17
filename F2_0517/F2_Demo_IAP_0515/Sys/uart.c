#include "uart.h"
#pragma import(__use_no_semihosting)             
struct __FILE
{
	int handle;
};
FILE __stdout;
void _sys_exit(int x)
{
	x = x;
}
void _ttywrch(int ch)
{
    ch = ch;
}
int fputc(int ch,FILE *f)
{
	while((USART6->SR & 0x40) == 0);
	USART6->DR = (uint8_t)ch;
	return ch;
}
UART_HandleTypeDef UartHandle;
void MX_USART6_UART_Init(void)
{

	UartHandle.Instance = USART6;
	UartHandle.Init.BaudRate = 115200;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		;//Error_Handler();
	}

}
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(uartHandle->Instance==USART6)
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

		/* USART6 interrupt Init */
		HAL_NVIC_SetPriority(USART6_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(USART6_IRQn);
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

	if(uartHandle->Instance==USART6)
	{
		__HAL_RCC_USART6_CLK_DISABLE();

		/**USART6 GPIO Configuration    
		PC6     ------> USART6_TX
		PC7     ------> USART6_RX 
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

		/* USART6 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART6_IRQn);

	}
}


void USART6_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UartHandle);
}




