!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on MtsSdkPs.dsp
!IF "$(CFG)" == ""
CFG=MtsSdkPs - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MtsSdkPs - Win32 Debug.
!ENDIF 

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="$(CPU)"
!ENDIF

!IF "$(CFG)" != "MtsSdkPs - Win32 Release" && "$(CFG)" !=\
 "MtsSdkPs - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MtsSdkPs.mak" CFG="MtsSdkPs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MtsSdkPs - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MtsSdkPs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MtsSdkPs - Win32 Release"

!IF "$(CPU)" == "IA64"
OUTDIR=.\Release64
INTDIR=.\Release64
# Begin Custom Macros
OutDir=.\Release64
# End Custom Macros
!ELSE
OUTDIR=.\Release32
INTDIR=.\Release32
# Begin Custom Macros
OutDir=.\Release32
# End Custom Macros
!ENDIF


!IF "$(RECURSE)" == "0" 

ALL : "SimpleLog_i.c" "SimpleLog.tlb" "SimpleLog.h" "CopyFileRm_i.c"\
 "CopyFileRm.tlb" "CopyFileRm.h" "$(OUTDIR)\MtsSdkPs.dll"

!ELSE 

ALL : "SimpleLog_i.c" "SimpleLog.tlb" "SimpleLog.h" "CopyFileRm_i.c"\
 "CopyFileRm.tlb" "CopyFileRm.h" "$(OUTDIR)\MtsSdkPs.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CopyFileRm_p.obj"
	-@erase "$(INTDIR)\dlldata.obj"
	-@erase "$(INTDIR)\iid.obj"
	-@erase "$(INTDIR)\SimpleLog_p.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\MtsSdkPs.dll"
	-@erase "$(OUTDIR)\MtsSdkPs.exp"
	-@erase "$(OUTDIR)\MtsSdkPs.lib"
	-@erase "CopyFileRm.h"
	-@erase "CopyFileRm.tlb"
	-@erase "CopyFileRm_i.c"
	-@erase "SimpleLog.h"
	-@erase "SimpleLog.tlb"
	-@erase "SimpleLog_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe

!IF "$(CPU)" == "IA64"
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\Inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0500 /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\MtsSdkPs.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /c 
!ELSE
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\Inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0500 /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\MtsSdkPs.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
!ENDIF

CPP_OBJS=$(OUTDIR)/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MtsSdkPs.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib\
 uuid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\MtsSdkPs.pdb" /machine:$(mach_type) /def:".\MtsSdkPs.def"\
 /out:"$(OUTDIR)\MtsSdkPs.dll" /implib:"$(OUTDIR)\MtsSdkPs.lib" 
DEF_FILE= \
	".\MtsSdkPs.def"
LINK32_OBJS= \
	"$(INTDIR)\CopyFileRm_p.obj" \
	"$(INTDIR)\dlldata.obj" \
	"$(INTDIR)\iid.obj" \
	"$(INTDIR)\SimpleLog_p.obj"

"$(OUTDIR)\MtsSdkPs.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=$(OUTDIR)\MtsSdkPs.dll
SOURCE=$(InputPath)
PostBuild_Desc=Registering Proxy Stub DLL
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=$(OUTDIR)
# End Custom Macros

$(DS_POSTBUILD_DEP) : "SimpleLog_i.c" "SimpleLog.tlb" "SimpleLog.h"\
 "CopyFileRm_i.c" "CopyFileRm.tlb" "CopyFileRm.h" "$(OUTDIR)\MtsSdkPs.dll"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "MtsSdkPs - Win32 Debug"

!IF "$(CPU)" == "IA64"
OUTDIR=.\Debug64
INTDIR=.\Debug64
# Begin Custom Macros
OutDir=.\Debug64
# End Custom Macros
!ELSE
OUTDIR=.\Debug32
INTDIR=.\Debug32
# Begin Custom Macros
OutDir=.\Debug32
# End Custom Macros
!ENDIF

!IF "$(RECURSE)" == "0" 

ALL : "..\Inc\SimpleLog_i.c" "..\Inc\SimpleLog.tlb" "..\Inc\SimpleLog.h"\
 "..\Inc\CopyFileRm_i.c" "..\Inc\CopyFileRm.tlb" "..\Inc\CopyFileRm.h"\
 "$(OUTDIR)\MtsSdkPs.dll"

!ELSE 

ALL : "..\Inc\SimpleLog_i.c" "..\Inc\SimpleLog.tlb" "..\Inc\SimpleLog.h"\
 "..\Inc\CopyFileRm_i.c" "..\Inc\CopyFileRm.tlb" "..\Inc\CopyFileRm.h"\
 "$(OUTDIR)\MtsSdkPs.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CopyFileRm_p.obj"
	-@erase "$(INTDIR)\dlldata.obj"
	-@erase "$(INTDIR)\iid.obj"
	-@erase "$(INTDIR)\SimpleLog_p.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\MtsSdkPs.dll"
	-@erase "$(OUTDIR)\MtsSdkPs.exp"
	-@erase "$(OUTDIR)\MtsSdkPs.ilk"
	-@erase "$(OUTDIR)\MtsSdkPs.lib"
	-@erase "$(OUTDIR)\MtsSdkPs.pdb"
	-@erase "..\Inc\CopyFileRm.h"
	-@erase "..\Inc\CopyFileRm.tlb"
	-@erase "..\Inc\CopyFileRm_i.c"
	-@erase "..\Inc\SimpleLog.h"
	-@erase "..\Inc\SimpleLog.tlb"
	-@erase "..\Inc\SimpleLog_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe

