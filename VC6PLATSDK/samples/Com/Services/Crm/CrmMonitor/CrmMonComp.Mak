!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on CrmMonComp.dsp
!IF "$(CFG)" == ""
CFG=CrmMonComp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CrmMonComp - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "CrmMonComp - Win32 Unicode Debug" && "$(CFG)" != "CrmMonComp - Win32 Release MinSize" && "$(CFG)" != "CrmMonComp - Win32 Release MinDependency" && "$(CFG)" != "CrmMonComp - Win32 Unicode Release MinSize" && "$(CFG)" != "CrmMonComp - Win32 Unicode Release MinDependency" && "$(CFG)" != "CrmMonComp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CrmMonComp.mak" CFG="CrmMonComp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CrmMonComp - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmMonComp - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmMonComp - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmMonComp - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmMonComp - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CrmMonComp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CrmMonComp - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\CrmMonComp.dll" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmMonComp.obj"
	-@erase "$(INTDIR)\CrmMonComp.pch"
	-@erase "$(INTDIR)\CrmMonComp.res"
	-@erase "$(INTDIR)\CrmMonCompObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CrmMonComp.dll"
	-@erase "$(OUTDIR)\CrmMonComp.exp"
	-@erase "$(OUTDIR)\CrmMonComp.ilk"
	-@erase "$(OUTDIR)\CrmMonComp.lib"
	-@erase "$(OUTDIR)\CrmMonComp.pdb"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CrmMonComp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmMonComp.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmMonComp.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\CrmMonComp.pdb" /debug /machine:$(CPU) /def:".\CrmMonComp.def" /out:"$(OUTDIR)\CrmMonComp.dll" /implib:"$(OUTDIR)\CrmMonComp.lib" /pdbtype:sept 
DEF_FILE= \
	".\CrmMonComp.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmMonComp.obj" \
	"$(INTDIR)\CrmMonCompObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmMonComp.res"

"$(OUTDIR)\CrmMonComp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\CrmMonComp.dll
InputPath=.\DebugU\CrmMonComp.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : ".\CrmMonComp_i.c" ".\CrmMonComp.tlb" ".\CrmMonComp.h" "$(OUTDIR)\CrmMonComp.dll" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmMonComp.obj"
	-@erase "$(INTDIR)\CrmMonComp.pch"
	-@erase "$(INTDIR)\CrmMonComp.res"
	-@erase "$(INTDIR)\CrmMonCompObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmMonComp.dll"
	-@erase "$(OUTDIR)\CrmMonComp.exp"
	-@erase "$(OUTDIR)\CrmMonComp.lib"
	-@erase ".\CrmMonComp.h"
	-@erase ".\CrmMonComp.tlb"
	-@erase ".\CrmMonComp_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmMonComp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmMonComp.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmMonComp.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmMonComp.pdb" /machine:$(CPU) /def:".\CrmMonComp.def" /out:"$(OUTDIR)\CrmMonComp.dll" /implib:"$(OUTDIR)\CrmMonComp.lib" 
DEF_FILE= \
	".\CrmMonComp.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmMonComp.obj" \
	"$(INTDIR)\CrmMonCompObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmMonComp.res"

"$(OUTDIR)\CrmMonComp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\CrmMonComp.dll
InputPath=.\ReleaseMinSize\CrmMonComp.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\CrmMonComp_i.c" ".\CrmMonComp.tlb" ".\CrmMonComp.h" "$(OUTDIR)\CrmMonComp.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmMonComp.obj"
	-@erase "$(INTDIR)\CrmMonComp.pch"
	-@erase "$(INTDIR)\CrmMonComp.res"
	-@erase "$(INTDIR)\CrmMonCompObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmMonComp.dll"
	-@erase "$(OUTDIR)\CrmMonComp.exp"
	-@erase "$(OUTDIR)\CrmMonComp.lib"
	-@erase ".\CrmMonComp.h"
	-@erase ".\CrmMonComp.tlb"
	-@erase ".\CrmMonComp_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmMonComp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmMonComp.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmMonComp.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmMonComp.pdb" /machine:$(CPU) /def:".\CrmMonComp.def" /out:"$(OUTDIR)\CrmMonComp.dll" /implib:"$(OUTDIR)\CrmMonComp.lib" 
DEF_FILE= \
	".\CrmMonComp.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmMonComp.obj" \
	"$(INTDIR)\CrmMonCompObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmMonComp.res"

