!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on tServer.dsp
!IF "$(CFG)" == ""
CFG=tServer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to tServer - Win32 Alpha Debug.
!ENDIF 

!IF "$(CFG)" != "tServer - Win32 Debug" && "$(CFG)" !=\
 "tServer - Win32 Unicode Debug" && "$(CFG)" !=\
 "tServer - Win32 Release MinDependency" && "$(CFG)" !=\
 "tServer - Win32 Unicode Release MinDependency" && "$(CFG)" !=\
 "tServer - Win32 Alpha Release MinDependency" && "$(CFG)" !=\
 "tServer - Win32 Alpha Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tServer.mak" CFG="tServer - Win32 Alpha Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tServer - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "tServer - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "tServer - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "tServer - Win32 Alpha Release MinDependency" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "tServer - Win32 Alpha Debug" (based on\
 "Win32 (ALPHA) Dynamic-Link Library")
!MESSAGE "tServer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "tServer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\tServer.dll" "$(OUTDIR)\tServer.bsc"

!ELSE 

ALL : "$(OUTDIR)\tServer.dll" "$(OUTDIR)\tServer.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Computer.obj"
	-@erase "$(INTDIR)\Computer.sbr"
	-@erase "$(INTDIR)\Human.obj"
	-@erase "$(INTDIR)\Human.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\tServer.obj"
	-@erase "$(INTDIR)\tServer.pch"
	-@erase "$(INTDIR)\tServer.res"
	-@erase "$(INTDIR)\tServer.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\tServer.bsc"
	-@erase "$(OUTDIR)\tServer.dll"
	-@erase "$(OUTDIR)\tServer.exp"
	-@erase "$(OUTDIR)\tServer.ilk"
	-@erase "$(OUTDIR)\tServer.lib"
	-@erase "$(OUTDIR)\tServer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tServer.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\tServer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Computer.sbr" \
	"$(INTDIR)\Human.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\tServer.sbr"

"$(OUTDIR)\tServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\tServer.pdb" /debug /machine:$(CPU) /nodefaultlib:"msvcrt.lib"\
 /def:".\tServer.def" /out:"$(OUTDIR)\tServer.dll"\
 /implib:"$(OUTDIR)\tServer.lib" /pdbtype:sept 
DEF_FILE= \
	".\tServer.def"
LINK32_OBJS= \
	"$(INTDIR)\Computer.obj" \
	"$(INTDIR)\Human.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tServer.obj" \
	"$(INTDIR)\tServer.res"

"$(OUTDIR)\tServer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\tServer.dll" "$(OUTDIR)\tServer.bsc"

!ELSE 

ALL : "$(OUTDIR)\tServer.dll" "$(OUTDIR)\tServer.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Computer.obj"
	-@erase "$(INTDIR)\Computer.sbr"
	-@erase "$(INTDIR)\Human.obj"
	-@erase "$(INTDIR)\Human.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\tServer.obj"
	-@erase "$(INTDIR)\tServer.pch"
	-@erase "$(INTDIR)\tServer.res"
	-@erase "$(INTDIR)\tServer.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\tServer.bsc"
	-@erase "$(OUTDIR)\tServer.dll"
	-@erase "$(OUTDIR)\tServer.exp"
	-@erase "$(OUTDIR)\tServer.ilk"
	-@erase "$(OUTDIR)\tServer.lib"
	-@erase "$(OUTDIR)\tServer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tServer.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\DebugU/

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\tServer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Computer.sbr" \
	"$(INTDIR)\Human.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\tServer.sbr"

"$(OUTDIR)\tServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\tServer.pdb" /debug /machine:$(CPU) /nodefaultlib:"msvcrt.lib"\
 /def:".\tServer.def" /out:"$(OUTDIR)\tServer.dll"\
 /implib:"$(OUTDIR)\tServer.lib" /pdbtype:sept 
DEF_FILE= \
	".\tServer.def"
LINK32_OBJS= \
	"$(INTDIR)\Computer.obj" \
	"$(INTDIR)\Human.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tServer.obj" \
	"$(INTDIR)\tServer.res"

"$(OUTDIR)\tServer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tServer - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\tServer.dll" "$(OUTDIR)\tServer.bsc"

!ELSE 

ALL : "$(OUTDIR)\tServer.dll" "$(OUTDIR)\tServer.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Computer.obj"
	-@erase "$(INTDIR)\Computer.sbr"
	-@erase "$(INTDIR)\Human.obj"
	-@erase "$(INTDIR)\Human.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\tServer.obj"
	-@erase "$(INTDIR)\tServer.pch"
	-@erase "$(INTDIR)\tServer.res"
	-@erase "$(INTDIR)\tServer.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\tServer.bsc"
	-@erase "$(OUTDIR)\tServer.dll"
	-@erase "$(OUTDIR)\tServer.exp"
	-@erase "$(OUTDIR)\tServer.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /Zi /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tServer.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\ReleaseMinDependency/
