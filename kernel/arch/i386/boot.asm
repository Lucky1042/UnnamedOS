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

section .data
%include "arch/i386/gdt.asm"

; Declare the stack
section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text



global _start:function (_start.end - _start)
_start:
	cli
	; Set the stack pointer register to the top of the stack
	mov esp, stack_top

	extern _init
	call _init

	lgdt [gdt_descriptor]
	mov eax, cr0 ; copy cr0 register to eax
	or eax, 0x1 ; set the first bit
	mov cr0, eax ; update cr0 with eax
	jmp 0x08:.gdt_jmp

.gdt_jmp:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp .gdt_jmp2

.gdt_jmp2:
	; setup the IDT
	extern idt_setup
	call idt_setup
	extern idtp
	lidt [idtp]

	extern PICInit
	call PICInit

	sti

	; Call the main kernel
	extern kmain
	call kmain
	
	; Hang the os once it's done doing everything
.hang	nop
	jmp .hang
.end:
