!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on CrmFiles.dsp
!IF "$(CFG)" == ""
CFG=CrmFiles - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CrmFiles - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "CrmFiles - Win32 Unicode Debug" && "$(CFG)" != "CrmFiles - Win32 Release MinSize" && "$(CFG)" != "CrmFiles - Win32 Release MinDependency" && "$(CFG)" != "CrmFiles - Win32 Unicode Release MinSize" && "$(CFG)" != "CrmFiles - Win32 Unicode Release MinDependency" && "$(CFG)" != "CrmFiles - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CrmFiles.mak" CFG="CrmFiles - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CrmFiles - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmFiles - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmFiles - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmFiles - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmFiles - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmFiles - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CrmFiles - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

#ALL : "$(OUTDIR)\CrmFiles.dll" "$(OUTDIR)\CrmFiles.bsc" ".\DebugU\regsvr32.trg"
ALL : "$(OUTDIR)\CrmFiles.dll"  ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFiles.obj"
	-@erase "$(INTDIR)\CrmFiles.pch"
	-@erase "$(INTDIR)\CrmFiles.res"
	-@erase "$(INTDIR)\CrmFiles.sbr"
	-@erase "$(INTDIR)\CrmFilesCompensator.obj"
	-@erase "$(INTDIR)\CrmFilesCompensator.sbr"
	-@erase "$(INTDIR)\CrmFilesWorker.obj"
	-@erase "$(INTDIR)\CrmFilesWorker.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CrmFiles.bsc"
	-@erase "$(OUTDIR)\CrmFiles.dll"
	-@erase "$(OUTDIR)\CrmFiles.exp"
	-@erase "$(OUTDIR)\CrmFiles.ilk"
	-@erase "$(OUTDIR)\CrmFiles.lib"
	-@erase "$(OUTDIR)\CrmFiles.pdb"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFiles.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFiles.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\CrmFiles.sbr" \
#	"$(INTDIR)\CrmFilesCompensator.sbr" \
#	"$(INTDIR)\CrmFilesWorker.sbr" \
#	"$(INTDIR)\StdAfx.sbr"

#"$(OUTDIR)\CrmFiles.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\CrmFiles.pdb" /debug /machine:$(CPU) /def:".\CrmFiles.def" /out:"$(OUTDIR)\CrmFiles.dll" /implib:"$(OUTDIR)\CrmFiles.lib" /pdbtype:sept 
DEF_FILE= \
	".\CrmFiles.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFiles.obj" \
	"$(INTDIR)\CrmFilesCompensator.obj" \
	"$(INTDIR)\CrmFilesWorker.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFiles.res"

"$(OUTDIR)\CrmFiles.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\CrmFiles.dll
InputPath=.\DebugU\CrmFiles.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

#ALL : ".\CrmFiles_i.c" ".\CrmFiles.tlb" ".\CrmFiles.h" "$(OUTDIR)\CrmFiles.dll" "$(OUTDIR)\CrmFiles.bsc" ".\ReleaseMinSize\regsvr32.trg"
ALL : ".\CrmFiles_i.c" ".\CrmFiles.tlb" ".\CrmFiles.h" "$(OUTDIR)\CrmFiles.dll"  ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFiles.obj"
	-@erase "$(INTDIR)\CrmFiles.pch"
	-@erase "$(INTDIR)\CrmFiles.res"
	-@erase "$(INTDIR)\CrmFiles.sbr"
	-@erase "$(INTDIR)\CrmFilesCompensator.obj"
	-@erase "$(INTDIR)\CrmFilesCompensator.sbr"
	-@erase "$(INTDIR)\CrmFilesWorker.obj"
	-@erase "$(INTDIR)\CrmFilesWorker.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmFiles.bsc"
	-@erase "$(OUTDIR)\CrmFiles.dll"
	-@erase "$(OUTDIR)\CrmFiles.exp"
	-@erase "$(OUTDIR)\CrmFiles.lib"
	-@erase ".\CrmFiles.h"
	-@erase ".\CrmFiles.tlb"
	-@erase ".\CrmFiles_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "NDEBUG" /D "_ATL_DLL"  /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFiles.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFiles.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\CrmFiles.sbr" \
#	"$(INTDIR)\CrmFilesCompensator.sbr" \
#	"$(INTDIR)\CrmFilesWorker.sbr" \
#	"$(INTDIR)\StdAfx.sbr"
#
#"$(OUTDIR)\CrmFiles.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmFiles.pdb" /machine:$(CPU) /def:".\CrmFiles.def" /out:"$(OUTDIR)\CrmFiles.dll" /implib:"$(OUTDIR)\CrmFiles.lib" 
DEF_FILE= \
	".\CrmFiles.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFiles.obj" \
	"$(INTDIR)\CrmFilesCompensator.obj" \
	"$(INTDIR)\CrmFilesWorker.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFiles.res"

