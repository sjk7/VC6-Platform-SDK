!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on Driver.dsp
!IF "$(CFG)" == ""
CFG=Driver - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Driver - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Driver - Win32 Release" && "$(CFG)" != "Driver - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Driver.mak" CFG="Driver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Driver - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Driver - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Driver - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Driver.exe"

!ELSE 

ALL : "QCOrder - Win32 Release" "$(OUTDIR)\Driver.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"QCOrder - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Driver.obj"
	-@erase "$(INTDIR)\Driver.pch"
	-@erase "$(INTDIR)\Driver.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Driver.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Driver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Driver.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Driver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\Driver.pdb" /machine:$(CPU) /out:"$(OUTDIR)\Driver.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Driver.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Driver.res" \
	"..\QCOrder\Release\QCOrder.lib"

"$(OUTDIR)\Driver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Driver - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Driver.exe"

!ELSE 

ALL : "QCOrder - Win32 Debug" "$(OUTDIR)\Driver.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"QCOrder - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Driver.obj"
	-@erase "$(INTDIR)\Driver.pch"
	-@erase "$(INTDIR)\Driver.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Driver.exe"
	-@erase "$(OUTDIR)\Driver.ilk"
	-@erase "$(OUTDIR)\Driver.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Driver.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Driver.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Driver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Driver.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\Driver.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Driver.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Driver.res" \
	"..\QCOrder\Debug\QCOrder.lib"

"$(OUTDIR)\Driver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Driver.dep")
!INCLUDE "Driver.dep"
!ELSE 
!MESSAGE Warning: cannot find "Driver.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Driver - Win32 Release" || "$(CFG)" == "Driver - Win32 Debug"
SOURCE=.\Driver.cpp

"$(INTDIR)\Driver.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Driver.pch"


SOURCE=.\Driver.rc

"$(INTDIR)\Driver.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Driver - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Driver.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Driver.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Driver - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Driver.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Driver.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "Driver - Win32 Release"

"QCOrder - Win32 Release" : 
   cd "..\QCOrder"
   $(MAKE) /$(MAKEFLAGS) /F .\QCOrder.mak CFG="QCOrder - Win32 Release" 
   cd "..\Driver"

"QCOrder - Win32 ReleaseCLEAN" : 
   cd "..\QCOrder"
   $(MAKE) /$(MAKEFLAGS) /F .\QCOrder.mak CFG="QCOrder - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Driver"

!ELSEIF  "$(CFG)" == "Driver - Win32 Debug"

"QCOrder - Win32 Debug" : 
   cd "..\QCOrder"
   $(MAKE) /$(MAKEFLAGS) /F .\QCOrder.mak CFG="QCOrder - Win32 Debug" 
   cd "..\Driver"

"QCOrder - Win32 DebugCLEAN" : 
   cd "..\QCOrder"
   $(MAKE) /$(MAKEFLAGS) /F .\QCOrder.mak CFG="QCOrder - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Driver"

!ENDIF 


!ENDIF 

