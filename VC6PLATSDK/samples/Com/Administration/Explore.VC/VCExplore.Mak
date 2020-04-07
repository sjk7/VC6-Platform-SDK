# Microsoft Developer Studio Generated NMAKE File, Based on VCExplore.dsp
!IF "$(CFG)" == ""
CFG=VCExplore - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VCExplore - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VCExplore - Win32 Release" && "$(CFG)" != "VCExplore - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCExplore.mak" CFG="VCExplore - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VCExplore - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VCExplore - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "VCExplore - Win32 Release"

OUTDIR=.\Release\x86
INTDIR=.\Release\x86
# Begin Custom Macros
OutDir=.\Release\x86
# End Custom Macros

ALL : "$(OUTDIR)\VCExplore.exe"


CLEAN :
	-@erase "$(INTDIR)\AppExportDlg.obj"
	-@erase "$(INTDIR)\AppInstallDlg.obj"
	-@erase "$(INTDIR)\AppUtilDlg.obj"
	-@erase "$(INTDIR)\CompImportDlg.obj"
	-@erase "$(INTDIR)\CompInstallDlg.obj"
	-@erase "$(INTDIR)\ConnectDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UtilitiesDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VCExplore.obj"
	-@erase "$(INTDIR)\VCExplore.pch"
	-@erase "$(INTDIR)\VCExplore.res"
	-@erase "$(INTDIR)\VCExploreDlg.obj"
	-@erase "$(OUTDIR)\VCExplore.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VCExplore.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VCExplore.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCExplore.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\VCExplore.pdb" /machine:$(CPU) /out:"$(OUTDIR)\VCExplore.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AppExportDlg.obj" \
	"$(INTDIR)\AppInstallDlg.obj" \
	"$(INTDIR)\AppUtilDlg.obj" \
	"$(INTDIR)\CompImportDlg.obj" \
	"$(INTDIR)\CompInstallDlg.obj" \
	"$(INTDIR)\ConnectDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UtilitiesDlg.obj" \
	"$(INTDIR)\VCExplore.obj" \
	"$(INTDIR)\VCExploreDlg.obj" \
	"$(INTDIR)\VCExplore.res"

"$(OUTDIR)\VCExplore.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VCExplore - Win32 Debug"

OUTDIR=.\Debug\x86
INTDIR=.\Debug\x86
# Begin Custom Macros
OutDir=.\Debug\x86
# End Custom Macros

ALL : "$(OUTDIR)\VCExplore.exe" "$(OUTDIR)\VCExplore.pch"


CLEAN :
	-@erase "$(INTDIR)\AppExportDlg.obj"
	-@erase "$(INTDIR)\AppInstallDlg.obj"
	-@erase "$(INTDIR)\AppUtilDlg.obj"
	-@erase "$(INTDIR)\CompImportDlg.obj"
	-@erase "$(INTDIR)\CompInstallDlg.obj"
	-@erase "$(INTDIR)\ConnectDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UtilitiesDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VCExplore.obj"
	-@erase "$(INTDIR)\VCExplore.pch"
	-@erase "$(INTDIR)\VCExplore.res"
	-@erase "$(INTDIR)\VCExploreDlg.obj"
	-@erase "$(OUTDIR)\VCExplore.exe"
	-@erase "$(OUTDIR)\VCExplore.ilk"
	-@erase "$(OUTDIR)\VCExplore.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
MTL_PROJ=/out "..\..\..\..\include" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VCExplore.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VCExplore.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\VCExplore.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\VCExplore.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AppExportDlg.obj" \
	"$(INTDIR)\AppInstallDlg.obj" \
	"$(INTDIR)\AppUtilDlg.obj" \
	"$(INTDIR)\CompImportDlg.obj" \
	"$(INTDIR)\CompInstallDlg.obj" \
	"$(INTDIR)\ConnectDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UtilitiesDlg.obj" \
	"$(INTDIR)\VCExplore.obj" \
	"$(INTDIR)\VCExploreDlg.obj" \
	"$(INTDIR)\VCExplore.res"

"$(OUTDIR)\VCExplore.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("VCExplore.dep")
!INCLUDE "VCExplore.dep"
!ELSE 
!MESSAGE Warning: cannot find "VCExplore.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VCExplore - Win32 Release" || "$(CFG)" == "VCExplore - Win32 Debug"
SOURCE=.\AppExportDlg.cpp

"$(INTDIR)\AppExportDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCExplore.pch"


SOURCE=.\AppInstallDlg.cpp

"$(INTDIR)\AppInstallDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCExplore.pch"


SOURCE=.\AppUtilDlg.cpp

"$(INTDIR)\AppUtilDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCExplore.pch"


SOURCE=.\CompImportDlg.cpp

"$(INTDIR)\CompImportDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCExplore.pch"


SOURCE=.\CompInstallDlg.cpp

"$(INTDIR)\CompInstallDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCExplore.pch"


SOURCE=.\ConnectDlg.cpp

"$(INTDIR)\ConnectDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCExplore.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "VCExplore - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VCExplore.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCExplore.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VCExplore - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\VCExplore.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VCExplore.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\UtilitiesDlg.cpp

"$(INTDIR)\UtilitiesDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCExplore.pch"


SOURCE=.\VCExplore.cpp

"$(INTDIR)\VCExplore.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCExplore.pch"


SOURCE=.\VCExplore.rc

"$(INTDIR)\VCExplore.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\VCExploreDlg.cpp

"$(INTDIR)\VCExploreDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VCExplore.pch"



!ENDIF 

