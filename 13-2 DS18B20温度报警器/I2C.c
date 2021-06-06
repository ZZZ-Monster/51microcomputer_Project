#include <REGX52.H>


sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;


//启动信号
void I2C_Start(void)
{
	I2C_SCL=1;
	I2C_SDA=1;
	I2C_SDA=0;
	I2C_SCL=0;
}



//停止信号
void I2C_Stop(void)
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}




//发送一个字节
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}
}

//接收一个字节
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte;
	I2C_SDA=1;    //主机在接收之前，需要释放SDA，置1
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;
		if(I2C_SDA){Byte=Byte|(0x80>>i);}
		I2C_SCL=0;
	}
	return Byte;
}



//发送应答信号
void I2C_SendAck(unsigned char AckByte)   //应答一位0或1  0指应答，1指非应答
{
	I2C_SDA=AckByte;
	I2C_SCL=1;
	I2C_SCL=0;
}



//接收应答信号
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA=1;               //主机在接收之前，需要释放SDA，置1
	I2C_SCL=1;
	AckBit=I2C_SDA;
	I2C_SCL=0;
	return 	AckBit;
}













