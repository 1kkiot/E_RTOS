/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Bluetooth.c
Description: ��Ҫʵ�ֽ�������ͨ�����Ӳ�ʵ�����ݴ��书��
			����ļ��༭���Һ������࣬ʲô����д���ģ���Ҫ����һ��Э��Ҳû��
			֮ǰ�Ĺ���ʦ��������Ҳ��nb��
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-12
Modify	   : 
Modify Time: 
******************************************************************************/
#include "Bluetooth.h"
#include <string.h>
#include <stdlib.h>
#include "delay.h"
#include "stdio.h"
#include "logic.h"
#include "memory.h"
#include "runflag.h"
#include "Thread.h"

_BLE Blevalue;//
/*******************************************************************************
* @Function		:u8 CheckSum(u8 *uBuff,u8 uBuffLen)
* @Description	:����У��ֵ
* @Input		:uBuff and len
* @Output		:crc
* @Return		:null
* @Others		:null
********************************************************************************/
u8 CheckSum(u8 *uBuff,u8 uBuffLen)
{
	u8 i,uSum=0;
	for(i=0; i<uBuffLen; i++)
	{
		uSum = uSum + uBuff[i];
	}
	uSum = (~uSum) + 1;
	return uSum;
}
/*******************************************************************************
* @Function		:void Bluetooth_init(void)
* @Description	:ʵ������ģ���ʼ������
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void Bluetooth_init()
{
	_BLE temp;
	u8 i;
	SET_GPIO_OUT(BLE_RST);
	SET_GPIO_OUT(BLE_WAKEUP);
	SET_GPIO_IN(BLE_STATUS);

	SET_GPIO_L(BLE_RST);
	Tick_delay_ms(50);
	SET_GPIO_H(BLE_RST);
	SET_GPIO_L(BLE_WAKEUP);
	Tick_delay_ms(50);
	while(ble_send_cmd((u8 *)"AT+ADVIN0",(u8 *)ACK,20))
	{
		if(i++ > 250)//��ӳ��д������������ֳ�ʼ����ͨ��ʱ���ܽ���������
		{
			break;
		}
	}
	i = 0;
	while(ble_send_cmd((u8 *)"AT+HOSTEN0",(u8 *)ACK,20))
	{
		if(i++ > 250)
		{
			break;
		}
	}
	i = 0;
	while(ble_send_cmd((u8 *)"AT+NEIN1",(u8 *)ACK,20))
	{
		if(i++ > 250)
		{
			break;
		}
	}
	i = 0;
	while(ble_send_cmd((u8 *)"AT+POWR0",(u8 *)ACK,20))
	{
		if(i++ > 250)
		{
			break;
		}
	}
	i = 0;
	while(ble_send_cmd((u8 *)"AT+ISCEN0",(u8 *)ACK,20))
	{
		if(i++ > 250)
		{
			break;
		}
	}
	memset(temp.buff,0,sizeof(temp.buff));
	memcpy(temp.buff,BT_NAME,sizeof(BT_NAME));
	while(ble_send_cmd((u8 *)temp.buff,(u8 *)ACK,20))
	{
		if(i++ > 250)
		{
			break;
		}
	}
	for(i=0;i<6;i++)
	{
		Blevalue.pass[i]=0x88;
	}
	while(0)
	{
		RunFlagHandler();
		ble_function();
		ble_start();
	}
}
/*******************************************************************************
* @Function		:u8 out_fifo_data(FIFO_t *fifoytpe,u8 *len,u8 *data)
* @Description	:ʵ���������ݶ��н��г���
* @Input		:fifoytpe
* @Output		:len,data
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 out_fifo_data(FIFO_t *fifoytpe,u8 *len,u8 *data)//��������������ӹ���
{
	u8 length,head_temp;
	do{
		if (!fifo_getc(fifoytpe, &head_temp))
		{
			return false;
		}
	}while(head_temp != BLESOF);
	*data++ = head_temp;
	fifo_getc(fifoytpe,&head_temp);
	*data++ = head_temp;
	if(fifo_getc(fifoytpe, &length))
	{
		*data++ = length;
		if(!fifo_gets(fifoytpe,data,length))
		{
			return false;
		}
	}
	*len = length;
	return true;
}
/******************************************************************************
 * ��������: void ble_unpack(void)
 * ��������: ��Ҫʵ�����ݴ�����ܣ�ϣ�����湤��ʦ���Ը���Э�飬���·�װ
 * ��    ��: null
 * ��    ��: null
 * ��    ��: null
 * ��    ����v1.0
 * ��    �ߣ�jason
 * ʱ    �䣺20190114
 *****************************************************************************/
