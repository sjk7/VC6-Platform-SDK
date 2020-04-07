!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on FreeObject.dsp
!IF "$(CFG)" == ""
CFG=FreeObject - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FreeObject - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "FreeObject - Win32 Release MinSize" && "$(CFG)" != "FreeObject - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FreeObject.mak" CFG="FreeObject - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FreeObject - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FreeObject - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FreeObject - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\FreeObject.tlb" ".\FreeObject.h" ".\FreeObject_i.c" "$(OUTDIR)\FreeObject.pch" "$(OUTDIR)\FreeObject.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\FreeObject.obj"
	-@erase "$(INTDIR)\FreeObject.pch"
	-@erase "$(INTDIR)\FreeObject.res"
	-@erase "$(INTDIR)\FreeTest.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FreeObject.dll"
	-@erase "$(OUTDIR)\FreeObject.exp"
	-@erase "$(OUTDIR)\FreeObject.lib"
	-@erase ".\FreeObject.h"
	-@erase ".\FreeObject.tlb"
	-@erase ".\FreeObject_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FreeObject.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FreeObject.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\FreeObject.pdb" /machine:$(CPU) /def:".\FreeObject.def" /out:"$(OUTDIR)\FreeObject.dll" /implib:"$(OUTDIR)\FreeObject.lib" 
DEF_FILE= \
	".\FreeObject.def"
LINK32_OBJS= \
	"$(INTDIR)\FreeObject.obj" \
	"$(INTDIR)\FreeTest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FreeObject.res"

"$(OUTDIR)\FreeObject.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\FreeObject.dll
InputPath=.\ReleaseMinSize\FreeObject.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "FreeObject - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\FreeObject.tlb" ".\FreeObject.h" ".\FreeObject_i.c" "$(OUTDIR)\FreeObject.pch" "$(OUTDIR)\FreeObject.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\FreeObject.obj"
	-@erase "$(INTDIR)\FreeObject.pch"
	-@erase "$(INTDIR)\FreeObject.res"
	-@erase "$(INTDIR)\FreeTest.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\FreeObject.dll"
	-@erase "$(OUTDIR)\FreeObject.exp"
	-@erase "$(OUTDIR)\FreeObject.ilk"
	-@erase "$(OUTDIR)\FreeObject.lib"
	-@erase "$(OUTDIR)\FreeObject.pdb"
	-@erase ".\FreeObject.h"
	-@erase ".\FreeObject.tlb"
	-@erase ".\FreeObject_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FreeObject.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FreeObject.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\FreeObject.pdb" /debug /machine:$(CPU) /def:".\FreeObject.def" /out:"$(OUTDIR)\FreeObject.dll" /implib:"$(OUTDIR)\FreeObject.lib" /pdbtype:sept 
DEF_FILE= \
	".\FreeObject.def"
LINK32_OBJS= \
	"$(INTDIR)\FreeObject.obj" \
	"$(INTDIR)\FreeTest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FreeObject.res"

"$(OUTDIR)\FreeObject.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\FreeObject.dll
InputPath=.\Debug\FreeObject.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FreeObject.dep")
!INCLUDE "FreeObject.dep"
!ELSE 
!MESSAGE Warning: cannot find "FreeObject.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FreeObject - Win32 Release MinSize" || "$(CFG)" == "FreeObject - Win32 Debug"
SOURCE=.\FreeObject.cpp

"$(INTDIR)\FreeObject.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FreeObject.idl

!IF  "$(CFG)" == "FreeObject - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\FreeObject.tlb" /h "FreeObject.h" /iid "FreeObject_i.c" /Oicf 

".\FreeObject.tlb"	".\FreeObject.h"	".\FreeObject_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FreeObject - Win32 Debug"

MTL_SWITCHES=/tlb ".\FreeObject.tlb" /h "FreeObject.h" /iid "FreeObject_i.c" /Oicf 

".\FreeObject.tlb"	".\FreeObject.h"	".\FreeObject_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\FreeObject.rc

"$(INTDIR)\FreeObject.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\FreeTest.cpp

"$(INTDIR)\FreeTest.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "FreeObject - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FreeObject.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FreeObject.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FreeObject - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\FreeObject.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FreeObject.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

