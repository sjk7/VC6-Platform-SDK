
# Microsoft Developer Studio Generated NMAKE File, Based on dogps.dsp
!IF "$(CFG)" == ""
CFG=dogps - Win64 Debug
!MESSAGE No configuration specified. Defaulting to dogps - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "dogps - Win64 Release" && "$(CFG)" != "dogps - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dogps64.mak" CFG="dogps - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dogps - Win64 Release" (based on "Win64 (IA64) Dynamic-Link Library")
!MESSAGE "dogps - Win64 Debug" (based on "Win64 (IA64) Dynamic-Link Library")
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

!IF  "$(CFG)" == "dogps - Win64 Release"

OUTDIR=.\..\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\..\Release\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dogps.dll"

!ELSE 

ALL : "idl - Win64 Release" "$(OUTDIR)\dogps.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"idl - Win64 ReleaseCLEAN" 
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

CPP_PROJ=/nologo /MT /W3 /Wp64 /GX /O2 /D "NDEBUG" /D "WIN64" /D "WIN32"  /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DOGPS_EXPORTS" /D _WIN32_WINNT=0x0500 /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\dogps.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win64 $(MIDL_OPTIMIZATION)
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dogps.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcndr.lib rpcns4.lib rpcrt4.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\dogps.pdb" /machine:IA64 /def:"..\dog\dog.def" /out:"$(OUTDIR)\dogps.dll" /implib:"$(OUTDIR)\dogps.lib" 
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

!ELSEIF  "$(CFG)" == "dogps - Win64 Debug"

OUTDIR=.\..\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\..\Debug\IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dogps.dll"

!ELSE 

ALL : "idl - Win64 Debug" "$(OUTDIR)\dogps.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"idl - Win64 DebugCLEAN" 
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

CPP_PROJ=/nologo /MTd /W3 /Wp64 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN64" /D "WIN32"  /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DOGPS_EXPORTS" /D _WIN32_WINNT=0x0500 /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\dogps.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"    /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win64 $(MIDL_OPTIMIZATION)
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dogps.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcndr.lib rpcns4.lib rpcrt4.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\dogps.pdb" /debug /machine:IA64 /def:"..\dog\dog.def" /out:"$(OUTDIR)\dogps.dll" /implib:"$(OUTDIR)\dogps.lib"  
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


!IF "$(CFG)" == "dogps - Win64 Release" || "$(CFG)" == "dogps - Win64 Debug"
SOURCE=..\idl\ps_Win64\dlldata.c

"$(INTDIR)\dlldata.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\idl\ps_Win64\idog_i.c

"$(INTDIR)\idog_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\idl\ps_Win64\idog_p.c

"$(INTDIR)\idog_p.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "dogps - Win64 Release"

"idl - Win64 Release" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Release" 
   cd "..\dogps"

"idl - Win64 ReleaseCLEAN" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Release" RECURSE=1 CLEAN 
   cd "..\dogps"

!ELSEIF  "$(CFG)" == "dogps - Win64 Debug"

"idl - Win64 Debug" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" 
   cd "..\dogps"

"idl - Win64 DebugCLEAN" : 
   cd ".\..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\dogps"

!ENDIF 


!ENDIF 
