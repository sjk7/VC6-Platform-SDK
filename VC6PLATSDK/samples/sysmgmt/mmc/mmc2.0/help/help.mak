# Microsoft Developer Studio Generated NMAKE File, Based on Help.dsp
!IF "$(CFG)" == ""
CFG=Help - Win32 Ansi Debug
!MESSAGE No configuration specified. Defaulting to Help - Win32 Ansi Debug.
!ENDIF 

!IF "$(CFG)" != "Help - Win32 Debug" && "$(CFG)" != "Help - Win32 Release" && "$(CFG)" != "Help - Win32 Ansi Debug" && "$(CFG)" != "Help - Win32 Ansi Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Help.mak" CFG="Help - Win32 Ansi Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Help - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Help - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Help - Win32 Ansi Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Help - Win32 Ansi Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Help - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Help.dll" "$(OUTDIR)\Help.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\AddDeviceDlg.obj"
	-@erase "$(INTDIR)\AddDeviceDlg.sbr"
	-@erase "$(INTDIR)\AddVFileDlg.obj"
	-@erase "$(INTDIR)\AddVFileDlg.sbr"
	-@erase "$(INTDIR)\BaseDialog.obj"
	-@erase "$(INTDIR)\BaseDialog.sbr"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\BaseSnap.sbr"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\Comp.sbr"
	-@erase "$(INTDIR)\Compdata.obj"
	-@erase "$(INTDIR)\Compdata.sbr"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\Dataobj.sbr"
	-@erase "$(INTDIR)\DeviceNode.obj"
	-@erase "$(INTDIR)\DeviceNode.sbr"
	-@erase "$(INTDIR)\FolderNode.obj"
	-@erase "$(INTDIR)\FolderNode.sbr"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Globals.sbr"
	-@erase "$(INTDIR)\Help.res"
	-@erase "$(INTDIR)\LListImpl.obj"
	-@erase "$(INTDIR)\LListImpl.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\StaticNode.obj"
	-@erase "$(INTDIR)\StaticNode.sbr"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\TraceMacro.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VirtualFile.obj"
	-@erase "$(INTDIR)\VirtualFile.sbr"
	-@erase "$(OUTDIR)\Help.bsc"
	-@erase "$(OUTDIR)\Help.dll"
	-@erase "$(OUTDIR)\Help.exp"
	-@erase "$(OUTDIR)\Help.ilk"
	-@erase "$(OUTDIR)\Help.lib"
	-@erase "$(OUTDIR)\Help.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HELP_EXPORTS" /D "_UNICODE" /D "UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Help.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Help.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Help.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\AddDeviceDlg.sbr" \
	"$(INTDIR)\AddVFileDlg.sbr" \
	"$(INTDIR)\BaseDialog.sbr" \
	"$(INTDIR)\BaseSnap.sbr" \
	"$(INTDIR)\Comp.sbr" \
	"$(INTDIR)\Compdata.sbr" \
	"$(INTDIR)\Dataobj.sbr" \
	"$(INTDIR)\DeviceNode.sbr" \
	"$(INTDIR)\FolderNode.sbr" \
	"$(INTDIR)\Globals.sbr" \
	"$(INTDIR)\LListImpl.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\StaticNode.sbr" \
	"$(INTDIR)\TraceMacro.sbr" \
	"$(INTDIR)\VirtualFile.sbr"

"$(OUTDIR)\Help.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=mmc.lib comctl32.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\Help.pdb" /debug /machine:$(CPU) /def:".\Help.Def" /out:"$(OUTDIR)\Help.dll" /implib:"$(OUTDIR)\Help.lib" /pdbtype:sept 
DEF_FILE= \
	".\Help.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\AddDeviceDlg.obj" \
	"$(INTDIR)\AddVFileDlg.obj" \
	"$(INTDIR)\BaseDialog.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\Compdata.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DeviceNode.obj" \
	"$(INTDIR)\FolderNode.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\LListImpl.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StaticNode.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\VirtualFile.obj" \
	"$(INTDIR)\Help.res"

