#include <REGX52.H>

void Timer0_Init()	
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x33;		//设置定时初始值
	TH0 = 0xFF;		//设置定时初始值
	ET0=1;          //打开定时器0的中断
	TR0 = 1;		//定时器0开始计时
	EA=1;           //开总中断
}
