!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on RDOKB.DSP
!IF "$(CFG)" == ""
CFG=RDOKB - Win32 Debug
!MESSAGE No configuration specified. Defaulting to RDOKB - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "RDOKB - Win32 Unicode Debug" && "$(CFG)" != "RDOKB - Win32 Release MinSize" && "$(CFG)" != "RDOKB - Win32 Release MinDependency" && "$(CFG)" != "RDOKB - Win32 Unicode Release MinSize" && "$(CFG)" != "RDOKB - Win32 Unicode Release MinDependency" && "$(CFG)" != "RDOKB - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RDOKB.MAK" CFG="RDOKB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RDOKB - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RDOKB - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RDOKB - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RDOKB - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RDOKB - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RDOKB - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "RDOKB - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : ".\RDOKB_i.c" ".\RDOKB.tlb" ".\RDOKB.h" "$(OUTDIR)\RDOKB.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\RDOComponent.obj"
	-@erase "$(INTDIR)\RDOKB.obj"
	-@erase "$(INTDIR)\RDOKB.pch"
	-@erase "$(INTDIR)\RDOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\RDOKB.dll"
	-@erase "$(OUTDIR)\RDOKB.exp"
	-@erase "$(OUTDIR)\RDOKB.ilk"
	-@erase "$(OUTDIR)\RDOKB.lib"
	-@erase "$(OUTDIR)\RDOKB.pdb"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\RDOKB.h"
	-@erase ".\RDOKB.tlb"
	-@erase ".\RDOKB_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RDOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RDOKB.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\RDOKB.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\RDOKB.pdb" /debug /machine:$(CPU) /def:".\RDOKB.def" /out:"$(OUTDIR)\RDOKB.dll" /implib:"$(OUTDIR)\RDOKB.lib" /pdbtype:sept 
DEF_FILE= \
	".\RDOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\RDOKB.obj" \
	"$(INTDIR)\RDOComponent.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\RDOKB.res"

"$(OUTDIR)\RDOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\RDOKB.dll
InputPath=.\DebugU\RDOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "RDOKB - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\RDOKB_i.c" ".\RDOKB.tlb" ".\RDOKB.h" "$(OUTDIR)\RDOKB.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\RDOComponent.obj"
	-@erase "$(INTDIR)\RDOKB.obj"
	-@erase "$(INTDIR)\RDOKB.pch"
	-@erase "$(INTDIR)\RDOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\RDOKB.dll"
	-@erase "$(OUTDIR)\RDOKB.exp"
	-@erase "$(OUTDIR)\RDOKB.lib"
	-@erase ".\RDOKB.h"
	-@erase ".\RDOKB.tlb"
	-@erase ".\RDOKB_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\RDOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RDOKB.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\RDOKB.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\RDOKB.pdb" /machine:$(CPU) /def:".\RDOKB.def" /out:"$(OUTDIR)\RDOKB.dll" /implib:"$(OUTDIR)\RDOKB.lib" 
DEF_FILE= \
	".\RDOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\RDOKB.obj" \
	"$(INTDIR)\RDOComponent.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\RDOKB.res"

"$(OUTDIR)\RDOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\RDOKB.dll
InputPath=.\ReleaseMinSize\RDOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "RDOKB - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\RDOKB_i.c" ".\RDOKB.tlb" ".\RDOKB.h" "$(OUTDIR)\RDOKB.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\RDOComponent.obj"
	-@erase "$(INTDIR)\RDOKB.obj"
	-@erase "$(INTDIR)\RDOKB.pch"
	-@erase "$(INTDIR)\RDOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\RDOKB.dll"
	-@erase "$(OUTDIR)\RDOKB.exp"
	-@erase "$(OUTDIR)\RDOKB.lib"
	-@erase ".\RDOKB.h"
	-@erase ".\RDOKB.tlb"
	-@erase ".\RDOKB_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\RDOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RDOKB.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\RDOKB.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\RDOKB.pdb" /machine:$(CPU) /def:".\RDOKB.def" /out:"$(OUTDIR)\RDOKB.dll" /implib:"$(OUTDIR)\RDOKB.lib" 
DEF_FILE= \
	".\RDOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\RDOKB.obj" \
	"$(INTDIR)\RDOComponent.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\RDOKB.res"

