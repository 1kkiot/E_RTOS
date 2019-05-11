#include "config.h"

#if 0
const u8 PROTOCOL[] __attribute__((at(AIR_LIB_ADDR))) =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,		//Ʒ����
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,		//�ͺ�
	0x00,																																								//У��ģʽ	0��CRC16	1���ۼӺ�
	0x01,																																								//CRC��������������	0��С��		1�����
	0x00,0x01,0x01,0x03,0x01,																														//���ػ���ģʽ���¶ȣ����٣�ɨ��ִ����һ�������5��
	//��һ������
	0x03,0x01,0x0A,0x00,0x00,0x00,																											//֡ͷ��־
	0x03,0x01,0x01,0x00,0x00,0x00,																											//�յ���ַ
	0x03,0x01,0x03,0x00,0x00,0x00,																											//���ܴ���
	0x00,0x00,0x00,0x00,0x00,0x00,																											//���ڻ���ʼ��ַ
	0x00,0x00,0x00,0x00,0x00,0x00,																											//���ڻ��Ĵ�������
	0x03,0x01,0x05,0x00,0x00,0x00,																											//���ݴ�С
	0x03,0x01,0x00,0x00,0x01,0x01,																											//���ػ�����
	0x00,0x01,0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x04,0x04,												//�յ�ģʽ����0:�Զ���
	0x00,0x01,																																					//�¶�����
	0x00,0x01,0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x00,0x00,												//��������
	0x00,0x01,0x00,0x00,0x01,0x01,																											//ɨ������
	0x01,0x02,																																					//У��
	0x01,0x01,0x05,0x00,0x00,0x00,																											//������־
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,										//˳��
	//�ڶ�������
	0x03,0x01,0x0A,0x00,0x00,0x00,																											//֡ͷ��־
	0x03,0x01,0x01,0x00,0x00,0x00,																											//�յ���ַ
	0x03,0x01,0x03,0x00,0x00,0x00,																											//���ܴ���
	0x00,0x00,0x00,0x00,0x00,0x00,																											//���ڻ���ʼ��ַ
	0x00,0x00,0x00,0x00,0x00,0x00,																											//���ڻ��Ĵ�������
	0x03,0x01,0x05,0x00,0x00,0x00,																											//���ݴ�С
	0x00,0x01,0x00,0x00,0x01,0x01,																											//���ػ�����
	0x03,0x01,0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x04,0x04,												//�յ�ģʽ����
	0x03,0x01,																																					//�¶�����
	0x00,0x01,0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x00,0x00,												//��������
	0x03,0x01,0x00,0x00,0x01,0x01,																											//ɨ������
	0x01,0x02,																																					//У��
	0x01,0x01,0x05,0x00,0x00,0x00,																											//������־
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,										//˳��
	//����������
	0x03,0x01,0x0A,0x00,0x00,0x00,																											//֡ͷ��־
	0x03,0x01,0x01,0x00,0x00,0x00,																											//�յ���ַ
	0x03,0x01,0x03,0x00,0x00,0x00,																											//���ܴ���
	0x00,0x00,0x00,0x00,0x00,0x00,																											//���ڻ���ʼ��ַ
	0x00,0x00,0x00,0x00,0x00,0x00,																											//���ڻ��Ĵ�������
	0x03,0x01,0x05,0x00,0x00,0x00,																											//���ݴ�С
	0x00,0x01,0x00,0x00,0x01,0x01,																											//���ػ�����
	0x00,0x01,0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x04,0x04,												//�յ�ģʽ����
	0x03,0x01,																																					//�¶�����
	0x00,0x01,0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x00,0x00,												//��������
	0x00,0x01,0x00,0x00,0x01,0x01,																											//ɨ������
	0x01,0x02,																																					//У��
	0x01,0x01,0x05,0x00,0x00,0x00,																											//������־
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,										//˳��
	//����������
	0x03,0x01,0x0A,0x00,0x00,0x00,																											//֡ͷ��־
	0x03,0x01,0x01,0x00,0x00,0x00,																											//�յ���ַ
	0x03,0x01,0x03,0x00,0x00,0x00,																											//���ܴ���
	0x00,0x00,0x00,0x00,0x00,0x00,																											//���ڻ���ʼ��ַ
	0x00,0x00,0x00,0x00,0x00,0x00,																											//���ڻ��Ĵ�������
	0x03,0x01,0x05,0x00,0x00,0x00,																											//���ݴ�С
	0x00,0x01,0x00,0x00,0x01,0x01,																											//���ػ�����
	0x00,0x01,0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x04,0x04,												//�յ�ģʽ����
	0x00,0x01,																																					//�¶�����
	0x03,0x01,0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x00,0x00,												//��������
	0x00,0x01,0x00,0x00,0x01,0x01,																											//ɨ������
	0x01,0x02,																																					//У��
	0x01,0x01,0x05,0x00,0x00,0x00,																											//������־
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,										//˳��
	//����������
	0x03,0x01,0x0A,0x00,0x00,0x00,																											//֡ͷ��־
	0x03,0x01,0x01,0x00,0x00,0x00,																											//�յ���ַ
	0x03,0x01,0x03,0x00,0x00,0x00,																											//���ܴ���
	0x00,0x00,0x00,0x00,0x00,0x00,																											//���ڻ���ʼ��ַ
	0x00,0x00,0x00,0x00,0x00,0x00,																											//���ڻ��Ĵ�������
	0x03,0x01,0x05,0x00,0x00,0x00,																											//���ݴ�С
	0x00,0x01,0x00,0x00,0x01,0x01,																											//���ػ�����
	0x00,0x01,0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x04,0x04,												//�յ�ģʽ����
	0x00,0x01,																																					//�¶�����
	0x03,0x01,0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x00,0x00,												//��������
	0x00,0x01,0x00,0x00,0x01,0x01,																											//ɨ������
	0x01,0x02,																																					//У��
	0x01,0x01,0x05,0x00,0x00,0x00,																											//������־
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,										//˳��
};
#endif