
AR=m68k-apple-macos-ar
RANLIB=m68k-apple-macos-ranlib
#AR=powerpc-apple-macos-ar
#RANLIB=powerpc-apple-macos-ranlib


all:
	make -i -C AGL/Sources/aglDD
	make -C AGL/Sources
	make -C GL/Sources
	make -C GLU/Sources
	make -C AUX?TK/Source
	make -C GLUT/Source?Common
	
lib:
	$(AR) rcv libOpenGLLibrary.a AGL/Sources/*.o AGL/Sources/aglDD/*.o GL/Sources/*.o
	$(RANLIB) libOpenGLLibrary.a
	$(AR) rcv libOpenGLUtility.a GLU/Sources/*.o
	$(RANLIB) libOpenGLUtility.a

clean:
	rm -f *.a
	rm -f */*/*.o */*/*.a
	rm -f */*/*/*.o */*/*/*.a
