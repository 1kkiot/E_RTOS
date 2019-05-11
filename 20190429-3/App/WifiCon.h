/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: WifiCon.h
Description		: ��Ҫʵ��wifi���ӹ�����ض���
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
	AT_e,//					"AT\r\n"//���wifiģ���Ƿ�����
	ATE0_e,//				"ATE0\r\n"//�رջ���
	ATE1_e,//				"ATE1\r\n"//��������
	WIFIMODE_e,//			"AT+CWMODE=3\r\n"//����ΪSTA+APģʽ
	RST_e,//					"AT+RST\r\n"//����ģʽ����������Ч
	CWJAP_e,//				"AT+CWJAP=\"LINK_001\",\"0123456789\"\r\n"//����wifi
	CIPMUX_e,//				"AT+CIPMUX=0\r\n"//���õ����ӣ�͸��ģʽֻ�����õ�����
	CIPMODE1_e,//			"AT+CIPMODE=1\r\n"//����͸��ģʽ
	CIPSTART_e,//			"AT+CIPSTART=\"TCP\",\"45.77.12.32\",9090\r\n"//����Զ��
	CIPSEND_e,//			"AT+CIPSEND\r\n"//����͸��ģʽ,����>
	BACKAT_e,//				"+++"//����ָ��ģʽ
	CLOSESER_e,//			"AT+CIPCLOSE\r\n"//�Ͽ��������������
	EXITLINK_e,//			"AT+CWQAP\r\n"//�˳���·����������
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
