/*****************************************************************************
File name  : RunTask1.h
Description: 主要实现任务初始化相关定义功能
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-05-15
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _runtask1_h
#define _runtask1_h
#include "TaskInit.h"
struct msg
{
	u8 *data_prt;
	u32 data_size;
};

void task1_thread_entry(void* parameter);
void task2_thread_entry(void* parameter);
void task3_thread_entry(void* parameter);
void task4_thread_entry(void* parameter);
void message_handler_entry(void* parameter);
void tim1_thread_entry(void* parameter);
void tim2_thread_entry(void* parameter);

#endif

