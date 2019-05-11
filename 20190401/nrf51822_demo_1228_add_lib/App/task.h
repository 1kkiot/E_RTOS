/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : task.h
Description: ҵ���߼����ͷ�ļ�
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _task_h
#define _task_h
#include "Thread.h"
//�����ֽڳ���Ϊһ���ֽ���Ҫ����Ϊͨ�����ݲ�̫��
#define			HEAD			0x7e
#define			Soft_ver		0x01//����汾
//#define			new_68
//#define			settype			0x1a//������������
//#define			seltype			0x2a//��ѯ��������
//#define			respond			0x3a//��Ӧ��������
//#define			setfer			0xa0//����Ƶ��
//#define			setmac			0xa1//���õ�ַ��
//#define			setspeed		0xa2//�����ٶ�
//#define			setch			0xa3//����ͨ��
//#define			setsendch		0xa6//���÷���ͨ��
//#define			setsendpow		0xa7//���÷��͹���
//#define			seldata			0xa4//��ѯ����
//#define			selrf			0xa5//��ѯƵ��

//Э������������ͺ�����������Ҫ��Ϊ�˺�����չ����
typedef enum{				//��Ƴ�������Ҫ��Ϊ�˺���ά��������ʹ�ú궨�岻���ں���ά������
	settype=0x1a,			//������������
	seltype,				//��ѯ��������
	respond,				//��Ӧ������������
	selinfo,				//��ѯ��ǩ��Ϣ��������
	setfer,					//����Ƶ����������
	setmac,					//���õ�ַ����������
	setspeed=0x20,			//�����ٶ���������
	setdatalen,				//�������ݳ�����������
	seldata,				//��ѯ��ǩ��Ϣ��������
	selrf,					//��ѯƵ����������
	setsendch,				//���÷���ͨ����������
	setsendpow,				//���÷��͹�����������
	target,					//��ʾ��ǩ��Ϣ��������
	reset,					//��ʾ��������
}_STATUS;
#pragma	pack(push,1)
typedef struct{
	u8 num;//ͳ��spi���ʹ���
	u8 count;
	u8 flag;
}_FLAG;
typedef struct{
	u8 mbuf[5];
}_Mac;
typedef struct{
	u8 head;
	u8 len;
	u8 softver;
	u8 cmdtype;
	u8 datatype;
	u8 dbuff[240];//�����������֧��240byte
}_CMD;
typedef struct{
	u8 fbuff[255];
	u8 bbuff[255];
}_DATA;
#pragma	pack(pop)
extern _DATA		dtemp;
extern _CMD			ctemp;
extern _FLAG		Send;


void rf_function(void);
void main_task(void);
void spi_function(void);
void radio_send(void);
u8 Escape(u8 *indata,u8 *outdata,u8 *len);
#endif




