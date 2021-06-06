#include <REGX52.H>

sbit XPT2046_CS=P3^5;
sbit XPT2046_DCLK=P3^6;
sbit XPT2046_DIN=P3^4;
sbit XPT2046_DOUT=P3^7;


unsigned int XPT2046_readAD(unsigned char Command)
{
	unsigned char i;
	unsigned int ADvalue;
	XPT2046_DCLK=0;    //初始化（不初始化也行）
	XPT2046_CS=0;

	for(i=0;i<8;i++)
	{
		XPT2046_DIN=Command&(0x80>>i);	//把Command的位数依次给DIN
		XPT2046_DCLK=1;
		XPT2046_DCLK=0;
	}
	for(i=0;i<16;i++)
	{
		XPT2046_DCLK=1;
		XPT2046_DCLK=0;
		if(XPT2046_DOUT){ADvalue|=(0x8000>>i);}		//依次制高电平       0或1=1
	}
		
	XPT2046_CS=1;
	return ADvalue>>8;
}



















