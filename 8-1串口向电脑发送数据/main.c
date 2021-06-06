#include <REGX52.H>
#include "DELAY.H"
#include "UART.H" 

unsigned char Sec=0X00;

void main()
{
	UART_Init();

	while(1)
	{
		UART_SendByte(Sec);
		Sec++;
		delay(1000);	//发的太快有误差
	}
}