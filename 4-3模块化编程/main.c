#include <REGX52.H>
#include "delay.h"
#include "Nixie.h"
void main()
{
	while(1)
	{
		Nixie(1,1);
//		delay(2);
		Nixie(2,2);
//		delay(2);
		Nixie(3,3);
//		delay(2);
		Nixie(4,4);
//		delay(2);
		Nixie(5,5);
//		delay(2);
		Nixie(6,6);
//		delay(2);
	}
}