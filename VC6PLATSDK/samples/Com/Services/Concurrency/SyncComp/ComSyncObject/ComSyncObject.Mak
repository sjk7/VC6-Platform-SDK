!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on ComSyncObject.dsp
!IF "$(CFG)" == ""
CFG=ComSyncObject - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ComSyncObject - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "ComSyncObject - Win32 Release MinSize" && "$(CFG)" != "ComSyncObject - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComSyncObject.mak" CFG="ComSyncObject - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComSyncObject - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComSyncObject - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ComSyncObject - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\ComSyncObject.tlb" ".\ComSyncObject.h" ".\ComSyncObject_i.c" "$(OUTDIR)\ComSyncObject.pch" "$(OUTDIR)\ComSyncObject.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ComSyncObject.obj"
	-@erase "$(INTDIR)\ComSyncObject.pch"
	-@erase "$(INTDIR)\ComSyncObject.res"
	-@erase "$(INTDIR)\ComSyncTest.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ComSyncObject.dll"
	-@erase "$(OUTDIR)\ComSyncObject.exp"
	-@erase "$(OUTDIR)\ComSyncObject.lib"
	-@erase ".\ComSyncObject.h"
	-@erase ".\ComSyncObject.tlb"
	-@erase ".\ComSyncObject_i.c"
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSyncObject.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSyncObject.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ComSyncObject.pdb" /machine:$(CPU) /def:".\ComSyncObject.def" /out:"$(OUTDIR)\ComSyncObject.dll" /implib:"$(OUTDIR)\ComSyncObject.lib" 
DEF_FILE= \
	".\ComSyncObject.def"
LINK32_OBJS= \
	"$(INTDIR)\ComSyncObject.obj" \
	"$(INTDIR)\ComSyncTest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ComSyncObject.res"

"$(OUTDIR)\ComSyncObject.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\ComSyncObject.dll
InputPath=.\ReleaseMinSize\ComSyncObject.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ComSyncObject - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\ComSyncObject.tlb" ".\ComSyncObject.h" ".\ComSyncObject_i.c" "$(OUTDIR)\ComSyncObject.pch" "$(OUTDIR)\ComSyncObject.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ComSyncObject.obj"
	-@erase "$(INTDIR)\ComSyncObject.pch"
	-@erase "$(INTDIR)\ComSyncObject.res"
	-@erase "$(INTDIR)\ComSyncTest.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ComSyncObject.dll"
	-@erase "$(OUTDIR)\ComSyncObject.exp"
	-@erase "$(OUTDIR)\ComSyncObject.ilk"
	-@erase "$(OUTDIR)\ComSyncObject.lib"
	-@erase "$(OUTDIR)\ComSyncObject.pdb"
	-@erase ".\ComSyncObject.h"
	-@erase ".\ComSyncObject.tlb"
	-@erase ".\ComSyncObject_i.c"
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSyncObject.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSyncObject.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ComSyncObject.pdb" /debug /machine:$(CPU) /def:".\ComSyncObject.def" /out:"$(OUTDIR)\ComSyncObject.dll" /implib:"$(OUTDIR)\ComSyncObject.lib" /pdbtype:sept 
DEF_FILE= \
	".\ComSyncObject.def"
LINK32_OBJS= \
	"$(INTDIR)\ComSyncObject.obj" \
	"$(INTDIR)\ComSyncTest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ComSyncObject.res"

"$(OUTDIR)\ComSyncObject.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ComSyncObject.dll
InputPath=.\Debug\ComSyncObject.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ComSyncObject.dep")
!INCLUDE "ComSyncObject.dep"
!ELSE 
!MESSAGE Warning: cannot find "ComSyncObject.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ComSyncObject - Win32 Release MinSize" || "$(CFG)" == "ComSyncObject - Win32 Debug"
SOURCE=.\ComSyncObject.cpp

"$(INTDIR)\ComSyncObject.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ComSyncObject.idl

!IF  "$(CFG)" == "ComSyncObject - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\ComSyncObject.tlb" /h "ComSyncObject.h" /iid "ComSyncObject_i.c" /Oicf 

".\ComSyncObject.tlb"	".\ComSyncObject.h"	".\ComSyncObject_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSyncObject - Win32 Debug"

MTL_SWITCHES=/tlb ".\ComSyncObject.tlb" /h "ComSyncObject.h" /iid "ComSyncObject_i.c" /Oicf 

".\ComSyncObject.tlb"	".\ComSyncObject.h"	".\ComSyncObject_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ComSyncObject.rc

"$(INTDIR)\ComSyncObject.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ComSyncTest.cpp

"$(INTDIR)\ComSyncTest.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ComSyncObject - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ComSyncObject.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ComSyncObject.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSyncObject - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\ComSyncObject.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ComSyncObject.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

