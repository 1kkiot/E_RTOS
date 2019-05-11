#ifndef _sys_clock_h
#define _sys_clock_h
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx_hal.h"
void HAL_MspInit(void);
void SystemClock_Config(void);
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif


