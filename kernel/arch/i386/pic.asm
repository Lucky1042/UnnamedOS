PIC1_COMMAND	equ 0x20
PIC1_DATA	equ (0x20 + 1)
PIC2_COMMAND	equ 0xA0
PIC2_DATA	equ (0xA0+1)

ICW1_ICW4	equ 0x01 ; ICW4 not needed
ICW_SINGLE	equ 0x02 ; Cascade mode
ICW1_INTERVAL4	equ 0x04 ; Call address interval 4 (8)
ICW1_LEVEL	equ 0x08 ; Edge mode
ICW1_INIT	equ 0x10 ; Initialization

ICW4_8086	equ 0x01 ; 8086 mode
ICW4_AUTO	equ 0x02
ICW4_BUF_SLAVE	equ 0x08
ICW4_BUF_MASTER	equ 0x0C
ICW4_SFNM	equ 0x10

global pic_remap

pic_remap:
	xchg bx, bx
	pusha
	in eax, (PIC1_DATA)
	push eax
	in eax, (PIC2_DATA)
	push eax
	
	xchg bx, bx

	; Initialize the pic
	mov eax, (ICW1_INIT | ICW1_ICW4)
	out PIC1_COMMAND, eax
	out PIC2_COMMAND, eax

	; Set the offset
	mov eax, 0x20
	out PIC1_DATA, eax
	mov eax, 0x28
	out PIC2_DATA, eax
	mov eax, 4
	out PIC1_DATA, eax
	mov eax, 2
	out PIC2_DATA, eax


	mov eax, ICW4_8086
	out PIC1_DATA, eax
	out PIC2_DATA, eax

	xchg bx, bx

	pop eax
	out PIC2_DATA, eax
	pop eax
	out PIC1_DATA, eax

	popa
	xchg bx, bx
	ret
