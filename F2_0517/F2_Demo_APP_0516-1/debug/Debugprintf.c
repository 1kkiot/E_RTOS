/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Debugprintf.c
Description		: ʵ�ִ��ڴ�ӡ�ض������⣬�����Ժ��ʽ�����
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-03-30
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Debugprintf.h"

/*******************************************************************************
* @Function		:printf(const char *format, ...)
* @Description	:��ʹ��dma���д����ض���
* @Input		:const char *format, ...
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
#pragma import(__use_no_semihosting)             
struct __FILE
{
	int handle;
};
FILE __stdout;
void _sys_exit(int x)
{
	x = x;
}
void _ttywrch(int ch)
{
    ch = ch;
}
int fputc(int ch,FILE *f)
{
	while((USART6->SR & 0x40) == 0);
	USART6->DR = (uint8_t)ch;
	return ch;
}

/*******************************************************************************
* @Function		:printf_dma()
* @Description	:ʹ��dma���д����ض���
* @Input		:const char *format, ...
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void printf_dma(const char *format, ...)
{
	static char print_buffer[256];
	u16 length;
	va_list args;
	while(HAL_DMA_GetState(&hdma_usart6_tx) == HAL_DMA_STATE_BUSY);
	__HAL_DMA_DISABLE(&hdma_usart6_tx);
	va_start(args, format);
	length = vsnprintf(print_buffer, sizeof(print_buffer), (char*)format, args);
	HAL_UART_Transmit_DMA(&huart6,(u8 *)print_buffer,length);
	va_end(args);
}

/*******************************************************************************
* @Function		:pack_printf()
* @Description	:����ָ����������
* @Input		:len����*data����
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void pack_printf(u8 *data,u16 len)
{
	u16 i;
	for(i=0;i<len;i++)
	{
		while((USART1->SR & 0x40) == 0);
		USART1->DR = (uint8_t)data[i];
	}
}






