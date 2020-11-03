/*Tell the bootloader what symbol to start excecution at*/
ENTRY(_start)

/*Tell the linker where the sections will be in the final image*/
SECTIONS
{
	/*Begin putting sections at 1MiB*/
	. = 1M;

	/*Put the multiboot header first. Then the .text section(code)*/
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/*read only data*/
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* initialized read write data */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	
	/* uninitialized read write data and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

}
