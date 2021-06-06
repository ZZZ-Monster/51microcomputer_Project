#include <REGX52.H>

void main()
{	  	
	while(1)
	{
		 if(P3_1==0)		 //&&与    ||并
		 {
		 	 P2_0=0;	//P2_0 =0是只对一个LED给高电平，P2=0xfe是对全部的8个辨别 1111 1110
		 }
		 else
		 {
		 	 P2_0=1;	   //P2_0灭
		 }
	}
}