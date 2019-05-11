/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : gpio.c
Description: 主要实现gpio初始化
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-04
Modify	   : 
Modify Time: 
******************************************************************************/
#include "gpio.h"
void LPC_GPIO_init()
{
	//CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO,ENABLE);
	SET_GPIO_OUT(LED2);
	SET_GPIO_OUT(BEEP);
}
void LED_toggle()
{
	static u8 flag = 0;
	flag = !flag;
	(flag == true ) ? SET_GPIO_H(BEEP):SET_GPIO_L(BEEP);
}

u32 ReadGPIO(u8 num)
{
	return GPIO_ReadValue(num);
}



