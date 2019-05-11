/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : uart.c
Description: 主要实现串口初始化及中断接收功能，这个串口3好坑啊，
			串口0是正常的串口3居然不正常，可能是配置问题
			好奇怪啊
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-09
Modify	   : 
Modify Time: 
******************************************************************************/
#include <stdarg.h>
#include <string.h>
#include "uart.h"
#include "stdio.h"
#include "memory.h"
#include "fifo.h"
/*******************************************************************************
* @Function		:void EnableIrq()
* @Description	:使能全局中断
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void EnableIrq()
{
	__enable_irq();
}
/*******************************************************************************
* @Function		:void DisableIrq()
* @Description	:禁止全局中断
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void DisableIrq()
{
	__disable_irq();
}
/*******************************************************************************
* @Function		:void Send_Data(char *buf,uint32_t len)
* @Description	:发送指定长度数据
* @Input		:data and len
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void Send_Data(char *buf,uint32_t len)
{
	uint16_t  t;
	for(t=0;t<len;t++)
	{
		while (!(LPC_UART0->LSR & 0x20));
		(LPC_UART0->THR = buf[t]); 
	}
	while (!(LPC_UART0->LSR & 0x20));
}
/*******************************************************************************
* @Function		:void USART3_Printf(const char *fmt, ...)
* @Description	:功能类似于printf函数
* @Input		:data
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void USART3_Printf(const char *fmt, ...)
{
	char Buff[256];
	va_list ap;
	va_start(ap, fmt);  
	vsprintf(Buff, fmt, ap);
	va_end(ap);
	Send_Data(Buff,strlen(Buff));
}

struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{
	while (!(LPC_UART3->LSR & 0x20))
	{
		;
	}
	(LPC_UART3->THR = ch);
	return ch;
}
/*******************************************************************************
* @Function		:void uart_config0(uint32_t Baud_rate)
* @Description	:串口初始化功能
* @Input		:Baud_rate
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void uart_config0(uint32_t Baud_rate)
{
	UART_CFG_Type UARTConfigStruct;
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 1;//设置管脚功能为串口功能
	PinCfg.Portnum = 0;//设置管脚端口号,GPIO0
	PinCfg.Pinnum = 3;//GPIO0_3
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	PinCfg.Pinnum = 2;//GPIO0_2
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	
	UARTConfigStruct.Baud_rate = Baud_rate;//设置波特率
	UARTConfigStruct.Databits=UART_DATABIT_8;//设置数据8位
	UARTConfigStruct.Parity=UART_PARITY_NONE;//无校验
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//设置停止位1位
	UART_Init(LPC_UART0, &UARTConfigStruct);//初始化结构体
	
	UART_TxCmd(LPC_UART0, ENABLE);//使能发送
	
	UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);//设置接收中断
	NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));//设置优先级
	NVIC_EnableIRQ(UART0_IRQn);//智能终端

}
/*********************************************************************************************************
函数名:void UART0_IRQHandler(void)
函数功能: 串口0中断通道服务函数
参数:无
返回值:无
*********************************************************************************************************/
void UART0_IRQHandler(void)
{
	u8 temp;
	NVIC_ClearPendingIRQ(UART0_IRQn);
	if((UART_GetLineStatus(LPC_UART0)&0x01))//读取LSR时中断会被清除
	{
		temp = UART_ReceiveByte(LPC_UART0);
		fifo_putc(&SetCache,temp);
	}
}
/*******************************************************************************
* @Function		:void uart_config3(uint32_t Baud_rate)
* @Description	:串口初始化功能
* @Input		:Baud_rate
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void uart_config3(uint32_t Baud_rate)
{
#if 1
	uint32_t Fdiv;
	LPC_PINCON->PINSEL0 |= UART3SEL;
	LPC_UART3->LCR = 0x83;
	Fdiv = (SystemCoreClock / 16) / Baud_rate;
	LPC_UART3->DLM = Fdiv / 256;
	LPC_UART3->DLL = (Fdiv % 256) + 1;
	LPC_UART3->LCR = 0x03;
	LPC_UART3->FCR = 0x07;
	NVIC_EnableIRQ(UART3_IRQn);
	LPC_UART3->IER = IER_RBR | IER_THRE | IER_RLS;
#else
	UART_CFG_Type UARTConfigStruct;
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 2;//设置管脚功能为串口功能
	PinCfg.Portnum = 0;//设置管脚端口号,GPIO0
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	PinCfg.Pinnum = 0;
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	
	UARTConfigStruct.Baud_rate = Baud_rate;//设置波特率
	UARTConfigStruct.Databits=UART_DATABIT_8;//设置数据8位
	UARTConfigStruct.Parity=UART_PARITY_NONE;//无校验
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//设置停止位1位
	UART_Init(LPC_UART3, &UARTConfigStruct);//初始化结构体
	
	UART_TxCmd(LPC_UART3, ENABLE);//使能发送
	
	UART_IntConfig(LPC_UART3, UART_INTCFG_RBR, ENABLE);//设置接收中断
	NVIC_SetPriority(UART3_IRQn, ((0x01<<3)|0x01));//设置优先级
	NVIC_EnableIRQ(UART3_IRQn);//智能终端
#endif
}

#if 0//好坑啊，搞死我了，居然不行~_~
void UART3_IRQHandler(void)
{
	u8 temp;
	NVIC_ClearPendingIRQ(UART3_IRQn);
	if((UART_GetLineStatus(LPC_UART3)&0x01))//读取LSR时中断会被清除
	{
		temp = UART_ReceiveByte(LPC_UART3);
		fifo_putc(&BleCache,temp);
	}
}
#else
/*******************************************************************************
* @Function		:void uart_config3(uint32_t Baud_rate)
* @Description	:串口中断函数
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void UART3_IRQHandler (void)
{
	uint8_t IIRValue;
	uint8_t LSRValue;
	uint8_t Dummy = Dummy;
	uint8_t temp;
	while(((IIRValue = LPC_UART3->IIR) & 0x01) == 0)
	{
		IIRValue >>= 1;
		IIRValue &= 0x07;
		switch(IIRValue)
		{
			case IIR_RLS://如果是接收线状态
			{
				LSRValue = LPC_UART3->LSR;
				if ( LSRValue & (LSR_OE | LSR_PE | LSR_FE | LSR_RXFE | LSR_BI) )
				{
//					UART3Status = LSRValue;
					Dummy = LPC_UART3->RBR; //错误数据放入变量中
					return;
				}
				if ( LSRValue & LSR_RDR )//数据可用
				{
					temp = LPC_UART3->RBR;
					fifo_putc(&BleCache,temp);
				}
			}
			case IIR_CTI://超时状态
			{
//				UART3Status |= 0x100;
				break;
			}
			case  IIR_RDA://接收数据状态ZZ
			{
				temp = LPC_UART3->RBR;
				fifo_putc(&BleCache,temp);
				break;
			}
			case IIR_THRE://发送保持寄存器中断
			{
				LSRValue = LPC_UART3->LSR;
				if ( LSRValue & LSR_THRE )
				{
					;
				}
				break;
			}
		}
	}
}
#endif

















