# Microsoft Developer Studio Generated NMAKE File, Based on ContextMenuEx.dsp
!IF "$(CFG)" == ""
CFG=ContextMenuEx - Win32 Ansi Debug
!MESSAGE No configuration specified. Defaulting to ContextMenuEx - Win32 Ansi Debug.
!ENDIF 

!IF "$(CFG)" != "ContextMenuEx - Win32 Debug" && "$(CFG)" != "ContextMenuEx - Win32 Ansi Debug" && "$(CFG)" != "ContextMenuEx - Win32 Release" && "$(CFG)" != "ContextMenuEx - Win32 Ansi Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ContextMenuEx.mak" CFG="ContextMenuEx - Win32 Ansi Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ContextMenuEx - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ContextMenuEx - Win32 Ansi Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ContextMenuEx - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ContextMenuEx - Win32 Ansi Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ContextMenuEx - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ContextMenuEx.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\ContextMenuEx.obj"
	-@erase "$(INTDIR)\ContextMenuEx.res"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ContextMenuEx.dll"
	-@erase "$(OUTDIR)\ContextMenuEx.exp"
	-@erase "$(OUTDIR)\ContextMenuEx.ilk"
	-@erase "$(OUTDIR)\ContextMenuEx.lib"
	-@erase "$(OUTDIR)\ContextMenuEx.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CONTEXTMENUEX_EXPORTS" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\ContextMenuEx.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ContextMenuEx.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ContextMenuEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\ContextMenuEx.pdb" /debug /machine:$(CPU) /def:".\ContextMenuEx.def" /out:"$(OUTDIR)\ContextMenuEx.dll" /implib:"$(OUTDIR)\ContextMenuEx.lib" /pdbtype:sept 
DEF_FILE= \
	".\ContextMenuEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\ContextMenuEx.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\ContextMenuEx.res"

"$(OUTDIR)\ContextMenuEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\ContextMenuEx.dll
InputPath=.\Debug\ContextMenuEx.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ContextMenuEx - Win32 Ansi Debug"

OUTDIR=.\Ansi_debug
INTDIR=.\Ansi_debug
# Begin Custom Macros
OutDir=.\Ansi_debug
# End Custom Macros

ALL : "$(OUTDIR)\ContextMenuEx.dll" ".\Ansi_debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\ContextMenuEx.obj"
	-@erase "$(INTDIR)\ContextMenuEx.res"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ContextMenuEx.dll"
	-@erase "$(OUTDIR)\ContextMenuEx.exp"
	-@erase "$(OUTDIR)\ContextMenuEx.ilk"
	-@erase "$(OUTDIR)\ContextMenuEx.lib"
	-@erase "$(OUTDIR)\ContextMenuEx.pdb"
	-@erase ".\Ansi_debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CONTEXTMENUEX_EXPORTS" /Fp"$(INTDIR)\ContextMenuEx.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ContextMenuEx.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ContextMenuEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\ContextMenuEx.pdb" /debug /machine:$(CPU) /def:".\ContextMenuEx.def" /out:"$(OUTDIR)\ContextMenuEx.dll" /implib:"$(OUTDIR)\ContextMenuEx.lib" /pdbtype:sept 
DEF_FILE= \
	".\ContextMenuEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\ContextMenuEx.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\ContextMenuEx.res"

"$(OUTDIR)\ContextMenuEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_debug
TargetPath=.\Ansi_debug\ContextMenuEx.dll
InputPath=.\Ansi_debug\ContextMenuEx.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ContextMenuEx - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ContextMenuEx.dll" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\ContextMenuEx.obj"
	-@erase "$(INTDIR)\ContextMenuEx.res"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ContextMenuEx.dll"
	-@erase "$(OUTDIR)\ContextMenuEx.exp"
	-@erase "$(OUTDIR)\ContextMenuEx.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CONTEXTMENUEX_EXPORTS" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\ContextMenuEx.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ContextMenuEx.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ContextMenuEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\ContextMenuEx.pdb" /machine:$(CPU) /def:".\ContextMenuEx.def" /out:"$(OUTDIR)\ContextMenuEx.dll" /implib:"$(OUTDIR)\ContextMenuEx.lib" 
DEF_FILE= \
	".\ContextMenuEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\ContextMenuEx.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\ContextMenuEx.res"

"$(OUTDIR)\ContextMenuEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\ContextMenuEx.dll
InputPath=.\Release\ContextMenuEx.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ContextMenuEx - Win32 Ansi Release"

OUTDIR=.\Ansi_release
INTDIR=.\Ansi_release
# Begin Custom Macros
OutDir=.\Ansi_release
# End Custom Macros

ALL : "$(OUTDIR)\ContextMenuEx.dll" ".\Ansi_release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\ContextMenuEx.obj"
	-@erase "$(INTDIR)\ContextMenuEx.res"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ContextMenuEx.dll"
	-@erase "$(OUTDIR)\ContextMenuEx.exp"
	-@erase "$(OUTDIR)\ContextMenuEx.lib"
	-@erase ".\Ansi_release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CONTEXTMENUEX_EXPORTS" /Fp"$(INTDIR)\ContextMenuEx.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ContextMenuEx.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ContextMenuEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\ContextMenuEx.pdb" /machine:$(CPU) /def:".\ContextMenuEx.def" /out:"$(OUTDIR)\ContextMenuEx.dll" /implib:"$(OUTDIR)\ContextMenuEx.lib" 
DEF_FILE= \
	".\ContextMenuEx.def"
LINK32_OBJS= \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\ContextMenuEx.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\ContextMenuEx.res"

"$(OUTDIR)\ContextMenuEx.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_release
TargetPath=.\Ansi_release\ContextMenuEx.dll
InputPath=.\Ansi_release\ContextMenuEx.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ContextMenuEx.dep")
!INCLUDE "ContextMenuEx.dep"
!ELSE 
!MESSAGE Warning: cannot find "ContextMenuEx.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ContextMenuEx - Win32 Debug" || "$(CFG)" == "ContextMenuEx - Win32 Ansi Debug" || "$(CFG)" == "ContextMenuEx - Win32 Release" || "$(CFG)" == "ContextMenuEx - Win32 Ansi Release"
SOURCE=.\BaseSnap.Cpp

"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ContextMenuEx.cpp

"$(INTDIR)\ContextMenuEx.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ContextMenuEx.rc

"$(INTDIR)\ContextMenuEx.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Globals.cpp

"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Registry.cpp

"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TraceMacro.cpp

"$(INTDIR)\TraceMacro.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

