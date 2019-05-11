/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Memory.h
Description		: 主要是系统内存相关宏定义
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-25
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _memory_h
#define _memory_h

#include "arm_base_define.h"
#include "Fifo.h"

#define		TagCacheLen			512*1*1+1//用于缓存标签信息
#define		TagLen				512*1*1+1//用于缓存解析出来的信息
#define		WifiLen				512*4*1+1//用于连接wifi数据缓存

extern FIFO_t TagCacheFifo;
extern u8 TagCacheBuf[];

extern FIFO_t TagFifo;
extern u8 TagBuf[];

extern FIFO_t WifiFifo;
extern u8 WifiBuf[];

void Init_memory(void);

#endif



