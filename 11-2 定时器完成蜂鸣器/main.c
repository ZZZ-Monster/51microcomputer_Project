#include <REGX52.H>
#include "Timer0.H"
sbit Buzzer=P1^5;



void main()
{
	Timer0Init();
	while(1)
	{
		
	}
} 


//每1ms来来一次中断
void Timer0_Routine() interrupt 1	//调用T0，溢出后接下来做什么(中断子程序)
{
	TL0 = 0x18;			//重新给初值。让它再从64535开始	
	TH0 = 0xFC;
	Buzzer=~Buzzer;			 //产生500Hz的反转频率
}