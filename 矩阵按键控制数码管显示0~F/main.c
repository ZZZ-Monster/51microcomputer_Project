#include <REGX52.H>
#include "delay.H" 
unsigned char shumaguan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7F,0x39,0x3F,0x79,0x71};
void display(unsigned char i);
unsigned char Key(void);
unsigned char matrixkey();
void Key_Loop(void); 
void Init_time0(void);

unsigned char KeyNum,Key_KeyNumber;


void main()
{	
	Init_time0();
	while(1)
	{	
		KeyNum=Key();
		if(KeyNum)
		{
			display(KeyNum);
//			Nixie_SetBuf(2,KeyNum);
//			Nixie_SetBuf(3,KeyNum);
		}

	}
}

						


unsigned char matrixkey_GetState()		   //矩阵键盘的选择
{
	unsigned char keynumber=0;	  
	P1_7=0;		   //第一列给高电平
	if(P1_3==0){keynumber=1;}	 //判断第一列的第几个
	if(P1_2==0){keynumber=2;}
	if(P1_1==0){keynumber=3;}	  //把while判断去掉，新加一个函数Key_Loop，用定时器每20ms调用一次
	if(P1_0==0){keynumber=4;}
	return keynumber;	
}


void Key_Loop(void)
{
	static unsigned char NowState,LastState;
	LastState=NowState;
	NowState=matrixkey_GetState();
	if(LastState==1&&NowState==0){Key_KeyNumber=1;}
	if(LastState==2&&NowState==0){Key_KeyNumber=2;}  
	if(LastState==3&&NowState==0){Key_KeyNumber=3;}  
	if(LastState==4&&NowState==0){Key_KeyNumber=4;}    
}

unsigned char Key(void)
{
	unsigned char Temp;
	Temp=Key_KeyNumber;
//	Key_KeyNumber=0;
	return Temp;
}



void display(unsigned char i)		 //数码管的显示
{
	P2_4=1;
	P2_3=1;
	P2_2=1;
	P0=shumaguan[i];
	delay(2);
	P2_4=1;									   
	P2_3=1;
	P2_2=0;
	P0=shumaguan[i];
	delay(2);															
	P2_4=1;
	P2_3=0;
	P2_2=1;
	P0=shumaguan[i];
	delay(2);
	P2_4=1;
	P2_3=0;							   
	P2_2=0;
	P0=shumaguan[i];								
	delay(2);	
}




void Init_time0(void)
{
 	TMOD |= 0x01;         
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
  	EA=1;             //总中断打开
  	ET0=1;            //定时器T0允许中断
  	TR0=1;            //定时器T0开始工作
}




void Interrupt_handler_time0(void) interrupt 1
{
	static unsigned int T0count1;    //无符号int为0~65535
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
   	T0count1++;
	if(T0count1>=20)
	{
		T0count1=0;
		Key_Loop();	
	}

}













