#include <REGX52.H>
#include "timer0.h"
#include "Uart.h"

sbit SG_PWM=P0^0;							//信号控制引脚
unsigned char count=0;					     //计次  赋初值为0
unsigned char PWM_count=0;                  //0--0度，2--45度，4--90度，6--135度，8--180度

void main()
{
  Timer0_Init();
  Uart_Init();
  while(1)
  {
//	  if(P1_0==0)PWM_count=0;	  //舵机转动0度
//	  if(P1_1==0)PWM_count=2;	  //舵机转动45度
//    if(P1_2==0)PWM_count=4;	  //舵机转动90度
//	  if(P1_3==0)PWM_count=6;else PWM_count=0;	  //舵机转动135度			(else PWM_count=0;该语句只能用其中一句上，否则有干扰)
//	  if(P1_4==0)PWM_count=8;	  //舵机转动180度
   }
}

void Timer0() interrupt 1      //特别注意此处，0--外部中断0，1--定时器中断0，2--外部中断1，3--定时器中断1，4--串行口中断1
{
  TR0=0;
  TL0 = 0x33;		
  TH0 = 0xFF;			 //重新赋计数初值为0.5ms
  

  if(count<=PWM_count)
  {									
    SG_PWM=1;
  }
  else
  {
    SG_PWM=0;
  }
  count++;						  //计次，每0.5毫秒加1
  if(count>=40)
  {
    count=0;
  }
  TR0=1;
}
void UART_Routine()  interrupt 4
{	
	if(RI==1)
	{	
	  P1 =SBUF;					   //发送的数据SBUF，赋给P2
	 if(P1==0X01)				   //0x01这个值可以通过蓝牙调试器编辑模式设置
	 {
	   PWM_count=0;
	 }
	 if(P1==0X02)				   //0x02这个值可以通过蓝牙调试器编辑模式设置
	 {
	   PWM_count=1;
	 }
	 if(P1==0X03)				   //0x03这个值可以通过蓝牙调试器编辑模式设置
	 {
	   PWM_count=2;
	 }
	 if(P1==0X04)				   //0x03这个值可以通过蓝牙调试器编辑模式设置
	 {
	   PWM_count=3;
	 }
	 if(P1==0X05)				   //0x03这个值可以通过蓝牙调试器编辑模式设置
	 {
	   PWM_count=4;
	 }
	 if(P1==0X06)				   //0x03这个值可以通过蓝牙调试器编辑模式设置
	 {
	   PWM_count=5;
	 }
	 if(P1==0X07)				   //0x03这个值可以通过蓝牙调试器编辑模式设置
	 {
	   PWM_count=6;
	 }
	 if(P1==0X08)				   //0x03这个值可以通过蓝牙调试器编辑模式设置
	 {
	   PWM_count=7;
	 }
	 if(P1==0X09)				   //0x03这个值可以通过蓝牙调试器编辑模式设置
	 {
	   PWM_count=8;
	 }

	  RI=0;
	}
}
