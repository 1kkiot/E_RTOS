/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Wifi.c
Description		: 主要实现Wifi模块初始化及连接功能
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-04
Modify			: 
Modify Time		: 
******************************************************************************/
/*
说明：关于wifi程序中添加延时函数问题，这个主要是wifi模块会自动连接之前连接过的热点
只能等待wifi模块工作完成，才可以对其进行操作，故添加软件延时函数
在check命令中添加延时函数主要是因为使用队列的是同时有可能出现数据没有接收完成的
情况下对其进行解析不正确，故添加软件延时函数，希望后续可以得到更好的优化
*/
#include "Wifi.h"
#include "Delay.h"

_WIFI_t Wifi_t;

/*******************************************************************************
* @Function		:u8 *check_cmd(u8 *cmd)
* @Description	:主要实现check是否有正确返回cmd
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
* @Description	:主要实现wifi模块发送相关命令
* @Input		:*cmd发送命令 *ack预期回应命令 waittime等待时间
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
* @Description	:主动断开tcp连接
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
* @Description	:主要实现wifi模块初始化功能
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

















