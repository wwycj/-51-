#include <STC89C5xRC.H>
#include "delay.h"
sbit key1=P3^7;
sbit key2=P3^3;
sbit key3=P3^4;
sbit key4=P3^5;



unsigned char Key_KeyNumber;

/**
  * @brief  ��ȡ��������
  * @param  ��
  * @retval ���°����ļ��룬��Χ��0,1~4,0��ʾ�ް�������
  */
unsigned char KeyNum(void)
{
	unsigned char Temp=0;
	Temp=Key_KeyNumber;
	Key_KeyNumber=0;
	return Temp;
}

/**
  * @brief  ��ȡ��ǰ������״̬�������������ּ��
  * @param  ��
  * @retval ���°����ļ��룬��Χ��0,1~4,0��ʾ�ް�������
  */
unsigned char Key_GetState()
{
	unsigned char KeyNumber=0;
	
	if(key1==0){KeyNumber=1;}
	if(key2==0){KeyNumber=2;}
	if(key3==0){KeyNumber=3;}
	if(key4==0){KeyNumber=4;}
	
	return KeyNumber;
}

/**
  * @brief  �����������������ж��е���
  * @param  ��
  * @retval ��
  */
void Key_Loop(void)
{
	static unsigned char NowState,LastState;
	LastState=NowState;				//����״̬����
	NowState=Key_GetState();		//��ȡ��ǰ����״̬
	//����ϸ�ʱ��㰴�����£����ʱ���δ���£���������˲�䣬�Դ˱������������ּ��
	if(LastState==1 && NowState==0)
	{
		Key_KeyNumber=1;
	}
	if(LastState==2 && NowState==0)
	{
		Key_KeyNumber=2;
	}
	if(LastState==3 && NowState==0)
	{
		Key_KeyNumber=3;
	}
	if(LastState==4 && NowState==0)
	{
		Key_KeyNumber=4;
	}
}


