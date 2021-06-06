#include <REGX52.H>
#include "LCD1602.H" 
#include "DS18B20 One Wire.H"
#include "DS18B20.H"
#include "DELAY.H" 
#include "AT24C02.H" 
#include "KEY2.H"
#include "Timer0.H"  


float T,Tshow;
unsigned char KeyNum;
char TLow,THigh;
void main()
{	
	DS18B20_ConvertT();			    //防止上电后出现短暂的初始值
	delay(1000);
	THigh=AT24C02_ReadByte(0);		//上电时取出数据
	TLow=AT24C02_ReadByte(1);
	if(THigh>125||THigh<=TLow||TLow<-55)
	{
		TLow=15;
		THigh=25;
	}
 	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,THigh,3);
	LCD_ShowSignedNum(2,12,TLow,3);
	Timer0Init();
 	while(1)
	{	/*温度读取及显示*/
		
	    KeyNum=Key();
		DS18B20_ConvertT();
		T=DS18B20_ReadT();
		if(T<0)
		{
			LCD_ShowChar(1,3,'-');
			Tshow=-T;
		}
		else
		{
			LCD_ShowChar(1,3,'+');
			Tshow=T;
		}
		LCD_ShowNum(1,4,Tshow,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(Tshow*100)%100,2);

		/*阈值判断及显示*/
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				THigh++;
				if(THigh>125){THigh=125;}	
			}
			if(KeyNum==2)
			{
				THigh--;
				if(THigh<=TLow){THigh++;}	
			}
			if(KeyNum==3)
			{
				TLow++;	
				if(THigh<=TLow){TLow--;}	

			}
			if(KeyNum==4)
			{
				TLow--;
				if(TLow<-55){TLow=-55;}	
			}
			LCD_ShowSignedNum(2,4,THigh,3);
			LCD_ShowSignedNum(2,12,TLow,3);
			AT24C02_WriteByte(0,THigh);			//存入 AT24C02
			delay(5);
			AT24C02_WriteByte(1,TLow);
			delay(5);

		}
		if(T>THigh)
		{
			LCD_ShowString(1,13,"OV:H");
		}
		else if(T<TLow)
		{
			LCD_ShowString(1,13,"OV:L");
		}
		else
		{
			LCD_ShowString(1,13,"    ");
		}
	}
}


void Timer0_Routine() interrupt 1	//调用T0，溢出后接下来做什么(中断子程序)
{
	static unsigned int T0count;    //无符号int为0~65535
	TL0 = 0x18;			//重新给初值。让它再从64535开始	
	TH0 = 0xFC;
	T0count++;
	if(T0count>=20)
	{
		T0count=0;
		Key_Loop();	
	}
}

































