/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : runflag.h
Description: 软件定时器相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-13
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _runflag_h
#define _runflag_h
#include "base.h"
#include "nrf.h"

typedef struct 
{
	uint32_t Hz1Tick;
	uint32_t Hz4Tick;
	uint32_t Hz10Tick;
	uint32_t Hz20Tick;
	uint32_t Hz50Tick;
	uint32_t Hz100Tick;
	uint32_t Hz250Tick;
	uint32_t Hz500Tick;
	uint32_t Hz1000Tick;
	uint8_t Hz1;
	uint8_t Hz4;
	uint8_t Hz10;
	uint8_t Hz20;
	uint8_t Hz50;
	uint8_t Hz100;
	uint8_t Hz250;
	uint8_t Hz500;
	uint8_t Hz1000;
}RunFlag_Type;

typedef struct 
{
	uint32_t capture;
	uint32_t count;
}IntervalTime_Type;

extern RunFlag_Type RunFlag;
void RunFlagInit(void);
void RunFlagHandler(void);

#endif