"$(OUTDIR)\CrmFiles.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\CrmFiles.dll
InputPath=.\ReleaseMinSize\CrmFiles.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

#ALL : ".\CrmFiles_i.c" ".\CrmFiles.tlb" ".\CrmFiles.h" "$(OUTDIR)\CrmFiles.dll" "$(OUTDIR)\CrmFiles.bsc" ".\ReleaseMinDependency\regsvr32.trg"
ALL : ".\CrmFiles_i.c" ".\CrmFiles.tlb" ".\CrmFiles.h" "$(OUTDIR)\CrmFiles.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFiles.obj"
	-@erase "$(INTDIR)\CrmFiles.pch"
	-@erase "$(INTDIR)\CrmFiles.res"
	-@erase "$(INTDIR)\CrmFiles.sbr"
	-@erase "$(INTDIR)\CrmFilesCompensator.obj"
	-@erase "$(INTDIR)\CrmFilesCompensator.sbr"
	-@erase "$(INTDIR)\CrmFilesWorker.obj"
	-@erase "$(INTDIR)\CrmFilesWorker.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmFiles.bsc"
	-@erase "$(OUTDIR)\CrmFiles.dll"
	-@erase "$(OUTDIR)\CrmFiles.exp"
	-@erase "$(OUTDIR)\CrmFiles.lib"
	-@erase ".\CrmFiles.h"
	-@erase ".\CrmFiles.tlb"
	-@erase ".\CrmFiles_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "NDEBUG" /D "_ATL_STATIC_REGISTRY"  /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFiles.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFiles.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\CrmFiles.sbr" \
#	"$(INTDIR)\CrmFilesCompensator.sbr" \
#	"$(INTDIR)\CrmFilesWorker.sbr" \
#	"$(INTDIR)\StdAfx.sbr"
#
#"$(OUTDIR)\CrmFiles.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmFiles.pdb" /machine:$(CPU) /def:".\CrmFiles.def" /out:"$(OUTDIR)\CrmFiles.dll" /implib:"$(OUTDIR)\CrmFiles.lib" 
DEF_FILE= \
	".\CrmFiles.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFiles.obj" \
	"$(INTDIR)\CrmFilesCompensator.obj" \
	"$(INTDIR)\CrmFilesWorker.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFiles.res"

"$(OUTDIR)\CrmFiles.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\CrmFiles.dll
InputPath=.\ReleaseMinDependency\CrmFiles.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

#ALL : ".\CrmFiles_i.c" ".\CrmFiles.tlb" ".\CrmFiles.h" "$(OUTDIR)\CrmFiles.dll" "$(OUTDIR)\CrmFiles.bsc" ".\ReleaseUMinSize\regsvr32.trg"
ALL : ".\CrmFiles_i.c" ".\CrmFiles.tlb" ".\CrmFiles.h" "$(OUTDIR)\CrmFiles.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFiles.obj"
	-@erase "$(INTDIR)\CrmFiles.pch"
	-@erase "$(INTDIR)\CrmFiles.res"
	-@erase "$(INTDIR)\CrmFiles.sbr"
	-@erase "$(INTDIR)\CrmFilesCompensator.obj"
	-@erase "$(INTDIR)\CrmFilesCompensator.sbr"
	-@erase "$(INTDIR)\CrmFilesWorker.obj"
	-@erase "$(INTDIR)\CrmFilesWorker.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmFiles.bsc"
	-@erase "$(OUTDIR)\CrmFiles.dll"
	-@erase "$(OUTDIR)\CrmFiles.exp"
	-@erase "$(OUTDIR)\CrmFiles.lib"
	-@erase ".\CrmFiles.h"
	-@erase ".\CrmFiles.tlb"
	-@erase ".\CrmFiles_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "NDEBUG" /D "_UNICODE" /D "_ATL_DLL"  /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFiles.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFiles.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\CrmFiles.sbr" \
#	"$(INTDIR)\CrmFilesCompensator.sbr" \
#	"$(INTDIR)\CrmFilesWorker.sbr" \
#	"$(INTDIR)\StdAfx.sbr"
#
#"$(OUTDIR)\CrmFiles.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmFiles.pdb" /machine:$(CPU) /def:".\CrmFiles.def" /out:"$(OUTDIR)\CrmFiles.dll" /implib:"$(OUTDIR)\CrmFiles.lib" 
DEF_FILE= \
	".\CrmFiles.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFiles.obj" \
	"$(INTDIR)\CrmFilesCompensator.obj" \
	"$(INTDIR)\CrmFilesWorker.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFiles.res"

"$(OUTDIR)\CrmFiles.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\CrmFiles.dll
InputPath=.\ReleaseUMinSize\CrmFiles.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

