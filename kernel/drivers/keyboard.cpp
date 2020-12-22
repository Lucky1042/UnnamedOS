#include <kernel/intio.h>
#include <kernel/tty.h>
#include <stdbool.h>
#include <stdio.h>

/* Scan code set 2 */
const unsigned short scset2[]{

	0x01

};

void clearIRQMask(unsigned char);

void keyboardInit()
{
	clearIRQMask(1);
	outb(0x60, 0xF4);
	inb(0x60);
	//outb(0x60, 0xF0);
	//outb(0x60, 0x02);
	//inb(0x60);
}

void keyboardWrite(short scancodes)
{
	inb(0x60);
	for (short i = 0; i < sizeof(scset2); i++)
	{
		if (scancodes == scset2[i])
		{
			printf("a\n");
		}
	}
}

void sendKbdCommand()
{
	
}
