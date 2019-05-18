#include "RunTask1.h"
#include "gpio.h"
#include "uart.h"
#include "Memory.h"
#include "Debugprintf.h"

struct msg
{
	u8 *data_prt;
	u32 data_size;
};

void send_op(void *data,rt_size_t len)
{
	struct msg msg_prt;
	msg_prt.data_prt = data;
	msg_prt.data_size = len;
	rt_mq_send(&mq_task,(void *)&msg_prt,sizeof(struct msg));
}

void message_handler_entry(void* parameter)
{
	struct msg msg_prt;
	if(rt_mq_recv(&mq_task,(void *)&msg_prt,sizeof(struct msg),0) == RT_EOK)
	{
		TogglePin(LED4);
		rt_kprintf("mq message = %s",msg_prt.data_prt);
	}
}

void tim1_thread_entry(void* parameter)
{
	;//rt_kprintf("periodic timer is timeout\n");
	TogglePin(LED3);
}
void tim2_thread_entry(void* parameter)
{
	;//rt_kprintf("onece timer is timeout\n");
}

void task1_thread_entry(void* parameter)
{

	while (1)
	{
		TogglePin(LED1);
		//printf("uart6 test printf\r\n");
		//rt_kprintf("led1_thread running\r\n");
		rt_thread_delay(140);
	}
}
void task2_thread_entry(void* parameter)
{

	while(1)
	{
		TogglePin(LED2);
		//rt_kprintf("led2_thread running\r\n");
		rt_thread_delay(80);
	}
}

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
				printf_dma("%s",buf);
				if(i++>9)
				{
					i=1;
					rt_memset(tbuf,0,sizeof(tbuf));
				}
				rt_memcpy(tbuf,buf,i);
				send_op(tbuf,i);
			}
		}
		rt_thread_delay(150);
	}
}




