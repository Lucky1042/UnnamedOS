#include <stdint.h>
#include <stddef.h>
/* idt.c 
 * Defines the IDT structure and loads it  */

// Base address is the address of the ISR function

/* Function prototypes for the ISR functions. IDT[0] to IDT[31] are reserved for hardware exceptions (i.e. Double fault, General protection fault, etc). Function prototypes use extern "C" function foo() due to using g++ for compiling C code. */
extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

struct idt_entry
{
	unsigned short offset_low;	// Lower half of base address
	unsigned short selector;	// Kernel segment goes here
	unsigned char always0;		// Always set to 0
	unsigned char flags;		// Type, S, DPL, Present
	unsigned short offset_high;	// Higher half of base address
}__attribute__((packed));

struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
}__attribute((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;
extern "C" void idt_load();

void idt_new_entry(unsigned char num, unsigned long offset, unsigned short sel, unsigned char flags)
{
	idt[num].offset_low = (offset & 0xFFFF);
	idt[num].selector = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
	idt[num].offset_high = (offset >> 16) & 0xFFFF;
}

/* Sets up the IDT  */
extern "C" void idt_setup() 
{
	/* Sets up IDT pointer */
	idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
	idtp.base = (unsigned int)idt;

	/* IDT entries are added using idt_new_entry(); 
	 * Flag order: Present, DPL, S, Type */
	idt_new_entry(6, (unsigned)isr6, 0x08, 0x8E);
	idt_new_entry(8, (unsigned)isr8, 0x08, 0x8E);
	idt_new_entry(11, (unsigned)isr11, 0x08, 0x8E);
	idt_new_entry(13, (unsigned)isr13, 0x08, 0x8E);
}
