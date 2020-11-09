; gdt.asm
; GDT is defined here

gdt_start:

gdt_null: ; Null segment
	dd 0x0
	dd 0x0

gdt_kcode: ; Kernel code segment. Kernel has seperate segment from users for ring level
	; flag and access byte description on osdev wiki
	dw 0xffff ; low limit
	dw 0x0 ;low base
	db 0x0 ; mid base
	db 10011010b ; order (reversed): ac, rw, dc, ex, s, privl, pr 
	db 11001111b ; flags then limit. order (reversed): 0, 0, size bit, granularity bit
	db 0x0 ; high limit

gdt_kdata: ; same as gdt_kcode but for the data segment
	dw 0xffff ;low limit
	dw 0x0 ;low base
	db 0x0 ;mid base
	db 10010010b ; order: same as code seg. changed for data seg
	db 11001111b ; same as kcode
	db 0x0

gdt_end:

gdt_descriptor: ; describes the gdt to the lgdt register
	dw gdt_end - gdt_start - 1

	dd gdt_start

CODE_SEG equ gdt_kcode - gdt_start
DATA_SEG equ gdt_kdata - gdt_start