"$(OUTDIR)\RDOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\RDOKB.dll
InputPath=.\ReleaseMinDependency\RDOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "RDOKB - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : ".\RDOKB_i.c" ".\RDOKB.tlb" ".\RDOKB.h" "$(OUTDIR)\RDOKB.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\RDOComponent.obj"
	-@erase "$(INTDIR)\RDOKB.obj"
	-@erase "$(INTDIR)\RDOKB.pch"
	-@erase "$(INTDIR)\RDOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\RDOKB.dll"
	-@erase "$(OUTDIR)\RDOKB.exp"
	-@erase "$(OUTDIR)\RDOKB.lib"
	-@erase ".\RDOKB.h"
	-@erase ".\RDOKB.tlb"
	-@erase ".\RDOKB_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\RDOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RDOKB.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\RDOKB.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\RDOKB.pdb" /machine:$(CPU) /def:".\RDOKB.def" /out:"$(OUTDIR)\RDOKB.dll" /implib:"$(OUTDIR)\RDOKB.lib" 
DEF_FILE= \
	".\RDOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\RDOKB.obj" \
	"$(INTDIR)\RDOComponent.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\RDOKB.res"

"$(OUTDIR)\RDOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\RDOKB.dll
InputPath=.\ReleaseUMinSize\RDOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "RDOKB - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : ".\RDOKB_i.c" ".\RDOKB.tlb" ".\RDOKB.h" "$(OUTDIR)\RDOKB.dll" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\RDOComponent.obj"
	-@erase "$(INTDIR)\RDOKB.obj"
	-@erase "$(INTDIR)\RDOKB.pch"
	-@erase "$(INTDIR)\RDOKB.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\RDOKB.dll"
	-@erase "$(OUTDIR)\RDOKB.exp"
	-@erase "$(OUTDIR)\RDOKB.lib"
	-@erase ".\RDOKB.h"
	-@erase ".\RDOKB.tlb"
	-@erase ".\RDOKB_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\RDOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RDOKB.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\RDOKB.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\RDOKB.pdb" /machine:$(CPU) /def:".\RDOKB.def" /out:"$(OUTDIR)\RDOKB.dll" /implib:"$(OUTDIR)\RDOKB.lib" 
DEF_FILE= \
	".\RDOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\RDOKB.obj" \
	"$(INTDIR)\RDOComponent.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\RDOKB.res"

"$(OUTDIR)\RDOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\RDOKB.dll
InputPath=.\ReleaseUMinDependency\RDOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "RDOKB - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

#ALL : "$(OUTDIR)\RDOKB.dll" "$(OUTDIR)\RDOKB.bsc" ".\Debug\regsvr32.trg"
ALL : "$(OUTDIR)\RDOKB.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\RDOComponent.obj"
	-@erase "$(INTDIR)\RDOComponent.sbr"
	-@erase "$(INTDIR)\RDOKB.obj"
	-@erase "$(INTDIR)\RDOKB.pch"
	-@erase "$(INTDIR)\RDOKB.res"
	-@erase "$(INTDIR)\RDOKB.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\RDOKB.bsc"
	-@erase "$(OUTDIR)\RDOKB.dll"
	-@erase "$(OUTDIR)\RDOKB.exp"
	-@erase "$(OUTDIR)\RDOKB.ilk"
	-@erase "$(OUTDIR)\RDOKB.lib"
	-@erase "$(OUTDIR)\RDOKB.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\RDOKB.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RDOKB.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\RDOKB.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\RDOKB.sbr" \
#	"$(INTDIR)\RDOComponent.sbr" \
#	"$(INTDIR)\StdAfx.sbr"

#"$(OUTDIR)\RDOKB.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\RDOKB.pdb" /debug /machine:$(CPU) /def:".\RDOKB.def" /out:"$(OUTDIR)\RDOKB.dll" /implib:"$(OUTDIR)\RDOKB.lib" /pdbtype:sept 
DEF_FILE= \
	".\RDOKB.def"
LINK32_OBJS= \
	"$(INTDIR)\RDOKB.obj" \
	"$(INTDIR)\RDOComponent.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\RDOKB.res"

