/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Sysgpio.c
Description		: 主要实现系统GPIO初始化
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-25
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Sysgpio.h"

/*******************************************************************************
* @Function		:void gpio_init()
* @Description	:初始化系统GPIO
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void gpio_init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	SET_GPIO_OUT(LED1);
	SET_GPIO_OUT(LED2);
	SET_GPIO_OUT(LED3);
	SET_GPIO_OUT(LED4);
	SET_GPIO_L(LED1);
	SET_GPIO_L(LED2);
	SET_GPIO_L(LED3);
	SET_GPIO_L(LED4);
}

/*******************************************************************************
* @Function		:void Set_GPIO_PIN(GPIO_TypeDef *gpio, u16 nPin,u32 mode,u32 speed)
* @Description	:设置系统GPIO方向
* @Input		:GPIO_TypeDef *gpio, u16 nPin,u32 mode,u32 speed
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void Set_GPIO_PIN(GPIO_TypeDef *gpio, u16 nPin,u32 mode,u32 speed)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	HAL_GPIO_WritePin(gpio, nPin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = nPin;
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = speed;
	HAL_GPIO_Init(gpio, &GPIO_InitStruct);

}















