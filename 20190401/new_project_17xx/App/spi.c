/*
 * 文件名称: spi.c
 * 创建人  : 黄帅
 * 创建时间: 2018.12.22
 * 文件说明: SPI逻辑处理
 * 更改记录:
	使用说明：在主循环中调用LPC17XX_SPIProcess()即可
	注意：SPI的全双工，发送一个字节的同时接收一个字节，
	但是主节点不知道子节点指令的长度，所以在使用时，
	请保证主节点发送数据长度大于子节点的指令长度
	硬件IO说明:
	CS1    0.6
	CS2    2.7
	CS3    2.8
	CS4    2.6
	SCK    0.7
	MISO 0.8
	MOSI 0.9
*/
#include "spi.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include <string.h>
#include "gpio.h"
#include "logic.h"

#define SPI_MAXRETRYTIMES 3

/*用于访问一个子SPI结束后的延时*/
volatile uint16_t usDelayms  = 0;
/*SPI 子节点选择*/
uint8_t  ucSPIIndex = 0;
uint8_t  ucErrTimes = 0;

/*缓冲区*/
uint8_t  ucSPITxBuffer[SPI_BUFFERSIZE];
uint8_t  ucSPIRxBuffer[SPI_BUFFERSIZE];
uint16_t usDataSended = 250;

typedef enum
{
    SPISTATUS_INIT,
    SPISTATUS_SELECT,
    SPISTATUS_WAIT,
    SPISTATUS_SEND,
    SPISTATUS_WAITSENDED,
    SPISTATUS_RECVPROCESS,
    SPISTATUS_DELAY,
    SPISTATUS_ERR
}SPISTATUS;
SPISTATUS eSPIStatus = SPISTATUS_INIT;

/******************************************************************************
 * 函数名称:   void LPC17XXSPI_CSHighLow(uint8_t ucCSIndex, uint8_t ucHighLow)
 * 功能描述:   SPI CS引脚高低电平
 * 前提条件:   对应得CS引脚已经配置为输出
 * 输入:       ucCSIndex-CS索引 ucHighLow-1高 0低
 * 输出:       无
 * 返回        
 * 注释:       
 *****************************************************************************/
void LPC17XXSPI_CSHighLow(uint8_t ucCSIndex, uint8_t ucHighLow)
{
	static const uint8_t ucCSTable[SPI_CHILDNUM][2] = {CS_PORT_NUM1,CS_PIN_NUM1,CS_PORT_NUM2,CS_PIN_NUM2,CS_PORT_NUM3,CS_PIN_NUM3,CS_PORT_NUM4,CS_PIN_NUM4 };
	if(ucCSIndex>=SPI_CHILDNUM)
		return;
	if (ucHighLow)
	{
		GPIO_SetValue(ucCSTable[ucCSIndex][0], (1<<ucCSTable[ucCSIndex][1]));
	}
	else
	{
		GPIO_ClearValue(ucCSTable[ucCSIndex][0], (1<<ucCSTable[ucCSIndex][1]));
	}
}

/******************************************************************************
 * 函数名称:   void LPC17XXSPI_Init()
 * 功能描述:   SPI 相关初始化
 * 前提条件:   无
 * 输入:       无
 * 输出:       无
 * 返回        
 * 注释:       
 *****************************************************************************/
void LPC17XXSPI_Init()
{
	uint16_t usCount;
	PINSEL_CFG_Type sPinCfg;
	SSP_CFG_Type sSPIConfigStruct;

	sPinCfg.Funcnum   = PINSEL_FUNC_2;
	sPinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	sPinCfg.Pinmode   = PINSEL_PINMODE_PULLUP;

	sPinCfg.Portnum = CS_PORT_NUM1;
	sPinCfg.Pinnum  = SCK_PIN_NUM;
	PINSEL_ConfigPin(&sPinCfg);
	
	sPinCfg.Pinnum  = MISO_PIN_NUM;
	PINSEL_ConfigPin(&sPinCfg);
	sPinCfg.Pinnum  = MOSI_PIN_NUM;
	PINSEL_ConfigPin(&sPinCfg);

	sPinCfg.Pinnum  = CS_PIN_NUM1;
	sPinCfg.Funcnum = PINSEL_FUNC_0;
	PINSEL_ConfigPin(&sPinCfg);

	sPinCfg.Portnum = CS_PORT_NUM2;
	sPinCfg.Pinnum  = CS_PIN_NUM2;
	sPinCfg.Funcnum = PINSEL_FUNC_0;
	PINSEL_ConfigPin(&sPinCfg);
	sPinCfg.Portnum = CS_PORT_NUM3;
	sPinCfg.Pinnum  = CS_PIN_NUM3;
	sPinCfg.Funcnum = PINSEL_FUNC_0;
	PINSEL_ConfigPin(&sPinCfg);
	sPinCfg.Portnum = CS_PORT_NUM4;
	sPinCfg.Pinnum  = CS_PIN_NUM4;
	sPinCfg.Funcnum = PINSEL_FUNC_0;
	PINSEL_ConfigPin(&sPinCfg);


	SSP_ConfigStructInit(&sSPIConfigStruct);
	sSPIConfigStruct.CPHA      = SSP_CPHA_SECOND;
	sSPIConfigStruct.CPOL      = SSP_CPOL_HI;
	sSPIConfigStruct.ClockRate = SPI_RATE;
	sSPIConfigStruct.FrameFormat = SSP_FRAME_SPI;
	sSPIConfigStruct.Databit   = SSP_DATABIT_8;
	sSPIConfigStruct.Mode      = SSP_MASTER_MODE;
	SSP_Init(LPC_SSP1, &sSPIConfigStruct);
	SSP_Cmd(LPC_SSP1, ENABLE);


	GPIO_SetDir(CS_PORT_NUM1, (1<<CS_PIN_NUM1), 1);
	GPIO_SetDir(CS_PORT_NUM2, (1<<CS_PIN_NUM2), 1);   
	GPIO_SetDir(CS_PORT_NUM3, (1<<CS_PIN_NUM3), 1);   
	GPIO_SetDir(CS_PORT_NUM4, (1<<CS_PIN_NUM4), 1);
	LPC17XXSPI_CSHighLow(0, 1);
	LPC17XXSPI_CSHighLow(1, 1);
	LPC17XXSPI_CSHighLow(2, 1);
	LPC17XXSPI_CSHighLow(3, 1);

	ucSPIIndex = 0;
	usDelayms  = 0;
	ucErrTimes = 0;

	memset(ucSPITxBuffer, 0, SPI_BUFFERSIZE);
	usCount=SPI_BUFFERSIZE;
	while(usCount--)
	{
		ucSPITxBuffer[usCount]=usCount;
	}
	memset(ucSPIRxBuffer, 0, SPI_BUFFERSIZE);
}

