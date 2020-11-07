# Kernel makefile

ifndef GAS
	GAS = i686-elf-as
endif

ifndef CXXFLAGS
	CXXFLAGS = -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -D__is_kernel
	CXXFLAGS += --sysroot="$(SYSROOT)"
	CXXFLAGS += -isystem="/usr/include"
endif

ifndef LDFLAGS
	LDFLAGS = -T linker.ld -ffreestanding -D__is_kernel
	LDFLAGS += --sysroot="$(SYSROOT)"
	LDFLAGS += -isystem="/usr/include"
endif

ifndef SYSROOT
	$(error No sysroot specified)
endif


LIBS = -nostdlib -lk -lgcc

#Find all the source files
CPP_SOURCES = $(shell find $(PWD)/kernel -type f -name '*.cpp')
HEADERS = $(shell find $(PWD) -type f -name '*.h')
ASMFILES = $(shell find $(PWD) -type f -name '*.asm')
GASFILES = $(wildcard *.s)
CRTBEGIN = $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND = $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)

OBJECTS = crti.o
OBJECTS += $(CRTBEGIN)
OBJECTS += ${CPP_SOURCES:.c=.o}
OBJECTS += ${ASMFILES:.asm=.o}
OBJECTS += $(CRTEND)
OBJECTS += crtn.o

.PHONY: all crt clean

all: crti.o crtn.o kernel.bin

kernel.bin: ${OBJECTS}
	$(info [INFO] Linking kernel)
	$(CXX) ${LDFLAGS} $(LIBS) -o ${PREFIX}/kernel.bin $^

%.o: %.cpp ${HEADERS}
	$(info [INFO] Compiling $<)
	$(CXX) ${CXXFLAGS} -c $< -o $@

%.o: %.asm
	$(info [INFO] Assembling assembly)
	$(NASM) $< -f elf -o $@

crti.o: 
	$(GAS) arch/$(ARCH)/crti.s -o $@

crtn.o: 
	$(GAS) arch/$(ARCH)/crtn.s -o $@

install-headers:
	cp -r --preserve=timestamps include $(SYSROOT)/usr

clean:
	$(info [INFO] Cleaning)
	#rm ${OBJECTS}
