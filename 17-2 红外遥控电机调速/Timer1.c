#include <REGX52.H>

//定时器0初始化，100微秒
void Timer1_Init(void)		//100微秒@12.000MHz
{

	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x9C;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	TF1 = 0;		//清除TF0标志
	TR1 = 1;		//定时器0开始计时
	ET1=1;          //中断允许控制     	  （允许T0中断）
	EA=1;           //						  （开放中断）
	PT0=0;			//优先级控制             （低级的优先级）（默认也是低级）
}




/*定时器中断函数模板（灯的一秒闪烁）
void Timer0_Routine() interrupt 3	//调用T0，溢出后接下来做什么(中断子程序)
{
	static unsigned int T0count;    //无符号int为0~65535
	TL1 = 0x9C;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	T0count++;
	if(T0count>=1000)
	{
		T0count=0;
		P2_0=~P2_0;	
	}

}
*/