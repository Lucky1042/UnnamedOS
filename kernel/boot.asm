; Declare multibot constants
MBALIGN		equ 1 << 0
MEMINFO		equ 1 << 1
FLAGS		equ MBALIGN | MEMINFO
MAGIC		equ 0x1BADB002
CHECKSUM	equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; Declare the stack
section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	
	; Set the stack pointer register to the top of the stack
	mov esp, stack_top

	; Call the main kernel
	extern kmain
	call kmain
	
	; Hang the os once it's done doing everything
	cli
.hang	hlt
	jmp .hang
.end:
