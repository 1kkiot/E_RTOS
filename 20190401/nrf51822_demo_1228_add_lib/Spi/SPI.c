#include "SPI.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_drv_spis.h"
#include "nrf_drv_common.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_gpio.h"
#include "base.h"
#include "fifo.h"
#include "memory.h"
#include "task.h"

#define SPIS_INSTANCE 1
static const nrf_drv_spis_t spis = NRF_DRV_SPIS_INSTANCE(SPIS_INSTANCE);

uint8_t  m_tx_buf[SPIS_BUFFER]={0};
static uint8_t  m_rx_buf[SPIS_BUFFER]={0};
static volatile bool spis_xfer_done;
static uint16_t m_tx_length  = 0;
static uint16_t m_real_recved = 0;
static uint16_t m_real_sended = 0;

typedef enum _STATUS
{
	SPISTATUS_INIT,
	SPISTATUS_PREPAREDATA,
	SPISTATUS_TRANSFER,
	SPISTATUS_WAIT,
	SPISTATUS_DATAPROCESS,
	SPISTATUS_UNINIT
}SPISTATUS;
SPISTATUS m_spistatus = SPISTATUS_INIT;


void spis_event_handler(nrf_drv_spis_event_t event)
{
	if (event.evt_type == NRF_DRV_SPIS_XFER_DONE)
	{
		spis_xfer_done = true;
		m_real_recved = event.rx_amount;
		m_real_sended = event.tx_amount;
	}
}

ret_code_t spis_gpio_init(void)
{
	spis_xfer_done = false;

	nrf_drv_spis_config_t spis_config = NRF_DRV_SPIS_DEFAULT_CONFIG(SPIS_INSTANCE);
	spis_config.csn_pin               = APP_SPIS_CS_PIN;
	spis_config.miso_pin              = APP_SPIS_MISO_PIN;
	spis_config.mosi_pin              = APP_SPIS_MOSI_PIN;
	spis_config.sck_pin               = APP_SPIS_SCK_PIN;
	spis_config.mode                  = NRF_DRV_SPIS_MODE_1;
	spis_config.bit_order             = NRF_DRV_SPIS_BIT_ORDER_MSB_FIRST;
	return nrf_drv_spis_init(&spis, &spis_config, spis_event_handler);
}

void spis_process(void)
{
	switch(m_spistatus)
	{
		case SPISTATUS_INIT:
		{
			if(NRF_SUCCESS==spis_gpio_init())
			{
				m_spistatus = SPISTATUS_PREPAREDATA;
			}
			else 
			{
				m_spistatus = SPISTATUS_UNINIT;
			}
			m_tx_length = SPIS_BUFFER;
			memset(m_rx_buf, 0, SPIS_BUFFER);
		}
		break;
		case SPISTATUS_PREPAREDATA:
			m_spistatus = SPISTATUS_TRANSFER;
		break;
		case SPISTATUS_TRANSFER:
		{
			spis_xfer_done = false;
			Send.num++;
			nrf_drv_spis_buffers_set(&spis, m_tx_buf, m_tx_length, m_rx_buf, m_tx_length);
			if(m_rx_buf[0] != 0)
			{
				fifo_puts(&SPIRxfifo,m_rx_buf,(m_rx_buf[1]+2));
				//printf("%s",&m_rx_buf[0]);
			}
			memset(m_rx_buf,0,sizeof(m_rx_buf));
			m_spistatus = SPISTATUS_WAIT;
		}
		break;
		case SPISTATUS_WAIT:
		{
			if(Send.num >= 1)
			{
				memset(m_tx_buf,0,sizeof(m_tx_buf));
			}
			if(!spis_xfer_done)
			{
				__WFE();
				//memset(m_tx_buf,0,sizeof(m_tx_buf));
			}
			else 
			{
				m_spistatus = SPISTATUS_DATAPROCESS;
			}
		}
		break;
		case SPISTATUS_DATAPROCESS:
		{
			m_spistatus = SPISTATUS_PREPAREDATA;
		}
		break;
		case SPISTATUS_UNINIT:
		{
			nrf_drv_spis_uninit(&spis);
			spis_xfer_done = false;
			m_spistatus = SPISTATUS_INIT;
		}
		break;
	}
}




















