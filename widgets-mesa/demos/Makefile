
#CC=m68k-apple-macos-gcc
#CXX=m68k-apple-macos-g++
#AR=m68k-apple-macos-ar
#RANLIB=m68k-apple-macos-ranlib
#CC=powerpc-apple-macos-gcc
#CXX=powerpc-apple-macos-g++
#AR=powerpc-apple-macos-ar
RANLIB=ranlib

CFLAGS= -I../include -I/opt/local/include

OBJS=$(subst .c,.o,$(wildcard *.c))


.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<


all: $(OBJS)

clean:
	rm -f *.o */*.o *.a
