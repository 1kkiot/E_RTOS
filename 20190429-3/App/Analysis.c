/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Analysis.c
Description		: 主要实现系统命令解析及打包功能
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-26
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Analysis.h"
_Tagdata tagdata;
_CMD packcmd;

/*******************************************************************************
* @Function		:u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data)
* @Description	:查找一条标签信息
* @Input		:FIFO_t *fifoytpe,u8 *len,
* @Output		:u8 *data
* @Return		:false or true
* @Others		:null
*******************************************************************************/
u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data)
{
	u8 length,head_temp;
	do{
		if (!fifo_getc(fifoytpe, &head_temp))
		{
			return false;
		}
	}while(head_temp != 0xfa);
	*data++ = head_temp;
	if(fifo_getc(fifoytpe, &length))
	{
		*data++ = length;
		if(!fifo_gets(fifoytpe,data,(length-1)))
		{
			return false;
		}
	}
	*len = length;
	return true;
}

/*******************************************************************************
* @Function		:u8 find_tag(u8 *indata,u8 *tagnum,u8 *tagdata)
* @Description	:将出队信息解析出标签信息后入队列
* @Input		:u8 *indata
* @Output		:u8 *tagnum,u8 *tagdata
* @Return		:false or true
* @Others		:null
*******************************************************************************/
u8 find_tag(u8 *indata,u8 *tagnum,u8 *tagdata)
{
	u16 temp_crc;
	_CMD *pPack;
	u8 *crc1,*crc2;
	u8 temp1,temp2;
	pPack = (_CMD *)indata;
	if(pPack->head != 0xfa)
	{
		return false;
	}
	*tagnum = pPack->tagnum;
	temp_crc = cal_crc16_ext(0xffff,&(pPack->len),(pPack->len - 2));
	temp1 = temp_crc & 0xff;
	temp2 = ((temp_crc >> 8) & 0xff);
	crc1 = (u8 *)((u8 *)pPack+1+(pPack->len-2));
	crc2 = (u8 *)((u8 *)pPack+1+(pPack->len-1));
	if((*crc1 != temp1)||(*crc2 != temp2))
	{
		return false;
	}
	//memcpy(tagdata,&(pPack->data),(pPack->len - 12));
	fifo_puts(&TagFifo,(pPack->data),(pPack->len - 12));
	return true;
}

/*******************************************************************************
* @Function		:u8 tag_out_fifo(FIFO_t *fifoytpe,u8 *otagtype,u8 *otype,u8 *olen,u8 *odata)
* @Description	:查找标签信息
* @Input		:FIFO_t *fifoytpe
* @Output		:u8 *otagtype,u8 *otype,u8 *olen,u8 *odata
* @Return		:false or true
* @Others		:null
*******************************************************************************/
u8 tag_out_fifo(FIFO_t *fifoytpe,u8 *otagtype,u8 *otype,u8 *olen,u8 *odata)
{
	u8 head_temp;
	u8 tagtype;
	u8 type;
	u8 lentemp;

	do{
		if (!fifo_getc(fifoytpe, &head_temp))
		{
			return false;
		}
	}while(head_temp != 0x0e);

	fifo_getc(fifoytpe, &tagtype);
	*otagtype = tagtype;
	fifo_getc(fifoytpe, &type);
	*otype = type;
	fifo_getc(fifoytpe, &lentemp);
	*olen = lentemp;
	if(!fifo_gets(fifoytpe,odata,lentemp))
	{
		return false;
	}
	return true;
}





















