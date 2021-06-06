#include <REGX52.H>

sbit DS1302_SCLK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

// DS1302要先写入时钟，再读出，并显示在LCD1602上

//写的地址加0x01就是读的地址
#define DS1302_Second  0x80			   //写入秒
#define DS1302_Minute  0x82			   //写入分钟
#define DS1302_Hour    0x84			   //写入小时
#define DS1302_Date    0x86			   //写入日
#define DS1302_Month   0x88			   //写入月
#define DS1302_Day     0x8a			   //写入星期
#define DS1302_Year    0x8c			   //写入年
#define DS1302_WP      0x8e			   //关闭保护



signed char DS1302_Time[]={21,5,20,15,50,50,4};	  //年、月、日、时、分、秒、星期



//初始化
void DS1302_Init(void)
{
	DS1302_CE=0;
	DS1302_SCLK=0;
}
//写入指令和书记员
void DS1302_WriteByte(unsigned char Command,Data)
{
	unsigned char i;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=1;					//一个机器周期大约为1us，所以不要加延时
		DS1302_SCLK=0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		DS1302_SCLK=1;					//一个机器周期大约为1us，所以不要加延时
		DS1302_SCLK=0;
	}
	DS1302_CE=0;	 
}

//读出数据
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i,Data=0x00;
	Command|=0x01;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;					//一个机器周期大约为1us，所以不要加延时
		DS1302_SCLK=1;
	}
	for(i=0;i<8;i++)
	{
		DS1302_SCLK=1;
		DS1302_SCLK=0;
		if(DS1302_IO){Data=Data|(0x01<<i);}	   //如果接收到了，就把Data置1，也就是Data就是接收到的数据		
	}
	DS1302_CE=0;
	DS1302_IO=0;	 	//写完一遍要置0，不然会花屏
	return Data;
}

//把数组写入到DS1302
void DS1302_SetTime(void)
{	
	DS1302_WriteByte(DS1302_WP,0x00);	//关闭写保护						 //※※※※※※DS1302里为BCD码※※※※※※
	DS1302_WriteByte(DS1302_Year,DS1302_Time[0]/10*16+DS1302_Time[0]%10);	//写入年   //要转换成BCD码存进去
	DS1302_WriteByte(DS1302_Month,DS1302_Time[1]/10*16+DS1302_Time[1]%10);	//写入月   //要转换成BCD码存进去
	DS1302_WriteByte(DS1302_Date,DS1302_Time[2]/10*16+DS1302_Time[2]%10);	 //写入日   //要转换成BCD码存进去
	DS1302_WriteByte(DS1302_Hour,DS1302_Time[3]/10*16+DS1302_Time[3]%10);	 //写入小时   //要转换成BCD码存进去
	DS1302_WriteByte(DS1302_Minute,DS1302_Time[4]/10*16+DS1302_Time[4]%10);	 //写入分钟   //要转换成BCD码存进去
	DS1302_WriteByte(DS1302_Second,DS1302_Time[5]/10*16+DS1302_Time[5]%10);	 //写入秒   //要转换成BCD码存进去
	DS1302_WriteByte(DS1302_Day,DS1302_Time[6]/10*16+DS1302_Time[6]%10);	 //写入星期   //要转换成BCD码存进去
	DS1302_WriteByte(0x8f,0x00);	//打开写保护					
}


//读出DS1302的数据
void DS1302_ReadTime(void)
{
	unsigned char Temp;						//给个临时量
	Temp=DS1302_ReadByte(DS1302_Year);      //程序里已经自动加1了，加1是读的指令
	DS1302_Time[0]=Temp/16*10+Temp%16;		//DS1302为BCD码，取出来就要变成十进制码
	Temp=DS1302_ReadByte(DS1302_Month);      //程序里已经自动加1了，加1是读的指令
	DS1302_Time[1]=Temp/16*10+Temp%16;		//DS1302为BCD码，取出来就要变成十进制码
	Temp=DS1302_ReadByte(DS1302_Date);      //程序里已经自动加1了，加1是读的指令
	DS1302_Time[2]=Temp/16*10+Temp%16;		//DS1302为BCD码，取出来就要变成十进制码
	Temp=DS1302_ReadByte(DS1302_Hour);      //程序里已经自动加1了，加1是读的指令
	DS1302_Time[3]=Temp/16*10+Temp%16;		//DS1302为BCD码，取出来就要变成十进制码
	Temp=DS1302_ReadByte(DS1302_Minute);      //程序里已经自动加1了，加1是读的指令
	DS1302_Time[4]=Temp/16*10+Temp%16;		//DS1302为BCD码，取出来就要变成十进制码
	Temp=DS1302_ReadByte(DS1302_Second);      //程序里已经自动加1了，加1是读的指令
	DS1302_Time[5]=Temp/16*10+Temp%16;		//DS1302为BCD码，取出来就要变成十进制码
	Temp=DS1302_ReadByte(DS1302_Day);      //程序里已经自动加1了，加1是读的指令
	DS1302_Time[6]=Temp/16*10+Temp%16;		//DS1302为BCD码，取出来就要变成十进制码

}














