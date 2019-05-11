#ifndef _delay_h
#define _delay_h
#include "arm_base_define.h"
#include <stm32f0xx.h>
void RunSysTick(void);
void delay_init(u8 SYSCLK);
void delay_us(u32 nus);
void delay_ms(u32 nms);
void delay_xms(u32 nms); 
void Delay_ms(u32 nms);

#endif





