CC		= i686-elf-gcc
CXX		= i686-elf-g++
LD		= i686-elf-ld
AR		= i686-elf-ar
NASM		= nasm
CFLAGS		= -ffreestanding -Wall -Wextra -std=gnu11 -Iinclude
CXXFLAGS 	= $(CFLAGS) -fno-exceptions -fno-rtti -D__is_libk
LDFLAGS	= -ffreestanding -O2 -nostdlib -lgcc
NASMFLAGS = -felf32

C_SOURCES = $(shell find $(PWD) -type f -name '*.c')
HEADERS = $(shell find $(PWD)/include -type f -name '*.h')
OBJECTS = ${C_SOURCES:.c=.o}

SYSROOT = $(PWD)/../../sysroot
CXXFLAGS += --sysroot="$(SYSROOT)" -isystem="/usr/include"

all: libc.a

libc.a: ${OBJECTS}
	$(info [INFO] Creating libc.a)
	$(AR) rcs $@ $(OBJECTS)

%.o: %.c ${HEADERS}
	$(info [INFO] Compiling $@)
	$(CC) -c $< -o $@ $(CXXFLAGS) -D__is_libc

install: install-headers install-lib

install-headers:
	cp --preserve=timestamps -r include/ $(SYSROOT)/usr/

install-lib: libc.a
	cp -r $< $(SYSROOT)/usr/lib

clean:
	rm *.a $(OBJECTS)
