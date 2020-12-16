#include <stdio.h>
#include <stdint.h>
#include <stddef.h>


extern "C" void exception_handler(int e)
{
	printf("Exception %c\n", (unsigned char)e);
}
