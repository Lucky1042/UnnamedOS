; IDT structure. ISR is implemented in idt.asm. IDT is loaded in boot.asm .text section

extern load_idt

section .data

idt_start:
; isrstub is for interrupts with no isrx function

int0:
	; #GP
	dw isr0
	dw 0x0008
	db 0x00
	db 11100001b
	dw 0x0000

idt_end:

idt_info:
	dw idt_end - idt_start - 1
	dd idt_start

section .text

isr0:
	iret

load_idt:
	pusha
	mov [idt_info], ebx
	lidt [ebx]
	popa
	ret
