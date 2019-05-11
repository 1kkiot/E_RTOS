/***************************Copyright BestFu 2014-05-14*************************
文	件：	contain_error.h
说	明：	库头文件
编	译：	Keil uVision4 V5.26.0.0
版	本：	v1.0
编	写：	Unarty
日	期：	2018-05-30
*******************************************************************************/
#ifndef __containerror_H
#define __containerror_H

/*容错宏*/
#define ERRR(conf, ret)      do              \
                            {                \
                                if (conf)    \
                                {            \
                                    ret;     \
                                }            \
                            } while(0) 
							
#define ABS(i, j)		(((i) > (j)) ? ((i) - (j)) : ((j) - (i))) 		//获取绝对值

                                
void memcpy(void *dest, const void *src, unsigned int num); //内存考备
char memcmp(void *dest,  const void *src, unsigned int num);	//内存比较
void memmove(void *dest,  const void *src, unsigned int num);	//内存移动
void memset(void *dest, unsigned char const val, unsigned int num);	//内存设置 
void* memfind(void *dest, unsigned int dLen, void *src, unsigned int sLen);							
void memcharget(void *dest, unsigned char *len, void const *src, unsigned int size);

#endif 
/**************************Copyright*************************/
							
