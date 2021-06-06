#include <REGX52.H>


void Uart_Init()   //9600bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率加倍	
	SCON = 0x50;		//8位数据
	TMOD &= 0x0F;		//清除定时器1模式
	TMOD |= 0x20;		//设定定时器8为自动
	TL1 = 0xFA;			//设定初始值
	TH1 = 0xFA;			//设定初始值
	ET1 = 0;		
    TR1 = 1;
    EA = 1;
    ES =1 ; 	
}

