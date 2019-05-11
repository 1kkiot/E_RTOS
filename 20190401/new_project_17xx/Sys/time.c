/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : time.c
Description: 主要实现系统定时器初始化,使用库函数搞不定，抄了一段寄存器
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-04
Modify	   : 
Modify Time: 
******************************************************************************/
#include "time.h"
#include "gpio.h"
#include "Thread.h"
extern volatile uint16_t usDelayms;
volatile unsigned long SysTickCnt;
u16 Systick_delay;
_COUNT	led;
/******************************************************************************
 * 函数名称:   void Timer_Timer0Init()
 * 功能描述:   1ms定时器
 * 前提条件:   无
 * 输入:       无
 * 输出:       无
 * 返回        
 * 注释:       
 *****************************************************************************/
void Timer_Timer0Init(uint32_t clk, uint32_t howtime)//垃圾定时器，坑爹啊，你把示波器调到1s就明白了0109
{
	LPC_SC->PCONP|=(1<<1);//打开TIMER0外设时钟
	LPC_TIM0->CTCR &=(~0x03);//计数控制寄存器
	LPC_TIM0->CTCR |=0x00;//定时器模式
	//----PC=PR-----TC++
	LPC_TIM0->TC =0;//定时计数器
	LPC_TIM0->PR =0;//预分频寄存器
	LPC_TIM0->PC =0;//预分频计数器
	LPC_TIM0->TCR |=(1<<1);//定时器控制寄存器--复位定时器
	LPC_TIM0->TCR &=~(1<<1);//清除复位
	LPC_TIM0->PR =clk-1;
	LPC_TIM0->IR=0xFFFFFFFF;   //清除中断
	//--------------------
	LPC_TIM0->MR0=howtime;//匹配寄存器---多少个1us将匹配
	LPC_TIM0->MCR &=~(0x07);  //匹配控制寄存器--禁止匹配-复位-停止产生的中断
	LPC_TIM0->MCR |=(1<<0); //允许匹配中断
	LPC_TIM0->MCR |=(1<<1); //允许复位中断--匹配时TC复位-重新计数
	NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));  //设置定时器中断优先级
	NVIC_EnableIRQ(TIMER0_IRQn);   //定时器中断使能
	LPC_TIM0->TCR |=(1<<0);  //启动定时器
}
/*******************************************************************************
* @Function		:void TIMER0_IRQHandler(void)
* @Description	:定时器中断函数
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void TIMER0_IRQHandler(void)
{
	if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)== SET)
	{
		;//LED_toggle();
	}
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}
/*******************************************************************************
* @Function		:void SysTickInit(void)
* @Description	:系统中断初始化
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void SysTickInit(void)
{
	SYSTICK_InternalInit(1);
	SYSTICK_IntCmd(ENABLE);
	SYSTICK_Cmd(ENABLE);
}
/*******************************************************************************
* @Function		:void SysTick_Handler(void)
* @Description	:系统中断函数1ms
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void SysTick_Handler(void)
{
	SysTickCnt++;
	Systick_delay++;
	Thread_RunCheck();
	led_function();
	if(usDelayms) 
	{
		usDelayms--;
	}
}
/*******************************************************************************
* @Function		:void start_led(u16 t)
* @Description	:是否进行闪灯操作
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void start_led(u16 t)
{
	SET_GPIO_H(LED2);
	SET_GPIO_H(BEEP);
	led.flag = true;
	led.num = t;
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
	if(led.flag)
	{
		if(led.count++ >= led.num)
		{
			led.flag = false;
			SET_GPIO_L(LED2);
			SET_GPIO_L(BEEP);
		}
	}
	else
	{
		led.count = 0;
	}
}














