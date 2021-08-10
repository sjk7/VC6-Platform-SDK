# Microsoft Developer Studio Generated NMAKE File, Based on NMft.dsp
!IF "$(CFG)" == ""
CFG=nmFt - Win32 Debug
!MESSAGE No configuration specified. Defaulting to nmFt - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "nmFt - Win32 Release" && "$(CFG)" != "nmFt - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NMft.mak" CFG="nmFt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nmFt - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nmFt - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "nmFt - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\NMft.exe"


CLEAN :
	-@erase "$(INTDIR)\cConf.obj"
	-@erase "$(INTDIR)\clUtil.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\imsconf2_i.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\NMft.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /WX /O1 /Ob2 /D "NDEBUG" /D "STRICT" /D "WIN32" /D "_WINDOWS" /Fp"$(INTDIR)\NMft.pch" /YX"precomp.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\res.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NMft.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo /entry:"main" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\NMft.pdb" /machine:I386 /out:"$(OUTDIR)\NMft.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cConf.obj" \
	"$(INTDIR)\clUtil.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\imsconf2_i.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\res.res"

"$(OUTDIR)\NMft.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "nmFt - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\imsconf2.h" ".\imsconf2.c" "$(OUTDIR)\NMft.exe"


CLEAN :
	-@erase "$(INTDIR)\cConf.obj"
	-@erase "$(INTDIR)\clUtil.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\imsconf2_i.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\NMft.exe"
	-@erase "$(OUTDIR)\NMft.ilk"
	-@erase "$(OUTDIR)\NMft.pdb"
	-@erase ".\imsconf2.c"
	-@erase ".\imsconf2.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "DEBUG" /D "_DEBUG" /D "STRICT" /D "WIN32" /D "_WINDOWS" /Fp"$(INTDIR)\NMft.pch" /YX"precomp.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\res.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NMft.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\NMft.pdb" /debug /machine:I386 /out:"$(OUTDIR)\NMft.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cConf.obj" \
	"$(INTDIR)\clUtil.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\imsconf2_i.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\res.res"

"$(OUTDIR)\NMft.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("NMft.dep")
!INCLUDE "NMft.dep"
!ELSE 
!MESSAGE Warning: cannot find "NMft.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "nmFt - Win32 Release" || "$(CFG)" == "nmFt - Win32 Debug"
SOURCE=.\cConf.cpp

"$(INTDIR)\cConf.obj" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\clUtil.cpp

"$(INTDIR)\clUtil.obj" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\debug.cpp

"$(INTDIR)\debug.obj" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=imsconf2.idl

!IF  "$(CFG)" == "nmFt - Win32 Release"

TargetDir=.\Release
InputPath=imsconf2.idl
InputName=imsconf2

".\imsconf2.h"	".\imsconf2_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /client none /server none /ms_ext /D INIT_OFFICE /W1 /c_ext /env win32   /Oicf  /dlldata      $(TargetDir)\dlldata.rpc /proxy   $(TargetDir)\$(InputName).rpc /header      $(InputName).h /iid $(InputName)_i.c   $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "nmFt - Win32 Debug"

TargetDir=.\Debug
InputPath=imsconf2.idl
InputName=imsconf2

".\imsconf2.h"	".\imsconf2.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /client none /server none /ms_ext /D INIT_OFFICE /W1 /c_ext /env win32   /Oicf  /dlldata      $(TargetDir)\dlldata.rpc /proxy   $(TargetDir)\$(InputName).rpc /header      $(InputName).h /iid $(InputName)_i.c   $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\imsconf2_i.c

"$(INTDIR)\imsconf2_i.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\msg.cpp

"$(INTDIR)\msg.obj" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\res.rc

"$(INTDIR)\res.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\util.cpp

"$(INTDIR)\util.obj" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"



!ENDIF 

