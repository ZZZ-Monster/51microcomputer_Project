#include <REGX52.H>
#include "delay.H" 
#include "LCD1602.H" 
#include "matrixkey.H"
#include "i2c.H"
#include "AT24C02.H"   

void main()
{
	unsigned char KeyNum;
	unsigned int Num;				   //16位数据
	LCD_Init();
	LCD_ShowNum(1,1,Num,5);
//	AT24C02_WriteByte(1,2);			//第一个地址写入
//	delay(10);
////	AT24C02_WriteByte(2,3);			//第一个地址写入
////	delay(10);
//	Data=AT24C02_ReadByte(2);		   //读第一个地址的数据
//	LCD_ShowNum(2,1,Data,3);			//显示地址的数据（掉电不丢失写入的数据）
	while(1)
	{
		KeyNum=matrixkey();
		if(KeyNum==1)				    //如果按键是1，Num++
		{
			Num++;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum==2)					//如果按键是2，Num--
		{
			Num--;
			LCD_ShowNum(1,1,Num,5);
		}
		if(KeyNum==3)					//如果按键是3，把Num的低八位存入AT24C02
		{
			AT24C02_WriteByte(0,Num%256);  //取Num的低八位
			delay(5);
			AT24C02_WriteByte(1,Num/256);  //取Num的高八位
			delay(5);
			LCD_ShowString(2,1,"Write Ok");
			delay(1000);
			LCD_ShowString(2,1,"         ");
		}
		if(KeyNum==4)
		{
			Num=AT24C02_ReadByte(0);           //读0位置的数据
			Num|=AT24C02_ReadByte(1)<<8;
			LCD_ShowNum(1,1,Num,5);
			LCD_ShowString(2,1,"Read Ok");
			delay(1000);
			LCD_ShowString(2,1,"         ");

		}
	}
}

























