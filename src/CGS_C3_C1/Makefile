CC=gcc
CFLAGS=-I. 
DEPS = mymemory.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shell:	shell.o mymemory.o
	$(CC) -o shell shell.o mymemory.o
