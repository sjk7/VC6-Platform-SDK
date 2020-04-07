# Microsoft Developer Studio Generated NMAKE File, Based on ComSpyCtl.dsp
!IF "$(CFG)" == ""
CFG=ComSpyCtl - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to ComSpyCtl - Win32 Unicode Debug.
!ENDIF 

!IF "$(CFG)" != "ComSpyCtl - Win32 Unicode Release" && "$(CFG)" != "ComSpyCtl - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComSpyCtl.mak" CFG="ComSpyCtl - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComSpyCtl - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComSpyCtl - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"

OUTDIR=.\..\ReleaseU\x86
INTDIR=.\ReleaseU\x86
# Begin Custom Macros
OutDir=.\..\ReleaseU\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ComSpyCtl.dll" 

!ELSE 

ALL : "ComSpyAudit - Win32 Unicode Release" "$(OUTDIR)\ComSpyCtl.dll" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ComSpyAudit - Win32 Unicode ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Adminwrap.obj"
	-@erase "$(INTDIR)\AppInfo.obj"
	-@erase "$(INTDIR)\ComSpy.obj"
	-@erase "$(INTDIR)\ComSpyCtl.obj"
	-@erase "$(INTDIR)\ComSpyCtl.pch"
	-@erase "$(INTDIR)\ComSpyCtl.res"
	-@erase "$(INTDIR)\ComSpyPropPage.obj"
	-@erase "$(INTDIR)\crmsub.obj"
	-@erase "$(INTDIR)\evtstoresub.obj"
	-@erase "$(INTDIR)\methodsub.obj"
	-@erase "$(INTDIR)\resourcesub.obj"
	-@erase "$(INTDIR)\SelectEventsDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SysLCESub.obj"
	-@erase "$(INTDIR)\txsub.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ComSpyCtl.dll"
	-@erase "$(OUTDIR)\ComSpyCtl.exp"
	-@erase "$(OUTDIR)\ComSpyCtl.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\idl\ps_win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\ComSpyCtl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpyCtl.res" /i "..\idl\ps_win32" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSpyCtl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=comdlg32.lib shell32.lib rpcrt4.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ComSpyCtl.pdb" /machine:$(CPU) /def:".\ComSpyCtl.def" /out:"$(OUTDIR)\ComSpyCtl.dll" /implib:"$(OUTDIR)\ComSpyCtl.lib" 
DEF_FILE= \
	".\ComSpyCtl.def"
LINK32_OBJS= \
	"$(INTDIR)\Adminwrap.obj" \
	"$(INTDIR)\AppInfo.obj" \
	"$(INTDIR)\ComSpy.obj" \
	"$(INTDIR)\ComSpyCtl.obj" \
	"$(INTDIR)\ComSpyPropPage.obj" \
	"$(INTDIR)\crmsub.obj" \
	"$(INTDIR)\evtstoresub.obj" \
	"$(INTDIR)\methodsub.obj" \
	"$(INTDIR)\resourcesub.obj" \
	"$(INTDIR)\SelectEventsDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SysLCESub.obj" \
	"$(INTDIR)\txsub.obj" \
	"$(INTDIR)\ComSpyCtl.res" \
	"$(OUTDIR)\ComSpyAudit.lib"

"$(OUTDIR)\ComSpyCtl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\ReleaseU\x86
TargetPath=.\..\ReleaseU\x86\ComSpyCtl.dll
InputPath=.\..\ReleaseU\x86\ComSpyCtl.dll
SOURCE="$(InputPath)"

!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"

OUTDIR=.\..\DebugU\x86
INTDIR=.\DebugU\x86
# Begin Custom Macros
OutDir=.\..\DebugU\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ComSpyCtl.dll" "$(OUTDIR)\ComSpyCtl.bsc"

!ELSE 

ALL : "ComSpyAudit - Win32 Unicode Debug" "$(OUTDIR)\ComSpyCtl.dll" "$(OUTDIR)\ComSpyCtl.bsc" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ComSpyAudit - Win32 Unicode DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Adminwrap.obj"
	-@erase "$(INTDIR)\Adminwrap.sbr"
	-@erase "$(INTDIR)\AppInfo.obj"
	-@erase "$(INTDIR)\AppInfo.sbr"
	-@erase "$(INTDIR)\ComSpy.obj"
	-@erase "$(INTDIR)\ComSpy.sbr"
	-@erase "$(INTDIR)\ComSpyCtl.obj"
	-@erase "$(INTDIR)\ComSpyCtl.pch"
	-@erase "$(INTDIR)\ComSpyCtl.res"
	-@erase "$(INTDIR)\ComSpyCtl.sbr"
	-@erase "$(INTDIR)\ComSpyPropPage.obj"
	-@erase "$(INTDIR)\ComSpyPropPage.sbr"
	-@erase "$(INTDIR)\crmsub.obj"
	-@erase "$(INTDIR)\crmsub.sbr"
	-@erase "$(INTDIR)\evtstoresub.obj"
	-@erase "$(INTDIR)\evtstoresub.sbr"
	-@erase "$(INTDIR)\methodsub.obj"
	-@erase "$(INTDIR)\methodsub.sbr"
	-@erase "$(INTDIR)\resourcesub.obj"
	-@erase "$(INTDIR)\resourcesub.sbr"
	-@erase "$(INTDIR)\SelectEventsDlg.obj"
	-@erase "$(INTDIR)\SelectEventsDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\SysLCESub.obj"
	-@erase "$(INTDIR)\SysLCESub.sbr"
	-@erase "$(INTDIR)\txsub.obj"
	-@erase "$(INTDIR)\txsub.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ComSpyCtl.bsc"
	-@erase "$(OUTDIR)\ComSpyCtl.dll"
	-@erase "$(OUTDIR)\ComSpyCtl.exp"
	-@erase "$(OUTDIR)\ComSpyCtl.ilk"
	-@erase "$(OUTDIR)\ComSpyCtl.lib"
	-@erase "$(OUTDIR)\ComSpyCtl.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\idl\ps_win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ComSpyCtl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ComSpyCtl.res" /i "..\idl\ps_win32" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ComSpyCtl.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Adminwrap.sbr" \
	"$(INTDIR)\AppInfo.sbr" \
	"$(INTDIR)\ComSpy.sbr" \
	"$(INTDIR)\ComSpyCtl.sbr" \
	"$(INTDIR)\ComSpyPropPage.sbr" \
	"$(INTDIR)\crmsub.sbr" \
	"$(INTDIR)\evtstoresub.sbr" \
	"$(INTDIR)\methodsub.sbr" \
	"$(INTDIR)\resourcesub.sbr" \
	"$(INTDIR)\SelectEventsDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\SysLCESub.sbr" \
	"$(INTDIR)\txsub.sbr"

