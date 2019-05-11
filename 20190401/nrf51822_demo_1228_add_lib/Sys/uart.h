/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : uart.h
Description: 系统串口相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _uart_h
#define _uart_h
#include "base.h"
#include "stdio.h"

#define RX_PIN  11  // UART RX pin number.
#define TX_PIN  9  // UART TX pin number.
#define uart_exit     1   //1开中断
void usart_init(void);
void send_uart_byte(uint8_t data);
#endif

