!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on STAObject.dsp
!IF "$(CFG)" == ""
CFG=STAObject - Win32 Debug
!MESSAGE No configuration specified. Defaulting to STAObject - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "STAObject - Win32 Release MinSize" && "$(CFG)" != "STAObject - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "STAObject.mak" CFG="STAObject - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "STAObject - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "STAObject - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "STAObject - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\STAObject.tlb" ".\STAObject.h" ".\STAObject_i.c" "$(OUTDIR)\STAObject.pch" "$(OUTDIR)\STAObject.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\STAObject.obj"
	-@erase "$(INTDIR)\STAObject.pch"
	-@erase "$(INTDIR)\STAObject.res"
	-@erase "$(INTDIR)\STATest.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\STAObject.dll"
	-@erase "$(OUTDIR)\STAObject.exp"
	-@erase "$(OUTDIR)\STAObject.lib"
	-@erase ".\STAObject.h"
	-@erase ".\STAObject.tlb"
	-@erase ".\STAObject_i.c"
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\STAObject.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\STAObject.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\STAObject.pdb" /machine:$(CPU) /def:".\STAObject.def" /out:"$(OUTDIR)\STAObject.dll" /implib:"$(OUTDIR)\STAObject.lib" 
DEF_FILE= \
	".\STAObject.def"
LINK32_OBJS= \
	"$(INTDIR)\STAObject.obj" \
	"$(INTDIR)\STATest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\STAObject.res"

"$(OUTDIR)\STAObject.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\STAObject.dll
InputPath=.\ReleaseMinSize\STAObject.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "STAObject - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\STAObject.tlb" ".\STAObject.h" ".\STAObject_i.c" "$(OUTDIR)\STAObject.pch" "$(OUTDIR)\STAObject.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\STAObject.obj"
	-@erase "$(INTDIR)\STAObject.pch"
	-@erase "$(INTDIR)\STAObject.res"
	-@erase "$(INTDIR)\STATest.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\STAObject.dll"
	-@erase "$(OUTDIR)\STAObject.exp"
	-@erase "$(OUTDIR)\STAObject.ilk"
	-@erase "$(OUTDIR)\STAObject.lib"
	-@erase "$(OUTDIR)\STAObject.pdb"
	-@erase ".\STAObject.h"
	-@erase ".\STAObject.tlb"
	-@erase ".\STAObject_i.c"
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\STAObject.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\STAObject.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\STAObject.pdb" /debug /machine:$(CPU) /def:".\STAObject.def" /out:"$(OUTDIR)\STAObject.dll" /implib:"$(OUTDIR)\STAObject.lib" /pdbtype:sept 
DEF_FILE= \
	".\STAObject.def"
LINK32_OBJS= \
	"$(INTDIR)\STAObject.obj" \
	"$(INTDIR)\STATest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\STAObject.res"

"$(OUTDIR)\STAObject.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\STAObject.dll
InputPath=.\Debug\STAObject.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("STAObject.dep")
!INCLUDE "STAObject.dep"
!ELSE 
!MESSAGE Warning: cannot find "STAObject.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "STAObject - Win32 Release MinSize" || "$(CFG)" == "STAObject - Win32 Debug"
SOURCE=.\STAObject.cpp

"$(INTDIR)\STAObject.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\STAObject.idl

!IF  "$(CFG)" == "STAObject - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\STAObject.tlb" /h "STAObject.h" /iid "STAObject_i.c" /Oicf 

".\STAObject.tlb"	".\STAObject.h"	".\STAObject_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "STAObject - Win32 Debug"

MTL_SWITCHES=/tlb ".\STAObject.tlb" /h "STAObject.h" /iid "STAObject_i.c" /Oicf 

".\STAObject.tlb"	".\STAObject.h"	".\STAObject_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\STAObject.rc

"$(INTDIR)\STAObject.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\STATest.cpp

"$(INTDIR)\STATest.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "STAObject - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\STAObject.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\STAObject.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "STAObject - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\STAObject.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\STAObject.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

