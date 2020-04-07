!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on NewsEventClass.dsp
!IF "$(CFG)" == ""
CFG=NewsEventClass - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NewsEventClass - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "NewsEventClass - Win32 Unicode Debug" && "$(CFG)" != "NewsEventClass - Win32 Release MinSize" && "$(CFG)" != "NewsEventClass - Win32 Release MinDependency" && "$(CFG)" != "NewsEventClass - Win32 Unicode Release MinSize" && "$(CFG)" != "NewsEventClass - Win32 Unicode Release MinDependency" && "$(CFG)" != "NewsEventClass - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NewsEventClass.mak" CFG="NewsEventClass - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NewsEventClass - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NewsEventClass - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NewsEventClass - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NewsEventClass - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NewsEventClass - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NewsEventClass - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "NewsEventClass - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\NewsEventClass.dll" "$(OUTDIR)\News.tlb" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\News.tlb"
	-@erase "$(INTDIR)\NewsEvent.obj"
	-@erase "$(INTDIR)\NewsEventClass.obj"
	-@erase "$(INTDIR)\NewsEventClass.pch"
	-@erase "$(INTDIR)\NewsEventClass.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\NewsEventClass.dll"
	-@erase "$(OUTDIR)\NewsEventClass.exp"
	-@erase "$(OUTDIR)\NewsEventClass.ilk"
	-@erase "$(OUTDIR)\NewsEventClass.lib"
	-@erase "$(OUTDIR)\NewsEventClass.pdb"
	-@erase ".\NewsEventClass.h"
	-@erase ".\NewsEventClass.tlb"
	-@erase ".\NewsEventClass_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\NewsEventClass.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NewsEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\NewsEventClass.pdb" /debug /machine:$(CPU) /def:".\NewsEventClass.def" /out:"$(OUTDIR)\NewsEventClass.dll" /implib:"$(OUTDIR)\NewsEventClass.lib" /pdbtype:sept 
DEF_FILE= \
	".\NewsEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\NewsEvent.obj" \
	"$(INTDIR)\NewsEventClass.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NewsEventClass.res"

"$(OUTDIR)\NewsEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\NewsEventClass.dll
InputPath=.\DebugU\NewsEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\News.tlb" ".\NewsEventClass.tlb" ".\NewsEventClass.h" ".\NewsEventClass_i.c" "$(OUTDIR)\NewsEventClass.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\News.tlb"
	-@erase "$(INTDIR)\NewsEvent.obj"
	-@erase "$(INTDIR)\NewsEventClass.obj"
	-@erase "$(INTDIR)\NewsEventClass.pch"
	-@erase "$(INTDIR)\NewsEventClass.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\NewsEventClass.dll"
	-@erase "$(OUTDIR)\NewsEventClass.exp"
	-@erase "$(OUTDIR)\NewsEventClass.lib"
	-@erase ".\NewsEventClass.h"
	-@erase ".\NewsEventClass.tlb"
	-@erase ".\NewsEventClass_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\NewsEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NewsEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\NewsEventClass.pdb" /machine:$(CPU) /def:".\NewsEventClass.def" /out:"$(OUTDIR)\NewsEventClass.dll" /implib:"$(OUTDIR)\NewsEventClass.lib" 
DEF_FILE= \
	".\NewsEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\NewsEvent.obj" \
	"$(INTDIR)\NewsEventClass.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NewsEventClass.res"

"$(OUTDIR)\NewsEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\NewsEventClass.dll
InputPath=.\ReleaseMinSize\NewsEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\NewsEventClass.dll" "$(OUTDIR)\News.tlb" ".\NewsEventClass.tlb" ".\NewsEventClass.h" ".\NewsEventClass_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\News.tlb"
	-@erase "$(INTDIR)\NewsEvent.obj"
	-@erase "$(INTDIR)\NewsEventClass.obj"
	-@erase "$(INTDIR)\NewsEventClass.pch"
	-@erase "$(INTDIR)\NewsEventClass.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\NewsEventClass.dll"
	-@erase "$(OUTDIR)\NewsEventClass.exp"
	-@erase "$(OUTDIR)\NewsEventClass.lib"
	-@erase ".\NewsEventClass.h"
	-@erase ".\NewsEventClass.tlb"
	-@erase ".\NewsEventClass_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\NewsEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NewsEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\NewsEventClass.pdb" /machine:$(CPU) /def:".\NewsEventClass.def" /out:"$(OUTDIR)\NewsEventClass.dll" /implib:"$(OUTDIR)\NewsEventClass.lib" 
