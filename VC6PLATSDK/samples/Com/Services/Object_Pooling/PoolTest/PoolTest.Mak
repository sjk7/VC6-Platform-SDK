!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on PoolTest.dsp
!IF "$(CFG)" == ""
CFG=PoolTest - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to PoolTest - Win32 Unicode Debug.
!ENDIF

!IF "$(CFG)" != "PoolTest - Win32 Unicode Release MinSize" && "$(CFG)" != "PoolTest - Win32 Unicode Release MinDependency" && "$(CFG)" != "PoolTest - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PoolTest.mak" CFG="PoolTest - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PoolTest - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "PoolTest - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "PoolTest - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "PoolTest - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\PoolTest.exe"

!ELSE 

ALL : "LogWriter - Win32 Unicode Release MinSize" "$(OUTDIR)\PoolTest.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LogWriter - Win32 Unicode Release MinSizeCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\PoolTest.obj"
	-@erase "$(INTDIR)\PoolTest.pch"
	-@erase "$(INTDIR)\PoolTest.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TestDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\PoolTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL"  /Fp"$(INTDIR)\PoolTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PoolTest.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PoolTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\PoolTest.pdb" /machine:$(CPU) /out:"$(OUTDIR)\PoolTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\PoolTest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestDlg.obj" \
	"$(INTDIR)\PoolTest.res" \
	".\LogWriter\ReleaseUMinSize\LogWriter.lib"

"$(OUTDIR)\PoolTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PoolTest - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\PoolTest.exe"

!ELSE 

ALL : "LogWriter - Win32 Unicode Release MinDependency" "$(OUTDIR)\PoolTest.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LogWriter - Win32 Unicode Release MinDependencyCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\PoolTest.obj"
	-@erase "$(INTDIR)\PoolTest.pch"
	-@erase "$(INTDIR)\PoolTest.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TestDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\PoolTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"  /Fp"$(INTDIR)\PoolTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PoolTest.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PoolTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\PoolTest.pdb" /machine:$(CPU) /out:"$(OUTDIR)\PoolTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\PoolTest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestDlg.obj" \
	"$(INTDIR)\PoolTest.res" \
	".\LogWriter\ReleaseUMinDependency\LogWriter.lib"

"$(OUTDIR)\PoolTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PoolTest - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\PoolTest.pch" "$(OUTDIR)\PoolTest.bsc" "$(OUTDIR)\PoolTest.exe"

!ELSE 

ALL : "LogWriter - Win32 Unicode Debug" "$(OUTDIR)\PoolTest.exe" "$(OUTDIR)\PoolTest.pch" "$(OUTDIR)\PoolTest.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"LogWriter - Win32 Unicode DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\PoolTest.obj"
	-@erase "$(INTDIR)\PoolTest.pch"
	-@erase "$(INTDIR)\PoolTest.res"
	-@erase "$(INTDIR)\PoolTest.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TestDlg.obj"
	-@erase "$(INTDIR)\TestDlg.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\PoolTest.bsc"
	-@erase "$(OUTDIR)\PoolTest.exe"
	-@erase "$(OUTDIR)\PoolTest.ilk"
	-@erase "$(OUTDIR)\PoolTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PoolTest.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PoolTest.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\PoolTest.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TestDlg.sbr"

"$(OUTDIR)\PoolTest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\PoolTest.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\PoolTest.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\PoolTest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestDlg.obj" \
	"$(INTDIR)\PoolTest.res" \
	".\LogWriter\DebugU\LogWriter.lib"

"$(OUTDIR)\PoolTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("PoolTest.dep")
!INCLUDE "PoolTest.dep"
!ELSE 
!MESSAGE Warning: cannot find "PoolTest.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "PoolTest - Win32 Unicode Release MinSize" || "$(CFG)" == "PoolTest - Win32 Unicode Release MinDependency" || "$(CFG)" == "PoolTest - Win32 Unicode Debug"
SOURCE=.\PoolTest.cpp

!IF  "$(CFG)" == "PoolTest - Win32 Unicode Release MinSize"


"$(INTDIR)\PoolTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PoolTest.pch"


!ELSEIF  "$(CFG)" == "PoolTest - Win32 Unicode Release MinDependency"


"$(INTDIR)\PoolTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PoolTest.pch"


!ELSEIF  "$(CFG)" == "PoolTest - Win32 Unicode Debug"


"$(INTDIR)\PoolTest.obj"	"$(INTDIR)\PoolTest.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\PoolTest.idl
SOURCE=.\PoolTest.rc

"$(INTDIR)\PoolTest.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "PoolTest - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL"  /Fp"$(INTDIR)\PoolTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\PoolTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "PoolTest - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"  /Fp"$(INTDIR)\PoolTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\PoolTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "PoolTest - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\PoolTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\PoolTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TestDlg.cpp

!IF  "$(CFG)" == "PoolTest - Win32 Unicode Release MinSize"


"$(INTDIR)\TestDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PoolTest.pch"


!ELSEIF  "$(CFG)" == "PoolTest - Win32 Unicode Release MinDependency"


"$(INTDIR)\TestDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PoolTest.pch"


!ELSEIF  "$(CFG)" == "PoolTest - Win32 Unicode Debug"


"$(INTDIR)\TestDlg.obj"	"$(INTDIR)\TestDlg.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

!IF  "$(CFG)" == "PoolTest - Win32 Unicode Release MinSize"

"LogWriter - Win32 Unicode Release MinSize" : 
   cd ".\LogWriter"
   $(MAKE) /$(MAKEFLAGS) /F .\LogWriter.mak CFG="LogWriter - Win32 Unicode Release MinSize" 
   cd ".."

"LogWriter - Win32 Unicode Release MinSizeCLEAN" : 
   cd ".\LogWriter"
   $(MAKE) /$(MAKEFLAGS) /F .\LogWriter.mak CFG="LogWriter - Win32 Unicode Release MinSize" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "PoolTest - Win32 Unicode Release MinDependency"

"LogWriter - Win32 Unicode Release MinDependency" : 
   cd ".\LogWriter"
   $(MAKE) /$(MAKEFLAGS) /F .\LogWriter.mak CFG="LogWriter - Win32 Unicode Release MinDependency" 
   cd ".."

"LogWriter - Win32 Unicode Release MinDependencyCLEAN" : 
   cd ".\LogWriter"
   $(MAKE) /$(MAKEFLAGS) /F .\LogWriter.mak CFG="LogWriter - Win32 Unicode Release MinDependency" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "PoolTest - Win32 Unicode Debug"

"LogWriter - Win32 Unicode Debug" : 
   cd ".\LogWriter"
   $(MAKE) /$(MAKEFLAGS) /F .\LogWriter.mak CFG="LogWriter - Win32 Unicode Debug" 
   cd ".."

"LogWriter - Win32 Unicode DebugCLEAN" : 
   cd ".\LogWriter"
   $(MAKE) /$(MAKEFLAGS) /F .\LogWriter.mak CFG="LogWriter - Win32 Unicode Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 


!ENDIF 

