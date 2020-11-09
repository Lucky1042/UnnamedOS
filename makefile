# The makefile for my OS 

OS_NAME		:= myos
ARCH		= i386
SYSROOT = $(PWD)/sysroot

# Variables for easy access of tools like gcc and nasm
CC		= i686-elf-gcc
CXX		= i686-elf-g++
LD		= i686-elf-ld 
NASM		= nasm
QEMU		:= qemu-system-i386
ASMFLAGS	:= -felf32
#CXXFLAGS 	:= -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
#LDFLAGS	:= -ffreestanding -O2 -nostdlib 

.PHONY: all kernel.bin multiboot_test clean

all: kernel.bin

kernel.bin:
	$(info [INFO] Building kernel)
	$(MAKE) -C ./kernel/ ARCH=$(ARCH) PREFIX=$(PWD) CC=$(CC) CXX=$(CXX) LD=$(LD) NASM=$(NASM) SYSROOT=$(SYSROOT)

grub: kernel.bin grub.cfg
	grub-file --is-x86-multiboot $<
	cp kernel.bin isodir/boot
	cp grub.cfg isodir/boot/grub
	grub-mkrescue -o os.iso isodir

qemu: grub
	$(QEMU) -no-reboot -s -m 512 -hda os.iso

install: install-headers

install-headers:
	$(MAKE) -C ./kernel/ install-headers SYSROOT=$(SYSROOT)

clean:
	@$(MAKE) -C ./kernel/ clean SYSROOT=$(SYSROOT)
