
# Microsoft Developer Studio Generated NMAKE File, Based on scaledemo.dsp
!IF "$(CFG)" == ""
CFG=scaledemo - Win64 Debug
!MESSAGE No configuration specified. Defaulting to scaledemo - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "scaledemo - Win64 Release" && "$(CFG)" != "scaledemo - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "scaledemo64.mak" CFG="scaledemo - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "scaledemo - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "scaledemo - Win64 Debug" (based on "Win64 (IA64) Console Application")
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

!IF  "$(CFG)" == "scaledemo - Win64 Release"

OUTDIR=.\..\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\..\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\scaledemo.exe"

!ELSE 

ALL : "$(OUTDIR)\scaledemo.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\scaledemo.obj"
	-@erase "$(INTDIR)\scaledemo.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\scaledemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /GX /O2 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\scaledemo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\scaledemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\scaledemo.pdb" /machine:IA64 /out:"$(OUTDIR)\scaledemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\scaledemo.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\scaledemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "scaledemo - Win64 Debug"

OUTDIR=.\..\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\..\Debug\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\scaledemo.exe"

!ELSE 

ALL : "FullSvr - Win64 Debug" "$(OUTDIR)\scaledemo.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FullSvr - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\scaledemo.obj"
	-@erase "$(INTDIR)\scaledemo.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\scaledemo.exe"
	-@erase "$(OUTDIR)\scaledemo.ilk"
	-@erase "$(OUTDIR)\scaledemo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\scaledemo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\scaledemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\scaledemo.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\scaledemo.exe"  
LINK32_OBJS= \
	"$(INTDIR)\scaledemo.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\scaledemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("scaledemo.dep")
!INCLUDE "scaledemo.dep"
!ELSE 
!MESSAGE Warning: cannot find "scaledemo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "scaledemo - Win64 Release" || "$(CFG)" == "scaledemo - Win64 Debug"
SOURCE=.\scaledemo.cpp

"$(INTDIR)\scaledemo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\scaledemo.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "scaledemo - Win64 Release"

CPP_SWITCHES=/nologo /ML /W3 /Wp64 /GX /O2 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\scaledemo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\scaledemo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "scaledemo - Win64 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\scaledemo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\scaledemo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "scaledemo - Win64 Release"

!ELSEIF  "$(CFG)" == "scaledemo - Win64 Debug"

"FullSvr - Win64 Debug" : 
   cd ".\..\FullSvr"
   $(MAKE) /$(MAKEFLAGS) /F .\FullSvr64.mak CFG="FullSvr - Win64 Debug" 
   cd "..\scaleDemo"

"FullSvr - Win64 DebugCLEAN" : 
   cd ".\..\FullSvr"
   $(MAKE) /$(MAKEFLAGS) /F .\FullSvr64.mak CFG="FullSvr - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\scaleDemo"

!ENDIF 


!ENDIF 
