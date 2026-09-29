
AR=m68k-apple-macos-ar
RANLIB=m68k-apple-macos-ranlib
#AR=powerpc-apple-macos-ar
#RANLIB=powerpc-apple-macos-ranlib


all:
	make -f Makefile.r68 -C AGL/Sources/aglDD
	make -f Makefile.r68 -C AGL/Sources
#	make -f Makefile.r68 -C GL/Sources
#	make -f Makefile.r68 -C GLU/Sources
	make -f Makefile.r68 -C AUX:TK/Source
	make -f Makefile.r68 -C Stub\ Libs
#	make -f Makefile.r68 -C GLUT/Source\ Common
#	make -f Makefile.r68 -i -C GLUT/Source\ Mac
	make -f Makefile.r68 lib
	
lib:
	rm -f *.a
	cp */*/*.a .
#	$(AR) rcv libOpenGLLibrary.a AGL/Sources/*.o AGL/Sources/aglDD/*.o GL/Sources/*.o
#	$(RANLIB) libOpenGLLibrary.a
#	$(AR) rcv libOpenGLUtility.a GLU/Sources/*.o
#	$(RANLIB) libOpenGLUtility.a
#	$(AR) rcv libglut_pp.a GLUT/Source\ Common/*.o GLUT/Source\ Mac/*.o
#	$(RANLIB) libglut_pp.a
#	$(AR) rcv libglut.a GLUT_apple/*.o
#	$(RANLIB) libglut.a

install:
#	make -f Makefile.r68 lib
#	cp libOpenGLLibrary.a libOpenGLUtility.a libglut.a $(HOME)/Retro68-build/toolchain/m68k-apple-macos/lib/.

clean:
	make -f Makefile.r68 -C AGL/Sources/aglDD clean
	make -f Makefile.r68 -C AGL/Sources clean
	make -f Makefile.r68 -C AUX:TK/Source clean
	make -f Makefile.r68 -C Stub\ Libs clean
	rm -f *.a */*.a
	rm -f */*/*.o */*/*.a
	rm -f */*/*/*.o */*/*/*.a