"$(OUTDIR)\CrmMonComp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\CrmMonComp.dll
InputPath=.\ReleaseMinDependency\CrmMonComp.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : ".\CrmMonComp_i.c" ".\CrmMonComp.tlb" ".\CrmMonComp.h" "$(OUTDIR)\CrmMonComp.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmMonComp.obj"
	-@erase "$(INTDIR)\CrmMonComp.pch"
	-@erase "$(INTDIR)\CrmMonComp.res"
	-@erase "$(INTDIR)\CrmMonCompObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmMonComp.dll"
	-@erase "$(OUTDIR)\CrmMonComp.exp"
	-@erase "$(OUTDIR)\CrmMonComp.lib"
	-@erase ".\CrmMonComp.h"
	-@erase ".\CrmMonComp.tlb"
	-@erase ".\CrmMonComp_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmMonComp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmMonComp.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmMonComp.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmMonComp.pdb" /machine:$(CPU) /def:".\CrmMonComp.def" /out:"$(OUTDIR)\CrmMonComp.dll" /implib:"$(OUTDIR)\CrmMonComp.lib" 
DEF_FILE= \
	".\CrmMonComp.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmMonComp.obj" \
	"$(INTDIR)\CrmMonCompObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmMonComp.res"

"$(OUTDIR)\CrmMonComp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\CrmMonComp.dll
InputPath=.\ReleaseUMinSize\CrmMonComp.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : ".\CrmMonComp_i.c" ".\CrmMonComp.tlb" ".\CrmMonComp.h" "$(OUTDIR)\CrmMonComp.dll" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmMonComp.obj"
	-@erase "$(INTDIR)\CrmMonComp.pch"
	-@erase "$(INTDIR)\CrmMonComp.res"
	-@erase "$(INTDIR)\CrmMonCompObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CrmMonComp.dll"
	-@erase "$(OUTDIR)\CrmMonComp.exp"
	-@erase "$(OUTDIR)\CrmMonComp.lib"
	-@erase ".\CrmMonComp.h"
	-@erase ".\CrmMonComp.tlb"
	-@erase ".\CrmMonComp_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmMonComp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmMonComp.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmMonComp.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\CrmMonComp.pdb" /machine:$(CPU) /def:".\CrmMonComp.def" /out:"$(OUTDIR)\CrmMonComp.dll" /implib:"$(OUTDIR)\CrmMonComp.lib" 
DEF_FILE= \
	".\CrmMonComp.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmMonComp.obj" \
	"$(INTDIR)\CrmMonCompObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmMonComp.res"

"$(OUTDIR)\CrmMonComp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\CrmMonComp.dll
InputPath=.\ReleaseUMinDependency\CrmMonComp.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

#ALL : ".\dlldata.c" ".\CrmMonComp_p.c" ".\CrmMonComp_i.c" ".\CrmMonComp.tlb" ".\CrmMonComp.h" "$(OUTDIR)\CrmMonComp.dll" "$(OUTDIR)\CrmMonComp.pch" "$(OUTDIR)\CrmMonComp.bsc" ".\Debug\regsvr32.trg"
ALL : ".\dlldata.c" ".\CrmMonComp_p.c" ".\CrmMonComp_i.c" ".\CrmMonComp.tlb" ".\CrmMonComp.h" "$(OUTDIR)\CrmMonComp.dll" "$(OUTDIR)\CrmMonComp.pch" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CrmMonComp.obj"
	-@erase "$(INTDIR)\CrmMonComp.pch"
	-@erase "$(INTDIR)\CrmMonComp.res"
	-@erase "$(INTDIR)\CrmMonComp.sbr"
	-@erase "$(INTDIR)\CrmMonCompObj.obj"
	-@erase "$(INTDIR)\CrmMonCompObj.sbr"
	-@erase "$(INTDIR)\dlldatax.obj"
	-@erase "$(INTDIR)\dlldatax.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CrmMonComp.bsc"
	-@erase "$(OUTDIR)\CrmMonComp.dll"
	-@erase "$(OUTDIR)\CrmMonComp.exp"
	-@erase "$(OUTDIR)\CrmMonComp.ilk"
	-@erase "$(OUTDIR)\CrmMonComp.lib"
	-@erase "$(OUTDIR)\CrmMonComp.pdb"
	-@erase ".\CrmMonComp.h"
	-@erase ".\CrmMonComp.tlb"
	-@erase ".\CrmMonComp_i.c"
	-@erase ".\Debug\regsvr32.trg"
	-@erase "CrmMonComp_p.c"
	-@erase "dlldata.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MERGE_PROXYSTUB" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CrmMonComp.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\CrmMonComp.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\CrmMonComp.sbr" \
#	"$(INTDIR)\CrmMonCompObj.sbr" \
#	"$(INTDIR)\dlldatax.sbr" \
#	"$(INTDIR)\StdAfx.sbr"

#"$(OUTDIR)\CrmMonComp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\CrmMonComp.pdb" /debug /machine:$(CPU) /def:".\CrmMonComp.def" /out:"$(OUTDIR)\CrmMonComp.dll" /implib:"$(OUTDIR)\CrmMonComp.lib" /pdbtype:sept 
DEF_FILE= \
	".\CrmMonComp.def"
