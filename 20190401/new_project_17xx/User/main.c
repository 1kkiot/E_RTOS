/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : main.c
Description: ʵ��mcu�����ʼ��������������л���ִ��
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-04
Modify	   : 
Modify Time: 
******************************************************************************/
#include "LPC17xx.h"
#include "system_LPC17xx.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"
#include "stdio.h"
#include "gpio.h"
#include "spi.h"
#include "runflag.h"
#include "time.h"
#include "wdt.h"
#include "Thread.h"
#include "fifo.h"
#include "memory.h"
#include "Analysis.h"
#include "logic.h"
#include "uart.h"
#include "delay.h"
#include "Bluetooth.h"
#include "setting.h"
/*******************************************************************************
* @Function		:int main(void)
* @Description	:������
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
int main(void)
{
	SystemInit();
	SysTickInit();
	LPC_GPIO_init();
	Timer_Timer0Init(25,1000);
	uart_config0(115200);
	uart_config3(115200);
	Init_fifo();
	Bluetooth_init();
	RunFlagInit();
	Thread_Init();
	Thread_Login(FOREVER, 0, 10, &CacheRxProcess);//spi������ս���
	Thread_Login(FOREVER, 0, 20, &CacheTxProcess);//spi���淢�ͽ���
	Thread_Login(FOREVER, 0, 30, &QueryProcess);//ѯ�ʽ��̲�ѯ�Ƿ��������ϱ�1754��ѯ51822
	Thread_Login(FOREVER, 0, 40, &SettingProcess);//ͨ��1754��������51822
	wdt_config();//���в�ι��ϵͳ����
	#ifdef debug
	printf("System start!!!");
	USART3_Printf("uart0 printf");
	#endif
	while(1)
	{
		LPC17XXSPI_Process();//������
		Thread_Process();
		RunFlagHandler();
		ble_function();
		get_ble_status();
		WDT_Feed();//ι��
	}
}





