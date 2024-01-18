#include <STC89C5xRC.H>


/**
  * @brief  定时器0初始化，1毫秒@12.000MHz
  * @param  无
  * @retval 无
  */
void Timer0_Init(void)
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0;		//设置定时初值
	TH0 = 0;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0不计时
}

/**
  * @brief  定时器0设置计数器值
  * @param  Value，要设置的计数器值，范围：0~65535
  * @retval 无
  */
void Timer0_SetCounter(unsigned int Value)
{
	TH0=Value/256;
	TL0=Value%256;
}

/**
  * @brief  定时器0获取计数器值
  * @param  无
  * @retval 计数器值，范围：0~65535
  */
unsigned int Timer0_GetCounter(void)
{
	return (TH0<<8)|TL0;
}

/**
  * @brief  定时器0启动停止控制
  * @param  Flag 启动停止标志，1为启动，0为停止
  * @retval 无
  */
void Timer0_Run(unsigned char Flag)
{
	TR0=Flag;
}

void Timer1_Init(void)
{
	TMOD &= 0x0f;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x18;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	TF1 = 0;		//清除TF0标志
	TR1 = 1;		//定时器0开始计时
	ET1=1;
	EA=1;
	PT1=0;
}

//void Timer1_Init(void)
//{
//			//设置定时器模式
//	TMOD |= 0x10;
//	TMOD &= 0x0f;		//设置定时器模式
//	TL1 = 0x50;		//设置定时初值
//	TH1 = 0xFB;		//设置定时初值
//	TF1 = 0;		//清除TF0标志
//	TR1 = 1;		//定时器0开始计时
//	ET1=1;
//	EA=1;
//	PT1=0;
//}

/*定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		
	}
}
*/
