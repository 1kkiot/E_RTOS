#include "SysGpio.h"

void MX_GPIO_Init(void)
{
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	SET_GPIO_OUT(LED1_GPIO);
	SET_GPIO_OUT(LED2_GPIO);
}

void Set_GPIO_PIN(GPIO_TypeDef *gpio, uint16_t nPin,uint32_t mode,uint32_t speed)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	HAL_GPIO_WritePin(gpio, nPin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = nPin;
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = speed;
	HAL_GPIO_Init(gpio, &GPIO_InitStruct);
}












