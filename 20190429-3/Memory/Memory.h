/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Memory.h
Description		: ��Ҫ��ϵͳ�ڴ���غ궨��
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

#define		TagCacheLen			512*1*1+1//���ڻ����ǩ��Ϣ
#define		TagLen				512*1*1+1//���ڻ��������������Ϣ
#define		WifiLen				512*4*1+1//��������wifi���ݻ���

extern FIFO_t TagCacheFifo;
extern u8 TagCacheBuf[];

extern FIFO_t TagFifo;
extern u8 TagBuf[];

extern FIFO_t WifiFifo;
extern u8 WifiBuf[];

void Init_memory(void);

#endif



