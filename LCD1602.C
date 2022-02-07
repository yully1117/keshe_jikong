#include "STC15Fxxxx.h"
#include "LCD1602.h"
 
//#include "fuzzy_pid.h"
#define uchar unsigned char
#define uint unsigned int
uchar table[8];
uchar code table1[]="Set temp:";
uchar code table2[]="Measure temp:"; 

//1ms延时程序
void lcd_delay(uint j)
{
	uint i=250;
   //uint i=250*8;
	for(;j>0;j--)
	{
		while(--i);
		i=249;
		while(--i);
		i=250;
	}
}
void write_com(uchar com)
{
   lcd_delay(3);
	e=0;
	rs=0;
	rw=0;
	out=com;
	e=1;
	_nop_();
	e=0;
	lcd_delay(1);
}


void write_data(uchar date)
{
   lcd_delay(3);
	e=0;
	rs=1;
	rw=0;
	out=date;
	e=1;
	_nop_();
	e=0;
	lcd_delay(1);	
}

void lcd_init()
{
    write_com(0x38);//8位总线,双行显示，5X7的点阵字符
	write_com(0x0C);//开整体显示,光标关，无黑块
	write_com(0x06);//光标右移
	write_com(0x01);//清屏
	lcd_delay(1);
 }

 void display_init()
{
   uchar num;
   write_com(0x80); 
   for(num=0;num<9;num++)
   {
    write_data(table1[num]);
    lcd_delay(3);
   }

   write_com(0x80+0x40);
   for(num=0;num<13;num++)
   {
    write_data(table2[num]);
    lcd_delay(3);
   }
}
  void display(float x1,float x2)
{
   uchar num;
   int num1,num2;
   num1=round(x1);
   num2=round(x2);
   //table[0]=num1/1000;
   table[0]=num1%1000/100;
   table[1]=num1%100/10;
   table[2]=num1%10;

   //table[4]=num2/1000;
   table[3]=num2%1000/100;
   table[4]=num2%100/10;
   table[5]=num2%10;
   
   write_com(0x80+13); 
   for(num=0;num<3;num++)
   {
    write_data(table[num]+0x30);
    lcd_delay(3);
   }

   write_com(0x80+0x40+13);
   for(;num<6;num++)
   {
    write_data(table[num]+0x30);
    lcd_delay(3);
   }
}

int round(float x)
{
   int x1;
   x1=(int)x;
     if(x>0)
        {if((x-x1)>=0.5) x1=x1+1;}
     if(x<0)
        {if((x1-x)>=0.5) x1=x1-1;}
   return x1;
} 