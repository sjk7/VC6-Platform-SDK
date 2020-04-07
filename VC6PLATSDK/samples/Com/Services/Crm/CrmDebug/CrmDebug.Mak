!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on CrmDebug.dsp
!IF "$(CFG)" == ""
CFG=CrmDebug - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CrmDebug - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "CrmDebug - Win32 Unicode Debug" && "$(CFG)" != "CrmDebug - Win32 Release MinSize" && "$(CFG)" != "CrmDebug - Win32 Release MinDependency" && "$(CFG)" != "CrmDebug - Win32 Unicode Release MinSize" && "$(CFG)" != "CrmDebug - Win32 Unicode Release MinDependency" && "$(CFG)" != "CrmDebug - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CrmDebug.mak" CFG="CrmDebug - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CrmDebug - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmDebug - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmDebug - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmDebug - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmDebug - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmDebug - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CrmDebug - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\CrmDebug.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmDebug.obj"
	-@erase "$(INTDIR)\CrmDebug.pch"
	-@erase "$(INTDIR)\CrmDebug.res"
	-@erase "$(INTDIR)\CrmDebugCompensator.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CrmDebug.dll"
	-@erase "$(OUTDIR)\CrmDebug.exp"
	-@erase "$(OUTDIR)\CrmDebug.ilk"
	-@erase "$(OUTDIR)\CrmDebug.lib"
	-@erase "$(OUTDIR)\CrmDebug.pdb"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CrmDebug.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmDebug.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmDebug.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\CrmDebug.pdb" /debug /machine:$(CPU) /def:".\CrmDebug.def" /out:"$(OUTDIR)\CrmDebug.dll" /implib:"$(OUTDIR)\CrmDebug.lib" /pdbtype:sept 
DEF_FILE= \
	".\CrmDebug.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmDebug.obj" \
	"$(INTDIR)\CrmDebugCompensator.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmDebug.res"

"$(OUTDIR)\CrmDebug.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\CrmDebug.dll
InputPath=.\DebugU\CrmDebug.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\CrmDebug_i.c" ".\CrmDebug.tlb" ".\CrmDebug.h" "$(OUTDIR)\CrmDebug.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmDebug.obj"
	-@erase "$(INTDIR)\CrmDebug.pch"
	-@erase "$(INTDIR)\CrmDebug.res"
	-@erase "$(INTDIR)\CrmDebugCompensator.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmDebug.dll"
	-@erase "$(OUTDIR)\CrmDebug.exp"
	-@erase "$(OUTDIR)\CrmDebug.lib"
	-@erase ".\CrmDebug.h"
	-@erase ".\CrmDebug.tlb"
	-@erase ".\CrmDebug_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CrmDebug.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmDebug.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmDebug.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmDebug.pdb" /machine:$(CPU) /def:".\CrmDebug.def" /out:"$(OUTDIR)\CrmDebug.dll" /implib:"$(OUTDIR)\CrmDebug.lib" 
DEF_FILE= \
	".\CrmDebug.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmDebug.obj" \
	"$(INTDIR)\CrmDebugCompensator.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmDebug.res"

"$(OUTDIR)\CrmDebug.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\CrmDebug.dll
InputPath=.\ReleaseMinSize\CrmDebug.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\CrmDebug_i.c" ".\CrmDebug.tlb" ".\CrmDebug.h" "$(OUTDIR)\CrmDebug.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmDebug.obj"
	-@erase "$(INTDIR)\CrmDebug.pch"
	-@erase "$(INTDIR)\CrmDebug.res"
	-@erase "$(INTDIR)\CrmDebugCompensator.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmDebug.dll"
	-@erase "$(OUTDIR)\CrmDebug.exp"
	-@erase "$(OUTDIR)\CrmDebug.lib"
	-@erase ".\CrmDebug.h"
	-@erase ".\CrmDebug.tlb"
	-@erase ".\CrmDebug_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CrmDebug.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmDebug.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmDebug.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmDebug.pdb" /machine:$(CPU) /def:".\CrmDebug.def" /out:"$(OUTDIR)\CrmDebug.dll" /implib:"$(OUTDIR)\CrmDebug.lib" 
DEF_FILE= \
	".\CrmDebug.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmDebug.obj" \
	"$(INTDIR)\CrmDebugCompensator.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmDebug.res"

