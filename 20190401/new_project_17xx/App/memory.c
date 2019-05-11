/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : memory.c
Description: 主要实现memory 缓存初始化及定义
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-07
Modify	   : 
Modify Time: 
******************************************************************************/
#include "memory.h"
FIFO_t	CacheRx;
FIFO_t	CacheTx;
FIFO_t	BleCache;
FIFO_t	UartCache;
FIFO_t	SetCache;
u8 CacheRxBuff[CacheLen];//用于spi接收
u8 CacheTxBuff[CacheLen];//用于spi发送
u8 BleBuff[BleLen];//用于建立蓝牙连接通信
u8 UartBuff[UartLen];//用于缓存标签信息并通过蓝牙方式发送给手持机
u8 SetBuff[SetLen];//用于通过串口设置/查询radio信息
/*******************************************************************************
* @Function		:void Init_fifo(void)
* @Description	:实现队列初始化
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void Init_fifo()
{
	fifo_Init(&CacheRx,CacheRxBuff,CacheLen);
	fifo_Init(&CacheTx,CacheTxBuff,CacheLen);
	fifo_Init(&BleCache,BleBuff,BleLen);
	fifo_Init(&UartCache,UartBuff,UartLen);
	fifo_Init(&SetCache,SetBuff,SetLen);
}


















