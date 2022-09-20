CC=gcc
CFLAGS=-Wall -ansi
SRCMODULES=StringList.c
HDRMODULES=$(SRCMODULES:.c=.h)
OBJMODULES=$(SRCMODULES:.c=.o)

%.o: %.c %.h
	$(CC) $(CFLAGS) -g $< -c -o $@

main: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) -g $^ -o $@

clean:
	rm *.o

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif


deps.mk: $(SRCMODULES)
	$(CC) -MM $^ > $@

all:
	make main
	make clean