#include<reg51.h>
#define uchar unsigned char
#define TR 1
uchar buf[10]={ 0x01,0x02,0x03,0x04,0x05,
0x063,0x07,0x08,0x09,0x0a };
uchar sum;
void send(void);
void receive(void);
void init(void)
{
	TMOD=0x20;
	TH1=0xF4;
	TL1=0xF4;
	PCON=0x00;
	SCON=0x50;
	TR1=1;
}
void main(void)
{
	init( );
	if(TR==0)
	{
		send( );
	}
	else if(TR==1)
	{
		 receive(  );
	}
}
void delay(unsigned int i)
{
	unsigned char j;
	for(;i>0;i--)
	for(j=0;j<125;j++)
	;
}
void send(void)
{
	uchar i;
	do
	{
		delay(1000);
		SBUF=0xaa;
		while(TI==0);
		while(RI==0);
	}while(SBUF!=0xbb);
	do
	{
		sum=0;
		for(i=0;i<10;i++)
		{
			delay(1000);
			SBUF=buf[i];
			sum+=buf[i];
			while(TI==0);
			TI=0;
		}
		delay(1000);
		SBUF=sum;
		while(TI==0);
		TI=0;
		while(RI==0);
		RI=0;
	}while(SBUF==0xFF);
	while(1);
}
void receive(void)
{
	uchar i;
	RI=0;
	while(RI==0);
	RI=0;
	while(SBUF!=0xaa);
	SBUF=0xBB;
	while(TI==0);
	TI=0;
	sum=0;
	for(i=0;i<10;i++)
	{
		while(RI==0);
		RI=0;
		buf[i]=SBUF;
		sum+=buf[i];
	}
	while(RI==0);
	RI=0;
	if(SBUF==sum)
	{
		SBUF=0x00;
	  while(TI==0);
	  TI=0;
}
else
{
	SBUF=0xFF;
	while(TI==0);
	TI=0;
}
}


