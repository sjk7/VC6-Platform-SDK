
# Microsoft Developer Studio Generated NMAKE File, Based on HelpDll.dsp
!IF "$(CFG)" == ""
CFG=HelpDll - Win64 Debug
!MESSAGE No configuration specified. Defaulting to HelpDll - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "HelpDll - Win64 Release" && "$(CFG)" != "HelpDll - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HelpDll64.mak" CFG="HelpDll - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HelpDll - Win64 Release" (based on "Win64 (IA64) Dynamic-Link Library")
!MESSAGE "HelpDll - Win64 Debug" (based on "Win64 (IA64) Dynamic-Link Library")
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

!IF  "$(CFG)" == "HelpDll - Win64 Release"

OUTDIR=.\..\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\..\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\HelpDll.dll"

!ELSE 

ALL : "$(OUTDIR)\HelpDll.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\HelpDll.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HelpDll.dll"
	-@erase "$(OUTDIR)\HelpDll.exp"
	-@erase "$(OUTDIR)\HelpDll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MT /W3 /Wp64 /GX /O2 /D "WIN64" /D "WIN32"  /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HELPDLL_EXPORTS" /Fp"$(INTDIR)\HelpDll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win64 $(MIDL_OPTIMIZATION)
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HelpDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\HelpDll.pdb" /machine:IA64 /out:"$(OUTDIR)\HelpDll.dll" /implib:"$(OUTDIR)\HelpDll.lib" 
LINK32_OBJS= \
	"$(INTDIR)\HelpDll.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\HelpDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "HelpDll - Win64 Debug"

OUTDIR=.\..\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\..\Debug\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\HelpDll.dll"

!ELSE 

ALL : "FullSvr - Win64 Debug" "$(OUTDIR)\HelpDll.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FullSvr - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\HelpDll.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HelpDll.dll"
	-@erase "$(OUTDIR)\HelpDll.exp"
	-@erase "$(OUTDIR)\HelpDll.ilk"
	-@erase "$(OUTDIR)\HelpDll.lib"
	-@erase "$(OUTDIR)\HelpDll.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Wp64 /Gm /GX /Zi /Od /D "WIN64" /D "WIN32"  /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HELPDLL_EXPORTS" /Fp"$(INTDIR)\HelpDll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win64 $(MIDL_OPTIMIZATION)
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HelpDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\HelpDll.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\HelpDll.dll" /implib:"$(OUTDIR)\HelpDll.lib"  
LINK32_OBJS= \
	"$(INTDIR)\HelpDll.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\HelpDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("HelpDll.dep")
!INCLUDE "HelpDll.dep"
!ELSE 
!MESSAGE Warning: cannot find "HelpDll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HelpDll - Win64 Release" || "$(CFG)" == "HelpDll - Win64 Debug"
SOURCE=.\HelpDll.cpp

"$(INTDIR)\HelpDll.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

"$(INTDIR)\StdAfx.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "HelpDll - Win64 Release"

!ELSEIF  "$(CFG)" == "HelpDll - Win64 Debug"

"FullSvr - Win64 Debug" : 
   cd ".\..\FullSvr"
   $(MAKE) /$(MAKEFLAGS) /F .\FullSvr64.mak CFG="FullSvr - Win64 Debug" 
   cd "..\HelpDll"

"FullSvr - Win64 DebugCLEAN" : 
   cd ".\..\FullSvr"
   $(MAKE) /$(MAKEFLAGS) /F .\FullSvr64.mak CFG="FullSvr - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\HelpDll"

!ENDIF 


!ENDIF 
