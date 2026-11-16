
#CC=m68k-apple-macos-gcc
#CXX=m68k-apple-macos-g++
#CC=powerpc-apple-macos-gcc
#CXX=powerpc-apple-macos-g++

CFLAGS= -I../../include
LDFLAGS=-L../.. -lglut -lMesaOpenGLUtility -lMesaOpenGLLibrary -lm -L/opt/local/lib

OBJS=$(subst .c,.o,$(wildcard *.c)) $(subst .cpp,.o,$(wildcard *.cpp))

.cpp.o:
	$(CXX) $(CFLAGS) -c -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(OBJS)
	$(CXX) -o walker $(OBJS) $(LDFLAGS)
#	../bin2app.sh walker
#	$(CC) -o walker $(OBJS) $(LDFLAGS)
#	$(HOME)/sdl2macos9/xcoff2app.sh walker

clean:
	rm -f *.o *.bin *.pef *.APPL *.dsk *.gdb walker
