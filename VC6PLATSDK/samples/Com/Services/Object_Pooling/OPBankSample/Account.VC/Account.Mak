# Microsoft Developer Studio Generated NMAKE File, Based on account.dsp
!IF "$(CFG)" == ""
CFG=account - Win32 Debug
!MESSAGE No configuration specified. Defaulting to account - Win32 Debug.
!ENDIF

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF 

!IF "$(CFG)" != "account - Win32 Debug" && "$(CFG)" !=\
 "account - Win32 Unicode Debug" && "$(CFG)" !=\
 "account - Win32 Release MinSize" && "$(CFG)" !=\
 "account - Win32 Release MinDependency" && "$(CFG)" !=\
 "account - Win32 Unicode Release MinSize" && "$(CFG)" !=\
 "account - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "account.mak" CFG="account - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "account - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "account - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "account - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "account - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "account - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "account - Win32 Unicode Release MinDependency" (based on\
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

!IF  "$(CFG)" == "account - Win32 Debug"

OUTDIR=.\account_
INTDIR=.\account_
# Begin Custom Macros
OutDir=.\account_
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\account.dll" "$(OUTDIR)\account.pch" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\account.dll" "$(OUTDIR)\account.pch" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\account.res"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\GetRec.obj"
	-@erase "$(INTDIR)\mvmoney.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UpdRec.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\account.dll"
	-@erase "$(OUTDIR)\account.exp"
	-@erase "$(OUTDIR)\account.ilk"
	-@erase "$(OUTDIR)\account.lib"
	-@erase "$(OUTDIR)\account.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /I "..\..\..\..\..\..\include"\
 /FI"unicode.h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\account_/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\account.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\account.pdb" /debug /machine:$(mach_type) /def:".\vcacct.def"\
 /out:"$(OUTDIR)\account.dll" /implib:"$(OUTDIR)\account.lib" /pdbtype:sept 
DEF_FILE= \
	".\vcacct.def"
LINK32_OBJS= \
	"$(INTDIR)\account.obj" \
	"$(INTDIR)\account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetRec.obj" \
	"$(INTDIR)\mvmoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdRec.obj"

"$(OUTDIR)\account.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\account_
TargetPath=.\account_\account.dll
InputPath=.\account_\account.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "account - Win32 Unicode Debug"

OUTDIR=.\account_U
INTDIR=.\account_U
# Begin Custom Macros
OutDir=.\account_U
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\account.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\account.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\account.res"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\GetRec.obj"
	-@erase "$(INTDIR)\mvmoney.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UpdRec.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\account.dll"
	-@erase "$(OUTDIR)\account.exp"
	-@erase "$(OUTDIR)\account.ilk"
	-@erase "$(OUTDIR)\account.lib"
	-@erase "$(OUTDIR)\account.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\account_U/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\account.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\account.pdb" /debug /machine:$(mach_type) /def:".\vcacct.def"\
 /out:"$(OUTDIR)\account.dll" /implib:"$(OUTDIR)\account.lib" /pdbtype:sept 
DEF_FILE= \
	".\vcacct.def"
LINK32_OBJS= \
	"$(INTDIR)\account.obj" \
	"$(INTDIR)\account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetRec.obj" \
	"$(INTDIR)\mvmoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdRec.obj"

"$(OUTDIR)\account.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\account_U
TargetPath=.\account_U\account.dll
InputPath=.\account_U\account.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "account - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\account.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\account.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\account.res"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\GetRec.obj"
	-@erase "$(INTDIR)\mvmoney.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UpdRec.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\account.dll"
	-@erase "$(OUTDIR)\account.exp"
	-@erase "$(OUTDIR)\account.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /FI"unicode.h" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\ReleaseMinSize/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\account.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\account.pdb" /machine:$(mach_type) /def:".\vcacct.def"\
 /out:"$(OUTDIR)\account.dll" /implib:"$(OUTDIR)\account.lib" 
DEF_FILE= \
	".\vcacct.def"
LINK32_OBJS= \
	"$(INTDIR)\account.obj" \
	"$(INTDIR)\account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetRec.obj" \
	"$(INTDIR)\mvmoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdRec.obj"

"$(OUTDIR)\account.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\account.dll
InputPath=.\ReleaseMinSize\account.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "account - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\account.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\account.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\account.res"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\GetRec.obj"
	-@erase "$(INTDIR)\mvmoney.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UpdRec.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\account.dll"
	-@erase "$(OUTDIR)\account.exp"
	-@erase "$(OUTDIR)\account.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /FI"unicode.h" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\ReleaseMinDependency/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\account.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\account.pdb" /machine:$(mach_type) /def:".\vcacct.def"\
 /out:"$(OUTDIR)\account.dll" /implib:"$(OUTDIR)\account.lib" 
