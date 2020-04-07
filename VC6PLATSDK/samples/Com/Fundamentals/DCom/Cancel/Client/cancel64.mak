
# Microsoft Developer Studio Generated NMAKE File, Based on cancel.dsp
!IF "$(CFG)" == ""
CFG=cancel - Win64 Debug
!MESSAGE No configuration specified. Defaulting to cancel - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "cancel - Win64 Release" && "$(CFG)" != "cancel - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cancel64.mak" CFG="cancel - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cancel - Win64 Release" (based on "Win64 (IA64) Application")
!MESSAGE "cancel - Win64 Debug" (based on "Win64 (IA64) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "cancel - Win64 Release"

OUTDIR=.\..\Bin\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\..\Bin\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\cancel.exe"

!ELSE 

ALL : "sta - Win64 Release" "mta - Win64 Release" "inproc - Win64 Release" "$(OUTDIR)\cancel.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"inproc - Win64 ReleaseCLEAN" "mta - Win64 ReleaseCLEAN" "sta - Win64 ReleaseCLEAN" 
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
CPP_PROJ=/nologo /ML /W3 /Wp64 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "_WIN32_DCOM" /D "WIN64" /D "WIN32"  /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\cancel.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win64 $(MIDL_OPTIMIZATION)
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\cancel.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cancel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\cancel.pdb" /machine:IA64 /out:"$(OUTDIR)\cancel.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cancel.obj" \
	"$(INTDIR)\cancel.res" \
	"$(OUTDIR)\inproc.lib"

"$(OUTDIR)\cancel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "cancel - Win64 Debug"

OUTDIR=.\..\Bin\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\..\Bin\Debug\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\cancel.exe"

!ELSE 

ALL : "sta - Win64 Debug" "mta - Win64 Debug" "inproc - Win64 Debug" "$(OUTDIR)\cancel.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"inproc - Win64 DebugCLEAN" "mta - Win64 DebugCLEAN" "sta - Win64 DebugCLEAN" 
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
CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /D "_WINDOWS" /D "_DEBUG" /D "UNICODE" /D "_UNICODE" /D "_WIN32_DCOM" /D "WIN64" /D "WIN32"  /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win64 $(MIDL_OPTIMIZATION)
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\cancel.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cancel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"WinMainCRTStartup" /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\cancel.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\cancel.exe"  
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


!IF "$(CFG)" == "cancel - Win64 Release" || "$(CFG)" == "cancel - Win64 Debug"

!IF  "$(CFG)" == "cancel - Win64 Release"

"inproc - Win64 Release" : 
   cd ".\..\inproc"
   $(MAKE) /$(MAKEFLAGS) /F .\inproc64.mak CFG="inproc - Win64 Release" 
   cd "..\client"

"inproc - Win64 ReleaseCLEAN" : 
   cd ".\..\inproc"
   $(MAKE) /$(MAKEFLAGS) /F .\inproc64.mak CFG="inproc - Win64 Release" RECURSE=1 CLEAN 
   cd "..\client"

!ELSEIF  "$(CFG)" == "cancel - Win64 Debug"

"inproc - Win64 Debug" : 
   cd ".\..\inproc"
   $(MAKE) /$(MAKEFLAGS) /F .\inproc64.mak CFG="inproc - Win64 Debug" 
   cd "..\client"

"inproc - Win64 DebugCLEAN" : 
   cd ".\..\inproc"
   $(MAKE) /$(MAKEFLAGS) /F .\inproc64.mak CFG="inproc - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\client"

!ENDIF 

!IF  "$(CFG)" == "cancel - Win64 Release"

"mta - Win64 Release" : 
   cd ".\..\local\mta"
   $(MAKE) /$(MAKEFLAGS) /F .\mta64.mak CFG="mta - Win64 Release" 
   cd "..\..\client"

"mta - Win64 ReleaseCLEAN" : 
   cd ".\..\local\mta"
   $(MAKE) /$(MAKEFLAGS) /F .\mta64.mak CFG="mta - Win64 Release" RECURSE=1 CLEAN 
   cd "..\..\client"

!ELSEIF  "$(CFG)" == "cancel - Win64 Debug"

"mta - Win64 Debug" : 
   cd ".\..\local\mta"
   $(MAKE) /$(MAKEFLAGS) /F .\mta64.mak CFG="mta - Win64 Debug" 
   cd "..\..\client"

"mta - Win64 DebugCLEAN" : 
   cd ".\..\local\mta"
   $(MAKE) /$(MAKEFLAGS) /F .\mta64.mak CFG="mta - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\..\client"

!ENDIF 

!IF  "$(CFG)" == "cancel - Win64 Release"

"sta - Win64 Release" : 
   cd ".\..\local\sta"
   $(MAKE) /$(MAKEFLAGS) /F .\sta64.mak CFG="sta - Win64 Release" 
   cd "..\..\client"

"sta - Win64 ReleaseCLEAN" : 
   cd ".\..\local\sta"
   $(MAKE) /$(MAKEFLAGS) /F .\sta64.mak CFG="sta - Win64 Release" RECURSE=1 CLEAN 
   cd "..\..\client"

!ELSEIF  "$(CFG)" == "cancel - Win64 Debug"

"sta - Win64 Debug" : 
   cd ".\..\local\sta"
   $(MAKE) /$(MAKEFLAGS) /F .\sta64.mak CFG="sta - Win64 Debug" 
   cd "..\..\client"

"sta - Win64 DebugCLEAN" : 
   cd ".\..\local\sta"
   $(MAKE) /$(MAKEFLAGS) /F .\sta64.mak CFG="sta - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\..\client"

!ENDIF 

SOURCE=.\cancel.cpp

"$(INTDIR)\cancel.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\cancel.rc

"$(INTDIR)\cancel.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 
