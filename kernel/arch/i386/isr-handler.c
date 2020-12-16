#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

extern "C" void exception_handler()
{
	printf("Exception\n");
}
