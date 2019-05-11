/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Analysis.c
Description: ���������ض���ͷ�ļ�
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-07
Modify	   : 
Modify Time: 
******************************************************************************/
#ifndef _analysis_h
#define _analysis_h
#include "fifo.h"

#define			HEAD			0x7e//��Ϣͷ��־
#define			Soft_ver		0x01//����汾
//#define			Target			0x2a//��ʾ��ǩ��Ϣ
//��������
//#define			settype			0x1a//������������
//#define			seltype			0x2a//��ѯ��������
//#define			respond			0x3a//��Ӧ��������
//#define			selinfo			0xc0//��ѯ��ǩ��Ϣ
////radio����2.4g rf�ź�������ã���������
//#define			setfer			0xa0//����Ƶ��
//#define			setmac			0xa1//���õ�ַ��
//#define			setspeed		0xa2//�����ٶ�
//#define			setch			0xa3//����ͨ��
////radio�����������
//#define			setsendch		0xb0//���÷���ͨ��
//#define			setsendpow		0xb1//���÷��͹���

typedef enum {				//��Ƴ�������Ҫ��Ϊ�˺���ά������
	settype=0x1a,			//������������
	seltype,				//��ѯ��������
	respond,				//��Ӧ������������
	selinfo,				//��ѯ��ǩ��Ϣ������������
	setfer,					//����Ƶ����������
	setmac,					//���õ�ַ����������
	setspeed=0x20,				//�����ٶ���������
	setdatalen,					//�������ݳ�����������
	seldata,				//��ѯ��ǩ��Ϣ��������
	selrf,					//��ѯƵ����������
	setsendch,				//���÷���ͨ����������
	setsendpow,				//���÷��͹�����������
	target,					//��ʾ��ǩ��Ϣ��������

}_STATUS;


#pragma pack(push,1)
typedef struct{
//�������ṹ����Ҫ��Ϊ���Ժ��������㣬������������ͺ���������
	u8 head;			//����ͷ
	u8 len;				//���ݳ���
	u8 softver;			//����汾
	u8 cmdtype;			//��������
	u8 datatype;		//��������
	u8 buf[240];		//�����������֧��240byte
}_Pack;
#pragma pack(pop)


u8 Analysis_function(u8 *cmdtype,u8 *datatype,u8 *outdata,u8 *indata,u8 *len);
u8 Unpack(u8 cmdtype,u8 datatype,u8 *data,u8 datalen);
u8 Unpack_target(u8 ch,u8 *data,u8 datalen);
u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data);



#endif











