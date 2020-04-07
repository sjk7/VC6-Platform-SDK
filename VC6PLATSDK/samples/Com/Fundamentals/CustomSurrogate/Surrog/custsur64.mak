
# Microsoft Developer Studio Generated NMAKE File, Based on custsur.dsp
!IF "$(CFG)" == ""
CFG=custsur - Win64 Debug
!MESSAGE No configuration specified. Defaulting to custsur - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "custsur - Win64 Release" && "$(CFG)" != "custsur - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "custsur64.mak" CFG="custsur - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "custsur - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "custsur - Win64 Debug" (based on "Win64 (IA64) Console Application")
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

!IF  "$(CFG)" == "custsur - Win64 Release"

OUTDIR=.\..\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\..\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\custsur.exe"

!ELSE 

ALL : "dog - Win64 Release" "idl - Win64 Release" "dogps - Win64 Release" "$(OUTDIR)\custsur.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"dogps - Win64 ReleaseCLEAN" "idl - Win64 ReleaseCLEAN" "dog - Win64 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\cfwrap.obj"
	-@erase "$(INTDIR)\csur.obj"
	-@erase "$(INTDIR)\custsur.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\custsur.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /GX /O2 /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_MBCS" /Fp"$(INTDIR)\custsur.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\custsur.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\custsur.pdb" /machine:IA64 /out:"$(OUTDIR)\custsur.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cfwrap.obj" \
	"$(INTDIR)\csur.obj" \
	"$(INTDIR)\custsur.obj" \
	"$(OUTDIR)\dogps.lib"

"$(OUTDIR)\custsur.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "custsur - Win64 Debug"

OUTDIR=.\..\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\..\Debug\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\custsur.exe"

!ELSE 

ALL : "dog - Win64 Debug" "idl - Win64 Debug" "dogps - Win64 Debug" "$(OUTDIR)\custsur.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"dogps - Win64 DebugCLEAN" "idl - Win64 DebugCLEAN" "dog - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\cfwrap.obj"
	-@erase "$(INTDIR)\csur.obj"
	-@erase "$(INTDIR)\custsur.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\custsur.exe"
	-@erase "$(OUTDIR)\custsur.ilk"
	-@erase "$(OUTDIR)\custsur.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_MBCS" /Fp"$(INTDIR)\custsur.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\custsur.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\custsur.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\custsur.exe"  
LINK32_OBJS= \
	"$(INTDIR)\cfwrap.obj" \
	"$(INTDIR)\csur.obj" \
	"$(INTDIR)\custsur.obj" \
	"$(OUTDIR)\dogps.lib"

"$(OUTDIR)\custsur.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("custsur.dep")
!INCLUDE "custsur.dep"
!ELSE 
!MESSAGE Warning: cannot find "custsur.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "custsur - Win64 Release" || "$(CFG)" == "custsur - Win64 Debug"

!IF  "$(CFG)" == "custsur - Win64 Release"

"dogps - Win64 Release" : 
   cd ".\..\dogps"
   $(MAKE) /$(MAKEFLAGS) /F .\dogps64.mak CFG="dogps - Win64 Release" 
   cd "..\surrog"

"dogps - Win64 ReleaseCLEAN" : 
   cd ".\..\dogps"
   $(MAKE) /$(MAKEFLAGS) /F .\dogps64.mak CFG="dogps - Win64 Release" RECURSE=1 CLEAN 
   cd "..\surrog"

!ELSEIF  "$(CFG)" == "custsur - Win64 Debug"

"dogps - Win64 Debug" : 
   cd ".\..\dogps"
   $(MAKE) /$(MAKEFLAGS) /F .\dogps64.mak CFG="dogps - Win64 Debug" 
   cd "..\surrog"

"dogps - Win64 DebugCLEAN" : 
   cd ".\..\dogps"
   $(MAKE) /$(MAKEFLAGS) /F .\dogps64.mak CFG="dogps - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\surrog"

!ENDIF 

!IF  "$(CFG)" == "custsur - Win64 Release"

"idl - Win64 Release" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Release" 
   cd "..\surrog"

"idl - Win64 ReleaseCLEAN" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Release" RECURSE=1 CLEAN 
   cd "..\surrog"

!ELSEIF  "$(CFG)" == "custsur - Win64 Debug"

"idl - Win64 Debug" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" 
   cd "..\surrog"

"idl - Win64 DebugCLEAN" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\surrog"

!ENDIF 

!IF  "$(CFG)" == "custsur - Win64 Release"

"dog - Win64 Release" : 
   cd ".\..\dog"
   $(MAKE) /$(MAKEFLAGS) /F .\dog64.mak CFG="dog - Win64 Release" 
   cd "..\surrog"

"dog - Win64 ReleaseCLEAN" : 
   cd ".\..\dog"
   $(MAKE) /$(MAKEFLAGS) /F .\dog64.mak CFG="dog - Win64 Release" RECURSE=1 CLEAN 
   cd "..\surrog"

!ELSEIF  "$(CFG)" == "custsur - Win64 Debug"

"dog - Win64 Debug" : 
   cd ".\..\dog"
   $(MAKE) /$(MAKEFLAGS) /F .\dog64.mak CFG="dog - Win64 Debug" 
   cd "..\surrog"

"dog - Win64 DebugCLEAN" : 
   cd ".\..\dog"
   $(MAKE) /$(MAKEFLAGS) /F .\dog64.mak CFG="dog - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\surrog"

!ENDIF 

SOURCE=.\cfwrap.cpp

"$(INTDIR)\cfwrap.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\csur.cpp

"$(INTDIR)\csur.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\custsur.cpp

"$(INTDIR)\custsur.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 
