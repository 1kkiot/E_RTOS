/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : memory.c
Description: ��Ҫʵ��memory �����ʼ��������
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
u8 CacheRxBuff[CacheLen];//����spi����
u8 CacheTxBuff[CacheLen];//����spi����
u8 BleBuff[BleLen];//���ڽ�����������ͨ��
u8 UartBuff[UartLen];//���ڻ����ǩ��Ϣ��ͨ��������ʽ���͸��ֳֻ�
u8 SetBuff[SetLen];//����ͨ����������/��ѯradio��Ϣ
/*******************************************************************************
* @Function		:void Init_fifo(void)
* @Description	:ʵ�ֶ��г�ʼ��
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


















