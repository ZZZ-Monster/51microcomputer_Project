#include <REGX52.H>
#include "delay.H"
#include "TIMER0.H"
//#include "NIXIE.H"
//#include "matrixkey.H"   
//产生pwm的方法
unsigned char Counter,Compare,i;		  //调节占空比只要调节Compare的值就可以
sbit DA=P2^1;

void main()
{
	Timer0Init();

	while(1)
	{

		 for(i=0;i<100;i++)
		 {
		 	 Compare=i;
			 delay(10);
		 }
		 for(i=100;i>0;i--)
		 {
		 	 Compare=i;
			 delay(10);
		 }
	
	
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
		DA=1;			  
	}
	else
	{
		DA=0;
	}

}







