MESALIB = ..\..\lib

CFLAGS= /O2 /D__MSC__ /DFX /D__WIN32__ /DWIN32 /I..\fxGLUT \
        /I..\..\include \
        /I$(MSVC)\include \

LINK=   /link $(MESALIB)\fxMesa.lib $(MESALIB)\fxGLU.lib \
        $(MESALIB)\fxGLUT.lib $(MESALIB)\fxTK.lib \
        glide2x.lib texus.lib kernel32.lib user32.lib gdi32.lib winmm.lib

LIB=$(MSVC)\lib

EXES =  teapot.exe fire.exe terrain.exe gears.exe tunnel.exe wave.exe isosurf.exe

all: $(EXES)

teapot.exe: teapot.c image.c dteapot.c shadow.c
        $(CC) $(CFLAGS) teapot.c image.c dteapot.c shadow.c $(LINK)

fire.exe: fire.c image.c
        $(CC) $(CFLAGS) fire.c image.c $(LINK)
        
terrain.exe: mesaland.c
        $(CC) $(CFLAGS) /oterrain.exe mesaland.c $(LINK)

gears.exe: gears.c
        $(CC) $(CFLAGS) gears.c $(LINK)

tunnel.exe: tunnel.c sources.c image.c
        $(CC) $(CFLAGS) tunnel.c sources.c image.c $(LINK)

wave.exe: wave.c
        $(CC) $(CFLAGS) wave.c $(LINK)
                                  
isosurf.exe: isosurf.c
        $(CC) $(CFLAGS) isosurf.c $(LINK)

