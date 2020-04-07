!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on Disp1.dsp
!IF "$(CFG)" == ""
CFG=Disp1 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Disp1 - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "Disp1 - Win32 Debug" && "$(CFG)" != "Disp1 - Win32 Unicode Debug" && "$(CFG)" != "Disp1 - Win32 Release MinSize" && "$(CFG)" != "Disp1 - Win32 Release MinDependency" && "$(CFG)" != "Disp1 - Win32 Unicode Release MinSize" && "$(CFG)" != "Disp1 - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Disp1.mak" CFG="Disp1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Disp1 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Disp1 - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Disp1 - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Disp1 - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Disp1 - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Disp1 - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Disp1 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Disp1.dll" "$(OUTDIR)\Disp1.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Disp1.obj"
	-@erase "$(INTDIR)\Disp1.pch"
	-@erase "$(INTDIR)\Disp1.res"
	-@erase "$(INTDIR)\Disp1.sbr"
	-@erase "$(INTDIR)\LDisp.obj"
	-@erase "$(INTDIR)\LDisp.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Disp1.bsc"
	-@erase "$(OUTDIR)\Disp1.dll"
	-@erase "$(OUTDIR)\Disp1.exp"
	-@erase "$(OUTDIR)\Disp1.ilk"
	-@erase "$(OUTDIR)\Disp1.lib"
	-@erase "$(OUTDIR)\Disp1.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Disp1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Disp1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Disp1.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Disp1.sbr" \
	"$(INTDIR)\LDisp.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Disp1.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtxdm.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Disp1.pdb" /debug /machine:$(mach_type) /def:".\Disp1.def" /out:"$(OUTDIR)\Disp1.dll" /implib:"$(OUTDIR)\Disp1.lib" /pdbtype:sept 
DEF_FILE= \
	".\Disp1.def"
LINK32_OBJS= \
	"$(INTDIR)\Disp1.obj" \
	"$(INTDIR)\LDisp.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Disp1.res"

"$(OUTDIR)\Disp1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\Disp1.dll
InputPath=.\Debug\Disp1.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : ".\Disp1_i.c" ".\Disp1.tlb" ".\Disp1.h" "$(OUTDIR)\Disp1.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Disp1.obj"
	-@erase "$(INTDIR)\Disp1.pch"
	-@erase "$(INTDIR)\Disp1.res"
	-@erase "$(INTDIR)\LDisp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Disp1.dll"
	-@erase "$(OUTDIR)\Disp1.exp"
	-@erase "$(OUTDIR)\Disp1.ilk"
	-@erase "$(OUTDIR)\Disp1.lib"
	-@erase "$(OUTDIR)\Disp1.pdb"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\Disp1.h"
	-@erase ".\Disp1.tlb"
	-@erase ".\Disp1_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Disp1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Disp1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Disp1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtxdm.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Disp1.pdb" /debug /machine:$(mach_type) /def:".\Disp1.def" /out:"$(OUTDIR)\Disp1.dll" /implib:"$(OUTDIR)\Disp1.lib" /pdbtype:sept 
DEF_FILE= \
	".\Disp1.def"
LINK32_OBJS= \
	"$(INTDIR)\Disp1.obj" \
	"$(INTDIR)\LDisp.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Disp1.res"

"$(OUTDIR)\Disp1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\Disp1.dll
InputPath=.\DebugU\Disp1.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Disp1 - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\Disp1_i.c" ".\Disp1.tlb" ".\Disp1.h" "$(OUTDIR)\Disp1.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Disp1.obj"
	-@erase "$(INTDIR)\Disp1.pch"
	-@erase "$(INTDIR)\Disp1.res"
	-@erase "$(INTDIR)\LDisp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Disp1.dll"
	-@erase "$(OUTDIR)\Disp1.exp"
	-@erase "$(OUTDIR)\Disp1.lib"
	-@erase ".\Disp1.h"
	-@erase ".\Disp1.tlb"
	-@erase ".\Disp1_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Disp1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Disp1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Disp1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtxdm.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Disp1.pdb" /machine:$(mach_type) /def:".\Disp1.def" /out:"$(OUTDIR)\Disp1.dll" /implib:"$(OUTDIR)\Disp1.lib" 
DEF_FILE= \
	".\Disp1.def"
LINK32_OBJS= \
	"$(INTDIR)\Disp1.obj" \
	"$(INTDIR)\LDisp.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Disp1.res"

"$(OUTDIR)\Disp1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Disp1.dll
InputPath=.\ReleaseMinSize\Disp1.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Disp1 - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\Disp1_i.c" ".\Disp1.tlb" ".\Disp1.h" "$(OUTDIR)\Disp1.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Disp1.obj"
	-@erase "$(INTDIR)\Disp1.pch"
	-@erase "$(INTDIR)\Disp1.res"
	-@erase "$(INTDIR)\LDisp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Disp1.dll"
	-@erase "$(OUTDIR)\Disp1.exp"
	-@erase "$(OUTDIR)\Disp1.lib"
	-@erase ".\Disp1.h"
	-@erase ".\Disp1.tlb"
	-@erase ".\Disp1_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Disp1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Disp1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Disp1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtxdm.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Disp1.pdb" /machine:$(mach_type) /def:".\Disp1.def" /out:"$(OUTDIR)\Disp1.dll" /implib:"$(OUTDIR)\Disp1.lib" 
DEF_FILE= \
	".\Disp1.def"
LINK32_OBJS= \
	"$(INTDIR)\Disp1.obj" \
	"$(INTDIR)\LDisp.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Disp1.res"

