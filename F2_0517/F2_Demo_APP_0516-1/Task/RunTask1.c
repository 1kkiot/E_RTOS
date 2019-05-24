/******************************************************************************
File name  : RunTask1.c
Description: 主要实现任务初始化
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-05-15
Modify	   : 
Modify Time: 
*******************************************************************************/
#include "RunTask1.h"
#include "gpio.h"
#include "uart.h"
#include "Memory.h"
#include "Debugprintf.h"
#include "mem_pool.h"
#include "LETN720.h"
#include "NRF24.h"

/*******************************************************************************
* @Function		:void send_op(void *data,rt_size_t len)
* @Description	:主要实现发送消息功能
* @Input		:*data,nPin,len
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void send_op(void *data,rt_size_t len)
{
	struct msg msg_prt;
	msg_prt.data_prt = data;
	msg_prt.data_size = len;
	rt_mq_send(&mq_task,(void *)&msg_prt,sizeof(struct msg));
}

/*******************************************************************************
* @Function		:void message_handler_entry(void* parameter)
* @Description	:主要实现定时接收消息
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void message_handler_entry(void* parameter)
{
	struct msg msg_prt;
	if(rt_mq_recv(&mq_task,(void *)&msg_prt,sizeof(struct msg),0) == RT_EOK)
	{
		;//TogglePin(LED4);
		;//rt_kprintf("mq message = %s",msg_prt.data_prt);
	}
}

/*******************************************************************************
* @Function		:void tim1_thread_entry(void* parameter)
* @Description	:主要实现软件定时器功能
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void tim1_thread_entry(void* parameter)
{
	;//rt_kprintf("periodic timer is timeout\n");
	TogglePin(LED3);
}

/*******************************************************************************
* @Function		:void tim2_thread_entry(void* parameter)
* @Description	:主要实现单次软件定时器功能
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void tim2_thread_entry(void* parameter)
{
	;//rt_kprintf("onece timer is timeout\n");
}

/*******************************************************************************
* @Function		:void task1_thread_entry(void* parameter)
* @Description	:主要实现任务一功能
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void task1_thread_entry(void* parameter)
{

	while (1)
	{
		;//TogglePin(LED1);
		//printf("uart6 test printf\r\n");
		//rt_kprintf("led1_thread running\r\n");
		rt_thread_mdelay(140);
	}
}

/*******************************************************************************
* @Function		:void task2_thread_entry(void* parameter)
* @Description	:主要实现任务二功能
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void task2_thread_entry(void* parameter)
{

	while(1)
	{
		;//TogglePin(LED4);
		//rt_kprintf("led2_thread running\r\n");
		rt_thread_mdelay(80);
	}
}

/*******************************************************************************
* @Function		:void task3_thread_entry(void* parameter)
* @Description	:主要实现任务三功能
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void task3_thread_entry(void* parameter)
{
	u8 i = 0;
	u8 buf[10];
	u8 tbuf[10];
	while(1)
	{
		if(!fifo_empty(&UartATFifo))
		{
			if(fifo_gets(&UartATFifo,&buf[0],10))
			{
				if(i++>9)
				{
					i=1;
					rt_memset(tbuf,0,sizeof(tbuf));
				}
				rt_memcpy(tbuf,buf,i);
				send_op(tbuf,i);
				printf_dma("%s",tbuf);
			}
		}
		rt_thread_mdelay(150);
	}
}

/*******************************************************************************
* @Function		:void task4_thread_entry(void* parameter)
* @Description	:主要实现任务四功能
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void task4_thread_entry(void* parameter)
{
	while(1)
	{
		//LTE_Connet();
		//TogglePin(LED4);
		NRF_TEST();
		rt_thread_mdelay(100);
	}
}


