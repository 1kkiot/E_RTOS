#ifndef _debugprintf_h
#define _debugprintf_h
#include "arm_base_define.h"
#include "uart.h"
void printf_dma(const char *format, ...);
void pack_printf(u8 *data,u16 len);
#endif
