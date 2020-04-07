# Microsoft Developer Studio Generated NMAKE File, Based on mta.dsp
!IF "$(CFG)" == ""
CFG=mta - Win32 Debug
!MESSAGE No configuration specified. Defaulting to mta - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "mta - Win32 Release" && "$(CFG)" != "mta - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mta.mak" CFG="mta - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mta - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "mta - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "mta - Win32 Release"

OUTDIR=.\..\..\Bin\Release\x86
INTDIR=.\Release\x86
# Begin Custom Macros
OutDir=.\..\..\Bin\Release\x86
# End Custom Macros

ALL : "$(OUTDIR)\mta.exe"


CLEAN :
	-@erase "$(INTDIR)\SSERVER.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\mta.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /D "WIN32" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\mta.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mta.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\mta.pdb" /machine:$(CPU) /out:"$(OUTDIR)\mta.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SSERVER.OBJ"

"$(OUTDIR)\mta.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mta - Win32 Debug"

OUTDIR=.\..\..\Bin\Debug\x86
INTDIR=.\Debug\x86
# Begin Custom Macros
OutDir=.\..\..\Bin\Debug\x86
# End Custom Macros

ALL : "$(OUTDIR)\mta.exe"


CLEAN :
	-@erase "$(INTDIR)\SSERVER.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\mta.exe"
	-@erase "$(OUTDIR)\mta.ilk"
	-@erase "$(OUTDIR)\mta.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "_CONSOLE" /D "_DEBUG" /D "UNICODE" /D "_UNICODE" /D "_WIN32_DCOM" /D "WIN32" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mta.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\mta.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\mta.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SSERVER.OBJ"

"$(OUTDIR)\mta.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("mta.dep")
!INCLUDE "mta.dep"
!ELSE 
!MESSAGE Warning: cannot find "mta.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "mta - Win32 Release" || "$(CFG)" == "mta - Win32 Debug"
SOURCE=.\SSERVER.CPP

"$(INTDIR)\SSERVER.OBJ" : $(SOURCE) "$(INTDIR)"



!ENDIF 

