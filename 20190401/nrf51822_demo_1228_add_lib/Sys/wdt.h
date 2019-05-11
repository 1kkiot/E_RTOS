/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : wdt.h
Description: 看门狗相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-03-06
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _wdt_h
#define _wdt_h

#define			RELOAD_COUNT			((32768*3)-1)

void wdt_start(void);
void wdt_stop(void);
void wdt_feed(void);
void wdt_init(void);
 
#endif


