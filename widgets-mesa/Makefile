
#AR=m68k-apple-macos-ar
RANLIB=ranlib
#AR=powerpc-apple-macos-ar
#RANLIB=powerpc-apple-macos-ranlib


all:
	make -i -f Makefile -C src
	make -i -f Makefile -C demos
	make -i -f Makefile lib

lib:
	rm -f *.a
	cp */*.a .
	
clean:
	make -f Makefile -C src clean
	make -f Makefile -C demos clean
	rm -f *.a */*.a
