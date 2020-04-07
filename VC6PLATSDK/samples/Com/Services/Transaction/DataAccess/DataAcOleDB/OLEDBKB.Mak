!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on Oledbkb.dsp
!IF "$(CFG)" == ""
CFG=Oledbkb - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Oledbkb - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "Oledbkb - Win32 Unicode Debug" && "$(CFG)" != "Oledbkb - Win32 Release MinSize" && "$(CFG)" != "Oledbkb - Win32 Release MinDependency" && "$(CFG)" != "Oledbkb - Win32 Unicode Release MinSize" && "$(CFG)" != "Oledbkb - Win32 Unicode Release MinDependency" && "$(CFG)" != "Oledbkb - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Oledbkb.mak" CFG="Oledbkb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Oledbkb - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Oledbkb - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Oledbkb - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Oledbkb - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Oledbkb - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Oledbkb - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Oledbkb - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : ".\Oledbkb_i.c" ".\Oledbkb.tlb" ".\Oledbkb.h" "$(OUTDIR)\Oledbkb.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\OLEDBComponent.obj"
	-@erase "$(INTDIR)\Oledbkb.obj"
	-@erase "$(INTDIR)\Oledbkb.pch"
	-@erase "$(INTDIR)\Oledbkb.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Oledbkb.dll"
	-@erase "$(OUTDIR)\Oledbkb.exp"
	-@erase "$(OUTDIR)\Oledbkb.ilk"
	-@erase "$(OUTDIR)\Oledbkb.lib"
	-@erase "$(OUTDIR)\Oledbkb.pdb"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\Oledbkb.h"
	-@erase ".\Oledbkb.tlb"
	-@erase ".\Oledbkb_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Oledbkb.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Oledbkb.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Oledbkb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledbd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Oledbkb.pdb" /debug /machine:$(CPU) /def:".\Oledbkb.def" /out:"$(OUTDIR)\Oledbkb.dll" /implib:"$(OUTDIR)\Oledbkb.lib" /pdbtype:sept 
DEF_FILE= \
	".\Oledbkb.def"
LINK32_OBJS= \
	"$(INTDIR)\OLEDBComponent.obj" \
	"$(INTDIR)\Oledbkb.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Oledbkb.res"

"$(OUTDIR)\Oledbkb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\Oledbkb.dll
InputPath=.\DebugU\Oledbkb.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\Oledbkb_i.c" ".\Oledbkb.tlb" ".\Oledbkb.h" "$(OUTDIR)\Oledbkb.dll" "$(OUTDIR)\Oledbkb.bsc" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\OLEDBComponent.obj"
	-@erase "$(INTDIR)\OLEDBComponent.sbr"
	-@erase "$(INTDIR)\Oledbkb.obj"
	-@erase "$(INTDIR)\Oledbkb.pch"
	-@erase "$(INTDIR)\Oledbkb.res"
	-@erase "$(INTDIR)\Oledbkb.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Oledbkb.bsc"
	-@erase "$(OUTDIR)\Oledbkb.dll"
	-@erase "$(OUTDIR)\Oledbkb.exp"
	-@erase "$(OUTDIR)\Oledbkb.lib"
	-@erase ".\Oledbkb.h"
	-@erase ".\Oledbkb.tlb"
	-@erase ".\Oledbkb_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Oledbkb.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Oledbkb.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Oledbkb.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\OLEDBComponent.sbr" \
	"$(INTDIR)\Oledbkb.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Oledbkb.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Oledbkb.pdb" /machine:$(CPU) /def:".\Oledbkb.def" /out:"$(OUTDIR)\Oledbkb.dll" /implib:"$(OUTDIR)\Oledbkb.lib" 
DEF_FILE= \
	".\Oledbkb.def"
LINK32_OBJS= \
	"$(INTDIR)\OLEDBComponent.obj" \
	"$(INTDIR)\Oledbkb.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Oledbkb.res"

