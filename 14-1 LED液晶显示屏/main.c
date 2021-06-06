#include <REGX52.H>
#include "LCD1602.H"
#include "delay.H"  

 void main()
 {
 	LCD_Init();

 	while(1)
	{
		LCD_ShowChar(1,1,0x25);	 //显示百分号
//		LCD_ShowString(1,1,"123456");
//		LCD_ShowNum(1,1,123,4);
//		LCD_ShowSignedNum(1,1,-1000,6);
//		LCD_ShowHexNum(1,1,0x85,2);
//		LCD_ShowBinNum(1,1,0xa5,8);
//		LCD_ShowChar(1,1,0xdf);  //显示温度符号
//		LCD_ShowChar(1,2,'C');  //显示温度符号


//		LCD_ShowString(1,5,"HT  Love  ZP");
//	  	LCD_WriteCommand(0x18);		  //写入左移一位指令，因为在while里，所以一直执行左移
//		delay(80);

	}
}