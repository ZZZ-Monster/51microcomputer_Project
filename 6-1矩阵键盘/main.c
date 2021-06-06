#include <REGX52.H>
#include "DELAY.H"
#include "LCD1602.H"
#include "matrixkey.H"


char NUM;
void main()
{

	LCD_Init();
	LCD_ShowString(1,1,"Matrixkey:");
	
	while(1)
	{
		NUM=matrixkey();
		if(NUM)
		{
			LCD_ShowNum(2,2,NUM,2);
		}
	}
}