/******************************************************************************
 * 函数名称:   void LPC17XXSPI_Process()
 * 功能描述:   SPI 逻辑处理
 * 前提条件:   无
 * 输入:       无
 * 输出:       无
 * 返回        
 * 注释:       
 *****************************************************************************/
void LPC17XXSPI_Process()
{  
	u8 temp;
	switch(eSPIStatus)
	{
		case SPISTATUS_INIT:
		{
			LPC17XXSPI_Init();
			eSPIStatus = SPISTATUS_SELECT;
		}
		break;
		case SPISTATUS_SELECT:
		{
			uint8_t ucSPIChildIndex = 0;
			while(ucSPIChildIndex<SPI_CHILDNUM)
			{
				LPC17XXSPI_CSHighLow(ucSPIChildIndex, 1);
				++ucSPIChildIndex;
			}
			memset(ucSPIRxBuffer, 0, SPI_BUFFERSIZE);
			LPC17XXSPI_CSHighLow(ucSPIIndex, 0);
			usDelayms  = 1;
			if(Runspi.count >= 2)
			{
				memset(ucSPITxBuffer,0,sizeof(ucSPITxBuffer));
				Runspi.count = 0;
			}
			eSPIStatus = SPISTATUS_WAIT;
		}
		break;
		case SPISTATUS_WAIT:
		{
			if(usDelayms==0)
				eSPIStatus = SPISTATUS_SEND;
		}
		break;
		case SPISTATUS_SEND:
		{
			uint16_t usSendIndex = 0;
			uint8_t  ucRecvedData= 0;
			while (LPC_SSP1->SR & SSP_SR_RNE)
			{
				SSP_ReceiveData(LPC_SSP1);
			}
			LPC_SSP1->ICR = SSP_ICR_BITMASK;
			while(usSendIndex<usDataSended)
			{
				while(0==(LPC_SSP1->SR & SSP_SR_TFE))
				{
					;
				}
				SSP_SendData(LPC_SSP1, ucSPITxBuffer[usSendIndex]);
				while(0==(LPC_SSP1->SR & SSP_SR_RNE))
				{
					;
				}
				ucRecvedData = SSP_ReceiveData(LPC_SSP1);
				if ((LPC_SSP1->RIS) & SSP_RIS_ROR)
				{
					LPC_SSP1->ICR = SSP_RIS_ROR;
				}
				if(usSendIndex==0 && ucRecvedData==0xFF)
				{
					break;
				}
				else
				{
					//ucSPIRxBuffer[usSendIndex] = SSP_DR_BITMASK(ucRecvedData);
					temp = SSP_DR_BITMASK(ucRecvedData);
					if(temp != 0x00)
					{
						fifo_putc(&CacheRx,temp);
					}
				}
				++usSendIndex;
			}
			Runspi.count++;
			if((usSendIndex!=usDataSended) && (ucErrTimes<SPI_MAXRETRYTIMES))
			{
				++ucErrTimes;
				usDelayms  = 2;
				eSPIStatus = SPISTATUS_DELAY;
			}
			else
			{
				usDelayms  = 1;
				eSPIStatus = SPISTATUS_WAITSENDED;
			}
		}
		break;
		case SPISTATUS_WAITSENDED:
		{
			if(usDelayms==0)
			{
				LPC17XXSPI_CSHighLow(ucSPIIndex, 1);
				eSPIStatus = SPISTATUS_RECVPROCESS;
			}
		}
		break;
		case SPISTATUS_RECVPROCESS://接收buff处理
		{
//			if(memcmp((uint8_t *)"jason test", ucSPIRxBuffer, 10)==0)
//			{
//				;
//			}
			ucErrTimes = 0;
			memset(ucSPIRxBuffer, 0, SPI_BUFFERSIZE);
			++ucSPIIndex;
			ucSPIIndex %= SPI_CHILDNUM; 
			usDelayms  = 11;
			eSPIStatus = SPISTATUS_DELAY;
		}
		break;
		case SPISTATUS_DELAY:
			if(usDelayms == 0)
			{
				uint8_t ucSPIChildIndex = 0;
				while(ucSPIChildIndex<SPI_CHILDNUM)
				{
					LPC17XXSPI_CSHighLow(ucSPIChildIndex, 1);
					++ucSPIChildIndex;
				}
				eSPIStatus = SPISTATUS_SELECT;
			}
		break;
		case SPISTATUS_ERR:
			SSP_DeInit(LPC_SSP1);
			eSPIStatus = SPISTATUS_INIT;
		break;
	}
}