CPP_SBRS=.\ReleaseMinDependency/

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\tServer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Computer.sbr" \
	"$(INTDIR)\Human.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\tServer.sbr"

"$(OUTDIR)\tServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\tServer.pdb" /machine:$(CPU) /nodefaultlib:"msvcrt.lib"\
 /def:".\tServer.def" /out:"$(OUTDIR)\tServer.dll"\
 /implib:"$(OUTDIR)\tServer.lib" 
DEF_FILE= \
	".\tServer.def"
LINK32_OBJS= \
	"$(INTDIR)\Computer.obj" \
	"$(INTDIR)\Human.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tServer.obj" \
	"$(INTDIR)\tServer.res"

"$(OUTDIR)\tServer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\tServer.dll"

!ELSE 

ALL : "$(OUTDIR)\tServer.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Computer.obj"
	-@erase "$(INTDIR)\Human.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\tServer.obj"
	-@erase "$(INTDIR)\tServer.pch"
	-@erase "$(INTDIR)\tServer.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\tServer.dll"
	-@erase "$(OUTDIR)\tServer.exp"
	-@erase "$(OUTDIR)\tServer.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\tServer.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\ReleaseUMinDependency/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\tServer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\tServer.pdb" /machine:$(CPU) /nodefaultlib:"msvcrt.lib"\
 /def:".\tServer.def" /out:"$(OUTDIR)\tServer.dll"\
 /implib:"$(OUTDIR)\tServer.lib" 
DEF_FILE= \
	".\tServer.def"
LINK32_OBJS= \
	"$(INTDIR)\Computer.obj" \
	"$(INTDIR)\Human.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tServer.obj" \
	"$(INTDIR)\tServer.res"

"$(OUTDIR)\tServer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Release MinDependency"

OUTDIR=.\AlphaRelease
INTDIR=.\AlphaRelease
# Begin Custom Macros
OutDir=.\AlphaRelease
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\tServer.dll" "$(OUTDIR)\tServer.bsc"

!ELSE 

ALL : "$(OUTDIR)\tServer.dll" "$(OUTDIR)\tServer.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Computer.obj"
	-@erase "$(INTDIR)\Computer.sbr"
	-@erase "$(INTDIR)\Human.obj"
	-@erase "$(INTDIR)\Human.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\tServer.obj"
	-@erase "$(INTDIR)\tServer.pch"
	-@erase "$(INTDIR)\tServer.res"
	-@erase "$(INTDIR)\tServer.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\tServer.bsc"
	-@erase "$(OUTDIR)\tServer.dll"
	-@erase "$(OUTDIR)\tServer.exp"
	-@erase "$(OUTDIR)\tServer.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 $(MIDL_OPTIMIZATION)
CPP=cl.exe
CPP_PROJ=/nologo /MT /Gt0 /W3 /GX /Zi /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tServer.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\AlphaRelease/
CPP_SBRS=.\AlphaRelease/

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

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\tServer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Computer.sbr" \
	"$(INTDIR)\Human.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\tServer.sbr"

"$(OUTDIR)\tServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /dll /pdb:"$(OUTDIR)\tServer.pdb" /machine:ALPHA\
 /def:".\tServer.def" /out:"$(OUTDIR)\tServer.dll"\
 /implib:"$(OUTDIR)\tServer.lib" 
DEF_FILE= \
	".\tServer.def"
LINK32_OBJS= \
	"$(INTDIR)\Computer.obj" \
	"$(INTDIR)\Human.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tServer.obj" \
	"$(INTDIR)\tServer.res"

"$(OUTDIR)\tServer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Debug"

OUTDIR=.\AlphaDebug
INTDIR=.\AlphaDebug
# Begin Custom Macros
OutDir=.\AlphaDebug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\tServer.dll" "$(OUTDIR)\tServer.bsc"

!ELSE 

ALL : "$(OUTDIR)\tServer.dll" "$(OUTDIR)\tServer.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Computer.obj"
	-@erase "$(INTDIR)\Computer.sbr"
	-@erase "$(INTDIR)\Human.obj"
	-@erase "$(INTDIR)\Human.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\tServer.obj"
	-@erase "$(INTDIR)\tServer.pch"
	-@erase "$(INTDIR)\tServer.res"
	-@erase "$(INTDIR)\tServer.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\tServer.bsc"
	-@erase "$(OUTDIR)\tServer.dll"
	-@erase "$(OUTDIR)\tServer.exp"
	-@erase "$(OUTDIR)\tServer.lib"
	-@erase "$(OUTDIR)\tServer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 $(MIDL_OPTIMIZATION)
CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tServer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\"   /MTd /c 
CPP_OBJS=.\AlphaDebug/
CPP_SBRS=.\AlphaDebug/

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

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\tServer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tServer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Computer.sbr" \
	"$(INTDIR)\Human.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\tServer.sbr"

"$(OUTDIR)\tServer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /dll /pdb:"$(OUTDIR)\tServer.pdb" /debug /machine:ALPHA\
 /def:".\tServer.def" /out:"$(OUTDIR)\tServer.dll"\
 /implib:"$(OUTDIR)\tServer.lib" /pdbtype:sept 
DEF_FILE= \
	".\tServer.def"
LINK32_OBJS= \
	"$(INTDIR)\Computer.obj" \
	"$(INTDIR)\Human.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\tServer.obj" \
	"$(INTDIR)\tServer.res"

"$(OUTDIR)\tServer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "tServer - Win32 Debug" || "$(CFG)" ==\
 "tServer - Win32 Unicode Debug" || "$(CFG)" ==\
 "tServer - Win32 Release MinDependency" || "$(CFG)" ==\
 "tServer - Win32 Unicode Release MinDependency" || "$(CFG)" ==\
 "tServer - Win32 Alpha Release MinDependency" || "$(CFG)" ==\
 "tServer - Win32 Alpha Debug"
SOURCE=.\Computer.cpp

!IF  "$(CFG)" == "tServer - Win32 Debug"

DEP_CPP_COMPU=\
	".\Computer.h"\
	".\tServer.h"\
	

"$(INTDIR)\Computer.obj"	"$(INTDIR)\Computer.sbr" : $(SOURCE) $(DEP_CPP_COMPU)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Debug"

DEP_CPP_COMPU=\
	".\Computer.h"\
	".\tServer.h"\
	

"$(INTDIR)\Computer.obj"	"$(INTDIR)\Computer.sbr" : $(SOURCE) $(DEP_CPP_COMPU)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Release MinDependency"

DEP_CPP_COMPU=\
	".\Computer.h"\
	".\tServer.h"\
	

"$(INTDIR)\Computer.obj"	"$(INTDIR)\Computer.sbr" : $(SOURCE) $(DEP_CPP_COMPU)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Release MinDependency"

DEP_CPP_COMPU=\
	".\Computer.h"\
	".\tServer.h"\
	

"$(INTDIR)\Computer.obj" : $(SOURCE) $(DEP_CPP_COMPU) "$(INTDIR)"\
 "$(INTDIR)\tServer.pch" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Release MinDependency"

DEP_CPP_COMPU=\
	".\Computer.h"\
	".\StdAfx.h"\
	".\tServer.h"\
	

"$(INTDIR)\Computer.obj"	"$(INTDIR)\Computer.sbr" : $(SOURCE) $(DEP_CPP_COMPU)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Debug"

DEP_CPP_COMPU=\
	".\Computer.h"\
	".\StdAfx.h"\
	".\tServer.h"\
	

"$(INTDIR)\Computer.obj"	"$(INTDIR)\Computer.sbr" : $(SOURCE) $(DEP_CPP_COMPU)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h"


!ENDIF 

SOURCE=.\Human.cpp

!IF  "$(CFG)" == "tServer - Win32 Debug"

DEP_CPP_HUMAN=\
	".\Human.h"\
	".\tServer.h"\
	

"$(INTDIR)\Human.obj"	"$(INTDIR)\Human.sbr" : $(SOURCE) $(DEP_CPP_HUMAN)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Debug"

DEP_CPP_HUMAN=\
	".\Human.h"\
	".\tServer.h"\
	

"$(INTDIR)\Human.obj"	"$(INTDIR)\Human.sbr" : $(SOURCE) $(DEP_CPP_HUMAN)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Release MinDependency"

DEP_CPP_HUMAN=\
	".\Human.h"\
	".\tServer.h"\
	

"$(INTDIR)\Human.obj"	"$(INTDIR)\Human.sbr" : $(SOURCE) $(DEP_CPP_HUMAN)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Release MinDependency"

DEP_CPP_HUMAN=\
	".\Human.h"\
	".\tServer.h"\
	

"$(INTDIR)\Human.obj" : $(SOURCE) $(DEP_CPP_HUMAN) "$(INTDIR)"\
 "$(INTDIR)\tServer.pch" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Release MinDependency"

DEP_CPP_HUMAN=\
	".\Human.h"\
	".\StdAfx.h"\
	".\tServer.h"\
	

"$(INTDIR)\Human.obj"	"$(INTDIR)\Human.sbr" : $(SOURCE) $(DEP_CPP_HUMAN)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Debug"

DEP_CPP_HUMAN=\
	".\Human.h"\
	".\StdAfx.h"\
	".\tServer.h"\
	