"$(OUTDIR)\Oledbkb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Oledbkb.dll
InputPath=.\ReleaseMinSize\Oledbkb.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\Oledbkb_i.c" ".\Oledbkb.tlb" ".\Oledbkb.h" "$(OUTDIR)\Oledbkb.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\OLEDBComponent.obj"
	-@erase "$(INTDIR)\Oledbkb.obj"
	-@erase "$(INTDIR)\Oledbkb.pch"
	-@erase "$(INTDIR)\Oledbkb.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Oledbkb.dll"
	-@erase "$(OUTDIR)\Oledbkb.exp"
	-@erase "$(OUTDIR)\Oledbkb.lib"
	-@erase ".\Oledbkb.h"
	-@erase ".\Oledbkb.tlb"
	-@erase ".\Oledbkb_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Oledbkb.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Oledbkb.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Oledbkb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Oledbkb.pdb" /machine:$(CPU) /def:".\Oledbkb.def" /out:"$(OUTDIR)\Oledbkb.dll" /implib:"$(OUTDIR)\Oledbkb.lib" 
DEF_FILE= \
	".\Oledbkb.def"
LINK32_OBJS= \
	"$(INTDIR)\OLEDBComponent.obj" \
	"$(INTDIR)\Oledbkb.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Oledbkb.res"

"$(OUTDIR)\Oledbkb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\Oledbkb.dll
InputPath=.\ReleaseMinDependency\Oledbkb.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : ".\Oledbkb_i.c" ".\Oledbkb.tlb" ".\Oledbkb.h" "$(OUTDIR)\Oledbkb.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\OLEDBComponent.obj"
	-@erase "$(INTDIR)\Oledbkb.obj"
	-@erase "$(INTDIR)\Oledbkb.pch"
	-@erase "$(INTDIR)\Oledbkb.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Oledbkb.dll"
	-@erase "$(OUTDIR)\Oledbkb.exp"
	-@erase "$(OUTDIR)\Oledbkb.lib"
	-@erase ".\Oledbkb.h"
	-@erase ".\Oledbkb.tlb"
	-@erase ".\Oledbkb_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\Oledbkb.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Oledbkb.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Oledbkb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Oledbkb.pdb" /machine:$(CPU) /def:".\Oledbkb.def" /out:"$(OUTDIR)\Oledbkb.dll" /implib:"$(OUTDIR)\Oledbkb.lib" 
DEF_FILE= \
	".\Oledbkb.def"
LINK32_OBJS= \
	"$(INTDIR)\OLEDBComponent.obj" \
	"$(INTDIR)\Oledbkb.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Oledbkb.res"

"$(OUTDIR)\Oledbkb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Oledbkb.dll
InputPath=.\ReleaseUMinSize\Oledbkb.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : ".\Oledbkb_i.c" ".\Oledbkb.tlb" ".\Oledbkb.h" "$(OUTDIR)\Oledbkb.dll" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\OLEDBComponent.obj"
	-@erase "$(INTDIR)\Oledbkb.obj"
	-@erase "$(INTDIR)\Oledbkb.pch"
	-@erase "$(INTDIR)\Oledbkb.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Oledbkb.dll"
	-@erase "$(OUTDIR)\Oledbkb.exp"
	-@erase "$(OUTDIR)\Oledbkb.lib"
	-@erase ".\Oledbkb.h"
	-@erase ".\Oledbkb.tlb"
	-@erase ".\Oledbkb_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Oledbkb.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Oledbkb.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Oledbkb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Oledbkb.pdb" /machine:$(CPU) /def:".\Oledbkb.def" /out:"$(OUTDIR)\Oledbkb.dll" /implib:"$(OUTDIR)\Oledbkb.lib" 
DEF_FILE= \
	".\Oledbkb.def"
LINK32_OBJS= \
	"$(INTDIR)\OLEDBComponent.obj" \
	"$(INTDIR)\Oledbkb.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Oledbkb.res"

"$(OUTDIR)\Oledbkb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\Oledbkb.dll
InputPath=.\ReleaseUMinDependency\Oledbkb.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\Oledbkb_i.c" ".\Oledbkb.tlb" ".\Oledbkb.h" "$(OUTDIR)\Oledbkb.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\OLEDBComponent.obj"
	-@erase "$(INTDIR)\Oledbkb.obj"
	-@erase "$(INTDIR)\Oledbkb.pch"
	-@erase "$(INTDIR)\Oledbkb.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Oledbkb.dll"
	-@erase "$(OUTDIR)\Oledbkb.exp"
	-@erase "$(OUTDIR)\Oledbkb.ilk"
	-@erase "$(OUTDIR)\Oledbkb.lib"
	-@erase "$(OUTDIR)\Oledbkb.pdb"
	-@erase ".\Debug\regsvr32.trg"
	-@erase ".\Oledbkb.h"
	-@erase ".\Oledbkb.tlb"
	-@erase ".\Oledbkb_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\Oledbkb.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Oledbkb.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Oledbkb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledbd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Oledbkb.pdb" /debug /machine:$(CPU) /def:".\Oledbkb.def" /out:"$(OUTDIR)\Oledbkb.dll" /implib:"$(OUTDIR)\Oledbkb.lib" /pdbtype:sept 
