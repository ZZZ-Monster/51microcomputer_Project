#include <REGX52.H>
#include "LCD1602.H"
#include "delay.H"
void main()
{
	int NUM=0;
//	LCD_Init();   //上电之前初始化一下
//	LCD_ShowChar(1,1,'A');
//	LCD_ShowString(1,3,"HT LOVE YOU");    //几行第几个开始显示字符串
//	LCD_ShowNum(2,2,123,3);
//	LCD_ShowHexNum(2,6,0xA8,2);		//显示十六进制数
//	LCD_ShowBinNum(2,9,0xA8,8);		//显示二进制数
	LCD_Init();
	while(1)
	{				
	   
	   NUM++;
	   delay(10);
	   LCD_ShowNum(2,5,NUM,4);
	
			
	}
}