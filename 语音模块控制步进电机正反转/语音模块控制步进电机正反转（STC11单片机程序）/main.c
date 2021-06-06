#include "config.h"

uint8_t G0_flag=DISABLE;//运行标志，ENABLE:运行。DISABLE:禁止运行 
uint8 idata nAsrStatus=0;	
//应用IO口定义 （模块标注 P2）
sbit PA1=P1^0; //对应板上标号 P1.0
sbit PA2=P1^1;  //对应板上标号 P1.1
sbit PA3=P1^2;  //.....
sbit PA4=P1^3;  //.....
sbit PA5=P1^4;  //.....
sbit PA6=P1^5;  //.....
sbit PA7=P1^6;  //对应板上标号 P1.6
sbit PA8=P1^7;  //对应板上标号 P1.7
sbit LED=P4^2;//信号指示灯

void MCU_init(); 
void ProcessInt0(); //识别处理函数
void delay(unsigned long uldata);
void User_handle(uint8 dat);//用户执行操作函数


/***********************************************************
* 名    称： void  main(void)
* 功    能： 主函数	程序入口
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void  main(void)
{
	uint8 idata nAsrRes;
	uint8 i=0;
	MCU_init();
	LD_Reset();
	nAsrStatus = LD_ASR_NONE;		//	初始状态：没有在作ASR
	
	PA1=1;
	PA2=1;

	while(1)
	{
		switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:		
				break;
			case LD_ASR_NONE:
			{
				nAsrStatus=LD_ASR_RUNING;
				if (RunASR()==0)	/*	启动一次ASR识别流程：ASR初始化，ASR添加关键词语，启动ASR运算*/
				{
					nAsrStatus = LD_ASR_ERROR;
				}
				break;
			}
			case LD_ASR_FOUNDOK: /*	一次ASR识别流程结束，去取ASR识别结果*/
			{				
				nAsrRes = LD_GetResult();		/*获取结果*/
				User_handle(nAsrRes);//用户执行函数 
				nAsrStatus = LD_ASR_NONE;
				break;
			}
			case LD_ASR_FOUNDZERO:
			default:
			{
				nAsrStatus = LD_ASR_NONE;
				break;
			}
		} 			
	}

}

/***********************************************************
* 名    称： void MCU_init()
* 功    能： 单片机初始化
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void MCU_init()
{
	P0 = 0xff;
	P1 = 0x00;
	P2 = 0xff;
	P3 = 0xff;
	P4 = 0xff;

	P1M0=0XFF;	//P1端口设置为推挽输出功能，即提高IO口驱动能力，从驱动继电器模块工作
	P1M1=0X00;

	LD_MODE = 0;		//	设置MD管脚为低，并行模式读写
	IE0=1;
	EX0=1;
	EA=1;
}
/***********************************************************
* 名    称：	延时函数
* 功    能：
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void Delay200us()		//@22.1184MHz
{
	unsigned char i, j;
	_nop_();
	_nop_();
	i = 5;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void  delay(unsigned long uldata)
{
	unsigned int j  =  0;
	unsigned int g  =  0;
	while(uldata--)
	Delay200us();
}

/***********************************************************
* 名    称： 中断处理函数
* 功    能：
* 入口参数：  
* 出口参数：
* 说    明： 					 
* 调用方法： 
**********************************************************/ 
void ExtInt0Handler(void) interrupt 0  
{ 	
	ProcessInt0();				/*	LD3320 送出中断信号，包括ASR和播放MP3的中断，需要在中断处理函数中分别处理*/
}
/***********************************************************
* 名    称：用户执行函数 
* 功    能：识别成功后，执行动作可在此进行修改 
* 入口参数： 无 
* 出口参数：无
* 说    明： 通过控制PAx端口的高低电平，从而控制外部继电器的通断					 
**********************************************************/
void 	User_handle(uint8 dat)
{
		 if(0==dat)
		 {
		  	G0_flag=ENABLE;
				LED=0;
		 }
		 else if(ENABLE==G0_flag)
		 {	
		 		G0_flag=DISABLE;
				LED=1;
			 switch(dat)		   /*对结果执行相关操作,客户修改*/
			  {
//				  case CODE_DMCS:			/*命令“测试”*/
//						PA1=1;//让PA1端口为高电平
//													 break;
//					case CODE_KFBYZ:	 /*命令“全开”*/
//						PA2=1;//让PA2端口为高电平
													 break;
					case CODE_BDDK:		/*命令“复位”*/			//把灯打开	
						PA1=0;//让PA1端口为低电平 
													break;
					case CODE_BDGD:		/*命令“复位”*/			//把灯关掉	
						PA1=1;//让PA1端口为高电平
													break;
					case CODE_DJZZ:		/*命令“复位”*/			//电机正转	
						PA2=0;//让PA2端口为低电平
													break;
					case CODE_DJFZ:		/*命令“复位”*/			//电机反转	
						PA2=1;//让PA2端口为高电平
													break;
//					case CODE_GZ:		/*命令“复位”*/				
//						PA6=1;//让PA6端口为高电平
//													break;																											
				}	
			}	
}	 
