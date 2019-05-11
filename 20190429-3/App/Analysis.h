/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Analysis.c
Description		: 主要实现系统命令解析相关定义
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-26
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _analysis_h
#define _analysis_h
#include "Command.h"
#include "Memory.h"

#define		Len			256

#pragma pack(push,1)
typedef struct{
	u8 data[Len];
	u8 tag[Len];
}_Tagdata;//出队数据
#pragma pack(pop)

#pragma pack(push,2)
typedef struct{
	u8 head;
	u8 len;
	u8 pcb;
	u8 cmd;
	u16 status;
	u8 stopbit;
	u16 tatoltag;
	u8 tagnum;
	u8 data[250];
}_CMD;//信息数据结构
#pragma pack(pop)

extern _Tagdata tagdata;
extern _CMD packcmd;

u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data);
u8 find_tag(u8 *indata,u8 *tagnum,u8 *tagdata);
u8 tag_out_fifo(FIFO_t *fifoytpe,u8 *otagtype,u8 *otype,u8 *olen,u8 *odata);

#endif





