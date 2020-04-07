# Microsoft Developer Studio Generated NMAKE File, Based on cancel.dsp
!IF "$(CFG)" == ""
CFG=cancel - Win32 Debug
!MESSAGE No configuration specified. Defaulting to cancel - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "cancel - Win32 Release" && "$(CFG)" != "cancel - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cancel.mak" CFG="cancel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cancel - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "cancel - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "cancel - Win32 Release"

OUTDIR=.\..\Bin\Release\x86
INTDIR=.\Release\x86
# Begin Custom Macros
OutDir=.\..\Bin\Release\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\cancel.exe"

!ELSE 

ALL : "sta - Win32 Release" "mta - Win32 Release" "inproc - Win32 Release" "$(OUTDIR)\cancel.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"inproc - Win32 ReleaseCLEAN" "mta - Win32 ReleaseCLEAN" "sta - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\cancel.obj"
	-@erase "$(INTDIR)\cancel.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\cancel.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "_WIN32_DCOM" /D "WIN32" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\cancel.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\cancel.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cancel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\cancel.pdb" /machine:$(CPU) /out:"$(OUTDIR)\cancel.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cancel.obj" \
	"$(INTDIR)\cancel.res" \
	"$(OUTDIR)\inproc.lib"

"$(OUTDIR)\cancel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "cancel - Win32 Debug"

OUTDIR=.\..\Bin\Debug\x86
INTDIR=.\Debug\x86
# Begin Custom Macros
OutDir=.\..\Bin\Debug\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\cancel.exe"

!ELSE 

ALL : "sta - Win32 Debug" "mta - Win32 Debug" "inproc - Win32 Debug" "$(OUTDIR)\cancel.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"inproc - Win32 DebugCLEAN" "mta - Win32 DebugCLEAN" "sta - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\cancel.obj"
	-@erase "$(INTDIR)\cancel.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\cancel.exe"
	-@erase "$(OUTDIR)\cancel.ilk"
	-@erase "$(OUTDIR)\cancel.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "_WINDOWS" /D "_DEBUG" /D "UNICODE" /D "_UNICODE" /D "_WIN32_DCOM" /D "WIN32" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\cancel.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cancel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\cancel.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\cancel.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cancel.obj" \
	"$(INTDIR)\cancel.res" \
	"$(OUTDIR)\inproc.lib"

"$(OUTDIR)\cancel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("cancel.dep")
!INCLUDE "cancel.dep"
!ELSE 
!MESSAGE Warning: cannot find "cancel.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "cancel - Win32 Release" || "$(CFG)" == "cancel - Win32 Debug"

!IF  "$(CFG)" == "cancel - Win32 Release"

"inproc - Win32 Release" : 
   cd ".\..\inproc"
   $(MAKE) /$(MAKEFLAGS) /F .\inproc.mak CFG="inproc - Win32 Release" 
   cd "..\client"

"inproc - Win32 ReleaseCLEAN" : 
   cd ".\..\inproc"
   $(MAKE) /$(MAKEFLAGS) /F .\inproc.mak CFG="inproc - Win32 Release" RECURSE=1 CLEAN 
   cd "..\client"

!ELSEIF  "$(CFG)" == "cancel - Win32 Debug"

"inproc - Win32 Debug" : 
   cd ".\..\inproc"
   $(MAKE) /$(MAKEFLAGS) /F .\inproc.mak CFG="inproc - Win32 Debug" 
   cd "..\client"

"inproc - Win32 DebugCLEAN" : 
   cd ".\..\inproc"
   $(MAKE) /$(MAKEFLAGS) /F .\inproc.mak CFG="inproc - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\client"

!ENDIF 

!IF  "$(CFG)" == "cancel - Win32 Release"

"mta - Win32 Release" : 
   cd ".\..\local\mta"
   $(MAKE) /$(MAKEFLAGS) /F .\mta.mak CFG="mta - Win32 Release" 
   cd "..\..\client"

"mta - Win32 ReleaseCLEAN" : 
   cd ".\..\local\mta"
   $(MAKE) /$(MAKEFLAGS) /F .\mta.mak CFG="mta - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\client"

!ELSEIF  "$(CFG)" == "cancel - Win32 Debug"

"mta - Win32 Debug" : 
   cd ".\..\local\mta"
   $(MAKE) /$(MAKEFLAGS) /F .\mta.mak CFG="mta - Win32 Debug" 
   cd "..\..\client"

"mta - Win32 DebugCLEAN" : 
   cd ".\..\local\mta"
   $(MAKE) /$(MAKEFLAGS) /F .\mta.mak CFG="mta - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\client"

!ENDIF 

!IF  "$(CFG)" == "cancel - Win32 Release"

"sta - Win32 Release" : 
   cd ".\..\local\sta"
   $(MAKE) /$(MAKEFLAGS) /F .\sta.mak CFG="sta - Win32 Release" 
   cd "..\..\client"

"sta - Win32 ReleaseCLEAN" : 
   cd ".\..\local\sta"
   $(MAKE) /$(MAKEFLAGS) /F .\sta.mak CFG="sta - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\client"

!ELSEIF  "$(CFG)" == "cancel - Win32 Debug"

"sta - Win32 Debug" : 
   cd ".\..\local\sta"
   $(MAKE) /$(MAKEFLAGS) /F .\sta.mak CFG="sta - Win32 Debug" 
   cd "..\..\client"

"sta - Win32 DebugCLEAN" : 
   cd ".\..\local\sta"
   $(MAKE) /$(MAKEFLAGS) /F .\sta.mak CFG="sta - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\client"

!ENDIF 

SOURCE=.\cancel.cpp

"$(INTDIR)\cancel.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\cancel.rc

"$(INTDIR)\cancel.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

