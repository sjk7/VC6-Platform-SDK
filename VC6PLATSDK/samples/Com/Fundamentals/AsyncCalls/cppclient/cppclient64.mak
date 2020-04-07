
# Microsoft Developer Studio Generated NMAKE File, Based on CppClient.dsp
!IF "$(CFG)" == ""
CFG=CppClient - Win64 Debug
!MESSAGE No configuration specified. Defaulting to CppClient - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "CppClient - Win64 Release" && "$(CFG)" != "CppClient - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CppClient64.mak" CFG="CppClient - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CppClient - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "CppClient - Win64 Debug" (based on "Win64 (IA64) Console Application")
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

!IF  "$(CFG)" == "CppClient - Win64 Release"

OUTDIR=.\..\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\..\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CppClient.exe"

!ELSE 

ALL : "$(OUTDIR)\CppClient.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\CppClient.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CppClient.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /GX /O2 /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\CppClient.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CppClient.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\CppClient.pdb" /machine:IA64 /out:"$(OUTDIR)\CppClient.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CppClient.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CppClient.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CppClient - Win64 Debug"

OUTDIR=.\..\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\..\Debug\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CppClient.exe"

!ELSE 

ALL : "FullSvr - Win64 Debug" "$(OUTDIR)\CppClient.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FullSvr - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\CppClient.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CppClient.exe"
	-@erase "$(OUTDIR)\CppClient.ilk"
	-@erase "$(OUTDIR)\CppClient.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /I "..\idl\ps_win64" /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\CppClient.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CppClient.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib  uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\CppClient.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\CppClient.exe"  
LINK32_OBJS= \
	"$(INTDIR)\CppClient.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CppClient.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("CppClient.dep")
!INCLUDE "CppClient.dep"
!ELSE 
!MESSAGE Warning: cannot find "CppClient.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CppClient - Win64 Release" || "$(CFG)" == "CppClient - Win64 Debug"
SOURCE=.\CppClient.cpp

"$(INTDIR)\CppClient.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

"$(INTDIR)\StdAfx.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "CppClient - Win64 Release"

!ELSEIF  "$(CFG)" == "CppClient - Win64 Debug"

"FullSvr - Win64 Debug" : 
   cd "$(MSSDK)\Samples\Com\Fundamentals\AsyncCalls\FullSvr"
   $(MAKE) /$(MAKEFLAGS) /F .\FullSvr64.mak CFG="FullSvr - Win64 Debug" 
   cd "..\CppClient"

"FullSvr - Win64 DebugCLEAN" : 
   cd "$(MSSDK)\Samples\Com\Fundamentals\AsyncCalls\FullSvr"
   $(MAKE) /$(MAKEFLAGS) /F .\FullSvr64.mak CFG="FullSvr - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\CppClient"

!ENDIF 


!ENDIF 
