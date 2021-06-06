#include <REGX52.H>


void Delayms(int ms)		//@12.000MHz
{
	unsigned char i, j;
	while(ms)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		ms--;
	}
}



void main()
{
	while(1)
	{
		if(P3_1==0)				 //判断按键的按下
		{
			Delayms(100);   //消除抖动 一般大约100ms
			if(P3_1==0)	 //再次判断按键是否按下
				{
					P2_0=~P2_0;	  //led状态取反
				}
			while(P3_1==1)				   //检测按键是否松开
		 		{
					continue;
				}
		}	
	}
}