#include <stdio.h>
#include <kernel/intio.h>

/*
 * Handles irq calls
 */

extern void irq0_handler(void) {
	static int count = 0;
	if (count++ >= 100000) {
		printf("%s", count);
		count = 0;
	} else
		++count;
	outb(0x20, 0x20);
}

extern void irq1_handler(void) {
	outb(0x20, 0x20);
}
