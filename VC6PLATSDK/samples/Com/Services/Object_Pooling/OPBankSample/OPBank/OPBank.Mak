# Microsoft Developer Studio Generated NMAKE File, Based on OPBank.dsp
!IF "$(CFG)" == ""
CFG=OPBank - Win32 Debug
!MESSAGE No configuration specified. Defaulting to OPBank - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "OPBank - Win32 Debug" && "$(CFG)" != "OPBank - Win32 Unicode Debug" && "$(CFG)" != "OPBank - Win32 Release MinSize" && "$(CFG)" != "OPBank - Win32 Release MinDependency" && "$(CFG)" != "OPBank - Win32 Unicode Release MinSize" && "$(CFG)" != "OPBank - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OPBank.mak" CFG="OPBank - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OPBank - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "OPBank - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "OPBank - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "OPBank - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "OPBank - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "OPBank - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OPBank - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\OPBank.exe" ".\OPBank_i.c" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\bankdlg.obj"
	-@erase "$(INTDIR)\bankthrds.obj"
	-@erase "$(INTDIR)\Linkable.obj"
	-@erase "$(INTDIR)\OPBank.obj"
	-@erase "$(INTDIR)\OPBank.pch"
	-@erase "$(INTDIR)\OPBank.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OPBank.exe"
	-@erase "$(OUTDIR)\OPBank.ilk"
	-@erase "$(OUTDIR)\OPBank.pdb"
	-@erase ".\OPBank.h"
	-@erase ".\OPBank.tlb"
	-@erase ".\OPBank_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\OPBank.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OPBank.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OPBank.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\OPBank.pdb" /debug /machine:$(mach_type) /out:"$(OUTDIR)\OPBank.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\bankdlg.obj" \
	"$(INTDIR)\bankthrds.obj" \
	"$(INTDIR)\Linkable.obj" \
	"$(INTDIR)\OPBank.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OPBank.res"

"$(OUTDIR)\OPBank.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\OPBank.exe
InputPath=.\Debug\OPBank.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	rem "$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "OPBank - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\OPBank.exe" ".\OPBank.tlb" ".\OPBank.h" ".\OPBank_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\bankdlg.obj"
	-@erase "$(INTDIR)\bankthrds.obj"
	-@erase "$(INTDIR)\Linkable.obj"
	-@erase "$(INTDIR)\OPBank.obj"
	-@erase "$(INTDIR)\OPBank.pch"
	-@erase "$(INTDIR)\OPBank.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OPBank.exe"
	-@erase "$(OUTDIR)\OPBank.ilk"
	-@erase "$(OUTDIR)\OPBank.pdb"
	-@erase ".\OPBank.h"
	-@erase ".\OPBank.tlb"
	-@erase ".\OPBank_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\OPBank.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OPBank.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OPBank.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\OPBank.pdb" /debug /machine:$(mach_type) /out:"$(OUTDIR)\OPBank.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\bankdlg.obj" \
	"$(INTDIR)\bankthrds.obj" \
	"$(INTDIR)\Linkable.obj" \
	"$(INTDIR)\OPBank.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OPBank.res"

"$(OUTDIR)\OPBank.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\OPBank.exe
InputPath=.\DebugU\OPBank.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "OPBank - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\OPBank.exe" ".\OPBank_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\bankdlg.obj"
	-@erase "$(INTDIR)\bankthrds.obj"
	-@erase "$(INTDIR)\Linkable.obj"
	-@erase "$(INTDIR)\OPBank.obj"
	-@erase "$(INTDIR)\OPBank.pch"
	-@erase "$(INTDIR)\OPBank.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OPBank.exe"
	-@erase ".\OPBank.h"
	-@erase ".\OPBank.tlb"
	-@erase ".\OPBank_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_UNICODE" /Fp"$(INTDIR)\OPBank.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OPBank.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OPBank.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\OPBank.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\OPBank.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bankdlg.obj" \
	"$(INTDIR)\bankthrds.obj" \
	"$(INTDIR)\Linkable.obj" \
	"$(INTDIR)\OPBank.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OPBank.res"

