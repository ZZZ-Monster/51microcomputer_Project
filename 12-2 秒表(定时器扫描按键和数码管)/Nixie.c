#include <REGX52.H>
#include "delay.h"

unsigned char shumaguan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00}; //数码管的数字
unsigned char Nixie_Buf[9]={0,1,2,10,10,10,10,10,10};

void Nixie_SetBuf(char Location,Number)
{
	Nixie_Buf[Location]=Number;		
}


void Nixie_Scan(char Location,Number)	  //NiXie为数码管,Location定义哪一个数码管亮，Number定义亮几
{
	P0=0x00;
	switch(Location)
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=shumaguan[Number];	
}



void Nixie_Loop(void)  //数码管扫描		  //每格2ms调用一次
{
	static unsigned char i=1;
	Nixie_Scan(i,Nixie_Buf[i]);
	i++;
	if(i>=9){i=1;}	
} 














