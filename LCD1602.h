#ifndef __LCD1602_H__
#define __LCD1602_H__

//�û����ú�����
void LCD_Init();
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
void LCD_Showstring(unsigned char Line,unsigned char Column,char *String);
void LCD_shownum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_showsignednum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

#endif
