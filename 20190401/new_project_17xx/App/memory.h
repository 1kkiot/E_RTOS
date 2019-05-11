/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : memory.h
Description: 主要实现memory 缓存定义头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-07
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _memory_h
#define _memory_h
#include "base.h"
#include "fifo.h"

#define		CacheLen		2*1024+1
#define		BleLen			512+1
#define		UartLen			4*1024+1
#define		SetLen			512+1

extern FIFO_t	CacheRx;
extern FIFO_t	CacheTx;
extern FIFO_t	BleCache;
extern FIFO_t	UartCache;
extern FIFO_t	SetCache;

void Init_fifo(void);


#endif



