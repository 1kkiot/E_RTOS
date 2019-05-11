/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Wifi.c
Description		: ��Ҫʵ��Wifiģ���ʼ�������ӹ���
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-04
Modify			: 
Modify Time		: 
******************************************************************************/
/*
˵��������wifi�����������ʱ�������⣬�����Ҫ��wifiģ����Զ�����֮ǰ���ӹ����ȵ�
ֻ�ܵȴ�wifiģ�鹤����ɣ��ſ��Զ�����в���������������ʱ����
��check�����������ʱ������Ҫ����Ϊʹ�ö��е���ͬʱ�п��ܳ�������û�н�����ɵ�
����¶�����н�������ȷ������������ʱ������ϣ���������Եõ����õ��Ż�
*/
#include "Wifi.h"
#include "Delay.h"

_WIFI_t Wifi_t;

/*******************************************************************************
* @Function		:u8 *check_cmd(u8 *cmd)
* @Description	:��Ҫʵ��check�Ƿ�����ȷ����cmd
* @Input		:*cmd
* @Output		:null
* @Return		:*cmd or null
* @Others		:null
*******************************************************************************/
u8 *check_cmd(u8 *cmd)
{
	char *strx=NULL;
	u16 i = 0;
	u8 tbuf[512];
	while(fifo_getc(&WifiFifo,&tbuf[i++]))
	{
		;
	}
	tbuf[i] = '\0';
	//printf_dma("%s",tbuf);
	strx=strstr((const char*)&tbuf[0],(const char*)cmd);
	return (u8*)strx;
}

/*******************************************************************************
* @Function		:u8 wifi_mode_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
* @Description	:��Ҫʵ��wifiģ�鷢���������
* @Input		:*cmd�������� *ackԤ�ڻ�Ӧ���� waittime�ȴ�ʱ��
* @Output		:null
* @Return		:0 or 1
* @Others		:null
*******************************************************************************/
u8 wifi_mode_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0;
	wifi_printf("%s",cmd);
	if(ack && waittime)
	{
		delay_xms(5);
		while(--waittime)
		{
			delay_xms(1);
			if(!fifo_empty(&WifiFifo))
			{
				if(check_cmd(ack))
				{
					printf_dma("send ok %s\n",cmd);
					res = 0;
					break;
				}
			}
		}
		if(waittime == 0)
		{
			return res;
		}
	}
	return res;
}

/*******************************************************************************
* @Function		:void wifi_reset()
* @Description	:�����Ͽ�tcp����
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void wifi_reset()
{
	//wifi_mode_send_cmd((u8 *)BACKAT,(u8 *)OK,2000);
	wifi_printf("%s",BACKAT);
	delay_xms(3200);
	wifi_mode_send_cmd((u8 *)CLOSESER,(u8 *)OK,50);
	wifi_mode_send_cmd((u8 *)EXITLINK,(u8 *)OK,50);
}

/*******************************************************************************
* @Function		:void wifi_init()
* @Description	:��Ҫʵ��wifiģ���ʼ������
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void wifi_init()
{
	wifi_reset();
	wifi_mode_send_cmd((u8 *)AT,(u8 *)OK,10);
	wifi_mode_send_cmd((u8 *)ATE1,(u8 *)OK,10);
	wifi_mode_send_cmd((u8 *)AT,(u8 *)OK,10);
	wifi_mode_send_cmd((u8 *)AT,(u8 *)OK,10);
	wifi_mode_send_cmd((u8 *)ATE0,(u8 *)OK,10);
	wifi_mode_send_cmd((u8 *)WIFIMODE,(u8 *)OK,10);
	wifi_mode_send_cmd((u8 *)RST,(u8 *)OK,10);
	wifi_mode_send_cmd((u8 *)CWJAP,(u8 *)OK,80);
	delay_xms(2000);
	wifi_mode_send_cmd((u8 *)CIPMUX,(u8 *)OK,80);
	delay_xms(1300);
	wifi_mode_send_cmd((u8 *)CIPMODE1,(u8 *)OK,80);
	delay_xms(300);
	wifi_mode_send_cmd((u8 *)CIPSTART,(u8 *)OK,80);
	delay_xms(300);
	if(wifi_mode_send_cmd((u8 *)CIPSEND,(u8 *)START,100) == 0)
	{
		Wifi_t.connect = true;
		wifi_printf("test tcp send\r\n");
		printf_dma("tcp connect ok\r\n");
	}
	else
	{
		Wifi_t.connect = false;
	}
}

















