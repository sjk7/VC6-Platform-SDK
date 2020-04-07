# Microsoft Developer Studio Generated NMAKE File, Based on psperf.dsp
!IF "$(CFG)" == ""
CFG=psperf - Win32 Debug
!MESSAGE No configuration specified. Defaulting to psperf - Win32 Debug.
!ENDIF 

!IF "$(APPVER)" == "4.0"
NMAKE_WINVER = 0x0400
!ELSEIF "$(APPVER)" == "5.0"
NMAKE_WINVER = 0x0500
!ELSEIF "$(APPVER)" == "5.01"
NMAKE_WINVER = 0x0501
!ELSEIF "$(APPVER)" == "5.02"
NMAKE_WINVER = 0x0502
!ENDIF

!IF "$(CFG)" != "psperf - Win32 Release" && "$(CFG)" != "psperf - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "psperf.mak" CFG="psperf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "psperf - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "psperf - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "psperf - Win32 Release"

OUTDIR=.\Release\x86
INTDIR=.\Release\x86
# Begin Custom Macros
OutDir=.\Release\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\psperf.dll"

!ELSE 

ALL : "psperflib - Win32 Release" "$(OUTDIR)\psperf.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"psperflib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\dlldata.obj"
	-@erase "$(INTDIR)\psperf_i.obj"
	-@erase "$(INTDIR)\psperf_p.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\psperf.dll"
	-@erase "$(OUTDIR)\psperf.exp"
	-@erase "$(OUTDIR)\psperf.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "ps_Win32" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PSPERF_EXPORTS" /D "_WIN32_DCOM" /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\psperf.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 $(MIDL_OPTIMIZATION)
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\psperf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\psperf.pdb" /machine:$(CPU) /def:".\psperf.def" /out:"$(OUTDIR)\psperf.dll" /implib:"$(OUTDIR)\psperf.lib" 
DEF_FILE= \
	".\psperf.def"
LINK32_OBJS= \
	"$(INTDIR)\psperf_p.obj" \
	"$(INTDIR)\psperf_i.obj" \
	"$(INTDIR)\dlldata.obj"

"$(OUTDIR)\psperf.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "psperf - Win32 Debug"

OUTDIR=.\Debug\x86
INTDIR=.\Debug\x86
# Begin Custom Macros
OutDir=.\Debug\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\psperf.dll"

!ELSE 

ALL : "psperflib - Win32 Debug" "$(OUTDIR)\psperf.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"psperflib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\dlldata.obj"
	-@erase "$(INTDIR)\psperf_i.obj"
	-@erase "$(INTDIR)\psperf_p.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\psperf.dll"
	-@erase "$(OUTDIR)\psperf.exp"
	-@erase "$(OUTDIR)\psperf.ilk"
	-@erase "$(OUTDIR)\psperf.lib"
	-@erase "$(OUTDIR)\psperf.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "ps_Win32" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PSPERF_EXPORTS" /D "_WIN32_DCOM" /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\psperf.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 $(MIDL_OPTIMIZATION)
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\psperf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\psperf.pdb" /debug /machine:$(CPU) /def:".\psperf.def" /out:"$(OUTDIR)\psperf.dll" /implib:"$(OUTDIR)\psperf.lib" /pdbtype:sept 
DEF_FILE= \
	".\psperf.def"
LINK32_OBJS= \
	"$(INTDIR)\psperf_p.obj" \
	"$(INTDIR)\psperf_i.obj" \
	"$(INTDIR)\dlldata.obj"

"$(OUTDIR)\psperf.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("psperf.dep")
!INCLUDE "psperf.dep"
!ELSE 
!MESSAGE Warning: cannot find "psperf.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "psperf - Win32 Release" || "$(CFG)" == "psperf - Win32 Debug"
SOURCE=.\ps_Win32\dlldata.c

"$(INTDIR)\dlldata.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\ps_Win32\psperf_i.c

"$(INTDIR)\psperf_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE) 


SOURCE=.\ps_Win32\psperf_p.c

"$(INTDIR)\psperf_p.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) /D_WIN32_WINNT=$(NMAKE_WINVER) $(SOURCE)


!IF  "$(CFG)" == "psperf - Win32 Release"

"psperflib - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\psperflib.mak CFG="psperflib - Win32 Release" 
   cd "."

"psperflib - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\psperflib.mak CFG="psperflib - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "psperf - Win32 Debug"

"psperflib - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\psperflib.mak CFG="psperflib - Win32 Debug" 
   cd "."

"psperflib - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\psperflib.mak CFG="psperflib - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 


!ENDIF 

