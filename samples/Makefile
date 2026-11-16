
#CC=m68k-apple-macos-gcc
#CXX=m68k-apple-macos-g++
#CC=powerpc-apple-macos-gcc
#CXX=powerpc-apple-macos-g++

CFLAGS= -I../include -I/opt/local/include
LDFLAGS=-lglu -lgl -lglut -lm -L/opt/local/include


OBJS=$(subst .c,.o,$(wildcard *.c))


.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<


all: $(OBJS) accum bitmap1 bitmap2 blendeq blendxor copy cursor depth eval fog font line logo nurb oglinfo olympic overlay point prim quad select shape speed sphere star stencil stretch texture tri wave
#	$(CC) -o logo.code.bin $(OBJS) $(LDFLAGS)
#	$(CC) -o bluepony $(OBJS) $(LDFLAGS)
#	../xcoff2app.sh logo

clean:
	rm -f *.o *.bin *.pef *.APPL *.dsk *.gdb
	rm -f accum bitmap1 bitmap2 blendeq blendxor copy cursor depth eval fog font line logo nurb oglinfo olympic overlay point prim quad select shape speed sphere star stencil stretch texture tri wave