# Microsoft Developer Studio Generated NMAKE File, Based on client.dsp
!IF "$(CFG)" == ""
CFG=client - Win32 Debug
!MESSAGE No configuration specified. Defaulting to client - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "client - Win32 Release" && "$(CFG)" != "client - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "client.mak" CFG="client - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "client - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "client - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "client - Win32 Release"

OUTDIR=.\../Bin/Release/x86
INTDIR=.\../Bin/Release/x86
# Begin Custom Macros
OutDir=.\../Bin/Release/x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\client.exe"

!ELSE 

ALL : "AsyncServer - Win32 Release" "idl - Win32 Release" "proxy - Win32 Release" "$(OUTDIR)\client.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"proxy - Win32 ReleaseCLEAN" "idl - Win32 ReleaseCLEAN" "AsyncServer - Win32 ReleaseCLEAN" 
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

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\ps_Win32" /D "NDEBUG" /D "_SECURE_" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0X500 /D "_ASYNC_COM_" /D "_EVENTSINK_" /Fp"$(INTDIR)\client.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\client.pdb" /machine:I386 /out:"$(OUTDIR)\client.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Proxy_i.obj" \
	"$(OUTDIR)\proxy.lib"

"$(OUTDIR)\client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "client - Win32 Debug"

OUTDIR=.\../Bin/Debug/x86
INTDIR=.\../Bin/Debug/x86
# Begin Custom Macros
OutDir=.\../Bin/Debug/x86
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\client.exe"

!ELSE 

ALL : "AsyncServer - Win32 Debug" "idl - Win32 Debug" "proxy - Win32 Debug" "$(OUTDIR)\client.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"proxy - Win32 DebugCLEAN" "idl - Win32 DebugCLEAN" "AsyncServer - Win32 DebugCLEAN" 
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

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\ps_Win32" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0X500 /D "_ASYNC_COM_" /D "_EVENTSINK_" /D "_SECURE_" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\client.pdb" /debug /machine:I386 /out:"$(OUTDIR)\client.exe" /pdbtype:sept 
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


!IF "$(CFG)" == "client - Win32 Release" || "$(CFG)" == "client - Win32 Debug"
SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\Server\debug.c

"$(INTDIR)\debug.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\ps_win32\Proxy_i.c

"$(INTDIR)\Proxy_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "client - Win32 Release"

"proxy - Win32 Release" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy.mak CFG="proxy - Win32 Release" 
   cd "..\client"

"proxy - Win32 ReleaseCLEAN" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy.mak CFG="proxy - Win32 Release" RECURSE=1 CLEAN 
   cd "..\client"

!ELSEIF  "$(CFG)" == "client - Win32 Debug"

"proxy - Win32 Debug" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy.mak CFG="proxy - Win32 Debug" 
   cd "..\client"

"proxy - Win32 DebugCLEAN" : 
   cd "..\proxy"
   $(MAKE) /$(MAKEFLAGS) /F .\proxy.mak CFG="proxy - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\client"

!ENDIF 

!IF  "$(CFG)" == "client - Win32 Release"

"idl - Win32 Release" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Release" 
   cd "..\client"

"idl - Win32 ReleaseCLEAN" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Release" RECURSE=1 CLEAN 
   cd "..\client"

!ELSEIF  "$(CFG)" == "client - Win32 Debug"

"idl - Win32 Debug" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Debug" 
   cd "..\client"

"idl - Win32 DebugCLEAN" : 
   cd "..\idl"
   $(MAKE) /$(MAKEFLAGS) /F .\idl.mak CFG="idl - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\client"

!ENDIF 

!IF  "$(CFG)" == "client - Win32 Release"

"AsyncServer - Win32 Release" : 
   cd "..\server"
   $(MAKE) /$(MAKEFLAGS) /F .\AsyncServer.mak CFG="AsyncServer - Win32 Release" 
   cd "..\client"

"AsyncServer - Win32 ReleaseCLEAN" : 
   cd "..\server"
   $(MAKE) /$(MAKEFLAGS) /F .\AsyncServer.mak CFG="AsyncServer - Win32 Release" RECURSE=1 CLEAN 
   cd "..\client"

!ELSEIF  "$(CFG)" == "client - Win32 Debug"

"AsyncServer - Win32 Debug" : 
   cd "..\server"
   $(MAKE) /$(MAKEFLAGS) /F .\AsyncServer.mak CFG="AsyncServer - Win32 Debug" 
   cd "..\client"

"AsyncServer - Win32 DebugCLEAN" : 
   cd "..\server"
   $(MAKE) /$(MAKEFLAGS) /F .\AsyncServer.mak CFG="AsyncServer - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\client"

!ENDIF 


!ENDIF 

