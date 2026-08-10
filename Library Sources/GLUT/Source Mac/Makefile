
#CC=powerpc-apple-macos-gcc
CC=m68k-apple-macos-gcc
#CXX=powerpc-apple-macos-g++
CXX=m68k-apple-macos-g++

.SUFFIXES: .cp

CFLAGS= -I../../../Headers

OBJS=$(subst .c,.o,$(wildcard *.c)) $(subst .cp,.o,$(wildcard *.cp))

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cp.o:
	$(CXX) $(CFLAGS) -c -o $@ $<


all: $(OBJS)

clean:
	rm -f *.o
