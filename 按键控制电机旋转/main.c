#include <REGX52.H>
#include "delay.h"
void main()
{
	while(1)  
	{		
		if(P3_2==0)
		{
			delay(100);
			while(P3_2==1);
			delay(100);
			P2_1=~P2_1;
			P1_0=~P1_0;		
		}
	}
}