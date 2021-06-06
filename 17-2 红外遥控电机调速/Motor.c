#include <REGX52.H>
#include "TIMER1.H"

sbit Motor=P1^0;

unsigned char Counter,Compare;

void Motor_Init()
{
	Timer1_Init();
}


void Motor_SetSpeed(unsigned char Speed)
{
	Compare=Speed;
}





void Timer1_Routine() interrupt 3	//调用T0，溢出后接下来做什么(中断子程序)
{
	TL1 = 0x9C;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	Counter++;
	if(Counter>=100)
		Counter=0;
	if(Counter<Compare)
	{
		Motor=1;			  //给1转
	}
	else
	{
		Motor=0;
	}

}






