# Top-level makefile for Mesa

# Mesa 3-D graphics library
# Version:  2.4
# Copyright (C) 1995-1997  Brian Paul
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free
# Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


# $Id: Makefile,v 1.31 1997/08/24 17:26:57 brianp Exp $

# $Log: Makefile,v $
# Revision 1.31  1997/08/24 17:26:57  brianp
# changed order of commands for openstep target (Pete French)
#
# Revision 1.30  1997/08/14 02:06:35  brianp
# updated version to 2.4, added linux-ppc config
#
# Revision 1.29  1997/06/30 22:45:14  brianp
# added sunos5-ultra, updated sunos5 cc flags (John Stone)
#
# Revision 1.28  1997/06/26 14:46:32  brianp
# added MESAFX.BAT to archive files
#
# Revision 1.27  1997/06/24 22:45:48  brianp
# added linux-alpha-elf config (Michael C. Vergallen)
#
# Revision 1.26  1997/06/21 15:38:28  brianp
# added hpux-gcc-sl config
#
# Revision 1.25  1997/06/20 04:01:43  brianp
# divided distribution into separate library and demo archives
#
# Revision 1.24  1997/05/29 23:58:56  brianp
# updated TAR_FILES list: removed MESADJ.BAT, added cygnus makefiles
#
# Revision 1.23  1997/05/27 03:03:13  brianp
# added linux-glide config
#
# Revision 1.22  1997/04/16 22:35:16  brianp
# added cygnus config, fixed a few bugs
#
# Revision 1.21  1997/04/03 03:50:07  brianp
# added lynxos config from Vik Sohal
#
# Revision 1.20  1997/04/03 03:45:08  brianp
# changed srctar stuff
#
# Revision 1.19  1997/03/14 00:23:53  brianp
# added STARTUP.MK and mesa3dfx to tar files
#
# Revision 1.18  1997/02/08 07:53:52  brianp
# added beos and osf1-sl configs
#
# Revision 1.17  1997/02/01 10:01:33  brianp
# replaced widgets-old with widgets-mesa
#
# Revision 1.16  1997/01/30 21:10:08  brianp
# src-tk/README was missing from tar file
#
# Revision 1.15  1997/01/30 18:52:12  brianp
# added linux-alpha config
#
# Revision 1.14  1997/01/04 06:19:46  brianp
# added openbsd config from Thomas Graichen
# added a few files to TAR_FILES for DOS/DJGPP from Charlie Wallace
#
# Revision 1.13  1996/12/18 18:19:04  brianp
# added -r flag (recurse) to zip command
#
# Revision 1.12  1996/12/18 18:15:28  brianp
# added xlib.opt to tar file, per Jouk Jansen
#
# Revision 1.11  1996/11/30 14:35:40  brianp
# fixed problem with openstep config
#
# Revision 1.10  1996/11/24 20:50:52  brianp
# removed windows2/ and nt/ from tar file
#
# Revision 1.9  1996/11/24 19:33:10  brianp
# added openstep config
#
# Revision 1.8  1996/11/14 01:42:45  brianp
# added MS-DOS driver files to TAR_FILES macro
#
# Revision 1.7  1996/11/14 01:13:50  brianp
# added rule to make a ZIP file
#
# Revision 1.6  1996/10/31 01:19:32  brianp
# incremented version to 2.1
#
# Revision 1.5  1996/10/31 01:13:02  brianp
# added VMS stuff
#
# Revision 1.4  1996/10/09 03:22:39  brianp
# added unixware-shared config
# removed old Amiga files from tar file list
#
# Revision 1.3  1996/09/27 17:30:40  brianp
# added windows2 subdirectory, removed README.WIN from tar files
#
# Revision 1.2  1996/09/26 22:42:32  brianp
# added linux-debug target
# added widgets-old and widgets-sgi to tar file list
#
# Revision 1.1  1996/09/12 00:39:00  brianp
# Initial revision
#


SHELL = /bin/sh


# To add a new configuration for your system add it to the list below
# then update the Make-config file.



