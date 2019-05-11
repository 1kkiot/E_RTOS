/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : wdt.c
Description: 实现看门狗初始化及相关操作
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-03-06
Modify	   : 
Modify Time: 
******************************************************************************/
#include "wdt.h"
#include "nrf51.h"
#include "nrf51_bitfields.h"
#include "nrf_delay.h"
/*******************************************************************************
* @Function		:void wdt_init(void)
* @Description	:初始化系统看门狗2s
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void wdt_init(void)
{
	NRF_WDT->TASKS_START = 0;
	NRF_WDT->CRV = RELOAD_COUNT;
	NRF_WDT->CONFIG = WDT_CONFIG_HALT_Pause << WDT_CONFIG_HALT_Pos | \
						WDT_CONFIG_SLEEP_Pause << WDT_CONFIG_SLEEP_Pos;
	NRF_WDT->RREN = WDT_RREN_RR0_Enabled << WDT_RREN_RR0_Pos;
	wdt_start();
}
/*******************************************************************************
* @Function		:void wdt_start(void)
* @Description	:开启看门狗
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/ 
void wdt_start(void)
{
	NRF_WDT->TASKS_START = 1;
}
/*******************************************************************************
* @Function		:void wdt_feed(void)
* @Description	:喂狗程序
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/ 
void wdt_feed(void)
{
	if(NRF_WDT->RUNSTATUS & WDT_RUNSTATUS_RUNSTATUS_Msk)
		NRF_WDT->RR[0] = WDT_RR_RR_Reload;
}
/*******************************************************************************
* @Function		:void wdt_stop(void)
* @Description	:停止看门狗功能
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/ 
void wdt_stop(void)
{
	NRF_WDT->TASKS_START = 0;
}

















