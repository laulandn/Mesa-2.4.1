
#CC=m68k-apple-macos-gcc
#CXX=m68k-apple-macos-g++
#CC=powerpc-apple-macos-gcc
#CXX=powerpc-apple-macos-g++

CFLAGS= -I../include -I/opt/local/include
LDFLAGS=-lglu -lgl -lglut -lm -L/opt/local/include


OBJS=$(subst .c,.o,$(wildcard *.c))


.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<


all: $(OBJS)


bounce:	bounce.o
	$(CXX) -o bounce bounce.o $(LDFLAGS)
#	../bin2app.sh bounce

clearspd:	clearspd.o
	$(CXX) -o clearspd clearspd.o $(LDFLAGS)
#	../bin2app.sh clearspd

gamma:	gamma.o
	$(CXX) -o gamma gamma.o $(LDFLAGS)
#	../bin2app.sh gamma

gears:	gears.o
	$(CXX) -o gears gears.o $(LDFLAGS)
#	../bin2app.sh gears

glxdemo:	glxdemo.o
	$(CXX) -o glxdemo glxdemo.o $(LDFLAGS)
#	../bin2app.sh glxdemo

glxpixmap:	glxpixmap.o
	$(CXX) -o glxpixmap glxpixmap.o $(LDFLAGS)
#	../bin2app.sh glxpixmap

isosurf:	isosurf.o
	$(CXX) -o isosurf isosurf.o $(LDFLAGS)
#	../bin2app.sh isosurf

morph3d:	morph3d.o
	$(CXX) -o morph3d morph3d.o $(LDFLAGS)
#	../bin2app.sh morph3d

offset:	offset.o
	$(CXX) -o offset offset.o $(LDFLAGS)
#	../bin2app.sh offset

osdemo:	osdemo.o
	$(CXX) -o osdemo osdemo.o $(LDFLAGS)
#	../bin2app.sh osdemo

reflect:	reflect.o
	$(CXX) -o reflect reflect.o $(LDFLAGS)
#	../bin2app.sh reflect

shape:	shape.o
	$(CXX) -o shape shape.o $(LDFLAGS)
#	../bin2app.sh shape

spectex:	spectex.o
	$(CXX) -o spectex spectex.o $(LDFLAGS)
#	../bin2app.sh spectex

spin:	spin.o
	$(CXX) -o spin spin.o $(LDFLAGS)
#	../bin2app.sh spin

stex3d:	stex3d.o
	$(CXX) -o stex3d stex3d.o $(LDFLAGS)
#	../bin2app.sh stex3d

tess_demo:	tess_demo.o
	$(CXX) -o tess_demo tess_demo.o $(LDFLAGS)
#	../bin2app.sh tess_demo

test0:	test0.o
	$(CXX) -o test0 test0.o $(LDFLAGS)
#	../bin2app.sh test0

texcyl:	texcyl.o
	$(CXX) -o texcyl texcyl.o $(LDFLAGS)
#	../bin2app.sh texcyl

texobj:	texobj.o
	$(CXX) -o texobj texobj.o $(LDFLAGS)
#	../bin2app.sh texobj

trispd:	trispd.o
	$(CXX) -o trispd trispd.o $(LDFLAGS)
#	../bin2app.sh trispd

vgears:	vgears.o
	$(CXX) -o vgears vgears.o $(LDFLAGS)
#	../bin2app.sh vgears

vindex:	vindex.o
	$(CXX) -o vindex vindex.o $(LDFLAGS)
#	../bin2app.sh vindex

vtest:	vtest.o
	$(CXX) -o vtest vtest.o $(LDFLAGS)
#	../bin2app.sh vtest

winpos:	winpos.o
	$(CXX) -o winpos winpos.o $(LDFLAGS)
#	../bin2app.sh winpos

xdemo:	xdemo.o
	$(CXX) -o xdemo xdemo.o $(LDFLAGS)
#	../bin2app.sh xdemo


clean:
	rm -f *.o *.bin *.pef *.APPL *.dsk *.gdb
	rm -f bounce clearspd gamma gears glxdemo glxpixmap isosurf morph3d offset osdemo reflect shape spectex spin stex3d tess_demo test0 texcyl texobj trispd vgears vindex vtest winpos xdemo