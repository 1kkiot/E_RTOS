/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Command.c
Description		: 主要实现读标签命令功能
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-26
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Command.h"
#include "Delay.h"
#include "Fifo.h"
#include "Memory.h"
#include "Wifi.h"
#include "Debugprintf.h"
//由于指令是从串口读出来的，故只能将指令一条条打包，希望后面可以将指令格式进行统一打包
//希望后面的niu x工程师可以挑战更高的刚好的代码执行效率
//指令说明
//>>05 07 FF 01 01 00 82 86//广播指令
//<<05 07 01 01 01 0F 1C A7 
//>>05 06 FF 01 00 90 97//第二条指令
//<<05 11 01 01 00 00 01 29 11 80 01 09 70 19 00 47 32 C7

//>>FA 08 FF 00 01 01 01 FF 8E//第三条指令
//<<FA 17 01 00 01 00 00 01 01 02 02 00 03 01 64 00 00 00 00 00 00 00 C0 95
//>>FA 08 FF 40 01 02 01 20 B2//四
//<<FA 17 01 40 01 00 00 01 00 09 00 07 00 10 07 13 01 00 00 00 00 00 80 14
//>>FA 08 FF 00 01 03 01 4F BD//五
//<<FA 17 01 00 01 00 00 01 00 00 00 E8 03 00 00 00 00 43 83 00 00 00 9A BF
//>>FA 08 FF 40 01 04 01 F0 E6//六
//<<FA 17 01 40 01 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 B5 E6
//>>FA 08 FF 00 01 05 01 9F E9//七
//<<FA 17 01 00 01 00 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 80 1E
//>>FA 08 FF 40 01 06 01 40 D5//八
//<<FA 17 01 40 01 00 00 01 01 00 03 00 00 01 00 00 00 01 00 01 00 00 D4 03
//>>FA 08 FF 00 01 07 01 2F DA//九
//<<FA 17 01 00 01 00 00 01 00 00 00 00 06 00 00 00 00 00 00 00 00 00 52 F6

//>>FA 16 FF 40 31 02 03 06 00 03 00 03 00 02 00 00 01 00 02 00 00 84 C2//读标签指令1
//<<FA 22 01 40 31 00 00 00 02 00 02 0E 02 01 07 04 4A 59 32 62 5D 80 0E 02 01 07 04 4F 59 32 62 5D 80 0F 31
//>>FA 16 FF 00 31 02 03 06 00 03 00 03 00 02 00 00 01 00 02 00 00 8B 00//读标签指令2
//<<FA 22 01 00 31 00 00 00 02 00 02 0E 02 01 07 04 4A 59 32 62 5D 80 0E 02 01 07 04 4F 59 32 62 5D 80 47 4D

//>>FA 16 FF 40 31 02 03 06 00 03 00 03 00 02 00 00 01 00 02 00 00 84 C2//读标签指令1
//<<FA 0C 01 40 31 00 00 00 00 00 00 A1 24//没有标签时返回
//>>FA 16 FF 00 31 02 03 06 00 03 00 03 00 02 00 00 01 00 02 00 00 8B 00//读标签指令2
//<<FA 0C 01 00 31 00 00 00 00 00 00 50 41//没有标签时返回

_READ_s READ_STUATS=STAUTS0;

/*******************************************************************************
* @Function		:u16 cal_crc16_ext(u16 initval ,u8 *ptr, u8 len)
* @Description	:计算crc校验
* @Input		:u16 initval ,u8 *ptr, u8 len
* @Output		:null
* @Return		:crc
* @Others		:null
*******************************************************************************/
u16 cal_crc16_ext(u16 initval ,u8 *ptr, u8 len)
{
	u16 crc;
	u16 i,j;
	u8 val;
	crc=0;
	crc= initval ;
	for(i=0;i<len;i++)
	{
		val =ptr[i];
		crc^=val ;
		for(j=0;j<8;j++)
		{
			if(crc&0x0001)
			{
				crc=(crc>>1)^0x8408;
			}
			else
			{
				crc=(crc>>1);
			}
		}
	} 
	return(crc);
}

void cmd_1()
{
//	u16 tmp;
	u8 buf[] = {0x05,0x07,0xFF,0x01,0x01,0x00,0x82,0x86};
//	tmp = cal_crc16_ext(0xffff,&buf[1],5);
//	tmp = 0xaa;
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}

