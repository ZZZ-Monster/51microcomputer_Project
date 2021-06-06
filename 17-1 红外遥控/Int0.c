#include <REGX52.H>

void Int0_Init(void)
{
	IT0=1;		  //外部中断触发的形式  1为下降沿 0为低电平
	IE0=0;		  //外部中断请求标志位	  0时开始是0,1时开始是1
	EX0=1;		  //外部中断允许位
	EA=1;		  //总中断
	PX0=1;		  //中断优先级
	
}




/* 
void Int0_Routine(void) interrupt 0
{
	Num++;	
}
*/
