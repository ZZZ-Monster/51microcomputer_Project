#include <REGX52.H>

//发送不需要中断，接收时要接收来自单片机的信息就需要一个中断，因为不知道什么时候发过来，所以用中断来处理
//串口初始化
void UART_Init()    //异步收发传输器初始化
{
	SCON=0x50;		//串行口控制寄存器
	PCON |= 0x80;	//电源控制寄存器
	TMOD &= 0x0F;	//设置定时器模式
	TMOD |= 0x20;	//设置定时器模式
	TL1 = 0xF3;		//设置定时初始值
	TH1 = 0xF3;		//设置定时重载值
	ET1 = 0;        //禁止定时器1中断     	 
 	TR1 = 1;		//定时器1启动
	EA = 1;
	ES = 1;
}


//串口发送一个字节数据到接收缓冲区
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);		 //检测是否发送完毕
	TI=0;
}


/*
//串口中断函数的模板
void UART_Routine() interrupt 4
{
	 if(RI==1)    //RI为接收中断标志位
	 {	
	 				
		
		RI=0;
	 }
}
*/