"$(OUTDIR)\ComSpyCtl.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=comdlg32.lib shell32.lib rpcrt4.lib svcguid.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ComSpyCtl.pdb" /debug /machine:$(CPU) /def:".\ComSpyCtl.def" /out:"$(OUTDIR)\ComSpyCtl.dll" /implib:"$(OUTDIR)\ComSpyCtl.lib" /pdbtype:sept 
DEF_FILE= \
	".\ComSpyCtl.def"
LINK32_OBJS= \
	"$(INTDIR)\Adminwrap.obj" \
	"$(INTDIR)\AppInfo.obj" \
	"$(INTDIR)\ComSpy.obj" \
	"$(INTDIR)\ComSpyCtl.obj" \
	"$(INTDIR)\ComSpyPropPage.obj" \
	"$(INTDIR)\crmsub.obj" \
	"$(INTDIR)\evtstoresub.obj" \
	"$(INTDIR)\methodsub.obj" \
	"$(INTDIR)\resourcesub.obj" \
	"$(INTDIR)\SelectEventsDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SysLCESub.obj" \
	"$(INTDIR)\txsub.obj" \
	"$(INTDIR)\ComSpyCtl.res" \
	"$(OUTDIR)\ComSpyAudit.lib"

"$(OUTDIR)\ComSpyCtl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\..\DebugU\x86
TargetPath=.\..\DebugU\x86\ComSpyCtl.dll
InputPath=.\..\DebugU\x86\ComSpyCtl.dll
SOURCE="$(InputPath)"

!ENDIF 

!IF "$(CFG)" == "ComSpyCtl - Win32 Unicode Release" || "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"
SOURCE=.\Adminwrap.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\idl\ps_win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\ComSpyCtl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Adminwrap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\idl\ps_win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Adminwrap.obj"	"$(INTDIR)\Adminwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\AppInfo.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\AppInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\AppInfo.obj"	"$(INTDIR)\AppInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

SOURCE=.\ComSpy.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\ComSpy.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\ComSpy.obj"	"$(INTDIR)\ComSpy.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

SOURCE=.\ComSpyCtl.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\ComSpyCtl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\ComSpyCtl.obj"	"$(INTDIR)\ComSpyCtl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

SOURCE=.\ComSpyCtl.rc

"$(INTDIR)\ComSpyCtl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ComSpyPropPage.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\ComSpyPropPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\ComSpyPropPage.obj"	"$(INTDIR)\ComSpyPropPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

SOURCE=.\crmsub.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\crmsub.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\crmsub.obj"	"$(INTDIR)\crmsub.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

SOURCE=.\evtstoresub.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\evtstoresub.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\evtstoresub.obj"	"$(INTDIR)\evtstoresub.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

SOURCE=.\methodsub.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\methodsub.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\methodsub.obj"	"$(INTDIR)\methodsub.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

SOURCE=.\resourcesub.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\resourcesub.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\resourcesub.obj"	"$(INTDIR)\resourcesub.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

SOURCE=.\SelectEventsDlg.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\SelectEventsDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\SelectEventsDlg.obj"	"$(INTDIR)\SelectEventsDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\idl\ps_win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\ComSpyCtl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ComSpyCtl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\idl\ps_win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ComSpyCtl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ComSpyCtl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\SysLCESub.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\SysLCESub.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\SysLCESub.obj"	"$(INTDIR)\SysLCESub.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

SOURCE=.\txsub.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"


"$(INTDIR)\txsub.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"


"$(INTDIR)\txsub.obj"	"$(INTDIR)\txsub.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ComSpyCtl.pch"


!ENDIF 

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"

!ENDIF 

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"

"ComSpyAudit - Win32 Unicode Release" : 
   cd ".\..\ComSpyAudit"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyAudit.mak CFG="ComSpyAudit - Win32 Unicode Release" 
   cd "..\ComSpyCtl"

"ComSpyAudit - Win32 Unicode ReleaseCLEAN" : 
   cd ".\..\ComSpyAudit"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyAudit.mak CFG="ComSpyAudit - Win32 Unicode Release" RECURSE=1 CLEAN 
   cd "..\ComSpyCtl"

!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"

"ComSpyAudit - Win32 Unicode Debug" : 
   cd ".\..\ComSpyAudit"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyAudit.mak CFG="ComSpyAudit - Win32 Unicode Debug" 
   cd "..\ComSpyCtl"

"ComSpyAudit - Win32 Unicode DebugCLEAN" : 
   cd ".\..\ComSpyAudit"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSpyAudit.mak CFG="ComSpyAudit - Win32 Unicode Debug" RECURSE=1 CLEAN 
   cd "..\ComSpyCtl"

!ENDIF 

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"

!ENDIF 


!ENDIF 

