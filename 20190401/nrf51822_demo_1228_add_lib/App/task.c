/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : task.c
Description: ʵ�ָ�����������
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include "task.h"
#include "stdio.h"
#include "string.h"
#include "memory.h"
#include "decrypt.h"
#include "runflag.h"
#include "Analysis.h"
#include "setting.h"
#include "spi.h"
#include <stdlib.h>
#include <string.h>
#include "olddecrypt.h"
#include "time.h"
static u8 rfdata[11];
_DATA		dtemp;
_CMD		ctemp;
_FLAG		Send;

/*******************************************************************************
* @Function		:void rf_function()
* @Description	:ʵ�ֱ�ǩ��Ϣ���ܲ�������Բ���
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void rf_function()
{
	u8 temp[11]={0,};
	u8 i = 0;
	if(!fifo_empty(&Radiofifo))
	{
		#ifndef new_68
		fifo_gets(&Radiofifo,temp,10);//����
		if(check_data(temp,&rfdata[0]))//��Ӳ���
		{
//			for(i=0;i<6;i++)
//			{
//				printf("%02x ",rfdata[i]);
//			}
			fifo_puts(&Uart0Tx,rfdata,6);
			start_led(10);
		}
		#else
		fifo_gets(&Radiofifo,temp,7);//����
		rfdata[6] = temp[6];//rssi
		if(check_data68(temp,&rfdata[0]))
		{
//			for(i=0;i<7;i++)
//			{
//				printf("%02x ",rfdata[i]);
//			}
			fifo_puts(&Uart0Tx,&rfdata[1],6);//��Ӳ���
			start_led(10);
		}
		#endif
	}
}

/*******************************************************************************
* @Function		:void main_task()
* @Description	:ʵ�������������
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void main_task()
{
	u8 len_temp=0;
	if(!fifo_empty(&SPIRxfifo))
	{
		memset(dtemp.fbuff,0,sizeof(dtemp.fbuff));
		if(info_out_fifo(&SPIRxfifo,&len_temp,&dtemp.fbuff[0]))
		{
			Analysis_function(&ctemp.cmdtype,&ctemp.datatype,&dtemp.bbuff[0],dtemp.fbuff,&len_temp);
			if(ctemp.cmdtype == settype)
			{
				set_fun(ctemp.datatype,dtemp.bbuff);
			}
			else if(ctemp.cmdtype == seltype)
			{
				sel_fun(ctemp.datatype,dtemp.bbuff);
			}
		}
	}
}
/*******************************************************************************
* @Function		:u8 Escape(u8 *indata,u8 *outdata,u8 *len)
* @Description	:ʵ�ֽ��ض����ַ�����ת�����
* @Input		:indata
* @Output		:outdata and len
* @Return		:true or false
* @Others		:null
********************************************************************************/
//����������crc����0���Ǿ�����ร��!�����������^��^
u8 Escape(u8 *indata,u8 *outdata,u8 *len)//����ת�嶯��
{
	u8 i,j;
	j=0;
	for(i=0;i<7;i++)
	{
		if(indata[i]==0x00)
		{
			outdata[j++] = 0x5a;
			outdata[j++] = 0xa5;
		}
		else
		{
			outdata[j++] = indata[i];
		}
	}
	*len = --j;
	return true;
}
/*******************************************************************************
* @Function		:void spi_function()
* @Description	:ʵ����Ϣ���Ӳ����͹���
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void spi_function()
{
	u8 len_temp=0;
	u8 buff[20];
	if(!fifo_empty(&SPITxfifo))
	{
		if(info_out_fifo(&SPITxfifo,&len_temp,buff))//���͸�������Ϣ
		{
			Send.num = 0;
			memcpy(m_tx_buf,buff,(len_temp+2));//���ͱ�ǩ��Ϣ������
			printf("%s",buff);
		}
	}
}
/*******************************************************************************
* @Function		:void radio_send()
* @Description	:���Թ���
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void radio_send()
{
	u8 buff[11],len;//,buf[22];
	if(!fifo_empty(&Uart0Tx))//�������ϱ�
	{
		fifo_gets(&Uart0Tx,buff,11);
		#ifdef debug
		//����ת��ֻ�ܱ���һ��0���Է��ͣ����������ܲ���ֺ�ת������ͬ�����ڵ�0x5a 0xa5�ͺǺ���
		//����ǲ�Ҫ�����ּ��������
//		buff[0] = 0xaa;//head
//		buff[1] = 0x01;//target
//		buff[2] = 0;
//		buff[3] = 0xa5;
//		buff[4] = 0;
//		buff[5] = 0x4a;
//		buff[6] = 0x4a;//rssi
		for(len=0;len<11;len++)
		{
			printf("%02x ",buff[len]);
		}
		#endif
		//Escape(buff,&buf[0],&len);
		//Unpack_function(0x2a,0x01,buf,len+1);//��ʾ�����ݽ��б�ǩ��Ϣ���Ӽ����
		
//		for(i=0;i<7;i++)
//		{
//			#if 0//���һ����ת�����spi bug ���
//			if(buff2[i] == 0x00)//spi�ÿӰ���0x00���ܷ��ͣ�ϣ�����������Խ�����������
//			{
//				buff2[i] = 0xff;
//			}
//			#else
//			if(buff2[i] == 0x00)//spi�ÿӰ���0x00���ܷ��ͣ�ϣ�����������Խ�����������
//			{
//				buff2[i] = 0xff;
//			}
//			#endif
//			//printf("%02x",buff2[i]);
//		}
//		Unpack_function(0x2a,0x01,buff2,7);//��ʾ�����ݽ��б�ǩ��Ϣ���Ӽ����
	}
}









