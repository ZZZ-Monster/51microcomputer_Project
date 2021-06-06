#include <REGX52.H> 
#include "delay.H"

unsigned char shumaguan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; 
unsigned int i,num,a,b;	     //如果定义无符号的char就只能为0~255，无符号的int为0~65535
void key();
void display(unsigned char shi,ge);
void main()
{  
	TMOD = 0x01;	//设置定时器模式
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0开始计时
	EA = 1;
	ET0 = 1;
	while(1)
	{
		a=num/10;
		b=num%10;
	    display(a,b);
		key();
	}
}

void display(unsigned char shi,ge)
{
	P2_4=1;
	P2_3=0;
	P2_2=1;
	P0=shumaguan[shi];
	delay(10);
	P2_4=1;
	P2_3=0;
	P2_2=0;
	P0=shumaguan[ge];
	delay(10);
}
			   
void T0_Timer() interrupt 1
{	
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	i++;
	if(i==1000)
	{
		i=0;
		num++;
		if(num==60)
			num=0;
	}

}

void key()
{
	if(P3_1==0)
	{
		delay(10);
		while(P3_1==0);
		delay(10);
		num++;
		if(num==60)
			num=0;			
	}
	if(P3_0==0)
	{
		delay(10);
		while(P3_0==0);
		delay(10);	
		if(num==0)
			num=60;
		num--;
	}
	if(P3_2==0)
	{
		delay(10);
		while(P3_2==0);
		delay(10);
		num=0;
	}
	if(P3_3==0)
	{
		delay(10);
		while(P3_3==0);
		delay(10);
		TR0=~TR0;	
	}
}









