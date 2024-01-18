#include <STC89C5xRC.H>
#include <intrins.h>
sbit LCD_RS=P2^0;
sbit LCD_RW=P2^1;
sbit LCD_E=P2^2;

#define LCD_DB P0
void delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}


void LCD_Writecmd(unsigned char Command)//为什么要把使能端开启后再关闭
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_DB=Command;
	LCD_E=1;
	delay1ms();	
	LCD_E=0;
	delay1ms();	
}
void LCD_WriteData(unsigned char Data)//为什么要把使能端开启后再关闭
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_DB=Data;
	LCD_E=1;
	delay1ms();	
	LCD_E=0;
	delay1ms();	
}
void LCD_SetCursor(unsigned char line,unsigned char column)
{
	if(line==1){LCD_Writecmd(0x80|(column-1));}
	else if(line==2){LCD_Writecmd(0x80|(column-1+0x40));}
}
void LCD_Init()
{
	LCD_Writecmd(0x38);//八位数据接口，两行显示，5*7点阵
	LCD_Writecmd(0x0c);//显示开，光标关，闪烁关
	LCD_Writecmd(0x06);//数据读写操作后，光标自动加一，画面不动
	LCD_Writecmd(0x01);//光标复位，清屏
}
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}
void LCD_Showstring(unsigned char line,unsigned char column,char *string)
{
	unsigned char i;
	LCD_SetCursor(line,column);
	for(i=0;string[i]!='\0';i++)
	{
		LCD_WriteData(string[i]);
	}

}
int LCD_Pow(int x,int y)
{
	unsigned char i;
	int result=1;
	for(i=0;i<y;i++)
	{
		result*=x;}
	return result;
}
void LCD_shownum(unsigned char line,unsigned char column,unsigned int Number,unsigned char length)
{
	unsigned char i;
	LCD_SetCursor(line,column);
	for(i=length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(10,i-1)%10+'0');
	}

}
void LCD_showsignednum(unsigned char line,unsigned char column,int Number,unsigned char length)
{
	unsigned char i;
//	LCD_SetCursor(line,column);
//	if(Number<0)
//	{
//		LCD_WriteData('-');
//		for(i=length;i>0;i--)
//		{
//		LCD_WriteData((-Number)/LCD_Pow(10,i-1)%10+'0');//这里直接用-可能会有点问题
//		}
//	}
//	if(Number>=0)
//	{
//		LCD_WriteData('+');
//		for(i=length;i>0;i--)
//		{
//		LCD_WriteData(Number/LCD_Pow(10,i-1)%10+'0');
//		}
//	}
	unsigned int Number1;
	LCD_SetCursor(line,column);
	if(Number>=0)
	{
		LCD_WriteData('+');
		Number1=Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1=-Number;
	}
	for(i=length;i>0;i--)
	{
		LCD_WriteData(Number1/LCD_Pow(10,i-1)%10+'0');
	}
	
}
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i,SingleNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData(SingleNumber+'0');
		}
		else
		{
			LCD_WriteData(SingleNumber-10+'A');
		}
	}
}
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(2,i-1)%2+'0');
	}
}
