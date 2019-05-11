/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Flash.c
Description: 实现对内部flash读写功能
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-03
Modify	   : 
Modify Time: 
******************************************************************************/
#include "Flash.h"
#include "nrf_gpio.h"
#include "nrf_drv_common.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf.h"
#include "string.h"

#define FLASH_PAGESIZE   1024
#define FLASH_PAGENUMMAX 256

uint32_t m_flash_pagesize   = FLASH_PAGESIZE;
uint32_t m_flash_pagenummax = FLASH_PAGENUMMAX;

void flash_init()
{
	m_flash_pagesize   = NRF_FICR->CODEPAGESIZE;//page size
	m_flash_pagenummax = NRF_FICR->CODESIZE;//memory size
}

static inline void flash_wait_for_ready()
{
	/*wait for flash ready*/
	while(NRF_NVMC->READY == NVMC_READY_READY_Busy){;}
}
//*******************************************************
/** 擦除flash的页
* 擦除一个页时只需向ERASEPAGE寄存器写入该页第一个字的地址即可
*/
void flash_page_erase_1(uint32_t * page_address)
{
	// 设置寄存器CONFIG.WEN = 2 使能FLASH的擦除操作
	NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Een << NVMC_CONFIG_WEN_Pos);
	// 等待NVMC(非易失存储器控制器)准备就绪
	while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
	{
		// Do nothing.
	}
	// 擦除页 擦除一个页时只需向ERASEPAGE寄存器写入该页第一个字的地址即可
	NRF_NVMC->ERASEPAGE = (uint32_t)page_address;
		
	// 等待NVMC(非易失存储器控制器)准备就绪
	while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
	{
		// Do nothing.
	}
	// 设置寄存器CONFIG.WEN = 0 关闭擦除，即FLASH处于只读状态
	NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);
		// 等待NVMC(非易失存储器控制器)准备就绪
	while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
	{
		// Do nothing.
	}
}

/** 向FLASH指定地址写入一个字
 */
void flash_word_write(uint32_t * address, uint32_t value)
{
	// 设置寄存器CONFIG.WEN = 1 使能FLASH的写操作
	NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos);

	// 等待NVMC(非易失存储器控制器)准备就绪
	while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
	{
		// Do nothing.
	}
	//向该地址写入一个字value
	*address = value;
	// 等待NVMC(非易失存储器控制器)准备就绪
		while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
	{
		// Do nothing.
	}
	// 设置寄存器CONFIG.WEN = 0 ，关闭写功能
	NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);
	// 等待NVMC(非易失存储器控制器)准备就绪
		while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
	{
		// Do nothing.
	}
}
void flash_write_buff(uint32_t *page_address, const uint8_t * src,uint8_t len)
{
//	uint32_t page_address = page_number*m_flash_pagesize;
//	uint32_t num_words    = m_flash_pagesize>>2;
	uint32_t num_index    = 0;
	const uint32_t *page_data = (const uint32_t *)src;

	/*enable write*/
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
	__ISB();
	__DSB();

	/*page write*/
	for(num_index=0;num_index<len;num_index++)
	{
		((uint32_t *)page_address)[num_index] = *page_data++;
		flash_wait_for_ready();
	}
	
	/*enable readonly*/
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
	__ISB();
	__DSB();
}


//*******************************************************
void flash_page_erase(uint32_t page_number)
{
	if(page_number<m_flash_pagenummax)
	{
		/*enable erase*/
		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Een;
		__ISB();
		__DSB();
		/*erase page*/
		page_number *= m_flash_pagesize;
		NRF_NVMC->ERASEPAGE = page_number;
		flash_wait_for_ready();
		/*enable readonly*/
		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
		__ISB();
		__DSB();
	}
}

void flash_page_write(uint32_t page_number, const uint8_t * src)
{
	if(page_number<m_flash_pagenummax)
	{
		uint32_t page_address = page_number*m_flash_pagesize;
		uint32_t num_words    = m_flash_pagesize>>2;
		uint32_t num_index    = 0;
		const uint32_t *page_data = (const uint32_t *)src;

		/*enable write*/
		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
		__ISB();
		__DSB();

		/*page write*/
		for(num_index=0;num_index<num_words;num_index++)
		{
			((uint32_t *)page_address)[num_index] = *page_data++;
			flash_wait_for_ready();
		}
		
		/*enable readonly*/
		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
		__ISB();
		__DSB();
	}
}

