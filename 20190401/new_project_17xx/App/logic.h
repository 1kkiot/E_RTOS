/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : logic.h
Description: ҵ���߼����ͷ�ļ�
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-07
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _logic_h
#define _logic_h
#include "base.h"

#define			dlen				250

#pragma pack(push,1)
typedef struct{
	u8 num;
	u8 count;
	u8 flag;
}_RUN;//��ҪĿ����Ϊ�˿���spi�����ظ����ݴ���
typedef struct{
	u8 obuf[dlen];//��������
	u8 bbuf[dlen];//��������
}_DATA;
#pragma pack(pop)
extern _DATA	Data;
extern _RUN		Runspi;

u8 respond_fun(u8 cmd,u8 *data,u8 len);
void CacheRxProcess(void);
void CacheTxProcess(void);
void QueryProcess(void);
void SettingProcess(void);
u8 Escape(u8 *indata,u8 *outdata,u8 len);


#endif

