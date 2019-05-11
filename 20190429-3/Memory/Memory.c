/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Memory.c
Description		: ��Ҫ��ϵͳ�ڴ���估��ʼ������
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-25
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Memory.h"

FIFO_t TagCacheFifo;
u8 TagCacheBuf[TagCacheLen];

FIFO_t TagFifo;
u8 TagBuf[TagLen];

FIFO_t WifiFifo;
u8 WifiBuf[WifiLen];

/*******************************************************************************
* @Function		:void Init_memory(void)
* @Description	:��ʼ��ϵͳ�ڴ�
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void Init_memory()
{
	fifo_init(&TagCacheFifo,TagCacheBuf,TagCacheLen);
	fifo_init(&TagFifo,TagBuf,TagLen);
	fifo_init(&WifiFifo,WifiBuf,WifiLen);
}









