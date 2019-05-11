/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : setting.c
Description: ʵ������radio����
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-23
Modify	   : 
Modify Time: 
******************************************************************************/
#include <string.h>
#include "setting.h"
#include "fifo.h"
#include "task.h"
#include "stdio.h"
#include "Flash.h"
#include "uart.h"
#include "memory.h"
#include "Analysis.h"
#include "gpio.h"
#include "radio_config.h"
//����������ֵ��Ҫ��Ϊ�������ά������
/*******************************************************************************
* @Function		:u8 set_fun(u8 datatype,u8 *data)
* @Description	:ʵ�����������������
* @Input		:datatype��data
* @Output		:null
* @Return		:true
* @Others		:null
********************************************************************************/
u8 set_fun(u8 datatype,u8 *data)
{
	switch(datatype)
	{
		case setfer:
			set_fer(data);
			break;
		case setmac:
			set_mac(data);
			break;
		case setspeed:
			set_speed(data);
			break;
		case setdatalen:
			set_datalen(data);
			break;
		case setsendch:
			break;
		case setsendpow:
			break;
		case reset:
			if(*data == ID)
			{
				NVIC_SystemReset();
			}
			break;
		default:
			break;
	}
	return true;
}
/*******************************************************************************
* @Function		:u8 sel_data(u8 *data)
* @Description	:ʵ���Ƿ��б�ǩ��ϢҪ�����ϱ�����
* @Input		:data
* @Output		:null
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 sel_data(u8 *data)
{
	u8 temp;
	u8 buff[7],buf[14],len;
	temp = *data;
	if(temp != ID)
	{
		return false;
	}
	if(!fifo_empty(&Uart0Tx))
	{
		fifo_gets(&Uart0Tx,buff,6);
		Escape(buff,&buf[0],&len);
		Unpack_function(target,ID,buf,len+1);
	}
	return true;
}
/*******************************************************************************
* @Function		:u8 sel_info(u8 *data)
* @Description	:ʵ�ֲ�ѯ51822 radio������Ϣ
* @Input		:data
* @Output		:null
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 sel_info(u8 *data)
{
	//��Ӧ��Ϣ����ͨ���ţ�Ƶ�ʣ����ݳ��ȣ�mac��ַ
	u8 temp;
	u8 buf[10];
	temp = *data;
	if(temp != ID)
	{
		return false;
	}
	buf[0] = ID;
	buf[1] = Radio.frequency;
	buf[2] = Radio.datalen;
	buf[3] = (u8)(*(u32 *)(setmacadd+(0)));
	buf[4] = (u8)(*(u32 *)(setmacadd+(1)));
	buf[5] = (u8)(*(u32 *)(setmacadd+(2)));
	buf[6] = (u8)(*(u32 *)(setmacadd+(3)));
	buf[7] = (u8)(*(u32 *)(setmacadd+(4)));
	buf[8] = ID;
	Unpack_function(respond,selinfo,&buf[0],9);
	return true;
}
/*******************************************************************************
* @Function		:u8 sel_fun(u8 datatype,u8 *data)
* @Description	:ʵ�ֲ��ҹ���
* @Input		:datatype,data
* @Output		:null
* @Return		:true
* @Others		:null
********************************************************************************/
u8 sel_fun(u8 datatype,u8 *data)
{
	switch(datatype)
	{
		case seldata:
			sel_data(data);
			break;
		case selrf:
			break;
		case selinfo:
			sel_info(data);
			break;
		default:
			break;
	}
	return true;
}
/*******************************************************************************
* @Function		:u8 set_fer(u8 *data)
* @Description	:ʵ������Ƶ�ʹ��ܲ����沢��Ӧ��Ϣ
* @Input		:data
* @Output		:null
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 set_fer(u8 *data)
{
	u8 temp[2];
	temp[0] = *data++;
	if(temp[0] != ID)//���Ǳ���ָ��
	{
		return false;
	}
	temp[1] = *data;
	flash_page_erase_1((u32 *)setferadd);
	flash_word_write((u32 *)setferadd,temp[1]);
	Unpack_function(respond,setfer,&temp[0],2);
	return true;
}
/*******************************************************************************
* @Function		:u8 set_mac(u8 *data)
* @Description	:ʵ������mac���ܲ����沢��Ӧ
* @Input		:data
* @Output		:null
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 set_mac(u8 *data)
{
	u8 buf[5] = {0,};
	u8 temp;
	temp = *data;
	if(*data++ != ID)
	{
		return false;
	}
	memcpy(buf,data,5);
	flash_page_erase_1((u32 *)setmacadd);
	flash_write_buff((u32 *)setmacadd,buf,2);
//	#ifdef debug
//	ttbuf[0] = (u8)(*(u32 *)(setmacadd+(0)));
//	ttbuf[1] = (u8)(*(u32 *)(setmacadd+(1)));
//	ttbuf[2] = (u8)(*(u32 *)(setmacadd+(2)));
//	ttbuf[3] = (u8)(*(u32 *)(setmacadd+(3)));
//	ttbuf[4] = (u8)(*(u32 *)(setmacadd+(4)));
//	printf("%s ",ttbuf);
//	#endif
	Unpack_function(respond,setmac,&temp,1);

	return true;
}
/*******************************************************************************
* @Function		:u8 set_speed(u8 *data)
* @Description	:ʵ�������ٶȹ��ܲ����沢��Ӧ
* @Input		:data
* @Output		:null
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 set_speed(u8 *data)
{
	u8 temp[2];
	temp[0] = *data++;
	if(temp[0] != ID)
	{
		return false;
	}
	temp[1] = *data;
	flash_page_erase_1((u32 *)setspeedadd);
	flash_word_write((u32 *)setspeedadd,temp[1]);
	Unpack_function(respond,setspeed,&temp[0],2);
	return true;
}
/*******************************************************************************
* @Function		:u8 set_ch(u8 *data)
* @Description	:ʵ������ʵ�ֽ������ݳ���
* @Input		:data
* @Output		:null
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 set_datalen(u8 *data)
{
	u8 temp[2];
	temp[0] = *data++;
	if(temp[0] != ID)
	{
		return false;
	}
	temp[1] = *data;
	flash_page_erase_1((u32 *)setdatalenadd);
	flash_word_write((u32 *)setdatalenadd,temp[1]);
	Unpack_function(respond,setdatalen,&temp[0],2);
	return true;
}




















