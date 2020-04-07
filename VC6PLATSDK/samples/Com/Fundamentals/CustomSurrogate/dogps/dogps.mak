# Microsoft Developer Studio Generated NMAKE File, Based on dogps.dsp
!IF "$(CFG)" == ""
CFG=dogps - Win32 Debug
!MESSAGE No configuration specified. Defaulting to dogps - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "dogps - Win32 Release" && "$(CFG)" != "dogps - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dogps.mak" CFG="dogps - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dogps - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dogps - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "dogps - Win32 Release"

OUTDIR=.\..\Release\x86
INTDIR=.\Release\x86
# Begin Custom Macros
OutDir=.\..\Release\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dogps.dll"

!ELSE 

ALL : "idl - Win32 Release" "$(OUTDIR)\dogps.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"idl - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\dlldata.obj"
	-@erase "$(INTDIR)\idog_i.obj"
	-@erase "$(INTDIR)\idog_p.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\dogps.dll"
	-@erase "$(OUTDIR)\dogps.exp"
	-@erase "$(OUTDIR)\dogps.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DOGPS_EXPORTS" /D _WIN32_WINNT=0x0500 /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\dogps.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 $(MIDL_OPTIMIZATION)
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dogps.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcndr.lib rpcns4.lib rpcrt4.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\dogps.pdb" /machine:$(CPU) /def:"..\dog\dog.def" /out:"$(OUTDIR)\dogps.dll" /implib:"$(OUTDIR)\dogps.lib" 
DEF_FILE= \
	"..\dog\dog.def"
LINK32_OBJS= \
	"$(INTDIR)\idog_p.obj" \
	"$(INTDIR)\idog_i.obj" \
	"$(INTDIR)\dlldata.obj"

"$(OUTDIR)\dogps.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dogps - Win32 Debug"

OUTDIR=.\..\Debug\x86
INTDIR=.\Debug\x86
# Begin Custom Macros
OutDir=.\..\Debug\x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dogps.dll"

!ELSE 

ALL : "idl - Win32 Debug" "$(OUTDIR)\dogps.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"idl - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\dlldata.obj"
	-@erase "$(INTDIR)\idog_i.obj"
	-@erase "$(INTDIR)\idog_p.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\dogps.dll"
	-@erase "$(OUTDIR)\dogps.exp"
	-@erase "$(OUTDIR)\dogps.ilk"
	-@erase "$(OUTDIR)\dogps.lib"
	-@erase "$(OUTDIR)\dogps.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DOGPS_EXPORTS" /D _WIN32_WINNT=0x0500 /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\dogps.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ  /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 $(MIDL_OPTIMIZATION)
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dogps.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcndr.lib rpcns4.lib rpcrt4.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\dogps.pdb" /debug /machine:$(CPU) /def:"..\dog\dog.def" /out:"$(OUTDIR)\dogps.dll" /implib:"$(OUTDIR)\dogps.lib" /pdbtype:sept 
DEF_FILE= \
	"..\dog\dog.def"
LINK32_OBJS= \
	"$(INTDIR)\idog_p.obj" \
	"$(INTDIR)\idog_i.obj" \
	"$(INTDIR)\dlldata.obj"

"$(OUTDIR)\dogps.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("dogps.dep")
!INCLUDE "dogps.dep"
!ELSE 
!MESSAGE Warning: cannot find "dogps.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "dogps - Win32 Release" || "$(CFG)" == "dogps - Win32 Debug"
SOURCE=..\idl\ps_Win32\dlldata.c

"$(INTDIR)\dlldata.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\idl\ps_Win32\idog_i.c

"$(INTDIR)\idog_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\idl\ps_Win32\idog_p.c

"$(INTDIR)\idog_p.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "dogps - Win32 Release"

"idl - Win32 Release" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Release" 
   cd "..\dogps"

"idl - Win32 ReleaseCLEAN" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Release" RECURSE=1 CLEAN 
   cd "..\dogps"

!ELSEIF  "$(CFG)" == "dogps - Win32 Debug"

"idl - Win32 Debug" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Debug" 
   cd "..\dogps"

"idl - Win32 DebugCLEAN" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\dogps"

!ENDIF 


!ENDIF 

