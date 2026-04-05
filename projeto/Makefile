CC = gcc
CFLAGS = -Wall -O3

all: eliza

eliza: eliza.o elib.o
	$(CC) $(CFLAGS) -o eliza eliza.o elib.o

eliza.o: eliza.c elib.h
	$(CC) $(CFLAGS) -c eliza.c

elib.o: elib.c elib.h
	$(CC) $(CFLAGS) -c elib.c

clean:
	rm -f *.o eliza