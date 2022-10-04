# Definitions for constants
CC=gcc
CFLAGS=-I.

# This will create your final output using .o compiled files
make: main.o stack.o getch.o getop.o
	$(CC) $(CFLAGS) -o main main.o stack.o getch.o getop.o

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

getch.o: getch.c
	$(CC) $(CFLAGS) -c getch.c

getop.o: getop.c
	$(CC) $(CFLAGS) -c getop.c

# This will compile main.c with its dependency
main.o: main.c calc.h
	$(CC) $(CFLAGS) -c main.c

# This will clean or remove compiled files so you can start fresh
clean:
	rm -f *.o *.exe