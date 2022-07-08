#include <REGX52.H>
void timing_init()
{
	TMOD=0x01;
	TL0 = 0x00;		//设置定时初值:50ms
	TH0 = 0x4C;
	EA=1;
	ET0=1;
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}
