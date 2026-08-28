CFLAGS	      = /O /D__MSC__ /DFX /D__WIN32__ /DFULL_SCREEN \
		/DWIN32 /I.. /I..\..\..\include \
                /I..\..\..\src \
                /I$(MSVC)\include

OBJS	      = glut_event.obj \
		glut_8x13.obj \
		glut_9x15.obj \
		glut_bitmap.obj \
		glut_bwidth.obj \
		glut_cindex.obj \
		glut_cursor.obj \
		glut_dials.obj \
		glut_ext.obj \
		glut_fullscrn.obj \
		glut_get.obj \
		glut_hel10.obj \
		glut_hel12.obj \
		glut_hel18.obj \
		glut_init.obj \
		glut_input.obj \
		glut_menu.obj \
		glut_mesa.obj \
		glut_modifier.obj \
		glut_mroman.obj \
		glut_overlay.obj \
		glut_roman.obj \
		glut_shapes.obj \
		glut_space.obj \
		glut_stroke.obj \
		glut_swidth.obj \
		glut_tablet.obj \
		glut_teapot.obj \
		glut_tr10.obj \
		glut_tr24.obj \
		glut_util.obj \
		glut_vidresize.obj \
		glut_warp.obj \
		glut_win.obj \
		glut_winmisc.obj \
		layerutil.obj 
#	strokegen.obj \
#	strokelex.obj

PROGRAM       = ..\..\..\lib\fxGLUT.lib

all:		$(PROGRAM)

$(PROGRAM):     $(OBJS)
		lib  /verbose /OUT:$(PROGRAM) $(OBJS)
