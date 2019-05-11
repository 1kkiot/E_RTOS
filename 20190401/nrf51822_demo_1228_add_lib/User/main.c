/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : main.c
Description: ʵ��mcu�����ʼ�����̳߳�ʼ��
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
* @Description	:���������
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
	Thread_Login(FOREVER, 0, 20, &main_task);//������
	Thread_Login(FOREVER, 0, 15, &rf_function);//����radio�������ݹ���
	Thread_Login(FOREVER, 0, 10, &spi_function);//spi��Ϣ����
	wdt_init();//�������Ź���ϵͳ�쳣��������
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








