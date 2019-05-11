/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Fifo.c
Description		: 主要实现对要处理的数据进行缓存
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-03-29
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Fifo.h"

/*******************************************************************************
* @Function		:u8 fifo_init(FIFO_t *head, u8 *buf, u32 len)
* @Description	:队列初始化
* @Input		:*head:队列头，*data:数据存储首地址，len:数据存储区域长度
* @Output		:null
* @Return		:TRUE OR FALSE
* @Others		:null
*******************************************************************************/
u8 fifo_init(FIFO_t *head, u8 *buf, u32 len)
{
	ERRR(head == NULL, return FALSE);
	head->data = buf;
	head->size = len;
	head->front = head->rear = 0;

	return TRUE;
}

/*******************************************************************************
* @Function		:void fifo_Clr(FIFO_t *head)
* @Description	:队列清空
* @Input		:*head:队列头
* @Output		:null
* @Return		:null
* @Others		:null
*******************************************************************************/
void fifo_Clr(FIFO_t *head)
{
	ERRR(head == NULL, return);
	head->front = 0;
	head->rear = 0;
}

/*******************************************************************************
* @Function		:u8 fifo_empty(FIFO_t *head)
* @Description	:判断队列是否为空
* @Input		:*head:队列头
* @Output		:null
* @Return		:TRUE(队列为空)/FALSE
* @Others		:null
*******************************************************************************/
u8 fifo_empty(FIFO_t *head)
{
	return ((head->front == head->rear) ? TRUE : FALSE);
}

/*******************************************************************************
* @Function		:static u8 fifo_full(FIFO_t *head)
* @Description	:判断队列是否已满
* @Input		:*head:队列头
* @Output		:null
* @Return		:TRUE(队列已满)/FALSE
* @Others		:null
*******************************************************************************/
u8 fifo_full(FIFO_t *head)
{

	return ((head->front == ((head->rear+1)%head->size)) ? TRUE : FALSE);
}

/*******************************************************************************
* @Function		:static u32 fifo_surplusSize(FIFO_t *head)
* @Description	:判断队列剩余空间大小
* @Input		:*head:队列头
* @Output		:null
* @Return		:剩余空间大小(字符为单位)
* @Others		:null
*******************************************************************************/
u32 fifo_surplusSize(FIFO_t *head)
{
	return ((head->front > head->rear)
			? (head->front - head->rear - 1)
			: (head->size + head->front - head->rear - 1));
}

/*******************************************************************************
* @Function		:u32 fifo_validSize(FIFO_t *head)
* @Description	:查询队列有效空间大小
* @Input		:*head:队列头
* @Output		:null
* @Return		:已用空间大小(字符为单位)
* @Others		:null
*******************************************************************************/
u32 fifo_validSize(FIFO_t *head)
{

	return ((head->rear < head->front)
			? (head->rear + head->size - head->front)
			: (head->rear - head->front));
}

/*******************************************************************************
* @Function		:u8 fifo_puts(FIFO_t *head, u8 *data, u32 len)
* @Description	:入队字符串操作
* @Input		:*head:队列头，*data:入队数据，len:数据长度
* @Output		:null
* @Return		:入队结果 TRUE/FALSE
* @Others		:null
*******************************************************************************/
u8 fifo_puts(FIFO_t *head, u8 *data, u32 len)
{  
	u32 size;

	ERRR(head == NULL, return FALSE);
	ERRR(len > fifo_surplusSize(head), return FALSE); //判断队列中是否还有存储空间

	size = MIN(len, head->size - head->rear);
	memcpy(head->data + head->rear, data, size);
	memcpy(head->data, data + size, len - size);

	head->rear = (head->rear + len)%head->size;

	return TRUE;   
}

/*******************************************************************************
* @Function		:u8 fifo_gets(FIFO_t *head, u8 *data, u32 len)
* @Description	:出队字符串操作
* @Input		:*head:队列头，*data:出队数据，len:数据长度
* @Output		:null
* @Return		:出队结果 TRUE/FALSE
* @Others		:null
*******************************************************************************/
u8 fifo_gets(FIFO_t *head, u8 *data, u32 len)
{
	u32 size;

	ERRR(head == NULL, return FALSE);
	ERRR(fifo_empty(head) == TRUE, return FALSE); //队列为空
	ERRR(len > fifo_validSize(head), return FALSE); //存储总数小于要读取的数

	size = MIN(len, head->size - head->front);
	memcpy(data, head->data + head->front, size);
	memcpy(data+size, head->data, len - size);

	head->front = (head->front + len)%head->size;

	return TRUE;   
}

/*******************************************************************************
* @Function		:u8 fifo_putc(FIFO_t *head, u8 data)
* @Description	:入队一个字符操作
* @Input		:*head:队列头，*data:入队数据
* @Output		:null
* @Return		:入队结果 TRUE/FALSE
* @Others		:null
*******************************************************************************/
u8 fifo_putc(FIFO_t *head, u8 data)
{
	ERRR(head == NULL, return FALSE);
	ERRR(fifo_full(head) == TRUE, return FALSE); //判断队列中是否还有存储空间

	head->data[head->rear] = data;

	head->rear = (++head->rear)%head->size;

	return TRUE;
}

/*******************************************************************************
* @Function		:u8 fifo_getc(FIFO_t *head, u8 *data)
* @Description	:出队一个字符操作
* @Input		:*head:队列头，*data:出队数据
* @Output		:null
* @Return		:入队结果 TRUE/FALSE
* @Others		:null
*******************************************************************************/
u8 fifo_getc(FIFO_t *head, u8 *data)
{
	ERRR(head == NULL, return FALSE);
	ERRR(fifo_empty(head) == TRUE, return FALSE); //队列为空

	*data = head->data[head->front];
	head->front = (++head->front)%head->size;

	return TRUE;   
}

/*******************************************************************************
* @Function		:u32 fifo_find(FIFO_t *head, const u8 *data, u32 len)
* @Description	:队列数据查找
* @Input		:*head:队列头，*data:数据匹配内容，len:匹配数据长度
* @Output		:null
* @Return		:队列匹配指针，查找到的位置
* @Others		:null
*******************************************************************************/
u32 fifo_find(FIFO_t *head, const u8 *data, u32 len)
{
	u32 i, n;

	ERRR((NULL == head)||(NULL == data)||(0 == len), return 0);

	for (i = head->front, n = 0; i != head->rear; i = (++i)%head->size)
	{
		if (head->data[i] == data[n])	//数据内容相等
		{
			if (++n == len)	//匹配长度相等
			{
				n--;
				break;
			}
		}
		else
		{
			n = 0;
		}
	}
	
	return ((i+head->size - n)%head->size);
}

/*******************************************************************************
* @Function		:u8 fifo_cmp(const FIFO_t *fifo, u32 seat, const u8 *cmp, u32 cmpsize)
* @Description	:队列数据比较
* @Input		:fifo:	比较源，seat:位于fifo的开始比较位置，cmp：	被比较数
					cmpsize:比较长度
* @Output		:null
* @Return		:TRUE/FALSE
* @Others		:null
*******************************************************************************/
u8 fifo_cmp(const FIFO_t *fifo, u32 seat, const u8 *cmp, u32 cmpsize)
{
	u32 i;

	ERRR((fifo->data == NULL)||(cmp == NULL), return FALSE);

	for (i = 0; i < cmpsize; i++)	//整个队列查找
	{
		if (fifo->data[(seat+i)%fifo->size] != *cmp++)
		{
			return FALSE;
		}
	}
	return TRUE;
}



