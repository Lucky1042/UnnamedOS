#include <kernel/intio.h>
#include <stdint.h>

extern "C" void Dev1Int();
void keyboardWrite(short);

void PS2Init()
{
	/* TODO: Implement ACPI to detect PS/2 devices */
	outb(0x64, 0xAD);
	outb(0x64, 0x60);
	//outb(0x64, 0x25);
	outb(0x64, 0xAE);
}

void Dev1Int()
{
	short scancodes = inb(0x60);
	keyboardWrite(scancodes);
	outb(0x20, 0x20);
}
