/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : setting.h
Description: �������ͷ�ļ�
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-23
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _setting_h
#define _setting_h
#include "base.h"



//0x0000-0x31fff----->�������г���
//0x3200-0x40000----->���ڱ�������
//200k��ʼ---256k����
#define			setferadd			((0xc8+0)*1024)//����Ƶ��
#define			setmacadd			((0xc8+1)*1024)//���õ�ַ��
#define			setspeedadd			((0xc8+2)*1024)//�����ٶ�
#define			setdatalenadd		((0xc8+3)*1024)//����ͨ��

#define			setsendchadd		((0xc8+4)*1024)//���÷���ͨ��
#define			setsendpowadd		((0xc8+5)*1024)//���÷��͹���



u8 set_fun(u8 datatype,u8 *data);
u8 sel_fun(u8 datatype,u8 *data);
u8 set_fer(u8 *data);
u8 set_mac(u8 *data);
u8 set_speed(u8 *data);
u8 set_datalen(u8 *data);
u8 sel_data(u8 *data);





#endif















