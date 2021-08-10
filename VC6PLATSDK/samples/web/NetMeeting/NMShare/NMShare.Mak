# Microsoft Developer Studio Generated NMAKE File, Based on nmshare.dsp
!IF "$(CFG)" == ""
CFG=nmShare - Win32 Debug
!MESSAGE No configuration specified. Defaulting to nmShare - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "nmShare - Win32 Release" && "$(CFG)" !=\
 "nmShare - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nmshare.mak" CFG="nmShare - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nmShare - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nmShare - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "nmShare - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\nmshare.exe"

!ELSE 

ALL : "$(OUTDIR)\nmshare.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cConf.obj"
	-@erase "$(INTDIR)\cHwnd.obj"
	-@erase "$(INTDIR)\clUtil.obj"
	-@erase "$(INTDIR)\cmd.obj"
	-@erase "$(INTDIR)\cMemb.obj"
	-@erase "$(INTDIR)\cShare.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\imsconf2.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\nmshare.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "STRICT" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\nmshare.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\res.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmshare.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\nmshare.pdb" /machine:I386\
 /out:"$(OUTDIR)\nmshare.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cConf.obj" \
	"$(INTDIR)\cHwnd.obj" \
	"$(INTDIR)\clUtil.obj" \
	"$(INTDIR)\cmd.obj" \
	"$(INTDIR)\cMemb.obj" \
	"$(INTDIR)\cShare.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\imsconf2.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\res.res" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\nmshare.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\nmshare.exe"

!ELSE 

ALL : "$(OUTDIR)\nmshare.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cConf.obj"
	-@erase "$(INTDIR)\cHwnd.obj"
	-@erase "$(INTDIR)\clUtil.obj"
	-@erase "$(INTDIR)\cmd.obj"
	-@erase "$(INTDIR)\cMemb.obj"
	-@erase "$(INTDIR)\cShare.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\imsconf2.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\res.res"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\nmshare.exe"
	-@erase "$(OUTDIR)\nmshare.ilk"
	-@erase "$(OUTDIR)\nmshare.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "STRICT" /D "DEBUG" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\nmshare.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\res.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nmshare.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\nmshare.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\nmshare.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cConf.obj" \
	"$(INTDIR)\cHwnd.obj" \
	"$(INTDIR)\clUtil.obj" \
	"$(INTDIR)\cmd.obj" \
	"$(INTDIR)\cMemb.obj" \
	"$(INTDIR)\cShare.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\imsconf2.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\res.res" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\nmshare.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "nmShare - Win32 Release" || "$(CFG)" ==\
 "nmShare - Win32 Debug"
SOURCE=.\cConf.cpp

!IF  "$(CFG)" == "nmShare - Win32 Release"

DEP_CPP_CCONF=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cConf.obj" : $(SOURCE) $(DEP_CPP_CCONF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

DEP_CPP_CCONF=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cConf.obj" : $(SOURCE) $(DEP_CPP_CCONF) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cHwnd.cpp

!IF  "$(CFG)" == "nmShare - Win32 Release"

DEP_CPP_CHWND=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cHwnd.obj" : $(SOURCE) $(DEP_CPP_CHWND) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

DEP_CPP_CHWND=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cHwnd.obj" : $(SOURCE) $(DEP_CPP_CHWND) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\clUtil.cpp

!IF  "$(CFG)" == "nmShare - Win32 Release"

DEP_CPP_CLUTI=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\clUtil.obj" : $(SOURCE) $(DEP_CPP_CLUTI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

DEP_CPP_CLUTI=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\clUtil.obj" : $(SOURCE) $(DEP_CPP_CLUTI) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cmd.cpp

!IF  "$(CFG)" == "nmShare - Win32 Release"

DEP_CPP_CMD_C=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cmd.obj" : $(SOURCE) $(DEP_CPP_CMD_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

DEP_CPP_CMD_C=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cmd.obj" : $(SOURCE) $(DEP_CPP_CMD_C) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cMemb.cpp

!IF  "$(CFG)" == "nmShare - Win32 Release"

DEP_CPP_CMEMB=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cMemb.obj" : $(SOURCE) $(DEP_CPP_CMEMB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

DEP_CPP_CMEMB=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cMemb.obj" : $(SOURCE) $(DEP_CPP_CMEMB) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\cShare.cpp

!IF  "$(CFG)" == "nmShare - Win32 Release"

DEP_CPP_CSHAR=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cShare.obj" : $(SOURCE) $(DEP_CPP_CSHAR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

DEP_CPP_CSHAR=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\cShare.obj" : $(SOURCE) $(DEP_CPP_CSHAR) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\debug.cpp

!IF  "$(CFG)" == "nmShare - Win32 Release"

DEP_CPP_DEBUG=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

DEP_CPP_DEBUG=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\imsconf2.c

"$(INTDIR)\imsconf2.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IMSCONF2.IDL

!IF  "$(CFG)" == "nmShare - Win32 Release"

!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

TargetDir=.\Debug
InputPath=.\IMSCONF2.IDL
InputName=IMSCONF2

".\$(InputName).h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /client none /server none /ms_ext /W1 /c_ext /env win32 /Oicf  /dlldata\
 $(TargetDir)\dlldata.rpc /proxy $(TargetDir)\$(InputName).rpc /header\
 $(InputName).h /iid $(InputName).c $(InputPath)

!ENDIF 

SOURCE=.\main.cpp

!IF  "$(CFG)" == "nmShare - Win32 Release"

DEP_CPP_MAIN_=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

DEP_CPP_MAIN_=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\msg.cpp

!IF  "$(CFG)" == "nmShare - Win32 Release"

DEP_CPP_MSG_C=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

DEP_CPP_MSG_C=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\msg.obj" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 

SOURCE=.\res.rc
DEP_RSC_RES_R=\
	".\main.ico"\
	

"$(INTDIR)\res.res" : $(SOURCE) $(DEP_RSC_RES_R) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\util.cpp

!IF  "$(CFG)" == "nmShare - Win32 Release"

DEP_CPP_UTIL_=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "nmShare - Win32 Debug"

DEP_CPP_UTIL_=\
	".\cconf.h"\
	".\clUtil.h"\
	".\cmemb.h"\
	".\cShare.h"\
	".\global.h"\
	".\imsconf2.h"\
	".\precomp.h"\
	

"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)" ".\imsconf2.h"


!ENDIF 


!ENDIF 

