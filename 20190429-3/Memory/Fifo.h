/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Fifo.h
Description		: 主要实现对要处理的数据进行缓存
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-03-29
Modify			: 
Modify Time		: 
******************************************************************************/

#ifndef __FIFO_H
#define __FIFO_H

#include "arm_base_define.h"

typedef struct{
	u8   *data;
	u32   size;
	u32   front;
	u32   rear;
}FIFO_t;

#define ERRR(conf, ret)      do              \
							{                \
								if (conf)    \
								{            \
									ret;     \
								}            \
							} while(0) 


u8 fifo_init(FIFO_t *head, u8 *buf, u32 len);		//队列初始化
void fifo_Clr(FIFO_t *head);						//清空队列
u32 fifo_validSize(FIFO_t *head);					//数据可用空间大小
u8 fifo_empty(FIFO_t *head);						//队空判断
u8 fifo_puts(FIFO_t *head, u8 *data, u32 len);		//入队字符串操作
u8 fifo_gets(FIFO_t *head, u8 *data, u32 len);		//出队字符串操作
u8 fifo_putc(FIFO_t *head, u8 data);				//如对一个字符操作
u8 fifo_getc(FIFO_t *head, u8 *data);				//出队一个字符操作
u32 fifo_find(FIFO_t *head, const u8 *data, u32 len);//队列查找功能
u8 fifo_cmp(const FIFO_t *fifo, u32 seat, const u8 *cmp, u32 cmpsize);//内容对比功能
u32 fifo_surplusSize(FIFO_t *head);					//队列剩余空间判断
u8 fifo_full(FIFO_t *head);							//队满判断
#endif








