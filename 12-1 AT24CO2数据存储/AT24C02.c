#include <REGX52.H>
#include "i2c.H"
#define	AT24C02_Address 0xa0   //默认写数据0xa0


//写字节	WordAddress为0~255 
void AT24C02_WriteByte(unsigned char WordAddress,Data)		
{
	I2C_Start();					//开始
	I2C_SendByte(AT24C02_Address);  //发送从机地址＋写
	I2C_ReceiveAck();				//接收应答
	I2C_SendByte(WordAddress);      //发送字地址
	I2C_ReceiveAck();				//接收应答
	I2C_SendByte(Data);             //发送数据
	I2C_ReceiveAck();				//接收应答
	I2C_Stop();						//结束

}
 
//读字节
unsigned char AT24C02_ReadByte(unsigned char WordAddress)		  
{
	unsigned char Data;
	I2C_Start();					//开始
	I2C_SendByte(AT24C02_Address);  //发送从机地址＋写
	I2C_ReceiveAck();				//接收应答
	I2C_SendByte(WordAddress);      //发送字地址
	I2C_ReceiveAck();				//接收应答
	I2C_Start();					//开始
	I2C_SendByte(AT24C02_Address|0x01);  //发送从机地址＋读	   读为0xa1
	I2C_ReceiveAck();				//接收应答
	Data=I2C_ReceiveByte();			 //接收数据
	I2C_SendAck(1);                  //不发送应答
	I2C_Stop();						//结束
	return Data;	
}







