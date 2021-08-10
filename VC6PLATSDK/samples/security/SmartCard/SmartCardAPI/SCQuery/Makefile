# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1997-1999.  Microsoft Corporation.  All rights reserved.
#
# Microsoft Developer Studio Generated NMAKE File, Based on scquery.dsp
!IF "$(CFG)" == ""
CFG=scquery - Win32 Debug
!MESSAGE No configuration specified. Defaulting to scquery - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "scquery - Win32 Release" && "$(CFG)" != "scquery - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE CFG="scquery - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "scquery - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "scquery - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE
!ERROR An invalid configuration is specified.
!ENDIF

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF

!IF  "$(CFG)" == "scquery - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\scquery.exe"


CLEAN :
        -@erase "$(INTDIR)\SCCommon.obj"
        -@erase "$(INTDIR)\SCQuery.obj"
        -@erase "$(INTDIR)\vc60.idb"
        -@erase "$(OUTDIR)\scquery.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\scquery.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=winscard.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\scquery.pdb" /machine:$(CPU) /out:"$(OUTDIR)\scquery.exe"
LINK32_OBJS= \
        "$(INTDIR)\SCCommon.obj" \
        "$(INTDIR)\SCQuery.obj"

"$(OUTDIR)\scquery.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "scquery - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\scquery.exe"


CLEAN :
        -@erase "$(INTDIR)\SCCommon.obj"
        -@erase "$(INTDIR)\SCQuery.obj"
        -@erase "$(INTDIR)\vc60.idb"
        -@erase "$(INTDIR)\vc60.pdb"
        -@erase "$(OUTDIR)\scquery.exe"
        -@erase "$(OUTDIR)\scquery.ilk"
        -@erase "$(OUTDIR)\scquery.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $<
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\scquery.bsc"
BSC32_SBRS= \

LINK32=link.exe
LINK32_FLAGS=winscard.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\scquery.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\scquery.exe" 
LINK32_OBJS= \
        "$(INTDIR)\SCCommon.obj" \
        "$(INTDIR)\SCQuery.obj"

"$(OUTDIR)\scquery.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF


.\SCCommon.Cpp : \
        ".\sccommon.h"\


.\SCQuery.Cpp : \
        ".\sccommon.h"\


!IF "$(CFG)" == "scquery - Win32 Release" || "$(CFG)" == "scquery - Win32 Debug"
SOURCE=.\SCCommon.Cpp

"$(INTDIR)\SCCommon.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SCQuery.Cpp

"$(INTDIR)\SCQuery.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF

