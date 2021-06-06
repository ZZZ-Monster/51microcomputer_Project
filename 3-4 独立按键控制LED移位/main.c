#include <REGX52.H>
void Delay(int ms);	 //放在前面时一定要加分号；
/*LED的左移  0000 0001
             0000 0010
			 0000 0100
			 0000 1000
			 0001 0000
			 0010 0000
			 0100 0000
			 1000 0000         左移符号<<      */	 


void main()
{
	unsigned char LED;
	P2=~0x01;
	while(1)
	{
//		P2=~0x01;	 //写错了这里
		if(P3_1==0)
		{							 
			Delay(100);
			while(P3_1==0);
			Delay(100);
			P2_1=0;
			LED++;
			if(LED>=8)
				{
					LED=0;
				}
			P2=~(0x01<<LED);
		}
		
		if(P3_0==0)
		{							 
			Delay(100);
			while(P3_0==0);
			Delay(100);
			if(LED==0)
				LED=7;
			else
				LED--;
			P2=~(0x01<<LED);
		}		
	}
}


//延迟函数----------------------------------------------------------------------------//
void Delay(int ms)		//@12.000MHz
{
	while(ms)
	{
		unsigned char i, j;	
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
		ms--;
	}
}