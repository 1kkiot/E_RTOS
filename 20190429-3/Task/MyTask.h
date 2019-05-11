/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: MyTask.h
Description		: 主要实现系统多任务管理功能相关定义
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-22
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _my_task_h
#define _my_task_h
#include "FreeRTOS.h"
#include "task.h"
#include "Sysgpio.h"
#include "arm_base_define.h"
#include "Delay.h"
#include "Sysuart.h"
void start_system(void);



#endif
