#include <STC89C5xRC.H>


/**
  * @brief  ��ʱ��0��ʼ����1����@12.000MHz
  * @param  ��
  * @retval ��
  */
void Timer0_Init(void)
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0;		//���ö�ʱ��ֵ
	TH0 = 0;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 0;		//��ʱ��0����ʱ
}

/**
  * @brief  ��ʱ��0���ü�����ֵ
  * @param  Value��Ҫ���õļ�����ֵ����Χ��0~65535
  * @retval ��
  */
void Timer0_SetCounter(unsigned int Value)
{
	TH0=Value/256;
	TL0=Value%256;
}

/**
  * @brief  ��ʱ��0��ȡ������ֵ
  * @param  ��
  * @retval ������ֵ����Χ��0~65535
  */
unsigned int Timer0_GetCounter(void)
{
	return (TH0<<8)|TL0;
}

/**
  * @brief  ��ʱ��0����ֹͣ����
  * @param  Flag ����ֹͣ��־��1Ϊ������0Ϊֹͣ
  * @retval ��
  */
void Timer0_Run(unsigned char Flag)
{
	TR0=Flag;
}

void Timer1_Init(void)
{
	TMOD &= 0x0f;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0x18;		//���ö�ʱ��ֵ
	TH1 = 0xFC;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF0��־
	TR1 = 1;		//��ʱ��0��ʼ��ʱ
	ET1=1;
	EA=1;
	PT1=0;
}

//void Timer1_Init(void)
//{
//			//���ö�ʱ��ģʽ
//	TMOD |= 0x10;
//	TMOD &= 0x0f;		//���ö�ʱ��ģʽ
//	TL1 = 0x50;		//���ö�ʱ��ֵ
//	TH1 = 0xFB;		//���ö�ʱ��ֵ
//	TF1 = 0;		//���TF0��־
//	TR1 = 1;		//��ʱ��0��ʼ��ʱ
//	ET1=1;
//	EA=1;
//	PT1=0;
//}

/*��ʱ���жϺ���ģ��
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		
	}
}
*/
