#include <stdio.h>
#include <kernel/tty.h>

extern "C" void kmain() {
	terminal_initialize();
	printf("Hello world!\n");
}

