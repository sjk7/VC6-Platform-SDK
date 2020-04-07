!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on ADOKB.DSP
!IF "$(CFG)" == ""
CFG=ADOKB - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ADOKB - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "ADOKB - Win32 Unicode Debug" && "$(CFG)" != "ADOKB - Win32 Release MinSize" && "$(CFG)" != "ADOKB - Win32 Release MinDependency" && "$(CFG)" != "ADOKB - Win32 Unicode Release MinSize" && "$(CFG)" != "ADOKB - Win32 Unicode Release MinDependency" && "$(CFG)" != "ADOKB - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ADOKB.MAK" CFG="ADOKB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ADOKB - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ADOKB - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ADOKB - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ADOKB - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ADOKB - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ADOKB - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ADOKB - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : ".\ADOKB_i.c" ".\ADOKB.tlb" ".\ADOKB.h" "$(OUTDIR)\ADOKB.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ADOComponent.obj"
	-@erase "$(INTDIR)\ADOKB.obj"
	-@erase "$(INTDIR)\ADOKB.pch"
	-@erase "$(INTDIR)\ADOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ADOKB.dll"
	-@erase "$(OUTDIR)\ADOKB.exp"
	-@erase "$(OUTDIR)\ADOKB.ilk"
	-@erase "$(OUTDIR)\ADOKB.lib"
	-@erase "$(OUTDIR)\ADOKB.pdb"
	-@erase ".\ADOKB.h"
	-@erase ".\ADOKB.tlb"
	-@erase ".\ADOKB_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ADOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ADOKB.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ADOKB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ADOKB.pdb" /debug /machine:$(CPU) /def:".\ADOKB.def" /out:"$(OUTDIR)\ADOKB.dll" /implib:"$(OUTDIR)\ADOKB.lib" /pdbtype:sept 
DEF_FILE= \
	".\ADOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\ADOComponent.obj" \
	"$(INTDIR)\ADOKB.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ADOKB.res"

"$(OUTDIR)\ADOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\ADOKB.dll
InputPath=.\DebugU\ADOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ADOKB - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\ADOKB_i.c" ".\ADOKB.tlb" ".\ADOKB.h" "$(OUTDIR)\ADOKB.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ADOComponent.obj"
	-@erase "$(INTDIR)\ADOKB.obj"
	-@erase "$(INTDIR)\ADOKB.pch"
	-@erase "$(INTDIR)\ADOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ADOKB.dll"
	-@erase "$(OUTDIR)\ADOKB.exp"
	-@erase "$(OUTDIR)\ADOKB.lib"
	-@erase ".\ADOKB.h"
	-@erase ".\ADOKB.tlb"
	-@erase ".\ADOKB_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\ADOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ADOKB.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ADOKB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ADOKB.pdb" /machine:$(CPU) /def:".\ADOKB.def" /out:"$(OUTDIR)\ADOKB.dll" /implib:"$(OUTDIR)\ADOKB.lib" 
DEF_FILE= \
	".\ADOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\ADOComponent.obj" \
	"$(INTDIR)\ADOKB.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ADOKB.res"

"$(OUTDIR)\ADOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\ADOKB.dll
InputPath=.\ReleaseMinSize\ADOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ADOKB - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\ADOKB_i.c" ".\ADOKB.tlb" ".\ADOKB.h" "$(OUTDIR)\ADOKB.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ADOComponent.obj"
	-@erase "$(INTDIR)\ADOKB.obj"
	-@erase "$(INTDIR)\ADOKB.pch"
	-@erase "$(INTDIR)\ADOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ADOKB.dll"
	-@erase "$(OUTDIR)\ADOKB.exp"
	-@erase "$(OUTDIR)\ADOKB.lib"
	-@erase ".\ADOKB.h"
	-@erase ".\ADOKB.tlb"
	-@erase ".\ADOKB_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ADOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ADOKB.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ADOKB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ADOKB.pdb" /machine:$(CPU) /def:".\ADOKB.def" /out:"$(OUTDIR)\ADOKB.dll" /implib:"$(OUTDIR)\ADOKB.lib" 
DEF_FILE= \
	".\ADOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\ADOComponent.obj" \
	"$(INTDIR)\ADOKB.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ADOKB.res"

"$(OUTDIR)\ADOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\ADOKB.dll
InputPath=.\ReleaseMinDependency\ADOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ADOKB - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : ".\ADOKB_i.c" ".\ADOKB.tlb" ".\ADOKB.h" "$(OUTDIR)\ADOKB.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ADOComponent.obj"
	-@erase "$(INTDIR)\ADOKB.obj"
	-@erase "$(INTDIR)\ADOKB.pch"
	-@erase "$(INTDIR)\ADOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ADOKB.dll"
	-@erase "$(OUTDIR)\ADOKB.exp"
	-@erase "$(OUTDIR)\ADOKB.lib"
	-@erase ".\ADOKB.h"
	-@erase ".\ADOKB.tlb"
	-@erase ".\ADOKB_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\ADOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ADOKB.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ADOKB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ADOKB.pdb" /machine:$(CPU) /def:".\ADOKB.def" /out:"$(OUTDIR)\ADOKB.dll" /implib:"$(OUTDIR)\ADOKB.lib" 
DEF_FILE= \
	".\ADOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\ADOComponent.obj" \
	"$(INTDIR)\ADOKB.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ADOKB.res"