LINK32_OBJS= \
	"$(INTDIR)\CrmMonComp.obj" \
	"$(INTDIR)\CrmMonCompObj.obj" \
	"$(INTDIR)\dlldatax.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\CrmMonComp.res"

"$(OUTDIR)\CrmMonComp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\CrmMonComp.dll
InputPath=.\Debug\CrmMonComp.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("CrmMonComp.dep")
!INCLUDE "CrmMonComp.dep"
!ELSE 
!MESSAGE Warning: cannot find "CrmMonComp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CrmMonComp - Win32 Unicode Debug" || "$(CFG)" == "CrmMonComp - Win32 Release MinSize" || "$(CFG)" == "CrmMonComp - Win32 Release MinDependency" || "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinSize" || "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinDependency" || "$(CFG)" == "CrmMonComp - Win32 Debug"
SOURCE=.\CrmMonComp.cpp

!IF  "$(CFG)" == "CrmMonComp - Win32 Unicode Debug"


"$(INTDIR)\CrmMonComp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmMonComp.pch" ".\CrmMonComp.h" ".\CrmMonComp_i.c"


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinSize"


"$(INTDIR)\CrmMonComp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmMonComp.pch"


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinDependency"


"$(INTDIR)\CrmMonComp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmMonComp.pch"


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinSize"


"$(INTDIR)\CrmMonComp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmMonComp.pch"


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinDependency"


"$(INTDIR)\CrmMonComp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmMonComp.pch"


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Debug"


#"$(INTDIR)\CrmMonComp.obj"	"$(INTDIR)\CrmMonComp.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\CrmMonComp.obj"	: $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CrmMonComp.idl

!IF  "$(CFG)" == "CrmMonComp - Win32 Unicode Debug"

InputPath=.\CrmMonComp.idl

".\CrmMonComp.tlb"	".\CrmMonComp.h"	".\CrmMonComp_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmMonComp.h" /iid "CrmMonComp_i.c" "CrmMonComp.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinSize"

InputPath=.\CrmMonComp.idl

".\CrmMonComp.tlb"	".\CrmMonComp.h"	".\CrmMonComp_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmMonComp.h" /iid "CrmMonComp_i.c" "CrmMonComp.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinDependency"

InputPath=.\CrmMonComp.idl

".\CrmMonComp.tlb"	".\CrmMonComp.h"	".\CrmMonComp_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmMonComp.h" /iid "CrmMonComp_i.c" "CrmMonComp.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinSize"

InputPath=.\CrmMonComp.idl

".\CrmMonComp.tlb"	".\CrmMonComp.h"	".\CrmMonComp_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmMonComp.h" /iid "CrmMonComp_i.c" "CrmMonComp.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinDependency"

InputPath=.\CrmMonComp.idl

".\CrmMonComp.tlb"	".\CrmMonComp.h"	".\CrmMonComp_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmMonComp.h" /iid "CrmMonComp_i.c" "CrmMonComp.idl"
<< 
	

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Debug"

InputPath=.\CrmMonComp.idl

".\CrmMonComp.tlb"	".\CrmMonComp.h"	".\CrmMonComp_i.c"	".\CrmMonComp_p.c"	".\dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "CrmMonComp.h" /iid "CrmMonComp_i.c" "CrmMonComp.idl"
<< 
	

!ENDIF 

SOURCE=.\CrmMonComp.rc

"$(INTDIR)\CrmMonComp.res" : $(SOURCE) "$(INTDIR)" ".\CrmMonComp.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CrmMonCompObj.cpp

!IF  "$(CFG)" == "CrmMonComp - Win32 Unicode Debug"


"$(INTDIR)\CrmMonCompObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmMonComp.pch" ".\CrmMonComp.h"


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinSize"


"$(INTDIR)\CrmMonCompObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmMonComp.pch"


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinDependency"


"$(INTDIR)\CrmMonCompObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmMonComp.pch"


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinSize"


"$(INTDIR)\CrmMonCompObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmMonComp.pch"


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinDependency"


"$(INTDIR)\CrmMonCompObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CrmMonComp.pch"


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Debug"


#"$(INTDIR)\CrmMonCompObj.obj"	"$(INTDIR)\CrmMonCompObj.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\CrmMonCompObj.obj"	: $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\dlldatax.c

!IF  "$(CFG)" == "CrmMonComp - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinDependency"

!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MERGE_PROXYSTUB" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\dlldatax.obj"	"$(INTDIR)\dlldatax.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\dlldatax.obj"	: $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CrmMonComp - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\CrmMonComp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmMonComp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmMonComp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmMonComp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmMonComp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmMonComp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\CrmMonComp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmMonComp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\CrmMonComp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CrmMonComp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CrmMonComp - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_MERGE_PROXYSTUB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CrmMonComp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CrmMonComp.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"		"$(INTDIR)\CrmMonComp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

