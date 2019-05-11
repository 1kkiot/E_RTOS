/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : logic.h
Description: 业务逻辑相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-07
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _logic_h
#define _logic_h
#include "base.h"

#define			dlen				250

#pragma pack(push,1)
typedef struct{
	u8 num;
	u8 count;
	u8 flag;
}_RUN;//主要目的是为了控制spi发送重复数据次数
typedef struct{
	u8 obuf[dlen];//带出数据
	u8 bbuf[dlen];//备份数据
}_DATA;
#pragma pack(pop)
extern _DATA	Data;
extern _RUN		Runspi;

u8 respond_fun(u8 cmd,u8 *data,u8 len);
void CacheRxProcess(void);
void CacheTxProcess(void);
void QueryProcess(void);
void SettingProcess(void);
u8 Escape(u8 *indata,u8 *outdata,u8 len);


#endif

