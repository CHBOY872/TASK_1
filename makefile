CC=gcc
CFLAGS=-Wall -ansi
SRCMODULES=StringList.c
HDRMODULES=$(SRCMODULES:.c=.h)
OBJMODULES=$(SRCMODULES:.c=.o)

%.o: %.c %.h
	$(CC) $(CFLAGS) -g $< -c -o $@

main: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) -g $^ -o $@