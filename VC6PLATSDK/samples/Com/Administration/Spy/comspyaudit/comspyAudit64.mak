
# Microsoft Developer Studio Generated NMAKE File, Based on ComSpyAudit.dsp
!IF "$(CFG)" == ""
CFG=ComSpyAudit - Win64 Unicode Debug
!MESSAGE No configuration specified. Defaulting to ComSpyAudit - Win64 Unicode Debug.
!ENDIF 

!IF "$(CFG)" != "ComSpyAudit - Win64 Unicode Release" && "$(CFG)" != "ComSpyAudit - Win64 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComSpyAudit64.mak" CFG="ComSpyAudit - Win64 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComSpyAudit - Win64 Unicode Release" (based on "Win64 (IA64) Dynamic-Link Library")
!MESSAGE "ComSpyAudit - Win64 Unicode Debug" (based on "Win64 (IA64) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Release"

OUTDIR=.\..\ReleaseU\IA64
INTDIR=.\ReleaseU\IA64
# Begin Custom Macros
OutDir=.\..\ReleaseU\IA64
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
CPP_PROJ=/nologo /MT /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpyAudit.res" /i "..\idl\ps_win64" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSpyAudit.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ComSpyAudit.pdb" /machine:IA64 /def:".\ComSpyAudit.def" /out:"$(OUTDIR)\ComSpyAudit.dll" /implib:"$(OUTDIR)\ComSpyAudit.lib" 
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

OutDir=.\..\ReleaseU\IA64
TargetPath=.\..\ReleaseU\IA64\ComSpyAudit.dll
InputPath=.\..\ReleaseU\IA64\ComSpyAudit.dll
SOURCE="$(InputPath)"

!ELSEIF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Debug"

OUTDIR=.\..\DebugU\IA64
INTDIR=.\DebugU\IA64
# Begin Custom Macros
OutDir=.\..\DebugU\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

#ALL : "$(OUTDIR)\ComSpyAudit.dll" "$(OUTDIR)\ComSpyAudit.bsc" 
ALL : "$(OUTDIR)\ComSpyAudit.dll"

!ELSE 

#ALL : "$(OUTDIR)\ComSpyAudit.dll" "$(OUTDIR)\ComSpyAudit.bsc" 
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
	-@erase "$(INTDIR)\ComSpyAudit.sbr"
	-@erase "$(INTDIR)\ComSpySqlAudit.obj"
	-@erase "$(INTDIR)\ComSpySqlAudit.sbr"
	-@erase "$(INTDIR)\events.obj"
	-@erase "$(INTDIR)\events.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
#	-@erase "$(OUTDIR)\ComSpyAudit.bsc"
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
CPP_PROJ=/nologo /MTd /W3 /Wp64 /Gm /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpyAudit.res" /i "..\idl\ps_win64" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSpyAudit.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\ComSpyAudit.sbr" \
#	"$(INTDIR)\ComSpySqlAudit.sbr" \
#	"$(INTDIR)\events.sbr" \
#	"$(INTDIR)\StdAfx.sbr"

#"$(OUTDIR)\ComSpyAudit.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=odbc32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ComSpyAudit.pdb" /debug /machine:IA64 /def:".\ComSpyAudit.def" /out:"$(OUTDIR)\ComSpyAudit.dll" /implib:"$(OUTDIR)\ComSpyAudit.lib"  
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

OutDir=.\..\DebugU\IA64
TargetPath=.\..\DebugU\IA64\ComSpyAudit.dll
InputPath=.\..\DebugU\IA64\ComSpyAudit.dll
SOURCE="$(InputPath)"

!ENDIF 


!IF "$(CFG)" == "ComSpyAudit - Win64 Unicode Release" || "$(CFG)" == "ComSpyAudit - Win64 Unicode Debug"
SOURCE=.\ComSpyAudit.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Release"


"$(INTDIR)\ComSpyAudit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Debug"


"$(INTDIR)\ComSpyAudit.obj"	: $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"
#"$(INTDIR)\ComSpyAudit.obj"	"$(INTDIR)\ComSpyAudit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ENDIF 

SOURCE=.\ComSpySqlAudit.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Release"


"$(INTDIR)\ComSpySqlAudit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Debug"


#"$(INTDIR)\ComSpySqlAudit.obj"	"$(INTDIR)\ComSpySqlAudit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"
"$(INTDIR)\ComSpySqlAudit.obj"	: $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ENDIF 

SOURCE=.\events.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Release"


"$(INTDIR)\events.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Debug"


#"$(INTDIR)\events.obj"	"$(INTDIR)\events.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"
"$(INTDIR)\events.obj"	: $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyAudit.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /Wp64 /O1 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ComSpyAudit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Wp64 /Gm /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ComSpyAudit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ComSpyAudit.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ComSpyAudit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ComSpyAudit.rc

"$(INTDIR)\ComSpyAudit.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Release"

!ELSEIF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Debug"

!ENDIF 

!IF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Release"

!ELSEIF  "$(CFG)" == "ComSpyAudit - Win64 Unicode Debug"

!ENDIF 


!ENDIF 
