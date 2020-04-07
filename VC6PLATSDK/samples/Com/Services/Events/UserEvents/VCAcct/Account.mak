!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on Account.dsp
!IF "$(CFG)" == ""
CFG=Account - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Account - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Account - Win32 Release" && "$(CFG)" != "Account - Win32 Unicode Release" && "$(CFG)" != "Account - Win32 Unicode Debug" && "$(CFG)" != "Account - Win32 Alpha Release" && "$(CFG)" != "Account - Win32 Alpha Debug" && "$(CFG)" != "Account - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Account.mak" CFG="Account - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Account - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Account - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Account - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Account - Win32 Alpha Release" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Account - Win32 Alpha Debug" (based on "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "Account - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Account - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\Account_i.c" ".\Account.tlb" ".\Account.h" "$(OUTDIR)\Vcacct.dll" "$(OUTDIR)\Account.bsc"


CLEAN :
	-@erase "$(INTDIR)\Account.obj"
	-@erase "$(INTDIR)\Account.pch"
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(INTDIR)\Account.sbr"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\CAccount.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Account.bsc"
	-@erase "$(OUTDIR)\Vcacct.dll"
	-@erase "$(OUTDIR)\Vcacct.exp"
	-@erase "$(OUTDIR)\Vcacct.lib"
	-@erase "Account.h"
	-@erase "Account.tlb"
	-@erase "Account_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /Zi /O2 /Ob2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Account.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Account.sbr" \
	"$(INTDIR)\CAccount.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Account.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtx.lib mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Vcacct.pdb" /machine:$(CPU) /nodefaultlib:"msvcrt.lib" /def:".\Account.def" /out:"$(OUTDIR)\Vcacct.dll" /implib:"$(OUTDIR)\Vcacct.lib" 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.obj" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Account.res"

"$(OUTDIR)\Vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : ".\Account_i.c" ".\Account.tlb" ".\Account.h" "$(OUTDIR)\vcacct.dll" "$(OUTDIR)\Account.bsc"


CLEAN :
	-@erase "$(INTDIR)\Account.obj"
	-@erase "$(INTDIR)\Account.pch"
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(INTDIR)\Account.sbr"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\CAccount.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Account.bsc"
	-@erase "$(OUTDIR)\vcacct.dll"
	-@erase "$(OUTDIR)\vcacct.exp"
	-@erase "$(OUTDIR)\vcacct.lib"
	-@erase "Account.h"
	-@erase "Account.tlb"
	-@erase "Account_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Account.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Account.sbr" \
	"$(INTDIR)\CAccount.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Account.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtx.lib mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\vcacct.pdb" /machine:$(CPU) /nodefaultlib:"msvcrt.lib" /def:".\Account.def" /out:"$(OUTDIR)\vcacct.dll" /implib:"$(OUTDIR)\vcacct.lib" 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.obj" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Account.res"

"$(OUTDIR)\vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : ".\Account_i.c" ".\Account.tlb" ".\Account.h" "$(OUTDIR)\vcacct.dll" "$(OUTDIR)\Account.bsc"


CLEAN :
	-@erase "$(INTDIR)\Account.obj"
	-@erase "$(INTDIR)\Account.pch"
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(INTDIR)\Account.sbr"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\CAccount.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Account.bsc"
	-@erase "$(OUTDIR)\vcacct.dll"
	-@erase "$(OUTDIR)\vcacct.exp"
	-@erase "$(OUTDIR)\vcacct.ilk"
	-@erase "$(OUTDIR)\vcacct.lib"
	-@erase "$(OUTDIR)\vcacct.pdb"
	-@erase "Account.h"
	-@erase "Account.tlb"
	-@erase "Account_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_MBCS" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Account.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Account.sbr" \
	"$(INTDIR)\CAccount.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Account.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib odbc32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\vcacct.pdb" /debug /machine:$(CPU) /nodefaultlib:"msvcrt.lib" /def:".\Account.def" /out:"$(OUTDIR)\vcacct.dll" /implib:"$(OUTDIR)\vcacct.lib" 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.obj" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Account.res"

"$(OUTDIR)\vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

OUTDIR=.\AlphaRelease
INTDIR=.\AlphaRelease
# Begin Custom Macros
OutDir=.\AlphaRelease
# End Custom Macros

ALL : ".\Account_i.c" ".\Account.tlb" ".\Account.h" "$(OUTDIR)\Vcacct.dll"


CLEAN :
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(OUTDIR)\Vcacct.dll"
	-@erase "$(OUTDIR)\Vcacct.exp"
	-@erase "$(OUTDIR)\Vcacct.lib"
	-@erase "Account.h"
	-@erase "Account.tlb"
	-@erase "Account_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Account.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mtxguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Vcacct.pdb" /machine:ALPHA /def:".\Account.def" /out:"$(OUTDIR)\Vcacct.dll" /implib:"$(OUTDIR)\Vcacct.lib" 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.res"

"$(OUTDIR)\Vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

OUTDIR=.\AlphaDebug
INTDIR=.\AlphaDebug
# Begin Custom Macros
OutDir=.\AlphaDebug
# End Custom Macros

ALL : ".\Account_i.c" ".\Account.tlb" ".\Account.h" "$(OUTDIR)\Vcacct.dll"


CLEAN :
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(OUTDIR)\Vcacct.dll"
	-@erase "$(OUTDIR)\Vcacct.exp"
	-@erase "$(OUTDIR)\Vcacct.ilk"
	-@erase "$(OUTDIR)\Vcacct.lib"
	-@erase "$(OUTDIR)\Vcacct.pdb"
	-@erase "Account.h"
	-@erase "Account.tlb"
	-@erase "Account_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Account.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mtxguid.lib mtx.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Vcacct.pdb" /debug /machine:ALPHA /def:".\Account.def" /out:"$(OUTDIR)\Vcacct.dll" /implib:"$(OUTDIR)\Vcacct.lib" 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.res"

"$(OUTDIR)\Vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Vcacct.dll" "$(OUTDIR)\Account.bsc"


CLEAN :
	-@erase "$(INTDIR)\Account.obj"
	-@erase "$(INTDIR)\Account.pch"
	-@erase "$(INTDIR)\Account.res"
	-@erase "$(INTDIR)\Account.sbr"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\CAccount.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Account.bsc"
	-@erase "$(OUTDIR)\Vcacct.dll"
	-@erase "$(OUTDIR)\Vcacct.exp"
	-@erase "$(OUTDIR)\Vcacct.ilk"
	-@erase "$(OUTDIR)\Vcacct.lib"
	-@erase "$(OUTDIR)\Vcacct.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Account.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Account.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Account.sbr" \
	"$(INTDIR)\CAccount.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Account.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib odbc32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Vcacct.pdb" /debug /machine:$(CPU) /nodefaultlib:"msvcrt.lib" /def:".\Account.def" /out:"$(OUTDIR)\Vcacct.dll" /implib:"$(OUTDIR)\Vcacct.lib" 
DEF_FILE= \
	".\Account.def"
LINK32_OBJS= \
	"$(INTDIR)\Account.obj" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Account.res"

"$(OUTDIR)\Vcacct.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Account.dep")
!INCLUDE "Account.dep"
!ELSE 
!MESSAGE Warning: cannot find "Account.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Account - Win32 Release" || "$(CFG)" == "Account - Win32 Unicode Release" || "$(CFG)" == "Account - Win32 Unicode Debug" || "$(CFG)" == "Account - Win32 Alpha Release" || "$(CFG)" == "Account - Win32 Alpha Debug" || "$(CFG)" == "Account - Win32 Debug"
SOURCE=.\Account.cpp