"$(OUTDIR)\Disp1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\Disp1.dll
InputPath=.\ReleaseMinDependency\Disp1.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : ".\Disp1_i.c" ".\Disp1.tlb" ".\Disp1.h" "$(OUTDIR)\Disp1.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Disp1.obj"
	-@erase "$(INTDIR)\Disp1.pch"
	-@erase "$(INTDIR)\Disp1.res"
	-@erase "$(INTDIR)\LDisp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Disp1.dll"
	-@erase "$(OUTDIR)\Disp1.exp"
	-@erase "$(OUTDIR)\Disp1.lib"
	-@erase ".\Disp1.h"
	-@erase ".\Disp1.tlb"
	-@erase ".\Disp1_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Disp1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Disp1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Disp1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtxdm.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Disp1.pdb" /machine:$(mach_type) /def:".\Disp1.def" /out:"$(OUTDIR)\Disp1.dll" /implib:"$(OUTDIR)\Disp1.lib" 
DEF_FILE= \
	".\Disp1.def"
LINK32_OBJS= \
	"$(INTDIR)\Disp1.obj" \
	"$(INTDIR)\LDisp.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Disp1.res"

"$(OUTDIR)\Disp1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Disp1.dll
InputPath=.\ReleaseUMinSize\Disp1.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : ".\Disp1_i.c" ".\Disp1.tlb" ".\Disp1.h" "$(OUTDIR)\Disp1.dll" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Disp1.obj"
	-@erase "$(INTDIR)\Disp1.pch"
	-@erase "$(INTDIR)\Disp1.res"
	-@erase "$(INTDIR)\LDisp.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Disp1.dll"
	-@erase "$(OUTDIR)\Disp1.exp"
	-@erase "$(OUTDIR)\Disp1.lib"
	-@erase ".\Disp1.h"
	-@erase ".\Disp1.tlb"
	-@erase ".\Disp1_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Disp1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Disp1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Disp1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mtxdm.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Disp1.pdb" /machine:$(mach_type) /def:".\Disp1.def" /out:"$(OUTDIR)\Disp1.dll" /implib:"$(OUTDIR)\Disp1.lib" 
DEF_FILE= \
	".\Disp1.def"
LINK32_OBJS= \
	"$(INTDIR)\Disp1.obj" \
	"$(INTDIR)\LDisp.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Disp1.res"

"$(OUTDIR)\Disp1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\Disp1.dll
InputPath=.\ReleaseUMinDependency\Disp1.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Disp1.dep")
!INCLUDE "Disp1.dep"
!ELSE 
!MESSAGE Warning: cannot find "Disp1.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Disp1 - Win32 Debug" || "$(CFG)" == "Disp1 - Win32 Unicode Debug" || "$(CFG)" == "Disp1 - Win32 Release MinSize" || "$(CFG)" == "Disp1 - Win32 Release MinDependency" || "$(CFG)" == "Disp1 - Win32 Unicode Release MinSize" || "$(CFG)" == "Disp1 - Win32 Unicode Release MinDependency"
SOURCE=.\Disp1.cpp

!IF  "$(CFG)" == "Disp1 - Win32 Debug"


"$(INTDIR)\Disp1.obj"	"$(INTDIR)\Disp1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch" ".\Disp1.h" ".\Disp1_i.c"


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Debug"


"$(INTDIR)\Disp1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch"


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Release MinSize"


"$(INTDIR)\Disp1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch"


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Release MinDependency"


"$(INTDIR)\Disp1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch"


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Release MinSize"


"$(INTDIR)\Disp1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch"


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Release MinDependency"


"$(INTDIR)\Disp1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch"


!ENDIF 

SOURCE=.\Disp1.idl

!IF  "$(CFG)" == "Disp1 - Win32 Debug"

InputPath=.\Disp1.idl

".\Disp1.tlb"	".\Disp1.h"	".\Disp1_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Disp1.h" /iid "Disp1_i.c" "Disp1.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Debug"

InputPath=.\Disp1.idl

".\Disp1.tlb"	".\Disp1.h"	".\Disp1_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Disp1.h" /iid "Disp1_i.c" "Disp1.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Disp1 - Win32 Release MinSize"

InputPath=.\Disp1.idl

".\Disp1.tlb"	".\Disp1.h"	".\Disp1_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Disp1.h" /iid "Disp1_i.c" "Disp1.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Disp1 - Win32 Release MinDependency"

InputPath=.\Disp1.idl

".\Disp1.tlb"	".\Disp1.h"	".\Disp1_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Disp1.h" /iid "Disp1_i.c" "Disp1.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Release MinSize"

InputPath=.\Disp1.idl

".\Disp1.tlb"	".\Disp1.h"	".\Disp1_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Disp1.h" /iid "Disp1_i.c" "Disp1.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Release MinDependency"

InputPath=.\Disp1.idl

".\Disp1.tlb"	".\Disp1.h"	".\Disp1_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "Disp1.h" /iid "Disp1_i.c" "Disp1.idl"
<< 
	

!ENDIF 

SOURCE=.\Disp1.rc

"$(INTDIR)\Disp1.res" : $(SOURCE) "$(INTDIR)" ".\Disp1.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\LDisp.cpp

!IF  "$(CFG)" == "Disp1 - Win32 Debug"


"$(INTDIR)\LDisp.obj"	"$(INTDIR)\LDisp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch" ".\Disp1.h"


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Debug"


"$(INTDIR)\LDisp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch"


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Release MinSize"


"$(INTDIR)\LDisp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch"


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Release MinDependency"


"$(INTDIR)\LDisp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch"


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Release MinSize"


"$(INTDIR)\LDisp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch"


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Release MinDependency"


"$(INTDIR)\LDisp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Disp1.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Disp1 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Disp1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Disp1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Disp1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Disp1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Disp1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Disp1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Disp1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Disp1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Disp1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Disp1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Disp1 - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Disp1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Disp1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

