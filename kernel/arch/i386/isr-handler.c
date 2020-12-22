#include <stdio.h>
#include <stdint.h>
#include <stddef.h>


extern "C" void exception_handler(int e)
{
	unsigned char errorcode[2]{((unsigned char) e) + 48};
	printf("Exception %s\n", errorcode);
}
