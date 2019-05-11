/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Analysis.h
Description: 命令解析相关头文件
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _analysis_h
#define _analysis_h
#include "base.h"
#include "fifo.h"
u8 Analysis_function(u8 *cmdtype,u8 *datatype,u8 *outdata,u8 *indata,u8 *len);
u8 Unpack_function(u8 cmd,u8 cdata,u8 *data,u8 datalen);
u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data);


#endif