default:
	@echo "Type one of the following:"
	@echo "  make aix                  for IBM RS/6000 with AIX"
	@echo "  make aix-sl               for IBM RS/6000, make shared libs"
	@echo "  make amiwin               for Amiga with SAS/C and AmiWin"
	@echo "  make amix                 for Amiga 3000 UX  SVR4 v2.1 systems"
	@echo "  make beos                 for BeOS with DR 8.2"
	@echo "  make bsdos                for BSD/OS from BSDI using GCC"
	@echo "  make cygnus               for Win95/NT using Cygnus-Win32"
	@echo "  make dgux                 for Data General"
	@echo "  make freebsd              for FreeBSD systems with GCC"
	@echo "  make gcc                  for a generic system with GCC"
	@echo "  make hpux                 for HP systems with HPUX"
	@echo "  make hpux-gcc             for HP systems with HPUX using GCC"
	@echo "  make hpux-sl              for HP systems with HPUX, make shared libs"
	@echo "  make hpux-gcc-sl          for HP systems with HPUX, GCC, make shared libs"
	@echo "  make irix4                for SGI systems with IRIX 4.x"
	@echo "  make irix5                for SGI systems with IRIX 5.x"
	@echo "  make irix5-dso            for SGI systems with IRIX 5.x, make DSOs"
	@echo "  make irix6-32             for SGI systems with IRIX 6.x, make 32-bit libs"
	@echo "  make irix6-32-dso         for SGI systems with IRIX 6.x, make 32-bit DSOs"
	@echo "  make irix6-n32            for SGI systems with IRIX 6.x, make n32-bit libs"
	@echo "  make irix6-n32-dso        for SGI systems with IRIX 6.x, make n32-bit DSOs"
	@echo "  make irix6-64             for SGI systems with IRIX 6.x, make 64-bit libs"
	@echo "  make irix6-64-dso         for SGI systems with IRIX 6.x, make 64-bit DSOs"

	@echo "  make linux                for Linux systems with GCC"
	@echo "  make linux-elf            for Linux systems, make ELF shared libs"
	@echo "  make linux-alpha          for Linux on Alpha systems"
	@echo "  make linux-alpha-elf      for Linux on Alpha systems, make ELF shared libs"
	@echo "  make linux-ppc            for Linux on PowerPC systems"
	@echo "  make linux-mondello       for Linux with prototype Cirrus Mondello card"
	@echo "  make linux-glide          for Linux with 3Dfx Glide driver"
	@echo "  make lynxos               for LynxOS systems with GCC"
	@echo "  make mswindows            for Microsoft Windows"
	@echo "  make macintosh            for Macintosh"
	@echo "  make machten-2.2          for Macs w/ MachTen 2.2 (68k w/ FPU)"
	@echo "  make machten-4.0          for Macs w/ MachTen 4.0.1 or newer with GNU make"
	@echo "  make mklinux              for Linux on Power Macintosh"
	@echo "  make netbsd               for NetBSD 1.0 systems with GCC"
	@echo "  make next                 for NeXT systems with NEXTSTEP 3.3"
	@echo "  make next-x86-x11         for NeXT on Intel x86 with X11"
	@echo "  make next-x11             for NeXT with X11"
	@echo "  make openbsd              for OpenBSD systems"
	@echo "  make openstep             for NeXT systems with OPENSTEP 4.0"
	@echo "  make os2                  for OS/2 with XFree86"
	@echo "  make osf1                 for DEC Alpha systems with OSF/1"
	@echo "  make osf1-sl              for DEC Alpha systems with OSF/1, make shared libs"
	@echo "  make qnx                  for QNX V4 systems with Watcom compiler"
	@echo "  make sco                  for SCO Unix systems with ODT"
	@echo "  make solaris-x86          for PCs with Solaris"
	@echo "  make solaris-x86-gcc      for PCs with Solaris using GCC"
