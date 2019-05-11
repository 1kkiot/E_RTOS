/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Sys.c
Description: set System clock init
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include "Sys.h"
#include "base.h"
#include "radio_config.h"
#include "system_nrf51.h"
void sysinit(void)
{
	 //判断电源时钟状态
	 if((((*(uint32_t *)0xF0000FE0) & 0xFF) == 1) && (((*(uint32_t *)0xF0000FE4) & 0xF) == 0))
	{
		if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x0) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
		{
			//解决radio无法写入  
			*(uint32_t *)0x40000504 = 0xC007FFDF;//电源时钟设置
			*(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE设置    
		}
		else if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x10) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
		{
			//解决radio无法写入  
			*(uint32_t *)0x40000504 = 0xC007FFDF;//电源时钟设置
			*(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE设置  
		}
		else if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x30) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
		{
			//解决radio无法写入  
			*(uint32_t *)0x40000504 = 0xC007FFDF;//电源时钟设置
			*(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE设置    
		}
	}
	NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;//HFCLK晶振运行状态0关闭，1运行
	NRF_CLOCK->TASKS_HFCLKSTART = 1;//高外晶振HFCLK 0关闭，1启动
	while(!NRF_CLOCK->EVENTS_HFCLKSTARTED);//等待HFCLK晶振运行状态为1

}





