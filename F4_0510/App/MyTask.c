#include "FreeRTOS.h"
#include "task.h"
#include "Memory.h"
#include "MyTask.h"
#include "SysGpio.h"
#include "SysUart.h"
#include "Debugprintf.h"
#include "Command.h"
#include "Analysis.h"
#include "Wifi.h"
#include "Pack.h"
#include "WifiCon.h"
#include "test.h"
#include "ReCmd.h"
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С
#define START_STK_SIZE 		128
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

#define MASTER1_TASK_PRIO		2
#define MASTER1_STK_SIZE 		512
TaskHandle_t MASTER1Task_Handler;
void master1_task(void *pvParameters);

#define MASTER2_TASK_PRIO		3
#define MASTER2_STK_SIZE 		512
TaskHandle_t MASTER2Task_Handler;
void master2_task(void *pvParameters);

#define MASTER3_TASK_PRIO		4
#define MASTER3_STK_SIZE 		64
TaskHandle_t MASTER3Task_Handler;
void master3_task(void *pvParameters);

#define MASTER4_TASK_PRIO		5
#define MASTER4_STK_SIZE 		512
TaskHandle_t MASTER4Task_Handler;
void master_wifi_task(void *pvParameters);


void start_system()
{
	
	xTaskCreate((TaskFunction_t )start_task,            //������
				(const char*    )"start_task",          //��������
				(uint16_t       )START_STK_SIZE,        //�����ջ��С
				(void*          )NULL,                  //���ݸ��������Ĳ���
				(UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
				(TaskHandle_t*  )&StartTask_Handler);   //������              
	vTaskStartScheduler();          //�����������
}
//��ʼ����������
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();			//�����ٽ���
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
				
	xTaskCreate((TaskFunction_t )master_wifi_task,
				(const char*    )"master_wifi_task",
				(uint16_t       )MASTER4_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER4_TASK_PRIO,
				(TaskHandle_t*  )&MASTER4Task_Handler);
	vTaskDelete(StartTask_Handler);	//ɾ����ʼ����
	taskEXIT_CRITICAL();			//�˳��ٽ���
}


void master1_task(void *pvParameters)
{
	//u16 time = 0;
	bool i=false;
	//one_cmd();
	//cmd_read();
	//wifi_init();
	wifi_reset();
	//testcj();
	while(1)
	{
		i = !i;
		if(i)
		{
			SET_GPIO_H(LED1_GPIO);
			SET_GPIO_L(LED2_GPIO);
		}
		else
		{
			SET_GPIO_L(LED1_GPIO);
			SET_GPIO_H(LED2_GPIO);
		}
		wifi_con();
		vTaskDelay(50);
	}
}

void master2_task(void *pvParameters)
{
	u8 tagtype,type,taglen;
	u8 buf[12];
	Wifi_t.respond = true;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		if((!fifo_empty(&TagFifo))&&(Wifi_t.respond == true))
		{
			tag_out_fifo(&TagFifo,&tagtype,&type,&taglen,&buf[0]);
			Pack(buf,taglen,0x0a);
			Wifi_t.respond = false;
		}
		vTaskDelay(30);
	}
}

void master3_task(void *pvParameters)
{
	u8 len,lentemp;
	while(1)
	{
		if(!fifo_empty(&Uart1Fifo))
		{
			if(info_out_fifo(&Uart1Fifo,&len,&tagdata.data[0]))
			{
				find_tag(tagdata.data,&lentemp,&tagdata.tag[0]);
			}
		}
		vTaskDelay(20);
	}
}

void master_wifi_task(void *pvParameters)
{
	u8 temp;
	u8 i;
	u8 buf[256];
	while(1)
	{
		if(Wifi_t.connect)
		{
			if(!fifo_empty(&WifiFifo))
			{
				temp = fifo_find(&WifiFifo,(u8 *)"msg!ok",6);
				if(fifo_cmp(&WifiFifo,temp,(u8 *)"msg!ok",6))
				{
					fifo_Clr(&WifiFifo);
					Wifi_t.respond = true;
				}

				temp = fifo_find(&WifiFifo,(u8 *)"A2",2);
				if(fifo_cmp(&WifiFifo,temp,(u8 *)"A2",2))
				{
					i =0;
					while(fifo_getc(&WifiFifo,&buf[i++]));
					buf[i] = '\0';
					printf_dma("%s",buf);
					Analysis_cmd(buf);
					fifo_Clr(&WifiFifo);
				}
			}
		}
		else
		{
			;
		}
		vTaskDelay(50);
	}
}







