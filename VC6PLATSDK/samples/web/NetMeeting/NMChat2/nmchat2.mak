# Microsoft Developer Studio Generated NMAKE File, Based on nmchat2.dsp
!IF "$(CFG)" == ""
CFG=nmchat2 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to nmchat2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "nmchat2 - Win32 Release" && "$(CFG)" != "nmchat2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nmchat2.mak" CFG="nmchat2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nmchat2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nmchat2 - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "nmchat2 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\nmchat2.exe"


CLEAN :
	-@erase "$(INTDIR)\applet.obj"
	-@erase "$(INTDIR)\conf.obj"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\session.obj"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\nmchat2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\nmchat2.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\res.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmchat2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\nmchat2.pdb" /machine:I386 /out:"$(OUTDIR)\nmchat2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ui.obj" \
	"$(INTDIR)\conf.obj" \
	"$(INTDIR)\res.res" \
	"$(INTDIR)\session.obj" \
	"$(INTDIR)\applet.obj"

"$(OUTDIR)\nmchat2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "nmchat2 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\nmchat2.exe"


CLEAN :
	-@erase "$(INTDIR)\applet.obj"
	-@erase "$(INTDIR)\conf.obj"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\session.obj"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\nmchat2.exe"
	-@erase "$(OUTDIR)\nmchat2.ilk"
	-@erase "$(OUTDIR)\nmchat2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\nmchat2.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\res.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmchat2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\nmchat2.pdb" /debug /machine:I386 /out:"$(OUTDIR)\nmchat2.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ui.obj" \
	"$(INTDIR)\conf.obj" \
	"$(INTDIR)\res.res" \
	"$(INTDIR)\session.obj" \
	"$(INTDIR)\applet.obj"

"$(OUTDIR)\nmchat2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("nmchat2.dep")
!INCLUDE "nmchat2.dep"
!ELSE 
!MESSAGE Warning: cannot find "nmchat2.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "nmchat2 - Win32 Release" || "$(CFG)" == "nmchat2 - Win32 Debug"
SOURCE=.\applet.cpp

"$(INTDIR)\applet.obj" : $(SOURCE) "$(INTDIR)" ".\iapplet.h" ".\imsconf2.h" ".\iapplet.c"


SOURCE=.\conf.cpp

"$(INTDIR)\conf.obj" : $(SOURCE) "$(INTDIR)" ".\iapplet.h" ".\imsconf2.c" ".\imsconf2.h"


SOURCE=.\iapplet.idl

!IF  "$(CFG)" == "nmchat2 - Win32 Release"

TargetDir=.\Release
InputPath=.\iapplet.idl
InputName=iapplet

".\iapplet.h"	".\iapplet.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata   $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header   $(InputName).h /iid $(InputName).c $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "nmchat2 - Win32 Debug"

TargetDir=.\Debug
InputPath=.\iapplet.idl
InputName=iapplet

".\iapplet.h"	".\iapplet.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata   $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header   $(InputName).h /iid $(InputName).c $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\imsconf2.idl

!IF  "$(CFG)" == "nmchat2 - Win32 Release"

TargetDir=.\Release
InputPath=.\imsconf2.idl
InputName=imsconf2

".\imsconf2.h"	".\imsconf2.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata   $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header   $(InputName).h /iid $(InputName).c $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "nmchat2 - Win32 Debug"

TargetDir=.\Debug
InputPath=.\imsconf2.idl
InputName=imsconf2

".\imsconf2.h"	".\imsconf2.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata   $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header   $(InputName).h /iid $(InputName).c $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\res.rc

"$(INTDIR)\res.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\session.cpp

"$(INTDIR)\session.obj" : $(SOURCE) "$(INTDIR)" ".\iapplet.h" ".\imsconf2.h"


SOURCE=.\ui.cpp

"$(INTDIR)\ui.obj" : $(SOURCE) "$(INTDIR)" ".\iapplet.h" ".\imsconf2.h"



!ENDIF 

