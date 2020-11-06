/* crti.S */
.section .init
.global _init
.type _init, @function
_init:
	push %ebp
	movl %esp, %ebp

.section .fini
.global _fini
.type _init, @function
_fini:
	push %ebp
	movl %esp, %ebp
