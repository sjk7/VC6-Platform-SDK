
# Microsoft Developer Studio Generated NMAKE File, Based on FullSvr.dsp
!IF "$(CFG)" == ""
CFG=FullSvr - Win64 Debug
!MESSAGE No configuration specified. Defaulting to FullSvr - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "FullSvr - Win64 Debug" && "$(CFG)" != "FullSvr - Win64 Unicode Debug" && "$(CFG)" != "FullSvr - Win64 Release MinSize" && "$(CFG)" != "FullSvr - Win64 Release MinDependency" && "$(CFG)" != "FullSvr - Win64 Unicode Release MinSize" && "$(CFG)" != "FullSvr - Win64 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FullSvr64.mak" CFG="FullSvr - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FullSvr - Win64 Debug" (based on "Win64 (IA64) Application")
!MESSAGE "FullSvr - Win64 Unicode Debug" (based on "Win64 (IA64) Application")
!MESSAGE "FullSvr - Win64 Release MinSize" (based on "Win64 (IA64) Application")
!MESSAGE "FullSvr - Win64 Release MinDependency" (based on "Win64 (IA64) Application")
!MESSAGE "FullSvr - Win64 Unicode Release MinSize" (based on "Win64 (IA64) Application")
!MESSAGE "FullSvr - Win64 Unicode Release MinDependency" (based on "Win64 (IA64) Application")
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

!IF  "$(CFG)" == "FullSvr - Win64 Debug"

OUTDIR=.\..\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\..\Debug\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ELSE 

ALL : "FullSrvps - Win64 Debug" "idl - Win64 Debug" "$(OUTDIR)\FullSvr.exe" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"idl - Win64 DebugCLEAN" "FullSrvps - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\FullSvr.exe"
	-@erase "$(OUTDIR)\FullSvr.ilk"
	-@erase "$(OUTDIR)\FullSvr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /i "..\idl\ps_win64" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\FullSvr.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\FullSvr.exe"  
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res" \
	"$(OUTDIR)\FullSrvps.lib"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\Debug\IA64
TargetPath=.\..\Debug\IA64\FullSvr.exe
InputPath=.\..\Debug\IA64\FullSvr.exe
SOURCE="$(InputPath)"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Debug"

OUTDIR=.\..\DebugU\IA64
INTDIR=.\DebugU\IA64
# Begin Custom Macros
OutDir=.\..\DebugU\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ELSE 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\FullSvr.exe"
	-@erase "$(OUTDIR)\FullSvr.ilk"
	-@erase "$(OUTDIR)\FullSvr.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /i "..\idl\ps_win64" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\FullSvr.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\FullSvr.exe"  
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\DebugU\IA64
TargetPath=.\..\DebugU\IA64\FullSvr.exe
InputPath=.\..\DebugU\IA64\FullSvr.exe
SOURCE="$(InputPath)"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Release MinSize"

OUTDIR=.\..\Release\IA64
INTDIR=.\ReleaseMinSize\IA64
# Begin Custom Macros
OutDir=.\..\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ELSE 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FullSvr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /i "..\idl\ps_win64" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\FullSvr.pdb" /machine:IA64 /out:"$(OUTDIR)\FullSvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\Release\IA64
TargetPath=.\..\Release\IA64\FullSvr.exe
InputPath=.\..\Release\IA64\FullSvr.exe
SOURCE="$(InputPath)"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Release MinDependency"

OUTDIR=.\..\Release\IA64
INTDIR=.\ReleaseMinDependency\IA64
# Begin Custom Macros
OutDir=.\..\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ELSE 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FullSvr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /i "..\idl\ps_win64" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\FullSvr.pdb" /machine:IA64 /out:"$(OUTDIR)\FullSvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\Release\IA64
TargetPath=.\..\Release\IA64\FullSvr.exe
InputPath=.\..\Release\IA64\FullSvr.exe
SOURCE="$(InputPath)"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Release MinSize"

OUTDIR=.\..\Release\IA64
INTDIR=.\ReleaseUMinSize\IA64
# Begin Custom Macros
OutDir=.\..\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ELSE 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FullSvr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /i "..\idl\ps_win64" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\FullSvr.pdb" /machine:IA64 /out:"$(OUTDIR)\FullSvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\Release\IA64
TargetPath=.\..\Release\IA64\FullSvr.exe
InputPath=.\..\Release\IA64\FullSvr.exe
SOURCE="$(InputPath)"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Release MinDependency"

OUTDIR=.\..\Release\IA64
INTDIR=.\ReleaseUMinDependency\IA64
# Begin Custom Macros
OutDir=.\..\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ELSE 

ALL : "$(OUTDIR)\FullSvr.exe" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\FullServ.obj"
	-@erase "$(INTDIR)\FullSvr.obj"
	-@erase "$(INTDIR)\FullSvr.pch"
	-@erase "$(INTDIR)\FullSvr.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FullSvr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\FullSvr.res" /i "..\idl\ps_win64" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FullSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\FullSvr.pdb" /machine:IA64 /out:"$(OUTDIR)\FullSvr.exe" 
LINK32_OBJS= \
	"$(INTDIR)\FullServ.obj" \
	"$(INTDIR)\FullSvr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\FullSvr.res"

"$(OUTDIR)\FullSvr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\Release\IA64
TargetPath=.\..\Release\IA64\FullSvr.exe
InputPath=.\..\Release\IA64\FullSvr.exe
SOURCE="$(InputPath)"

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
!IF EXISTS("FullSvr.dep")
!INCLUDE "FullSvr.dep"
!ELSE 
!MESSAGE Warning: cannot find "FullSvr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FullSvr - Win64 Debug" || "$(CFG)" == "FullSvr - Win64 Unicode Debug" || "$(CFG)" == "FullSvr - Win64 Release MinSize" || "$(CFG)" == "FullSvr - Win64 Release MinDependency" || "$(CFG)" == "FullSvr - Win64 Unicode Release MinSize" || "$(CFG)" == "FullSvr - Win64 Unicode Release MinDependency"
SOURCE=.\FullServ.cpp

"$(INTDIR)\FullServ.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


SOURCE=.\FullSvr.cpp

"$(INTDIR)\FullSvr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\FullSvr.pch"


SOURCE=.\FullSvr.rc

"$(INTDIR)\FullSvr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "FullSvr - Win64 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Wp64 /Gm /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Wp64 /Gm /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win64 Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win64 Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\FullSvr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\FullSvr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "FullSvr - Win64 Debug"

"idl - Win64 Debug" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" 
   cd "..\FullSvr"

"idl - Win64 DebugCLEAN" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\FullSvr"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Debug"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Release MinSize"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Release MinDependency"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Release MinDependency"

!ENDIF 

!IF  "$(CFG)" == "FullSvr - Win64 Debug"

"FullSrvps - Win64 Debug" : 
   cd ".\..\FullSrvps"
   $(MAKE) /$(MAKEFLAGS) /F .\FullSrvps64.mak CFG="FullSrvps - Win64 Debug" 
   cd "..\FullSvr"

"FullSrvps - Win64 DebugCLEAN" : 
   cd ".\..\FullSrvps"
   $(MAKE) /$(MAKEFLAGS) /F .\FullSrvps64.mak CFG="FullSrvps - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\FullSvr"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Debug"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Release MinSize"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Release MinDependency"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "FullSvr - Win64 Unicode Release MinDependency"

!ENDIF 


!ENDIF 
