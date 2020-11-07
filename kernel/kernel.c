#include <stdio.h>
#include <kernel/tty.h>

void kmain() {
	terminal_initialize();
	printf("Hello world!\n");
}

