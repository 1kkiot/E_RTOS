/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : decrypt.c
Description: 实现软件信息解密功能
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include "decrypt.h"
#include "string.h"
#include "stdio.h"
#include <stdlib.h>
u8 key[2] = {0x41,0x55};
/*******************************************************************************
* @Function		:u8 data_decrypt(u8 *buf,u8 *data)
* @Description	:进行标签软件揭秘功能
* @Input		:buf
* @Output		:data
* @Return		:1
* @Others		:null
********************************************************************************/
u8 data_decrypt(u8 *buf,u8 *data)
{
	u8 *p;
	u8 temp[6] = {0,},i;
	p = buf;
	for(i=5;i>=1;i--)
	{
		temp[i] = *(p+i) ^ *(p+(i-1)) ^ key[i&0x01];
	}
	temp[0] = *(p) ^ key[0];
	memcpy(data,temp,6);
	return 1;
}
u8 check_data68(u8 *buf,u8 *out)
{
	u8 tbuf[10];
	data_decrypt(buf,&tbuf[0]);//软件解密
	if(tbuf[1] == 0x68)
	{
		memcpy(out,tbuf,6);
		return true;
	}
	return false;
}





















