CC = gcc
CFLAGS = -Wall -O3

all: eliza

eliza: eliza.o elib.o dataman.o
	$(CC) $(CFLAGS) -o eliza eliza.o elib.o dataman.o

eliza.o: eliza.c elib.h
	$(CC) $(CFLAGS) -c eliza.c

elib.o: elib.c elib.h
	$(CC) $(CFLAGS) -c elib.c

dataman.o: dataman.c elib.h
	$(CC) $(CFLAGS) -c dataman.c

clean:
	rm -f *.o eliza