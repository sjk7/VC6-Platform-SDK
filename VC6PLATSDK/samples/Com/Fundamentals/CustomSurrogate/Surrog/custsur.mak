# Microsoft Developer Studio Generated NMAKE File, Based on custsur.dsp
!IF "$(CFG)" == ""
CFG=custsur - Win32 Debug
!MESSAGE No configuration specified. Defaulting to custsur - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "custsur - Win32 Release" && "$(CFG)" != "custsur - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "custsur.mak" CFG="custsur - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "custsur - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "custsur - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "custsur - Win32 Release"

OUTDIR=.\..\Release\x86
INTDIR=.\Release\x86
# Begin Custom Macros
OutDir=.\..\Release\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\custsur.exe"

!ELSE 

ALL : "dog - Win32 Release" "idl - Win32 Release" "dogps - Win32 Release" "$(OUTDIR)\custsur.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"dogps - Win32 ReleaseCLEAN" "idl - Win32 ReleaseCLEAN" "dog - Win32 ReleaseCLEAN" 
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

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /Fp"$(INTDIR)\custsur.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\custsur.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\custsur.pdb" /machine:$(CPU) /out:"$(OUTDIR)\custsur.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cfwrap.obj" \
	"$(INTDIR)\csur.obj" \
	"$(INTDIR)\custsur.obj" \
	"$(OUTDIR)\dogps.lib"

"$(OUTDIR)\custsur.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "custsur - Win32 Debug"

OUTDIR=.\..\Debug\x86
INTDIR=.\Debug\x86
# Begin Custom Macros
OutDir=.\..\Debug\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\custsur.exe"

!ELSE 

ALL : "dog - Win32 Debug" "idl - Win32 Debug" "dogps - Win32 Debug" "$(OUTDIR)\custsur.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"dogps - Win32 DebugCLEAN" "idl - Win32 DebugCLEAN" "dog - Win32 DebugCLEAN" 
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

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /Fp"$(INTDIR)\custsur.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\custsur.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\custsur.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\custsur.exe" /pdbtype:sept 
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


!IF "$(CFG)" == "custsur - Win32 Release" || "$(CFG)" == "custsur - Win32 Debug"

!IF  "$(CFG)" == "custsur - Win32 Release"

"dogps - Win32 Release" : 
   cd ".\..\dogps"
   $(MAKE) /$(MAKEFLAGS) /F .\dogps.mak CFG="dogps - Win32 Release" 
   cd "..\surrog"

"dogps - Win32 ReleaseCLEAN" : 
   cd ".\..\dogps"
   $(MAKE) /$(MAKEFLAGS) /F .\dogps.mak CFG="dogps - Win32 Release" RECURSE=1 CLEAN 
   cd "..\surrog"

!ELSEIF  "$(CFG)" == "custsur - Win32 Debug"

"dogps - Win32 Debug" : 
   cd ".\..\dogps"
   $(MAKE) /$(MAKEFLAGS) /F .\dogps.mak CFG="dogps - Win32 Debug" 
   cd "..\surrog"

"dogps - Win32 DebugCLEAN" : 
   cd ".\..\dogps"
   $(MAKE) /$(MAKEFLAGS) /F .\dogps.mak CFG="dogps - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\surrog"

!ENDIF 

!IF  "$(CFG)" == "custsur - Win32 Release"

"idl - Win32 Release" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Release" 
   cd "..\surrog"

"idl - Win32 ReleaseCLEAN" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Release" RECURSE=1 CLEAN 
   cd "..\surrog"

!ELSEIF  "$(CFG)" == "custsur - Win32 Debug"

"idl - Win32 Debug" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Debug" 
   cd "..\surrog"

"idl - Win32 DebugCLEAN" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\surrog"

!ENDIF 

!IF  "$(CFG)" == "custsur - Win32 Release"

"dog - Win32 Release" : 
   cd ".\..\dog"
   $(MAKE) /$(MAKEFLAGS) /F .\dog.mak CFG="dog - Win32 Release" 
   cd "..\surrog"

"dog - Win32 ReleaseCLEAN" : 
   cd ".\..\dog"
   $(MAKE) /$(MAKEFLAGS) /F .\dog.mak CFG="dog - Win32 Release" RECURSE=1 CLEAN 
   cd "..\surrog"

!ELSEIF  "$(CFG)" == "custsur - Win32 Debug"

"dog - Win32 Debug" : 
   cd ".\..\dog"
   $(MAKE) /$(MAKEFLAGS) /F .\dog.mak CFG="dog - Win32 Debug" 
   cd "..\surrog"

"dog - Win32 DebugCLEAN" : 
   cd ".\..\dog"
   $(MAKE) /$(MAKEFLAGS) /F .\dog.mak CFG="dog - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\surrog"

!ENDIF 

SOURCE=.\cfwrap.cpp

"$(INTDIR)\cfwrap.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\csur.cpp

"$(INTDIR)\csur.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\custsur.cpp

"$(INTDIR)\custsur.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

