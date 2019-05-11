/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Analysis.c
Description: 主要实现命令解析及打包功能
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include <stdlib.h>
#include "Analysis.h"
#include "task.h"
#include "string.h"
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
	_CMD *pbuff;
	u16 crc_temp;
//	u16 *crc;
	u8 *crc1,*crc2;
	u8 temp1,temp2;
	pbuff = (_CMD *)indata;
	if((pbuff->head != HEAD)||(pbuff->softver != Soft_ver))
	{
		return false;
	}
	*cmdtype = pbuff->cmdtype;
	*datatype = pbuff->datatype;
	crc_temp = check_crc(&(pbuff->len),(pbuff->len-1),0xffff);
	temp1 = crc_temp & 0xff;
	temp2 = ((crc_temp >> 8) & 0xff);
//	crc = (u16 *)((u8 *)pbuff+2+(pbuff->len-2));
	crc1 = (u8 *)((u8 *)pbuff+2+(pbuff->len-2));
	crc2 = (u8 *)((u8 *)pbuff+2+(pbuff->len-1));
	if((*crc1 != temp1)||(*crc2 != temp2))
	{
		return false;
	}
//	if((*crc) != crc_temp)//好坑啊，无缘无故会出现HardFault, Go to hell!!!
//	{                     //垃圾memory tmd
//		return false;
//	}
	memcpy(outdata,&(pbuff->dbuff),(pbuff->len - 5));
	return true;
}
/*******************************************************************************
* @Function		:u8 Unpack_function(u8 cmd,u8 cdata,u8 *data,u8 datalen)
* @Description	:实现命令打包功能
* @Input		:cmd,cdata,data,datalen
* @Output		:null
* @Return		:true or false
* @Others		:null
********************************************************************************/
u8 Unpack_function(u8 cmd,u8 cdata,u8 *data,u8 datalen)
{
//	u16 *pCRCValueRegion;
	_CMD *pPack;
//	u8 *crc1;
//	u8 *crc2;
	u8 templ;
	u8 temph;
	u16 CRCValue;

	pPack = (_CMD *)malloc(sizeof(pPack));
	if(pPack == NULL)
	{
		return false;
	}
	pPack->head = HEAD;
	pPack->len = 0x05+datalen;
	pPack->softver = Soft_ver;
	pPack->cmdtype = cmd;
	pPack->datatype = cdata;
	memcpy(&pPack->dbuff[0],data,datalen);
	CRCValue = check_crc(&(pPack->len),(pPack->len-1),0xffff);
	templ = CRCValue & 0xff;
	temph = (CRCValue >> 8);
	pPack->dbuff[datalen++] = templ;//校验位
	pPack->dbuff[datalen] = temph;
//	crc1 =(u8 *)((u8 *)pPack + datalen + 5);
//	*crc1 = templ;
//	crc2 =(u8 *)((u8 *)pPack + datalen + 6);
//	*crc2 = temph;//设计转译对spi bug进行规避
//	memcpy(&pPack->dbuff[datalen],(u8 *)CRCValue,2);//拷贝方法不行啊
//	pCRCValueRegion = (u16 *)((u8 *)pPack + (datalen + 6));
//	*pCRCValueRegion = CRCValue;//好坑啊，居然会出现HardFault Go to hell!!!
	if(!fifo_puts(&SPITxfifo,(u8 *)pPack,(datalen+7)))
	{
		free(pPack);
		return false;
	}

	free(pPack);
	return true;
}
/*******************************************************************************
* @Function		:u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data)
* @Description	:实现命令出队操作
* @Input		:fifoytpe
* @Output		:len,data
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
