DEF_FILE= \
	".\vcacct.def"
LINK32_OBJS= \
	"$(INTDIR)\account.obj" \
	"$(INTDIR)\account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetRec.obj" \
	"$(INTDIR)\mvmoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdRec.obj"

"$(OUTDIR)\account.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\account.dll
InputPath=.\ReleaseMinDependency\account.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\account.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\account.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\account.res"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\GetRec.obj"
	-@erase "$(INTDIR)\mvmoney.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UpdRec.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\account.dll"
	-@erase "$(OUTDIR)\account.exp"
	-@erase "$(OUTDIR)\account.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /FI"unicode.h" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\ReleaseUMinSize/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\account.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\account.pdb" /machine:$(mach_type) /def:".\vcacct.def"\
 /out:"$(OUTDIR)\account.dll" /implib:"$(OUTDIR)\account.lib" 
DEF_FILE= \
	".\vcacct.def"
LINK32_OBJS= \
	"$(INTDIR)\account.obj" \
	"$(INTDIR)\account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetRec.obj" \
	"$(INTDIR)\mvmoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdRec.obj"

"$(OUTDIR)\account.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\account.dll
InputPath=.\ReleaseUMinSize\account.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\account.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\account.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\account.obj"
	-@erase "$(INTDIR)\account.pch"
	-@erase "$(INTDIR)\account.res"
	-@erase "$(INTDIR)\CAccount.obj"
	-@erase "$(INTDIR)\GetRec.obj"
	-@erase "$(INTDIR)\mvmoney.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UpdRec.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\account.dll"
	-@erase "$(OUTDIR)\account.exp"
	-@erase "$(OUTDIR)\account.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\account.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\ReleaseUMinDependency/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\account.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\account.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\account.pdb" /machine:$(mach_type) /def:".\vcacct.def"\
 /out:"$(OUTDIR)\account.dll" /implib:"$(OUTDIR)\account.lib" 
DEF_FILE= \
	".\vcacct.def"
LINK32_OBJS= \
	"$(INTDIR)\account.obj" \
	"$(INTDIR)\account.res" \
	"$(INTDIR)\CAccount.obj" \
	"$(INTDIR)\GetRec.obj" \
	"$(INTDIR)\mvmoney.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UpdRec.obj"

"$(OUTDIR)\account.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\account.dll
InputPath=.\ReleaseUMinDependency\account.dll
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


!IF "$(CFG)" == "account - Win32 Debug" || "$(CFG)" ==\
 "account - Win32 Unicode Debug" || "$(CFG)" ==\
 "account - Win32 Release MinSize" || "$(CFG)" ==\
 "account - Win32 Release MinDependency" || "$(CFG)" ==\
 "account - Win32 Unicode Release MinSize" || "$(CFG)" ==\
 "account - Win32 Unicode Release MinDependency"
SOURCE=.\account.cpp

!IF  "$(CFG)" == "account - Win32 Debug"

DEP_CPP_ACCOU=\
	"..\..\..\..\..\..\include\basetsd.h"\
	"..\..\..\..\..\..\include\msxml.h"\
	"..\..\..\..\..\..\include\propidl.h"\
	"..\..\..\..\..\..\include\rpcasync.h"\
	"..\..\..\..\..\..\include\winefs.h"\
	"..\..\..\..\..\..\include\winscard.h"\
	"..\..\..\..\..\..\include\winsmcrd.h"\
	".\account.h"\
	".\account_i.c"\
	".\CAccount.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	".\unicode.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\account.obj" : $(SOURCE) $(DEP_CPP_ACCOU) "$(INTDIR)" ".\account.h"\
 ".\account_i.c"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Debug"

DEP_CPP_ACCOU=\
	".\account.h"\
	".\account_i.c"\
	".\CAccount.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\account.obj" : $(SOURCE) $(DEP_CPP_ACCOU) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h" ".\account_i.c"


!ELSEIF  "$(CFG)" == "account - Win32 Release MinSize"

DEP_CPP_ACCOU=\
	".\account.h"\
	".\account_i.c"\
	".\CAccount.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\account.obj" : $(SOURCE) $(DEP_CPP_ACCOU) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h" ".\account_i.c"


!ELSEIF  "$(CFG)" == "account - Win32 Release MinDependency"

DEP_CPP_ACCOU=\
	".\account.h"\
	".\account_i.c"\
	".\CAccount.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\account.obj" : $(SOURCE) $(DEP_CPP_ACCOU) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h" ".\account_i.c"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinSize"

DEP_CPP_ACCOU=\
	".\account.h"\
	".\account_i.c"\
	".\CAccount.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\account.obj" : $(SOURCE) $(DEP_CPP_ACCOU) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h" ".\account_i.c"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinDependency"

