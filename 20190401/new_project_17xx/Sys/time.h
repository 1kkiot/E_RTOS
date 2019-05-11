/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : time.h
Description: 定时器相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-04
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _time_h
#define _time_h
#include "base.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_systick.h"

#pragma pack(push,1)
typedef struct{
	u16 num;
	u16 count;
	u8 flag;
}_COUNT;
#pragma pack(pop)

extern _COUNT	led;

void Timer_Timer0Init(uint32_t clk, uint32_t howtime);
void SysTickInit(void);
void start_led(u16 t);
void led_function(void);



#endif








