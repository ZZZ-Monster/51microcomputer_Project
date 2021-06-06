#include <REGX52.H>
unsigned char shumaguan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; //数码管的数字


void delay(int ms)		//@12.000MHz
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





void NiXie(char Location,Number)	  //NiXie为数码管,Location定义哪一个数码管亮，Number定义亮几
{
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
	delay(1);		//这两行代码是消影的作用
	P0=0x00;	
}



void main()
{
	while(1)
	{
		NiXie(1,1);
//		delay(2);
		NiXie(2,2);
//		delay(2);
		NiXie(3,3);
//		delay(2);
		NiXie(4,4);
//		delay(2);
		NiXie(5,5);
//		delay(2);
		NiXie(6,6);
//		delay(2);

	}
}





