#include <REGX52.H>
void timing_init()
{
	TMOD=0x01;
	TL0 = 0x00;		//���ö�ʱ��ֵ:50ms
	TH0 = 0x4C;
	EA=1;
	ET0=1;
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}
