/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Delay.c
Description		: 主要实现在freertos中软件延时并不发生任务切换
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-03-29
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Delay.h"

#include "FreeRTOS.h"							//FreeRTOS使用
#include "task.h"

static u32 fac_us=0;							//us延时倍乘数
static u16 fac_ms=0;							//ms延时倍乘数,在os下,代表每个节拍的ms数
extern void xPortSysTickHandler(void);
/*******************************************************************************
* @Function		:void SysTick_Handler(void)
* @Description	:系统滴答中断函数
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
* @Description	:为freertos提供系统滴答
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void RunSysTick()
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//系统已经运行
	{
		xPortSysTickHandler();
	}
}
/*******************************************************************************
* @Function		:void delay_init(u8 SYSCLK)
* @Description	:进行软件延时初始化
* @Input		:主频MHZ
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
//SYSTICK的时钟固定为AHB时钟
//SYSCLK:系统时钟频率
void delay_init(u8 SYSCLK)
{
	u32 reload;
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTick频率为HCLK
	fac_us=SYSCLK;							//不论是否使用OS,fac_us都需要使用
	reload=SYSCLK;							//每秒钟的计数次数 单位为K	   
	reload*=1000000/configTICK_RATE_HZ;		//根据configTICK_RATE_HZ设定溢出时间
											//reload为24位寄存器,最大值:16777216,在180M下,约合0.745s左右
	fac_ms=1000/configTICK_RATE_HZ;			//代表OS可以延时的最少单位
    SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//开启SYSTICK中断
	SysTick->LOAD=reload; 					//每1/configTICK_RATE_HZ断一次	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; //开启SYSTICK
}
/*******************************************************************************
* @Function		:void delay_us(u32 nus)
* @Description	:进行us级延时测试延时函数基本准确
* @Input		:延时时长
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
//延时nus
//nus:要延时的us数.	
//nus:0~190887435(最大值即2^32/fac_us@fac_us=22.5)
void delay_us(u32 nus)
{
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;				//LOAD的值
	ticks=nus*fac_us; 						//需要的节拍数 
	told=SysTick->VAL;						//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;
		if(tnow!=told)
		{
			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}  
	};
}
/*******************************************************************************
* @Function		:void delay_ms(u32 nus)
* @Description	:进行ms级延时测试延时函数基本准确，会引起任务调度
* @Input		:延时时长
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
//nms:要延时的ms数
//nms:0~65535
void delay_ms(u32 nms)
{	
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//系统已经运行
	{		
		if(nms>=fac_ms)						//延时的时间大于OS的最少时间周期 
		{
			vTaskDelay(nms/fac_ms);	 		//FreeRTOS延时
		}
		nms%=fac_ms;						//OS已经无法提供这么小的延时了,采用普通方式延时    
	}
	delay_us((u32)(nms*1000));				//普通方式延时
}
/*******************************************************************************
* @Function		:void delay_xms(u32 nus)
* @Description	:进行ms级延时测试延时函数基本准确，不会引起任务调度
* @Input		:延时时长
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
//nms:要延时的ms数
void delay_xms(u32 nms)
{
	u32 i;
	for(i=0;i<nms;i++) delay_us(1000);
}


















//不带操作系统时可以使用
///*
//函数功能：系统滴答微秒延时
//函数形参：nus
//返回值：无
//*/
//void systick_delay_us(u32 nus)
//{	
//	//21MHz = 21000000Hz/s  = 21000Hz/ms = 21us
//	if(nus>(0xffffff / 21))	//微秒，只要是大于这个值就不允许延时
//	{
//		return;
//	}
//	SysTick->CTRL &= ~(0x1<<2);//选择21MHz的时钟源
//	SysTick->VAL = 0x00; 	   //清空当前计数器的值
//	SysTick->LOAD = nus * 21;  //要记的数
//	SysTick->CTRL |= 1<<0;	   //使能倒计数寄存器
//	/** SysTick->CTRL中的Set bit 16 - count flag **/
//	while(!(SysTick->CTRL & (0x1<<16)))//等待定时时间达到产生(位16)的标志
//	{
//		;
//	}
//	SysTick->CTRL &= ~(1<<0);	//关闭倒数计数器 清零  可以不写
//	SysTick->VAL &= ~(1<<0);	//计数器清零   可以不写，寄存器有自动清零功能
//}


///*
//函数功能：系统滴答豪秒延时
//函数形参：nms
//返回值：无
//*/
//void systick_delay_ms(u16 nms)
//{	
//	//21MHz = 21000000Hz/s  = 21000Hz/ms
//	if(nms>(0xffffff / 21000))	//毫秒，只要是大于这个值就不允许延时
//	{
//		return;
//	}
//	SysTick->CTRL &= ~(0x1<<2);  //选择21MHz的时钟源
//	SysTick->VAL = 0x00; 	     //清空当前计数器的值
//	SysTick->LOAD = nms * 21000; //要记的数
//	SysTick->CTRL |= 1<<0;	     //使能倒计数寄存器
//	/** SysTick->CTRL中的Set bit 16 - count flag **/
//	while(!(SysTick->CTRL & (0x1<<16)))//等待定时时间达到产生(位16)的标志
//	{
//		;
//	}
//	SysTick->CTRL &= ~(1<<0);	//关闭倒数计数器 清零  可以不写
//	SysTick->VAL &= ~(1<<0);	//计数器清零   可以不写，寄存器有自动清零功能
//}


///*
//函数功能：系统滴答 实现任意ms级别的延时
//函数形参：nms
//返回值：  无   
//备注：    以500ms的延时为基准延时
//*/
//void systick_delay_xms(u32 xms)
//{
//	u16 i =0;//延时的倍数循环变量
//	//计算整数个基准延时
//	for(i=0; i<xms/500; i++)
//	{
//		systick_delay_ms(500);
//	}
//	//如果不是整数倍 有剩余的延时
//	if(xms%500!=0)  //有余数
//	{
//		systick_delay_ms(xms%500);
//	}
//}



