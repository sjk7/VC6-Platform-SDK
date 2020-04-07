
# Microsoft Developer Studio Generated NMAKE File, Based on comperf.dsp
!IF "$(CFG)" == ""
CFG=comperf - Win64 Debug
!MESSAGE No configuration specified. Defaulting to comperf - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "comperf - Win64 Release" && "$(CFG)" != "comperf - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "comperf64.mak" CFG="comperf - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "comperf - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "comperf - Win64 Debug" (based on "Win64 (IA64) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "comperf - Win64 Release"

OUTDIR=.\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\comperf.exe"

!ELSE 

ALL : "psperf - Win64 Release" "$(OUTDIR)\comperf.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"psperf - Win64 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\comperf.obj"
	-@erase "$(INTDIR)\psperf_i.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\comperf.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /Wp64 /GX /O2 /I "ps_Win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\comperf.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\comperf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\comperf.pdb" /machine:IA64 /out:"$(OUTDIR)\comperf.exe" 
LINK32_OBJS= \
	"$(INTDIR)\comperf.obj" \
	"$(INTDIR)\psperf_i.obj" \
	"$(OUTDIR)\psperf.lib"

"$(OUTDIR)\comperf.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "comperf - Win64 Debug"

OUTDIR=.\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\Debug\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\comperf.exe"

!ELSE 

ALL : "psperf - Win64 Debug" "$(OUTDIR)\comperf.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"psperf - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\comperf.obj"
	-@erase "$(INTDIR)\psperf_i.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\comperf.exe"
	-@erase "$(OUTDIR)\comperf.ilk"
	-@erase "$(OUTDIR)\comperf.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Wp64 /Gm /GX /Zi /Od /I "ps_Win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\comperf.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\comperf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\comperf.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\comperf.exe"  
LINK32_OBJS= \
	"$(INTDIR)\comperf.obj" \
	"$(INTDIR)\psperf_i.obj" \
	"$(OUTDIR)\psperf.lib"

"$(OUTDIR)\comperf.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("comperf.dep")
!INCLUDE "comperf.dep"
!ELSE 
!MESSAGE Warning: cannot find "comperf.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "comperf - Win64 Release" || "$(CFG)" == "comperf - Win64 Debug"
SOURCE=.\comperf.Cpp

"$(INTDIR)\comperf.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ps_Win64\psperf_i.c

"$(INTDIR)\psperf_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "comperf - Win64 Release"

"psperf - Win64 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\psperf64.mak CFG="psperf - Win64 Release" 
   cd "."

"psperf - Win64 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\psperf64.mak CFG="psperf - Win64 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "comperf - Win64 Debug"

"psperf - Win64 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\psperf64.mak CFG="psperf - Win64 Debug" 
   cd "."

"psperf - Win64 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\psperf64.mak CFG="psperf - Win64 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 


!ENDIF 
