!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on TxEnlister.dsp
!IF "$(CFG)" == ""
CFG=TxEnlister - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TxEnlister - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "TxEnlister - Win32 Unicode Debug" && "$(CFG)" != "TxEnlister - Win32 Release MinSize" && "$(CFG)" != "TxEnlister - Win32 Release MinDependency" && "$(CFG)" != "TxEnlister - Win32 Unicode Release MinSize" && "$(CFG)" != "TxEnlister - Win32 Unicode Release MinDependency" && "$(CFG)" != "TxEnlister - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TxEnlister.mak" CFG="TxEnlister - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TxEnlister - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TxEnlister - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TxEnlister - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TxEnlister - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TxEnlister - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TxEnlister - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "TxEnlister - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\TxEnlister.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EnlistTransaction.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TxEnlister.obj"
	-@erase "$(INTDIR)\TxEnlister.pch"
	-@erase "$(INTDIR)\TxEnlister.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TxEnlister.dll"
	-@erase "$(OUTDIR)\TxEnlister.exp"
	-@erase "$(OUTDIR)\TxEnlister.ilk"
	-@erase "$(OUTDIR)\TxEnlister.lib"
	-@erase "$(OUTDIR)\TxEnlister.pdb"
	-@erase ".\TxEnlister.h"
	-@erase ".\TxEnlister.tlb"
	-@erase ".\TxEnlister_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\TxEnlister.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TxEnlister.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TxEnlister.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\TxEnlister.pdb" /debug /machine:$(CPU) /def:".\TxEnlister.def" /out:"$(OUTDIR)\TxEnlister.dll" /implib:"$(OUTDIR)\TxEnlister.lib" /pdbtype:sept 
DEF_FILE= \
	".\TxEnlister.def"
LINK32_OBJS= \
	"$(INTDIR)\EnlistTransaction.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TxEnlister.obj" \
	"$(INTDIR)\TxEnlister.res"

"$(OUTDIR)\TxEnlister.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\TxEnlister.dll
InputPath=.\DebugU\TxEnlister.dll
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
	

!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\TxEnlister.tlb" ".\TxEnlister.h" ".\TxEnlister_i.c" "$(OUTDIR)\TxEnlister.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EnlistTransaction.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TxEnlister.obj"
	-@erase "$(INTDIR)\TxEnlister.pch"
	-@erase "$(INTDIR)\TxEnlister.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TxEnlister.dll"
	-@erase "$(OUTDIR)\TxEnlister.exp"
	-@erase "$(OUTDIR)\TxEnlister.lib"
	-@erase ".\TxEnlister.h"
	-@erase ".\TxEnlister.tlb"
	-@erase ".\TxEnlister_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\TxEnlister.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TxEnlister.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TxEnlister.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\TxEnlister.pdb" /machine:$(CPU) /def:".\TxEnlister.def" /out:"$(OUTDIR)\TxEnlister.dll" /implib:"$(OUTDIR)\TxEnlister.lib" 
DEF_FILE= \
	".\TxEnlister.def"
LINK32_OBJS= \
	"$(INTDIR)\EnlistTransaction.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TxEnlister.obj" \
	"$(INTDIR)\TxEnlister.res"

"$(OUTDIR)\TxEnlister.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TxEnlister.dll
InputPath=.\ReleaseMinSize\TxEnlister.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\TxEnlister.dll" ".\TxEnlister.tlb" ".\TxEnlister.h" ".\TxEnlister_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EnlistTransaction.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TxEnlister.obj"
	-@erase "$(INTDIR)\TxEnlister.pch"
	-@erase "$(INTDIR)\TxEnlister.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TxEnlister.dll"
	-@erase "$(OUTDIR)\TxEnlister.exp"
	-@erase "$(OUTDIR)\TxEnlister.lib"
	-@erase ".\TxEnlister.h"
	-@erase ".\TxEnlister.tlb"
	-@erase ".\TxEnlister_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\TxEnlister.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TxEnlister.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TxEnlister.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\TxEnlister.pdb" /machine:$(CPU) /def:".\TxEnlister.def" /out:"$(OUTDIR)\TxEnlister.dll" /implib:"$(OUTDIR)\TxEnlister.lib" 
DEF_FILE= \
	".\TxEnlister.def"
LINK32_OBJS= \
	"$(INTDIR)\EnlistTransaction.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TxEnlister.obj" \
	"$(INTDIR)\TxEnlister.res"

"$(OUTDIR)\TxEnlister.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\TxEnlister.dll
InputPath=.\ReleaseMinDependency\TxEnlister.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\TxEnlister.dll" ".\TxEnlister.tlb" ".\TxEnlister.h" ".\TxEnlister_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EnlistTransaction.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TxEnlister.obj"
	-@erase "$(INTDIR)\TxEnlister.pch"
	-@erase "$(INTDIR)\TxEnlister.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TxEnlister.dll"
	-@erase "$(OUTDIR)\TxEnlister.exp"
	-@erase "$(OUTDIR)\TxEnlister.lib"
	-@erase ".\TxEnlister.h"
	-@erase ".\TxEnlister.tlb"
	-@erase ".\TxEnlister_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\TxEnlister.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TxEnlister.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TxEnlister.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\TxEnlister.pdb" /machine:$(CPU) /def:".\TxEnlister.def" /out:"$(OUTDIR)\TxEnlister.dll" /implib:"$(OUTDIR)\TxEnlister.lib" 
DEF_FILE= \
	".\TxEnlister.def"
LINK32_OBJS= \
	"$(INTDIR)\EnlistTransaction.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TxEnlister.obj" \
	"$(INTDIR)\TxEnlister.res"

"$(OUTDIR)\TxEnlister.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\TxEnlister.dll
InputPath=.\ReleaseUMinSize\TxEnlister.dll
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
	

!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\TxEnlister.dll" ".\TxEnlister.tlb" ".\TxEnlister.h" ".\TxEnlister_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EnlistTransaction.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TxEnlister.obj"
	-@erase "$(INTDIR)\TxEnlister.pch"
	-@erase "$(INTDIR)\TxEnlister.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TxEnlister.dll"
	-@erase "$(OUTDIR)\TxEnlister.exp"
	-@erase "$(OUTDIR)\TxEnlister.lib"
	-@erase ".\TxEnlister.h"
	-@erase ".\TxEnlister.tlb"
	-@erase ".\TxEnlister_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\TxEnlister.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TxEnlister.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TxEnlister.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\TxEnlister.pdb" /machine:$(CPU) /def:".\TxEnlister.def" /out:"$(OUTDIR)\TxEnlister.dll" /implib:"$(OUTDIR)\TxEnlister.lib" 
DEF_FILE= \
	".\TxEnlister.def"
LINK32_OBJS= \
	"$(INTDIR)\EnlistTransaction.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TxEnlister.obj" \
	"$(INTDIR)\TxEnlister.res"

"$(OUTDIR)\TxEnlister.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\TxEnlister.dll
InputPath=.\ReleaseUMinDependency\TxEnlister.dll
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
	

!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\TxEnlister.tlb" ".\TxEnlister.h" ".\TxEnlister_i.c" "$(OUTDIR)\TxEnlister.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\EnlistTransaction.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TxEnlister.obj"
	-@erase "$(INTDIR)\TxEnlister.pch"
	-@erase "$(INTDIR)\TxEnlister.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TxEnlister.dll"
	-@erase "$(OUTDIR)\TxEnlister.exp"
	-@erase "$(OUTDIR)\TxEnlister.ilk"
	-@erase "$(OUTDIR)\TxEnlister.lib"
	-@erase "$(OUTDIR)\TxEnlister.pdb"
	-@erase ".\TxEnlister.h"
	-@erase ".\TxEnlister.tlb"
	-@erase ".\TxEnlister_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\TxEnlister.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TxEnlister.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TxEnlister.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\TxEnlister.pdb" /debug /machine:$(CPU) /def:".\TxEnlister.def" /out:"$(OUTDIR)\TxEnlister.dll" /implib:"$(OUTDIR)\TxEnlister.lib" /pdbtype:sept 
DEF_FILE= \
	".\TxEnlister.def"
LINK32_OBJS= \
	"$(INTDIR)\EnlistTransaction.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TxEnlister.obj" \
	"$(INTDIR)\TxEnlister.res"

"$(OUTDIR)\TxEnlister.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\TxEnlister.dll
InputPath=.\Debug\TxEnlister.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("TxEnlister.dep")
!INCLUDE "TxEnlister.dep"
!ELSE 
!MESSAGE Warning: cannot find "TxEnlister.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TxEnlister - Win32 Unicode Debug" || "$(CFG)" == "TxEnlister - Win32 Release MinSize" || "$(CFG)" == "TxEnlister - Win32 Release MinDependency" || "$(CFG)" == "TxEnlister - Win32 Unicode Release MinSize" || "$(CFG)" == "TxEnlister - Win32 Unicode Release MinDependency" || "$(CFG)" == "TxEnlister - Win32 Debug"
SOURCE=.\EnlistTransaction.cpp

"$(INTDIR)\EnlistTransaction.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TxEnlister.pch" ".\TxEnlister.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TxEnlister - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\TxEnlister.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TxEnlister.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\TxEnlister.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TxEnlister.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\TxEnlister.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TxEnlister.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\TxEnlister.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TxEnlister.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\TxEnlister.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TxEnlister.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\TxEnlister.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TxEnlister.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TxEnlister.cpp

"$(INTDIR)\TxEnlister.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TxEnlister.pch" ".\TxEnlister.h" ".\TxEnlister_i.c"


SOURCE=.\TxEnlister.idl

!IF  "$(CFG)" == "TxEnlister - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\TxEnlister.tlb" /h "TxEnlister.h" /iid "TxEnlister_i.c" /Oicf 

".\TxEnlister.tlb"	".\TxEnlister.h"	".\TxEnlister_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\TxEnlister.tlb" /h "TxEnlister.h" /iid "TxEnlister_i.c" /Oicf 

".\TxEnlister.tlb"	".\TxEnlister.h"	".\TxEnlister_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\TxEnlister.tlb" /h "TxEnlister.h" /iid "TxEnlister_i.c" /Oicf 

".\TxEnlister.tlb"	".\TxEnlister.h"	".\TxEnlister_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\TxEnlister.tlb" /h "TxEnlister.h" /iid "TxEnlister_i.c" /Oicf 

".\TxEnlister.tlb"	".\TxEnlister.h"	".\TxEnlister_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\TxEnlister.tlb" /h "TxEnlister.h" /iid "TxEnlister_i.c" /Oicf 

".\TxEnlister.tlb"	".\TxEnlister.h"	".\TxEnlister_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TxEnlister - Win32 Debug"

MTL_SWITCHES=/tlb ".\TxEnlister.tlb" /h "TxEnlister.h" /iid "TxEnlister_i.c" /Oicf 

".\TxEnlister.tlb"	".\TxEnlister.h"	".\TxEnlister_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TxEnlister.rc

"$(INTDIR)\TxEnlister.res" : $(SOURCE) "$(INTDIR)" ".\TxEnlister.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

