/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: WifiCon.h
Description		: 主要实现wifi连接功能相关定义
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-09
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _wificon_h
#define _wificon_h
#include "arm_base_define.h"
#include "Wifi.h"

typedef enum
{
	OK_e=0,//					"OK"
	START_e,//				">"
	AT_e,//					"AT\r\n"//检测wifi模块是否在线
	ATE0_e,//				"ATE0\r\n"//关闭回显
	ATE1_e,//				"ATE1\r\n"//开启回显
	WIFIMODE_e,//			"AT+CWMODE=3\r\n"//设置为STA+AP模式
	RST_e,//					"AT+RST\r\n"//设置模式进行重启生效
	CWJAP_e,//				"AT+CWJAP=\"LINK_001\",\"0123456789\"\r\n"//连接wifi
	CIPMUX_e,//				"AT+CIPMUX=0\r\n"//设置但连接，透传模式只能设置但连接
	CIPMODE1_e,//			"AT+CIPMODE=1\r\n"//设置透传模式
	CIPSTART_e,//			"AT+CIPSTART=\"TCP\",\"45.77.12.32\",9090\r\n"//连接远端
	CIPSEND_e,//			"AT+CIPSEND\r\n"//进入透传模式,返回>
	BACKAT_e,//				"+++"//返回指令模式
	CLOSESER_e,//			"AT+CIPCLOSE\r\n"//断开与服务器的连接
	EXITLINK_e,//			"AT+CWQAP\r\n"//退出与路由器的连接
}_STATUS;
#pragma pack(push,1)
typedef struct{
	u8 wait;
	u8 count;
	u8 flag;
}_CONNECT_s;
#pragma pack(pop)

void cmd_wait_time(u8 num);
void wifi_con(void);

#endif