#ALL : ".\CrmFiles_i.c" ".\CrmFiles.tlb" ".\CrmFiles.h" "$(OUTDIR)\CrmFiles.dll" "$(OUTDIR)\CrmFiles.bsc" ".\ReleaseUMinDependency\regsvr32.trg"
ALL : ".\CrmFiles_i.c" ".\CrmFiles.tlb" ".\CrmFiles.h" "$(OUTDIR)\CrmFiles.dll" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFiles.obj"
	-@erase "$(INTDIR)\CrmFiles.pch"
	-@erase "$(INTDIR)\CrmFiles.res"
	-@erase "$(INTDIR)\CrmFiles.sbr"
	-@erase "$(INTDIR)\CrmFilesCompensator.obj"
	-@erase "$(INTDIR)\CrmFilesCompensator.sbr"
	-@erase "$(INTDIR)\CrmFilesWorker.obj"
	-@erase "$(INTDIR)\CrmFilesWorker.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmFiles.bsc"
	-@erase "$(OUTDIR)\CrmFiles.dll"
	-@erase "$(OUTDIR)\CrmFiles.exp"
	-@erase "$(OUTDIR)\CrmFiles.lib"
	-@erase ".\CrmFiles.h"
	-@erase ".\CrmFiles.tlb"
	-@erase ".\CrmFiles_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "NDEBUG" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"  /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFiles.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFiles.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\CrmFiles.sbr" \
#	"$(INTDIR)\CrmFilesCompensator.sbr" \
#	"$(INTDIR)\CrmFilesWorker.sbr" \
#	"$(INTDIR)\StdAfx.sbr"
#
#"$(OUTDIR)\CrmFiles.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmFiles.pdb" /machine:$(CPU) /def:".\CrmFiles.def" /out:"$(OUTDIR)\CrmFiles.dll" /implib:"$(OUTDIR)\CrmFiles.lib" 
DEF_FILE= \
	".\CrmFiles.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFiles.obj" \
	"$(INTDIR)\CrmFilesCompensator.obj" \
	"$(INTDIR)\CrmFilesWorker.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFiles.res"

"$(OUTDIR)\CrmFiles.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\CrmFiles.dll
InputPath=.\ReleaseUMinDependency\CrmFiles.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

#ALL : ".\dlldata.c" ".\CrmFiles_p.c" ".\CrmFiles_i.c" ".\CrmFiles.tlb" ".\CrmFiles.h" "$(OUTDIR)\CrmFiles.dll" "$(OUTDIR)\CrmFiles.pch" "$(OUTDIR)\CrmFiles.bsc" ".\Debug\regsvr32.trg"
ALL : ".\dlldata.c" ".\CrmFiles_p.c" ".\CrmFiles_i.c" ".\CrmFiles.tlb" ".\CrmFiles.h" "$(OUTDIR)\CrmFiles.dll" "$(OUTDIR)\CrmFiles.pch" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmFiles.obj"
	-@erase "$(INTDIR)\CrmFiles.pch"
	-@erase "$(INTDIR)\CrmFiles.res"
	-@erase "$(INTDIR)\CrmFiles.sbr"
	-@erase "$(INTDIR)\CrmFilesCompensator.obj"
	-@erase "$(INTDIR)\CrmFilesCompensator.sbr"
	-@erase "$(INTDIR)\CrmFilesWorker.obj"
	-@erase "$(INTDIR)\CrmFilesWorker.sbr"
	-@erase "$(INTDIR)\dlldatax.obj"
	-@erase "$(INTDIR)\dlldatax.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CrmFiles.bsc"
	-@erase "$(OUTDIR)\CrmFiles.dll"
	-@erase "$(OUTDIR)\CrmFiles.exp"
	-@erase "$(OUTDIR)\CrmFiles.ilk"
	-@erase "$(OUTDIR)\CrmFiles.lib"
	-@erase "$(OUTDIR)\CrmFiles.pdb"
	-@erase ".\CrmFiles.h"
	-@erase ".\CrmFiles.tlb"
	-@erase ".\CrmFiles_i.c"
	-@erase ".\Debug\regsvr32.trg"
	-@erase "CrmFiles_p.c"
	-@erase "dlldata.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W4 /Gm /Zi /Od /D "_DEBUG" /D "_MERGE_PROXYSTUB" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmFiles.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmFiles.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\CrmFiles.sbr" \
