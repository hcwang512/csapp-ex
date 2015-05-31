CC = gcc
CFLAGS = -O2 -Wall -I .

# This flag includes the Pthreads library on a linux box.
LIB = -lpthread

all: tiny

tiny: tiny.c csapp.o
	$(CC) $(CFLAGS) -o tiny tiny.c csapp.o $(LIB)

csapp.o:
	$(CC) $(CFLAGS) -c csapp.c

clean:
	rm -rf *.o tiny

