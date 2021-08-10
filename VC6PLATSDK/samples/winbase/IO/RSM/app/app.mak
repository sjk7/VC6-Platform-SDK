# Microsoft Developer Studio Generated NMAKE File, Based on App.dsp
!IF "$(CFG)" == ""
CFG=App - Win32 Debug
!MESSAGE No configuration specified. Defaulting to App - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "App - Win32 Release" && "$(CFG)" != "App - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "App.mak" CFG="App - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "App - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "App - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "App - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\App.exe"


CLEAN :
	-@erase "$(INTDIR)\App.obj"
	-@erase "$(INTDIR)\App_Utls.obj"
	-@erase "$(INTDIR)\STL_write.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\App.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\App.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\App.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\App.pdb" /machine:I386 /out:"$(OUTDIR)\App.exe" 
LINK32_OBJS= \
	"$(INTDIR)\App.obj" \
	"$(INTDIR)\App_Utls.obj" \
	"$(INTDIR)\STL_write.obj"

"$(OUTDIR)\App.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "App - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\App.exe"


CLEAN :
	-@erase "$(INTDIR)\App.obj"
	-@erase "$(INTDIR)\App_Utls.obj"
	-@erase "$(INTDIR)\STL_write.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\App.exe"
	-@erase "$(OUTDIR)\App.ilk"
	-@erase "$(OUTDIR)\App.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\App.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\App.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrtd.lib ntmsapi.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\App.pdb" /debug /machine:I386 /nodefaultlib /out:"$(OUTDIR)\App.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\App.obj" \
	"$(INTDIR)\App_Utls.obj" \
	"$(INTDIR)\STL_write.obj"

"$(OUTDIR)\App.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("App.dep")
!INCLUDE "App.dep"
!ELSE 
!MESSAGE Warning: cannot find "App.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "App - Win32 Release" || "$(CFG)" == "App - Win32 Debug"
SOURCE=.\App.cpp

"$(INTDIR)\App.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\App_Utls.cpp

"$(INTDIR)\App_Utls.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\STL_write.cpp

"$(INTDIR)\STL_write.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

