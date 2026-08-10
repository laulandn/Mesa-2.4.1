
AR=m68k-apple-macos-ar
RANLIB=m68k-apple-macos-ranlib
#AR=powerpc-apple-macos-ar
#RANLIB=powerpc-apple-macos-ranlib


all:
	make -C Library?Sources
	
clean:
	make -C Library?Sources clean
