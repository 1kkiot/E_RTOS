#ifndef _debugprintf_h
#define _debugprintf_h
#include "arm_base_define.h"
#include "SysUart.h"

void printf_dma(const char *format, ...);
void wifi_printf(const char *format, ...);
void pack_printf(u8 *data,u16 len);
#endif
