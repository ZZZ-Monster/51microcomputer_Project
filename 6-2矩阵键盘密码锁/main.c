#include <REGX52.H>
#include "DELAY.H"
#include "LCD1602.H"
#include "matrixkey.H"

int pass;
char NUM,count;
void main()
{

	LCD_Init();
	LCD_ShowString(1,1,"Pass world:");
	
	while(1)
	{
		NUM=matrixkey();
		if(NUM)
		{
			if(NUM<=10)		  //如果1到10的按钮按下，输入密码
			{
				if(count<4)		  //超过四位就不再输入
				{
					pass*=10;
					pass+=NUM%10;
					count++;	  //计次
				}
			}
			LCD_ShowNum(2,2,pass,4);
		

			if(NUM==11)	  //确认键
			{
				 if(pass==1234)			//如果密码等于1234，显示ok
				 {
					LCD_ShowString(1,13,"OK ");
					pass=0;						  //密码清零
					count=0;					  //计数清零
					LCD_ShowNum(2,2,pass,4);	 //更新显示
				 }
				 else
				 {
				 	LCD_ShowString(1,13,"err");	    
					pass=0;							//密码清零
					count=0;						//计数清零
					LCD_ShowNum(2,2,pass,4);	  //更新显示
				 }
			}

			  if(NUM==12)
			  {
			   		pass=0;							//密码清零
					count=0;						//计数清零
					LCD_ShowNum(2,2,pass,4);	  //更新显示	
			  }

		
		}

	}
}