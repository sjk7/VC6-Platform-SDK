!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on API.DSP
!IF "$(CFG)" == ""
CFG=API - Win32 Debug
!MESSAGE No configuration specified. Defaulting to API - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "API - Win32 Release" && "$(CFG)" != "API - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "API.MAK" CFG="API - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "API - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "API - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "API - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\API.exe"


CLEAN :
	-@erase "$(INTDIR)\API.obj"
	-@erase "$(INTDIR)\API.pch"
	-@erase "$(INTDIR)\API.res"
	-@erase "$(INTDIR)\APIDoc.obj"
	-@erase "$(INTDIR)\APIView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MessageDlg.obj"
	-@erase "$(INTDIR)\ProcessDlg.obj"
	-@erase "$(INTDIR)\QueryDlg.obj"
	-@erase "$(INTDIR)\ServerDlg.obj"
	-@erase "$(INTDIR)\SessionDlg.obj"
	-@erase "$(INTDIR)\ShutdownDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WaitSystemDlg.obj"
	-@erase "$(OUTDIR)\API.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\API.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\API.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\API.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\API.pdb" /machine:$(CPU) /out:"$(OUTDIR)\API.exe" 
LINK32_OBJS= \
	"$(INTDIR)\API.obj" \
	"$(INTDIR)\APIDoc.obj" \
	"$(INTDIR)\APIView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MessageDlg.obj" \
	"$(INTDIR)\ProcessDlg.obj" \
	"$(INTDIR)\QueryDlg.obj" \
	"$(INTDIR)\ServerDlg.obj" \
	"$(INTDIR)\SessionDlg.obj" \
	"$(INTDIR)\ShutdownDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WaitSystemDlg.obj" \
	"$(INTDIR)\API.res"

"$(OUTDIR)\API.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "API - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\API.exe"


CLEAN :
	-@erase "$(INTDIR)\API.obj"
	-@erase "$(INTDIR)\API.pch"
	-@erase "$(INTDIR)\API.res"
	-@erase "$(INTDIR)\APIDoc.obj"
	-@erase "$(INTDIR)\APIView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MessageDlg.obj"
	-@erase "$(INTDIR)\ProcessDlg.obj"
	-@erase "$(INTDIR)\QueryDlg.obj"
	-@erase "$(INTDIR)\ServerDlg.obj"
	-@erase "$(INTDIR)\SessionDlg.obj"
	-@erase "$(INTDIR)\ShutdownDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WaitSystemDlg.obj"
	-@erase "$(OUTDIR)\API.exe"
	-@erase "$(OUTDIR)\API.ilk"
	-@erase "$(OUTDIR)\API.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\API.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\API.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\API.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wtsapi32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\API.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\API.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\API.obj" \
	"$(INTDIR)\APIDoc.obj" \
	"$(INTDIR)\APIView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MessageDlg.obj" \
	"$(INTDIR)\ProcessDlg.obj" \
	"$(INTDIR)\QueryDlg.obj" \
	"$(INTDIR)\ServerDlg.obj" \
	"$(INTDIR)\SessionDlg.obj" \
	"$(INTDIR)\ShutdownDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WaitSystemDlg.obj" \
	"$(INTDIR)\API.res"

"$(OUTDIR)\API.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("API.DEP")
!INCLUDE "API.DEP"
!ELSE 
!MESSAGE Warning: cannot find "API.DEP"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "API - Win32 Release" || "$(CFG)" == "API - Win32 Debug"
SOURCE=.\API.cpp

"$(INTDIR)\API.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"


SOURCE=.\API.rc

"$(INTDIR)\API.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\APIDoc.cpp

"$(INTDIR)\APIDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"


SOURCE=.\APIView.cpp

"$(INTDIR)\APIView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"


SOURCE=.\MessageDlg.cpp

"$(INTDIR)\MessageDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"


SOURCE=.\ProcessDlg.cpp

"$(INTDIR)\ProcessDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"


SOURCE=.\QueryDlg.cpp

"$(INTDIR)\QueryDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"


SOURCE=.\ServerDlg.cpp

"$(INTDIR)\ServerDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"


SOURCE=.\SessionDlg.cpp

"$(INTDIR)\SessionDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"


SOURCE=.\ShutdownDlg.cpp

"$(INTDIR)\ShutdownDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "API - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\API.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\API.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "API - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\API.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\API.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\WaitSystemDlg.cpp

"$(INTDIR)\WaitSystemDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\API.pch"



!ENDIF 

