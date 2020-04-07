!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on CrmFilesTest.dsp
!IF "$(CFG)" == ""
CFG=CrmFilesTest - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CrmFilesTest - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CrmFilesTest - Win32 Unicode Debug" && "$(CFG)" != "CrmFilesTest - Win32 Release MinSize" && "$(CFG)" != "CrmFilesTest - Win32 Release MinDependency" && "$(CFG)" != "CrmFilesTest - Win32 Unicode Release MinSize" && "$(CFG)" != "CrmFilesTest - Win32 Unicode Release MinDependency" && "$(CFG)" != "CrmFilesTest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CrmFilesTest.mak" CFG="CrmFilesTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CrmFilesTest - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmFilesTest - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmFilesTest - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmFilesTest - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmFilesTest - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmFilesTest - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : ".\CrmFilesTest_i.c" ".\CrmFilesTest.tlb" ".\CrmFilesTest.h" "$(OUTDIR)\CrmFilesTest.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFilesTest.obj"
	-@erase "$(INTDIR)\CrmFilesTest.pch"
	-@erase "$(INTDIR)\CrmFilesTest.res"
	-@erase "$(INTDIR)\CrmFilesTestObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CrmFilesTest.dll"
	-@erase "$(OUTDIR)\CrmFilesTest.exp"
	-@erase "$(OUTDIR)\CrmFilesTest.ilk"
	-@erase "$(OUTDIR)\CrmFilesTest.lib"
	-@erase "$(OUTDIR)\CrmFilesTest.pdb"
	-@erase ".\CrmFilesTest.h"
	-@erase ".\CrmFilesTest.tlb"
	-@erase ".\CrmFilesTest_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFilesTest.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFilesTest.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\CrmFilesTest.pdb" /debug /machine:$(CPU) /def:".\CrmFilesTest.def" /out:"$(OUTDIR)\CrmFilesTest.dll" /implib:"$(OUTDIR)\CrmFilesTest.lib" /pdbtype:sept 
DEF_FILE= \
	".\CrmFilesTest.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFilesTest.obj" \
	"$(INTDIR)\CrmFilesTestObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFilesTest.res"

"$(OUTDIR)\CrmFilesTest.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\CrmFilesTest.dll
InputPath=.\DebugU\CrmFilesTest.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\CrmFilesTest.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFilesTest.obj"
	-@erase "$(INTDIR)\CrmFilesTest.pch"
	-@erase "$(INTDIR)\CrmFilesTest.res"
	-@erase "$(INTDIR)\CrmFilesTestObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmFilesTest.dll"
	-@erase "$(OUTDIR)\CrmFilesTest.exp"
	-@erase "$(OUTDIR)\CrmFilesTest.lib"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFilesTest.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFilesTest.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmFilesTest.pdb" /machine:$(CPU) /def:".\CrmFilesTest.def" /out:"$(OUTDIR)\CrmFilesTest.dll" /implib:"$(OUTDIR)\CrmFilesTest.lib" 
DEF_FILE= \
	".\CrmFilesTest.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFilesTest.obj" \
	"$(INTDIR)\CrmFilesTestObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFilesTest.res"

"$(OUTDIR)\CrmFilesTest.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\CrmFilesTest.dll
InputPath=.\ReleaseMinSize\CrmFilesTest.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\CrmFilesTest_i.c" ".\CrmFilesTest.tlb" ".\CrmFilesTest.h" "$(OUTDIR)\CrmFilesTest.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFilesTest.obj"
	-@erase "$(INTDIR)\CrmFilesTest.pch"
	-@erase "$(INTDIR)\CrmFilesTest.res"
	-@erase "$(INTDIR)\CrmFilesTestObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmFilesTest.dll"
	-@erase "$(OUTDIR)\CrmFilesTest.exp"
	-@erase "$(OUTDIR)\CrmFilesTest.lib"
	-@erase ".\CrmFilesTest.h"
	-@erase ".\CrmFilesTest.tlb"
	-@erase ".\CrmFilesTest_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFilesTest.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFilesTest.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmFilesTest.pdb" /machine:$(CPU) /def:".\CrmFilesTest.def" /out:"$(OUTDIR)\CrmFilesTest.dll" /implib:"$(OUTDIR)\CrmFilesTest.lib" 
DEF_FILE= \
	".\CrmFilesTest.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFilesTest.obj" \
	"$(INTDIR)\CrmFilesTestObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFilesTest.res"

"$(OUTDIR)\CrmFilesTest.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\CrmFilesTest.dll
InputPath=.\ReleaseMinDependency\CrmFilesTest.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : ".\CrmFilesTest_i.c" ".\CrmFilesTest.tlb" ".\CrmFilesTest.h" "$(OUTDIR)\CrmFilesTest.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFilesTest.obj"
	-@erase "$(INTDIR)\CrmFilesTest.pch"
	-@erase "$(INTDIR)\CrmFilesTest.res"
	-@erase "$(INTDIR)\CrmFilesTestObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmFilesTest.dll"
	-@erase "$(OUTDIR)\CrmFilesTest.exp"
	-@erase "$(OUTDIR)\CrmFilesTest.lib"
	-@erase ".\CrmFilesTest.h"
	-@erase ".\CrmFilesTest.tlb"
	-@erase ".\CrmFilesTest_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFilesTest.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFilesTest.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmFilesTest.pdb" /machine:$(CPU) /def:".\CrmFilesTest.def" /out:"$(OUTDIR)\CrmFilesTest.dll" /implib:"$(OUTDIR)\CrmFilesTest.lib" 
DEF_FILE= \
	".\CrmFilesTest.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFilesTest.obj" \
	"$(INTDIR)\CrmFilesTestObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFilesTest.res"

"$(OUTDIR)\CrmFilesTest.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\CrmFilesTest.dll
InputPath=.\ReleaseUMinSize\CrmFilesTest.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : ".\CrmFilesTest_i.c" ".\CrmFilesTest.tlb" ".\CrmFilesTest.h" "$(OUTDIR)\CrmFilesTest.dll" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFilesTest.obj"
	-@erase "$(INTDIR)\CrmFilesTest.pch"
	-@erase "$(INTDIR)\CrmFilesTest.res"
	-@erase "$(INTDIR)\CrmFilesTestObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmFilesTest.dll"
	-@erase "$(OUTDIR)\CrmFilesTest.exp"
	-@erase "$(OUTDIR)\CrmFilesTest.lib"
	-@erase ".\CrmFilesTest.h"
	-@erase ".\CrmFilesTest.tlb"
	-@erase ".\CrmFilesTest_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /I "..\CrmFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFilesTest.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFilesTest.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmFilesTest.pdb" /machine:$(CPU) /def:".\CrmFilesTest.def" /out:"$(OUTDIR)\CrmFilesTest.dll" /implib:"$(OUTDIR)\CrmFilesTest.lib" 
DEF_FILE= \
	".\CrmFilesTest.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFilesTest.obj" \
	"$(INTDIR)\CrmFilesTestObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFilesTest.res"

"$(OUTDIR)\CrmFilesTest.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\CrmFilesTest.dll
InputPath=.\ReleaseUMinDependency\CrmFilesTest.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

#ALL : ".\CrmFilesTest_i.c" ".\CrmFilesTest.tlb" ".\CrmFilesTest.h" "$(OUTDIR)\CrmFilesTest.dll" "$(OUTDIR)\CrmFilesTest.pch" "$(OUTDIR)\CrmFilesTest.bsc" ".\Debug\regsvr32.trg"
ALL : ".\CrmFilesTest_i.c" ".\CrmFilesTest.tlb" ".\CrmFilesTest.h" "$(OUTDIR)\CrmFilesTest.dll" "$(OUTDIR)\CrmFilesTest.pch" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFilesTest.obj"
	-@erase "$(INTDIR)\CrmFilesTest.pch"
	-@erase "$(INTDIR)\CrmFilesTest.res"
	-@erase "$(INTDIR)\CrmFilesTest.sbr"
	-@erase "$(INTDIR)\CrmFilesTestObj.obj"
	-@erase "$(INTDIR)\CrmFilesTestObj.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CrmFilesTest.bsc"
	-@erase "$(OUTDIR)\CrmFilesTest.dll"
	-@erase "$(OUTDIR)\CrmFilesTest.exp"
	-@erase "$(OUTDIR)\CrmFilesTest.ilk"
	-@erase "$(OUTDIR)\CrmFilesTest.lib"
	-@erase "$(OUTDIR)\CrmFilesTest.pdb"
	-@erase ".\CrmFilesTest.h"
	-@erase ".\CrmFilesTest.tlb"
	-@erase ".\CrmFilesTest_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W4 /Gm /Zi /Od /I "..\CrmFiles" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFilesTest.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFilesTest.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\CrmFilesTest.sbr" \
