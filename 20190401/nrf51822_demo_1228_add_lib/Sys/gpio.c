/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : gpio.c
Description: set gpio High Low Input
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include "gpio.h"
#include "nrf_delay.h"
u8 ID;
/*******************************************************************************
* @Function		:void gpio_inti()
* @Description	:gpio实现初始化
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void gpio_inti()
{
	nrf_gpio_cfg_output(LED);
	nrf_gpio_cfg_input(ID1,NRF_GPIO_PIN_NOPULL);
	nrf_gpio_cfg_input(ID2,NRF_GPIO_PIN_NOPULL);
	ID = get_id();
//	nrf_gpio_pin_set(LED);
//	nrf_delay_ms(100);
//	nrf_gpio_pin_clear(LED);

}
/*******************************************************************************
* @Function		:void get_id()
* @Description	:获取通道ID
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
u8 get_id()
{
	u8 temp = 0;
	temp |= nrf_gpio_pin_read(ID1);
	temp <<= 1;
	temp |= nrf_gpio_pin_read(ID2);
	temp += 1;
	return temp;
}
void test_gpio()
{
	nrf_gpio_pin_toggle(LED);
}




