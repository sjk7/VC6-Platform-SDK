!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on SyncComp.dsp
!IF "$(CFG)" == ""
CFG=SyncComp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SyncComp - Win32 Debug.
!ENDIF

!IF "$(CFG)" != "SyncComp - Win32 Release MinSize" && "$(CFG)" != "SyncComp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SyncComp.mak" CFG="SyncComp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SyncComp - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "SyncComp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SyncComp - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

#ALL : "$(OUTDIR)\SyncComp.exe" "$(OUTDIR)\SyncComp.pch" "$(OUTDIR)\SyncComp.bsc"
ALL : "$(OUTDIR)\SyncComp.exe" "$(OUTDIR)\SyncComp.pch"

!ELSE 

#ALL : "STAObject - Win32 Release MinSize" "FreeObject - Win32 Release MinSize" "ComSyncObject - Win32 Release MinSize" "$(OUTDIR)\SyncComp.exe" "$(OUTDIR)\SyncComp.pch" "$(OUTDIR)\SyncComp.bsc"
ALL : "STAObject - Win32 Release MinSize" "FreeObject - Win32 Release MinSize" "ComSyncObject - Win32 Release MinSize" "$(OUTDIR)\SyncComp.exe" "$(OUTDIR)\SyncComp.pch"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ComSyncObject - Win32 Release MinSizeCLEAN" "FreeObject - Win32 Release MinSizeCLEAN" "STAObject - Win32 Release MinSizeCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Main.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\SyncComp.obj"
	-@erase "$(INTDIR)\SyncComp.pch"
	-@erase "$(INTDIR)\SyncComp.res"
	-@erase "$(INTDIR)\SyncComp.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SyncComp.bsc"
	-@erase "$(OUTDIR)\SyncComp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /D "_MBCS" /D "_ATL_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SyncComp.res" /d "NDEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\SyncComp.bsc" 
#BSC32_SBRS= \
#	"$(INTDIR)\Main.sbr" \
#	"$(INTDIR)\StdAfx.sbr" \
#	"$(INTDIR)\SyncComp.sbr"
#
#"$(OUTDIR)\SyncComp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
#    $(BSC32) @<<
#  $(BSC32_FLAGS) $(BSC32_SBRS)
#<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\SyncComp.pdb" /machine:$(CPU) /out:"$(OUTDIR)\SyncComp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SyncComp.obj" \
	"$(INTDIR)\SyncComp.res" \
	".\ComSyncObject\ReleaseMinSize\ComSyncObject.lib" \
	".\FreeObject\ReleaseMinSize\FreeObject.lib" \
	".\STAObject\ReleaseMinSize\STAObject.lib"

"$(OUTDIR)\SyncComp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SyncComp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SyncComp.exe" "$(OUTDIR)\SyncComp.pch"

!ELSE 

ALL : "STAObject - Win32 Debug" "FreeObject - Win32 Debug" "ComSyncObject - Win32 Debug" "$(OUTDIR)\SyncComp.exe" "$(OUTDIR)\SyncComp.pch"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"ComSyncObject - Win32 DebugCLEAN" "FreeObject - Win32 DebugCLEAN" "STAObject - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SyncComp.obj"
	-@erase "$(INTDIR)\SyncComp.pch"
	-@erase "$(INTDIR)\SyncComp.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SyncComp.exe"
	-@erase "$(OUTDIR)\SyncComp.ilk"
	-@erase "$(OUTDIR)\SyncComp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_DEBUG_OBJECTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SyncComp.res" /d "_DEBUG" 
#BSC32=bscmake.exe
#BSC32_FLAGS=/nologo /o"$(OUTDIR)\SyncComp.bsc" 
#BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\SyncComp.pdb" /debug /machine:$(CPU) /out:"$(OUTDIR)\SyncComp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SyncComp.obj" \
	"$(INTDIR)\SyncComp.res" \
	".\ComSyncObject\Debug\ComSyncObject.lib" \
	".\FreeObject\Debug\FreeObject.lib" \
	".\STAObject\Debug\STAObject.lib"

