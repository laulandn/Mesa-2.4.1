#
# Makefile for the Voodoo demos
#

CC=gcc
LINKER=gcc
COPTS=-O3 -fomit-frame-pointer -m486 -Wall -pipe -I../../include -I../../glut-3.5/include -DFX
LINKOPTS=-L../../lib -L../../glut-3.5/lib/glut -L/usr/local/glide/lib -L/usr/X11R6/lib -lglut -lMesaGLU -lMesaGL -lMesatk -lXi -lXmu -lXext -lX11 -lm  -lglide2x -ltexus

all: tunnel teapot fire terrain gears wave isosurf

tunnel: tunnel.o image.o sources.o
	$(LINKER) $(COPTS) $(OBJS) $^ -o $@ $(LINKOPTS)

teapot: teapot.o image.o dteapot.o shadow.o
	$(LINKER) $(COPTS) $(OBJS) $^ -o $@ $(LINKOPTS)

fire: fire.o image.o
	$(LINKER) $(COPTS) $(OBJS) $^ -o $@ $(LINKOPTS)

terrain: mesaland.o
	$(LINKER) $(COPTS) $(OBJS) $^ -o $@ $(LINKOPTS)

gears: gears.o
	$(LINKER) $(COPTS) $(OBJS) $^ -o $@ $(LINKOPTS)

wave: wave.o
	$(LINKER) $(COPTS) $(OBJS) $^ -o $@ $(LINKOPTS)

isosurf: isosurf.o
	$(LINKER) $(COPTS) $(OBJS) $^ -o $@ $(LINKOPTS)

clean:
	rm -f *.o tunnel teapot fire terrain gears wave isosurf

%.o: %.c
	$(CC) -c $(COPTS) $< -o $@
