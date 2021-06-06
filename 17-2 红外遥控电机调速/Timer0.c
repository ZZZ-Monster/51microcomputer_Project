#include <REGX52.H>
//中断一般用来处理不确定的因素，如按键、发来的不定时信号等。
//定时器0初始化，1毫秒
void Timer0Init(void)		//1毫秒@12.000MHz
{

	TMOD &= 0xF0;	//设置定时器模式
	TMOD |= 0x01;	//设置定时器模式
	TL0 = 0;		//设置定时初始值0
	TH0 = 0;		//设置定时初始值0
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0不开始计时
}

void Timer0_SetCounter(unsigned int Value)	 //给定时器初值
{
	TH0=Value/256;
	TL0=Value%256;
}

unsigned int Timer0_GetCounter(void)	  //计时时间
{
	return (TH0<<8)|TL0;
}


void Timer0_Run(unsigned int Flag)		 //是否允许开始计时
{
	TR0 = Flag;	
}






//1秒=1000毫秒ms=1000 000微妙μs

/*定时器中断函数模板（灯的一秒闪烁）
void Timer0_Routine() interrupt 1	//调用T0，溢出后接下来做什么(中断子程序)
{
	static unsigned int T0count;    //无符号int为0~65535
	TL0 = 0x18;			//重新给初值。让它再从64535开始	
	TH0 = 0xFC;
	T0count++;
	if(T0count>=1000)
	{
		T0count=0;
		P2_0=~P2_0;	
	}

}
*/

