#Makefile for Concurrent assignment 2

CC=gcc
CFLAGS=-pthread
PROGS=conc2


all: $(PROGS)

conc2: conc2.o
	$(CC) $(CFLAGS) -o conc2 conc2.o

conc2.o: conc2.c
	$(CC) $(CFLAGS) -c conc2.c

clean:
	rm -f $(PROGS) *.o *~
