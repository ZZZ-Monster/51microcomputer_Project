#include <REGX52.H>
#include "delaytime10us.h"
#include "motorrun.h"

sbit key=P2^0;

void main()
{
	while(1)
	{
	    if(key==0)
		{
		 	MotorRun(4096/2,1,100);
		}
		else
		{
			MotorRun(4096/2,0,100);				//	nangle=4096为一圈；	drct=0为逆时针转动，drct=1为顺时针转动；  speed转速75`400；
		}
		delay(50000);		//停止  延时500ms
	}
}

