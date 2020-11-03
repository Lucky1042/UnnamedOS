#include <stdint.h>
#include <stddef.h>

extern "C" void kmain() {
	char* videomem = (char*) 0xB8000;
	*videomem = 'X';
}
