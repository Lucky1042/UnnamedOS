#include <stdio.h>
#include <kernel/tty.h>

extern "C" void kmain(void) {
	terminal_initialize();
}
