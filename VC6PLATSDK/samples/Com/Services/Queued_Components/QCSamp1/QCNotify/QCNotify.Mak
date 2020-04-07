!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on QCNotify.dsp
!IF "$(CFG)" == ""
CFG=QCNotify - Win32 Debug
!MESSAGE No configuration specified. Defaulting to QCNotify - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "QCNotify - Win32 Release" && "$(CFG)" != "QCNotify - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QCNotify.mak" CFG="QCNotify - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QCNotify - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "QCNotify - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "QCNotify - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\QCNotify.dll"


CLEAN :
	-@erase "$(INTDIR)\Notify.obj"
	-@erase "$(INTDIR)\QCNotify.obj"
	-@erase "$(INTDIR)\QCNotify.pch"
	-@erase "$(INTDIR)\QCNotify.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\QCNotify.dll"
	-@erase "$(OUTDIR)\QCNotify.exp"
	-@erase "$(OUTDIR)\QCNotify.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\QCNotify.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\QCNotify.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\QCNotify.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\QCNotify.pdb" /machine:$(CPU) /def:".\QCNotify.def" /out:"$(OUTDIR)\QCNotify.dll" /implib:"$(OUTDIR)\QCNotify.lib" 
DEF_FILE= \
	".\QCNotify.def"
LINK32_OBJS= \
	"$(INTDIR)\Notify.obj" \
	"$(INTDIR)\QCNotify.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\QCNotify.res"

"$(OUTDIR)\QCNotify.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "QCNotify - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\QCNotify_i.c" ".\QCNotify.tlb" ".\QCNotify.h" "$(OUTDIR)\QCNotify.dll"


CLEAN :
	-@erase "$(INTDIR)\Notify.obj"
	-@erase "$(INTDIR)\QCNotify.obj"
	-@erase "$(INTDIR)\QCNotify.pch"
	-@erase "$(INTDIR)\QCNotify.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\QCNotify.dll"
	-@erase "$(OUTDIR)\QCNotify.exp"
	-@erase "$(OUTDIR)\QCNotify.ilk"
	-@erase "$(OUTDIR)\QCNotify.lib"
	-@erase "$(OUTDIR)\QCNotify.pdb"
	-@erase ".\QCNotify.h"
	-@erase ".\QCNotify.tlb"
	-@erase ".\QCNotify_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\QCNotify.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\QCNotify.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\QCNotify.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\QCNotify.pdb" /debug /machine:$(CPU) /def:".\QCNotify.def" /out:"$(OUTDIR)\QCNotify.dll" /implib:"$(OUTDIR)\QCNotify.lib" /pdbtype:sept 
DEF_FILE= \
	".\QCNotify.def"
LINK32_OBJS= \
	"$(INTDIR)\Notify.obj" \
	"$(INTDIR)\QCNotify.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\QCNotify.res"

"$(OUTDIR)\QCNotify.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("QCNotify.dep")
!INCLUDE "QCNotify.dep"
!ELSE 
!MESSAGE Warning: cannot find "QCNotify.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "QCNotify - Win32 Release" || "$(CFG)" == "QCNotify - Win32 Debug"
SOURCE=.\Notify.cpp

"$(INTDIR)\Notify.obj" : $(SOURCE) "$(INTDIR)" ".\QCNotify.h" "$(INTDIR)\QCNotify.pch"


SOURCE=.\QCNotify.cpp

"$(INTDIR)\QCNotify.obj" : $(SOURCE) "$(INTDIR)" ".\QCNotify.h" ".\QCNotify_i.c" "$(INTDIR)\QCNotify.pch"


SOURCE=.\QCNotify.idl

!IF  "$(CFG)" == "QCNotify - Win32 Release"

InputPath=.\QCNotify.idl

".\QCNotify.tlb"	".\QCNotify.h"	".\QCNotify_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "QCNotify.h" /iid "QCNotify_i.c" "QCNotify.idl"
<< 
	

!ELSEIF  "$(CFG)" == "QCNotify - Win32 Debug"

InputPath=.\QCNotify.idl

".\QCNotify.tlb"	".\QCNotify.h"	".\QCNotify_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "QCNotify.h" /iid "QCNotify_i.c" "QCNotify.idl"
<< 
	

!ENDIF 

SOURCE=.\QCNotify.rc

"$(INTDIR)\QCNotify.res" : $(SOURCE) "$(INTDIR)" ".\QCNotify.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "QCNotify - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\QCNotify.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\QCNotify.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "QCNotify - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\QCNotify.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\QCNotify.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

