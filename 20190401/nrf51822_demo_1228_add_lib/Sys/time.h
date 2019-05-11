/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : time.h
Description: 系统定时器相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _time_h
#define _time_h

#include "base.h"

void time_init(void);
void led_function(void);
void start_led(u16 t);
#pragma pack(1)
typedef struct
{
	uint8_t	hour;
	uint8_t min;
	uint8_t sec;
	uint16_t us;
	uint8_t flag;
}_TIME;
typedef struct
{
	u8		Flag;
	u16		star;
	u16		count;
}_COUNT;

extern _TIME	tim0;
#endif


