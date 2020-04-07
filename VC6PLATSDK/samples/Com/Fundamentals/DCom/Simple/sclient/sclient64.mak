
# Microsoft Developer Studio Generated NMAKE File, Based on sclient.dsp
!IF "$(CFG)" == ""
CFG=sclient - Win64 Debug
!MESSAGE No configuration specified. Defaulting to sclient - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "sclient - Win64 Release" && "$(CFG)" != "sclient - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sclient64.mak" CFG="sclient - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sclient - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "sclient - Win64 Debug" (based on "Win64 (IA64) Console Application")
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

!IF  "$(CFG)" == "sclient - Win64 Release"

OUTDIR=.\..\bin\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\..\bin\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\sclient.exe"

!ELSE 

ALL : "sserver - Win64 Release" "$(OUTDIR)\sclient.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"sserver - Win64 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\sclient.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\sclient.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /Gz /ML /W3 /Wp64 /GX /O2 /D "NDEBUG" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\sclient.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sclient.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\sclient.pdb" /machine:IA64 /out:"$(OUTDIR)\sclient.exe" 
LINK32_OBJS= \
	"$(INTDIR)\sclient.obj"

"$(OUTDIR)\sclient.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sclient - Win64 Debug"

OUTDIR=.\..\bin\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\..\bin\Debug\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\sclient.exe"

!ELSE 

ALL : "sserver - Win64 Debug" "$(OUTDIR)\sclient.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"sserver - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\sclient.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\sclient.exe"
	-@erase "$(OUTDIR)\sclient.ilk"
	-@erase "$(OUTDIR)\sclient.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /Gz /MLd /W3 /Wp64 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\sclient.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sclient.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\sclient.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\sclient.exe"  
LINK32_OBJS= \
	"$(INTDIR)\sclient.obj"

"$(OUTDIR)\sclient.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("sclient.dep")
!INCLUDE "sclient.dep"
!ELSE 
!MESSAGE Warning: cannot find "sclient.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "sclient - Win64 Release" || "$(CFG)" == "sclient - Win64 Debug"
SOURCE=.\sclient.cpp

"$(INTDIR)\sclient.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "sclient - Win64 Release"

"sserver - Win64 Release" : 
   cd ".\..\sserver"
   $(MAKE) /$(MAKEFLAGS) /F .\sserver64.mak CFG="sserver - Win64 Release" 
   cd "..\sclient"

"sserver - Win64 ReleaseCLEAN" : 
   cd ".\..\sserver"
   $(MAKE) /$(MAKEFLAGS) /F .\sserver64.mak CFG="sserver - Win64 Release" RECURSE=1 CLEAN 
   cd "..\sclient"

!ELSEIF  "$(CFG)" == "sclient - Win64 Debug"

"sserver - Win64 Debug" : 
   cd ".\..\sserver"
   $(MAKE) /$(MAKEFLAGS) /F .\sserver64.mak CFG="sserver - Win64 Debug" 
   cd "..\sclient"

"sserver - Win64 DebugCLEAN" : 
   cd ".\..\sserver"
   $(MAKE) /$(MAKEFLAGS) /F .\sserver64.mak CFG="sserver - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\sclient"

!ENDIF 


!ENDIF 
