#include <REGX52.H>
#include "delay.H"
#include "motor.H"
#include "NIXIE.H"
#include "matrixkey.H" 
#include "IR.H"   

unsigned char Command,Speed;		  //调节占空比只要调节Compare的值就可以


void main()
{	
	IR_Init();
	Motor_Init();
	while(1)
	{
		if(IR_GetDataFlag())
		{
			Command=IR_GetCommand();
			if(Command==IR_0)  Speed=0;
			if(Command==IR_1)  Speed=1;
			if(Command==IR_2)  Speed=2;
			if(Command==IR_3)  Speed=3;

							
			if(Speed==0){Motor_SetSpeed(0);}
			if(Speed==1){Motor_SetSpeed(50);}
			if(Speed==2){Motor_SetSpeed(70);}
			if(Speed==3){Motor_SetSpeed(100);}
		}
		Nixie(1,Speed);	
	} 
	
}










