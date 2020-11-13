#include <kernel/intio.h>

extern "C" void pit_init(void) {
	outb(0x43, 0b00111100); //Initialize the pit (0x43)
}
