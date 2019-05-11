/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Debugprintf.h
Description		: ʵ�ִ��ڴ�ӡ�ض������⣬�����Ժ��ʽ���������ض���
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-03-30
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _debugprintf_h
#define _debugprintf_h
#include "arm_base_define.h"
#include "SysUart.h"

void printf_232(const char *format, ...);
void printf_wifi(const char *format, ...);
void printf_uart1(const char *format, ...);
void pack_printf(u8 *data,u16 len);
void printf_1(u8 *data,u16 len);
#endif
