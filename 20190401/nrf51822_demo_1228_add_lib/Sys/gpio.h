/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : gpio.h
Description: gpio相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _gpio_h
#define _gpio_h
#include "base.h"
#include "nrf_gpio.h"
#define		LED			29

#define		ID1			10//H
#define		ID2			12//L

extern u8 ID;

void gpio_inti(void);
u8 get_id(void);
void test_gpio(void);



#endif