void cmd_2()
{
//	u16 tmp;
	u8 buf[] = {0x05,0x06,0xFF,0x01,0x00,0x90,0x97};
//	tmp = cal_crc16_ext(0xffff,&buf[1],4);
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}

void cmd_3()
{
	u8 buf[] = {0xFA,0x08,0xFF,0x00,0x01,0x01,0x01,0xFF,0x8E};
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}

void cmd_4()
{
	u8 buf[] = {0xFA,0x08,0xFF,0x40,0x01,0x02,0x01,0x20,0xB2};
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}
void cmd_5()
{
	u8 buf[] = {0xFA,0x08,0xFF,0x00,0x01,0x03,0x01,0x4F,0xBD};
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}
void cmd_6()
{
	u8 buf[] = {0xFA,0x08,0xFF,0x40,0x01,0x04,0x01,0xF0,0xE6};
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}
void cmd_7()
{
	u8 buf[] = {0xFA,0x08,0xFF,0x00,0x01,0x05,0x01,0x9F,0xE9};
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}
void cmd_8()
{
	u8 buf[] = {0xFA,0x08,0xFF,0x40,0x01,0x06,0x01,0x40,0xD5};
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}
void cmd_9()
{
	u8 buf[] = {0xFA,0x08,0xFF,0x00,0x01,0x07,0x01,0x2F,0xDA};
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}
void cmd10()
{
	u8 buf[23] = {0xFA,0x16,0xFF,0x40,0x31,0x02,0x03,0x06,0x00,0x03,0x00,\
				0x03,0x00,0x02,0x00,0x00,0x01,0x00,0x02,0x00,0x00,0x84,0xC2};
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}
void cmd11()
{//FA 16 FF 00 31 02 03 06 00 03 00 03 00 02 00 00 01 00 02 00 00 8B 00
	u8 buf[23] = {0xFA,0x16,0xFF,0x00,0x31,0x02,0x03,0x06,0x00,0x03,0x00,\
				0x03,0x00,0x02,0x00,0x00,0x01,0x00,0x02,0x00,0x00,0x8B,0x00};
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}


void Read_fun()
{
	switch(READ_STUATS)
	{
		case STAUTS0:
			//cmd_1();
			READ_STUATS = STAUTS1;
			break;
		case STAUTS1:
			//cmd_2();
			READ_STUATS = STAUTS2;
			break;
		case STAUTS2:
			cmd_3();
			READ_STUATS = STAUTS3;
			break;
		case STAUTS3:
			cmd_4();
			READ_STUATS = STAUTS4;
			break;
		case STAUTS4:
			cmd_5();
			READ_STUATS = STAUTS5;
			break;
		case STAUTS5:
			cmd_6();
			READ_STUATS = STAUTS6;
			break;
		case STAUTS6:
			cmd_7();
			READ_STUATS = STAUTS7;
			break;
		case STAUTS7:
			cmd_8();
			READ_STUATS = STAUTS8;
			break;
		case STAUTS8:
			cmd_9();
			READ_STUATS = STAUTS9;
			break;
		case STAUTS9:
			cmd11();
			READ_STUATS = STAUTS10;
			break;
		case STAUTS10:
			cmd10();
			READ_STUATS = STAUTS11;
			break;
		default:
			break;
	}
}

void read_tag_cmd()
{
	static u8 flag=0;
	u16 tmp;
	u8 buf[23] = {0xFA,0x16,0xFF,0x40,0x31,0x02,0x03,0x06,0x00,0x03,0x00,\
				0x03,0x00,0x02,0x00,0x00,0x01,0x00,0x02,0x00,0x00,0x84,0xC2};
	flag = !flag;
	(flag == false) ? (buf[3] = 0x40) : (buf[3] = 0x00);
	tmp = cal_crc16_ext(0xffff,&buf[1],20);
	buf[21] = (tmp & 0xff);
	buf[22] = (tmp>>8) & 0xff;
	send_data(buf,sizeof(buf));
	printf_1(buf,sizeof(buf));
}


u8 send_data(u8 *data,u8 len)
{
	u16 i;
	for(i=0;i<len;i++)
	{
		while((USART3->ISR & 0x40) == 0)
		{
			;
		}
		USART3->TDR = (uint8_t)data[i];
	}
	return true;
}





