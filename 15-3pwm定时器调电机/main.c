#include <REGX52.H>
//#include "delay.H"
#include "TIMER0.H"
#include "NIXIE.H"
#include "matrixkey.H"   
//产生pwm的方法
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







