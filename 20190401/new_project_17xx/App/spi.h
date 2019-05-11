#ifndef _psi_h
#define _psi_h
#include "memory.h"
#define		SPI_CHILDNUM				 4


#define		CS_PORT_NUM1				0
#define		CS_PIN_NUM1					6
#define		CS_PORT_NUM2				2
#define		CS_PIN_NUM2					2
#define		CS_PORT_NUM3				2
#define		CS_PIN_NUM3					3
#define		CS_PORT_NUM4				2
#define		CS_PIN_NUM4					6

#define		SCK_PIN_NUM					7
#define		MISO_PIN_NUM				8
#define		MOSI_PIN_NUM				9


#define		SPI_DATABIT_SIZE			8

#define		SPI_RATE 					(4000000)
#define SPI_BUFFERSIZE 250
extern uint8_t  ucSPITxBuffer[SPI_BUFFERSIZE];
extern uint8_t  ucSPIRxBuffer[SPI_BUFFERSIZE];
extern uint16_t usDataSended;
extern uint8_t  ucSPITxBuffer[];
void LPC17XXSPI_Init(void);
void LPC17XXSPI_Process(void);

#endif





