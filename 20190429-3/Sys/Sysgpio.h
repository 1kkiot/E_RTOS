/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Sysgpio.h
Description		: 主要实现系统GPIO定义
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-25
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _sys_gpio_h
#define _sys_gpio_h

#include "arm_base_define.h"


#define		LED1						GPIOA
#define		LED1_PIN					GPIO_PIN_5
#define		LED2						GPIOA
#define		LED2_PIN					GPIO_PIN_6
#define		LED3						GPIOA
#define		LED3_PIN					GPIO_PIN_7
#define		LED4						GPIOB
#define		LED4_PIN					GPIO_PIN_0

#define 	SET_GPIO_OUT(x)				Set_GPIO_PIN(x,x##_PIN,GPIO_MODE_OUTPUT_PP,GPIO_SPEED_FREQ_LOW)
#define 	SET_GPIO_IN(x)				Set_GPIO_PIN(x,x##_PIN,GPIO_MODE_INPUT,GPIO_SPEED_FREQ_LOW)

#define 	SET_GPIO_L(x)				(x->BSRR = (uint32_t)((x##_PIN)<<16U)) 
#define 	SET_GPIO_H(x)				(x->BSRR = (x##_PIN)) 
#define		TogglePin(x)				(x->ODR ^= (x##_PIN))

#define 	READ_GPIO_PIN(x)			(((x->IDR & x##_PIN)!= GPIO_PIN_RESET) ? 1 : 0) 


void gpio_init(void);
void Set_GPIO_PIN(GPIO_TypeDef *gpio, u16 nPin,u32 mode,u32 speed);
#endif