void flash_byte_write(uint32_t byte_address, uint8_t value)
{
	uint32_t byte_mask     = byte_address&0x03;
	uint32_t words_address = byte_address & (~byte_mask);
	uint32_t words_value   = (*(uint32_t*)words_address & ~((uint32_t)0xFF << (byte_mask << (uint32_t)3)));
	words_value = words_value + ((uint32_t)value<<(byte_mask<<3));
	/*enable write*/
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
	__ISB();
	__DSB();
	/*byte write*/
	*(uint32_t *)words_address = words_value;
	flash_wait_for_ready();
	/*enable readonly*/
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
	__ISB();
	__DSB();
}

void flash_words_write(uint32_t words_address, const uint32_t *src, uint32_t num_words)
{
	uint32_t num_index = 0;

	words_address &= 0xFFFFFFFC;
	if(num_words>(m_flash_pagesize>>2))
	{
		num_words = m_flash_pagesize>>2;
	}
	/*enable write*/
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
	__ISB();
	__DSB();
		
	/*words write*/
	while(num_index<num_words)
	{
		((uint32_t *)words_address)[num_index] = *src++;
		++num_index;
	}
	flash_wait_for_ready();
			
	/*enable readonly*/
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
	__ISB();
	__DSB();
}

void flash_write(uint32_t bytes_address, const uint8_t *src, uint32_t num_byte)
{
	uint32_t bytes_address_temp = bytes_address-(bytes_address%m_flash_pagesize);
	const uint8_t *src_temp = src;
	uint32_t num_index = 0;		
	uint32_t num_pages = num_byte/m_flash_pagesize;
	uint32_t num_lastline = num_byte%m_flash_pagesize;
	while(num_index<num_pages)
	{
		uint32_t num_page_index = bytes_address_temp/m_flash_pagesize;
		flash_page_erase(num_page_index);
		flash_page_write(num_page_index, src_temp);
		src_temp += m_flash_pagesize;
		bytes_address_temp += m_flash_pagesize;
		++num_index;
	}
	
	if(num_lastline)
	{
		flash_page_erase(bytes_address_temp/m_flash_pagesize);
		while(num_lastline--)
		{
			flash_byte_write(bytes_address_temp, *src_temp);
			++src_temp;
			++bytes_address_temp;
		}
	}
}

void flash_read(uint32_t bytes_address, uint8_t *dest, uint32_t num_byte)
{
	uint32_t num_index = 0;
	uint8_t *dest_temp = (uint8_t *)dest;
	uint8_t *src       = (uint8_t *)bytes_address;
	
	while(num_index<num_byte)
	{
		dest[num_index] = *src;
		++src;
		++num_index;
	}
}

void flash_test()
{
	uint8_t constbuffer[1024];
	uint8_t testbuffer[1024];
	uint32_t ulSrc[560];
	uint32_t ulDest[560];
	uint32_t index = 0;
	
	while(index<1024)
	{
		constbuffer[index] = index&0xFF;
		if(index<560) ulSrc[index] = index;
		++index;
	}

	flash_page_erase(m_flash_pagenummax-1);
	flash_page_write(m_flash_pagenummax-1, constbuffer);
	flash_read((m_flash_pagenummax-1)*m_flash_pagesize, testbuffer, 862);
	
	if(memcmp(testbuffer, constbuffer, 862)==0)
	{
		printf("1024succ!!!!!\r\n");
	}
	else
	{
		printf("1024fail!!!\r\n");
	}

	flash_write((m_flash_pagenummax-3)*m_flash_pagesize, (const uint8_t*)ulSrc, 560*4);
	flash_read((m_flash_pagenummax-3)*m_flash_pagesize, (uint8_t *)ulDest, 560*4);
	
	if(memcmp(ulSrc, ulDest, 560*4)==0)
	{
		printf("we560succ!!!!!\r\n");
	}
	else
	{
		printf("fail560!!!\r\n");
	}
}