"$(OUTDIR)\RDOKB.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\RDOKB.dll
InputPath=.\Debug\RDOKB.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("RDOKB.DEP")
!INCLUDE "RDOKB.DEP"
!ELSE 
!MESSAGE Warning: cannot find "RDOKB.DEP"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "RDOKB - Win32 Unicode Debug" || "$(CFG)" == "RDOKB - Win32 Release MinSize" || "$(CFG)" == "RDOKB - Win32 Release MinDependency" || "$(CFG)" == "RDOKB - Win32 Unicode Release MinSize" || "$(CFG)" == "RDOKB - Win32 Unicode Release MinDependency" || "$(CFG)" == "RDOKB - Win32 Debug"
SOURCE=.\RDOComponent.cpp

!IF  "$(CFG)" == "RDOKB - Win32 Unicode Debug"


"$(INTDIR)\RDOComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch"


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Release MinSize"


"$(INTDIR)\RDOComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch"


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Release MinDependency"


"$(INTDIR)\RDOComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch"


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Unicode Release MinSize"


"$(INTDIR)\RDOComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch"


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Unicode Release MinDependency"


"$(INTDIR)\RDOComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch"


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Debug"


#"$(INTDIR)\RDOComponent.obj"	"$(INTDIR)\RDOComponent.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch" ".\RDOKB.h"
"$(INTDIR)\RDOComponent.obj"	: $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch" ".\RDOKB.h"


!ENDIF 

SOURCE=.\RDOKB.cpp

!IF  "$(CFG)" == "RDOKB - Win32 Unicode Debug"


"$(INTDIR)\RDOKB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch"


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Release MinSize"


"$(INTDIR)\RDOKB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch"


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Release MinDependency"


"$(INTDIR)\RDOKB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch"


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Unicode Release MinSize"


"$(INTDIR)\RDOKB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch"


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Unicode Release MinDependency"


"$(INTDIR)\RDOKB.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch"


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Debug"


#"$(INTDIR)\RDOKB.obj"	"$(INTDIR)\RDOKB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch" ".\RDOKB_i.c" ".\RDOKB.h"
"$(INTDIR)\RDOKB.obj"	 : $(SOURCE) "$(INTDIR)" "$(INTDIR)\RDOKB.pch" ".\RDOKB_i.c" ".\RDOKB.h"


!ENDIF 

SOURCE=.\RDOKB.idl

!IF  "$(CFG)" == "RDOKB - Win32 Unicode Debug"

InputPath=.\RDOKB.idl

".\RDOKB.tlb"	".\RDOKB.h"	".\RDOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "RDOKB.h" /iid "RDOKB_i.c" "RDOKB.idl"
<< 
	

!ELSEIF  "$(CFG)" == "RDOKB - Win32 Release MinSize"

InputPath=.\RDOKB.idl

".\RDOKB.tlb"	".\RDOKB.h"	".\RDOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "RDOKB.h" /iid "RDOKB_i.c" "RDOKB.idl"
<< 
	

!ELSEIF  "$(CFG)" == "RDOKB - Win32 Release MinDependency"

InputPath=.\RDOKB.idl

".\RDOKB.tlb"	".\RDOKB.h"	".\RDOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "RDOKB.h" /iid "RDOKB_i.c" "RDOKB.idl"
<< 
	

!ELSEIF  "$(CFG)" == "RDOKB - Win32 Unicode Release MinSize"

InputPath=.\RDOKB.idl

".\RDOKB.tlb"	".\RDOKB.h"	".\RDOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "RDOKB.h" /iid "RDOKB_i.c" "RDOKB.idl"
<< 
	

!ELSEIF  "$(CFG)" == "RDOKB - Win32 Unicode Release MinDependency"

InputPath=.\RDOKB.idl

".\RDOKB.tlb"	".\RDOKB.h"	".\RDOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "RDOKB.h" /iid "RDOKB_i.c" "RDOKB.idl"
<< 
	

!ELSEIF  "$(CFG)" == "RDOKB - Win32 Debug"

InputPath=.\RDOKB.idl

".\RDOKB.tlb"	".\RDOKB.h"	".\RDOKB_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "RDOKB.h" /iid "RDOKB_i.c" "RDOKB.idl"
<< 
	

!ENDIF 

SOURCE=.\RDOKB.rc

"$(INTDIR)\RDOKB.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "RDOKB - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\RDOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\RDOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\RDOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\RDOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\RDOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\RDOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\RDOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\RDOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\RDOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\RDOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "RDOKB - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\RDOKB.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\RDOKB.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\RDOKB.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