"$(OUTDIR)\Help.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\Help.dll
InputPath=.\Debug\Help.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Help - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Help.dll" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\AddDeviceDlg.obj"
	-@erase "$(INTDIR)\AddVFileDlg.obj"
	-@erase "$(INTDIR)\BaseDialog.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\Compdata.obj"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\DeviceNode.obj"
	-@erase "$(INTDIR)\FolderNode.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Help.res"
	-@erase "$(INTDIR)\LListImpl.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\StaticNode.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VirtualFile.obj"
	-@erase "$(OUTDIR)\Help.dll"
	-@erase "$(OUTDIR)\Help.exp"
	-@erase "$(OUTDIR)\Help.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HELP_EXPORTS" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\Help.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Help.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Help.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib comctl32.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\Help.pdb" /machine:$(CPU) /def:".\Help.Def" /out:"$(OUTDIR)\Help.dll" /implib:"$(OUTDIR)\Help.lib" 
DEF_FILE= \
	".\Help.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\AddDeviceDlg.obj" \
	"$(INTDIR)\AddVFileDlg.obj" \
	"$(INTDIR)\BaseDialog.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\Compdata.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DeviceNode.obj" \
	"$(INTDIR)\FolderNode.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\LListImpl.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StaticNode.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\VirtualFile.obj" \
	"$(INTDIR)\Help.res"

"$(OUTDIR)\Help.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\Help.dll
InputPath=.\Release\Help.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"

OUTDIR=.\Ansi_debug
INTDIR=.\Ansi_debug
# Begin Custom Macros
OutDir=.\Ansi_debug
# End Custom Macros

ALL : "$(OUTDIR)\Help.dll" ".\Ansi_debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\AddDeviceDlg.obj"
	-@erase "$(INTDIR)\AddVFileDlg.obj"
	-@erase "$(INTDIR)\BaseDialog.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\Compdata.obj"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\DeviceNode.obj"
	-@erase "$(INTDIR)\FolderNode.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Help.res"
	-@erase "$(INTDIR)\LListImpl.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\StaticNode.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VirtualFile.obj"
	-@erase "$(OUTDIR)\Help.dll"
	-@erase "$(OUTDIR)\Help.exp"
	-@erase "$(OUTDIR)\Help.ilk"
	-@erase "$(OUTDIR)\Help.lib"
	-@erase "$(OUTDIR)\Help.pdb"
	-@erase ".\Ansi_debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HELP_EXPORTS" /Fp"$(INTDIR)\Help.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Help.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Help.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib comctl32.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\Help.pdb" /debug /machine:$(CPU) /def:".\Help.Def" /out:"$(OUTDIR)\Help.dll" /implib:"$(OUTDIR)\Help.lib" /pdbtype:sept 
DEF_FILE= \
	".\Help.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\AddDeviceDlg.obj" \
	"$(INTDIR)\AddVFileDlg.obj" \
	"$(INTDIR)\BaseDialog.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\Compdata.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DeviceNode.obj" \
	"$(INTDIR)\FolderNode.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\LListImpl.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StaticNode.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\VirtualFile.obj" \
	"$(INTDIR)\Help.res"

"$(OUTDIR)\Help.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_debug
TargetPath=.\Ansi_debug\Help.dll
InputPath=.\Ansi_debug\Help.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"

OUTDIR=.\Ansi_release
INTDIR=.\Ansi_release
# Begin Custom Macros
OutDir=.\Ansi_release
# End Custom Macros

ALL : "$(OUTDIR)\Help.dll" ".\Ansi_release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\AddDeviceDlg.obj"
	-@erase "$(INTDIR)\AddVFileDlg.obj"
	-@erase "$(INTDIR)\BaseDialog.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\Comp.obj"
	-@erase "$(INTDIR)\Compdata.obj"
	-@erase "$(INTDIR)\Dataobj.obj"
	-@erase "$(INTDIR)\DeviceNode.obj"
	-@erase "$(INTDIR)\FolderNode.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Help.res"
	-@erase "$(INTDIR)\LListImpl.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\StaticNode.obj"
	-@erase "$(INTDIR)\TraceMacro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VirtualFile.obj"
	-@erase "$(OUTDIR)\Help.dll"
	-@erase "$(OUTDIR)\Help.exp"
	-@erase "$(OUTDIR)\Help.lib"
	-@erase ".\Ansi_release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HELP_EXPORTS" /Fp"$(INTDIR)\Help.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Help.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Help.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mmc.lib comctl32.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\Help.pdb" /machine:$(CPU) /def:".\Help.Def" /out:"$(OUTDIR)\Help.dll" /implib:"$(OUTDIR)\Help.lib" 
