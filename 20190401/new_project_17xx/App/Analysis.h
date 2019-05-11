/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Analysis.c
Description: 命令解析相关定义头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-07
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _analysis_h
#define _analysis_h
#include "fifo.h"

#define			HEAD			0x7e//信息头标志
#define			Soft_ver		0x01//软件版本
//#define			Target			0x2a//表示标签信息
//命令类型
//#define			settype			0x1a//设置命令类型
//#define			seltype			0x2a//查询命令类型
//#define			respond			0x3a//回应设置命令
//#define			selinfo			0xc0//查询标签信息
////radio接收2.4g rf信号相关设置，数据类型
//#define			setfer			0xa0//设置频率
//#define			setmac			0xa1//设置地址码
//#define			setspeed		0xa2//设置速度
//#define			setch			0xa3//设置通道
////radio发送相关设置
//#define			setsendch		0xb0//设置发送通道
//#define			setsendpow		0xb1//设置发送功率

typedef enum {				//设计成美剧主要是为了后面维护工作
	settype=0x1a,			//设置命令类型
	seltype,				//查询命令类型
	respond,				//回应设置命令类型
	selinfo,				//查询标签信息数据命令类型
	setfer,					//设置频率数据类型
	setmac,					//设置地址码数据类型
	setspeed=0x20,				//设置速度数据类型
	setdatalen,					//设置数据长度数据类型
	seldata,				//查询标签信息数据类型
	selrf,					//查询频率数据类型
	setsendch,				//设置发送通道数据类型
	setsendpow,				//设置发送功率数据类型
	target,					//表示标签信息数据类型

}_STATUS;


#pragma pack(push,1)
typedef struct{
//设计这个结构体主要是为了以后添加命令方便，故设计命令类型和数据类型
	u8 head;			//数据头
	u8 len;				//数据长度
	u8 softver;			//软件版本
	u8 cmdtype;			//命令类型
	u8 datatype;		//数据类型
	u8 buf[240];		//命令内容最大支持240byte
}_Pack;
#pragma pack(pop)


u8 Analysis_function(u8 *cmdtype,u8 *datatype,u8 *outdata,u8 *indata,u8 *len);
u8 Unpack(u8 cmdtype,u8 datatype,u8 *data,u8 datalen);
u8 Unpack_target(u8 ch,u8 *data,u8 datalen);
u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data);



#endif











