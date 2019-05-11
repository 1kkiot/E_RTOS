/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : memory.c
Description: get cmd frame from uart fifo
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include "memory.h"
#include "fifo.h"


FIFO_t	Uart0Tx;
FIFO_t	Uart0Rx;
FIFO_t	Radiofifo;
FIFO_t	SPITxfifo;
FIFO_t	SPIRxfifo;

u8 Uart0Rx_buff[Uart0Rx_len];
u8 Uart0Tx_buff[Uart0Tx_len];
u8 Radiofifo_buff[Radiofifo_len];
u8 SPITxBuff[SPIRxlen];
u8 SPIRxBuff[SPITxlen];

/*******************************************************************************
* @Function		:void Init_fifo()
* @Description	:实现fifo初始化操作
* @Input		:null
* @Output		:null
* @Return		:null
* @Others		:null
********************************************************************************/
void Init_fifo()
{
	fifo_Init(&Uart0Tx,Uart0Tx_buff,Uart0Tx_len);//
	fifo_Init(&Uart0Rx,Uart0Rx_buff,Uart0Rx_len);//
	fifo_Init(&Radiofifo,Radiofifo_buff,Radiofifo_len);//用于缓存radio命令缓存
	fifo_Init(&SPITxfifo,SPITxBuff,SPITxlen);
	fifo_Init(&SPIRxfifo,SPIRxBuff,SPIRxlen);
}









