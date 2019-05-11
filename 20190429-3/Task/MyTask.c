/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: MyTask.c
Description		: 主要实现系统多任务管理功能
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-22
Modify			: 
Modify Time		: 
******************************************************************************/
#include "MyTask.h"
#include "Fifo.h"
#include "Memory.h"
#include "Debugprintf.h"
#include "Command.h"
#include "Analysis.h"
#include "Wifi.h"
#include "WifiCon.h"
#include "ReCmd.h"
#include "Function.h"
#include "Pack.h"

#define START_TASK_PRIO		1
#define START_STK_SIZE 		64
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);

#define MASTER1_TASK_PRIO		3
#define MASTER1_STK_SIZE 		256
TaskHandle_t MASTER1Task_Handler;
void master1_task(void *pvParameters);

#define MASTER2_TASK_PRIO		2
#define MASTER2_STK_SIZE 		512
TaskHandle_t MASTER2Task_Handler;
void master2_task(void *pvParameters);

#define MASTER3_TASK_PRIO		4
#define MASTER3_STK_SIZE 		128
TaskHandle_t MASTER3Task_Handler;
void master3_task(void *pvParameters);

/*******************************************************************************
* @Function		:start_system
* @Description	:初始化主任务
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void start_system()
{
	xTaskCreate((TaskFunction_t )start_task,
				(const char*    )"start_task",
				(uint16_t       )START_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )START_TASK_PRIO,
				(TaskHandle_t*  )&StartTask_Handler);
	vTaskStartScheduler();
}

/*******************************************************************************
* @Function		:start_task
* @Description	:任务初始化
* @Input		:*pvParameters
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();

	xTaskCreate((TaskFunction_t )master1_task,
				(const char*    )"master1_task",
				(uint16_t       )MASTER1_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER1_TASK_PRIO,
				(TaskHandle_t*  )&MASTER1Task_Handler);

	xTaskCreate((TaskFunction_t )master2_task,
				(const char*    )"master2_task",
				(uint16_t       )MASTER2_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER2_TASK_PRIO,
				(TaskHandle_t*  )&MASTER2Task_Handler);

	xTaskCreate((TaskFunction_t )master3_task,
				(const char*    )"master3_task",
				(uint16_t       )MASTER3_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER3_TASK_PRIO,
				(TaskHandle_t*  )&MASTER3Task_Handler);

	vTaskDelete(StartTask_Handler);
	taskEXIT_CRITICAL();
}

/*******************************************************************************
* @Function		:master1_task
* @Description	:任务一用于232通信
* @Input		:*pvParameters
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void master1_task(void *pvParameters)//
{
//	u8 tmp;
	u8 len;
	u8 lentemp;
	u8 tagtype,type,taglen;
	u8 buf[64];
	Wifi_t.respond = true;
	while(1)
	{
		TogglePin(LED1);
		if(!fifo_empty(&TagCacheFifo))
		{
			if(info_out_fifo(&TagCacheFifo,&len,&tagdata.data[0]))
			{
				find_tag(tagdata.data,&lentemp,&tagdata.tag[0]);
			}
//			len =0;
//			tmp = fifo_validSize(&TagCacheFifo);
//			if(fifo_gets(&TagCacheFifo,buf,tmp))
//			{
////				printf_232("232=%s",buf);
////				printf("232->wifi=%s",buf);
//				printf_1(buf,tmp);
//				memset(buf,0,tmp);
//			}
		}
		if((!fifo_empty(&TagFifo))&&(Wifi_t.respond == true))
		{
			tag_out_fifo(&TagFifo,&tagtype,&type,&taglen,&buf[0]);
			Pack(buf,taglen,0x0a);
			Wifi_t.respond = false;
			memset(buf,0,sizeof(buf));
		}
		vTaskDelay(50);
	}
}

/*******************************************************************************
* @Function		:master2_task
* @Description	:用于数据打包如对
* @Input		:*pvParameters
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void master2_task(void *pvParameters)//
{
	u16 tmp;
	u8 buf[256];
	while(1)
	{
		TogglePin(LED2);
		wifi_con();
		if(Wifi_t.connect)
		{
			if(!fifo_empty(&WifiFifo))
			{
				tmp = fifo_find(&WifiFifo,(u8 *)"msg!ok",6);
				if(fifo_cmp(&WifiFifo,tmp,(u8 *)"msg!ok",6))
				{
					fifo_Clr(&WifiFifo);
					Wifi_t.respond = true;
				}

				tmp = fifo_validSize(&WifiFifo);
				memset(buf,0,sizeof(buf));
				if(fifo_gets(&WifiFifo,buf,tmp))
				{
					//printf_232("link_wifi->%s\r\n",buf);
					Analysis_cmd(buf);
				}
			}
		}
		else
		{
			fifo_Clr(&WifiFifo);
		}
		vTaskDelay(50);
	}
}

/*******************************************************************************
* @Function		:master3_task
* @Description	:实现报警功能和盘点功能
* @Input		:*pvParameters
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void master3_task(void *pvParameters)//
{
	while(1)
	{
		TogglePin(LED3);
		if(RunFlag.autof)
		{
			RunFlag.autof = false;
			read_tag_cmd();
			TogglePin(LED4);
			//printf("inventory=%d",RunFlag.autonum);
		}
		if(Wifi_t.connect)
		{
			Read_fun();
		}
//		if(RunFlag.read1)
//		{
//			RunFlag.read1 = false;
//			cmd11();
//		}
//		if(RunFlag.read2)
//		{
//			RunFlag.read2 = false;
//			cmd10();
//		}
		Count_time();
		vTaskDelay(100);
	}
}




