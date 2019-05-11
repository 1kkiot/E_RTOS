/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : logic.c
Description: ��Ҫʵ�ָ�������ҵ���߼�
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-07
Modify	   : 
Modify Time: 
******************************************************************************/
#include  <string.h>
#include "logic.h"
#include "fifo.h"
#include "memory.h"
#include "stdio.h"
#include "spi.h"
#include "Analysis.h"
#include "gpio.h"
#include "uart.h"
#include "Bluetooth.h"
#include "time.h"
_RUN	Runspi;
_DATA	Data;//���м�¼����
_Pack	Pack;//Э���
/*******************************************************************************
* @Function		:u8 Escape(u8 *indata,u8 *outdata,u8 len)
* @Description	:ʵ�ֱ�ǩ��Ϣת�巵��
* @Input		:indata
* @Output		:outdata
* @Return		:null
* @Others		:null
********************************************************************************/
u8 Escape(u8 *indata,u8 *outdata,u8 len)
{
	u8 i,j;
	j=0;
	for(i=0;i<14;i++)//�˴��ǰ�����󳤶Ƚ���ת�����
	{
		if(indata[i] == 0x5a)
		{
			if(indata[++i] == 0xa5)
			{
				outdata[j++] = 0x00;
			}
			else
			{
				--i;
			}
		}
		else
		{
			outdata[j++] = indata[i];
		}
	}
	return true;
}
/*******************************************************************************
* @Function		:void CacheRxProcess(void)
* @Description	:ʵ��spi���ն��г��Ӳ�����
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
//���ձ�ǩ��Ϣ
//���ղ�ѯradio������Ϣ
void CacheRxProcess()
{
	u8 len_temp,len,buf[14],tbuf[10];
	u8 data_len;
	if(!fifo_empty(&CacheRx))
	{
		memset(Data.obuf,0,sizeof(Data.obuf));
		if(info_out_fifo(&CacheRx,&len_temp,&Data.obuf[0]))
		{
			Analysis_function(&Pack.cmdtype,&Pack.datatype,&Data.obuf[0],Data.obuf,&data_len);
			if(Pack.cmdtype == target)//��ǩ��Ϣ
			{
				start_led(10);
				Escape(Data.obuf,&buf[0],9);//ת�峤����ʱ���ã�������󳤶Ƚ���ת�����
				tbuf[0] = buf[5]; //rssi
				memcpy(tbuf+1,buf,5);//id
				#if 1
//				for(len=0;len<6;len++)
//				{
//					USART3_Printf("%02x ",buf[len]);
//				}
//				USART3_Printf("%02x ",Pack.datatype);//��ʾ�ڼ�ͨ��
				//Unpack_target(datatype,data,7);
				//if(Blevalue.ValidCode)
				{
					ble_target_unpack(Pack.datatype,tbuf,7);
					memset(buf,0,sizeof(buf));
					fifo_gets(&UartCache,buf,10);
					//memcpy(buf,"abcdfeghij",10);
					send_str_len(buf,1);//ble send
					USART3_Printf("%02x",buf[0]);
				}
//				for(len=0;len<10;len++)
//				{
//					USART3_Printf("%02x ",buf[len]);
//				}
				//USART3_Printf("%02x ",Pack.datatype);//��ʾ�ڼ�ͨ��
				#endif
			}
			else if(Pack.cmdtype == respond)//���û�Ӧ��Ϣ
			{
				respond_fun(Pack.datatype,Data.obuf,data_len);
			}
		}
	}
}
/*******************************************************************************
* @Function		:u8 respond_fun(u8 cmd,u8 *data,u8 len)
* @Description	:�����Ӧ��Ϣ
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
u8 respond_fun(u8 cmd,u8 *data,u8 len)
{
	u8 buf[20];
	buf[0] = cmd;
	memcpy(buf+1,data,len-5);
	USART3_Printf("%s",buf);
//	switch(cmd)
//	{
//		case setfer:
//			buf[0] = setfer;
//			memcpy(buf+1,data,len-5);
//			USART3_Printf("%s",buf);
//			break;
//		case setmac:
//			USART3_Printf("rf mac setting succ!!!");
//			break;
//		case setspeed:
//			USART3_Printf("rf speed setting succ!!!");
//			break;
//		case setdatalen:
//			USART3_Printf("rf datalen setting succ!!!");
//			break;
//		case selinfo:
//			memcpy(buf,data,len-5);
//			USART3_Printf("%s",buf);
//			break;
//		default:
//			break;
//	}
}
/*******************************************************************************
* @Function		:void CacheTxProcess()
* @Description	:1754������Ϣ��51822��ѯ�Ƿ��������ϱ�
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void CacheTxProcess()
{
	u8 len_temp;
//	u8 tbuff[10];
	if(!fifo_empty(&CacheTx))
	{
		memset(Data.obuf,0,sizeof(Data.obuf));
		if(info_out_fifo(&CacheTx,&len_temp,&Data.obuf[0]))
		{
			memset(ucSPITxBuffer,0,sizeof(ucSPITxBuffer));
			memcpy(ucSPITxBuffer,Data.obuf,len_temp+2);//��������
			Runspi.count = 0;
			usDataSended = 100;//������Ҫ����������������ֹ��������̫�����Ͳ�ȫ
			//USART3_Printf("%s",ucSPITxBuffer);
		}
	}
}
/*******************************************************************************
* @Function		:void QueryProcess()
* @Description	:��ѯ51822�Ƿ��������ϴ�
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void QueryProcess()
{
	static u8 temp_ch=0;
	if(temp_ch++ >=4)
	{
		temp_ch = 1;
	}
	Unpack(seltype,seldata,&temp_ch,1);//��������������
}
/*******************************************************************************
* @Function		:void QueryProcess()
* @Description	:����nxp��������
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void SettingProcess()
{
	u8 len_temp;
	u8 temp;
	if(!fifo_empty(&SetCache))
	{
		memset(Data.obuf,0,sizeof(Data.obuf));
		if(info_out_fifo(&SetCache,&len_temp,&Data.obuf[0]))
		{
			Analysis_function(&Pack.cmdtype,&Pack.datatype,&Data.obuf[0],Data.obuf,&temp);
			if((Pack.cmdtype == settype)||(Pack.cmdtype == seltype))//ʵ������ת������
			{
				Unpack(Pack.cmdtype,Pack.datatype,Data.obuf,len_temp-5);//��������������
			}
		}
	}
}









