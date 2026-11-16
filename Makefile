
#AR=m68k-apple-macos-ar
RANLIB=ranlib
#AR=powerpc-apple-macos-ar
#RANLIB=powerpc-apple-macos-ranlib


all:
	make -f Makefile -C agl-mini
	make -f Makefile -C src
	make -f Makefile -C src-glu
	make -f Makefile -C src-aux
	make -i -f Makefile -C src-tk
	make -i -f Makefile -C util
#	make -f Makefile -C GLUT_apple
#	make -f Makefile -C Library\ Sources
#	cp Library\ Sources/*a .
	rm -f *.a
	cp */*.a .
	$(AR) rcv libMesaOpenGLLibrary.a src/*.o agl-mini/*.o 
	$(RANLIB) libMesaOpenGLLibrary.a
	$(AR) rcv libMesaOpenGLUtility.a src-glu/*.o
	$(RANLIB) libMesaOpenGLUtility.a
	make -f Makefile -C Examples
	make -i -f Makefile -C book
	make -i -f Makefile -C demos
	make -i -f Makefile -C samples

install:
	make -f Makefile lib
	# NOTE: Do NOT copy the include files!
#	cp *.a $(HOME)/Retro68-build/toolchain/m68k-apple-macos/lib/.
	
clean:
	make -f Makefile -C agl-mini clean
	make -f Makefile -C src clean
	make -f Makefile -C src-glu clean
	make -f Makefile -C src-aux clean
	make -f Makefile -C src-tk clean
	make -f Makefile -C GLUT_apple clean
	make -f Makefile -C Library\ Sources clean
	make -f Makefile -C Examples clean
	make -f Makefile -C book clean
	make -f Makefile -C demos clean
	make -f Makefile -C samples clean
	make -f Makefile -C util clean
	rm -f *.a */*.a
