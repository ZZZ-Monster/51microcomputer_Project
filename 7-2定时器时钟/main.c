#include <REGX52.H>
#include "delay.H"
#include "LCD1602.H" 
#include "Timer0.H"

char sec,min,hour; 
void main()
{
	LCD_Init();   //初始化显示屏
	Timer0Init();  //初始化定时器
	LCD_ShowString(1,1,"CLock");
	
	while(1)
	{
		 LCD_ShowNum(2,1,hour,2);
		 LCD_ShowString(2,3,":");
		 LCD_ShowNum(2,4,min,2);
		 LCD_ShowString(2,6,":");
		 LCD_ShowNum(2,7,sec,2);
	}
}



void Timer0_Routine() interrupt 1	//调用T0，溢出后接下来做什么(中断子程序)
{
	static unsigned int T0count;
	TL0 = 0x18;			//重新给初值。让它再从64535开始	
	TH0 = 0xFC;
	T0count++;
	if(T0count>=1000)
	{
		T0count=0;
		sec++;
		if(sec>=60)
		{
			sec=0;
			min++;
			if(min>=60)
			{
				min=0;
				hour++;
				if(hour>=24)
				{
					hour=0;
				}
			}
		}	
	}

}







