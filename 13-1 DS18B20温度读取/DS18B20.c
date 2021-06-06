#include <REGX52.H>
#include "LCD1602.H"
#include "DS18B20 One Wire.H"

//0xcc忽略ROM指令
//0x44温度转换指令
//0xbe读指令
//0x4e写暂存器指令
//0x48把TH和TL和配置寄存器的内容拷贝到EEPROM		把配置的值放在EEPROM中

void DS18B20_ConvertT(void)		//开始温度变换	  PPT上有
{
	OneWire_Init();
	LCD_ShowNum(1,14,OneWire_Init(),2);		//OneWire_Init()返回值为0表示有从机响应
	OneWire_SendByte(0xcc);
	OneWire_SendByte(0x44);
}


float DS18B20_ReadT(void)
{
	unsigned char TLSB,TMSB;
	int Temp1,Temp2;	 //Temp要放16位
	float T;	  
	OneWire_Init();
	OneWire_SendByte(0xcc);
	OneWire_SendByte(0xbe);
	TLSB=OneWire_ReceiveByte();
	TMSB=OneWire_ReceiveByte();
//	LCD_ShowBinNum(1,1,TMSB,8);
//	LCD_ShowBinNum(1,9,TLSB,8);
//	Temp=(TMSB<<8)|TLSB;
	Temp1=TMSB;			  //把TLSB，TMSB一起存放到Temp中
	Temp2=Temp1<<8;
	Temp2=Temp2|TLSB;		  //此三行的功能与上面一行一样Temp=(TMSB<<8)|TLSB;
	T=Temp2/16.0;
	return T;
}



















 