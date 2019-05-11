/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : radio_config.c
Description: 对RF发送和接收进行配置
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include "radio_config.h"
#include "nrf_delay.h"
#include "base.h"
#include "fifo.h"
#include "memory.h"
#include "time.h"
#include "flash.h"
#include "setting.h"
#include "gpio.h"
#include "task.h"

static u8 PacketBuffer[15]={0,};
_RADIO	Radio;

// Function to do bytewise bit-swap on a unsigned 32 bit value
static u32 bytewise_bit_swap(u8 const * p_inp)
{
	u32 inp = (*(u32*)p_inp);
	inp = (inp & 0xF0F0F0F0) >> 4 | (inp & 0x0F0F0F0F) << 4;
	inp = (inp & 0xCCCCCCCC) >> 2 | (inp & 0x33333333) << 2;
	inp = (inp & 0xAAAAAAAA) >> 1 | (inp & 0x55555555) << 1;
	return inp;
}
static uint32_t addr_conv(uint8_t const* p_addr)
{
	return __REV(bytewise_bit_swap(p_addr));
}
/*******************************************************************************
* @Function		:void radio_temp_init()
* @Description	:初始化radio配置变量
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void radio_temp_init()
{
	u8 temp[4];
	u8 tmp[4];
	Radio.frequency = (u8)(*(u32 *)(setferadd));
	Radio.speed = (u8)(*(u32 *)(setspeedadd));
	Radio.speed -= 1;
	#if 0
	tmp[0] = (u8)(*(u32 *)(setmacadd+(0)));
	tmp[1] = 0xc3;
	tmp[2] = 0xc4;
	tmp[3] = 0xc5;
	temp[0] = (u8)(*(u32 *)(setmacadd+(1)));
	temp[1] = (u8)(*(u32 *)(setmacadd+(2)));
	temp[2] = (u8)(*(u32 *)(setmacadd+(3)));
	temp[3] = (u8)(*(u32 *)(setmacadd+(4)));
	Radio.datalen = (u8)(*(u32 *)(setdatalenadd));
	#else
	switch(ID)
	{
		case 1:
			Radio.frequency = 10;
			break;
		case 2:
			Radio.frequency = 20;
			break;
		case 3:
			Radio.frequency = 30;
			break;
		case 4:
			Radio.frequency = 40;
			break;
		default:
			Radio.frequency = 10;
			break;
	}
	
	Radio.speed = 0;
	tmp[0] = 0xf2;//读操作
	tmp[1] = 0xa5;
	tmp[2] = 0xc4;
	tmp[3] = 0xc5;
	temp[0] = 0xa2;
	temp[1] = 0xef;
	temp[2] = 0x10;
	temp[3] = 0x01;
	Radio.datalen = 9;
	#endif
	Radio.macl = addr_conv(temp);
	Radio.mach = bytewise_bit_swap(&tmp[0]);
}
/*******************************************************************************
* @Function		:void radio_configure()
* @Description	:实现radio配置
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void radio_configure()//无线配置，准备和nrf24L01通讯
{
	NRF_RADIO->TXPOWER = (0xf8<<0);//无线功率4分贝
	NRF_RADIO->FREQUENCY = Radio.frequency;
	//无线速率：00：1Mbit，01：2Mbit，02：250Kbit，03：1Mbit（蓝牙）
	NRF_RADIO->MODE = (Radio.speed<<1);//速率1MHz
	NRF_RADIO->PREFIX0 = Radio.mach;  // 通道3 到 0 的低1字节
	NRF_RADIO->BASE0   = Radio.macl;  // 通道0的高字节
	NRF_RADIO->PREFIX1 = 0x23C343AB;  // 通道7 到 4 的低1字节
	NRF_RADIO->BASE1   = 0x23C343AB;  // 通道1-7的高字节
	NRF_RADIO->TXADDRESS = 0x00UL;    // 发射使用的通道号：1通道
	NRF_RADIO->RXADDRESSES = 0x01UL;  // 接收的通道号：0通道
	//配置包0的设置
	NRF_RADIO->PCNF0 = (0<<16)| //S1领域的长度
						(0<<8)| //S0场的长度
						(0<<0);  //长度字段中的比特数

	//配置包1的设置
	NRF_RADIO->PCNF1 = (0<<25)| //效验位（0关，1开）
					  (1<<24)|  //数据大小端（高低字节哪个先发 0低字节，1高字节）
					  (2<<16)|  //通道1~7高字节长度（ nrf24高低字节5字节：4个高+1个低）
					  (Radio.datalen<<8)| //数据字节长度（255~1）3字节QxC
					  (Radio.datalen<<0);  //硬件传输字节长度（255~1）3字节QxC
	// CRC 校验长度配置
	NRF_RADIO->CRCCNF = 2; // 校验长度 2个char
	if ((NRF_RADIO->CRCCNF & 0x03)== 2 )
	{
		NRF_RADIO->CRCINIT = 0xFFFFUL;      // 校验初始值
		NRF_RADIO->CRCPOLY = 0x11021UL;     // CRC poly: x^16+x^12^x^5+1
	}
	else if ((NRF_RADIO->CRCCNF & 0x03) == 1 )
	{
		NRF_RADIO->CRCINIT = 0xFFUL;        // 校验初始值
		NRF_RADIO->CRCPOLY = 0x107UL;       // CRC poly: x^8+x^2^x^1+1
	}
	nrf_delay_ms(5);
}
/*******************************************************************************
* @Function		:void radio()
* @Description	:实现radio数据接收初始化
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void radio()
{
	NRF_RADIO->SHORTS |= RADIO_SHORTS_ADDRESS_RSSISTART_Msk;
	NRF_RADIO->INTENSET = RADIO_INTENSET_READY_Msk | RADIO_INTENSET_END_Msk ;//| RADIO_INTENSET_DISABLED_Msk;
	NVIC_EnableIRQ(RADIO_IRQn);
	NRF_RADIO->PACKETPTR = (uint32_t)PacketBuffer;//指针指向数据缓冲packet
	NRF_RADIO->TASKS_RXEN   = 1U; //接收模式	
}
/*******************************************************************************
* @Function		:void RADIO_IRQHandler()
* @Description	:实现radio中断接收功能
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void RADIO_IRQHandler()
{
	if(NRF_RADIO->EVENTS_READY)
	{
		NRF_RADIO->EVENTS_READY = 0;
		NRF_RADIO->TASKS_START = 1;
	}
	if(NRF_RADIO->EVENTS_END)
	{
		NRF_RADIO->EVENTS_END = 0;       
		if(NRF_RADIO->CRCSTATUS == 1)
		{
			while(NRF_RADIO->EVENTS_RSSIEND == 0)
			{}
			#ifndef new_68
			PacketBuffer[9] = NRF_RADIO->RSSISAMPLE;
			NRF_RADIO->EVENTS_RSSIEND = 0;
			//if(PacketBuffer[0] == 0xc5)
			{
				fifo_puts(&Radiofifo,&PacketBuffer[0],10);
				//start_led(10);
			}
			#else
			PacketBuffer[6] = NRF_RADIO->RSSISAMPLE;
			NRF_RADIO->EVENTS_RSSIEND = 0;
			fifo_puts(&Radiofifo,&PacketBuffer[0],7);
			#endif
		}
		NRF_RADIO->TASKS_START = 1;
	}
}





