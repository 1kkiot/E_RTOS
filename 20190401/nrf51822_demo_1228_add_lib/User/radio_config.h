/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : radio_config.h
Description: radio 相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef RADIO_CONFIG_H
#define RADIO_CONFIG_H
#include "base.h"
#pragma pack(push,1)
typedef struct{
	u8 frequency;		//频率
	u8 speed;			//速度
	u8 crc;				//crc位数
	u16 datalen;
	u32 mach;			//高一位
	u32 macl;			//低四位
}_RADIO;
#pragma pack(pop)


extern u8 PacketBuffer[];
extern _RADIO	Radio;
void radio_temp_init(void);
void radio_configure(void);
void radio(void);


#endif
