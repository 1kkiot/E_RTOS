#ifndef SPI_H
#define SPI_H

#include "nrf_gpio.h"
#include "nrf_drv_spis.h"

#define APP_SPIS_CS_PIN       1//20
#define APP_SPIS_MISO_PIN     3//18
#define APP_SPIS_MOSI_PIN     4//17
#define APP_SPIS_SCK_PIN      2//19


#define APP_SPIS_IRQ_PRIORITY 3

#define SPIS_BUFFER 250
extern uint8_t  m_tx_buf[SPIS_BUFFER];
ret_code_t spis_gpio_init(void);
void spis_process(void);
void spis_event_handler(nrf_drv_spis_event_t event);


#endif

