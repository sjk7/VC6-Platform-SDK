
# Microsoft Developer Studio Generated NMAKE File, Based on AsyncServer.dsp
!IF "$(CFG)" == ""
CFG=AsyncServer - Win64 Debug
!MESSAGE No configuration specified. Defaulting to AsyncServer - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "AsyncServer - Win64 Release" && "$(CFG)" != "AsyncServer - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AsyncServer64.mak" CFG="AsyncServer - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AsyncServer - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "AsyncServer - Win64 Debug" (based on "Win64 (IA64) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AsyncServer - Win64 Release"

OUTDIR=.\../Bin/Release/IA64
INTDIR=.\../Bin/Release/IA64
# Begin Custom Macros
OutDir=.\../Bin/Release/IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\AsyncServer.exe"

!ELSE 

ALL : "proxy - Win64 Release" "idl - Win64 Release" "$(OUTDIR)\AsyncServer.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"idl - Win64 ReleaseCLEAN" "proxy - Win64 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\CAsyncTest.obj"
	-@erase "$(INTDIR)\CConnectionPT.obj"
	-@erase "$(INTDIR)\cfactory.obj"
	-@erase "$(INTDIR)\cunknown.obj"
	-@erase "$(INTDIR)\DCOMServer.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\Proxy_i.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\SERVER.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AsyncServer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /Wp64 /GX /O2 /I "..\ps_Win64" /D "NDEBUG" /D "_AGGREGATE_" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0X500 /D "_APARTMENT_" /D "_ASYNC_COM_" /D "_EVENTSINK_" /D "_SECURE_" /Fp"$(INTDIR)\AsyncServer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AsyncServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\AsyncServer.pdb" /machine:IA64 /out:"$(OUTDIR)\AsyncServer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CAsyncTest.obj" \
	"$(INTDIR)\CConnectionPT.obj" \
	"$(INTDIR)\cfactory.obj" \
	"$(INTDIR)\cunknown.obj" \
	"$(INTDIR)\DCOMServer.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\SERVER.OBJ" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Proxy_i.obj" \
	"$(OUTDIR)\proxy.lib"

"$(OUTDIR)\AsyncServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AsyncServer - Win64 Debug"

OUTDIR=.\../Bin/Debug/IA64
INTDIR=.\../Bin/Debug/IA64
# Begin Custom Macros
OutDir=.\../Bin/Debug/IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\AsyncServer.exe"

!ELSE 

ALL : "proxy - Win64 Debug" "idl - Win64 Debug" "$(OUTDIR)\AsyncServer.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"idl - Win64 DebugCLEAN" "proxy - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\CAsyncTest.obj"
	-@erase "$(INTDIR)\CConnectionPT.obj"
	-@erase "$(INTDIR)\cfactory.obj"
	-@erase "$(INTDIR)\cunknown.obj"
	-@erase "$(INTDIR)\DCOMServer.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\Proxy_i.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\SERVER.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\AsyncServer.exe"
	-@erase "$(OUTDIR)\AsyncServer.ilk"
	-@erase "$(OUTDIR)\AsyncServer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Wp64 /GX /Zi /Od /I "..\ps_Win64" /D "_DEBUG" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0X500 /D "_APARTMENT_" /D "_ASYNC_COM_" /D "_EVENTSINK_" /Fp"$(INTDIR)\AsyncServer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AsyncServer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\AsyncServer.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\AsyncServer.exe"  
LINK32_OBJS= \
	"$(INTDIR)\CAsyncTest.obj" \
	"$(INTDIR)\CConnectionPT.obj" \
	"$(INTDIR)\cfactory.obj" \
	"$(INTDIR)\cunknown.obj" \
	"$(INTDIR)\DCOMServer.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\SERVER.OBJ" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Proxy_i.obj" \
	"$(OUTDIR)\proxy.lib"

"$(OUTDIR)\AsyncServer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("AsyncServer.dep")
!INCLUDE "AsyncServer.dep"
!ELSE 
!MESSAGE Warning: cannot find "AsyncServer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "AsyncServer - Win64 Release" || "$(CFG)" == "AsyncServer - Win64 Debug"
SOURCE=.\CAsyncTest.cpp

"$(INTDIR)\CAsyncTest.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CConnectionPT.cpp

"$(INTDIR)\CConnectionPT.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\cfactory.cpp

"$(INTDIR)\cfactory.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\cunknown.cpp

"$(INTDIR)\cunknown.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DCOMServer.cpp

"$(INTDIR)\DCOMServer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\registry.cpp

"$(INTDIR)\registry.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SERVER.CPP

"$(INTDIR)\SERVER.OBJ" : $(SOURCE) "$(INTDIR)"


SOURCE=.\debug.c

"$(INTDIR)\debug.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\ps_win64\Proxy_i.c

"$(INTDIR)\Proxy_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "AsyncServer - Win64 Release"

"idl - Win64 Release" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Release" 
   cd "..\server"

"idl - Win64 ReleaseCLEAN" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Release" RECURSE=1 CLEAN 
   cd "..\server"

!ELSEIF  "$(CFG)" == "AsyncServer - Win64 Debug"

"idl - Win64 Debug" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" 
   cd "..\server"

"idl - Win64 DebugCLEAN" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\server"

!ENDIF 

!IF  "$(CFG)" == "AsyncServer - Win64 Release"

"proxy - Win64 Release" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy64.mak CFG="proxy - Win64 Release" 
   cd "..\server"

"proxy - Win64 ReleaseCLEAN" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy64.mak CFG="proxy - Win64 Release" RECURSE=1 CLEAN 
   cd "..\server"

!ELSEIF  "$(CFG)" == "AsyncServer - Win64 Debug"

"proxy - Win64 Debug" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy64.mak CFG="proxy - Win64 Debug" 
   cd "..\server"

"proxy - Win64 DebugCLEAN" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy64.mak CFG="proxy - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\server"

!ENDIF 


!ENDIF 
