
# Microsoft Developer Studio Generated NMAKE File, Based on cmallspy.dsp
!IF "$(CFG)" == ""
CFG=cmallspy - Win64 Debug
!MESSAGE No configuration specified. Defaulting to cmallspy - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "cmallspy - Win64 Release" && "$(CFG)" != "cmallspy - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cmallspy64.mak" CFG="cmallspy - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cmallspy - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "cmallspy - Win64 Debug" (based on "Win64 (IA64) Console Application")
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

!IF  "$(CFG)" == "cmallspy - Win64 Release"

OUTDIR=.\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\Release\IA64
# End Custom Macros

ALL : "$(OUTDIR)\cmallspy.exe"


CLEAN :
	-@erase "$(INTDIR)\cmallspy.obj"
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\cmallspy.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /GX /O2 /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\cmallspy.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cmallspy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\cmallspy.pdb" /machine:IA64 /out:"$(OUTDIR)\cmallspy.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cmallspy.obj" \
	"$(INTDIR)\test.obj"

"$(OUTDIR)\cmallspy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "cmallspy - Win64 Debug"

OUTDIR=.\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\Debug\IA64
# End Custom Macros

ALL : "$(OUTDIR)\cmallspy.exe"


CLEAN :
	-@erase "$(INTDIR)\cmallspy.obj"
	-@erase "$(INTDIR)\test.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\cmallspy.exe"
	-@erase "$(OUTDIR)\cmallspy.ilk"
	-@erase "$(OUTDIR)\cmallspy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\cmallspy.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cmallspy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\cmallspy.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\cmallspy.exe"  
LINK32_OBJS= \
	"$(INTDIR)\cmallspy.obj" \
	"$(INTDIR)\test.obj"

"$(OUTDIR)\cmallspy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("cmallspy.dep")
!INCLUDE "cmallspy.dep"
!ELSE 
!MESSAGE Warning: cannot find "cmallspy.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "cmallspy - Win64 Release" || "$(CFG)" == "cmallspy - Win64 Debug"
SOURCE=.\cmallspy.cxx

"$(INTDIR)\cmallspy.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\test.cxx

"$(INTDIR)\test.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 
