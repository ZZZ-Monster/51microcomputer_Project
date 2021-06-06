#include <REGX52.H>
#include "DELAY.H"
#include "UART.H" 


void main()
{
	UART_Init();
	while(1)
	{

	}
}

void UART_Routine() interrupt 4
{
	 if(RI==1)    //RI为接收中断标志位
	 {	
	 	P2=SBUF;				//电脑向单片机发送的变量
		UART_SendByte(SBUF);	//单片机向电脑发送字节
		RI=0;
	 }
}






