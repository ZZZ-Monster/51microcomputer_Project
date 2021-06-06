#include <REGX52.H>
#include "DELAY.H" 

unsigned char matrixkey()
{
	unsigned char keynumber=0;
	P1=0xff;	  //先全部置零
	P1_3=0;		   //第一列给高电平
	if(P1_7==0){delay(20);while(P1_7==0);delay(20);keynumber=1;}	 //判断第一列的第几个
	if(P1_6==0){delay(20);while(P1_6==0);delay(20);keynumber=5;}
	if(P1_5==0){delay(20);while(P1_5==0);delay(20);keynumber=9;}
	if(P1_4==0){delay(20);while(P1_4==0);delay(20);keynumber=13;}
	
	
	P1=0xff;	  
	P1_2=0;		 
	if(P1_7==0){delay(20);while(P1_7==0);delay(20);keynumber=2;}	
	if(P1_6==0){delay(20);while(P1_6==0);delay(20);keynumber=6;}
	if(P1_5==0){delay(20);while(P1_5==0);delay(20);keynumber=10;}
	if(P1_4==0){delay(20);while(P1_4==0);delay(20);keynumber=14;}
	
	P1=0xff;	  
	P1_1=0;		 
	if(P1_7==0){delay(20);while(P1_7==0);delay(20);keynumber=3;}	
	if(P1_6==0){delay(20);while(P1_6==0);delay(20);keynumber=7;}
	if(P1_5==0){delay(20);while(P1_5==0);delay(20);keynumber=11;}
	if(P1_4==0){delay(20);while(P1_4==0);delay(20);keynumber=15;}
	
	
	P1=0xff;	  
	P1_0=0;		 
	if(P1_7==0){delay(20);while(P1_7==0);delay(20);keynumber=4;}	
	if(P1_6==0){delay(20);while(P1_6==0);delay(20);keynumber=8;}
	if(P1_5==0){delay(20);while(P1_5==0);delay(20);keynumber=12;}
	if(P1_4==0){delay(20);while(P1_4==0);delay(20);keynumber=16;}	
	
		
	return keynumber;
	
}