"$(OUTDIR)\CrmDebug.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\CrmDebug.dll
InputPath=.\ReleaseMinDependency\CrmDebug.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : ".\CrmDebug_i.c" ".\CrmDebug.tlb" ".\CrmDebug.h" "$(OUTDIR)\CrmDebug.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmDebug.obj"
	-@erase "$(INTDIR)\CrmDebug.pch"
	-@erase "$(INTDIR)\CrmDebug.res"
	-@erase "$(INTDIR)\CrmDebugCompensator.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmDebug.dll"
	-@erase "$(OUTDIR)\CrmDebug.exp"
	-@erase "$(OUTDIR)\CrmDebug.lib"
	-@erase ".\CrmDebug.h"
	-@erase ".\CrmDebug.tlb"
	-@erase ".\CrmDebug_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CrmDebug.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmDebug.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmDebug.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmDebug.pdb" /machine:$(CPU) /def:".\CrmDebug.def" /out:"$(OUTDIR)\CrmDebug.dll" /implib:"$(OUTDIR)\CrmDebug.lib" 
DEF_FILE= \
	".\CrmDebug.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmDebug.obj" \
	"$(INTDIR)\CrmDebugCompensator.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmDebug.res"

"$(OUTDIR)\CrmDebug.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\CrmDebug.dll
InputPath=.\ReleaseUMinSize\CrmDebug.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : ".\CrmDebug_i.c" ".\CrmDebug.tlb" ".\CrmDebug.h" "$(OUTDIR)\CrmDebug.dll" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmDebug.obj"
	-@erase "$(INTDIR)\CrmDebug.pch"
	-@erase "$(INTDIR)\CrmDebug.res"
	-@erase "$(INTDIR)\CrmDebugCompensator.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmDebug.dll"
	-@erase "$(OUTDIR)\CrmDebug.exp"
	-@erase "$(OUTDIR)\CrmDebug.lib"
	-@erase ".\CrmDebug.h"
	-@erase ".\CrmDebug.tlb"
	-@erase ".\CrmDebug_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CrmDebug.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmDebug.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmDebug.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmDebug.pdb" /machine:$(CPU) /def:".\CrmDebug.def" /out:"$(OUTDIR)\CrmDebug.dll" /implib:"$(OUTDIR)\CrmDebug.lib" 
DEF_FILE= \
	".\CrmDebug.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmDebug.obj" \
	"$(INTDIR)\CrmDebugCompensator.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmDebug.res"

"$(OUTDIR)\CrmDebug.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\CrmDebug.dll
InputPath=.\ReleaseUMinDependency\CrmDebug.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

#ALL : ".\dlldata.c" ".\CrmDebug_p.c" ".\CrmDebug_i.c" ".\CrmDebug.tlb" ".\CrmDebug.h" "$(OUTDIR)\CrmDebug.dll" "$(OUTDIR)\CrmDebug.pch" "$(OUTDIR)\CrmDebug.bsc" ".\Debug\regsvr32.trg"
ALL : ".\dlldata.c" ".\CrmDebug_p.c" ".\CrmDebug_i.c" ".\CrmDebug.tlb" ".\CrmDebug.h" "$(OUTDIR)\CrmDebug.dll" "$(OUTDIR)\CrmDebug.pch"  ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmDebug.obj"
	-@erase "$(INTDIR)\CrmDebug.pch"
	-@erase "$(INTDIR)\CrmDebug.res"
	-@erase "$(INTDIR)\CrmDebug.sbr"
	-@erase "$(INTDIR)\CrmDebugCompensator.obj"
	-@erase "$(INTDIR)\CrmDebugCompensator.sbr"
	-@erase "$(INTDIR)\dlldatax.obj"
	-@erase "$(INTDIR)\dlldatax.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CrmDebug.bsc"
	-@erase "$(OUTDIR)\CrmDebug.dll"
	-@erase "$(OUTDIR)\CrmDebug.exp"
	-@erase "$(OUTDIR)\CrmDebug.ilk"
	-@erase "$(OUTDIR)\CrmDebug.lib"
	-@erase "$(OUTDIR)\CrmDebug.pdb"
	-@erase ".\CrmDebug.h"
	-@erase ".\CrmDebug.tlb"
	-@erase ".\CrmDebug_i.c"
	-@erase ".\Debug\regsvr32.trg"
	-@erase "CrmDebug_p.c"
	-@erase "dlldata.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MERGE_PROXYSTUB" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmDebug.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmDebug.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\CrmDebug.sbr" \
#	"$(INTDIR)\CrmDebugCompensator.sbr" \
#	"$(INTDIR)\dlldatax.sbr" \
#	"$(INTDIR)\StdAfx.sbr"
#
#"$(OUTDIR)\CrmDebug.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\CrmDebug.pdb" /debug /machine:$(CPU) /def:".\CrmDebug.def" /out:"$(OUTDIR)\CrmDebug.dll" /implib:"$(OUTDIR)\CrmDebug.lib" /pdbtype:sept 
DEF_FILE= \
	".\CrmDebug.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmDebug.obj" \
	"$(INTDIR)\CrmDebugCompensator.obj" \
	"$(INTDIR)\dlldatax.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmDebug.res"

"$(OUTDIR)\CrmDebug.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\CrmDebug.dll
InputPath=.\Debug\CrmDebug.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("CrmDebug.dep")
!INCLUDE "CrmDebug.dep"
!ELSE 
!MESSAGE Warning: cannot find "CrmDebug.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CrmDebug - Win32 Unicode Debug" || "$(CFG)" == "CrmDebug - Win32 Release MinSize" || "$(CFG)" == "CrmDebug - Win32 Release MinDependency" || "$(CFG)" == "CrmDebug - Win32 Unicode Release MinSize" || "$(CFG)" == "CrmDebug - Win32 Unicode Release MinDependency" || "$(CFG)" == "CrmDebug - Win32 Debug"
SOURCE=.\CrmDebug.cpp

!IF  "$(CFG)" == "CrmDebug - Win32 Unicode Debug"


"$(INTDIR)\CrmDebug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmDebug.pch" ".\CrmDebug.h" ".\CrmDebug_i.c"


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinSize"


"$(INTDIR)\CrmDebug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmDebug.pch"


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinDependency"


"$(INTDIR)\CrmDebug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmDebug.pch"


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinSize"


"$(INTDIR)\CrmDebug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmDebug.pch"


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinDependency"


"$(INTDIR)\CrmDebug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmDebug.pch"


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Debug"


#"$(INTDIR)\CrmDebug.obj"	"$(INTDIR)\CrmDebug.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\CrmDebug.obj"	: $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CrmDebug.idl

!IF  "$(CFG)" == "CrmDebug - Win32 Unicode Debug"

InputPath=.\CrmDebug.idl

".\CrmDebug.tlb"	".\CrmDebug.h"	".\CrmDebug_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmDebug.h" /iid "CrmDebug_i.c" "CrmDebug.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinSize"

InputPath=.\CrmDebug.idl

".\CrmDebug.tlb"	".\CrmDebug.h"	".\CrmDebug_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmDebug.h" /iid "CrmDebug_i.c" "CrmDebug.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinDependency"

InputPath=.\CrmDebug.idl

".\CrmDebug.tlb"	".\CrmDebug.h"	".\CrmDebug_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmDebug.h" /iid "CrmDebug_i.c" "CrmDebug.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinSize"

InputPath=.\CrmDebug.idl

".\CrmDebug.tlb"	".\CrmDebug.h"	".\CrmDebug_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmDebug.h" /iid "CrmDebug_i.c" "CrmDebug.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinDependency"

InputPath=.\CrmDebug.idl

".\CrmDebug.tlb"	".\CrmDebug.h"	".\CrmDebug_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmDebug.h" /iid "CrmDebug_i.c" "CrmDebug.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Debug"

InputPath=.\CrmDebug.idl

".\CrmDebug.tlb"	".\CrmDebug.h"	".\CrmDebug_i.c"	".\CrmDebug_p.c"	".\dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmDebug.h" /iid "CrmDebug_i.c" "CrmDebug.idl"
<< 
	

!ENDIF 

SOURCE=.\CrmDebug.rc

"$(INTDIR)\CrmDebug.res" : $(SOURCE) "$(INTDIR)" ".\CrmDebug.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CrmDebugCompensator.cpp

!IF  "$(CFG)" == "CrmDebug - Win32 Unicode Debug"


"$(INTDIR)\CrmDebugCompensator.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmDebug.pch" ".\CrmDebug.h"


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinSize"


"$(INTDIR)\CrmDebugCompensator.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmDebug.pch"


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinDependency"


"$(INTDIR)\CrmDebugCompensator.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmDebug.pch"


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinSize"


"$(INTDIR)\CrmDebugCompensator.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmDebug.pch"


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinDependency"


"$(INTDIR)\CrmDebugCompensator.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmDebug.pch"


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Debug"


#"$(INTDIR)\CrmDebugCompensator.obj"	"$(INTDIR)\CrmDebugCompensator.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\CrmDebugCompensator.obj"	: $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\dlldatax.c

!IF  "$(CFG)" == "CrmDebug - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MERGE_PROXYSTUB" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\dlldatax.obj"	"$(INTDIR)\dlldatax.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\dlldatax.obj"	: $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CrmDebug - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CrmDebug.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmDebug.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CrmDebug.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmDebug.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CrmDebug.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmDebug.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CrmDebug.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmDebug.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\CrmDebug.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmDebug.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmDebug - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MERGE_PROXYSTUB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmDebug.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CrmDebug.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmDebug.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