!IF  "$(CFG)" == "Account - Win32 Release"


"$(INTDIR)\Account.obj"	"$(INTDIR)\Account.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Account.pch" ".\Account.h" ".\Account_i.c"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"


"$(INTDIR)\Account.obj"	"$(INTDIR)\Account.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Account.pch" ".\Account.h" ".\Account_i.c"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"


"$(INTDIR)\Account.obj"	"$(INTDIR)\Account.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Account.pch" ".\Account.h" ".\Account_i.c"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"


"$(INTDIR)\Account.obj"	"$(INTDIR)\Account.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Account.pch" ".\Account.h" ".\Account_i.c"


!ENDIF 

SOURCE=.\Account.idl

!IF  "$(CFG)" == "Account - Win32 Release"

InputPath=.\Account.idl

".\Account.tlb"	".\Account.h"	".\Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl Account.idl
<< 
	

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

InputPath=.\Account.idl

".\Account.tlb"	".\Account.h"	".\Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl Account.idl
<< 
	

!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

InputPath=.\Account.idl

".\Account.tlb"	".\Account.h"	".\Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl Account.idl
<< 
	

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

InputPath=.\Account.idl

".\Account.tlb"	".\Account.h"	".\Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl Account.idl
<< 
	

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

InputPath=.\Account.idl

".\Account.tlb"	".\Account.h"	".\Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl Account.idl
<< 
	

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

InputPath=.\Account.idl

".\Account.tlb"	".\Account.h"	".\Account_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl Account.idl
<< 
	

!ENDIF 

SOURCE=.\Account.rc

"$(INTDIR)\Account.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CAccount.cpp

!IF  "$(CFG)" == "Account - Win32 Release"


"$(INTDIR)\CAccount.obj"	"$(INTDIR)\CAccount.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"


"$(INTDIR)\CAccount.obj"	"$(INTDIR)\CAccount.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"


"$(INTDIR)\CAccount.obj"	"$(INTDIR)\CAccount.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Account.pch" ".\Account.h"


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"


"$(INTDIR)\CAccount.obj"	"$(INTDIR)\CAccount.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Account.pch" ".\Account.h"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Account - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /Zi /O2 /Ob2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Account.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "_MBCS" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Account.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Account - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_MBCS" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Account.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Release"

!ELSEIF  "$(CFG)" == "Account - Win32 Alpha Debug"

!ELSEIF  "$(CFG)" == "Account - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Account.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

