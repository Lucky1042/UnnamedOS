CC		= i686-elf-gcc
CXX		= i686-elf-g++
LD		= i686-elf-ld
AR		= i686-elf-ar
CFLAGS		:= -ffreestanding -Wall -Wextra -std=gnu11 -Iinclude
CXXFLAGS 	:= -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -D__is_libk
LDFLAGS	:= -ffreestanding -O2 -nostdlib -lgcc

C_SOURCES = $(shell find $(PWD) -type f -name '*.c')
HEADERS = $(shell find $(PWD)/include -type f -name '*.h')

OBJECTS = ${C_SOURCES:.c=.o}

all: libk.a

libk.a: ${OBJECTS}
	$(info [INFO] Creating libk.a)
	$(AR) rcs $@ $(OBJECTS)

%.o: %.c ${HEADERS}
	$(info [INFO] Compiling $@)
	$(CC) -c $< -o $@ $(CFLAGS) -D__is_libc


clean:
	rm *.a $(OBJECTS)
