#include <REGX52.H>
#include "delay.H" 

sbit RCK=P3^5;		 //RCLK
sbit SCK=P3^6;		 //SRCLK
sbit SER=P3^4;		 //SER


//74HC595写入字节（控制D口灯）
void _74HC595_WriteByte(unsigned char Byte)	   //名字不能以数字开头，所以加个下划线
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=Byte&0x80;  //把Byte的最高位赋值给SER
		SCK=1;			   //给上升沿使SER输入传入
		SCK=0;			   //置零，为下次做准备
		Byte=Byte<<1;
	}
	RCK=1;				  //把八位Byte数据送到IO口
	RCK=0;				  //置零


}

//Lie为列，HangData为一列中灯的亮
void MatrixLED_ShowColumn(unsigned char Lie,HangData)
{
	_74HC595_WriteByte(HangData);	 //_74HC595_WriteByte函数用来写一列中的LED点亮数据
	P0=~(0x80>>Lie);	   //P0口控制列
}


//初始化点阵屏
void  MatrixLED_Init()
{
	SCK=0;   //初始化脉冲
	RCK=0;	  //初始化锁存器
}



