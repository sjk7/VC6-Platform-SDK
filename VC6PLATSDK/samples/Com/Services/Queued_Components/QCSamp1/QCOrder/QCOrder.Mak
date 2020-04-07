!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on QCOrder.dsp
!IF "$(CFG)" == ""
CFG=QCOrder - Win32 Debug
!MESSAGE No configuration specified. Defaulting to QCOrder - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "QCOrder - Win32 Release" && "$(CFG)" != "QCOrder - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QCOrder.mak" CFG="QCOrder - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QCOrder - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "QCOrder - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "QCOrder - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\QCOrder.dll"

!ELSE 

ALL : "QCShip - Win32 Release" "$(OUTDIR)\QCOrder.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"QCShip - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Order.obj"
	-@erase "$(INTDIR)\QCOrder.obj"
	-@erase "$(INTDIR)\QCOrder.pch"
	-@erase "$(INTDIR)\QCOrder.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\QCOrder.dll"
	-@erase "$(OUTDIR)\QCOrder.exp"
	-@erase "$(OUTDIR)\QCOrder.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\QCOrder.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\QCOrder.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\QCOrder.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\QCOrder.pdb" /machine:$(CPU) /def:".\QCOrder.def" /out:"$(OUTDIR)\QCOrder.dll" /implib:"$(OUTDIR)\QCOrder.lib" 
DEF_FILE= \
	".\QCOrder.def"
LINK32_OBJS= \
	"$(INTDIR)\Order.obj" \
	"$(INTDIR)\QCOrder.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\QCOrder.res" \
	"..\QCShip\Release\QCShip.lib"

"$(OUTDIR)\QCOrder.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "QCOrder - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\QCOrder_i.c" ".\QCOrder.tlb" ".\QCOrder.h" "$(OUTDIR)\QCOrder.dll"

!ELSE 

ALL : "QCShip - Win32 Debug" ".\QCOrder_i.c" ".\QCOrder.tlb" ".\QCOrder.h" "$(OUTDIR)\QCOrder.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"QCShip - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Order.obj"
	-@erase "$(INTDIR)\QCOrder.obj"
	-@erase "$(INTDIR)\QCOrder.pch"
	-@erase "$(INTDIR)\QCOrder.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\QCOrder.dll"
	-@erase "$(OUTDIR)\QCOrder.exp"
	-@erase "$(OUTDIR)\QCOrder.ilk"
	-@erase "$(OUTDIR)\QCOrder.lib"
	-@erase "$(OUTDIR)\QCOrder.pdb"
	-@erase ".\QCOrder.h"
	-@erase ".\QCOrder.tlb"
	-@erase ".\QCOrder_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\QCOrder.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\QCOrder.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\QCOrder.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\QCOrder.pdb" /debug /machine:$(CPU) /def:".\QCOrder.def" /out:"$(OUTDIR)\QCOrder.dll" /implib:"$(OUTDIR)\QCOrder.lib" /pdbtype:sept 
DEF_FILE= \
	".\QCOrder.def"
LINK32_OBJS= \
	"$(INTDIR)\Order.obj" \
	"$(INTDIR)\QCOrder.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\QCOrder.res" \
	"..\QCShip\Debug\QCShip.lib"

"$(OUTDIR)\QCOrder.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("QCOrder.dep")
!INCLUDE "QCOrder.dep"
!ELSE 
!MESSAGE Warning: cannot find "QCOrder.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "QCOrder - Win32 Release" || "$(CFG)" == "QCOrder - Win32 Debug"
SOURCE=.\Order.cpp

"$(INTDIR)\Order.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\QCOrder.pch" ".\QCOrder.h"


SOURCE=.\QCOrder.cpp

"$(INTDIR)\QCOrder.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\QCOrder.pch" ".\QCOrder.h" ".\QCOrder_i.c"


SOURCE=.\QCOrder.idl

!IF  "$(CFG)" == "QCOrder - Win32 Release"

InputPath=.\QCOrder.idl

".\QCOrder.tlb"	".\QCOrder.h"	".\QCOrder_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "QCOrder.h" /iid "QCOrder_i.c" "QCOrder.idl"
<< 
	

!ELSEIF  "$(CFG)" == "QCOrder - Win32 Debug"

InputPath=.\QCOrder.idl

".\QCOrder.tlb"	".\QCOrder.h"	".\QCOrder_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "QCOrder.h" /iid "QCOrder_i.c" "QCOrder.idl"
<< 
	

!ENDIF 

SOURCE=.\QCOrder.rc

"$(INTDIR)\QCOrder.res" : $(SOURCE) "$(INTDIR)" ".\QCOrder.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "QCOrder - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\QCOrder.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\QCOrder.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "QCOrder - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\QCOrder.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\QCOrder.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "QCOrder - Win32 Release"

"QCShip - Win32 Release" : 
   cd "..\QCShip"
   $(MAKE) /$(MAKEFLAGS) /F .\QCShip.mak CFG="QCShip - Win32 Release" 
   cd "..\QCOrder"

"QCShip - Win32 ReleaseCLEAN" : 
   cd "..\QCShip"
   $(MAKE) /$(MAKEFLAGS) /F .\QCShip.mak CFG="QCShip - Win32 Release" RECURSE=1 CLEAN 
   cd "..\QCOrder"

!ELSEIF  "$(CFG)" == "QCOrder - Win32 Debug"

"QCShip - Win32 Debug" : 
   cd "..\QCShip"
   $(MAKE) /$(MAKEFLAGS) /F .\QCShip.mak CFG="QCShip - Win32 Debug" 
   cd "..\QCOrder"

"QCShip - Win32 DebugCLEAN" : 
   cd "..\QCShip"
   $(MAKE) /$(MAKEFLAGS) /F .\QCShip.mak CFG="QCShip - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\QCOrder"

!ENDIF 


!ENDIF 

