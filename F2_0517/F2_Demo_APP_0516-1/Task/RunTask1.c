#include "RunTask1.h"
#include "gpio.h"
#include "uart.h"
#include "Memory.h"
#include "Debugprintf.h"

void led1_thread_entry(void* parameter)
{

	while (1)
	{
		TogglePin(LED1);
		//printf("uart6 test printf\r\n");
		//rt_kprintf("led1_thread running\r\n");
		rt_thread_delay(200);
	}
}
void led2_thread_entry(void* parameter)
{

	while(1)
	{
		TogglePin(LED2);
		//rt_kprintf("led2_thread running\r\n");
		rt_thread_delay(150);
	}
}

void task3_thread_entry(void* parameter)
{
	u8 buf[10];
	while(1)
	{
		if(!fifo_empty(&UartATFifo))
		{
			if(fifo_gets(&UartATFifo,&buf[0],10))
			{
				printf_dma("uart6 receive=%s\r\n",buf);
			}
		}
		rt_thread_delay(150);
	}
}




