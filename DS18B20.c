#include <REGX52.H>
#include "LCD1602.H"
#include "DS18B20 One Wire.H"

void DS18B20_ConvertT(void)		//开始温度变换	  PPT上有
{
	OneWire_Init();
	OneWire_SendByte(0xcc);
	OneWire_SendByte(0x44);
}


float DS18B20_ReadT(void)
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(0xcc);
	OneWire_SendByte(0xbe);
	TLSB=OneWire_ReceiveByte();
	TMSB=OneWire_ReceiveByte();
//	LCD_ShowBinNum(1,1,TMSB,8);
//	LCD_ShowBinNum(1,9,TLSB,8);
	Temp=(TMSB<<8)|TLSB;
	T=Temp/16.0;
	return T;
}



















 