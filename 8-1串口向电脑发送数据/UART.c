#include <REGX52.H>


//串口初始化
void UART_Init()    //异步收发传输器初始化
{	 	

	TMOD &= 0x0F;	//设置定时器模式
	TMOD |= 0x20;	//设置定时器模式
	TL1 = 0xF3;		//设置定时初始值
	TH1 = 0xF3;		//设置定时重载值			  //12MHZ只能4800波特率，误差小
 	TR1 = 1;		//定时器启动
	SCON=0x40;		//串行口控制寄存器   SM0=0；SM1=1；REN=1； 
	PCON |= 0x80;	//电源控制寄存器	 SMOD=1；
	ET1 = 0;        //禁止定时器中断     	 

}


//串口发送一个字节数据
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;		 	  //把要发送的字节送给缓冲寄存器
	while(TI==0);		  //判断是否发送完毕，如果发送完毕TI会由系统自动置1
	TI=0;				   //响应中断后必须手动置0，
}