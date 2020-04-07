!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on ByotTransaction.dsp
!IF "$(CFG)" == ""
CFG=ByotTransaction - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ByotTransaction - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "ByotTransaction - Win32 Unicode Debug" && "$(CFG)" != "ByotTransaction - Win32 Release MinSize" && "$(CFG)" != "ByotTransaction - Win32 Release MinDependency" && "$(CFG)" != "ByotTransaction - Win32 Unicode Release MinSize" && "$(CFG)" != "ByotTransaction - Win32 Unicode Release MinDependency" && "$(CFG)" != "ByotTransaction - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ByotTransaction.mak" CFG="ByotTransaction - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ByotTransaction - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ByotTransaction - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ByotTransaction - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ByotTransaction - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ByotTransaction - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ByotTransaction - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ByotTransaction - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\ByotTransaction.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ByotTransaction.obj"
	-@erase "$(INTDIR)\ByotTransaction.pch"
	-@erase "$(INTDIR)\ByotTransaction.res"
	-@erase "$(INTDIR)\ByotTransObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ByotTransaction.dll"
	-@erase "$(OUTDIR)\ByotTransaction.exp"
	-@erase "$(OUTDIR)\ByotTransaction.ilk"
	-@erase "$(OUTDIR)\ByotTransaction.lib"
	-@erase "$(OUTDIR)\ByotTransaction.pdb"
	-@erase ".\ByotTransaction.h"
	-@erase ".\ByotTransaction.tlb"
	-@erase ".\ByotTransaction_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ByotTransaction.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ByotTransaction.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ByotTransaction.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comsvcs.lib svcguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ByotTransaction.pdb" /debug /machine:$(CPU) /def:".\ByotTransaction.def" /out:"$(OUTDIR)\ByotTransaction.dll" /implib:"$(OUTDIR)\ByotTransaction.lib" /pdbtype:sept 
DEF_FILE= \
	".\ByotTransaction.def"
LINK32_OBJS= \
	"$(INTDIR)\ByotTransaction.obj" \
	"$(INTDIR)\ByotTransObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ByotTransaction.res"

"$(OUTDIR)\ByotTransaction.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\ByotTransaction.dll
InputPath=.\DebugU\ByotTransaction.dll
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
	

!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\ByotTransaction.dll" ".\ByotTransaction.tlb" ".\ByotTransaction.h" ".\ByotTransaction_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ByotTransaction.obj"
	-@erase "$(INTDIR)\ByotTransaction.pch"
	-@erase "$(INTDIR)\ByotTransaction.res"
	-@erase "$(INTDIR)\ByotTransObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ByotTransaction.dll"
	-@erase "$(OUTDIR)\ByotTransaction.exp"
	-@erase "$(OUTDIR)\ByotTransaction.lib"
	-@erase ".\ByotTransaction.h"
	-@erase ".\ByotTransaction.tlb"
	-@erase ".\ByotTransaction_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ByotTransaction.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ByotTransaction.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ByotTransaction.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comsvcs.lib svcguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ByotTransaction.pdb" /machine:$(CPU) /def:".\ByotTransaction.def" /out:"$(OUTDIR)\ByotTransaction.dll" /implib:"$(OUTDIR)\ByotTransaction.lib" 
DEF_FILE= \
	".\ByotTransaction.def"
LINK32_OBJS= \
	"$(INTDIR)\ByotTransaction.obj" \
	"$(INTDIR)\ByotTransObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ByotTransaction.res"

"$(OUTDIR)\ByotTransaction.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\ByotTransaction.dll
InputPath=.\ReleaseMinSize\ByotTransaction.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\ByotTransaction.dll" ".\ByotTransaction.tlb" ".\ByotTransaction.h" ".\ByotTransaction_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ByotTransaction.obj"
	-@erase "$(INTDIR)\ByotTransaction.pch"
	-@erase "$(INTDIR)\ByotTransaction.res"
	-@erase "$(INTDIR)\ByotTransObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ByotTransaction.dll"
	-@erase "$(OUTDIR)\ByotTransaction.exp"
	-@erase "$(OUTDIR)\ByotTransaction.lib"
	-@erase ".\ByotTransaction.h"
	-@erase ".\ByotTransaction.tlb"
	-@erase ".\ByotTransaction_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ByotTransaction.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ByotTransaction.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ByotTransaction.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comsvcs.lib svcguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ByotTransaction.pdb" /machine:$(CPU) /def:".\ByotTransaction.def" /out:"$(OUTDIR)\ByotTransaction.dll" /implib:"$(OUTDIR)\ByotTransaction.lib" 
