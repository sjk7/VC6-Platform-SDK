!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on QCShip2.dsp
!IF "$(CFG)" == ""
CFG=QCShip2 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to QCShip2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "QCShip2 - Win32 Debug" && "$(CFG)" != "QCShip2 - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QCShip2.mak" CFG="QCShip2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QCShip2 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "QCShip2 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "QCShip2 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\QCShip2.dll"

!ELSE 

ALL : "QCNotify - Win32 Debug" "$(OUTDIR)\QCShip2.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"QCNotify - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\QCShip2.obj"
	-@erase "$(INTDIR)\QCShip2.pch"
	-@erase "$(INTDIR)\QCShip2.res"
	-@erase "$(INTDIR)\Ship2.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\QCShip2.dll"
	-@erase "$(OUTDIR)\QCShip2.exp"
	-@erase "$(OUTDIR)\QCShip2.ilk"
	-@erase "$(OUTDIR)\QCShip2.lib"
	-@erase "$(OUTDIR)\QCShip2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\QCShip2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\QCShip2.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\QCShip2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\QCShip2.pdb" /debug /machine:$(CPU) /def:".\QCShip2.def" /out:"$(OUTDIR)\QCShip2.dll" /implib:"$(OUTDIR)\QCShip2.lib" /pdbtype:sept 
DEF_FILE= \
	".\QCShip2.def"
LINK32_OBJS= \
	"$(INTDIR)\QCShip2.obj" \
	"$(INTDIR)\Ship2.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\QCShip2.res" \
	"..\QCNotify\Debug\QCNotify.lib"

"$(OUTDIR)\QCShip2.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "QCShip2 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\QCShip2_i.c" ".\QCShip2.tlb" ".\QCShip2.h" "$(OUTDIR)\QCShip2.dll"

!ELSE 

ALL : "QCNotify - Win32 Release" ".\QCShip2_i.c" ".\QCShip2.tlb" ".\QCShip2.h" "$(OUTDIR)\QCShip2.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"QCNotify - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\QCShip2.obj"
	-@erase "$(INTDIR)\QCShip2.pch"
	-@erase "$(INTDIR)\QCShip2.res"
	-@erase "$(INTDIR)\Ship2.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\QCShip2.dll"
	-@erase "$(OUTDIR)\QCShip2.exp"
	-@erase "$(OUTDIR)\QCShip2.lib"
	-@erase ".\QCShip2.h"
	-@erase ".\QCShip2.tlb"
	-@erase ".\QCShip2_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\QCShip2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\QCShip2.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\QCShip2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\QCShip2.pdb" /machine:$(CPU) /def:".\QCShip2.def" /out:"$(OUTDIR)\QCShip2.dll" /implib:"$(OUTDIR)\QCShip2.lib" 
DEF_FILE= \
	".\QCShip2.def"
LINK32_OBJS= \
	"$(INTDIR)\QCShip2.obj" \
	"$(INTDIR)\Ship2.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\QCShip2.res" \
	"..\QCNotify\Release\QCNotify.lib"

"$(OUTDIR)\QCShip2.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("QCShip2.dep")
!INCLUDE "QCShip2.dep"
!ELSE 
!MESSAGE Warning: cannot find "QCShip2.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "QCShip2 - Win32 Debug" || "$(CFG)" == "QCShip2 - Win32 Release"
SOURCE=.\QCShip2.cpp

"$(INTDIR)\QCShip2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\QCShip2.pch" ".\QCShip2.h" ".\QCShip2_i.c"


SOURCE=.\QCShip2.idl

!IF  "$(CFG)" == "QCShip2 - Win32 Debug"

InputPath=.\QCShip2.idl

".\QCShip2.tlb"	".\QCShip2.h"	".\QCShip2_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "QCShip2.h" /iid "QCShip2_i.c" "QCShip2.idl"
<< 
	

!ELSEIF  "$(CFG)" == "QCShip2 - Win32 Release"

InputPath=.\QCShip2.idl

".\QCShip2.tlb"	".\QCShip2.h"	".\QCShip2_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "QCShip2.h" /iid "QCShip2_i.c" "QCShip2.idl"
<< 
	

!ENDIF 

SOURCE=.\QCShip2.rc

"$(INTDIR)\QCShip2.res" : $(SOURCE) "$(INTDIR)" ".\QCShip2.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Ship2.cpp

"$(INTDIR)\Ship2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\QCShip2.pch" ".\QCShip2.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "QCShip2 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\QCShip2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\QCShip2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "QCShip2 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\QCShip2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\QCShip2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "QCShip2 - Win32 Debug"

"QCNotify - Win32 Debug" : 
   cd "..\QCNotify"
   $(MAKE) /$(MAKEFLAGS) /F .\QCNotify.mak CFG="QCNotify - Win32 Debug" 
   cd "..\QCShip2"

"QCNotify - Win32 DebugCLEAN" : 
   cd "..\QCNotify"
   $(MAKE) /$(MAKEFLAGS) /F .\QCNotify.mak CFG="QCNotify - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\QCShip2"

!ELSEIF  "$(CFG)" == "QCShip2 - Win32 Release"

"QCNotify - Win32 Release" : 
   cd "..\QCNotify"
   $(MAKE) /$(MAKEFLAGS) /F .\QCNotify.mak CFG="QCNotify - Win32 Release" 
   cd "..\QCShip2"

"QCNotify - Win32 ReleaseCLEAN" : 
   cd "..\QCNotify"
   $(MAKE) /$(MAKEFLAGS) /F .\QCNotify.mak CFG="QCNotify - Win32 Release" RECURSE=1 CLEAN 
   cd "..\QCShip2"

!ENDIF 


!ENDIF 

