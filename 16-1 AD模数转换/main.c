#include <REGX52.H>
#include "delay.H"
#include "LCD1602.H"
#include "XPT2046.H"

unsigned int ADvalue; 
void main()
{  	
	
	LCD_Init();
	LCD_ShowString(1,1,"ADJ");
	while(1)
	{
		ADvalue=XPT2046_readAD(XPT2046_XP);
		LCD_ShowNum(2,1,ADvalue,4);
		delay(10);
		ADvalue=XPT2046_readAD(XPT2046_YP);
		LCD_ShowNum(2,6,ADvalue,4);
		delay(10);
		ADvalue=XPT2046_readAD(XPT2046_AUX);
		LCD_ShowNum(2,11,ADvalue,4);
		delay(10);
	}
}  