DEF_FILE= \
	".\ByotTransaction.def"
LINK32_OBJS= \
	"$(INTDIR)\ByotTransaction.obj" \
	"$(INTDIR)\ByotTransObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ByotTransaction.res"

"$(OUTDIR)\ByotTransaction.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\ByotTransaction.dll
InputPath=.\ReleaseMinDependency\ByotTransaction.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\ByotTransaction.dll" ".\ByotTransaction.tlb" ".\ByotTransaction.h" ".\ByotTransaction_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ByotTransaction.obj"
	-@erase "$(INTDIR)\ByotTransaction.pch"
	-@erase "$(INTDIR)\ByotTransaction.res"
	-@erase "$(INTDIR)\ByotTransObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ByotTransaction.dll"
	-@erase "$(OUTDIR)\ByotTransaction.exp"
	-@erase "$(OUTDIR)\ByotTransaction.lib"
	-@erase ".\ByotTransaction.h"
	-@erase ".\ByotTransaction.tlb"
	-@erase ".\ByotTransaction_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ByotTransaction.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ByotTransaction.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ByotTransaction.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comsvcs.lib svcguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ByotTransaction.pdb" /machine:$(CPU) /def:".\ByotTransaction.def" /out:"$(OUTDIR)\ByotTransaction.dll" /implib:"$(OUTDIR)\ByotTransaction.lib" 
DEF_FILE= \
	".\ByotTransaction.def"
LINK32_OBJS= \
	"$(INTDIR)\ByotTransaction.obj" \
	"$(INTDIR)\ByotTransObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ByotTransaction.res"

"$(OUTDIR)\ByotTransaction.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\ByotTransaction.dll
InputPath=.\ReleaseUMinSize\ByotTransaction.dll
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
	

!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\ByotTransaction.dll" ".\ByotTransaction.tlb" ".\ByotTransaction.h" ".\ByotTransaction_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ByotTransaction.obj"
	-@erase "$(INTDIR)\ByotTransaction.pch"
	-@erase "$(INTDIR)\ByotTransaction.res"
	-@erase "$(INTDIR)\ByotTransObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ByotTransaction.dll"
	-@erase "$(OUTDIR)\ByotTransaction.exp"
	-@erase "$(OUTDIR)\ByotTransaction.lib"
	-@erase ".\ByotTransaction.h"
	-@erase ".\ByotTransaction.tlb"
	-@erase ".\ByotTransaction_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ByotTransaction.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ByotTransaction.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ByotTransaction.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comsvcs.lib svcguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ByotTransaction.pdb" /machine:$(CPU) /def:".\ByotTransaction.def" /out:"$(OUTDIR)\ByotTransaction.dll" /implib:"$(OUTDIR)\ByotTransaction.lib" 
DEF_FILE= \
	".\ByotTransaction.def"
LINK32_OBJS= \
	"$(INTDIR)\ByotTransaction.obj" \
	"$(INTDIR)\ByotTransObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ByotTransaction.res"

"$(OUTDIR)\ByotTransaction.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\ByotTransaction.dll
InputPath=.\ReleaseUMinDependency\ByotTransaction.dll
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
	

