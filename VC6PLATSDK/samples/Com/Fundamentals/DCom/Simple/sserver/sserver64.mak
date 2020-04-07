
# Microsoft Developer Studio Generated NMAKE File, Based on sserver.dsp
!IF "$(CFG)" == ""
CFG=sserver - Win64 Debug
!MESSAGE No configuration specified. Defaulting to sserver - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "sserver - Win64 Release" && "$(CFG)" != "sserver - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sserver64.mak" CFG="sserver - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sserver - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "sserver - Win64 Debug" (based on "Win64 (IA64) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "sserver - Win64 Release"

OUTDIR=.\..\bin\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\..\bin\Release\IA64
# End Custom Macros

ALL : "$(OUTDIR)\sserver.exe" ".\..\bin\Release\IA64\sserver.reg"


CLEAN :
	-@erase "$(INTDIR)\sserver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\sserver.exe"
	-@erase ".\..\bin\Release\IA64\sserver.reg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Gz /ML /W3 /Wp64 /GX /O2 /D "NDEBUG" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\sserver.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sserver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\sserver.pdb" /machine:IA64 /out:"$(OUTDIR)\sserver.exe" 
LINK32_OBJS= \
	"$(INTDIR)\sserver.obj"

"$(OUTDIR)\sserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\bin\Release\IA64
TargetPath=.\..\bin\Release\IA64\sserver.exe
TargetName=sserver
InputPath=.\..\bin\Release\IA64\sserver.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\sserver.reg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	Echo REGEDIT > $(OutDir)\$(TargetName).reg 
	Echo HKEY_CLASSES_ROOT\CLSID\{5e9ddec7-5767-11cf-beab-00aa006c3606} = Simple Object Server >> $(OutDir)\$(TargetName).reg 
	Echo HKEY_CLASSES_ROOT\CLSID\{5e9ddec7-5767-11cf-beab-00aa006c3606}\LocalServer32 = $(TargetPath) >> $(OutDir)\$(TargetName).reg
<< 
	

!ELSEIF  "$(CFG)" == "sserver - Win64 Debug"

OUTDIR=.\..\bin\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\..\bin\Debug\IA64
# End Custom Macros

ALL : "$(OUTDIR)\sserver.exe" ".\..\bin\Debug\IA64\sserver.reg"


CLEAN :
	-@erase "$(INTDIR)\sserver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\sserver.exe"
	-@erase "$(OUTDIR)\sserver.ilk"
	-@erase "$(OUTDIR)\sserver.pdb"
	-@erase ".\..\bin\Debug\IA64\sserver.reg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Gz /MLd /W3 /Wp64 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\sserver.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sserver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\sserver.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\sserver.exe"  
LINK32_OBJS= \
	"$(INTDIR)\sserver.obj"

"$(OUTDIR)\sserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\bin\Debug\IA64
TargetPath=.\..\bin\Debug\IA64\sserver.exe
TargetName=sserver
InputPath=.\..\bin\Debug\IA64\sserver.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\sserver.reg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	Echo REGEDIT > $(OutDir)\$(TargetName).reg 
	Echo HKEY_CLASSES_ROOT\CLSID\{5e9ddec7-5767-11cf-beab-00aa006c3606} = Simple Object Server >> $(OutDir)\$(TargetName).reg 
	Echo HKEY_CLASSES_ROOT\CLSID\{5e9ddec7-5767-11cf-beab-00aa006c3606}\LocalServer32 = $(TargetPath) >> $(OutDir)\$(TargetName).reg
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("sserver.dep")
!INCLUDE "sserver.dep"
!ELSE 
!MESSAGE Warning: cannot find "sserver.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "sserver - Win64 Release" || "$(CFG)" == "sserver - Win64 Debug"
SOURCE=.\sserver.cpp

"$(INTDIR)\sserver.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 
