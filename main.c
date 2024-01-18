#include <STC89C5xRC.H>
#include <intrins.h>
#include "delay.h"
#include "LCD1602.h"
#include "DS18b20.h"
#include "key.h"
#include "AT24C02.h"
#include "IR.h"
#include "timer.h"
#include "onewire.h"
sbit motor=P1^0;
sbit mode=P1^6;
	
unsigned char Counter,Compare;
float A,T;
char Thigh,Tlow;
char flag;
unsigned char Key;
unsigned char Command;


void main()
{	
	IR_Init();
	mode=0;
	Readtemp_convert();	//�ϵ���ת��һ���¶ȣ���ֹ��һ�ζ����ݴ���
	delay(1000);
	Thigh=AT24C02_ReadByte(0);	//��ȡ�¶���ֵ����
	Tlow=AT24C02_ReadByte(1);
	LCD_Init();
//	LCD_Showstring(1,1,"T:");
//	LCD_Showstring(2,1,"TH:");
//	LCD_Showstring(2,8,"TL:");
	if(Thigh>125||Tlow<-55||Thigh<=Tlow)
	{Thigh=20;Tlow=15;}

	Timer1_Init();

	
	while(1)
	{
		
		if(IR_GetCommand()==IR_POWER){flag=1;}
		if(IR_GetCommand()==IR_START_STOP){flag=2;}
		if(flag==1){
		TR1=1;	
	
		LCD_Showstring(1,1,"T:");
		LCD_Showstring(2,1,"TH:");
		LCD_Showstring(2,8,"TL:");
		Key=KeyNum();
		
//	    temp_convert();
		A=Readtemp_convert();
		
		if(A<0)
		{
			LCD_ShowChar(1,3,'-');
			T=-A;
		}
		else if(A>=0)
		{
			LCD_ShowChar(1,3,'+');
			T=A;
		}
		LCD_shownum(1,4,T,3);		//��ʾ�¶���������
		LCD_ShowChar(1,7,'.');		//��ʾС����
		LCD_shownum(1,8,(unsigned long)(T*10000)%10000,4);//��ʾ�¶�С������
		AT24C02_WriteByte(0,Thigh);		//д�뵽At24C02�б���
		delay(5);
		AT24C02_WriteByte(1,Tlow);
		delay(5);
		if(Key || IR_GetDataFlag() || IR_GetRepeatFlag())
		{
			//��ȡң������ַ��
			Command=IR_GetCommand();
			if(Key==1 ||Command==IR_VOL_ADD )
				{
				if(Thigh<125)
					{Thigh++;
					LCD_Showstring(2,15,"  ");}
				else
					{if(Thigh==125)
						LCD_Showstring(2,15,"MX");}
				}
			if(Key==2||Command==IR_VOL_MINUS )
				{
					Thigh--;
					if(Thigh<=Tlow){Thigh++;}
				}
			if(Key==3 ||Command==IR_USD )
				{
				
					Tlow++;
					if(Tlow>=Thigh)
						Tlow--;
				}
			if(Key==4 ||Command==IR_RPT )
				{
				if(Tlow>-55)
					{Tlow--;
					LCD_Showstring(2,15,"  ");}
				else
					{if(Tlow==-55)
					LCD_Showstring(2,15,"MI");}
				}
			
		}
		
		if(IR_GetCommand()==IR_MODE){mode=1;}
		if(IR_GetCommand()==IR_MUTE){mode=0;}
		if(mode==0){
		LCD_Showstring(2,15,"  ");
		if(T>Thigh ){LCD_Showstring(1,13,"HIGH");Compare=100;}
		else if(T<Tlow){LCD_Showstring(1,13,"NO  ");Compare=0;}
		else if(T<Thigh&&T>Tlow){LCD_Showstring(1,13,"LOW ");Compare=50;}	}
		if(mode==1)
		{
			LCD_Showstring(2,15,"IR");
		if(Command==IR_4 ){LCD_Showstring(1,13,"   4");Compare=100;}
		else if(Command==IR_3){LCD_Showstring(1,13,"   3");Compare=75;}
		else if(Command==IR_2){LCD_Showstring(1,13,"   2");Compare=50;}
		else if(Command==IR_1){LCD_Showstring(1,13,"   1");Compare=25;}
		else if(Command==IR_0){LCD_Showstring(1,13,"   0");Compare=0;}
		}
		LCD_showsignednum(2,4,Thigh,3);
		LCD_showsignednum(2,11,Tlow,3);
	}
		else if(flag==2)
		{
		LCD_Showstring(1,1,"                ");
		LCD_Showstring(2,1,"                ");
		TR1=0;
		
		}
	
}

}
//void Timer0_Routine() interrupt 1
//{
//	static unsigned int T0Count;
//	TL0 = 0x18;		//���ö�ʱ��ֵ��1ms��
//	TH0 = 0xFC;		//���ö�ʱ��ֵ
//	T0Count++;
//	if(T0Count>=20)
//	{
//		T0Count=0;
//		Key_Loop();	//ÿ20ms����һ�ΰ�����������
//	}
//}
//void Timer1_Routine() interrupt 3
//{
//	TL1 = 0x50;		//���ö�ʱ��ֵ
//	TH1 = 0xFB;		//���ö�ʱ��ֵ
//	Counter++;
//	Counter%=100;	//����ֵ�仯��Χ������0~99
//	if(Counter<Compare)	//����ֵС�ڱȽ�ֵ
//	{
//		motor=1;		//���1
//	}
//	else				//����ֵ���ڱȽ�ֵ
//	{
//		motor=0;		//���0
//	}
//}
void Timer1_Routine() interrupt 3
{
	static unsigned int T1Count;
	TL1 = 0xA4;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ100us
	T1Count++;
	Counter++;
	Counter%=100;	//����ֵ�仯��Χ������0~99
	if(T1Count>=200)
	{
		T1Count=0;
		Key_Loop();	//ÿ20ms����һ�ΰ�����������
	}
	
	if(Counter<Compare)	//����ֵС�ڱȽ�ֵ
	{
		motor=1;		//���1
	}
	else				//����ֵ���ڱȽ�ֵ
	{
		motor=0;		//���0
	}
}
