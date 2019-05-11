/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Wifi.h
Description		: ��Ҫʵ��wifiģ�����ָ���
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-04
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _wifi_h
#define _wifi_h
#include "arm_base_define.h"
#include "Memory.h"
#include "Debugprintf.h"

#define			OK					"OK"
#define			START				">"
#define			AT					"AT\r\n"//���wifiģ���Ƿ�����
#define			ATE0				"ATE0\r\n"//�رջ���
#define			ATE1				"ATE1\r\n"//��������
#define			WIFIMODE			"AT+CWMODE=3\r\n"//����ΪSTA+APģʽ
#define			RST					"AT+RST\r\n"//����ģʽ����������Ч
#define			CWJAP				"AT+CWJAP=\"LINK_001\",\"0123456789\"\r\n"//����wifi
#define			CIPMUX				"AT+CIPMUX=0\r\n"//���õ����ӣ�͸��ģʽֻ�����õ�����
#define			CIPMODE1			"AT+CIPMODE=1\r\n"//����͸��ģʽ
#define			CIPSTART			"AT+CIPSTART=\"TCP\",\"192.168.1.101\",9090\r\n"//����Զ��
//#define			CIPSTART			"AT+CIPSTART=\"TCP\",\"45.77.12.32\",9090\r\n"//����Զ��
#define			CIPSEND				"AT+CIPSEND\r\n"//����͸��ģʽ,����>

#define			BACKAT				"+++"//����ָ��ģʽ
#define			CLOSESER			"AT+CIPCLOSE\r\n"//�Ͽ��������������
#define			EXITLINK			"AT+CWQAP\r\n"//�˳���·����������

#pragma pack(push,1)
typedef struct{
	u8 connect;
	u8 send;
	u8 respond;//����Ӧ��Ϣ
}_WIFI_t;
#pragma pack(pop)

extern _WIFI_t Wifi_t;

u8 *check_cmd(u8 *cmd);
u8 wifi_mode_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
void wifi_reset(void);
void wifi_init(void);


#endif
