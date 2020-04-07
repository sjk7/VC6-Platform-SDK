!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on VCSecuritySample.dsp
!IF "$(CFG)" == ""
CFG=VCSecuritySample - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VCSecuritySample - Win32\
 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "VCSecuritySample - Win32 Debug" && "$(CFG)" !=\
 "VCSecuritySample - Win32 Unicode Debug" && "$(CFG)" !=\
 "VCSecuritySample - Win32 Release MinSize" && "$(CFG)" !=\
 "VCSecuritySample - Win32 Release MinDependency" && "$(CFG)" !=\
 "VCSecuritySample - Win32 Unicode Release MinSize" && "$(CFG)" !=\
 "VCSecuritySample - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCSecuritySample.mak" CFG="VCSecuritySample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VCSecuritySample - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VCSecuritySample - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VCSecuritySample - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VCSecuritySample - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VCSecuritySample - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VCSecuritySample - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "VCSecuritySample - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\VCSecuritySample.obj"
	-@erase "$(INTDIR)\VCSecuritySample.pch"
	-@erase "$(INTDIR)\VCSecuritySample.res"
	-@erase "$(INTDIR)\VCSecuritySampleClass.obj"
	-@erase "$(OUTDIR)\VCSecuritySample.dll"
	-@erase "$(OUTDIR)\VCSecuritySample.exp"
	-@erase "$(OUTDIR)\VCSecuritySample.ilk"
	-@erase "$(OUTDIR)\VCSecuritySample.lib"
	-@erase "$(OUTDIR)\VCSecuritySample.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\VCSecuritySample.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VCSecuritySample.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCSecuritySample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\VCSecuritySample.pdb" /debug /machine:$(mach_type)\
 /def:".\VCSecuritySample.def" /out:"$(OUTDIR)\VCSecuritySample.dll"\
 /implib:"$(OUTDIR)\VCSecuritySample.lib" /pdbtype:sept 
DEF_FILE= \
	".\VCSecuritySample.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VCSecuritySample.obj" \
	"$(INTDIR)\VCSecuritySample.res" \
	"$(INTDIR)\VCSecuritySampleClass.obj"

"$(OUTDIR)\VCSecuritySample.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\VCSecuritySample.dll
InputPath=.\Debug\VCSecuritySample.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\VCSecuritySample.obj"
	-@erase "$(INTDIR)\VCSecuritySample.pch"
	-@erase "$(INTDIR)\VCSecuritySample.res"
	-@erase "$(INTDIR)\VCSecuritySampleClass.obj"
	-@erase "$(OUTDIR)\VCSecuritySample.dll"
	-@erase "$(OUTDIR)\VCSecuritySample.exp"
	-@erase "$(OUTDIR)\VCSecuritySample.ilk"
	-@erase "$(OUTDIR)\VCSecuritySample.lib"
	-@erase "$(OUTDIR)\VCSecuritySample.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\VCSecuritySample.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VCSecuritySample.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCSecuritySample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\VCSecuritySample.pdb" /debug /machine:$(mach_type)\
 /def:".\VCSecuritySample.def" /out:"$(OUTDIR)\VCSecuritySample.dll"\
 /implib:"$(OUTDIR)\VCSecuritySample.lib" /pdbtype:sept 
DEF_FILE= \
	".\VCSecuritySample.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VCSecuritySample.obj" \
	"$(INTDIR)\VCSecuritySample.res" \
	"$(INTDIR)\VCSecuritySampleClass.obj"

"$(OUTDIR)\VCSecuritySample.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\VCSecuritySample.dll
InputPath=.\DebugU\VCSecuritySample.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\VCSecuritySample.obj"
	-@erase "$(INTDIR)\VCSecuritySample.pch"
	-@erase "$(INTDIR)\VCSecuritySample.res"
	-@erase "$(INTDIR)\VCSecuritySampleClass.obj"
	-@erase "$(OUTDIR)\VCSecuritySample.dll"
	-@erase "$(OUTDIR)\VCSecuritySample.exp"
	-@erase "$(OUTDIR)\VCSecuritySample.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\VCSecuritySample.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\ReleaseMinSize/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VCSecuritySample.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCSecuritySample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\VCSecuritySample.pdb" /machine:$(mach_type)\
 /def:".\VCSecuritySample.def" /out:"$(OUTDIR)\VCSecuritySample.dll"\
 /implib:"$(OUTDIR)\VCSecuritySample.lib" 