"$(OUTDIR)\ADOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\ADOKB.dll
InputPath=.\ReleaseUMinSize\ADOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ADOKB - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : ".\ADOKB_i.c" ".\ADOKB.tlb" ".\ADOKB.h" "$(OUTDIR)\ADOKB.dll" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ADOComponent.obj"
	-@erase "$(INTDIR)\ADOKB.obj"
	-@erase "$(INTDIR)\ADOKB.pch"
	-@erase "$(INTDIR)\ADOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ADOKB.dll"
	-@erase "$(OUTDIR)\ADOKB.exp"
	-@erase "$(OUTDIR)\ADOKB.lib"
	-@erase ".\ADOKB.h"
	-@erase ".\ADOKB.tlb"
	-@erase ".\ADOKB_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ADOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ADOKB.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ADOKB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ADOKB.pdb" /machine:$(CPU) /def:".\ADOKB.def" /out:"$(OUTDIR)\ADOKB.dll" /implib:"$(OUTDIR)\ADOKB.lib" 
DEF_FILE= \
	".\ADOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\ADOComponent.obj" \
	"$(INTDIR)\ADOKB.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ADOKB.res"

"$(OUTDIR)\ADOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\ADOKB.dll
InputPath=.\ReleaseUMinDependency\ADOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ADOKB - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\ADOKB_i.c" ".\ADOKB.tlb" ".\ADOKB.h" "$(OUTDIR)\ADOKB.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ADOComponent.obj"
	-@erase "$(INTDIR)\ADOKB.obj"
	-@erase "$(INTDIR)\ADOKB.pch"
	-@erase "$(INTDIR)\ADOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ADOKB.dll"
	-@erase "$(OUTDIR)\ADOKB.exp"
	-@erase "$(OUTDIR)\ADOKB.ilk"
	-@erase "$(OUTDIR)\ADOKB.lib"
	-@erase "$(OUTDIR)\ADOKB.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\ADOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ADOKB.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ADOKB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ADOKB.pdb" /debug /machine:$(CPU) /def:".\ADOKB.def" /out:"$(OUTDIR)\ADOKB.dll" /implib:"$(OUTDIR)\ADOKB.lib" /pdbtype:sept 
DEF_FILE= \
	".\ADOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\ADOComponent.obj" \
	"$(INTDIR)\ADOKB.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ADOKB.res"

"$(OUTDIR)\ADOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ADOKB.dll
InputPath=.\Debug\ADOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ADOKB.DEP")
!INCLUDE "ADOKB.DEP"
!ELSE 
!MESSAGE Warning: cannot find "ADOKB.DEP"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ADOKB - Win32 Unicode Debug" || "$(CFG)" == "ADOKB - Win32 Release MinSize" || "$(CFG)" == "ADOKB - Win32 Release MinDependency" || "$(CFG)" == "ADOKB - Win32 Unicode Release MinSize" || "$(CFG)" == "ADOKB - Win32 Unicode Release MinDependency" || "$(CFG)" == "ADOKB - Win32 Debug"
SOURCE=.\ADOComponent.cpp

"$(INTDIR)\ADOComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ADOKB.pch"


SOURCE=.\ADOKB.cpp

"$(INTDIR)\ADOKB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ADOKB.pch"


SOURCE=.\ADOKB.idl

!IF  "$(CFG)" == "ADOKB - Win32 Unicode Debug"

InputPath=.\ADOKB.idl

".\ADOKB.tlb"	".\ADOKB.h"	".\ADOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "ADOKB.h" /iid "ADOKB_i.c" "ADOKB.idl"
<< 
	

!ELSEIF  "$(CFG)" == "ADOKB - Win32 Release MinSize"

InputPath=.\ADOKB.idl

".\ADOKB.tlb"	".\ADOKB.h"	".\ADOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "ADOKB.h" /iid "ADOKB_i.c" "ADOKB.idl"
<< 
	

!ELSEIF  "$(CFG)" == "ADOKB - Win32 Release MinDependency"

InputPath=.\ADOKB.idl

".\ADOKB.tlb"	".\ADOKB.h"	".\ADOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "ADOKB.h" /iid "ADOKB_i.c" "ADOKB.idl"
<< 
	

!ELSEIF  "$(CFG)" == "ADOKB - Win32 Unicode Release MinSize"

InputPath=.\ADOKB.idl

".\ADOKB.tlb"	".\ADOKB.h"	".\ADOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "ADOKB.h" /iid "ADOKB_i.c" "ADOKB.idl"
<< 
	

!ELSEIF  "$(CFG)" == "ADOKB - Win32 Unicode Release MinDependency"

InputPath=.\ADOKB.idl

".\ADOKB.tlb"	".\ADOKB.h"	".\ADOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "ADOKB.h" /iid "ADOKB_i.c" "ADOKB.idl"
<< 
	

!ELSEIF  "$(CFG)" == "ADOKB - Win32 Debug"

InputPath=.\ADOKB.idl

".\ADOKB.tlb"	".\ADOKB.h"	".\ADOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "ADOKB.h" /iid "ADOKB_i.c" "ADOKB.idl"
<< 
	

!ENDIF 

SOURCE=.\ADOKB.rc

"$(INTDIR)\ADOKB.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ADOKB - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ADOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ADOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ADOKB - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\ADOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ADOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ADOKB - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ADOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ADOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ADOKB - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\ADOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ADOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ADOKB - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ADOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ADOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ADOKB - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\ADOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ADOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