DEP_CPP_ACCOU=\
	".\account.h"\
	".\account_i.c"\
	".\CAccount.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\account.obj" : $(SOURCE) $(DEP_CPP_ACCOU) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h" ".\account_i.c"


!ENDIF 

SOURCE=.\account.idl

!IF  "$(CFG)" == "account - Win32 Debug"

InputPath=.\account.idl

".\account.tlb"	".\account.h"	".\account_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "account.h" /iid "account_i.c" "account.idl"

!ELSEIF  "$(CFG)" == "account - Win32 Unicode Debug"

InputPath=.\account.idl

".\account.tlb"	".\account.h"	".\account_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "account.h" /iid "account_i.c" "account.idl"

!ELSEIF  "$(CFG)" == "account - Win32 Release MinSize"

InputPath=.\account.idl

".\account.tlb"	".\account.h"	".\account_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "account.h" /iid "account_i.c" "account.idl"

!ELSEIF  "$(CFG)" == "account - Win32 Release MinDependency"

InputPath=.\account.idl

".\account.tlb"	".\account.h"	".\account_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "account.h" /iid "account_i.c" "account.idl"

!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinSize"

InputPath=.\account.idl

".\account.tlb"	".\account.h"	".\account_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "account.h" /iid "account_i.c" "account.idl"

!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinDependency"

InputPath=.\account.idl

".\account.tlb"	".\account.h"	".\account_i.c"	 : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	midl /Oicf /h "account.h" /iid "account_i.c" "account.idl"

!ENDIF 

SOURCE=.\account.rc
DEP_RSC_ACCOUN=\
	".\account.tlb"\
	".\CAccount.rgs"\
	".\GetRec.rgs"\
	".\MvMoney.rgs"\
	".\UpdRec.rgs"\
	

"$(INTDIR)\account.res" : $(SOURCE) $(DEP_RSC_ACCOUN) "$(INTDIR)"\
 ".\account.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CAccount.cpp

!IF  "$(CFG)" == "account - Win32 Debug"

DEP_CPP_CACCO=\
	"..\..\..\..\..\..\include\basetsd.h"\
	"..\..\..\..\..\..\include\msxml.h"\
	"..\..\..\..\..\..\include\propidl.h"\
	"..\..\..\..\..\..\include\rpcasync.h"\
	"..\..\..\..\..\..\include\winefs.h"\
	"..\..\..\..\..\..\include\winscard.h"\
	"..\..\..\..\..\..\include\winsmcrd.h"\
	".\account.h"\
	".\CAccount.h"\
	".\StdAfx.h"\
	".\unicode.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\CAccount.obj" : $(SOURCE) $(DEP_CPP_CACCO) "$(INTDIR)" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Debug"

DEP_CPP_CACCO=\
	".\account.h"\
	".\CAccount.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\CAccount.obj" : $(SOURCE) $(DEP_CPP_CACCO) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Release MinSize"

DEP_CPP_CACCO=\
	".\account.h"\
	".\CAccount.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\CAccount.obj" : $(SOURCE) $(DEP_CPP_CACCO) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Release MinDependency"

DEP_CPP_CACCO=\
	".\account.h"\
	".\CAccount.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\CAccount.obj" : $(SOURCE) $(DEP_CPP_CACCO) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinSize"

DEP_CPP_CACCO=\
	".\account.h"\
	".\CAccount.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\CAccount.obj" : $(SOURCE) $(DEP_CPP_CACCO) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinDependency"

DEP_CPP_CACCO=\
	".\account.h"\
	".\CAccount.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\CAccount.obj" : $(SOURCE) $(DEP_CPP_CACCO) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ENDIF 

SOURCE=.\GetRec.cpp

!IF  "$(CFG)" == "account - Win32 Debug"

DEP_CPP_GETRE=\
	"..\..\..\..\..\..\include\basetsd.h"\
	"..\..\..\..\..\..\include\msxml.h"\
	"..\..\..\..\..\..\include\propidl.h"\
	"..\..\..\..\..\..\include\rpcasync.h"\
	"..\..\..\..\..\..\include\winefs.h"\
	"..\..\..\..\..\..\include\winscard.h"\
	"..\..\..\..\..\..\include\winsmcrd.h"\
	".\account.h"\
	".\GetRec.h"\
	".\StdAfx.h"\
	".\unicode.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\GetRec.obj" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Debug"

DEP_CPP_GETRE=\
	".\account.h"\
	".\GetRec.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\GetRec.obj" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Release MinSize"

DEP_CPP_GETRE=\
	".\account.h"\
	".\GetRec.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\GetRec.obj" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Release MinDependency"

DEP_CPP_GETRE=\
	".\account.h"\
	".\GetRec.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\GetRec.obj" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinSize"

