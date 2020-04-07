# Microsoft Developer Studio Generated NMAKE File, Based on inproc.dsp
!IF "$(CFG)" == ""
CFG=inproc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to inproc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "inproc - Win32 Release" && "$(CFG)" != "inproc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "inproc.mak" CFG="inproc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "inproc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "inproc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "inproc - Win32 Release"

OUTDIR=.\..\Bin\Release\x86
INTDIR=.\Release\x86
# Begin Custom Macros
OutDir=.\..\Bin\Release\x86
# End Custom Macros

ALL : "$(OUTDIR)\inproc.dll"


CLEAN :
	-@erase "$(INTDIR)\SSERVER.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\inproc.dll"
	-@erase "$(OUTDIR)\inproc.exp"
	-@erase "$(OUTDIR)\inproc.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "_WIN32_DCOM" /D "WIN32" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\inproc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\inproc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\inproc.pdb" /machine:$(CPU) /def:".\dllsrv.def" /out:"$(OUTDIR)\inproc.dll" /implib:"$(OUTDIR)\inproc.lib" 
DEF_FILE= \
	".\dllsrv.def"
LINK32_OBJS= \
	"$(INTDIR)\SSERVER.OBJ"

"$(OUTDIR)\inproc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "inproc - Win32 Debug"

OUTDIR=.\..\Bin\Debug\x86
INTDIR=.\Debug\x86
# Begin Custom Macros
OutDir=.\..\Bin\Debug\x86
# End Custom Macros

ALL : "$(OUTDIR)\inproc.dll"


CLEAN :
	-@erase "$(INTDIR)\SSERVER.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\inproc.dll"
	-@erase "$(OUTDIR)\inproc.exp"
	-@erase "$(OUTDIR)\inproc.ilk"
	-@erase "$(OUTDIR)\inproc.lib"
	-@erase "$(OUTDIR)\inproc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_WINDOWS" /D "_DEBUG" /D "UNICODE" /D "_UNICODE" /D "_WIN32_DCOM" /D "WIN32" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\inproc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\inproc.pdb" /debug /machine:$(CPU) /def:".\dllsrv.def" /out:"$(OUTDIR)\inproc.dll" /implib:"$(OUTDIR)\inproc.lib" /pdbtype:sept 
DEF_FILE= \
	".\dllsrv.def"
LINK32_OBJS= \
	"$(INTDIR)\SSERVER.OBJ"

"$(OUTDIR)\inproc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("inproc.dep")
!INCLUDE "inproc.dep"
!ELSE 
!MESSAGE Warning: cannot find "inproc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "inproc - Win32 Release" || "$(CFG)" == "inproc - Win32 Debug"
SOURCE=.\SSERVER.CPP

"$(INTDIR)\SSERVER.OBJ" : $(SOURCE) "$(INTDIR)"



!ENDIF 

