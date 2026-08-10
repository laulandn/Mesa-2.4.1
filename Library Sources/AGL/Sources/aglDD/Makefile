
CC=powerpc-apple-macos-gcc
#CC=m68k-apple-macos-gcc
CXX=powerpc-apple-macos-g++
#CXX=m68k-apple-macos-g++


CFLAGS= -I../../../../Headers -I../../../GL/Sources -I..

OBJS=$(subst .c,.o,$(wildcard *.c))

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<


all: $(OBJS)

clean:
	rm -f *.o
