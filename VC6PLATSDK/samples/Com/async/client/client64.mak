
# Microsoft Developer Studio Generated NMAKE File, Based on client.dsp
!IF "$(CFG)" == ""
CFG=client - Win64 Debug
!MESSAGE No configuration specified. Defaulting to client - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "client - Win64 Release" && "$(CFG)" != "client - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "client64.mak" CFG="client - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "client - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "client - Win64 Debug" (based on "Win64 (IA64) Console Application")
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

!IF  "$(CFG)" == "client - Win64 Release"

OUTDIR=.\../Bin/Release/IA64
INTDIR=.\../Bin/Release/IA64
# Begin Custom Macros
OutDir=.\../Bin/Release/IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\client.exe"

!ELSE 

ALL : "AsyncServer - Win64 Release" "idl - Win64 Release" "proxy - Win64 Release" "$(OUTDIR)\client.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"proxy - Win64 ReleaseCLEAN" "idl - Win64 ReleaseCLEAN" "AsyncServer - Win64 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\Proxy_i.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\client.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /Wp64 /GX /O2 /I "..\ps_Win64" /D "NDEBUG" /D "_SECURE_" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0X500 /D "_ASYNC_COM_" /D "_EVENTSINK_" /Fp"$(INTDIR)\client.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\client.pdb" /machine:IA64 /out:"$(OUTDIR)\client.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Proxy_i.obj" \
	"$(OUTDIR)\proxy.lib"

"$(OUTDIR)\client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "client - Win64 Debug"

OUTDIR=.\../Bin/Debug/IA64
INTDIR=.\../Bin/Debug/IA64
# Begin Custom Macros
OutDir=.\../Bin/Debug/IA64
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\client.exe"

!ELSE 

ALL : "AsyncServer - Win64 Debug" "idl - Win64 Debug" "proxy - Win64 Debug" "$(OUTDIR)\client.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"proxy - Win64 DebugCLEAN" "idl - Win64 DebugCLEAN" "AsyncServer - Win64 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\Proxy_i.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\client.exe"
	-@erase "$(OUTDIR)\client.ilk"
	-@erase "$(OUTDIR)\client.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Wp64 /Gm /GX /Zi /Od /I "..\ps_Win64" /D "_DEBUG" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0X500 /D "_ASYNC_COM_" /D "_EVENTSINK_" /D "_SECURE_" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\client.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\client.exe"  
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Proxy_i.obj" \
	"$(OUTDIR)\proxy.lib"

"$(OUTDIR)\client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("client.dep")
!INCLUDE "client.dep"
!ELSE 
!MESSAGE Warning: cannot find "client.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "client - Win64 Release" || "$(CFG)" == "client - Win64 Debug"
SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\Server\debug.c

"$(INTDIR)\debug.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ps_win64\Proxy_i.c

"$(INTDIR)\Proxy_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "client - Win64 Release"

"proxy - Win64 Release" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy64.mak CFG="proxy - Win64 Release" 
   cd "..\client"

"proxy - Win64 ReleaseCLEAN" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy64.mak CFG="proxy - Win64 Release" RECURSE=1 CLEAN 
   cd "..\client"

!ELSEIF  "$(CFG)" == "client - Win64 Debug"

"proxy - Win64 Debug" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy64.mak CFG="proxy - Win64 Debug" 
   cd "..\client"

"proxy - Win64 DebugCLEAN" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy64.mak CFG="proxy - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\client"

!ENDIF 

!IF  "$(CFG)" == "client - Win64 Release"

"idl - Win64 Release" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Release" 
   cd "..\client"

"idl - Win64 ReleaseCLEAN" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Release" RECURSE=1 CLEAN 
   cd "..\client"

!ELSEIF  "$(CFG)" == "client - Win64 Debug"

"idl - Win64 Debug" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" 
   cd "..\client"

"idl - Win64 DebugCLEAN" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl64.mak CFG="idl - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\client"

!ENDIF 

!IF  "$(CFG)" == "client - Win64 Release"

"AsyncServer - Win64 Release" : 
   cd "..\server"
   $(MAKE) /$(MAKEFLAGS) /F .\AsyncServer64.mak CFG="AsyncServer - Win64 Release" 
   cd "..\client"

"AsyncServer - Win64 ReleaseCLEAN" : 
   cd "..\server"
   $(MAKE) /$(MAKEFLAGS) /F .\AsyncServer64.mak CFG="AsyncServer - Win64 Release" RECURSE=1 CLEAN 
   cd "..\client"

!ELSEIF  "$(CFG)" == "client - Win64 Debug"

"AsyncServer - Win64 Debug" : 
   cd "..\server"
   $(MAKE) /$(MAKEFLAGS) /F .\AsyncServer64.mak CFG="AsyncServer - Win64 Debug" 
   cd "..\client"

"AsyncServer - Win64 DebugCLEAN" : 
   cd "..\server"
   $(MAKE) /$(MAKEFLAGS) /F .\AsyncServer64.mak CFG="AsyncServer - Win64 Debug" RECURSE=1 CLEAN 
   cd "..\client"

!ENDIF 


!ENDIF 
