/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : time.c
Description: 主要实现定时器初始化及中断实现
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include "time.h"
#include "nrf.h"
#include "Thread.h"
#include "runflag.h"
#include "nrf_gpio.h"
#include "gpio.h"
volatile unsigned long uwTick;
_TIME	tim0;
_COUNT	LLED;
/*******************************************************************************
* @Function		:void time_init(void)
* @Description	:定时器初始化函数
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void time_init(void)
{
	NRF_TIMER0->PRESCALER =4;
	NRF_TIMER0->MODE =0;
	NRF_TIMER0->BITMODE =3;
	NRF_TIMER0->CC[0]=1000;
	NRF_TIMER0->INTENSET =1<<16;
	NRF_TIMER0->SHORTS=1;
	NRF_TIMER0->TASKS_START=1;
	NVIC_SetPriority(TIMER0_IRQn,3);
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);
}
/*******************************************************************************
* @Function		:void TIMER0_IRQHandler()
* @Description	:定时器中断函数1ms
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void TIMER0_IRQHandler()//1ms测试准确
{
	if(NRF_TIMER0->EVENTS_COMPARE[0]==1)
	{
		NRF_TIMER0->EVENTS_COMPARE[0]=0;
		uwTick++;
		Thread_RunCheck();
		led_function();
//		if(tim0.us % 680 == 0)
//			tim0.flag = true;
//		if(tim0.us++ >= 999)
//		{
//			tim0.us = 0;
//			if(tim0.sec++ >= 59)
//			{
//				tim0.sec = 0;
//				if(tim0.min ++ >= 59)
//				{
//					tim0.min = 0;
//				}
//			}
//		}
	}
}
/*******************************************************************************
* @Function		:void start_led(u16 t)
* @Description	:闪灯操作
* @Input		:闪烁时间
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void start_led(u16 t)
{
	nrf_gpio_pin_set(LED);
	LLED.Flag = true;
	LLED.star = t;
}
/*******************************************************************************
* @Function		:void led_function()
* @Description	:是否进行闪灯操作
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void led_function()
{
	if(LLED.Flag)
	{
		if(LLED.count++ >= LLED.star)
		{
			LLED.Flag = false;
			nrf_gpio_pin_clear(LED);
		}
	}
	else
	{
		LLED.count = 0;
	}
}




