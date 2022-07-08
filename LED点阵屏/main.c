#include <REGX52.H>
#include "delay.h"
#include "timing.h"
#define unchar unsigned char
sbit SER=P3^4;
sbit RCK=P3^5;
sbit SRCK=P3^6;
unchar c=0;
unchar j=0;
unchar time;
unchar a[]={0x00,0x00,0x7F,0x08,0x08,0x7F,0x00,0x1E,0x21,0x29,0x29,0x11,0x00,0x7E,0x01,0x02,0x00,0x7E,
0x01,0x02,0x00,0x1E,0x21,0x21,0x1E,0x00,0x00,0x00,0x7D,0x00,0x00,0x7F,0x08,0x08,
0x7F,0x00,0x1E};                 //要滚动的文字按一列一列显示排列

void timing()interrupt 1
{
	TF0 = 0;
	TL0 = 0x00;		//设置定时初值:50ms
	TH0 = 0x4C;
	time++;
	if(time>=20)            //1秒中断
	{
		time=0;
		c++;
		if(c>28)        //c控制第j列显示a【c】
		{
			c=0;
		}
	}
	
}

void _74HC595_writebyte(unchar byte)//74595写入数据
{
	
	char i;
	for(i=0;i<8;i++)
	{
		SER=byte&(0x80>>i);         //依次读取byte的最高位到最低位
		SRCK=1;                     //给一个上升沿
		delay_ms(1);
		SRCK=0;                     //清零为下一次读数做准备
	}
	RCK=1;                          //八个二进制位读完给一个上升沿并位输出
	delay_ms(1);
	RCK=0;
}

void Column_display(unchar column,unchar byte)
{
	P0=~(0x80>>(column-1));          //一列一列扫描显示
	_74HC595_writebyte(byte);
	P0=0xff;
	delay_ms(1);
}
	

void main()
{
	
	timing_init();            //定时中断初始化
	RCK=0;
	SRCK=0;
	while(1)
	{
		
		for(j=1;j<=8;j++) //8x8点阵屏依次按列显示
		{
			Column_display(j,a[j+c-1]);
			P0=0xff;
			delay_ms(1);
		}
		
	}
	
}
