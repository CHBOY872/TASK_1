CC=gcc
CFLAGS=-Wall -ansi
CPP=g++
CPPFLAGS=-Wall
ISOSTD=-std=c++11
LIBS=-lgtest -lgtest_main -lpthread
SRCMODULES=StringList.c
HDRMODULES=$(SRCMODULES:.c=.h)
OBJMODULES=$(SRCMODULES:.c=.o)

%.o: %.c %.h
	$(CC) $(CFLAGS) -g $< -c -o $@

main: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) -g $^ -o $@

test: test.cpp $(OBJMODULES)
	$(CPP) $(CPPFLAGS) -g $^ $(LIBS) -o $@ $(ISOSTD)

clean:
	rm *.o

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif


deps.mk: $(SRCMODULES)
	$(CC) -MM $^ > $@

runtest:
	make test
	make clean
all:
	make main
	make clean
