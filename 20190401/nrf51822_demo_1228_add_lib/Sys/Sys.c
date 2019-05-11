/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Sys.c
Description: set System clock init
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include "Sys.h"
#include "base.h"
#include "radio_config.h"
#include "system_nrf51.h"
void sysinit(void)
{
	 //�жϵ�Դʱ��״̬
	 if((((*(uint32_t *)0xF0000FE0) & 0xFF) == 1) && (((*(uint32_t *)0xF0000FE4) & 0xF) == 0))
	{
		if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x0) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
		{
			//���radio�޷�д��  
			*(uint32_t *)0x40000504 = 0xC007FFDF;//��Դʱ������
			*(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE����    
		}
		else if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x10) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
		{
			//���radio�޷�д��  
			*(uint32_t *)0x40000504 = 0xC007FFDF;//��Դʱ������
			*(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE����  
		}
		else if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x30) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
		{
			//���radio�޷�д��  
			*(uint32_t *)0x40000504 = 0xC007FFDF;//��Դʱ������
			*(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE����    
		}
	}
	NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;//HFCLK��������״̬0�رգ�1����
	NRF_CLOCK->TASKS_HFCLKSTART = 1;//���⾧��HFCLK 0�رգ�1����
	while(!NRF_CLOCK->EVENTS_HFCLKSTARTED);//�ȴ�HFCLK��������״̬Ϊ1

}





