
# Microsoft Developer Studio Generated NMAKE File, Based on ComSpy.dsp
!IF "$(CFG)" == ""
CFG=ComSpy - Win64 Unicode Debug
!MESSAGE No configuration specified. Defaulting to ComSpy - Win64 Unicode Debug.
!ENDIF 

!IF "$(CFG)" != "ComSpy - Win64 Unicode Release" && "$(CFG)" != "ComSpy - Win64 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComSpy64.mak" CFG="ComSpy - Win64 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComSpy - Win64 Unicode Release" (based on "Win64 (IA64) Application")
!MESSAGE "ComSpy - Win64 Unicode Debug" (based on "Win64 (IA64) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ComSpy - Win64 Unicode Release"

OUTDIR=.\..\ReleaseU\IA64
INTDIR=.\ReleaseU\IA64
# Begin Custom Macros
OutDir=.\..\ReleaseU\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : ".\ComSpy_i.c" ".\ComSpy.tlb" ".\ComSpy.h" "$(OUTDIR)\ComSpy.exe" 

!ELSE 

ALL : "ComSpyCtl - Win64 Unicode Release" "ComSpyAudit - Win64 Unicode Release" ".\ComSpy_i.c" ".\ComSpy.tlb" ".\ComSpy.h" "$(OUTDIR)\ComSpy.exe" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ComSpyAudit - Win64 Unicode ReleaseCLEAN" "ComSpyCtl - Win64 Unicode ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ComSpy.obj"
	-@erase "$(INTDIR)\ComSpy.pch"
	-@erase "$(INTDIR)\ComSpy.res"
	-@erase "$(INTDIR)\SpyCon.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ComSpy.exe"
	-@erase "ComSpy.h"
	-@erase "ComSpy.tlb"
	-@erase "ComSpy_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ComSpy.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win64 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpy.res" /i "..\idl\ps_win64" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSpy.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ComSpy.pdb" /machine:IA64 /out:"$(OUTDIR)\ComSpy.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ComSpy.obj" \
	"$(INTDIR)\SpyCon.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ComSpy.res" \
	"$(OUTDIR)\ComSpyAudit.lib" \
	"$(OUTDIR)\ComSpyCtl.lib"

"$(OUTDIR)\ComSpy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\ReleaseU\IA64
TargetPath=.\..\ReleaseU\IA64\ComSpy.exe
InputPath=.\..\ReleaseU\IA64\ComSpy.exe
SOURCE="$(InputPath)"

!ELSEIF  "$(CFG)" == "ComSpy - Win64 Unicode Debug"

OUTDIR=.\..\DebugU\IA64
INTDIR=.\DebugU\IA64
# Begin Custom Macros
OutDir=.\..\DebugU\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

#ALL : "$(OUTDIR)\ComSpy.exe" "$(OUTDIR)\ComSpy.bsc" 
ALL : "$(OUTDIR)\ComSpy.exe" 

!ELSE 

#ALL : "ComSpyCtl - Win64 Unicode Debug" "ComSpyAudit - Win64 Unicode Debug" "$(OUTDIR)\ComSpy.exe" "$(OUTDIR)\ComSpy.bsc" 
ALL : "ComSpyCtl - Win64 Unicode Debug" "ComSpyAudit - Win64 Unicode Debug" "$(OUTDIR)\ComSpy.exe" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ComSpyAudit - Win64 Unicode DebugCLEAN" "ComSpyCtl - Win64 Unicode DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ComSpy.obj"
	-@erase "$(INTDIR)\ComSpy.pch"
	-@erase "$(INTDIR)\ComSpy.res"
	-@erase "$(INTDIR)\ComSpy.sbr"
	-@erase "$(INTDIR)\SpyCon.obj"
	-@erase "$(INTDIR)\SpyCon.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ComSpy.bsc"
	-@erase "$(OUTDIR)\ComSpy.exe"
	-@erase "$(OUTDIR)\ComSpy.ilk"
	-@erase "$(OUTDIR)\ComSpy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ComSpy.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win64 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpy.res" /i "..\idl\ps_win64" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSpy.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\ComSpy.sbr" \
#	"$(INTDIR)\SpyCon.sbr" \
#	"$(INTDIR)\StdAfx.sbr"

#"$(OUTDIR)\ComSpy.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib svcguid.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ComSpy.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\ComSpy.exe"  
LINK32_OBJS= \
	"$(INTDIR)\ComSpy.obj" \
	"$(INTDIR)\SpyCon.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ComSpy.res" \
	"$(OUTDIR)\ComSpyAudit.lib" \
	"$(OUTDIR)\ComSpyCtl.lib"

"$(OUTDIR)\ComSpy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\DebugU\IA64
TargetPath=.\..\DebugU\IA64\ComSpy.exe
InputPath=.\..\DebugU\IA64\ComSpy.exe
SOURCE="$(InputPath)"

!ENDIF 


!IF "$(CFG)" == "ComSpy - Win64 Unicode Release" || "$(CFG)" == "ComSpy - Win64 Unicode Debug"
SOURCE=.\ComSpy.cpp

!IF  "$(CFG)" == "ComSpy - Win64 Unicode Release"


"$(INTDIR)\ComSpy.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpy.pch"


!ELSEIF  "$(CFG)" == "ComSpy - Win64 Unicode Debug"


#"$(INTDIR)\ComSpy.obj"	"$(INTDIR)\ComSpy.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpy.pch" ".\ComSpy.h" ".\ComSpy_i.c"
"$(INTDIR)\ComSpy.obj"	: $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpy.pch" ".\ComSpy.h" ".\ComSpy_i.c"


!ENDIF 

SOURCE=.\ComSpy.idl

!IF  "$(CFG)" == "ComSpy - Win64 Unicode Release"

InputPath=.\ComSpy.idl

".\ComSpy.h"	".\ComSpy_i.c"	".\ComSpy.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\ComSpy.h" /tlb ".\ComSpy.tlb" /iid   ".\ComSpy_i.c"        "ComSpy.idl"
<< 
	

!ELSEIF  "$(CFG)" == "ComSpy - Win64 Unicode Debug"

InputPath=.\ComSpy.idl

".\ComSpy.h"	".\ComSpy_i.c"	".\ComSpy.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\ComSpy.h" /tlb ".\ComSpy.tlb" /iid   ".\ComSpy_i.c"        "ComSpy.idl"
<< 
	

!ENDIF 

SOURCE=.\ComSpy.rc

"$(INTDIR)\ComSpy.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SpyCon.cpp

!IF  "$(CFG)" == "ComSpy - Win64 Unicode Release"


"$(INTDIR)\SpyCon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpy.pch"


!ELSEIF  "$(CFG)" == "ComSpy - Win64 Unicode Debug"


#"$(INTDIR)\SpyCon.obj"	"$(INTDIR)\SpyCon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpy.pch" ".\ComSpy.h"
"$(INTDIR)\SpyCon.obj"	: $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpy.pch" ".\ComSpy.h"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ComSpy - Win64 Unicode Release"

CPP_SWITCHES=/nologo /ML /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ComSpy.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ComSpy.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSpy - Win64 Unicode Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Wp64 /Gm /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ComSpy.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ComSpy.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ComSpy.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "ComSpy - Win64 Unicode Release"

"ComSpyAudit - Win64 Unicode Release" : 
   cd ".\..\ComSpyAudit"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyAudit64.mak CFG="ComSpyAudit - Win64 Unicode Release" 
   cd "..\ComSpy"

"ComSpyAudit - Win64 Unicode ReleaseCLEAN" : 
   cd ".\..\ComSpyAudit"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyAudit64.mak CFG="ComSpyAudit - Win64 Unicode Release" RECURSE=1 CLEAN 
   cd "..\ComSpy"

!ELSEIF  "$(CFG)" == "ComSpy - Win64 Unicode Debug"

"ComSpyAudit - Win64 Unicode Debug" : 
   cd ".\..\ComSpyAudit"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyAudit64.mak CFG="ComSpyAudit - Win64 Unicode Debug" 
   cd "..\ComSpy"

"ComSpyAudit - Win64 Unicode DebugCLEAN" : 
   cd ".\..\ComSpyAudit"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyAudit64.mak CFG="ComSpyAudit - Win64 Unicode Debug" RECURSE=1 CLEAN 
   cd "..\ComSpy"

!ENDIF 

!IF  "$(CFG)" == "ComSpy - Win64 Unicode Release"

"ComSpyCtl - Win64 Unicode Release" : 
   cd ".\..\ComSpyCtl"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyCtl64.mak CFG="ComSpyCtl - Win64 Unicode Release" 
   cd "..\ComSpy"

"ComSpyCtl - Win64 Unicode ReleaseCLEAN" : 
   cd ".\..\ComSpyCtl"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyCtl64.mak CFG="ComSpyCtl - Win64 Unicode Release" RECURSE=1 CLEAN 
   cd "..\ComSpy"

!ELSEIF  "$(CFG)" == "ComSpy - Win64 Unicode Debug"

"ComSpyCtl - Win64 Unicode Debug" : 
   cd ".\..\ComSpyCtl"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyCtl64.mak CFG="ComSpyCtl - Win64 Unicode Debug" 
   cd "..\ComSpy"

"ComSpyCtl - Win64 Unicode DebugCLEAN" : 
   cd ".\..\ComSpyCtl"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyCtl64.mak CFG="ComSpyCtl - Win64 Unicode Debug" RECURSE=1 CLEAN 
   cd "..\ComSpy"

!ENDIF 

!IF  "$(CFG)" == "ComSpy - Win64 Unicode Release"

!ELSEIF  "$(CFG)" == "ComSpy - Win64 Unicode Debug"

!ENDIF 

!IF  "$(CFG)" == "ComSpy - Win64 Unicode Release"

!ELSEIF  "$(CFG)" == "ComSpy - Win64 Unicode Debug"

!ENDIF 


!ENDIF 
