/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : uart.c
Description: ��Ҫʵ�ִ��ڳ�ʼ�����жϽ��չ��ܣ��������3�ÿӰ���
			����0�������Ĵ���3��Ȼ����������������������
			����ְ�
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
* @Description	:ʹ��ȫ���ж�
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
* @Description	:��ֹȫ���ж�
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
* @Description	:����ָ����������
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
* @Description	:����������printf����
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
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
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
* @Description	:���ڳ�ʼ������
* @Input		:Baud_rate
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void uart_config0(uint32_t Baud_rate)
{
	UART_CFG_Type UARTConfigStruct;
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 1;//���ùܽŹ���Ϊ���ڹ���
	PinCfg.Portnum = 0;//���ùܽŶ˿ں�,GPIO0
	PinCfg.Pinnum = 3;//GPIO0_3
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	PinCfg.Pinnum = 2;//GPIO0_2
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	
	UARTConfigStruct.Baud_rate = Baud_rate;//���ò�����
	UARTConfigStruct.Databits=UART_DATABIT_8;//��������8λ
	UARTConfigStruct.Parity=UART_PARITY_NONE;//��У��
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//����ֹͣλ1λ
	UART_Init(LPC_UART0, &UARTConfigStruct);//��ʼ���ṹ��
	
	UART_TxCmd(LPC_UART0, ENABLE);//ʹ�ܷ���
	
	UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);//���ý����ж�
	NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));//�������ȼ�
	NVIC_EnableIRQ(UART0_IRQn);//�����ն�

}
/*********************************************************************************************************
������:void UART0_IRQHandler(void)
��������: ����0�ж�ͨ��������
����:��
����ֵ:��
*********************************************************************************************************/
void UART0_IRQHandler(void)
{
	u8 temp;
	NVIC_ClearPendingIRQ(UART0_IRQn);
	if((UART_GetLineStatus(LPC_UART0)&0x01))//��ȡLSRʱ�жϻᱻ���
	{
		temp = UART_ReceiveByte(LPC_UART0);
		fifo_putc(&SetCache,temp);
	}
}
/*******************************************************************************
* @Function		:void uart_config3(uint32_t Baud_rate)
* @Description	:���ڳ�ʼ������
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
	PinCfg.Funcnum = 2;//���ùܽŹ���Ϊ���ڹ���
	PinCfg.Portnum = 0;//���ùܽŶ˿ں�,GPIO0
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	PinCfg.Pinnum = 0;
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	
	UARTConfigStruct.Baud_rate = Baud_rate;//���ò�����
	UARTConfigStruct.Databits=UART_DATABIT_8;//��������8λ
	UARTConfigStruct.Parity=UART_PARITY_NONE;//��У��
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//����ֹͣλ1λ
	UART_Init(LPC_UART3, &UARTConfigStruct);//��ʼ���ṹ��
	
	UART_TxCmd(LPC_UART3, ENABLE);//ʹ�ܷ���
	
	UART_IntConfig(LPC_UART3, UART_INTCFG_RBR, ENABLE);//���ý����ж�
	NVIC_SetPriority(UART3_IRQn, ((0x01<<3)|0x01));//�������ȼ�
	NVIC_EnableIRQ(UART3_IRQn);//�����ն�
#endif
}

#if 0//�ÿӰ����������ˣ���Ȼ����~_~
void UART3_IRQHandler(void)
{
	u8 temp;
	NVIC_ClearPendingIRQ(UART3_IRQn);
	if((UART_GetLineStatus(LPC_UART3)&0x01))//��ȡLSRʱ�жϻᱻ���
	{
		temp = UART_ReceiveByte(LPC_UART3);
		fifo_putc(&BleCache,temp);
	}
}
#else
/*******************************************************************************
* @Function		:void uart_config3(uint32_t Baud_rate)
* @Description	:�����жϺ���
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
			case IIR_RLS://����ǽ�����״̬
			{
				LSRValue = LPC_UART3->LSR;
				if ( LSRValue & (LSR_OE | LSR_PE | LSR_FE | LSR_RXFE | LSR_BI) )
				{
//					UART3Status = LSRValue;
					Dummy = LPC_UART3->RBR; //�������ݷ��������
					return;
				}
				if ( LSRValue & LSR_RDR )//���ݿ���
				{
					temp = LPC_UART3->RBR;
					fifo_putc(&BleCache,temp);
				}
			}
			case IIR_CTI://��ʱ״̬
			{
//				UART3Status |= 0x100;
				break;
			}
			case  IIR_RDA://��������״̬ZZ
			{
				temp = LPC_UART3->RBR;
				fifo_putc(&BleCache,temp);
				break;
			}
			case IIR_THRE://���ͱ��ּĴ����ж�
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

















