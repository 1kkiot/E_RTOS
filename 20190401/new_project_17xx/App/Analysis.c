/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Analysis.c
Description: 主要实现命令解析和打包发送
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-07
Modify	   : 
Modify Time: 
******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "Analysis.h"
#include "crc.h"
#include "memory.h"
/*******************************************************************************
* @Function		:u8 Analysis_function(u8 *cmdtype,u8 *datatype,u8 *outdata,u8 *indata,u8 *len)
* @Description	:实现命令解析功能
* @Input		:cmdtype,datatype,indata
* @Output		:outdata,len
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 Analysis_function(u8 *cmdtype,u8 *datatype,u8 *outdata,u8 *indata,u8 *len)
{
	_Pack *pbuff;
	u16 crc_temp;
	u16 *crc;
	pbuff = (_Pack *)indata;
	if((pbuff->head != HEAD)||(pbuff->softver != Soft_ver))
	{
		return false;
	}
	crc_temp = check_crc(&(pbuff->len),(pbuff->len-1),0xffff);
	crc = (u16 *)((u8 *)pbuff+2+(pbuff->len-2));
	if((*crc) != crc_temp)
	//if(0)
	{
		return false;
	}
	*cmdtype = pbuff->cmdtype;
	*datatype = pbuff->datatype;
	*len = pbuff->len;
	memcpy(outdata,&(pbuff->buf),pbuff->len - 5);

	return true;
}
/*******************************************************************************
* @Function		:u8 Unpack_target(u8 ch,u8 *data,u8 datalen)
* @Description	:实现标签信息打包功能
* @Input		:ch,data,datalen
* @Output		:null
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 Unpack_target(u8 ch,u8 *data,u8 datalen)
{
	_Pack *pPack;
	u16 CRCValue;
	u16 *pCRCValueRegion;
	pPack = (_Pack *)malloc(datalen+7);
	pPack->cmdtype = 0x00;
	pPack->datatype = 0x00;
	if(pPack == NULL)
	{
		return false;
	}
	pPack->head = HEAD;
	pPack->len = 0x05+datalen;
	pPack->softver = Soft_ver;
	pPack->cmdtype = ch;//通道号
	pPack->datatype = ch;//通道号
	memcpy(&pPack->buf[0],data,datalen);
	CRCValue = check_crc(&(pPack->len),(pPack->len-1),0xffff);
	pCRCValueRegion = (u16 *)((u8 *)pPack + datalen + 5); 
	*pCRCValueRegion = CRCValue;
	if(!fifo_puts(&UartCache,(u8 *)pPack,datalen+7))//标签信息入队操作
	{
		free(pPack);
		return false;
	}
	free(pPack);
	return true;
}
/*******************************************************************************
* @Function		:u8 Unpack_target(u8 ch,u8 *data,u8 datalen)
* @Description	:实现命令信息打包功能
* @Input		:cmd,cdata,data,datalen
* @Output		:null
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 Unpack(u8 cmd,u8 cdata,u8 *data,u8 datalen)
{
	_Pack *pPack;
	u16 CRCValue;
	u16 *pCRCValueRegion;
	pPack = (_Pack *)malloc(datalen+7);
	if(pPack == NULL)
	{
		return false;
	}
	pPack->head = HEAD;
	pPack->len = 0x05+datalen;
	pPack->softver = Soft_ver;
	pPack->cmdtype = cmd;
	pPack->datatype = cdata;
	memcpy(&pPack->buf[0],data,datalen);
	CRCValue = check_crc(&(pPack->len),(pPack->len-1),0xffff);
	pCRCValueRegion = (u16 *)((u8 *)pPack + datalen + 5); 
	*pCRCValueRegion = CRCValue;
	if(!fifo_puts(&CacheTx,(u8 *)pPack,datalen+7))
	{
		free(pPack);
		return false;
	}
	free(pPack);
	return true;
}
/*******************************************************************************
* @Function		:u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data)
* @Description	:实现队列出队操作
* @Input		:fifoytpe
* @Output		:data, len
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data)
{
	u8 length,head_temp;
	do{
		if (!fifo_getc(fifoytpe, &head_temp))
		{
			return false;
		}
	}while(head_temp != 0x7e);
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
















