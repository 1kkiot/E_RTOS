/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Command.h
Description		: 主要实现读标签命令功能相关定义
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-26
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _command_h
#define _command_h
#include "arm_base_define.h"

typedef enum{
	STAUTS0=0,
	STAUTS1,
	STAUTS2,
	STAUTS3,
	STAUTS4,
	STAUTS5,
	STAUTS6,
	STAUTS7,
	STAUTS8,
	STAUTS9,
	STAUTS10,
	STAUTS11,
}_READ_s;

extern _READ_s READ_STUATS;
u16 cal_crc16_ext(u16 initval ,u8 *ptr, u8 len);
u8 send_data(u8 *data,u8 len);

void Read_fun(void);
void read_tag_cmd(void);
void cmd10(void);
void cmd11(void);

#endif