DEF_FILE= \
	".\VCSecuritySample.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VCSecuritySample.obj" \
	"$(INTDIR)\VCSecuritySample.res" \
	"$(INTDIR)\VCSecuritySampleClass.obj"

"$(OUTDIR)\VCSecuritySample.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\VCSecuritySample.dll
InputPath=.\ReleaseMinSize\VCSecuritySample.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\VCSecuritySample.obj"
	-@erase "$(INTDIR)\VCSecuritySample.pch"
	-@erase "$(INTDIR)\VCSecuritySample.res"
	-@erase "$(INTDIR)\VCSecuritySampleClass.obj"
	-@erase "$(OUTDIR)\VCSecuritySample.dll"
	-@erase "$(OUTDIR)\VCSecuritySample.exp"
	-@erase "$(OUTDIR)\VCSecuritySample.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\VCSecuritySample.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\ReleaseMinDependency/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VCSecuritySample.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCSecuritySample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\VCSecuritySample.pdb" /machine:$(mach_type)\
 /def:".\VCSecuritySample.def" /out:"$(OUTDIR)\VCSecuritySample.dll"\
 /implib:"$(OUTDIR)\VCSecuritySample.lib" 
DEF_FILE= \
	".\VCSecuritySample.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VCSecuritySample.obj" \
	"$(INTDIR)\VCSecuritySample.res" \
	"$(INTDIR)\VCSecuritySampleClass.obj"

"$(OUTDIR)\VCSecuritySample.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\VCSecuritySample.dll
InputPath=.\ReleaseMinDependency\VCSecuritySample.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\VCSecuritySample.obj"
	-@erase "$(INTDIR)\VCSecuritySample.pch"
	-@erase "$(INTDIR)\VCSecuritySample.res"
	-@erase "$(INTDIR)\VCSecuritySampleClass.obj"
	-@erase "$(OUTDIR)\VCSecuritySample.dll"
	-@erase "$(OUTDIR)\VCSecuritySample.exp"
	-@erase "$(OUTDIR)\VCSecuritySample.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\VCSecuritySample.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\ReleaseUMinSize/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VCSecuritySample.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCSecuritySample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mtxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\VCSecuritySample.pdb" /machine:$(mach_type)\
 /def:".\VCSecuritySample.def" /out:"$(OUTDIR)\VCSecuritySample.dll"\
 /implib:"$(OUTDIR)\VCSecuritySample.lib" 
DEF_FILE= \
	".\VCSecuritySample.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VCSecuritySample.obj" \
	"$(INTDIR)\VCSecuritySample.res" \
	"$(INTDIR)\VCSecuritySampleClass.obj"

"$(OUTDIR)\VCSecuritySample.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\VCSecuritySample.dll
InputPath=.\ReleaseUMinSize\VCSecuritySample.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\VCSecuritySample.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\VCSecuritySample.obj"
	-@erase "$(INTDIR)\VCSecuritySample.pch"
	-@erase "$(INTDIR)\VCSecuritySample.res"
	-@erase "$(INTDIR)\VCSecuritySampleClass.obj"
	-@erase "$(OUTDIR)\VCSecuritySample.dll"
	-@erase "$(OUTDIR)\VCSecuritySample.exp"
	-@erase "$(OUTDIR)\VCSecuritySample.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\VCSecuritySample.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\"   /c 
CPP_OBJS=.\ReleaseUMinDependency/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 $(MIDL_OPTIMIZATION)
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VCSecuritySample.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCSecuritySample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\VCSecuritySample.pdb" /machine:$(mach_type)\
 /def:".\VCSecuritySample.def" /out:"$(OUTDIR)\VCSecuritySample.dll"\
 /implib:"$(OUTDIR)\VCSecuritySample.lib" 
