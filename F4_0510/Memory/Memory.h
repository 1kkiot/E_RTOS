#ifndef _memory_h
#define _memory_h

#include "arm_base_define.h"
#include "Fifo.h"

#define		Uart1Len			512*2*3+1//用于串口通信数据缓存
#define		TagCacheLen			512*2*3+1//用于缓存标签信息
#define		TagLen				512*2*2+1//用于缓存解析出来的信息
#define		WifiLen				512*2*1+1//用于连接wifi数据缓存

extern FIFO_t	Uart1Fifo;
extern u8 Uart1Buf[];

extern FIFO_t TagFifo;
extern u8 TagCacheBuf[];

extern FIFO_t TagFifo;
extern u8 TagBuf[];

extern FIFO_t WifiFifo;
extern u8 WifiBuf[];

void Init_memory(void);

#endif



