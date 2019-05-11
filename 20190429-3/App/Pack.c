/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Pack.c
Description		: 主要实现标签的打包并发送
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-04
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Pack.h"
#include "stdlib.h"
_Pack_t Pack_t;

u8 Pack(u8 *tag,u8 len,u8 id)
{
	char str[20]={0,};

	Pack_t.len = 0;
	memset(Pack_t.data,0,sizeof(Pack_t.data));

	memcpy(Pack_t.data+Pack_t.len,"A2 TAG,",7);//HEAD
	Pack_t.len += 7;

	memcpy(Pack_t.data+Pack_t.len,"tray_id=",8);
	Pack_t.len += 8;

	sprintf((char *)str,"%02X",id);
	memcpy(Pack_t.data+Pack_t.len,str,2);
	Pack_t.len += 2;

	memcpy(Pack_t.data+Pack_t.len,",tag_id=",8);
	Pack_t.len += 8;

	if(len == 9)
	{
		sprintf((char *)str,"%02X%02X%02X%02X%02X%02X%02X%02X%02X,",tag[0],tag[1],tag[2],tag[3],tag[4],tag[5],tag[6] \
															,tag[7],tag[8]);
		memcpy(Pack_t.data + Pack_t.len,str,19);
		Pack_t.len += 19;
	}
	else if(len == 7)
	{
		sprintf((char *)str,"%02X%02X%02X%02X%02X%02X%02X,",tag[0],tag[1],tag[2],tag[3],tag[4],tag[5],tag[6]);
		memcpy(Pack_t.data + Pack_t.len,str,15);
		Pack_t.len += 15;
	}

	memcpy(Pack_t.data + Pack_t.len,",,",2);
	Pack_t.len += 2;

	memcpy(Pack_t.data+Pack_t.len,",TAG END,,\r\n",12);//end
	Pack_t.len += 12;

	printf_232("%s",Pack_t.data);
	printf("%s",Pack_t.data);


	return true;
}






