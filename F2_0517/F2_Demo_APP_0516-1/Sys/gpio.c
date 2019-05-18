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
File name  : gpio.c
Description: 主要实现gpio初始化
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-05-13
Modify	   : 
Modify Time: 
******************************************************************************/
#include "gpio.h"

/*******************************************************************************
* @Function		:void MX_GPIO_Init(void)
* @Description	:实现GPIO初始化
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void MX_GPIO_Init(void)
{
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	SET_GPIO_OUT(LED1);
	SET_GPIO_OUT(LED2);
	SET_GPIO_OUT(LED3);
	SET_GPIO_OUT(LED4);
}

/*******************************************************************************
* @Function		:void Set_GPIO_PIN(GPIO_TypeDef *gpio, uint16_t nPin,uint32_t speed,uint32_t mode)
* @Description	:实现设置gpio方向
* @Input		:GPIO_TypeDef,nPin,speed,mode
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void Set_GPIO_PIN(GPIO_TypeDef *gpio, uint16_t nPin,uint32_t speed,uint32_t mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	HAL_GPIO_WritePin(gpio, nPin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = nPin;
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = speed;
	HAL_GPIO_Init(gpio, &GPIO_InitStruct);
}




