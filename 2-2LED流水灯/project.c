#include <REGX52.H>
//#include <INTRINS.H>
void delay(int ms)		//@12.000MHz
{
	while(ms)
	{
	 	unsigned char i, j;
		i = 2;
		j = 239;
		do
			{
				while (--j);
			} 
			while (--i);
		ms--;
	}	
}



void main()
{
	while(1)
	{
		P2_0=0;    
		delay(10);
		P2_0=1;
		P2_1=0;	
		delay(10);
		P2_1=1;
		P2_2=0;	
		delay(10);
		P2_2=1;
		P2_3=0;
		delay(10);
		P2_3=1;
		P2_4=0;	
		delay(10);
		P2_4=1;
		P2_5=0;
		delay(10);
		P2_5=1;
		P2_6=0;	 
		delay(10);
		P2_6=1;
		P2_7=0;	 
		delay(10);
		P2_7=1;
		
	}	
}