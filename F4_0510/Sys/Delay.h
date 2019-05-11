#ifndef _delay_h
#define _delay_h
#include "arm_base_define.h"
#include <stm32f4xx.h>
void RunSysTick(void);
void delay_init(u8 SYSCLK);
void delay_us(u32 nus);
void delay_ms(u32 nms);
void delay_xms(u32 nms); 
//void systick_delay_us(u32 nus);
//void systick_delay_ms(u16 nms);
//void systick_delay_xms(u32 xms);

#endif