DEF_FILE= \
	".\Oledbkb.def"
LINK32_OBJS= \
	"$(INTDIR)\OLEDBComponent.obj" \
	"$(INTDIR)\Oledbkb.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Oledbkb.res"

"$(OUTDIR)\Oledbkb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\Oledbkb.dll
InputPath=.\Debug\Oledbkb.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Oledbkb.dep")
!INCLUDE "Oledbkb.dep"
!ELSE 
!MESSAGE Warning: cannot find "Oledbkb.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Oledbkb - Win32 Unicode Debug" || "$(CFG)" == "Oledbkb - Win32 Release MinSize" || "$(CFG)" == "Oledbkb - Win32 Release MinDependency" || "$(CFG)" == "Oledbkb - Win32 Unicode Release MinSize" || "$(CFG)" == "Oledbkb - Win32 Unicode Release MinDependency" || "$(CFG)" == "Oledbkb - Win32 Debug"
SOURCE=.\OLEDBComponent.cpp

!IF  "$(CFG)" == "Oledbkb - Win32 Unicode Debug"


"$(INTDIR)\OLEDBComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Release MinSize"


"$(INTDIR)\OLEDBComponent.obj"	"$(INTDIR)\OLEDBComponent.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Release MinDependency"


"$(INTDIR)\OLEDBComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Unicode Release MinSize"


"$(INTDIR)\OLEDBComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Unicode Release MinDependency"


"$(INTDIR)\OLEDBComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Debug"


"$(INTDIR)\OLEDBComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ENDIF 

SOURCE=.\Oledbkb.cpp

!IF  "$(CFG)" == "Oledbkb - Win32 Unicode Debug"


"$(INTDIR)\Oledbkb.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Release MinSize"


"$(INTDIR)\Oledbkb.obj"	"$(INTDIR)\Oledbkb.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Release MinDependency"


"$(INTDIR)\Oledbkb.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Unicode Release MinSize"


"$(INTDIR)\Oledbkb.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Unicode Release MinDependency"


"$(INTDIR)\Oledbkb.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Debug"


"$(INTDIR)\Oledbkb.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Oledbkb.pch"


!ENDIF 

SOURCE=.\Oledbkb.idl

!IF  "$(CFG)" == "Oledbkb - Win32 Unicode Debug"

InputPath=.\Oledbkb.idl

".\Oledbkb.tlb"	".\Oledbkb.h"	".\Oledbkb_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Oledbkb.h" /iid "Oledbkb_i.c" "Oledbkb.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Release MinSize"

InputPath=.\Oledbkb.idl

".\Oledbkb.tlb"	".\Oledbkb.h"	".\Oledbkb_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Oledbkb.h" /iid "Oledbkb_i.c" "Oledbkb.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Release MinDependency"

InputPath=.\Oledbkb.idl

".\Oledbkb.tlb"	".\Oledbkb.h"	".\Oledbkb_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Oledbkb.h" /iid "Oledbkb_i.c" "Oledbkb.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Unicode Release MinSize"

InputPath=.\Oledbkb.idl

".\Oledbkb.tlb"	".\Oledbkb.h"	".\Oledbkb_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Oledbkb.h" /iid "Oledbkb_i.c" "Oledbkb.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Unicode Release MinDependency"

InputPath=.\Oledbkb.idl

".\Oledbkb.tlb"	".\Oledbkb.h"	".\Oledbkb_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Oledbkb.h" /iid "Oledbkb_i.c" "Oledbkb.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Debug"

InputPath=.\Oledbkb.idl

".\Oledbkb.tlb"	".\Oledbkb.h"	".\Oledbkb_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Oledbkb.h" /iid "Oledbkb_i.c" "Oledbkb.idl"
<< 
	

!ENDIF 

SOURCE=.\Oledbkb.rc

"$(INTDIR)\Oledbkb.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Oledbkb - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Oledbkb.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Oledbkb.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Oledbkb.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Oledbkb.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Oledbkb.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Oledbkb.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\Oledbkb.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Oledbkb.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Oledbkb.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Oledbkb.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Oledbkb - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\Oledbkb.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Oledbkb.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

