!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on nmui.dsp
!IF "$(CFG)" == ""
CFG=nmui - Win32 Debug
!MESSAGE No configuration specified. Defaulting to nmui - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "nmui - Win32 Release" && "$(CFG)" != "nmui - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nmui.mak" CFG="nmui - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nmui - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nmui - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "nmui - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\nmui.exe" "$(OUTDIR)\nmui.bsc"


CLEAN :
	-@erase "$(INTDIR)\cCall.obj"
	-@erase "$(INTDIR)\cCall.sbr"
	-@erase "$(INTDIR)\cchan.obj"
	-@erase "$(INTDIR)\cchan.sbr"
	-@erase "$(INTDIR)\cConf.obj"
	-@erase "$(INTDIR)\cConf.sbr"
	-@erase "$(INTDIR)\cData.obj"
	-@erase "$(INTDIR)\cData.sbr"
	-@erase "$(INTDIR)\cft.obj"
	-@erase "$(INTDIR)\cft.sbr"
	-@erase "$(INTDIR)\clUtil.obj"
	-@erase "$(INTDIR)\clUtil.sbr"
	-@erase "$(INTDIR)\cmd.obj"
	-@erase "$(INTDIR)\cmd.sbr"
	-@erase "$(INTDIR)\cMemb.obj"
	-@erase "$(INTDIR)\cMemb.sbr"
	-@erase "$(INTDIR)\cMgr.obj"
	-@erase "$(INTDIR)\cMgr.sbr"
	-@erase "$(INTDIR)\cshare.obj"
	-@erase "$(INTDIR)\cshare.sbr"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\debug.sbr"
	-@erase "$(INTDIR)\dlg.obj"
	-@erase "$(INTDIR)\dlg.sbr"
	-@erase "$(INTDIR)\imsconf2.obj"
	-@erase "$(INTDIR)\imsconf2.sbr"
	-@erase "$(INTDIR)\init.obj"
	-@erase "$(INTDIR)\init.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\msg.sbr"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\rtns.obj"
	-@erase "$(INTDIR)\rtns.sbr"
	-@erase "$(INTDIR)\sbar.obj"
	-@erase "$(INTDIR)\sbar.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\nmui.bsc"
	-@erase "$(OUTDIR)\nmui.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "STRICT" /D "WIN32" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\nmui.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmui.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cCall.sbr" \
	"$(INTDIR)\cchan.sbr" \
	"$(INTDIR)\cConf.sbr" \
	"$(INTDIR)\cData.sbr" \
	"$(INTDIR)\cft.sbr" \
	"$(INTDIR)\clUtil.sbr" \
	"$(INTDIR)\cmd.sbr" \
	"$(INTDIR)\cMemb.sbr" \
	"$(INTDIR)\cMgr.sbr" \
	"$(INTDIR)\cshare.sbr" \
	"$(INTDIR)\debug.sbr" \
	"$(INTDIR)\dlg.sbr" \
	"$(INTDIR)\imsconf2.sbr" \
	"$(INTDIR)\init.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\msg.sbr" \
	"$(INTDIR)\rtns.sbr" \
	"$(INTDIR)\sbar.sbr" \
	"$(INTDIR)\util.sbr"

"$(OUTDIR)\nmui.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\nmui.pdb" /machine:$(CPU) /out:"$(OUTDIR)\nmui.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cCall.obj" \
	"$(INTDIR)\cchan.obj" \
	"$(INTDIR)\cConf.obj" \
	"$(INTDIR)\cData.obj" \
	"$(INTDIR)\cft.obj" \
	"$(INTDIR)\clUtil.obj" \
	"$(INTDIR)\cmd.obj" \
	"$(INTDIR)\cMemb.obj" \
	"$(INTDIR)\cMgr.obj" \
	"$(INTDIR)\cshare.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\dlg.obj" \
	"$(INTDIR)\imsconf2.obj" \
	"$(INTDIR)\init.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\rtns.obj" \
	"$(INTDIR)\sbar.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\res.res"

"$(OUTDIR)\nmui.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\imsconf2.h" ".\imsconf2.c" "$(OUTDIR)\nmui.exe" "$(OUTDIR)\nmui.bsc"


