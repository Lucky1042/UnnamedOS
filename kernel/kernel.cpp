#include <stdio.h>
#include <kernel/tty.h>

void keyboardInit();
void PS2Init();
void PITInit(unsigned char, int);

extern "C" void kmain(void) {
	//PITInit(0x3E, 100);
	PS2Init();
	terminal_initialize();
	keyboardInit();
	printf("Hello world!\n");
}
