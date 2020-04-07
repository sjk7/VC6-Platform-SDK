!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on QCShip.dsp
!IF "$(CFG)" == ""
CFG=QCShip - Win32 Debug
!MESSAGE No configuration specified. Defaulting to QCShip - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "QCShip - Win32 Release" && "$(CFG)" != "QCShip - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QCShip.mak" CFG="QCShip - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QCShip - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "QCShip - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QCShip - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\QCShip.dll"

!ELSE 

ALL : "QCNotify - Win32 Release" "$(OUTDIR)\QCShip.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"QCNotify - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\QCShip.obj"
	-@erase "$(INTDIR)\QCShip.pch"
	-@erase "$(INTDIR)\QCShip.res"
	-@erase "$(INTDIR)\Ship.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\QCShip.dll"
	-@erase "$(OUTDIR)\QCShip.exp"
	-@erase "$(OUTDIR)\QCShip.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\QCShip.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\QCShip.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\QCShip.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\QCShip.pdb" /machine:$(CPU) /def:".\QCShip.def" /out:"$(OUTDIR)\QCShip.dll" /implib:"$(OUTDIR)\QCShip.lib" 
DEF_FILE= \
	".\QCShip.def"
LINK32_OBJS= \
	"$(INTDIR)\QCShip.obj" \
	"$(INTDIR)\Ship.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\QCShip.res" \
	"..\QCNotify\Release\QCNotify.lib"

"$(OUTDIR)\QCShip.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "QCShip - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\QCShip_i.c" ".\QCShip.tlb" ".\QCShip.h" "$(OUTDIR)\QCShip.dll"

!ELSE 

ALL : "QCNotify - Win32 Debug" ".\QCShip_i.c" ".\QCShip.tlb" ".\QCShip.h" "$(OUTDIR)\QCShip.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"QCNotify - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\QCShip.obj"
	-@erase "$(INTDIR)\QCShip.pch"
	-@erase "$(INTDIR)\QCShip.res"
	-@erase "$(INTDIR)\Ship.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\QCShip.dll"
	-@erase "$(OUTDIR)\QCShip.exp"
	-@erase "$(OUTDIR)\QCShip.ilk"
	-@erase "$(OUTDIR)\QCShip.lib"
	-@erase "$(OUTDIR)\QCShip.pdb"
	-@erase ".\QCShip.h"
	-@erase ".\QCShip.tlb"
	-@erase ".\QCShip_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\QCShip.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\QCShip.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\QCShip.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\QCShip.pdb" /debug /machine:$(CPU) /def:".\QCShip.def" /out:"$(OUTDIR)\QCShip.dll" /implib:"$(OUTDIR)\QCShip.lib" /pdbtype:sept 
DEF_FILE= \
	".\QCShip.def"
LINK32_OBJS= \
	"$(INTDIR)\QCShip.obj" \
	"$(INTDIR)\Ship.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\QCShip.res" \
	"..\QCNotify\Debug\QCNotify.lib"

"$(OUTDIR)\QCShip.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("QCShip.dep")
!INCLUDE "QCShip.dep"
!ELSE 
!MESSAGE Warning: cannot find "QCShip.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "QCShip - Win32 Release" || "$(CFG)" == "QCShip - Win32 Debug"
SOURCE=.\QCShip.cpp

"$(INTDIR)\QCShip.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\QCShip.pch" ".\QCShip.h" ".\QCShip_i.c"


SOURCE=.\QCShip.idl

!IF  "$(CFG)" == "QCShip - Win32 Release"

InputPath=.\QCShip.idl

".\QCShip.tlb"	".\QCShip.h"	".\QCShip_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "QCShip.h" /iid "QCShip_i.c" "QCShip.idl"
<< 
	

!ELSEIF  "$(CFG)" == "QCShip - Win32 Debug"

InputPath=.\QCShip.idl

".\QCShip.tlb"	".\QCShip.h"	".\QCShip_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "QCShip.h" /iid "QCShip_i.c" "QCShip.idl"
<< 
	

!ENDIF 

SOURCE=.\QCShip.rc

"$(INTDIR)\QCShip.res" : $(SOURCE) "$(INTDIR)" ".\QCShip.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Ship.cpp

"$(INTDIR)\Ship.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\QCShip.pch" ".\QCShip.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "QCShip - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\QCShip.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\QCShip.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "QCShip - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\QCShip.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\QCShip.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "QCShip - Win32 Release"

"QCNotify - Win32 Release" : 
   cd "..\QCNotify"
   $(MAKE) /$(MAKEFLAGS) /F .\QCNotify.mak CFG="QCNotify - Win32 Release" 
   cd "..\QCShip"

"QCNotify - Win32 ReleaseCLEAN" : 
   cd "..\QCNotify"
   $(MAKE) /$(MAKEFLAGS) /F .\QCNotify.mak CFG="QCNotify - Win32 Release" RECURSE=1 CLEAN 
   cd "..\QCShip"

!ELSEIF  "$(CFG)" == "QCShip - Win32 Debug"

"QCNotify - Win32 Debug" : 
   cd "..\QCNotify"
   $(MAKE) /$(MAKEFLAGS) /F .\QCNotify.mak CFG="QCNotify - Win32 Debug" 
   cd "..\QCShip"

"QCNotify - Win32 DebugCLEAN" : 
   cd "..\QCNotify"
   $(MAKE) /$(MAKEFLAGS) /F .\QCNotify.mak CFG="QCNotify - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\QCShip"

!ENDIF 


!ENDIF 

