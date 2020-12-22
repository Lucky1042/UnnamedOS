#include <kernel/intio.h>
#include <stdio.h>
#include <float.h>

#include <pic.h>

bool testbool = false;
int timerCount = 0;
int divisor = 0;
void PITInit(unsigned char mode, int aDivisor)
{
	outb(0x43, mode);
	divisor = aDivisor;
}

void setPITDivisor(int aDivisor)
{
	divisor = aDivisor;
}

extern "C" void pit_handler()
{
	++timerCount;
	if (timerCount == divisor) 
	{
		timerCount = 0;
		printf("a\n");
	}
	

	if (testbool)
	{
		printf("a");
		testbool = false;
	}
	else
	{
		printf("b");
		testbool = true;
	}
	printf("c");

	outb(0x20, 0x20);
}