void ble_unpack()
{
	u8 test_buff[5] = {0,};
	test_buff[0] = 0x5a;
	test_buff[1] = 0xFF;
	test_buff[2] = 0x02;
	test_buff[3] = 0x00;
	test_buff[4] = 0xc8;//��һλ����ô���ģ���Ҳ�������֮ǰ����ʦ����ôʵ�ֵ�
	send_str_len(test_buff,5);
}
void ble_failed()//����app����Э�鶼û�У����ý��д����װ
{
	u8 test_buff[5] = {0,};
	test_buff[0] = 0x5a;
	test_buff[1] = 0xFF;
	test_buff[2] = 0x02;
	test_buff[3] = 0x07;
	test_buff[4] = CheckSum(test_buff,4);
	send_str_len(test_buff,5);
}
/*******************************************************************************
* @Function		:u8 ble_target_unpack(u8 ch,u8 *data,u8 datalen)
* @Description	:ʵ�ֱ�ǩ��Ϣ������ܣ���ͨ����������Ϣ����
* @Input		:ch,data,datalen
* @Output		:null
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 ble_target_unpack(u8 ch,u8 *data,u8 datalen)
{
	_Response_Frame *pPack;
	u8 CRCValue;
	u8 *pCRCValueRegion;
	pPack = (_Response_Frame *)malloc(datalen+7);
	if(pPack == NULL)
	{
		return false;
	}
	pPack->SOF = 0x5a;
	pPack->Addr = 0xff;
	pPack->Len = datalen;
	pPack->Status = *data++;//rssi
	memcpy(&pPack->Response[0],data,datalen-1);

//	pCRCValueRegion = (u8 *)((u8 *)pPack + datalen + 3);
//	*pCRCValueRegion = ch;

	CRCValue = CheckSum(&pPack->SOF,datalen + 2);
	pCRCValueRegion = (u8 *)((u8 *)pPack + datalen + 2);
	*pCRCValueRegion = CRCValue;
	if(!fifo_puts(&UartCache,(u8 *)pPack,datalen+3))//��ǩ��Ϣ��Ӳ���
	{
		free(pPack);
		return false;
	}
	free(pPack);
	return true;
}
/******************************************************************************
 * ��������: void ble_transport(void)
 * ��������: ��Ҫʵ�����ݽ�������,ϣ�����湤��ʦ���Ը���Э��,���·�װ
 * ��    ��: null
 * ��    ��: null
 * ��    ��: null
 * ��    ����v1.0
 * ��    �ߣ�jason
 * ʱ    �䣺20190114
 *****************************************************************************/
