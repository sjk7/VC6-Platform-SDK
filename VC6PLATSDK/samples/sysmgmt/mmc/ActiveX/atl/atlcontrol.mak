# Microsoft Developer Studio Generated NMAKE File, Based on atlcontrol.dsp
!IF "$(CFG)" == ""
CFG=ATLControl - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ATLControl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ATLControl - Win32 Ansi Debug" && "$(CFG)" != "ATLControl - Win32 Debug" && "$(CFG)" != "ATLControl - Win32 Ansi Release" && "$(CFG)" != "ATLControl - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "atlcontrol.mak" CFG="ATLControl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ATLControl - Win32 Ansi Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLControl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLControl - Win32 Ansi Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ATLControl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ATLControl - Win32 Ansi Debug"

OUTDIR=.\Ansi_debug
INTDIR=.\Ansi_debug
# Begin Custom Macros
OutDir=.\Ansi_debug
# End Custom Macros

ALL : "$(OUTDIR)\atlcontrol.dll" "$(OUTDIR)\ATLControl.h" "$(OUTDIR)\ATLControl_i.c" ".\Ansi_debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLControl.h"
	-@erase "$(INTDIR)\ATLControl.obj"
	-@erase "$(INTDIR)\atlcontrol.pch"
	-@erase "$(INTDIR)\ATLControl.res"
	-@erase "$(INTDIR)\ATLControl.tlb"
	-@erase "$(INTDIR)\ATLControl_i.c"
	-@erase "$(INTDIR)\MMCControl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\atlcontrol.dll"
	-@erase "$(OUTDIR)\atlcontrol.exp"
	-@erase "$(OUTDIR)\atlcontrol.ilk"
	-@erase "$(OUTDIR)\atlcontrol.lib"
	-@erase "$(OUTDIR)\atlcontrol.pdb"
	-@erase ".\Ansi_debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "Ansi_debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\atlcontrol.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/out "Ansi_debug" 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLControl.res" /i "Ansi_debug" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\atlcontrol.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\atlcontrol.pdb" /debug /machine:I386 /def:".\ATLControl.def" /out:"$(OUTDIR)\atlcontrol.dll" /implib:"$(OUTDIR)\atlcontrol.lib" /pdbtype:sept 
DEF_FILE= \
	".\ATLControl.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLControl.obj" \
	"$(INTDIR)\MMCControl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLControl.res"

"$(OUTDIR)\atlcontrol.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_debug
TargetPath=.\Ansi_debug\atlcontrol.dll
InputPath=.\Ansi_debug\atlcontrol.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ATLControl - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\atlcontrol.dll" "$(OUTDIR)\ATLControl.tlb" "$(OUTDIR)\ATLControl.h" "$(OUTDIR)\ATLControl_i.c" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLControl.h"
	-@erase "$(INTDIR)\ATLControl.obj"
	-@erase "$(INTDIR)\atlcontrol.pch"
	-@erase "$(INTDIR)\ATLControl.res"
	-@erase "$(INTDIR)\ATLControl.tlb"
	-@erase "$(INTDIR)\ATLControl_i.c"
	-@erase "$(INTDIR)\MMCControl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\atlcontrol.dll"
	-@erase "$(OUTDIR)\atlcontrol.exp"
	-@erase "$(OUTDIR)\atlcontrol.ilk"
	-@erase "$(OUTDIR)\atlcontrol.lib"
	-@erase "$(OUTDIR)\atlcontrol.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "Debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\atlcontrol.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/out "Debug" 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLControl.res" /i "Debug" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\atlcontrol.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\atlcontrol.pdb" /debug /machine:I386 /def:".\ATLControl.def" /out:"$(OUTDIR)\atlcontrol.dll" /implib:"$(OUTDIR)\atlcontrol.lib" /pdbtype:sept 
DEF_FILE= \
	".\ATLControl.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLControl.obj" \
	"$(INTDIR)\MMCControl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLControl.res"

"$(OUTDIR)\atlcontrol.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\atlcontrol.dll
InputPath=.\Debug\atlcontrol.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ATLControl - Win32 Ansi Release"

OUTDIR=.\Ansi_release
INTDIR=.\Ansi_release
# Begin Custom Macros
OutDir=.\Ansi_release
# End Custom Macros