"$(OUTDIR)\OPBank.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\OPBank.exe
InputPath=.\ReleaseMinSize\OPBank.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	rem "$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "OPBank - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\OPBank.exe" ".\OPBank_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\bankdlg.obj"
	-@erase "$(INTDIR)\bankthrds.obj"
	-@erase "$(INTDIR)\Linkable.obj"
	-@erase "$(INTDIR)\OPBank.obj"
	-@erase "$(INTDIR)\OPBank.pch"
	-@erase "$(INTDIR)\OPBank.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OPBank.exe"
	-@erase ".\OPBank.h"
	-@erase ".\OPBank.tlb"
	-@erase ".\OPBank_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_UNICODE" /Fp"$(INTDIR)\OPBank.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OPBank.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OPBank.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\OPBank.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\OPBank.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bankdlg.obj" \
	"$(INTDIR)\bankthrds.obj" \
	"$(INTDIR)\Linkable.obj" \
	"$(INTDIR)\OPBank.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OPBank.res"

"$(OUTDIR)\OPBank.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\OPBank.exe
InputPath=.\ReleaseMinDependency\OPBank.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "OPBank - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\OPBank.exe" ".\OPBank_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\bankdlg.obj"
	-@erase "$(INTDIR)\bankthrds.obj"
	-@erase "$(INTDIR)\Linkable.obj"
	-@erase "$(INTDIR)\OPBank.obj"
	-@erase "$(INTDIR)\OPBank.pch"
	-@erase "$(INTDIR)\OPBank.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OPBank.exe"
	-@erase ".\OPBank.h"
	-@erase ".\OPBank.tlb"
	-@erase ".\OPBank_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\OPBank.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OPBank.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OPBank.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\OPBank.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\OPBank.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bankdlg.obj" \
	"$(INTDIR)\bankthrds.obj" \
	"$(INTDIR)\Linkable.obj" \
	"$(INTDIR)\OPBank.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OPBank.res"

"$(OUTDIR)\OPBank.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\OPBank.exe
InputPath=.\ReleaseUMinSize\OPBank.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "OPBank - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\OPBank.exe" ".\OPBank_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\bankdlg.obj"
	-@erase "$(INTDIR)\bankthrds.obj"
	-@erase "$(INTDIR)\Linkable.obj"
	-@erase "$(INTDIR)\OPBank.obj"
	-@erase "$(INTDIR)\OPBank.pch"
	-@erase "$(INTDIR)\OPBank.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OPBank.exe"
	-@erase ".\OPBank.h"
	-@erase ".\OPBank.tlb"
	-@erase ".\OPBank_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\OPBank.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OPBank.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OPBank.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\OPBank.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\OPBank.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bankdlg.obj" \
	"$(INTDIR)\bankthrds.obj" \
	"$(INTDIR)\Linkable.obj" \
	"$(INTDIR)\OPBank.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OPBank.res"

"$(OUTDIR)\OPBank.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\OPBank.exe
InputPath=.\ReleaseUMinDependency\OPBank.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ENDIF 

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

MTL_PROJ=

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("OPBank.dep")
!INCLUDE "OPBank.dep"
!ELSE 
!MESSAGE Warning: cannot find "OPBank.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OPBank - Win32 Debug" || "$(CFG)" == "OPBank - Win32 Unicode Debug" || "$(CFG)" == "OPBank - Win32 Release MinSize" || "$(CFG)" == "OPBank - Win32 Release MinDependency" || "$(CFG)" == "OPBank - Win32 Unicode Release MinSize" || "$(CFG)" == "OPBank - Win32 Unicode Release MinDependency"
SOURCE=.\bankdlg.cpp

"$(INTDIR)\bankdlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OPBank.pch"


SOURCE=.\bankthrds.cpp

"$(INTDIR)\bankthrds.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OPBank.pch"


SOURCE=.\Linkable.cpp

"$(INTDIR)\Linkable.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OPBank.pch"


SOURCE=.\OPBank.cpp

"$(INTDIR)\OPBank.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OPBank.pch" ".\OPBank.h"


SOURCE=.\OPBank.idl
MTL_SWITCHES=/tlb ".\OPBank.tlb" /h "OPBank.h" /iid "OPBank_i.c" /Oicf 

".\OPBank.tlb"	".\OPBank.h"	".\OPBank_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\OPBank.rc

"$(INTDIR)\OPBank.res" : $(SOURCE) "$(INTDIR)" ".\OPBank.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "OPBank - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\OPBank.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OPBank.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OPBank - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\OPBank.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OPBank.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OPBank - Win32 Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_UNICODE" /Fp"$(INTDIR)\OPBank.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OPBank.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OPBank - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_UNICODE" /Fp"$(INTDIR)\OPBank.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OPBank.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OPBank - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\OPBank.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OPBank.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OPBank - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\OPBank.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OPBank.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

