
#ifndef __DS18B20_One_Wire_H__
#define __DS18B20_One_Wire_H__
unsigned char OneWire_Init(void);
unsigned char OneWire_ReceiveByte(void);
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_ReceiveBit(void);
void OneWire_SendBit(unsigned char Bit);

#endif