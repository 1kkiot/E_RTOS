/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Function.h
Description		: 主要实现上位机下发指令执行功能相关宏定义
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-27
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _function_h
#define _function_h

#include "arm_base_define.h"

#define		VER			"VER_1.0.1_20190427"


typedef struct{
	u8 *head;
	u8 *id;
	u8 *iddata;
	u8 *cmd;
	u8 *cmddata;
}_Cmd;

struct attr_exe_data
{
	u8 *cmd;
	RunStatus (*exe_attr)(u8 *,u8 *);
};

#pragma pack(push,1)
typedef struct
{
	u8 alame;
	u8 alamet;
	u8 autof;
	u8 autonum;
	u8 tim;
	u8 timt;
	u8 ms;
	u8 sec;
	u8 min;
	u8 read1;
	u8 read2;
}_Run_s;
#pragma pack(pop)



extern _Run_s RunFlag;
void Count_time(void);
RunStatus MsgDeal(u8 *data,u32 len);
RunStatus Inv_fun(u8 *cmd,u8 *data);
RunStatus Alarm_fun(u8 *cmd,u8 *data);
RunStatus Ver_fun(u8 *cmd,u8 *data);
RunStatus Read1_fun(u8 *cmd,u8 *data);
RunStatus Read2_fun(u8 *cmd,u8 *data);
#endif