DEF_FILE= \
	".\NewsEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\NewsEvent.obj" \
	"$(INTDIR)\NewsEventClass.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NewsEventClass.res"

"$(OUTDIR)\NewsEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\NewsEventClass.dll
InputPath=.\ReleaseMinDependency\NewsEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\NewsEventClass.dll" "$(OUTDIR)\News.tlb" ".\NewsEventClass.tlb" ".\NewsEventClass.h" ".\NewsEventClass_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\News.tlb"
	-@erase "$(INTDIR)\NewsEvent.obj"
	-@erase "$(INTDIR)\NewsEventClass.obj"
	-@erase "$(INTDIR)\NewsEventClass.pch"
	-@erase "$(INTDIR)\NewsEventClass.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\NewsEventClass.dll"
	-@erase "$(OUTDIR)\NewsEventClass.exp"
	-@erase "$(OUTDIR)\NewsEventClass.lib"
	-@erase ".\NewsEventClass.h"
	-@erase ".\NewsEventClass.tlb"
	-@erase ".\NewsEventClass_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\NewsEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NewsEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\NewsEventClass.pdb" /machine:$(CPU) /def:".\NewsEventClass.def" /out:"$(OUTDIR)\NewsEventClass.dll" /implib:"$(OUTDIR)\NewsEventClass.lib" 
DEF_FILE= \
	".\NewsEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\NewsEvent.obj" \
	"$(INTDIR)\NewsEventClass.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NewsEventClass.res"

"$(OUTDIR)\NewsEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\NewsEventClass.dll
InputPath=.\ReleaseUMinSize\NewsEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\NewsEventClass.dll" "$(OUTDIR)\News.tlb" ".\NewsEventClass.tlb" ".\NewsEventClass.h" ".\NewsEventClass_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\News.tlb"
	-@erase "$(INTDIR)\NewsEvent.obj"
	-@erase "$(INTDIR)\NewsEventClass.obj"
	-@erase "$(INTDIR)\NewsEventClass.pch"
	-@erase "$(INTDIR)\NewsEventClass.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\NewsEventClass.dll"
	-@erase "$(OUTDIR)\NewsEventClass.exp"
	-@erase "$(OUTDIR)\NewsEventClass.lib"
	-@erase ".\NewsEventClass.h"
	-@erase ".\NewsEventClass.tlb"
	-@erase ".\NewsEventClass_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\NewsEventClass.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NewsEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\NewsEventClass.pdb" /machine:$(CPU) /def:".\NewsEventClass.def" /out:"$(OUTDIR)\NewsEventClass.dll" /implib:"$(OUTDIR)\NewsEventClass.lib" 
DEF_FILE= \
	".\NewsEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\NewsEvent.obj" \
	"$(INTDIR)\NewsEventClass.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NewsEventClass.res"

"$(OUTDIR)\NewsEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\NewsEventClass.dll
InputPath=.\ReleaseUMinDependency\NewsEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "..\include\News.h" "..\include\News_i.c" ".\NewsEventClass.tlb" ".\NewsEventClass.h" ".\NewsEventClass_i.c" "$(OUTDIR)\NewsEventClass.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\NewsEvent.obj"
	-@erase "$(INTDIR)\NewsEventClass.obj"
	-@erase "$(INTDIR)\NewsEventClass.pch"
	-@erase "$(INTDIR)\NewsEventClass.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\NewsEventClass.dll"
	-@erase "$(OUTDIR)\NewsEventClass.exp"
	-@erase "$(OUTDIR)\NewsEventClass.ilk"
	-@erase "$(OUTDIR)\NewsEventClass.lib"
	-@erase "$(OUTDIR)\NewsEventClass.pdb"
	-@erase "..\include\News.h"
	-@erase "..\include\News_i.c"
	-@erase ".\NewsEventClass.h"
	-@erase ".\NewsEventClass.tlb"
	-@erase ".\NewsEventClass_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\NewsEventClass.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NewsEventClass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\NewsEventClass.pdb" /debug /machine:$(CPU) /def:".\NewsEventClass.def" /out:"$(OUTDIR)\NewsEventClass.dll" /implib:"$(OUTDIR)\NewsEventClass.lib" /pdbtype:sept 
