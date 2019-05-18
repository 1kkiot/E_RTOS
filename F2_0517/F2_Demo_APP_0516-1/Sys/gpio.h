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
File name  : gpio.h
Description: 主要实现gpio初始化相关定义
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-05-13
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _gpio_h
#define _gpio_h
#include "stm32f2xx_hal.h"
#define		LED1					GPIOE
#define		LED1_PIN				GPIO_PIN_11
#define		LED2					GPIOB
#define		LED2_PIN				GPIO_PIN_1
#define		LED3					GPIOA
#define		LED3_PIN				GPIO_PIN_4
#define		LED4					GPIOA
#define		LED4_PIN				GPIO_PIN_5

#define 	SET_GPIO_OUT(x)				Set_GPIO_PIN(x,x##_PIN,GPIO_SPEED_FREQ_LOW,GPIO_MODE_OUTPUT_PP)
#define 	SET_GPIO_IN(x)				Set_GPIO_PIN(x,x##_PIN,GPIO_SPEED_FREQ_LOW,GPIO_MODE_INPUT)

#define 	SET_GPIO_L(x)				(x->BSRR = (uint32_t)((x##_PIN)<<16U)) 
#define 	SET_GPIO_H(x)				(x->BSRR = (x##_PIN)) 
#define		TogglePin(x)				(x->ODR ^= x##_PIN)
#define 	READ_GPIO_PIN(x)			(((x->IDR & x##_PIN)!= GPIO_PIN_RESET) ? 1 : 0) 

void MX_GPIO_Init(void);
void Set_GPIO_PIN(GPIO_TypeDef *gpio, uint16_t nPin,uint32_t speed,uint32_t mode);
#endif



/*****************************END OF FILE*************************************************/
