# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=olympic - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to olympic - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "olympic - Win32 Release" && "$(CFG)" !=\
 "olympic - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "olympic.mak" CFG="olympic - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "olympic - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "olympic - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "olympic - Win32 Debug"
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "olympic - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "olympic_"
# PROP BASE Intermediate_Dir "olympic_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "olympic_"
# PROP Intermediate_Dir "olympic_"
# PROP Target_Dir ""
OUTDIR=.\olympic_
INTDIR=.\olympic_

ALL : "$(OUTDIR)\olympic.exe"

CLEAN : 
	-@erase "$(INTDIR)\olympic.obj"
	-@erase "$(OUTDIR)\olympic.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/olympic.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\olympic_/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/olympic.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmesa.lib glaux.lib winglu.lib tk.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib winmesa.lib glaux.lib winglu.lib tk.lib /nologo /subsystem:console\
 /incremental:no /pdb:"$(OUTDIR)/olympic.pdb" /machine:I386\
 /out:"$(OUTDIR)/olympic.exe" 
LINK32_OBJS= \
	"$(INTDIR)\olympic.obj"

"$(OUTDIR)\olympic.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "olympic - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "olympic0"
# PROP BASE Intermediate_Dir "olympic0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "olympic0"
# PROP Intermediate_Dir "olympic0"
# PROP Target_Dir ""
OUTDIR=.\olympic0
INTDIR=.\olympic0

ALL : "$(OUTDIR)\olympic.exe"

CLEAN : 
	-@erase "$(INTDIR)\olympic.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\olympic.exe"
	-@erase "$(OUTDIR)\olympic.ilk"
	-@erase "$(OUTDIR)\olympic.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/olympic.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\olympic0/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/olympic.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmesa.lib glaux.lib winglu.lib tk.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib winmesa.lib glaux.lib winglu.lib tk.lib /nologo /subsystem:console\
 /incremental:yes /pdb:"$(OUTDIR)/olympic.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/olympic.exe" 
LINK32_OBJS= \
	"$(INTDIR)\olympic.obj"

"$(OUTDIR)\olympic.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "olympic - Win32 Release"
# Name "olympic - Win32 Debug"

!IF  "$(CFG)" == "olympic - Win32 Release"

!ELSEIF  "$(CFG)" == "olympic - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\olympic.c
DEP_CPP_OLYMP=\
	{$(INCLUDE)}"\GL\gl.h"\
	{$(INCLUDE)}"\GL\glu.h"\
	{$(INCLUDE)}"\gltk.h"\
	{$(INCLUDE)}"\sys\types.h"\
	
NODEP_CPP_OLYMP=\
	"..\include\GL\gl_mangle.h"\
	"..\include\GL\glu_mangle.h"\
	

"$(INTDIR)\olympic.obj" : $(SOURCE) $(DEP_CPP_OLYMP) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
