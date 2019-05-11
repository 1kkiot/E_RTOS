#ifndef _memory_h
#define _memory_h

#include "arm_base_define.h"
#include "Fifo.h"

#define		Uart1Len			512*2*3+1//���ڴ���ͨ�����ݻ���
#define		TagCacheLen			512*2*3+1//���ڻ����ǩ��Ϣ
#define		TagLen				512*2*2+1//���ڻ��������������Ϣ
#define		WifiLen				512*2*1+1//��������wifi���ݻ���

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