#	"$(INTDIR)\CrmFilesCompensator.sbr" \
#	"$(INTDIR)\CrmFilesWorker.sbr" \
#	"$(INTDIR)\dlldatax.sbr" \
#	"$(INTDIR)\StdAfx.sbr"
#
#"$(OUTDIR)\CrmFiles.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=comsvcs.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\CrmFiles.pdb" /debug /machine:$(CPU) /def:".\CrmFiles.def" /out:"$(OUTDIR)\CrmFiles.dll" /implib:"$(OUTDIR)\CrmFiles.lib" /pdbtype:sept 
DEF_FILE= \
	".\CrmFiles.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmFiles.obj" \
	"$(INTDIR)\CrmFilesCompensator.obj" \
	"$(INTDIR)\CrmFilesWorker.obj" \
	"$(INTDIR)\dlldatax.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmFiles.res"

"$(OUTDIR)\CrmFiles.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\CrmFiles.dll
InputPath=.\Debug\CrmFiles.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("CrmFiles.dep")
!INCLUDE "CrmFiles.dep"
!ELSE 
!MESSAGE Warning: cannot find "CrmFiles.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CrmFiles - Win32 Unicode Debug" || "$(CFG)" == "CrmFiles - Win32 Release MinSize" || "$(CFG)" == "CrmFiles - Win32 Release MinDependency" || "$(CFG)" == "CrmFiles - Win32 Unicode Release MinSize" || "$(CFG)" == "CrmFiles - Win32 Unicode Release MinDependency" || "$(CFG)" == "CrmFiles - Win32 Debug"
SOURCE=.\CrmFiles.cpp

#"$(INTDIR)\CrmFiles.obj"	"$(INTDIR)\CrmFiles.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFiles.pch" ".\CrmFiles.h" ".\CrmFiles_i.c"
"$(INTDIR)\CrmFiles.obj"	: $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFiles.pch" ".\CrmFiles.h" ".\CrmFiles_i.c"


SOURCE=.\CrmFiles.idl

!IF  "$(CFG)" == "CrmFiles - Win32 Unicode Debug"

InputPath=.\CrmFiles.idl

".\CrmFiles.tlb"	".\CrmFiles.h"	".\CrmFiles_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFiles.h" /iid "CrmFiles_i.c" "CrmFiles.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Release MinSize"

InputPath=.\CrmFiles.idl

".\CrmFiles.tlb"	".\CrmFiles.h"	".\CrmFiles_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFiles.h" /iid "CrmFiles_i.c" "CrmFiles.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Release MinDependency"

InputPath=.\CrmFiles.idl

".\CrmFiles.tlb"	".\CrmFiles.h"	".\CrmFiles_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFiles.h" /iid "CrmFiles_i.c" "CrmFiles.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Unicode Release MinSize"

InputPath=.\CrmFiles.idl

".\CrmFiles.tlb"	".\CrmFiles.h"	".\CrmFiles_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFiles.h" /iid "CrmFiles_i.c" "CrmFiles.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Unicode Release MinDependency"

InputPath=.\CrmFiles.idl

".\CrmFiles.tlb"	".\CrmFiles.h"	".\CrmFiles_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFiles.h" /iid "CrmFiles_i.c" "CrmFiles.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Debug"

InputPath=.\CrmFiles.idl

".\CrmFiles.tlb"	".\CrmFiles.h"	".\CrmFiles_i.c"	".\CrmFiles_p.c"	".\dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmFiles.h" /iid "CrmFiles_i.c" "CrmFiles.idl"
<< 
	

!ENDIF 

SOURCE=.\CrmFiles.rc

"$(INTDIR)\CrmFiles.res" : $(SOURCE) "$(INTDIR)" ".\CrmFiles.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CrmFilesCompensator.cpp

#"$(INTDIR)\CrmFilesCompensator.obj"	"$(INTDIR)\CrmFilesCompensator.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFiles.pch" ".\CrmFiles.h"
"$(INTDIR)\CrmFilesCompensator.obj"	 : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFiles.pch" ".\CrmFiles.h"


SOURCE=.\CrmFilesWorker.cpp

#"$(INTDIR)\CrmFilesWorker.obj"	"$(INTDIR)\CrmFilesWorker.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFiles.pch" ".\CrmFiles.h"
"$(INTDIR)\CrmFilesWorker.obj"	: $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmFiles.pch" ".\CrmFiles.h"


SOURCE=.\dlldatax.c

!IF  "$(CFG)" == "CrmFiles - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W4 /Gm /Zi /Od /D "_DEBUG" /D "_MERGE_PROXYSTUB" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\dlldatax.obj"	"$(INTDIR)\dlldatax.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\dlldatax.obj"	: $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CrmFiles - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "NDEBUG" /D "_ATL_DLL"  /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "NDEBUG" /D "_ATL_STATIC_REGISTRY"  /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "NDEBUG" /D "_UNICODE" /D "_ATL_DLL"  /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "NDEBUG" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"  /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmFiles - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W4 /Gm /Zi /Od /D "_DEBUG" /D "_MERGE_PROXYSTUB" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmFiles.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmFiles.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