CLEAN :
	-@erase "$(INTDIR)\cCall.obj"
	-@erase "$(INTDIR)\cCall.sbr"
	-@erase "$(INTDIR)\cchan.obj"
	-@erase "$(INTDIR)\cchan.sbr"
	-@erase "$(INTDIR)\cConf.obj"
	-@erase "$(INTDIR)\cConf.sbr"
	-@erase "$(INTDIR)\cData.obj"
	-@erase "$(INTDIR)\cData.sbr"
	-@erase "$(INTDIR)\cft.obj"
	-@erase "$(INTDIR)\cft.sbr"
	-@erase "$(INTDIR)\clUtil.obj"
	-@erase "$(INTDIR)\clUtil.sbr"
	-@erase "$(INTDIR)\cmd.obj"
	-@erase "$(INTDIR)\cmd.sbr"
	-@erase "$(INTDIR)\cMemb.obj"
	-@erase "$(INTDIR)\cMemb.sbr"
	-@erase "$(INTDIR)\cMgr.obj"
	-@erase "$(INTDIR)\cMgr.sbr"
	-@erase "$(INTDIR)\cshare.obj"
	-@erase "$(INTDIR)\cshare.sbr"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\debug.sbr"
	-@erase "$(INTDIR)\dlg.obj"
	-@erase "$(INTDIR)\dlg.sbr"
	-@erase "$(INTDIR)\imsconf2.obj"
	-@erase "$(INTDIR)\imsconf2.sbr"
	-@erase "$(INTDIR)\init.obj"
	-@erase "$(INTDIR)\init.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\msg.sbr"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\rtns.obj"
	-@erase "$(INTDIR)\rtns.sbr"
	-@erase "$(INTDIR)\sbar.obj"
	-@erase "$(INTDIR)\sbar.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\nmui.bsc"
	-@erase "$(OUTDIR)\nmui.exe"
	-@erase "$(OUTDIR)\nmui.ilk"
	-@erase "$(OUTDIR)\nmui.pdb"
	-@erase ".\imsconf2.c"
	-@erase ".\imsconf2.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "DEBUG" /D "_DEBUG" /D "STRICT" /D "WIN32" /D "_WINDOWS" /D "INIT_OFFICE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\nmui.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmui.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cCall.sbr" \
	"$(INTDIR)\cchan.sbr" \
	"$(INTDIR)\cConf.sbr" \
	"$(INTDIR)\cData.sbr" \
	"$(INTDIR)\cft.sbr" \
	"$(INTDIR)\clUtil.sbr" \
	"$(INTDIR)\cmd.sbr" \
	"$(INTDIR)\cMemb.sbr" \
	"$(INTDIR)\cMgr.sbr" \
	"$(INTDIR)\cshare.sbr" \
	"$(INTDIR)\debug.sbr" \
	"$(INTDIR)\dlg.sbr" \
	"$(INTDIR)\imsconf2.sbr" \
	"$(INTDIR)\init.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\msg.sbr" \
	"$(INTDIR)\rtns.sbr" \
	"$(INTDIR)\sbar.sbr" \
	"$(INTDIR)\util.sbr"

"$(OUTDIR)\nmui.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\nmui.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\nmui.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cCall.obj" \
	"$(INTDIR)\cchan.obj" \
	"$(INTDIR)\cConf.obj" \
	"$(INTDIR)\cData.obj" \
	"$(INTDIR)\cft.obj" \
	"$(INTDIR)\clUtil.obj" \
	"$(INTDIR)\cmd.obj" \
	"$(INTDIR)\cMemb.obj" \
	"$(INTDIR)\cMgr.obj" \
	"$(INTDIR)\cshare.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\dlg.obj" \
	"$(INTDIR)\imsconf2.obj" \
	"$(INTDIR)\init.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\rtns.obj" \
	"$(INTDIR)\sbar.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\res.res"

"$(OUTDIR)\nmui.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("nmui.dep")
!INCLUDE "nmui.dep"
!ELSE 
!MESSAGE Warning: cannot find "nmui.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "nmui - Win32 Release" || "$(CFG)" == "nmui - Win32 Debug"
SOURCE=.\res.rc

"$(INTDIR)\res.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\cCall.cpp

"$(INTDIR)\cCall.obj"	"$(INTDIR)\cCall.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\cchan.cpp

"$(INTDIR)\cchan.obj"	"$(INTDIR)\cchan.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\cConf.cpp

"$(INTDIR)\cConf.obj"	"$(INTDIR)\cConf.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\cData.cpp

"$(INTDIR)\cData.obj"	"$(INTDIR)\cData.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\cft.cpp

"$(INTDIR)\cft.obj"	"$(INTDIR)\cft.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\clUtil.cpp

"$(INTDIR)\clUtil.obj"	"$(INTDIR)\clUtil.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\cmd.cpp

"$(INTDIR)\cmd.obj"	"$(INTDIR)\cmd.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\cMemb.cpp

"$(INTDIR)\cMemb.obj"	"$(INTDIR)\cMemb.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\cMgr.cpp

"$(INTDIR)\cMgr.obj"	"$(INTDIR)\cMgr.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\cshare.cpp

"$(INTDIR)\cshare.obj"	"$(INTDIR)\cshare.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\debug.cpp

"$(INTDIR)\debug.obj"	"$(INTDIR)\debug.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\dlg.cpp

"$(INTDIR)\dlg.obj"	"$(INTDIR)\dlg.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\imsconf2.c

"$(INTDIR)\imsconf2.obj"	"$(INTDIR)\imsconf2.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\init.cpp

"$(INTDIR)\init.obj"	"$(INTDIR)\init.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\msg.cpp

"$(INTDIR)\msg.obj"	"$(INTDIR)\msg.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\rtns.cpp

"$(INTDIR)\rtns.obj"	"$(INTDIR)\rtns.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\sbar.cpp

"$(INTDIR)\sbar.obj"	"$(INTDIR)\sbar.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\util.cpp

"$(INTDIR)\util.obj"	"$(INTDIR)\util.sbr" : $(SOURCE) "$(INTDIR)" ".\imsconf2.h"


SOURCE=.\imsconf2.idl

!IF  "$(CFG)" == "nmui - Win32 Release"

TargetDir=.\Release
InputPath=.\imsconf2.idl
InputName=imsconf2

".\imsconf2.h"	".\imsconf2.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata   $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header   $(InputName).h /iid $(InputName).c $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "nmui - Win32 Debug"

TargetDir=.\Debug
InputPath=.\imsconf2.idl
InputName=imsconf2

".\imsconf2.h"	".\imsconf2.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata   $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header   $(InputName).h /iid $(InputName).c $(InputPath)
<< 
	

!ENDIF 


!ENDIF 