#	@echo "  make solaris-gcc          for Solaris 2 systems with GCC"
	@echo "  make sunos4               for Suns with SunOS 4.x"
	@echo "  make sunos4-sl            for Suns with SunOS 4.x, make shared libs"
	@echo "  make sunos4-gcc           for Suns with SunOS 4.x and GCC"
	@echo "  make sunos4-gcc-sl        for Suns with SunOS 4.x, GCC, make shared libs"
	@echo "  make sunos5               for Suns with SunOS 5.x"
	@echo "  make sunos5-sl            for Suns with SunOS 5.x, make shared libs"
	@echo "  make sunos5-ultra         for Sun UltraSPARCs with SunOS 5.x"
	@echo "  make sunos5-gcc           for Suns with SunOS 5.x and GCC"
	@echo "  make sunos5-gcc-sl        for Suns with SunOS 5.x, GCC, make shared libs"
	@echo "  make sunos5-x11r6-gcc-sl  for Suns with X11R6, GCC, make shared libs"
	@echo "  make sunSolaris-CC        for Solaris using C++ compiler"
	@echo "  make ultrix-gcc           for DEC systems with Ultrix and GCC"
	@echo "  make unicos               for Cray C90 (and other?) systems"
	@echo "  make unixware             for PCs running UnixWare"
	@echo "  make unixware-shared      for PCs running UnixWare, shared libs"
	@echo "  make vistra               for Stardent Vistra systems"
	@echo "  make clean                remove .o files"
	@echo "  make realclean            remove .o, library and executable files"



aix aix-sl amix bsdos debug dgux freebsd gcc \
hpux hpux-gcc hpux-sl hpux-gcc-sl \
irix4 irix5 irix5-dso irix6-32 irix6-n32 irix6-64 \
irix6-32-dso irix6-n32-dso irix6-64-dso \
linux linux-debug linux-elf linux-alpha linux-alpha-elf linux-glide linux-ppc \
lynxos machten-2.2 machten-4.0 \
mklinux netbsd next-x86-x11 next-x11 osf1 osf1-sl openbsd qnx sco \
solaris-x86 solaris-x86-gcc sunSolaris-CC \
sunos4 sunos4-sl sunos4-gcc sunos4-gcc-sl \
sunos5 sunos5-sl sunos5-ultra sunos5-gcc sunos5-gcc-sl sunos5-x11r6-gcc-sl \
ultrix-gcc unicos unixware vistra:
	-mkdir lib
	touch src/depend
	touch src-glu/depend
	cd src ; $(MAKE) $@
	cd src-glu ; $(MAKE) $@
	if [ -d src-tk ]  ; then cd src-tk  ; $(MAKE) $@ ; fi
	if [ -d src-aux ] ; then cd src-aux ; $(MAKE) $@ ; fi
	if [ -d demos ]   ; then cd demos   ; $(MAKE) $@ ; fi
	if [ -d samples ] ; then cd samples ; $(MAKE) $@ ; fi
	if [ -d book ]    ; then cd book    ; $(MAKE) $@ ; fi

amiwin:
	mklib.amiwin

beos:
	-mkdir lib
	cd src ; $(MAKE) -f Makefile.BeOS $@
	cd src-glu ; $(MAKE) -f Makefile $@
	if [ -d src-tk ]  ; then cd src-tk  ; $(MAKE) -f Makefile.BeOS $@ ; fi
	if [ -d src-aux ] ; then cd src-aux ; $(MAKE) -f Makefile.BeOS $@ ; fi
	if [ -d BeOS ]    ; then cd BeOS    ; $(MAKE) -f Makefile.BeOS $@ ; fi

cygnus:
	-mkdir lib
	touch src/depend
	touch src-glu/depend
	cd src ; $(MAKE) $@
	cd src-glu ; $(MAKE) $@
	if [ -d src-tk ]  ; then cd src-tk  ; $(MAKE) $@ ; fi
	if [ -d src-aux ] ; then cd src-aux ; $(MAKE) $@ ; fi
	if [ -d demos ]   ; then cd demos   ; $(MAKE) $@ ; fi

linux-mondello:
	-mkdir lib
	touch src/depend
	touch src-glu/depend
	cd src ; $(MAKE) $@
	cd mondello ; $(MAKE) $@
	cd src-glu ; $(MAKE) $@
	if [ -d src-tk2 ] ; then cd src-tk2 ; $(MAKE) $@ ; fi
	if [ -d src-aux ] ; then cd src-aux ; $(MAKE) $@ ; fi
	if [ -d demos ]   ; then cd demos   ; $(MAKE) $@ ; fi
	if [ -d samples ] ; then cd samples ; $(MAKE) $@ ; fi
	if [ -d book ]    ; then cd book    ; $(MAKE) $@ ; fi

