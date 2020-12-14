# Unnamed OS
Text

# How to build
This project requires a cross compiler with instructions to build here:
https://wiki.osdev.org/GCC_Cross-Compiler

NASM is also required for assembling which can be found here:
https://nasm.us

Make sure that the cross compiler is in the path

To build use

    make
    make grub

## Running

To run with qemu use:

    qemu-system-i386
    
To run with bochs use:

    bochs
