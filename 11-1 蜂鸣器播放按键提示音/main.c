#include <REGX52.H>

#include "delay.H"
#include "matrixkey.H" 
#include "Nixie.H"  
#include "Buzzer.H"  


unsigned char Number;


void main()
{
	Nixie(1,0);
	while(1)
	{
		Number=matrixkey();
		if(Number)
		{
			Buzzer_Time(100);
			Nixie(1,Number);
		}
	}
}