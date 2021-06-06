#include <REGX52.H>
#include "delay.H" 

sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;

#define LCD_Datapart P0


void LCD_WriteCommand(unsigned char Command)	  //进行写设置的指令
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_Datapart=Command;
	LCD_E=1;	//上升沿为纳秒级别，应该延时一下，读取不过来
	delay(1);
	LCD_E=0;
	delay(1); 	//下降沿为纳秒级别，应该延时一下，读取不过来
}


void LCD_WriteData(unsigned char Data)				//用户给的字符等数据
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_Datapart=Data;
	LCD_E=1;	//上升沿为纳秒级别，应该延时一下，读取不过来
	delay(1);
	LCD_E=0;
	delay(1); 	//下降沿为纳秒级别，应该延时一下，读取不过来	
}

void LCD_Init(void)
{
	LCD_WriteCommand(0x38);							//初始化代码0x38  八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0c);							//          0x0c  显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);							//          0x06  数据读写操作后，光标自动加1，画面不动
	LCD_WriteCommand(0x01);							//          0x01  清屏
													
												
}



																	  

//显示一个字符-----------------------------------------------------------------------------------------------------
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)	 
{
	 if(Line==1)
	 {
	 	 LCD_WriteCommand(0x80+(Column-1));	  //显示字符  0x80+地址 设置光标位置(1000 0000代表它是一个地址设置的指令)
	 }
	 if(Line==2)
	 {
	 	 LCD_WriteCommand(0x80+(Column-1)+0x40);  //显示字符  0x80|地址 设置光标位置(1000 0000代表它是一个地址设置的指令)
	 }
	 LCD_WriteData(Char);     //显示字符	//发送数据											   
											   
}





//字符串数组-----------------------------------------------------------------------------------------------------
void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char String[])  
{
	 unsigned char i;
	 if(Line==1)
	 {
	 	 LCD_WriteCommand(0x80|(Column-1));	 
	 }
	 if(Line==2)
	 {
	 	 LCD_WriteCommand(0x80|(Column-1)+0x40); 
	 }
	 for(i=0;String[i]!='\0';i++)	  //数组最后一位标志位'\0'，遍历到最后
	 {
	 	LCD_WriteData(String[i]);		 //发送数据
	 }
	
}


//x的y次方函数-----------------------------------------------------------------------------------------------------
int LCD_Pow(int X,int Y)
{
	 unsigned char i;
	 int result=1;
	 for(i=0;i<Y;i++)
	 {
	 	  result*=X;
	 }
	 return result;
}


//显示数字
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)  
{
	 unsigned char i;
	 if(Line==1)
	 {
	 	 LCD_WriteCommand(0x80|(Column-1));	 
	 }
	 if(Line==2)
	 {
	 	 LCD_WriteCommand(0x80|(Column-1)+0x40); 
	 }
	 for(i=Length;i>0;i--)
	 {													   //	 Number/100%10;	百		i=3		 10^(3-1)
		LCD_WriteData(0x30+Number/LCD_Pow(10,i-1)%10);	  //	 Number/10%10;	十		i=2		 10^(2-1)
		//这里加0x30是为了得到数字真正的ASCLL码值		  //	 Number/1%10; 	个		i=1		 10^(1-1)
	 }
	
}




//显示带正负的整数-----------------------------------------------------------------------------------------------------
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	 unsigned char i;  
	 if(Line==1)
	 {
	 	 LCD_WriteCommand(0x80|(Column-1));	 
	 }
	 if(Line==2)
	 {
	 	 LCD_WriteCommand(0x80|(Column-1)+0x40); 
	 }
	 if(Number>=0)
	 {
	 	 LCD_WriteData('+');

	 }
	 else
	 {
	 	 LCD_WriteData('-');
		 Number=-Number;
	 }
	 for(i=Length;i>0;i--)
	 {													   //	 Number/100%10;	百		i=3		 10^(3-1)
		LCD_WriteData(0x30+Number/LCD_Pow(10,i-1)%10);	  //	 Number/10%10;	十		i=2		 10^(2-1)
		//这里加0x30是为了得到数字真正的ASCLL码值		  //	 Number/1%10; 	个		i=1		 10^(1-1)
	 }
 }


//显示16进制数-----------------------------------------------------------------------------------------------------
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	 unsigned char i,SingleNumber;  

	 if(Line==1)
	 {
	 	 LCD_WriteCommand(0x80|(Column-1));	 
	 }
	 if(Line==2)
	 {
	 	 LCD_WriteCommand(0x80|(Column-1)+0x40); 
	 }
	 for(i=Length;i>0;i--)
	 {	
	 	SingleNumber=Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData(0x30+Number/LCD_Pow(16,i-1)%16); //这里加0x30是为了得到数字真正的ASCLL码值
		}												   
		else
		{
			LCD_WriteData('A'+SingleNumber-10);
		}	  
				
	  }
 }



//显示2进制数-----------------------------------------------------------------------------------------------------
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	 unsigned char i;  
	 if(Line==1)
	 {
	 	 LCD_WriteCommand(0x80|(Column-1));	 
	 }
	 if(Line==2)
	 {
	 	 LCD_WriteCommand(0x80|(Column-1)+0x40); 
	 }
	 for(i=Length;i>0;i--)
	 {													   
		LCD_WriteData(0x30+Number/LCD_Pow(2,i-1)%2);	
		//这里加0x30是为了得到数字真正的ASCLL码值		  
	 }
}

















