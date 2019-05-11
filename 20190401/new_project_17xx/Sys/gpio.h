/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : gpio.h
Description: 实现管脚定义头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-04
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _gpio_h
#define _gpio_h
#include "lpc17xx_gpio.h"
#include "base.h"
#include "lpc17xx_clkpwr.h"
#define		LED2				1
#define		LED2_PIN			1<<24
#define		BEEP				1
#define		BEEP_PIN			1<<20

#define		GPIO_OUT			1
#define		GPIO_IN				0
#define		SET_GPIO_OUT(x)		GPIO_SetDir(x,x##_PIN,GPIO_OUT)
#define		SET_GPIO_IN(x)		GPIO_SetDir(x,x##_PIN,GPIO_IN)
#define		SET_GPIO_H(x)		GPIO_SetValue(x,x##_PIN)
#define		SET_GPIO_L(x)		GPIO_ClearValue(x,x##_PIN)

u32 ReadGPIO(u8 num);//读管脚使用的函数
void LPC_GPIO_init(void);
void LED_toggle(void);

#endif

