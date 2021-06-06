
#ifndef __DS1302_H__
#define __DS1302_H__

void DS1302_Init(void);
unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_WriteByte(unsigned char Command,Data);
void DS1302_ReadTime(void);
void DS1302_SetTime(void);
extern unsigned char DS1302_Time[];	  //年、月、日、时、分、秒、星期


#endif