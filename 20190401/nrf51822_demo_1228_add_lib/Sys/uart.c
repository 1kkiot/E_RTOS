/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : uart.c
Description: set uart init
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include "uart.h"
#include "nrf_gpio.h"
#include "fifo.h"
#include "memory.h"
/*******************************************************************************
* @Function		:void usart_init(void)
* @Description	:���ڳ�ʼ������
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void usart_init(void)
{
	/** @snippet [Configure UART RX and TX pin] */
	nrf_gpio_cfg_output(TX_PIN);             //����usart-io
	nrf_gpio_cfg_input(RX_PIN, NRF_GPIO_PIN_NOPULL);  

	NRF_UART0->PSELTXD =TX_PIN;//0x200ul;//0x01ul<<TX_PIN_NUMBER;  //ѡ��tx�ܽ�
	NRF_UART0->PSELRXD =RX_PIN;//0x800ul;//0x01ul<<RX_PIN_NUMBER;
	//��������������š� ����������λ��Чֵ
	NRF_UART0->PSELRXD = RX_PIN;      
	NRF_UART0->PSELTXD = TX_PIN;
	NRF_UART0->PSELRTS = 0XFFFFFFFF;
	NRF_UART0->PSELCTS = 0XFFFFFFFF;
	NRF_UART0->CONFIG = 0;             //��ʹ�����أ���ʹ��У��
	NRF_UART0->BAUDRATE         = (UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos);   //������
	NRF_UART0->ENABLE           = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);            //��usart
	NRF_UART0->TASKS_STARTTX    = 1;
	NRF_UART0->TASKS_STARTRX    = 1;
	NRF_UART0->EVENTS_RXDRDY    = 0;
	NRF_UART0->EVENTS_TXDRDY	= 0;
#if uart_exit     //usart�ж�����
	NRF_UART0->INTENSET = UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos;
	NVIC_SetPriority(UART0_IRQn, 1);
	NVIC_EnableIRQ(UART0_IRQn);
#endif
}
/*******************************************************************************
* @Function		:void UART0_IRQHandler(void)
* @Description	:�����жϺ���
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void UART0_IRQHandler(void)  //usart�жϴ���
{
	u8 res;
	while (NRF_UART0->EVENTS_RXDRDY != 1)
	{
		;
	}
	res = (uint8_t)NRF_UART0->RXD;
	fifo_putc(&Uart0Rx,res);
	NRF_UART0->EVENTS_RXDRDY = 0;

}
/*******************************************************************************
* @Function		:
* @Description	:�����ض���
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;       
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{
	NRF_UART0->EVENTS_TXDRDY = 0;
	NRF_UART0->TXD = ch;
	while(NRF_UART0->EVENTS_TXDRDY == 0){
		;
	}      
	return ch;
}
/*******************************************************************************
* @Function		:void send_uart_byte(uint8_t data)
* @Description	:���ڷ���1byte
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void send_uart_byte(uint8_t data)
{
	uint8_t temp = data;
	NRF_UART0->EVENTS_TXDRDY = 0;
	NRF_UART0->TXD = temp;
	while(NRF_UART0->EVENTS_TXDRDY == 0){
		;
	}
}