!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\ByotTransaction.tlb" ".\ByotTransaction.h" ".\ByotTransaction_i.c" "$(OUTDIR)\ByotTransaction.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ByotTransaction.obj"
	-@erase "$(INTDIR)\ByotTransaction.pch"
	-@erase "$(INTDIR)\ByotTransaction.res"
	-@erase "$(INTDIR)\ByotTransObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ByotTransaction.dll"
	-@erase "$(OUTDIR)\ByotTransaction.exp"
	-@erase "$(OUTDIR)\ByotTransaction.ilk"
	-@erase "$(OUTDIR)\ByotTransaction.lib"
	-@erase "$(OUTDIR)\ByotTransaction.pdb"
	-@erase ".\ByotTransaction.h"
	-@erase ".\ByotTransaction.tlb"
	-@erase ".\ByotTransaction_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\ByotTransaction.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ByotTransaction.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ByotTransaction.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=svcguid.lib comsvcs.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ByotTransaction.pdb" /debug /machine:$(CPU) /def:".\ByotTransaction.def" /out:"$(OUTDIR)\ByotTransaction.dll" /implib:"$(OUTDIR)\ByotTransaction.lib" /pdbtype:sept 
DEF_FILE= \
	".\ByotTransaction.def"
LINK32_OBJS= \
	"$(INTDIR)\ByotTransaction.obj" \
	"$(INTDIR)\ByotTransObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ByotTransaction.res"

"$(OUTDIR)\ByotTransaction.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ByotTransaction.dll
InputPath=.\Debug\ByotTransaction.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ByotTransaction.dep")
!INCLUDE "ByotTransaction.dep"
!ELSE 
!MESSAGE Warning: cannot find "ByotTransaction.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ByotTransaction - Win32 Unicode Debug" || "$(CFG)" == "ByotTransaction - Win32 Release MinSize" || "$(CFG)" == "ByotTransaction - Win32 Release MinDependency" || "$(CFG)" == "ByotTransaction - Win32 Unicode Release MinSize" || "$(CFG)" == "ByotTransaction - Win32 Unicode Release MinDependency" || "$(CFG)" == "ByotTransaction - Win32 Debug"
SOURCE=.\ByotTransaction.cpp

"$(INTDIR)\ByotTransaction.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ByotTransaction.pch" ".\ByotTransaction.h" ".\ByotTransaction_i.c"


SOURCE=.\ByotTransaction.idl

!IF  "$(CFG)" == "ByotTransaction - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\ByotTransaction.tlb" /h "ByotTransaction.h" /iid "ByotTransaction_i.c" /Oicf 

".\ByotTransaction.tlb"	".\ByotTransaction.h"	".\ByotTransaction_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\ByotTransaction.tlb" /h "ByotTransaction.h" /iid "ByotTransaction_i.c" /Oicf 

".\ByotTransaction.tlb"	".\ByotTransaction.h"	".\ByotTransaction_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\ByotTransaction.tlb" /h "ByotTransaction.h" /iid "ByotTransaction_i.c" /Oicf 

".\ByotTransaction.tlb"	".\ByotTransaction.h"	".\ByotTransaction_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\ByotTransaction.tlb" /h "ByotTransaction.h" /iid "ByotTransaction_i.c" /Oicf 

".\ByotTransaction.tlb"	".\ByotTransaction.h"	".\ByotTransaction_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\ByotTransaction.tlb" /h "ByotTransaction.h" /iid "ByotTransaction_i.c" /Oicf 

".\ByotTransaction.tlb"	".\ByotTransaction.h"	".\ByotTransaction_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Debug"

MTL_SWITCHES=/tlb ".\ByotTransaction.tlb" /h "ByotTransaction.h" /iid "ByotTransaction_i.c" /Oicf 

".\ByotTransaction.tlb"	".\ByotTransaction.h"	".\ByotTransaction_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ByotTransaction.rc

"$(INTDIR)\ByotTransaction.res" : $(SOURCE) "$(INTDIR)" ".\ByotTransaction.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ByotTransObj.cpp

"$(INTDIR)\ByotTransObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ByotTransaction.pch" ".\ByotTransaction.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ByotTransaction - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ByotTransaction.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ByotTransaction.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ByotTransaction.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ByotTransaction.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ByotTransaction.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ByotTransaction.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ByotTransaction.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ByotTransaction.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ByotTransaction.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ByotTransaction.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ByotTransaction - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\ByotTransaction.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ByotTransaction.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