ALL : "$(OUTDIR)\atlcontrol.dll" "$(OUTDIR)\ATLControl.tlb" "$(OUTDIR)\ATLControl.h" "$(OUTDIR)\ATLControl_i.c" ".\Ansi_release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLControl.h"
	-@erase "$(INTDIR)\ATLControl.obj"
	-@erase "$(INTDIR)\atlcontrol.pch"
	-@erase "$(INTDIR)\ATLControl.res"
	-@erase "$(INTDIR)\ATLControl.tlb"
	-@erase "$(INTDIR)\ATLControl_i.c"
	-@erase "$(INTDIR)\MMCControl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\atlcontrol.dll"
	-@erase "$(OUTDIR)\atlcontrol.exp"
	-@erase "$(OUTDIR)\atlcontrol.lib"
	-@erase ".\Ansi_release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "Ansi_release" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\atlcontrol.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/out "Ansi_release" 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLControl.res" /i "Ansi_release" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\atlcontrol.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\atlcontrol.pdb" /machine:I386 /def:".\ATLControl.def" /out:"$(OUTDIR)\atlcontrol.dll" /implib:"$(OUTDIR)\atlcontrol.lib" 
DEF_FILE= \
	".\ATLControl.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLControl.obj" \
	"$(INTDIR)\MMCControl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLControl.res"

"$(OUTDIR)\atlcontrol.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_release
TargetPath=.\Ansi_release\atlcontrol.dll
InputPath=.\Ansi_release\atlcontrol.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ATLControl - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\atlcontrol.dll" "$(OUTDIR)\ATLControl.tlb" "$(OUTDIR)\ATLControl.h" "$(OUTDIR)\ATLControl_i.c" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ATLControl.h"
	-@erase "$(INTDIR)\ATLControl.obj"
	-@erase "$(INTDIR)\atlcontrol.pch"
	-@erase "$(INTDIR)\ATLControl.res"
	-@erase "$(INTDIR)\ATLControl.tlb"
	-@erase "$(INTDIR)\ATLControl_i.c"
	-@erase "$(INTDIR)\MMCControl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\atlcontrol.dll"
	-@erase "$(OUTDIR)\atlcontrol.exp"
	-@erase "$(OUTDIR)\atlcontrol.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "Release" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\atlcontrol.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/out "Release" 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ATLControl.res" /i "Release" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\atlcontrol.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\atlcontrol.pdb" /machine:I386 /def:".\ATLControl.def" /out:"$(OUTDIR)\atlcontrol.dll" /implib:"$(OUTDIR)\atlcontrol.lib" 
DEF_FILE= \
	".\ATLControl.def"
LINK32_OBJS= \
	"$(INTDIR)\ATLControl.obj" \
	"$(INTDIR)\MMCControl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ATLControl.res"

"$(OUTDIR)\atlcontrol.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\atlcontrol.dll
InputPath=.\Release\atlcontrol.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("atlcontrol.dep")
!INCLUDE "atlcontrol.dep"
!ELSE 
!MESSAGE Warning: cannot find "atlcontrol.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ATLControl - Win32 Ansi Debug" || "$(CFG)" == "ATLControl - Win32 Debug" || "$(CFG)" == "ATLControl - Win32 Ansi Release" || "$(CFG)" == "ATLControl - Win32 Release"
SOURCE=.\ATLControl.cpp

"$(INTDIR)\ATLControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlcontrol.pch"


SOURCE=.\ATLControl.idl

!IF  "$(CFG)" == "ATLControl - Win32 Ansi Debug"

MTL_SWITCHES=/tlb "ATLControl.tlb" /h "ATLControl.h" /iid "ATLControl_i.c" /out "Ansi_debug" /Oicf 

"$(INTDIR)\ATLControl.tlb"	"$(INTDIR)\ATLControl.h"	"$(INTDIR)\ATLControl_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLControl - Win32 Debug"

MTL_SWITCHES=/tlb "ATLControl.tlb" /h "ATLControl.h" /iid "ATLControl_i.c" /out "Debug" /Oicf 

"$(INTDIR)\ATLControl.tlb"	"$(INTDIR)\ATLControl.h"	"$(INTDIR)\ATLControl_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLControl - Win32 Ansi Release"

MTL_SWITCHES=/tlb "ATLControl.tlb" /h "ATLControl.h" /iid "ATLControl_i.c" /out "Ansi_release" /Oicf 

"$(INTDIR)\ATLControl.tlb"	"$(INTDIR)\ATLControl.h"	"$(INTDIR)\ATLControl_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLControl - Win32 Release"

MTL_SWITCHES=/tlb "ATLControl.tlb" /h "ATLControl.h" /iid "ATLControl_i.c" /out "Release" /Oicf 

"$(INTDIR)\ATLControl.tlb"	"$(INTDIR)\ATLControl.h"	"$(INTDIR)\ATLControl_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ATLControl.rc

"$(INTDIR)\ATLControl.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ATLControl.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MMCControl.cpp

"$(INTDIR)\MMCControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\atlcontrol.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ATLControl - Win32 Ansi Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "Ansi_debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\atlcontrol.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\atlcontrol.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLControl - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "Debug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\atlcontrol.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\atlcontrol.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLControl - Win32 Ansi Release"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "Ansi_release" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\atlcontrol.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\atlcontrol.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ATLControl - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "Release" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\atlcontrol.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\atlcontrol.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