DEF_FILE= \
	".\VCSecuritySample.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VCSecuritySample.obj" \
	"$(INTDIR)\VCSecuritySample.res" \
	"$(INTDIR)\VCSecuritySampleClass.obj"

"$(OUTDIR)\VCSecuritySample.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\VCSecuritySample.dll
InputPath=.\ReleaseUMinDependency\VCSecuritySample.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

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


!IF "$(CFG)" == "VCSecuritySample - Win32 Debug" || "$(CFG)" ==\
 "VCSecuritySample - Win32 Unicode Debug" || "$(CFG)" ==\
 "VCSecuritySample - Win32 Release MinSize" || "$(CFG)" ==\
 "VCSecuritySample - Win32 Release MinDependency" || "$(CFG)" ==\
 "VCSecuritySample - Win32 Unicode Release MinSize" || "$(CFG)" ==\
 "VCSecuritySample - Win32 Unicode Release MinDependency"
SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "VCSecuritySample - Win32 Debug"

DEP_CPP_STDAF=\
	"..\..\..\..\..\include\basetsd.h"\
	"..\..\..\..\..\include\msxml.h"\
	"..\..\..\..\..\include\propidl.h"\
	"..\..\..\..\..\include\qos.h"\
	"..\..\..\..\..\include\rpcasync.h"\
	"..\..\..\..\..\include\winefs.h"\
	"..\..\..\..\..\include\winscard.h"\
	"..\..\..\..\..\include\winsmcrd.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\VCSecuritySample.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCSecuritySample.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\VCSecuritySample.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCSecuritySample.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Release MinSize"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\VCSecuritySample.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCSecuritySample.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Release MinDependency"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\VCSecuritySample.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCSecuritySample.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Release MinSize"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\VCSecuritySample.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCSecuritySample.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Release MinDependency"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\VCSecuritySample.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCSecuritySample.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\VCSecuritySample.cpp

!IF  "$(CFG)" == "VCSecuritySample - Win32 Debug"

DEP_CPP_VCSEC=\
	".\VCSecuritySample.h"\
	".\VCSecuritySample_i.c"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySample.obj" : $(SOURCE) $(DEP_CPP_VCSEC) "$(INTDIR)"\
 "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample_i.c"\
 ".\VCSecuritySample.h"


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Debug"

DEP_CPP_VCSEC=\
	".\StdAfx.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySample_i.c"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySample.obj" : $(SOURCE) $(DEP_CPP_VCSEC) "$(INTDIR)"\
 "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"\
 ".\VCSecuritySample_i.c"


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Release MinSize"

DEP_CPP_VCSEC=\
	".\StdAfx.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySample_i.c"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySample.obj" : $(SOURCE) $(DEP_CPP_VCSEC) "$(INTDIR)"\
 "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"\
 ".\VCSecuritySample_i.c"


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Release MinDependency"

DEP_CPP_VCSEC=\
	".\StdAfx.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySample_i.c"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySample.obj" : $(SOURCE) $(DEP_CPP_VCSEC) "$(INTDIR)"\
 "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"\
 ".\VCSecuritySample_i.c"


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Release MinSize"

DEP_CPP_VCSEC=\
	".\StdAfx.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySample_i.c"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySample.obj" : $(SOURCE) $(DEP_CPP_VCSEC) "$(INTDIR)"\
 "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"\
 ".\VCSecuritySample_i.c"


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Release MinDependency"

DEP_CPP_VCSEC=\
	".\StdAfx.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySample_i.c"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySample.obj" : $(SOURCE) $(DEP_CPP_VCSEC) "$(INTDIR)"\
 "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"\
 ".\VCSecuritySample_i.c"


!ENDIF 

SOURCE=.\VCSecuritySample.idl

!IF  "$(CFG)" == "VCSecuritySample - Win32 Debug"

InputPath=.\VCSecuritySample.idl