macintosh:
	@echo "See the README file for Macintosh intallation information"

mswindows:
	@echo "See the windows/README file for installation information"

next:
	-mkdir lib
	cd src ; $(MAKE) -f Makefile.NeXT $@
	cd src-glu ; $(MAKE) -f Makefile $@
	cd NeXT ; $(MAKE) -f Makefile.NeXT $@
	if [ -d src-tk ]  ; then cd src-tk  ; $(MAKE) -f Makefile.NeXT $@ ; fi
	if [ -d src-aux ] ; then cd src-aux ; $(MAKE) -f Makefile.NeXT $@ ; fi

openstep:
	-mkdir lib
	cd src ; $(MAKE) -f Makefile.OpenStep $@
	cd src-glu ; $(MAKE) -f Makefile.OpenStep $@
	if [ -d src-tk ]  ; then cd src-tk  ; $(MAKE) -f Makefile.OpenStep $@ ; fi
	if [ -d src-aux ] ; then cd src-aux ; $(MAKE) -f Makefile.OpenStep $@ ; fi
	cd OpenStep; $(MAKE)

os2:
	@echo "See the README.OS2 file for instructions"



# Remove .o files, emacs backup files, etc.
clean:
	-rm -f include/*~
	-rm -f include/GL/*~
	-rm -f src/*.o src/*~ src/*.a
	-rm -f src-aux/*.o src-aux/*~ src-aux/*.a
	-rm -f src-glu/*.o src-glu/*~ src-glu/*.a
	-rm -f src-tk/*.o src-tk/*~ src-tk/*.a
	-rm -f src-tk2/*.o src-tk2/*~ src-tk2/*.a
	-rm -f book/*.o book/*~
	-rm -f demos/*.o demos/*~
	-rm -f samples/*.o samples/*~
	-rm -f mondello/*.o mondello/*~ mondello/*.a

# Remove everthing that can be remade
realclean: clean
	-rm -f lib/*.a lib/*.so*
	cd book ; $(MAKE) realclean
	cd demos ; $(MAKE) realclean
	cd samples ; $(MAKE) realclean
	cd mondello; $(MAKE) realclean
	-rm -f lib/*.a lib/*.so*



DIRECTORY = Mesa-2.4
LIB_NAME = MesaLib-2.4
DEMO_NAME = MesaDemos-2.4


LIB_FILES =	\
	$(DIRECTORY)/README*			\
	$(DIRECTORY)/IAFA-PACKAGE		\
	$(DIRECTORY)/LICENSE			\
	$(DIRECTORY)/VERSIONS			\
	$(DIRECTORY)/RELNOTES			\
	$(DIRECTORY)/FUTURE			\
	$(DIRECTORY)/Makefile*			\
	$(DIRECTORY)/Make-config		\
	$(DIRECTORY)/MESAFX.BAT			\
	$(DIRECTORY)/Imakefile			\
	$(DIRECTORY)/descrip.mms		\
	$(DIRECTORY)/mms-config			\
	$(DIRECTORY)/xlib.opt			\
	$(DIRECTORY)/MESADOS.BAT		\
	$(DIRECTORY)/STARTUP.MK			\
	$(DIRECTORY)/mklib.*			\
	$(DIRECTORY)/include/*.h		\
	$(DIRECTORY)/include/GL/*.h		\
	$(DIRECTORY)/include/mondello/*.h	\
	$(DIRECTORY)/src/Makefile*		\
	$(DIRECTORY)/src/Imakefile		\
	$(DIRECTORY)/src/descrip.mms		\
	$(DIRECTORY)/src/mms_depend		\
	$(DIRECTORY)/src/DEPEND.DOS		\
	$(DIRECTORY)/src/*.def			\
	$(DIRECTORY)/src/*.rsp			\
	$(DIRECTORY)/src/depend			\
	$(DIRECTORY)/src/wing32.def		\
	$(DIRECTORY)/src/*.[ch]			\
	$(DIRECTORY)/src-glu/README[12]		\
	$(DIRECTORY)/src-glu/Makefile*		\
	$(DIRECTORY)/src-glu/Imakefile		\
	$(DIRECTORY)/src-glu/descrip.mms	\
	$(DIRECTORY)/src-glu/mms_depend		\
	$(DIRECTORY)/src-glu/*.def		\
	$(DIRECTORY)/src-glu/*.rsp		\
	$(DIRECTORY)/src-glu/depend		\
	$(DIRECTORY)/src-glu/*.[ch]		\
	$(DIRECTORY)/widgets-mesa		\
	$(DIRECTORY)/widgets-sgi		\
	$(DIRECTORY)/util/README		\
	$(DIRECTORY)/util/*.c			\
	$(DIRECTORY)/windows			\
	$(DIRECTORY)/NeXT			\
	$(DIRECTORY)/BeOS			\
	$(DIRECTORY)/mondello			\
	$(DIRECTORY)/OpenStep

DEMO_FILES =	\
	$(DIRECTORY)/src-tk/README		\
	$(DIRECTORY)/src-tk/Makefile*		\
	$(DIRECTORY)/src-tk/Imakefile		\
	$(DIRECTORY)/src-tk/descrip.mms		\
	$(DIRECTORY)/src-tk/*.def		\
	$(DIRECTORY)/src-tk/*.rsp		\
	$(DIRECTORY)/src-tk/*.[ch]		\
	$(DIRECTORY)/src-tk/*cpp		\
	$(DIRECTORY)/src-aux/Makefile*		\
	$(DIRECTORY)/src-aux/Imakefile		\
	$(DIRECTORY)/src-aux/descrip.mms	\
	$(DIRECTORY)/src-aux/*.def		\
	$(DIRECTORY)/src-aux/*.rsp		\
	$(DIRECTORY)/src-aux/*.[ch]		\
	$(DIRECTORY)/demos/Makefile*		\
	$(DIRECTORY)/demos/Imakefile		\
	$(DIRECTORY)/demos/descrip.mms		\
	$(DIRECTORY)/demos/*.[cf]		\
	$(DIRECTORY)/demos/isosurf.dat		\
	$(DIRECTORY)/book/Makefile*		\
	$(DIRECTORY)/book/Imakefile		\
	$(DIRECTORY)/book/README		\
	$(DIRECTORY)/book/*.[ch]		\
	$(DIRECTORY)/samples/Makefile*		\
	$(DIRECTORY)/samples/Imakefile		\
	$(DIRECTORY)/samples/README		\
	$(DIRECTORY)/samples/*.rgb		\
	$(DIRECTORY)/samples/*.c		\
	$(DIRECTORY)/3Dfx


lib_tar:
	cd .. ; \
	tar -cvf $(LIB_NAME).tar $(LIB_FILES) ; \
	gzip $(LIB_NAME).tar ; \
	mv $(LIB_NAME).tar.gz $(DIRECTORY)

demo_tar:
	cd .. ; \
	tar -cvf $(DEMO_NAME).tar $(DEMO_FILES) ; \
	gzip $(DEMO_NAME).tar ; \
	mv $(DEMO_NAME).tar.gz $(DIRECTORY)

lib_zip:
	-rm $(LIB_NAME).zip
	cd .. ; \
	zip -r $(LIB_NAME).zip $(LIB_FILES) ; \
	mv $(LIB_NAME).zip $(DIRECTORY)

demo_zip:
	-rm $(DEMO_NAME).zip
	cd .. ; \
	zip -r $(DEMO_NAME).zip $(DEMO_FILES) ; \
	mv $(DEMO_NAME).zip $(DIRECTORY)



SRC_FILES =	\
	src/Makefile		\
	src/depend		\
	src/*.[ch]		\
	include/*.h		\
	include/GL/*.h

srctar:
	tar -cvf src.tar $(SRC_FILES) ; \
	gzip src.tar

srctar.zip:
	-rm src.zip
	zip -r src.zip $(SRC_FILES) ; \