DEF_FILE= \
	".\NewsEventClass.def"
LINK32_OBJS= \
	"$(INTDIR)\NewsEvent.obj" \
	"$(INTDIR)\NewsEventClass.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\NewsEventClass.res"

"$(OUTDIR)\NewsEventClass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\NewsEventClass.dll
InputPath=.\Debug\NewsEventClass.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("NewsEventClass.dep")
!INCLUDE "NewsEventClass.dep"
!ELSE 
!MESSAGE Warning: cannot find "NewsEventClass.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NewsEventClass - Win32 Unicode Debug" || "$(CFG)" == "NewsEventClass - Win32 Release MinSize" || "$(CFG)" == "NewsEventClass - Win32 Release MinDependency" || "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinSize" || "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinDependency" || "$(CFG)" == "NewsEventClass - Win32 Debug"
SOURCE=..\include\News.idl

!IF  "$(CFG)" == "NewsEventClass - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\News.tlb" 

"$(INTDIR)\News.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\News.tlb" 

"$(INTDIR)\News.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\News.tlb" 

"$(INTDIR)\News.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\News.tlb" 

"$(INTDIR)\News.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\News.tlb" 

"$(INTDIR)\News.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Debug"

MTL_SWITCHES=/I "..\include" /h "..\include\News.h" /iid "..\include\News_i.c" 

"..\include\News.h"	"..\include\News_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\NewsEvent.cpp

!IF  "$(CFG)" == "NewsEventClass - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\NewsEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch" ".\NewsEventClass.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\NewsEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\NewsEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\NewsEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\NewsEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\NewsEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\NewsEventClass.cpp

!IF  "$(CFG)" == "NewsEventClass - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\NewsEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch" ".\NewsEventClass.h" ".\NewsEventClass_i.c"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\NewsEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\NewsEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\NewsEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\NewsEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\NewsEventClass.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\NewsEventClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\NewsEventClass.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\NewsEventClass.idl

!IF  "$(CFG)" == "NewsEventClass - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\NewsEventClass.tlb" /h "NewsEventClass.h" /iid "NewsEventClass_i.c" /Oicf 

".\NewsEventClass.tlb"	".\NewsEventClass.h"	".\NewsEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\NewsEventClass.tlb" /h "NewsEventClass.h" /iid "NewsEventClass_i.c" /Oicf 

".\NewsEventClass.tlb"	".\NewsEventClass.h"	".\NewsEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\NewsEventClass.tlb" /h "NewsEventClass.h" /iid "NewsEventClass_i.c" /Oicf 

".\NewsEventClass.tlb"	".\NewsEventClass.h"	".\NewsEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\NewsEventClass.tlb" /h "NewsEventClass.h" /iid "NewsEventClass_i.c" /Oicf 

".\NewsEventClass.tlb"	".\NewsEventClass.h"	".\NewsEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\NewsEventClass.tlb" /h "NewsEventClass.h" /iid "NewsEventClass_i.c" /Oicf 

".\NewsEventClass.tlb"	".\NewsEventClass.h"	".\NewsEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Debug"

MTL_SWITCHES=/I "..\include" /tlb ".\NewsEventClass.tlb" /h "NewsEventClass.h" /iid "NewsEventClass_i.c" /Oicf 

".\NewsEventClass.tlb"	".\NewsEventClass.h"	".\NewsEventClass_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\NewsEventClass.rc

"$(INTDIR)\NewsEventClass.res" : $(SOURCE) "$(INTDIR)" ".\NewsEventClass.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "NewsEventClass - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\NewsEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NewsEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NewsEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NewsEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NewsEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\NewsEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NewsEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NewsEventClass - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\NewsEventClass.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NewsEventClass.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

