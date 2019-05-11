#ifndef _sys_gpio_h
#define _sys_gpio_h
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#define		LED1_GPIO					GPIOA
#define		LED1_GPIO_PIN				GPIO_PIN_7
#define		LED2_GPIO					GPIOA
#define		LED2_GPIO_PIN				GPIO_PIN_6

#define 	SET_GPIO_OUT(x)				Set_GPIO_PIN(x,x##_PIN,GPIO_MODE_OUTPUT_PP,GPIO_SPEED_FREQ_LOW)
#define 	SET_GPIO_IN(x)				Set_GPIO_PIN(x,x##_PIN,GPIO_MODE_INPUT,GPIO_SPEED_FREQ_LOW)

#define 	SET_GPIO_L(x)				(x->BSRR = (uint32_t)((x##_PIN)<<16U)) 
#define 	SET_GPIO_H(x)				(x->BSRR = (x##_PIN)) 

#define 	READ_GPIO_PIN(x)			(((x->IDR & x##_PIN)!= GPIO_PIN_RESET) ? 1 : 0) 

void MX_GPIO_Init(void);
void Set_GPIO_PIN(GPIO_TypeDef *gpio, uint16_t nPin,uint32_t mode,uint32_t speed);
#endif