#	"$(INTDIR)\CrmFilesTestObj.sbr" \
#	"$(INTDIR)\StdAfx.sbr"

#"$(OUTDIR)\CrmFilesTest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\CrmFilesTest.pdb" /debug /machine:$(CPU) /def:".\CrmFilesTest.def" /out:"$(OUTDIR)\CrmFilesTest.dll" /implib:"$(OUTDIR)\CrmFilesTest.lib" /pdbtype:sept 
DEF_FILE= \
	".\CrmFilesTest.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFilesTest.obj" \
	"$(INTDIR)\CrmFilesTestObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFilesTest.res"

"$(OUTDIR)\CrmFilesTest.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\CrmFilesTest.dll
InputPath=.\Debug\CrmFilesTest.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("CrmFilesTest.dep")
!INCLUDE "CrmFilesTest.dep"
!ELSE 
!MESSAGE Warning: cannot find "CrmFilesTest.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CrmFilesTest - Win32 Unicode Debug" || "$(CFG)" == "CrmFilesTest - Win32 Release MinSize" || "$(CFG)" == "CrmFilesTest - Win32 Release MinDependency" || "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinSize" || "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinDependency" || "$(CFG)" == "CrmFilesTest - Win32 Debug"
SOURCE=.\CrmFilesTest.cpp

!IF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\CrmFilesTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFilesTest.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\CrmFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\CrmFilesTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFilesTest.pch" ".\CrmFilesTest.h" ".\CrmFilesTest_i.c"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\CrmFilesTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFilesTest.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\CrmFilesTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFilesTest.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\CrmFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\CrmFilesTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFilesTest.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W4 /Gm /Zi /Od /I "..\CrmFiles" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\CrmFilesTest.obj"	"$(INTDIR)\CrmFilesTest.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\CrmFilesTest.obj"	: $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CrmFilesTest.idl

!IF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Debug"

InputPath=.\CrmFilesTest.idl

".\CrmFilesTest.tlb"	".\CrmFilesTest.h"	".\CrmFilesTest_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFilesTest.h" /iid "CrmFilesTest_i.c" "CrmFilesTest.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Release MinSize"

InputPath=.\CrmFilesTest.idl

".\CrmFilesTest.tlb"	".\CrmFilesTest.h"	".\CrmFilesTest_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFilesTest.h" /iid "CrmFilesTest_i.c" "CrmFilesTest.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Release MinDependency"

InputPath=.\CrmFilesTest.idl

".\CrmFilesTest.tlb"	".\CrmFilesTest.h"	".\CrmFilesTest_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFilesTest.h" /iid "CrmFilesTest_i.c" "CrmFilesTest.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinSize"

InputPath=.\CrmFilesTest.idl

".\CrmFilesTest.tlb"	".\CrmFilesTest.h"	".\CrmFilesTest_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFilesTest.h" /iid "CrmFilesTest_i.c" "CrmFilesTest.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinDependency"

InputPath=.\CrmFilesTest.idl

".\CrmFilesTest.tlb"	".\CrmFilesTest.h"	".\CrmFilesTest_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFilesTest.h" /iid "CrmFilesTest_i.c" "CrmFilesTest.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Debug"

InputPath=.\CrmFilesTest.idl

".\CrmFilesTest.tlb"	".\CrmFilesTest.h"	".\CrmFilesTest_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFilesTest.h" /iid "CrmFilesTest_i.c" "CrmFilesTest.idl"
<< 
	

!ENDIF 

SOURCE=.\CrmFilesTest.rc

"$(INTDIR)\CrmFilesTest.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CrmFilesTestObj.cpp

!IF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\CrmFilesTestObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFilesTest.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\CrmFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\CrmFilesTestObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFilesTest.pch" ".\CrmFilesTest.h"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\CrmFilesTestObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFilesTest.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\CrmFilesTestObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFilesTest.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\CrmFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\CrmFilesTestObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFilesTest.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W4 /Gm /Zi /Od /I "..\CrmFiles" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\CrmFilesTestObj.obj"	"$(INTDIR)\CrmFilesTestObj.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\CrmFilesTestObj.obj"	: $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\dlldatax.c
SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFilesTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFilesTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFilesTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFilesTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\CrmFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFilesTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFilesTest - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W4 /Gm /Zi /Od /I "..\CrmFiles" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFilesTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CrmFilesTest.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFilesTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

