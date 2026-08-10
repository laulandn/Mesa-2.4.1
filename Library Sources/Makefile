
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
	make -C Stub?Libs
	make -C GLUT/Source?Common
	make -i -C GLUT/Source?Mac
	
lib:
	$(AR) rcv libOpenGLLibrary.a AGL/Sources/*.o AGL/Sources/aglDD/*.o GL/Sources/*.o
	$(RANLIB) libOpenGLLibrary.a

clean:
	rm -f *.a
	rm -f */*/*.o */*/*.a
	rm -f */*/*/*.o */*/*/*.a
