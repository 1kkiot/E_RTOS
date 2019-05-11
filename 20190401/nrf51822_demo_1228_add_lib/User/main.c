/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : main.c
Description: 实现mcu外设初始化及线程初始化
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-13
Modify	   : 
Modify Time: 
******************************************************************************/
#include "radio_config.h"
#include "Sys.h"
#include "time.h"
#include "uart.h"
#include "gpio.h"
#include "memory.h"
#include "task.h"
#include "runflag.h"
#include "SPI.h"
#include "Flash.h"
#include "wdt.h"
/*******************************************************************************
* @Function		:int main(void)
* @Description	:主程序入口
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
int main(void)
{
	sysinit();
	time_init();
	Init_fifo();
	RunFlagInit();
	gpio_inti();
	spis_gpio_init();
	usart_init();
	flash_init();
//	flash_test();
	radio_temp_init();
	radio_configure();
	radio();
	Thread_Init();
	Thread_Login(FOREVER, 0, 20, &main_task);//主任务
	Thread_Login(FOREVER, 0, 15, &rf_function);//处理radio接收数据功能
	Thread_Login(FOREVER, 0, 10, &spi_function);//spi消息队列
	wdt_init();//开启看门狗，系统异常重新启动
	printf("System start ID=%d!\r\n",ID);
	while(1)
	{
		RunFlagHandler();
		Thread_Process();
		spis_process();
		wdt_feed();
	}
}

/**
 *@}
 **/








