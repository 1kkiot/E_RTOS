/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: ReCmd.c
Description		: 主要实现上位机下发指令解析功能
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-26
Modify			: 
Modify Time		: 
******************************************************************************/
#include "ReCmd.h"
#include "string.h"
#include "Debugprintf.h"
#include "Function.h"

/*******************************************************************************
* @Function		:u8 Analysis_cmd(u8 *cmd)
* @Description	:进行命令解析功能
* @Input		:u8 *cmd
* @Output		:null
* @Return		:true
* @Others		:null
*******************************************************************************/
u8 Analysis_cmd(u8 *cmd)
{
	char *token;
	char *segment_ptr[15];
	const char s[3] = ", =";
	char i;
	for(i = 0; i < 15; i++)
	{
		segment_ptr[i] = NULL;
	}
	i=0;
	token = strtok((char *)cmd,s);
	while(token != NULL)
	{
		segment_ptr[i] = token;
		#ifdef debug_p
		printf("%s\r\n",segment_ptr[i]);
		pack_printf((u8 *)segment_ptr[i],strlen(segment_ptr[i]));
		pack_printf((u8 *)"\r\n",2);
		#endif
		i++;
		token = strtok(NULL,s);
	}
	MsgDeal((u8 *)segment_ptr,1);
	return true;
}















