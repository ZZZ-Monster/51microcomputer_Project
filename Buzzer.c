#include <REGX52.H>
#include "delay.H" 
sbit Buzzer=P1^5;

unsigned int i;

void Buzzer_Time(unsigned int ms)		//蜂鸣器响多少毫秒



{
	for(i=0;i<ms;i++)				  //只有加个循环和延时，蜂鸣器才能响
	{
		Buzzer=!Buzzer;
		delay(1);
	}

}

