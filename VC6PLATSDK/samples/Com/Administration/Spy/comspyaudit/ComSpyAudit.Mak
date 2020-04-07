# Microsoft Developer Studio Generated NMAKE File, Based on ComSpyAudit.dsp
!IF "$(CFG)" == ""
CFG=ComSpyAudit - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to ComSpyAudit - Win32 Unicode Debug.
!ENDIF 

!IF "$(CFG)" != "ComSpyAudit - Win32 Unicode Release" && "$(CFG)" != "ComSpyAudit - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComSpyAudit.mak" CFG="ComSpyAudit - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComSpyAudit - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComSpyAudit - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"

OUTDIR=.\..\ReleaseU\x86
INTDIR=.\ReleaseU\x86
# Begin Custom Macros
OutDir=.\..\ReleaseU\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ComSpyAudit.dll" 

!ELSE 

ALL : "$(OUTDIR)\ComSpyAudit.dll" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ComSpyAudit.obj"
	-@erase "$(INTDIR)\ComSpyAudit.pch"
	-@erase "$(INTDIR)\ComSpyAudit.res"
	-@erase "$(INTDIR)\ComSpySqlAudit.obj"
	-@erase "$(INTDIR)\events.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ComSpyAudit.dll"
	-@erase "$(OUTDIR)\ComSpyAudit.exp"
	-@erase "$(OUTDIR)\ComSpyAudit.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /I "..\idl\ps_win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpyAudit.res" /i "..\idl\ps_win32" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSpyAudit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ComSpyAudit.pdb" /machine:$(CPU) /def:".\ComSpyAudit.def" /out:"$(OUTDIR)\ComSpyAudit.dll" /implib:"$(OUTDIR)\ComSpyAudit.lib" 
DEF_FILE= \
	".\ComSpyAudit.def"
LINK32_OBJS= \
	"$(INTDIR)\ComSpyAudit.obj" \
	"$(INTDIR)\ComSpySqlAudit.obj" \
	"$(INTDIR)\events.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ComSpyAudit.res"

"$(OUTDIR)\ComSpyAudit.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\ReleaseU\x86
TargetPath=.\..\ReleaseU\x86\ComSpyAudit.dll
InputPath=.\..\ReleaseU\x86\ComSpyAudit.dll
SOURCE="$(InputPath)"

!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"

OUTDIR=.\..\DebugU\x86
INTDIR=.\DebugU\x86
# Begin Custom Macros
OutDir=.\..\DebugU\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ComSpyAudit.dll" "$(OUTDIR)\ComSpyAudit.bsc" 

!ELSE 

ALL : "$(OUTDIR)\ComSpyAudit.dll" "$(OUTDIR)\ComSpyAudit.bsc" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ComSpyAudit.obj"
	-@erase "$(INTDIR)\ComSpyAudit.pch"
	-@erase "$(INTDIR)\ComSpyAudit.res"
	-@erase "$(INTDIR)\ComSpyAudit.sbr"
	-@erase "$(INTDIR)\ComSpySqlAudit.obj"
	-@erase "$(INTDIR)\ComSpySqlAudit.sbr"
	-@erase "$(INTDIR)\events.obj"
	-@erase "$(INTDIR)\events.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ComSpyAudit.bsc"
	-@erase "$(OUTDIR)\ComSpyAudit.dll"
	-@erase "$(OUTDIR)\ComSpyAudit.exp"
	-@erase "$(OUTDIR)\ComSpyAudit.ilk"
	-@erase "$(OUTDIR)\ComSpyAudit.lib"
	-@erase "$(OUTDIR)\ComSpyAudit.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "..\idl\ps_win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpyAudit.res" /i "..\idl\ps_win32" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSpyAudit.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ComSpyAudit.sbr" \
	"$(INTDIR)\ComSpySqlAudit.sbr" \
	"$(INTDIR)\events.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ComSpyAudit.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ComSpyAudit.pdb" /debug /machine:$(CPU) /def:".\ComSpyAudit.def" /out:"$(OUTDIR)\ComSpyAudit.dll" /implib:"$(OUTDIR)\ComSpyAudit.lib" /pdbtype:sept 
DEF_FILE= \
	".\ComSpyAudit.def"
LINK32_OBJS= \
	"$(INTDIR)\ComSpyAudit.obj" \
	"$(INTDIR)\ComSpySqlAudit.obj" \
	"$(INTDIR)\events.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ComSpyAudit.res"

"$(OUTDIR)\ComSpyAudit.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\DebugU\x86
TargetPath=.\..\DebugU\x86\ComSpyAudit.dll
InputPath=.\..\DebugU\x86\ComSpyAudit.dll
SOURCE="$(InputPath)"


!ENDIF 


!IF "$(CFG)" == "ComSpyAudit - Win32 Unicode Release" || "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"
SOURCE=.\ComSpyAudit.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"


"$(INTDIR)\ComSpyAudit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"


"$(INTDIR)\ComSpyAudit.obj"	"$(INTDIR)\ComSpyAudit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ENDIF 

SOURCE=.\ComSpySqlAudit.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"


"$(INTDIR)\ComSpySqlAudit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"


"$(INTDIR)\ComSpySqlAudit.obj"	"$(INTDIR)\ComSpySqlAudit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ENDIF 

SOURCE=.\events.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"


"$(INTDIR)\events.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"


"$(INTDIR)\events.obj"	"$(INTDIR)\events.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\idl\ps_win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ComSpyAudit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\idl\ps_win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ComSpyAudit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ComSpyAudit.rc

"$(INTDIR)\ComSpyAudit.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"

!ENDIF 

!IF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "ComSpyAudit - Win32 Unicode Debug"

!ENDIF 


!ENDIF 

