# Makefile for CS 413 32-bit ARM Assembly Programs
# On native ARMv7/ARM32 Linux (e.g., Raspberry Pi / UAH Lab): make all
# On x86_64 Linux with cross-compiler: make AS=arm-linux-gnueabihf-as CC=arm-linux-gnueabihf-gcc all

AS = as
CC = gcc
LDFLAGS = -z noexecstack

all: lab2 lab3

lab2: lab2_stack_calculator/lab2.s
	$(AS) -o lab2.o lab2_stack_calculator/lab2.s
	$(CC) $(LDFLAGS) -o lab2 lab2.o

lab3: lab3_coffee_maker_fsm/lab3.s
	$(AS) -o lab3.o lab3_coffee_maker_fsm/lab3.s
	$(CC) $(LDFLAGS) -o lab3 lab3.o

clean:
	rm -f lab2 lab3 *.o

.PHONY: all clean
