#include <REGX52.H>


sbit OneWire_PQ=P3^7;

//初始化
unsigned char OneWire_Init(void)	
{	
	unsigned char i,AckBit;			//AckBit为应答位
	EA=0;										/*EA中断的打开和关闭主要是为了使定时器不扰乱数据传输的延时*/				   
	OneWire_PQ=1;
	OneWire_PQ=0;
	i = 247;while (--i);		//延时500us
	OneWire_PQ=1;
	i = 32;while (--i);			//延时70us(15-60us)
	AckBit=	OneWire_PQ;		   //应答的数据给应答位
	i = 247;while (--i);		//延时500us
	EA=1;
	return  AckBit;			   //从机如果给响应了就是0，没有给就是1
}


//发送一位
void OneWire_SendBit(unsigned char Bit)
{   
	unsigned char i;
	EA=0;
	OneWire_PQ=0;
	i = 4;while (--i);	  //延时13us左右
	OneWire_PQ=Bit;
	i = 24;while (--i);	  //延时50us左右
	OneWire_PQ=1;
	EA=1;
}

//接收一位
unsigned char OneWire_ReceiveBit(void)
{
	
	unsigned char Bite,i; 
	EA=0;
	OneWire_PQ=0;
	i = 2;while (--i);	   //5us的延时
	OneWire_PQ=1;
	i = 2;while (--i);	   //5us的延时
	Bite=OneWire_PQ;
	i = 24;while (--i);	  //延时50us左右
	EA=1;
	return Bite;
}



//发送一个字节
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&0x01<<i);
	}	
}



//接收一个字节
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte=Byte|(0x01<<i);}
	}
	return Byte;	
}