void ble_transport()
{
	static u8 temp=0x68;
	u8 buff[10]={0,};
	buff[0] = 0x5A;
	buff[1] = 0xFF;
	buff[2] = 0x07;
	if(++temp > 0x6d)
	{
		temp = 0x68;
	}
	buff[3] = 0x68;

	buff[4] = 0x11;
	buff[5] = 0x22;
	buff[6] = 0x33;
	buff[7] = 0x44;
	buff[8] = 0x55;
	
	buff[9] = CheckSum(buff,9);
	ble_target_unpack(1,&buff[3],7);
	send_str_len(buff,10);
}
/*******************************************************************************
* @Function		:u8 ble_analysis(u8 *cmd,u8 *outdata,u8 *indata)
* @Description	:���������������
* @Input		:cmd,indata
* @Output		:outdata
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 ble_analysis(u8 *cmd,u8 *outdata,u8 *indata)
{
//	u8 crctemp;
//	u8 *crc;
	_Cmd_Frame *pCmd;
	pCmd = (_Cmd_Frame *)(indata);
	if((pCmd->SOF != BLESOF)||(pCmd->Addr != 0xFF))
	{
		return false;
	}
//	crctemp = CheckSum(&pCmd->SOF,pCmd->Len + 2);
//	crc = (u8 *)((u8 *)pCmd + pCmd->Len + 2);
//	if(crctemp != (*crc))//���˰������crc��Ȼ��д����
//	{
//		return false;
//	}
	*cmd = pCmd->Cmd;
	memcpy(outdata,&(pCmd->Parameters),(pCmd->Len - 1));
	return true;
}
/*******************************************************************************
* @Function		:void BluetoothProcess()
* @Description	:����������Ϣ
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void BluetoothProcess()
{
	u8 tbuff[10];
	if(!fifo_empty(&UartCache))
	{
		if(fifo_gets(&UartCache,tbuff,10))//������Ϣ����
		{
			;
		}
	}
	if(Blevalue.ValidCode)
	{
		send_str_len(tbuff,10);
//		ble_transport();
	}
}
/*******************************************************************************
* @Function		:void get_ble_status()
* @Description	:��ȡ��������״̬
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void get_ble_status()
{
	if(RunFlag.Hz100)
	{
		Blevalue.status = GET_BT_STATUS();
		Blevalue.status = ((Blevalue.status & 0x80000) >> 19) & 0x01 ;
		if(Blevalue.status != 0x01)
		{
			Thread_Hang(&BluetoothProcess);
			Blevalue.ValidCode = false;
		}
	}
}
/*******************************************************************************
* @Function		:void ble_function()
* @Description	:��������Ƿ�����
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void ble_function()
{
	u8 len;
	u8 cmd;
	_DATA data;
	if(!fifo_empty(&BleCache))
	{
		Delay_ms(1);
		if(out_fifo_data(&BleCache,&len,data.obuf))
		{
			ble_analysis(&cmd,&data.bbuf[0],data.obuf);
			if((cmd == 0x60)&&(0==memcmp(data.bbuf,Blevalue.pass,sizeof(Blevalue.pass))))//����appУ��ֵ��Ȼ��д����
			{
				ble_unpack();
				Tick_delay_ms(50);
				if(Blevalue.linkf == false)
				{
					Blevalue.linkf = true;
					Thread_Login(FOREVER, 0, 20,&BluetoothProcess);
				}
				else
				{
					Thread_Wake(&BluetoothProcess);
				}
				Blevalue.ValidCode = true;
			}
			else
			{
				ble_failed();
			}
		}
	}
}
/*******************************************************************************
* @Function		:void send_str(u8 *str)
* @Description	:�����ַ���
* @Input		:str
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void send_str(u8 *str)
{
	while(*str != 0)
	{
		while (!(LPC_UART3->LSR & 0x20))
		{
			;
		}
		(LPC_UART3->THR = *str++);
	}
}
/*******************************************************************************
* @Function		:void send_str_len(u8 *str,u8 len)
* @Description	:����ָ�������ַ���
* @Input		:str,len
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void send_str_len(u8 *str,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		while (!(LPC_UART3->LSR & 0x20))
		{
			;
		}
		(LPC_UART3->THR = *str++);
	}
}
/*******************************************************************************
* @Function		:u8* ble_check_cmd(u8 *str)
* @Description	:�����ض��ֶ���Ϣ
* @Input		:str,len
* @Output		:null
* @Return		:�ƶ��ַ���
* @Others		:null
********************************************************************************/
u8* ble_check_cmd(u8 *str)
{
	_BLE BleTemp;
	char *strx=0;
	u16 i = 0;
	memset(BleTemp.buff,0,sizeof(BleTemp.buff));
	while(fifo_getc(&BleCache,&BleTemp.buff[i++]))
	{
		;
	}
	strx=strstr((const char*)&BleTemp.buff[0],(const char*)str);
	return (u8*)strx;
}
/*******************************************************************************
* @Function		:u8 ble_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
* @Description	:��������ȴ���Ӧ��Ϣ
* @Input		:cmd,ack,waittime
* @Output		:null
* @Return		:0 or 1
* @Others		:null
********************************************************************************/
u8 ble_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0;
	send_str(cmd);
	if(ack&&waittime)
	{
		while(--waittime)
		{
			Delay_ms(2);
			if(!fifo_empty(&BleCache))
			{
				if(ble_check_cmd(ack))
				{
					break;
				}
			}
		}
		if(waittime == 0)
		{
			res = 1;
		}
	}
	return res;
}
















