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
//��׼����Ҫ��֧�ֺ���
struct __FILE
{
	int handle;
};
FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x)
{
	x = x;
}
//void _ttywrch(int ch)
//{
//    ch = ch;
//}
int fputc(int ch,FILE *f)
{
	while((USART1->ISR & 0x40) == 0)
	{
		;
	}
	USART1->TDR = (uint8_t)ch;
	return ch;
}


/*******************************************************************************
* @Function		:printf_wifi()
* @Description	:����wifiʹ���ض�����
* @Input		:const char *format, ...
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void printf_wifi(const char *format, ...)
{
	static char print_buffer[256];
	u16 length;
	va_list args;
	while(HAL_DMA_GetState(&hdma_usart1_tx) == HAL_DMA_STATE_BUSY);
	__HAL_DMA_DISABLE(&hdma_usart1_tx);
	va_start(args, format);
	length = vsnprintf(print_buffer, sizeof(print_buffer), (char*)format, args);
	HAL_UART_Transmit_DMA(&huart1,(u8 *)print_buffer,length);
	va_end(args);
}
/*******************************************************************************
* @Function		:printf_uart1()
* @Description	:����wifiʹ���ض�����
* @Input		:const char *format, ...
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void printf_uart1(const char *format, ...)
{
	static char print_buffer[256];
	u16 length;
	va_list args;
	va_start(args, format);
	length = vsnprintf(print_buffer, sizeof(print_buffer), (char*)format, args);
	va_end(args);
	printf_1((u8 *)print_buffer,length);
}
/*******************************************************************************
* @Function		:printf_232()
* @Description	:ʹ��dma���д����ض���
* @Input		:const char *format, ...
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
#if 1
void printf_232(const char *format, ...)
{
	static char print_buffer[256];
	u16 length;
	va_list args;
	va_start(args, format);
	length = vsnprintf((char*)print_buffer, sizeof(print_buffer), (char*)format, args);
	va_end(args);
	pack_printf((u8 *)print_buffer,length);
}
#else
void printf_232(const char *format, ...)
{
	static char print_buffer[256];
	u16 length;
	va_list args;
	while(HAL_DMA_GetState(&hdma_usart3_tx) == HAL_DMA_STATE_BUSY);
	__HAL_DMA_DISABLE(&hdma_usart3_tx);
	va_start(args, format);
	length = vsnprintf((char*)print_buffer, sizeof(print_buffer), (char*)format, args);
	HAL_UART_Transmit_DMA(&huart3,(u8 *)print_buffer,length);
	va_end(args);
}
#endif

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
		while((USART3->ISR & 0x40) == 0);
		USART3->TDR = (uint8_t)data[i];
	}
}
/*******************************************************************************
* @Function		:printf_1()
* @Description	:����ָ����������
* @Input		:len����*data����
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void printf_1(u8 *data,u16 len)
{
	u16 i;
	for(i=0;i<len;i++)
	{
		while((USART1->ISR & 0x40) == 0);
		USART1->TDR = (uint8_t)data[i];
	}
}