DEF_FILE= \
	".\Help.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\AddDeviceDlg.obj" \
	"$(INTDIR)\AddVFileDlg.obj" \
	"$(INTDIR)\BaseDialog.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\Comp.obj" \
	"$(INTDIR)\Compdata.obj" \
	"$(INTDIR)\Dataobj.obj" \
	"$(INTDIR)\DeviceNode.obj" \
	"$(INTDIR)\FolderNode.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\LListImpl.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\StaticNode.obj" \
	"$(INTDIR)\TraceMacro.obj" \
	"$(INTDIR)\VirtualFile.obj" \
	"$(INTDIR)\Help.res"

"$(OUTDIR)\Help.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_release
TargetPath=.\Ansi_release\Help.dll
InputPath=.\Ansi_release\Help.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Help.dep")
!INCLUDE "Help.dep"
!ELSE 
!MESSAGE Warning: cannot find "Help.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Help - Win32 Debug" || "$(CFG)" == "Help - Win32 Release" || "$(CFG)" == "Help - Win32 Ansi Debug" || "$(CFG)" == "Help - Win32 Ansi Release"
SOURCE=.\About.Cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\AddDeviceDlg.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\AddDeviceDlg.obj"	"$(INTDIR)\AddDeviceDlg.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\AddDeviceDlg.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\AddDeviceDlg.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\AddDeviceDlg.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\AddVFileDlg.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\AddVFileDlg.obj"	"$(INTDIR)\AddVFileDlg.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\AddVFileDlg.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\AddVFileDlg.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\AddVFileDlg.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\BaseDialog.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\BaseDialog.obj"	"$(INTDIR)\BaseDialog.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\BaseDialog.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\BaseDialog.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\BaseDialog.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\BaseSnap.Cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\BaseSnap.obj"	"$(INTDIR)\BaseSnap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Comp.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\Comp.obj"	"$(INTDIR)\Comp.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\Comp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\Comp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\Comp.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Compdata.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\Compdata.obj"	"$(INTDIR)\Compdata.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\Compdata.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\Compdata.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\Compdata.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Dataobj.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\Dataobj.obj"	"$(INTDIR)\Dataobj.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\Dataobj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\Dataobj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\Dataobj.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeviceNode.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\DeviceNode.obj"	"$(INTDIR)\DeviceNode.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\DeviceNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\DeviceNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\DeviceNode.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\FolderNode.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\FolderNode.obj"	"$(INTDIR)\FolderNode.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\FolderNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\FolderNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\FolderNode.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Globals.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\Globals.obj"	"$(INTDIR)\Globals.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Help.rc

"$(INTDIR)\Help.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\LListImpl.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\LListImpl.obj"	"$(INTDIR)\LListImpl.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\LListImpl.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\LListImpl.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\LListImpl.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Registry.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StaticNode.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\StaticNode.obj"	"$(INTDIR)\StaticNode.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\StaticNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\StaticNode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\StaticNode.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\TraceMacro.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\TraceMacro.obj"	"$(INTDIR)\TraceMacro.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\TraceMacro.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\TraceMacro.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\TraceMacro.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\VirtualFile.cpp

!IF  "$(CFG)" == "Help - Win32 Debug"


"$(INTDIR)\VirtualFile.obj"	"$(INTDIR)\VirtualFile.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Release"


"$(INTDIR)\VirtualFile.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Debug"


"$(INTDIR)\VirtualFile.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Help - Win32 Ansi Release"


"$(INTDIR)\VirtualFile.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