"$(OUTDIR)\SyncComp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SyncComp.dep")
!INCLUDE "SyncComp.dep"
!ELSE 
!MESSAGE Warning: cannot find "SyncComp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SyncComp - Win32 Release MinSize" || "$(CFG)" == "SyncComp - Win32 Debug"
SOURCE=.\Main.cpp

!IF  "$(CFG)" == "SyncComp - Win32 Release MinSize"


#"$(INTDIR)\Main.obj"	"$(INTDIR)\Main.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\Main.obj"	: $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SyncComp - Win32 Debug"


"$(INTDIR)\Main.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SyncComp - Win32 Release MinSize"

CPP_SWITCHES=/nologo /ML /W3 /O1 /D "_MBCS" /D "_ATL_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SyncComp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

#"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\SyncComp.pch" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SyncComp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SyncComp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_DEBUG_OBJECTS" /Fp"$(INTDIR)\SyncComp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SyncComp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\SyncComp.cpp

!IF  "$(CFG)" == "SyncComp - Win32 Release MinSize"


#"$(INTDIR)\SyncComp.obj"	"$(INTDIR)\SyncComp.sbr" : $(SOURCE) "$(INTDIR)"
"$(INTDIR)\SyncComp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SyncComp - Win32 Debug"


"$(INTDIR)\SyncComp.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SyncComp.idl
SOURCE=.\SyncComp.rc

"$(INTDIR)\SyncComp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "SyncComp - Win32 Release MinSize"

"ComSyncObject - Win32 Release MinSize" : 
   cd ".\ComSyncObject"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSyncObject.mak CFG="ComSyncObject - Win32 Release MinSize" 
   cd ".."

"ComSyncObject - Win32 Release MinSizeCLEAN" : 
   cd ".\ComSyncObject"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSyncObject.mak CFG="ComSyncObject - Win32 Release MinSize" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "SyncComp - Win32 Debug"

"ComSyncObject - Win32 Debug" : 
   cd ".\ComSyncObject"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSyncObject.mak CFG="ComSyncObject - Win32 Debug" 
   cd ".."

"ComSyncObject - Win32 DebugCLEAN" : 
   cd ".\ComSyncObject"
   $(MAKE) /$(MAKEFLAGS) /F .\ComSyncObject.mak CFG="ComSyncObject - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "SyncComp - Win32 Release MinSize"

"FreeObject - Win32 Release MinSize" : 
   cd ".\FreeObject"
   $(MAKE) /$(MAKEFLAGS) /F .\FreeObject.mak CFG="FreeObject - Win32 Release MinSize" 
   cd ".."

"FreeObject - Win32 Release MinSizeCLEAN" : 
   cd ".\FreeObject"
   $(MAKE) /$(MAKEFLAGS) /F .\FreeObject.mak CFG="FreeObject - Win32 Release MinSize" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "SyncComp - Win32 Debug"

"FreeObject - Win32 Debug" : 
   cd ".\FreeObject"
   $(MAKE) /$(MAKEFLAGS) /F .\FreeObject.mak CFG="FreeObject - Win32 Debug" 
   cd ".."

"FreeObject - Win32 DebugCLEAN" : 
   cd ".\FreeObject"
   $(MAKE) /$(MAKEFLAGS) /F .\FreeObject.mak CFG="FreeObject - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "SyncComp - Win32 Release MinSize"

"STAObject - Win32 Release MinSize" : 
   cd ".\STAObject"
   $(MAKE) /$(MAKEFLAGS) /F .\STAObject.mak CFG="STAObject - Win32 Release MinSize" 
   cd ".."

"STAObject - Win32 Release MinSizeCLEAN" : 
   cd ".\STAObject"
   $(MAKE) /$(MAKEFLAGS) /F .\STAObject.mak CFG="STAObject - Win32 Release MinSize" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "SyncComp - Win32 Debug"

"STAObject - Win32 Debug" : 
   cd ".\STAObject"
   $(MAKE) /$(MAKEFLAGS) /F .\STAObject.mak CFG="STAObject - Win32 Debug" 
   cd ".."

"STAObject - Win32 DebugCLEAN" : 
   cd ".\STAObject"
   $(MAKE) /$(MAKEFLAGS) /F .\STAObject.mak CFG="STAObject - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 


!ENDIF 

