#ifndef _myfinsh_h
#define _myfinsh_h
#include "stm32f2xx_hal.h"
#include "uart.h"
int hw_usart_init(void);
extern UART_HandleTypeDef huart2;

#endif

