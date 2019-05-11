/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : task.h
Description: 业务逻辑相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _task_h
#define _task_h
#include "Thread.h"
//设置字节长度为一个字节主要是因为通信内容不太长
#define			HEAD			0x7e
#define			Soft_ver		0x01//软件版本
//#define			new_68
//#define			settype			0x1a//设置命令类型
//#define			seltype			0x2a//查询命令类型
//#define			respond			0x3a//回应设置命令
//#define			setfer			0xa0//设置频率
//#define			setmac			0xa1//设置地址码
//#define			setspeed		0xa2//设置速度
//#define			setch			0xa3//设置通道
//#define			setsendch		0xa6//设置发送通道
//#define			setsendpow		0xa7//设置发送功率
//#define			seldata			0xa4//查询数据
//#define			selrf			0xa5//查询频率

//协议设计命令类型和数据类型主要是为了后续扩展方便
typedef enum{				//设计成美剧主要是为了后面维护工作，使用宏定义不利于后续维护工作
	settype=0x1a,			//设置命令类型
	seltype,				//查询命令类型
	respond,				//回应设置命令类型
	selinfo,				//查询标签信息数据类型
	setfer,					//设置频率数据类型
	setmac,					//设置地址码数据类型
	setspeed=0x20,			//设置速度数据类型
	setdatalen,				//设置数据长度数据类型
	seldata,				//查询标签信息数据类型
	selrf,					//查询频率数据类型
	setsendch,				//设置发送通道数据类型
	setsendpow,				//设置发送功率数据类型
	target,					//表示标签信息数据类型
	reset,					//表示重新启动
}_STATUS;
#pragma	pack(push,1)
typedef struct{
	u8 num;//统计spi发送次数
	u8 count;
	u8 flag;
}_FLAG;
typedef struct{
	u8 mbuf[5];
}_Mac;
typedef struct{
	u8 head;
	u8 len;
	u8 softver;
	u8 cmdtype;
	u8 datatype;
	u8 dbuff[240];//命令内容最大支持240byte
}_CMD;
typedef struct{
	u8 fbuff[255];
	u8 bbuff[255];
}_DATA;
#pragma	pack(pop)
extern _DATA		dtemp;
extern _CMD			ctemp;
extern _FLAG		Send;


void rf_function(void);
void main_task(void);
void spi_function(void);
void radio_send(void);
u8 Escape(u8 *indata,u8 *outdata,u8 *len);
#endif




