/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: WifiCon.c
Description		: ��Ҫʵ��wifi���ӹ��ܺͼ�������Ƿ�����
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-09
Modify			: 
Modify Time		: 
******************************************************************************/
#include "WifiCon.h"
#include "Memory.h"

_STATUS WifiStatus = AT_e;
_CONNECT_s Wifi_s;

void cmd_wait_time(u8 num)
{
	Wifi_s.flag = true;
	Wifi_s.count = 0;
	Wifi_s.wait = num;
}

/*******************************************************************************
* @Function		:void wifi_con()
* @Description	:��Ҫʵ��wifi���ӹ���
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void wifi_con()
{
	if(Wifi_s.flag)
	{
		if(Wifi_s.wait > Wifi_s.count++)
		{
			return;
		}
	}
	Wifi_s.flag = false;
	switch(WifiStatus)
	{
		case OK_e:
			Wifi_t.connect = true;
			//printf_232("connect succ!\r\n");
			fifo_Clr(&WifiFifo);
			WifiStatus = BACKAT_e;
			break;
		case AT_e:
			if(wifi_mode_send_cmd((u8 *)AT,(u8 *)OK,10))
			{
				WifiStatus = AT_e;//ģ���쳣����������
			}
			else
			{
				WifiStatus = ATE0_e;//ģ������
			}
			break;
		case ATE0_e:
			if(wifi_mode_send_cmd((u8 *)ATE0,(u8 *)OK,10))
			{
				WifiStatus = AT_e;//ģ���쳣����������
			}
			else
			{
				WifiStatus = WIFIMODE_e;//ģ������
			}
			break;
		case WIFIMODE_e:
			if(wifi_mode_send_cmd((u8 *)WIFIMODE,(u8 *)OK,10))
			{
				WifiStatus = ATE0_e;//ģ���쳣����������
			}
			else
			{
				WifiStatus = RST_e;//ģ������
			}
			break;
		case RST_e:
			printf("%s",RST);
			WifiStatus = CWJAP_e;
			cmd_wait_time(100);
			break;
		case CWJAP_e:
			if((wifi_mode_send_cmd((u8 *)CWJAP,(u8 *)OK,10)))
			{
				WifiStatus = CIPMUX_e;//ģ���쳣����������
				cmd_wait_time(20);
			}
			else
			{
				WifiStatus = CIPMUX_e;//ģ������
				cmd_wait_time(20);
			}
			break;
		case CIPMUX_e:
			if(wifi_mode_send_cmd((u8 *)CIPMUX,(u8 *)OK,10))
			{
				WifiStatus = CIPMUX_e;//ģ���쳣����������
			}
			else
			{
				WifiStatus = CIPMODE1_e;//ģ������
				cmd_wait_time(20);
			}
			break;
		case CIPMODE1_e:
			if(wifi_mode_send_cmd((u8 *)CIPMODE1,(u8 *)OK,10))
			{
				WifiStatus = CIPMUX_e;//ģ���쳣����������
				cmd_wait_time(20);
			}
			else
			{
				WifiStatus = CIPSTART_e;//ģ������
				cmd_wait_time(20);
			}
			break;
		case CIPSTART_e:
			if(wifi_mode_send_cmd((u8 *)CIPSTART,(u8 *)OK,10))
			{
				WifiStatus = AT_e;//ģ���쳣����������
			}
			else
			{
				WifiStatus = CIPSEND_e;//ģ������
				cmd_wait_time(20);
			}
			break;
		case CIPSEND_e:
			if(wifi_mode_send_cmd((u8 *)CIPSEND,(u8 *)START,100))
			{
				WifiStatus = AT_e;//ģ���쳣����������
			}
			else
			{
				WifiStatus = OK_e;//���ӳɹ�
				cmd_wait_time(2);
			}
			break;
		case BACKAT_e:
			break;
		case CLOSESER_e:
			break;
		case EXITLINK_e:
			break;
		default:
			break;
	}
}















