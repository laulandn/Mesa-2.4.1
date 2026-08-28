set MSVC=h:\winapps\msdev

mkdir lib
cd src
nmake /f Makefile.fx
cd ..\src-glu
nmake /f Makefile.fx
cd ..\src-tk
nmake /f Makefile.fx
cd ..\3Dfx\fxGLUT\src
nmake /f Makefile.fx
cd ..\..\demos
nmake /f Makefile.fx




