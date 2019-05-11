/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : time.c
Description: ��Ҫʵ��ϵͳ��ʱ����ʼ��,ʹ�ÿ⺯���㲻��������һ�μĴ���
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
 * ��������:   void Timer_Timer0Init()
 * ��������:   1ms��ʱ��
 * ǰ������:   ��
 * ����:       ��
 * ���:       ��
 * ����        
 * ע��:       
 *****************************************************************************/
void Timer_Timer0Init(uint32_t clk, uint32_t howtime)//������ʱ�����ӵ��������ʾ��������1s��������0109
{
	LPC_SC->PCONP|=(1<<1);//��TIMER0����ʱ��
	LPC_TIM0->CTCR &=(~0x03);//�������ƼĴ���
	LPC_TIM0->CTCR |=0x00;//��ʱ��ģʽ
	//----PC=PR-----TC++
	LPC_TIM0->TC =0;//��ʱ������
	LPC_TIM0->PR =0;//Ԥ��Ƶ�Ĵ���
	LPC_TIM0->PC =0;//Ԥ��Ƶ������
	LPC_TIM0->TCR |=(1<<1);//��ʱ�����ƼĴ���--��λ��ʱ��
	LPC_TIM0->TCR &=~(1<<1);//�����λ
	LPC_TIM0->PR =clk-1;
	LPC_TIM0->IR=0xFFFFFFFF;   //����ж�
	//--------------------
	LPC_TIM0->MR0=howtime;//ƥ��Ĵ���---���ٸ�1us��ƥ��
	LPC_TIM0->MCR &=~(0x07);  //ƥ����ƼĴ���--��ֹƥ��-��λ-ֹͣ�������ж�
	LPC_TIM0->MCR |=(1<<0); //����ƥ���ж�
	LPC_TIM0->MCR |=(1<<1); //����λ�ж�--ƥ��ʱTC��λ-���¼���
	NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));  //���ö�ʱ���ж����ȼ�
	NVIC_EnableIRQ(TIMER0_IRQn);   //��ʱ���ж�ʹ��
	LPC_TIM0->TCR |=(1<<0);  //������ʱ��
}
/*******************************************************************************
* @Function		:void TIMER0_IRQHandler(void)
* @Description	:��ʱ���жϺ���
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
* @Description	:ϵͳ�жϳ�ʼ��
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
* @Description	:ϵͳ�жϺ���1ms
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
* @Description	:�Ƿ�������Ʋ���
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
* @Description	:�Ƿ�������Ʋ���
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














