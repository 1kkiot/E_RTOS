/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: main.c
Description		: 主程序入口
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-25
Modify			: 
Modify Time		: 
******************************************************************************/
#include "sys_clock.h"
#include "Sysgpio.h"
#include "Sysuart.h"
#include "Delay.h"
#include "MyTask.h"
#include "Memory.h"
#include "Wifi.h"
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	delay_init(48-1);
	gpio_init();
	Init_memory();
	MX_DMA_Init();
	MX_USART1_UART_Init();//wifi
	MX_USART3_UART_Init();//232
	SET_GPIO_H(LED3);
	wifi_reset();
	SET_GPIO_L(LED3);
	start_system();

}










