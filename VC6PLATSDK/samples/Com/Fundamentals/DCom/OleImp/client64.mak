
# Microsoft Developer Studio Generated NMAKE File, Based on client.dsp
!IF "$(CFG)" == ""
CFG=client - Win64 Debug
!MESSAGE No configuration specified. Defaulting to client - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "client - Win64 Release" && "$(CFG)" != "client - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "client64.mak" CFG="client - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "client - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "client - Win64 Debug" (based on "Win64 (IA64) Console Application")
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

!IF  "$(CFG)" == "client - Win64 Release"

OUTDIR=.\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\client.exe"

!ELSE 

ALL : "oleimp - Win64 Release" "$(OUTDIR)\client.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"oleimp - Win64 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\client.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /GX /O2 /D "NDEBUG" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\client.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\client.pdb" /machine:IA64 /out:"$(OUTDIR)\client.exe" 
LINK32_OBJS= \
	"$(INTDIR)\client.obj"

"$(OUTDIR)\client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "client - Win64 Debug"

OUTDIR=.\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\Debug\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\client.exe"

!ELSE 

ALL : "oleimp - Win64 Debug" "$(OUTDIR)\client.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"oleimp - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\client.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\client.exe"
	-@erase "$(OUTDIR)\client.ilk"
	-@erase "$(OUTDIR)\client.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\client.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\client.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\client.exe"  
LINK32_OBJS= \
	"$(INTDIR)\client.obj"

"$(OUTDIR)\client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("client.dep")
!INCLUDE "client.dep"
!ELSE 
!MESSAGE Warning: cannot find "client.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "client - Win64 Release" || "$(CFG)" == "client - Win64 Debug"
SOURCE=.\client.Cpp

"$(INTDIR)\client.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "client - Win64 Release"

"oleimp - Win64 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\oleimp64.mak CFG="oleimp - Win64 Release" 
   cd "."

"oleimp - Win64 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\oleimp64.mak CFG="oleimp - Win64 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "client - Win64 Debug"

"oleimp - Win64 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\oleimp64.mak CFG="oleimp - Win64 Debug" 
   cd "."

"oleimp - Win64 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\oleimp64.mak CFG="oleimp - Win64 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 


!ENDIF 
