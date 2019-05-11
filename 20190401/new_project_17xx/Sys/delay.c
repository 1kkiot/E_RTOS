/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : delay.c
Description: 只要实现软件延时不是很精确，希望你可以使用系统滴答定时器来实现精确延时
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-09
Modify	   : 
Modify Time: 
******************************************************************************/
#include "delay.h"
extern u16 Systick_delay;
/*******************************************************************************
* @Function		:void delay_50us(u16 n)
* @Description	:50us级延时函数
* @Input		:延时长度
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void delay_50us(u16 n)
{
	u16 i,j;
	for(i=n;i>0;i--)
	{
		for(j=1000;j>0;j--)
		{
			;
		}
	}
}
/*******************************************************************************
* @Function		:void Delay_ms(u16 n)
* @Description	:ms级延时函数
* @Input		:延时长度
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void Delay_ms(u16 n)
{
	u16 i,j;
	for(i=n;i>0;i--)
	{
		for(j=20;j>0;j--)
		{
			delay_50us(1);
		}
	}

}
/*****************************************************************************
函数名:void Tick_delay_ms (u16 tick) 
函数功能:毫秒延时函数
参数:毫秒参数// 单位ms
返回值:无
******************************************************************************/
void Tick_delay_ms(u16 tick) 
{
	u16 systickcnt;
	systickcnt = Systick_delay;
	while ((Systick_delay - systickcnt) < tick);
}






