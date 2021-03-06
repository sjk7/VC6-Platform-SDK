
# Microsoft Developer Studio Generated NMAKE File, Based on proxy.dsp
!IF "$(CFG)" == ""
CFG=proxy - Win64 Debug
!MESSAGE No configuration specified. Defaulting to proxy - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "proxy - Win64 Release" && "$(CFG)" != "proxy - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "proxy64.mak" CFG="proxy - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "proxy - Win64 Release" (based on "Win64 (IA64) Dynamic-Link Library")
!MESSAGE "proxy - Win64 Debug" (based on "Win64 (IA64) Dynamic-Link Library")
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

!IF  "$(CFG)" == "proxy - Win64 Release"

OUTDIR=.\../Bin/Release/IA64
INTDIR=.\../Bin/Release/IA64
# Begin Custom Macros
OutDir=.\../Bin/Release/IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\proxy.dll"

!ELSE 

ALL : "idl - Win64 Release" "$(OUTDIR)\proxy.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"idl - Win64 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\dlldata.obj"
	-@erase "$(INTDIR)\Proxy_i.obj"
	-@erase "$(INTDIR)\Proxy_p.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\proxy.dll"
	-@erase "$(OUTDIR)\proxy.exp"
	-@erase "$(OUTDIR)\proxy.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /Wp64 /GX /O2 /D "NDEBUG" /D "WIN64" /D "WIN32"  /D _WIN32_WINNT=0X500 /D "REGISTER_PROXY_DLL" /Fp"$(INTDIR)\proxy.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
MTL_PROJ=/nologo /D "NDEBUG" /o "NUL" /win64 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\proxy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\proxy.pdb" /machine:IA64 /def:".\proxy.def" /out:"$(OUTDIR)\proxy.dll" /implib:"$(OUTDIR)\proxy.lib" 
DEF_FILE= \
	".\proxy.def"
LINK32_OBJS= \
	"$(INTDIR)\dlldata.obj" \
	"$(INTDIR)\Proxy_i.obj" \
	"$(INTDIR)\Proxy_p.obj"

"$(OUTDIR)\proxy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "proxy - Win64 Debug"

OUTDIR=.\../Bin/Debug/IA64
INTDIR=.\../Bin/Debug/IA64
# Begin Custom Macros
OutDir=.\../Bin/Debug/IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\proxy.dll"

!ELSE 

ALL : "idl - Win64 Debug" "$(OUTDIR)\proxy.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"idl - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\dlldata.obj"
	-@erase "$(INTDIR)\Proxy_i.obj"
	-@erase "$(INTDIR)\Proxy_p.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\proxy.dll"
	-@erase "$(OUTDIR)\proxy.exp"
	-@erase "$(OUTDIR)\proxy.ilk"
	-@erase "$(OUTDIR)\proxy.lib"
	-@erase "$(OUTDIR)\proxy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Wp64 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN64" /D "WIN32"  /D _WIN32_WINNT=0X500 /D "REGISTER_PROXY_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
MTL_PROJ=/nologo /D "_DEBUG" /o "NUL" /win64 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\proxy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\proxy.pdb" /debug /machine:IA64 /def:".\proxy.def" /out:"$(OUTDIR)\proxy.dll" /implib:"$(OUTDIR)\proxy.lib"  
DEF_FILE= \
	".\proxy.def"
LINK32_OBJS= \
	"$(INTDIR)\dlldata.obj" \
	"$(INTDIR)\Proxy_i.obj" \
	"$(INTDIR)\Proxy_p.obj"

"$(OUTDIR)\proxy.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("proxy.dep")
!INCLUDE "proxy.dep"
!ELSE 
!MESSAGE Warning: cannot find "proxy.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "proxy - Win64 Release" || "$(CFG)" == "proxy - Win64 Debug"

!IF  "$(CFG)" == "proxy - Win64 Release"

"idl - Win64 Release" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Release" 
   cd "..\proxy"

"idl - Win64 ReleaseCLEAN" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Release" RECURSE=1 CLEAN 
   cd "..\proxy"

!ELSEIF  "$(CFG)" == "proxy - Win64 Debug"

"idl - Win64 Debug" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" 
   cd "..\proxy"

"idl - Win64 DebugCLEAN" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\proxy"

!ENDIF 

SOURCE=..\ps_win64\dlldata.c

"$(INTDIR)\dlldata.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ps_win64\Proxy_i.c

"$(INTDIR)\Proxy_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ps_win64\Proxy_p.c

"$(INTDIR)\Proxy_p.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 
