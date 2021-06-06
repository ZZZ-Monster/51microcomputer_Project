#include <REGX52.H>
//#include "delay.H" 

sbit LED=P2^0;

void del(unsigned int t)		 //快延时
{
	while(t--);
}

void main()
{	unsigned char time,z;    //光定义time会闪的非常快，再定义一个i用来延缓变化		
	while(1)
	{
		for(time=0;time<100;time++)
		{
			for(z=0;z<20;z++)
			{
				LED=0;
				del(time);
				LED=1;
				del(100-time);				 
			}

		}
		 for(time=100;time>0;time--)
		{
			for(z=0;z<20;z++)
			{
				LED=0;
				del(time);
				LED=1;
				del(100-time);
			}

		}
	}

//		LED=0;
//		LED=1;
//		LED=1;
//		LED=1;
//		LED=1;
//		LED=1;
//		LED=1;
//		LED=1;		 //亮一个，灭7个，灯变暗，这就是PWM的基本原理
	
}