"$(INTDIR)\Human.obj"	"$(INTDIR)\Human.sbr" : $(SOURCE) $(DEP_CPP_HUMAN)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "tServer - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tServer.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\tServer.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\tServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  \
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\tServer.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "tServer - Win32 Release MinDependency"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /GX /Zi /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tServer.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\tServer.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Release MinDependency"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\tServer.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\tServer.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Release MinDependency"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /Gt0 /W3 /GX /Zi /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tServer.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\tServer.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\tServer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\"   /MTd /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\tServer.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\tServer.cpp

!IF  "$(CFG)" == "tServer - Win32 Debug"

DEP_CPP_TSERV=\
	".\Computer.h"\
	".\Human.h"\
	".\tServer.h"\
	".\tServer_i.c"\
	

"$(INTDIR)\tServer.obj"	"$(INTDIR)\tServer.sbr" : $(SOURCE) $(DEP_CPP_TSERV)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer_i.c" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Debug"

DEP_CPP_TSERV=\
	".\Computer.h"\
	".\Human.h"\
	".\tServer.h"\
	".\tServer_i.c"\
	

"$(INTDIR)\tServer.obj"	"$(INTDIR)\tServer.sbr" : $(SOURCE) $(DEP_CPP_TSERV)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer_i.c" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Release MinDependency"

DEP_CPP_TSERV=\
	".\Computer.h"\
	".\Human.h"\
	".\tServer.h"\
	".\tServer_i.c"\
	

"$(INTDIR)\tServer.obj"	"$(INTDIR)\tServer.sbr" : $(SOURCE) $(DEP_CPP_TSERV)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer_i.c" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Release MinDependency"

DEP_CPP_TSERV=\
	".\Computer.h"\
	".\Human.h"\
	".\tServer.h"\
	".\tServer_i.c"\
	

"$(INTDIR)\tServer.obj" : $(SOURCE) $(DEP_CPP_TSERV) "$(INTDIR)"\
 "$(INTDIR)\tServer.pch" ".\tServer_i.c" ".\tServer.h"


!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Release MinDependency"

DEP_CPP_TSERV=\
	".\Computer.h"\
	".\Human.h"\
	".\StdAfx.h"\
	".\tServer.h"\
	".\tServer_i.c"\
	

"$(INTDIR)\tServer.obj"	"$(INTDIR)\tServer.sbr" : $(SOURCE) $(DEP_CPP_TSERV)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h" ".\tServer_i.c"


!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Debug"

DEP_CPP_TSERV=\
	".\Computer.h"\
	".\Human.h"\
	".\StdAfx.h"\
	".\tServer.h"\
	".\tServer_i.c"\
	

"$(INTDIR)\tServer.obj"	"$(INTDIR)\tServer.sbr" : $(SOURCE) $(DEP_CPP_TSERV)\
 "$(INTDIR)" "$(INTDIR)\tServer.pch" ".\tServer.h" ".\tServer_i.c"


!ENDIF 

SOURCE=.\tServer.idl

!IF  "$(CFG)" == "tServer - Win32 Debug"

InputPath=.\tServer.idl

".\tServer.tlb"	".\tServer.h"	".\tServer_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "tServer.h" /iid "tServer_i.c" "tServer.idl"

!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Debug"

InputPath=.\tServer.idl

".\tServer.tlb"	".\tServer.h"	".\tServer_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "tServer.h" /iid "tServer_i.c" "tServer.idl"

!ELSEIF  "$(CFG)" == "tServer - Win32 Release MinDependency"

InputPath=.\tServer.idl

".\tServer.tlb"	".\tServer.h"	".\tServer_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "tServer.h" /iid "tServer_i.c" "tServer.idl"

!ELSEIF  "$(CFG)" == "tServer - Win32 Unicode Release MinDependency"

InputPath=.\tServer.idl

".\tServer.tlb"	".\tServer.h"	".\tServer_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "tServer.h" /iid "tServer_i.c" "tServer.idl"

!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Release MinDependency"

InputPath=.\tServer.idl

".\tServer.tlb"	".\tServer.h"	".\tServer_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "tServer.h" /iid "tServer_i.c" "tServer.idl"

!ELSEIF  "$(CFG)" == "tServer - Win32 Alpha Debug"

InputPath=.\tServer.idl

".\tServer.tlb"	".\tServer.h"	".\tServer_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "tServer.h" /iid "tServer_i.c" "tServer.idl"

!ENDIF 

SOURCE=.\tServer.rc
DEP_RSC_TSERVE=\
	".\computer.bin"\
	".\Computer.rgs"\
	".\human.bin"\
	".\Human.rgs"\
	".\tServer.tlb"\
	

"$(INTDIR)\tServer.res" : $(SOURCE) $(DEP_RSC_TSERVE) "$(INTDIR)"\
 ".\tServer.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

