!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on LogWriter.dsp
!IF "$(CFG)" == ""
CFG=LOGWRITER - WIN32 UNICODE DEBUG
!MESSAGE No configuration specified. Defaulting to LOGWRITER - WIN32 UNICODE DEBUG.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF  

!IF "$(CFG)" != "LogWriter - Win32 Unicode Release MinSize" && "$(CFG)" != "LogWriter - Win32 Unicode Release MinDependency" && "$(CFG)" != "LogWriter - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LogWriter.mak" CFG="LOGWRITER - WIN32 UNICODE DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LogWriter - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LogWriter - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LogWriter - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "LogWriter - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\LogWriter.dll" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\LogFile.obj"
	-@erase "$(INTDIR)\LogWriter.obj"
	-@erase "$(INTDIR)\LogWriter.pch"
	-@erase "$(INTDIR)\LogWriter.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LogWriter.dll"
	-@erase "$(OUTDIR)\LogWriter.exp"
	-@erase "$(OUTDIR)\LogWriter.lib"
	-@erase ".\LogWriter.h"
	-@erase ".\LogWriter.tlb"
	-@erase ".\LogWriter_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL"  /Fp"$(INTDIR)\LogWriter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LogWriter.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LogWriter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\LogWriter.pdb" /machine:$(mach_type) /def:".\LogWriter.def" /out:"$(OUTDIR)\LogWriter.dll" /implib:"$(OUTDIR)\LogWriter.lib" 
DEF_FILE= \
	".\LogWriter.def"
LINK32_OBJS= \
	"$(INTDIR)\LogFile.obj" \
	"$(INTDIR)\LogWriter.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LogWriter.res"

"$(OUTDIR)\LogWriter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\LogWriter.dll
InputPath=.\ReleaseUMinSize\LogWriter.dll
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
	

!ELSEIF  "$(CFG)" == "LogWriter - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\LogWriter.dll" ".\LogWriter.tlb" ".\LogWriter.h" ".\LogWriter_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\LogFile.obj"
	-@erase "$(INTDIR)\LogWriter.obj"
	-@erase "$(INTDIR)\LogWriter.pch"
	-@erase "$(INTDIR)\LogWriter.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LogWriter.dll"
	-@erase "$(OUTDIR)\LogWriter.exp"
	-@erase "$(OUTDIR)\LogWriter.lib"
	-@erase ".\LogWriter.h"
	-@erase ".\LogWriter.tlb"
	-@erase ".\LogWriter_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"  /Fp"$(INTDIR)\LogWriter.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LogWriter.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LogWriter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\LogWriter.pdb" /machine:$(mach_type) /def:".\LogWriter.def" /out:"$(OUTDIR)\LogWriter.dll" /implib:"$(OUTDIR)\LogWriter.lib" 
DEF_FILE= \
	".\LogWriter.def"
LINK32_OBJS= \
	"$(INTDIR)\LogFile.obj" \
	"$(INTDIR)\LogWriter.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LogWriter.res"

"$(OUTDIR)\LogWriter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\LogWriter.dll
InputPath=.\ReleaseUMinDependency\LogWriter.dll
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
	

!ELSEIF  "$(CFG)" == "LogWriter - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\LogWriter.dll" ".\LogWriter.tlb" ".\LogWriter.h" ".\LogWriter_i.c" "$(OUTDIR)\LogWriter.pch" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\LogFile.obj"
	-@erase "$(INTDIR)\LogWriter.obj"
	-@erase "$(INTDIR)\LogWriter.pch"
	-@erase "$(INTDIR)\LogWriter.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LogWriter.dll"
	-@erase "$(OUTDIR)\LogWriter.exp"
	-@erase "$(OUTDIR)\LogWriter.ilk"
	-@erase "$(OUTDIR)\LogWriter.lib"
	-@erase "$(OUTDIR)\LogWriter.pdb"
	-@erase ".\LogWriter.h"
	-@erase ".\LogWriter.tlb"
	-@erase ".\LogWriter_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LogWriter.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LogWriter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\LogWriter.pdb" /debug /machine:$(mach_type) /def:".\LogWriter.def" /out:"$(OUTDIR)\LogWriter.dll" /implib:"$(OUTDIR)\LogWriter.lib" /pdbtype:sept 
DEF_FILE= \
	".\LogWriter.def"
LINK32_OBJS= \
	"$(INTDIR)\LogFile.obj" \
	"$(INTDIR)\LogWriter.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LogWriter.res"

"$(OUTDIR)\LogWriter.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\LogWriter.dll
InputPath=.\DebugU\LogWriter.dll
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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LogWriter.dep")
!INCLUDE "LogWriter.dep"
!ELSE 
!MESSAGE Warning: cannot find "LogWriter.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LogWriter - Win32 Unicode Release MinSize" || "$(CFG)" == "LogWriter - Win32 Unicode Release MinDependency" || "$(CFG)" == "LogWriter - Win32 Unicode Debug"
SOURCE=.\dlldatax.c
SOURCE=.\LogFile.cpp

"$(INTDIR)\LogFile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LogWriter.pch" ".\LogWriter.h"


SOURCE=.\LogWriter.cpp

"$(INTDIR)\LogWriter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LogWriter.pch" ".\LogWriter.h" ".\LogWriter_i.c"


SOURCE=.\LogWriter.idl

!IF  "$(CFG)" == "LogWriter - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\LogWriter.tlb" /h "LogWriter.h" /iid "LogWriter_i.c" /Oicf 

".\LogWriter.tlb"	".\LogWriter.h"	".\LogWriter_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LogWriter - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\LogWriter.tlb" /h "LogWriter.h" /iid "LogWriter_i.c" /Oicf 

".\LogWriter.tlb"	".\LogWriter.h"	".\LogWriter_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LogWriter - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\LogWriter.tlb" /h "LogWriter.h" /iid "LogWriter_i.c" /Oicf 

".\LogWriter.tlb"	".\LogWriter.h"	".\LogWriter_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\LogWriter.rc

"$(INTDIR)\LogWriter.res" : $(SOURCE) "$(INTDIR)" ".\LogWriter.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LogWriter - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL"  /Fp"$(INTDIR)\LogWriter.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LogWriter.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LogWriter - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"  /Fp"$(INTDIR)\LogWriter.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LogWriter.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LogWriter - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\LogWriter.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LogWriter.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

