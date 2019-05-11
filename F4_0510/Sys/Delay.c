/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Delay.c
Description		: ��Ҫʵ����freertos�������ʱ�������������л�
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-03-29
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Delay.h"

#include "FreeRTOS.h"							//FreeRTOSʹ��
#include "task.h"

static u32 fac_us=0;							//us��ʱ������
static u16 fac_ms=0;							//ms��ʱ������,��os��,����ÿ�����ĵ�ms��
extern void xPortSysTickHandler(void);
/*******************************************************************************
* @Function		:void SysTick_Handler(void)
* @Description	:ϵͳ�δ��жϺ���
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void SysTick_Handler()
{
	RunSysTick();
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
/*******************************************************************************
* @Function		:void RunSysTick(void)
* @Description	:Ϊfreertos�ṩϵͳ�δ�
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void RunSysTick()
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
	{
		xPortSysTickHandler();
	}
}
/*******************************************************************************
* @Function		:void delay_init(u8 SYSCLK)
* @Description	:���������ʱ��ʼ��
* @Input		:��ƵMHZ
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
//SYSTICK��ʱ�ӹ̶�ΪAHBʱ��
//SYSCLK:ϵͳʱ��Ƶ��
void delay_init(u8 SYSCLK)
{
	u32 reload;
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTickƵ��ΪHCLK
	fac_us=SYSCLK;							//�����Ƿ�ʹ��OS,fac_us����Ҫʹ��
	reload=SYSCLK;							//ÿ���ӵļ������� ��λΪK	   
	reload*=1000000/configTICK_RATE_HZ;		//����configTICK_RATE_HZ�趨���ʱ��
											//reloadΪ24λ�Ĵ���,���ֵ:16777216,��180M��,Լ��0.745s����
	fac_ms=1000/configTICK_RATE_HZ;			//����OS������ʱ�����ٵ�λ
    SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//����SYSTICK�ж�
	SysTick->LOAD=reload; 					//ÿ1/configTICK_RATE_HZ��һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; //����SYSTICK
}
/*******************************************************************************
* @Function		:void delay_us(u32 nus)
* @Description	:����us����ʱ������ʱ��������׼ȷ
* @Input		:��ʱʱ��
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
//��ʱnus
//nus:Ҫ��ʱ��us��.	
//nus:0~190887435(���ֵ��2^32/fac_us@fac_us=22.5)
void delay_us(u32 nus)
{
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;				//LOAD��ֵ
	ticks=nus*fac_us; 						//��Ҫ�Ľ����� 
	told=SysTick->VAL;						//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;
		if(tnow!=told)
		{
			if(tnow<told)tcnt+=told-tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;
			told=tnow;
			if(tcnt>=ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	};
}
/*******************************************************************************
* @Function		:void delay_ms(u32 nus)
* @Description	:����ms����ʱ������ʱ��������׼ȷ���������������
* @Input		:��ʱʱ��
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
//nms:Ҫ��ʱ��ms��
//nms:0~65535
void delay_ms(u32 nms)
{	
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//ϵͳ�Ѿ�����
	{		
		if(nms>=fac_ms)						//��ʱ��ʱ�����OS������ʱ������ 
		{
			vTaskDelay(nms/fac_ms);	 		//FreeRTOS��ʱ
		}
		nms%=fac_ms;						//OS�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
	}
	delay_us((u32)(nms*1000));				//��ͨ��ʽ��ʱ
}
/*******************************************************************************
* @Function		:void delay_xms(u32 nus)
* @Description	:����ms����ʱ������ʱ��������׼ȷ�����������������
* @Input		:��ʱʱ��
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
//nms:Ҫ��ʱ��ms��
void delay_xms(u32 nms)
{
	u32 i;
	for(i=0;i<nms;i++) delay_us(1000);
}


















//��������ϵͳʱ����ʹ��
///*
//�������ܣ�ϵͳ�δ�΢����ʱ
//�����βΣ�nus
//����ֵ����
//*/
//void systick_delay_us(u32 nus)
//{	
//	//21MHz = 21000000Hz/s  = 21000Hz/ms = 21us
//	if(nus>(0xffffff / 21))	//΢�룬ֻҪ�Ǵ������ֵ�Ͳ�������ʱ
//	{
//		return;
//	}
//	SysTick->CTRL &= ~(0x1<<2);//ѡ��21MHz��ʱ��Դ
//	SysTick->VAL = 0x00; 	   //��յ�ǰ��������ֵ
//	SysTick->LOAD = nus * 21;  //Ҫ�ǵ���
//	SysTick->CTRL |= 1<<0;	   //ʹ�ܵ������Ĵ���
//	/** SysTick->CTRL�е�Set bit 16 - count flag **/
//	while(!(SysTick->CTRL & (0x1<<16)))//�ȴ���ʱʱ��ﵽ����(λ16)�ı�־
//	{
//		;
//	}
//	SysTick->CTRL &= ~(1<<0);	//�رյ��������� ����  ���Բ�д
//	SysTick->VAL &= ~(1<<0);	//����������   ���Բ�д���Ĵ������Զ����㹦��
//}


///*
//�������ܣ�ϵͳ�δ������ʱ
//�����βΣ�nms
//����ֵ����
//*/
//void systick_delay_ms(u16 nms)
//{	
//	//21MHz = 21000000Hz/s  = 21000Hz/ms
//	if(nms>(0xffffff / 21000))	//���룬ֻҪ�Ǵ������ֵ�Ͳ�������ʱ
//	{
//		return;
//	}
//	SysTick->CTRL &= ~(0x1<<2);  //ѡ��21MHz��ʱ��Դ
//	SysTick->VAL = 0x00; 	     //��յ�ǰ��������ֵ
//	SysTick->LOAD = nms * 21000; //Ҫ�ǵ���
//	SysTick->CTRL |= 1<<0;	     //ʹ�ܵ������Ĵ���
//	/** SysTick->CTRL�е�Set bit 16 - count flag **/
//	while(!(SysTick->CTRL & (0x1<<16)))//�ȴ���ʱʱ��ﵽ����(λ16)�ı�־
//	{
//		;
//	}
//	SysTick->CTRL &= ~(1<<0);	//�رյ��������� ����  ���Բ�д
//	SysTick->VAL &= ~(1<<0);	//����������   ���Բ�д���Ĵ������Զ����㹦��
//}


///*
//�������ܣ�ϵͳ�δ� ʵ������ms�������ʱ
//�����βΣ�nms
//����ֵ��  ��   
//��ע��    ��500ms����ʱΪ��׼��ʱ
//*/
//void systick_delay_xms(u32 xms)
//{
//	u16 i =0;//��ʱ�ı���ѭ������
//	//������������׼��ʱ
//	for(i=0; i<xms/500; i++)
//	{
//		systick_delay_ms(500);
//	}
//	//������������� ��ʣ�����ʱ
//	if(xms%500!=0)  //������
//	{
//		systick_delay_ms(xms%500);
//	}
//}