DEP_CPP_GETRE=\
	".\account.h"\
	".\GetRec.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\GetRec.obj" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinDependency"

DEP_CPP_GETRE=\
	".\account.h"\
	".\GetRec.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\GetRec.obj" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ENDIF 

SOURCE=.\mvmoney.cpp

!IF  "$(CFG)" == "account - Win32 Debug"

DEP_CPP_MVMON=\
	"..\..\..\..\..\..\include\basetsd.h"\
	"..\..\..\..\..\..\include\msxml.h"\
	"..\..\..\..\..\..\include\propidl.h"\
	"..\..\..\..\..\..\include\rpcasync.h"\
	"..\..\..\..\..\..\include\winefs.h"\
	"..\..\..\..\..\..\include\winscard.h"\
	"..\..\..\..\..\..\include\winsmcrd.h"\
	".\account.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	".\unicode.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\mvmoney.obj" : $(SOURCE) $(DEP_CPP_MVMON) "$(INTDIR)" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Debug"

DEP_CPP_MVMON=\
	".\account.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\mvmoney.obj" : $(SOURCE) $(DEP_CPP_MVMON) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Release MinSize"

DEP_CPP_MVMON=\
	".\account.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\mvmoney.obj" : $(SOURCE) $(DEP_CPP_MVMON) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Release MinDependency"

DEP_CPP_MVMON=\
	".\account.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\mvmoney.obj" : $(SOURCE) $(DEP_CPP_MVMON) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinSize"

DEP_CPP_MVMON=\
	".\account.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\mvmoney.obj" : $(SOURCE) $(DEP_CPP_MVMON) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinDependency"

DEP_CPP_MVMON=\
	".\account.h"\
	".\GetRec.h"\
	".\mvmoney.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"comsvcs.h"\
	

"$(INTDIR)\mvmoney.obj" : $(SOURCE) $(DEP_CPP_MVMON) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "account - Win32 Debug"

DEP_CPP_STDAF=\
	"..\..\..\..\..\..\include\basetsd.h"\
	"..\..\..\..\..\..\include\msxml.h"\
	"..\..\..\..\..\..\include\propidl.h"\
	"..\..\..\..\..\..\include\rpcasync.h"\
	"..\..\..\..\..\..\include\winefs.h"\
	"..\..\..\..\..\..\include\winscard.h"\
	"..\..\..\..\..\..\include\winsmcrd.h"\
	".\StdAfx.h"\
	".\unicode.h"\
	
CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /I "..\..\..\..\..\..\include"\
 /FI"unicode.h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\account.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\account.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "account - Win32 Release MinSize"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /O1 /FI"unicode.h" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\account.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "account - Win32 Release MinDependency"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /O1 /FI"unicode.h" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\account.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinSize"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /O1 /FI"unicode.h" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\account.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinDependency"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\account.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\account.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\UpdRec.cpp

!IF  "$(CFG)" == "account - Win32 Debug"

DEP_CPP_UPDRE=\
	"..\..\..\..\..\..\include\basetsd.h"\
	"..\..\..\..\..\..\include\msxml.h"\
	"..\..\..\..\..\..\include\propidl.h"\
	"..\..\..\..\..\..\include\rpcasync.h"\
	"..\..\..\..\..\..\include\winefs.h"\
	"..\..\..\..\..\..\include\winscard.h"\
	"..\..\..\..\..\..\include\winsmcrd.h"\
	".\account.h"\
	".\StdAfx.h"\
	".\unicode.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\UpdRec.obj" : $(SOURCE) $(DEP_CPP_UPDRE) "$(INTDIR)" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Debug"

DEP_CPP_UPDRE=\
	".\account.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\UpdRec.obj" : $(SOURCE) $(DEP_CPP_UPDRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Release MinSize"

DEP_CPP_UPDRE=\
	".\account.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\UpdRec.obj" : $(SOURCE) $(DEP_CPP_UPDRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Release MinDependency"

DEP_CPP_UPDRE=\
	".\account.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\UpdRec.obj" : $(SOURCE) $(DEP_CPP_UPDRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinSize"

DEP_CPP_UPDRE=\
	".\account.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\UpdRec.obj" : $(SOURCE) $(DEP_CPP_UPDRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ELSEIF  "$(CFG)" == "account - Win32 Unicode Release MinDependency"

DEP_CPP_UPDRE=\
	".\account.h"\
	".\StdAfx.h"\
	".\UpdRec.h"\
	{$(INCLUDE)}"comsvcs.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\UpdRec.obj" : $(SOURCE) $(DEP_CPP_UPDRE) "$(INTDIR)"\
 "$(INTDIR)\account.pch" ".\account.h"


!ENDIF 


!ENDIF 

