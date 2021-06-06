#include <REGX52.H>
//中断一般用来处理不确定的因素，如按键、发来的不定时信号等。
//定时器0初始化，1毫秒
void Timer0Init(void)		//1毫秒@12.000MHz
{

	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;          //中断允许控制     	  （允许T0中断）
	EA=1;           //						  （开放中断）
	PT0=0;			//优先级控制             （低级的优先级）（默认也是低级）
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

//电机的三级调速

/*
unsigned char Counter,Compare,Key,Speed,i;		  //调节占空比只要调节Compare的值就可以
sbit Motor=P1^0;

void main()
{
	Timer0Init();

	while(1)
	{
		Key=matrixkey();
		if(Key==1)
		{
			Speed++;
			if(Speed==4)
				Speed=0;
			if(Speed==0){Compare=0;}
			if(Speed==1){Compare=50;}
			if(Speed==2){Compare=70;}
			if(Speed==3){Compare=100;}
		}
		Nixie(1,Speed);	
	} 
	
}
//100微秒的定时器0
void Timer0_Routine() interrupt 1	//调用T0，溢出后接下来做什么(中断子程序)
{
	TL0 = 0x9C;		//设置定时初始值
	TH0 = 0xFF;		//设置定时初始值
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












*/