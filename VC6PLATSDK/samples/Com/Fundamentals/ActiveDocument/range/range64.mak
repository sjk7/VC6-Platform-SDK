
# Microsoft Developer Studio Generated NMAKE File, Based on range.dsp
!IF "$(CFG)" == ""
CFG=range - Win64 Debug
!MESSAGE No configuration specified. Defaulting to range - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "range - Win64 Release" && "$(CFG)" != "range - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "range64.mak" CFG="range - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "range - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "range - Win64 Debug" (based on "Win64 (IA64) Console Application")
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

!IF  "$(CFG)" == "range - Win64 Release"

OUTDIR=.\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\Release\IA64
# End Custom Macros

ALL : "$(OUTDIR)\range.exe"


CLEAN :
	-@erase "$(INTDIR)\cache.obj"
	-@erase "$(INTDIR)\callback.obj"
	-@erase "$(INTDIR)\download.obj"
	-@erase "$(INTDIR)\range.obj"
	-@erase "$(INTDIR)\recvbuf.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\range.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /GX /O2 /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\range.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\range.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib urlmon.lib wininet.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\range.pdb" /machine:IA64 /out:"$(OUTDIR)\range.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cache.obj" \
	"$(INTDIR)\callback.obj" \
	"$(INTDIR)\download.obj" \
	"$(INTDIR)\range.obj" \
	"$(INTDIR)\recvbuf.obj"

"$(OUTDIR)\range.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "range - Win64 Debug"

OUTDIR=.\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\Debug\IA64
# End Custom Macros

ALL : "$(OUTDIR)\range.exe"


CLEAN :
	-@erase "$(INTDIR)\cache.obj"
	-@erase "$(INTDIR)\callback.obj"
	-@erase "$(INTDIR)\download.obj"
	-@erase "$(INTDIR)\range.obj"
	-@erase "$(INTDIR)\recvbuf.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\range.exe"
	-@erase "$(OUTDIR)\range.ilk"
	-@erase "$(OUTDIR)\range.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\range.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\range.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib urlmon.lib wininet.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\range.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\range.exe"  
LINK32_OBJS= \
	"$(INTDIR)\cache.obj" \
	"$(INTDIR)\callback.obj" \
	"$(INTDIR)\download.obj" \
	"$(INTDIR)\range.obj" \
	"$(INTDIR)\recvbuf.obj"

"$(OUTDIR)\range.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("range.dep")
!INCLUDE "range.dep"
!ELSE 
!MESSAGE Warning: cannot find "range.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "range - Win64 Release" || "$(CFG)" == "range - Win64 Debug"
SOURCE=.\cache.cpp

"$(INTDIR)\cache.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\callback.cpp

!IF  "$(CFG)" == "range - Win64 Release"

CPP_SWITCHES=/nologo /ML /W3 /Wp64 /GX /O2 /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\range.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

"$(INTDIR)\callback.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "range - Win64 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\range.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\callback.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\download.cpp

"$(INTDIR)\download.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\range.c

"$(INTDIR)\range.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\recvbuf.cpp

"$(INTDIR)\recvbuf.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 