!IF "$(CPU)" == "IA64"
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\Inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0500 /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\MtsSdkPs.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /c 
!ELSE
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\Inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x0500 /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\MtsSdkPs.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
!ENDIF

CPP_OBJS=$(OUTDIR)/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MtsSdkPs.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib\
 uuid.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\MtsSdkPs.pdb" /debug /machine:$(mach_type) /def:".\MtsSdkPs.def"\
 /out:"$(OUTDIR)\MtsSdkPs.dll" /implib:"$(OUTDIR)\MtsSdkPs.lib" /pdbtype:sept 
DEF_FILE= \
	".\MtsSdkPs.def"
LINK32_OBJS= \
	"$(INTDIR)\CopyFileRm_p.obj" \
	"$(INTDIR)\dlldata.obj" \
	"$(INTDIR)\iid.obj" \
	"$(INTDIR)\SimpleLog_p.obj"

"$(OUTDIR)\MtsSdkPs.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=$(OUTDIR)\MtsSdkPs.dll
SOURCE=$(InputPath)
PostBuild_Desc=Registering Proxy Stub DLL
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=$(OUTDIR)
# End Custom Macros

$(DS_POSTBUILD_DEP) : "..\Inc\SimpleLog_i.c" "..\Inc\SimpleLog.tlb"\
 "..\Inc\SimpleLog.h" "..\Inc\CopyFileRm_i.c" "..\Inc\CopyFileRm.tlb"\
 "..\Inc\CopyFileRm.h" "$(OUTDIR)\MtsSdkPs.dll"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(CFG)" == "MtsSdkPs - Win32 Release" || "$(CFG)" == "MtsSdkPs - Win32 Debug"
SOURCE=.\CopyFileRm.idl

!IF  "$(CFG)" == "MtsSdkPs - Win32 Release"

InputPath=.\CopyFileRm.idl

"CopyFileRm.h"	"CopyFileRm_i.c"	"CopyFileRm.tlb"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "..\inc\CopyFileRm.h" /tlb "..\inc\CopyFileRm.tlb" /iid\
     "..\inc\CopyFileRm_i.c"  "CopyFileRm.idl"

!ELSEIF  "$(CFG)" == "MtsSdkPs - Win32 Debug"

InputPath=.\CopyFileRm.idl

"..\Inc\CopyFileRm.h"	"..\Inc\CopyFileRm_i.c"	"..\Inc\CopyFileRm.tlb"	 : \
$(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "..\inc\CopyFileRm.h" /tlb "..\inc\CopyFileRm.tlb" /iid\
     "..\inc\CopyFileRm_i.c"  "CopyFileRm.idl"

!ENDIF 

SOURCE=.\CopyFileRm_p.c

"$(INTDIR)\CopyFileRm_p.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\dlldata.c

"$(INTDIR)\dlldata.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\iid.c

!IF  "$(CFG)" == "MtsSdkPs - Win32 Release"

NODEP_CPP_IID_C=\
	".\CopyFileRm_i.c"\
	".\SimpleLog_i.c"\
	

"$(INTDIR)\iid.obj" : $(SOURCE) "$(INTDIR)" "..\inc\CopyFileRm_i.c"\
 "..\inc\SimpleLog_i.c"


!ELSEIF  "$(CFG)" == "MtsSdkPs - Win32 Debug"

NODEP_CPP_IID_C=\
	"..\Inc\CopyFileRm_i.c"\
	"..\Inc\SimpleLog_i.c"\
	

"$(INTDIR)\iid.obj" : $(SOURCE) "$(INTDIR)" "..\Inc\CopyFileRm_i.c"\
 "..\Inc\SimpleLog_i.c"


!ENDIF 

SOURCE=.\SimpleLog.idl

!IF  "$(CFG)" == "MtsSdkPs - Win32 Release"

InputPath=.\SimpleLog.idl

"SimpleLog.h"	"SimpleLog.tlb"	"SimpleLog_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "..\inc\SimpleLog.h" /tlb "..\inc\SimpleLog.tlb" /iid\
     "..\inc\SimpleLog_i.c"  "SimpleLog.idl"

!ELSEIF  "$(CFG)" == "MtsSdkPs - Win32 Debug"

InputPath=.\SimpleLog.idl

"..\Inc\SimpleLog.h"	"..\Inc\SimpleLog.tlb"	"..\Inc\SimpleLog_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "..\inc\SimpleLog.h" /tlb "..\inc\SimpleLog.tlb" /iid\
     "..\inc\SimpleLog_i.c"  "SimpleLog.idl"

!ENDIF 

SOURCE=.\SimpleLog_p.c

"$(INTDIR)\SimpleLog_p.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

