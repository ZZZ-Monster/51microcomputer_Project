#include <REGX52.H>
#include <STDIO.H>
#include "delay.H"
#include "timer0.H"  

unsigned char i=0x00;



void main()
{	
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF3;		//设置定时初始值
	TH1 = 0xF3;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时


	while(1)
	{
		TI=1;
		printf("张鹏制作\n");		  //在使用printf和puts时都应该TI=1
		if(TI==1)
		{
			TI=0;		
		}
		delay(1000);
	}



//	while(1)
//	{
//		SBUF='a';	//可以输入字符
//		SBUF=i;
//		if(TI==1)
//		{
//			TI=0;		
//		}
////		i++;		
//		delay(1000);
//	}
}



