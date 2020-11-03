# Kernel makefile

ifndef CXXFLAGS
	CXXFLAGS = -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti
endif

ifndef LDFLAGS
	LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc
endif

#Find all the source files
CPP_SOURCES = $(shell find $(PWD)/kernel -type f -name '*.cpp')
HEADERS = $(shell find $(PWD) -type f -name '*.h')
ASMFILES = $(shell find $(PWD) -type f -name '*.asm')

OBJECTS = ${CPP_SOURCES:.c=.o}
OBJECTS += ${ASMFILES:.asm=.o}

all: kernel.bin

kernel.bin: ${OBJECTS}
	$(info [INFO] Linking kernel)
	$(CXX) ${LDFLAGS} -o ${PREFIX}/kernel.bin $^

%.o: %.c ${HEADERS}
	$(info [INFO] Compiling C++)
	$(CXX) ${CXXFLAGS} -c $< -o $@

%.o: %.asm
	$(info [INFO} Assembling assembly)
	$(NASM) $< -f elf -o $@

clean:
	$(info [INFO] Cleaning)
	rm -rf ${OBJECTS}
