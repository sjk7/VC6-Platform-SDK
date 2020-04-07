# Microsoft Developer Studio Generated NMAKE File, Based on CallBackClient.dsp
!IF "$(CFG)" == ""
CFG=CallBackClient - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CallBackClient - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CallBackClient - Win32 Release" && "$(CFG)" != "CallBackClient - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CallBackClient.mak" CFG="CallBackClient - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CallBackClient - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "CallBackClient - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CallBackClient - Win32 Release"

OUTDIR=.\..\Release\x86
INTDIR=.\Release\x86
# Begin Custom Macros
OutDir=.\..\Release\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CallBackClient.exe"

!ELSE 

ALL : "$(OUTDIR)\CallBackClient.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\CallBackClient.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CallBackClient.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\idl\ps_win32" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\CallBackClient.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CallBackClient.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\CallBackClient.pdb" /machine:$(CPU) /out:"$(OUTDIR)\CallBackClient.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CallBackClient.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CallBackClient.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CallBackClient - Win32 Debug"

OUTDIR=.\..\Debug\x86
INTDIR=.\Debug\x86
# Begin Custom Macros
OutDir=.\..\Debug\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CallBackClient.exe"

!ELSE 

ALL : "FullSvr - Win32 Debug" "$(OUTDIR)\CallBackClient.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FullSvr - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\CallBackClient.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CallBackClient.exe"
	-@erase "$(OUTDIR)\CallBackClient.ilk"
	-@erase "$(OUTDIR)\CallBackClient.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\idl\ps_win32" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\CallBackClient.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CallBackClient.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\CallBackClient.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\CallBackClient.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CallBackClient.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CallBackClient.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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
!IF EXISTS("CallBackClient.dep")
!INCLUDE "CallBackClient.dep"
!ELSE 
!MESSAGE Warning: cannot find "CallBackClient.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CallBackClient - Win32 Release" || "$(CFG)" == "CallBackClient - Win32 Debug"
SOURCE=.\CallBackClient.cpp

"$(INTDIR)\CallBackClient.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

"$(INTDIR)\StdAfx.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "CallBackClient - Win32 Release"

!ELSEIF  "$(CFG)" == "CallBackClient - Win32 Debug"

"FullSvr - Win32 Debug" : 
   cd ".\..\FullSvr"
   $(MAKE) /$(MAKEFLAGS) /F .\FullSvr.mak CFG="FullSvr - Win32 Debug" 
   cd "..\CallBackClient"

"FullSvr - Win32 DebugCLEAN" : 
   cd ".\..\FullSvr"
   $(MAKE) /$(MAKEFLAGS) /F .\FullSvr.mak CFG="FullSvr - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\CallBackClient"

!ENDIF 


!ENDIF 