".\VCSecuritySample.tlb"	".\VCSecuritySample.h"	".\VCSecuritySample_i.c"	 : \
$(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "VCSecuritySample.h" /iid "VCSecuritySample_i.c"\
    "VCSecuritySample.idl"

!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Debug"

InputPath=.\VCSecuritySample.idl

".\VCSecuritySample.tlb"	".\VCSecuritySample.h"	".\VCSecuritySample_i.c"	 : \
$(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "VCSecuritySample.h" /iid "VCSecuritySample_i.c"\
    "VCSecuritySample.idl"

!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Release MinSize"

InputPath=.\VCSecuritySample.idl

".\VCSecuritySample.tlb"	".\VCSecuritySample.h"	".\VCSecuritySample_i.c"	 : \
$(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "VCSecuritySample.h" /iid "VCSecuritySample_i.c"\
    "VCSecuritySample.idl"

!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Release MinDependency"

InputPath=.\VCSecuritySample.idl

".\VCSecuritySample.tlb"	".\VCSecuritySample.h"	".\VCSecuritySample_i.c"	 : \
$(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "VCSecuritySample.h" /iid "VCSecuritySample_i.c"\
    "VCSecuritySample.idl"

!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Release MinSize"

InputPath=.\VCSecuritySample.idl

".\VCSecuritySample.tlb"	".\VCSecuritySample.h"	".\VCSecuritySample_i.c"	 : \
$(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "VCSecuritySample.h" /iid "VCSecuritySample_i.c"\
    "VCSecuritySample.idl"

!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Release MinDependency"

InputPath=.\VCSecuritySample.idl

".\VCSecuritySample.tlb"	".\VCSecuritySample.h"	".\VCSecuritySample_i.c"	 : \
$(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "VCSecuritySample.h" /iid "VCSecuritySample_i.c"\
    "VCSecuritySample.idl"

!ENDIF 

SOURCE=.\VCSecuritySample.rc
DEP_RSC_VCSECU=\
	".\VCSecuritySample.tlb"\
	".\VCSecuritySampleClass.rgs"\
	

"$(INTDIR)\VCSecuritySample.res" : $(SOURCE) $(DEP_RSC_VCSECU) "$(INTDIR)"\
 ".\VCSecuritySample.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\VCSecuritySampleClass.cpp

!IF  "$(CFG)" == "VCSecuritySample - Win32 Debug"

DEP_CPP_VCSECUR=\
	"..\..\..\..\..\include\comsvcs.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySampleClass.obj" : $(SOURCE) $(DEP_CPP_VCSECUR)\
 "$(INTDIR)" "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Debug"

DEP_CPP_VCSECUR=\
	".\StdAfx.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySampleClass.obj" : $(SOURCE) $(DEP_CPP_VCSECUR)\
 "$(INTDIR)" "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Release MinSize"

DEP_CPP_VCSECUR=\
	".\StdAfx.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySampleClass.obj" : $(SOURCE) $(DEP_CPP_VCSECUR)\
 "$(INTDIR)" "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Release MinDependency"

DEP_CPP_VCSECUR=\
	".\StdAfx.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySampleClass.obj" : $(SOURCE) $(DEP_CPP_VCSECUR)\
 "$(INTDIR)" "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Release MinSize"

DEP_CPP_VCSECUR=\
	".\StdAfx.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySampleClass.obj" : $(SOURCE) $(DEP_CPP_VCSECUR)\
 "$(INTDIR)" "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"


!ELSEIF  "$(CFG)" == "VCSecuritySample - Win32 Unicode Release MinDependency"

DEP_CPP_VCSECUR=\
	".\StdAfx.h"\
	".\VCSecuritySample.h"\
	".\VCSecuritySampleClass.h"\
	

"$(INTDIR)\VCSecuritySampleClass.obj" : $(SOURCE) $(DEP_CPP_VCSECUR)\
 "$(INTDIR)" "$(INTDIR)\VCSecuritySample.pch" ".\VCSecuritySample.h"


!ENDIF 


!ENDIF 

