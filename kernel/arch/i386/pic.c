#include <kernel/intio.h>
#include <stdint.h>

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

void sendPicEOI(unsigned char irq)
{
	if(irq >= 8)
		outb(PIC2_COMMAND, PIC_EOI);
	outb(PIC1_COMMAND, PIC_EOI);
}

void setIRQMask(unsigned char IRQLine)
{
	uint16_t port;
	uint8_t value;

	if (IRQLine < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		IRQLine -= 8;
	}
	value = inb(port) | (1 << IRQLine);
	outb(port, value);
}

void clearIRQMask(unsigned char IRQLine)
{
	uint16_t port;
	uint8_t value;

	if (IRQLine < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		IRQLine -=8;
	}
	value = inb(port) & ~(1 << IRQLine);
	outb(port, value);
}

#define ICW1_ICW4 0x01 // ICW4
#define ICW1_SINGLE 0x02 // Single (cascade) mode
#define ICW1_INTERVAL4 0x04 // Call address interval 4 (8)
#define ICW1_LEVEL 0x08 // Level triggered (edge) mode
#define ICW1_INIT 0x10 // Initialization

#define ICW4_8086 0x01


extern "C" void PICInit()
{
	unsigned char a1, a2;

	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); //Initialize the pic
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

	outb(PIC1_DATA, 0x20); // Set master PIC offset to 0x20
	outb(PIC2_DATA, 0x28); // Set slave PIC offset to 0x28

	outb(PIC1_DATA, 4); // Tell master PIC there's a slave PIC at IRQ2
	outb(PIC2_DATA, 2); // Tell slave PIC its cascade identity

	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);

	/* Mask all IRQ lines until IRQs are used */ 
	for (char i = 0; i < 15; i++)
	{
		setIRQMask(i);
	}

	clearIRQMask(0);
}
