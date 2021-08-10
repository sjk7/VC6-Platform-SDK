# Microsoft Developer Studio Generated NMAKE File, Based on wmi.dsp
!IF "$(CFG)" == ""
CFG=WMI - Win32 Ansi Debug
!MESSAGE No configuration specified. Defaulting to WMI - Win32 Ansi Debug.
!ENDIF 

!IF "$(CFG)" != "WMI - Win32 Release" && "$(CFG)" != "WMI - Win32 Debug" && "$(CFG)" != "WMI - Win32 Ansi Release" && "$(CFG)" != "WMI - Win32 Ansi Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wmi.mak" CFG="WMI - Win32 Ansi Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WMI - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WMI - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WMI - Win32 Ansi Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WMI - Win32 Ansi Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "WMI - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\WMISnap.dll" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\basesnap.obj"
	-@erase "$(INTDIR)\comp.obj"
	-@erase "$(INTDIR)\compdata.obj"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\delebase.obj"
	-@erase "$(INTDIR)\land.obj"
	-@erase "$(INTDIR)\mmccrack.obj"
	-@erase "$(INTDIR)\people.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\sky.obj"
	-@erase "$(INTDIR)\space.obj"
	-@erase "$(INTDIR)\statnode.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\WMISnap.dll"
	-@erase "$(OUTDIR)\WMISnap.exp"
	-@erase "$(OUTDIR)\WMISnap.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "_UNICODE" /D "UNICODE" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WMI_EXPORTS" /Fp"$(INTDIR)\wmi.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Resource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wmi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib wbemuuid.lib /nologo /base:"0x11000000" /dll /incremental:no /pdb:"$(OUTDIR)\WMISnap.pdb" /machine:I386 /def:".\basesnap.def" /out:"$(OUTDIR)\WMISnap.dll" /implib:"$(OUTDIR)\WMISnap.lib" 
DEF_FILE= \
	".\basesnap.def"
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\basesnap.obj" \
	"$(INTDIR)\comp.obj" \
	"$(INTDIR)\compdata.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\delebase.obj" \
	"$(INTDIR)\land.obj" \
	"$(INTDIR)\mmccrack.obj" \
	"$(INTDIR)\people.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\sky.obj" \
	"$(INTDIR)\space.obj" \
	"$(INTDIR)\statnode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\WMISnap.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\WMISnap.dll
InputPath=.\Release\WMISnap.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\WMISnap.dll" "$(OUTDIR)\wmi.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\about.sbr"
	-@erase "$(INTDIR)\basesnap.obj"
	-@erase "$(INTDIR)\basesnap.sbr"
	-@erase "$(INTDIR)\comp.obj"
	-@erase "$(INTDIR)\comp.sbr"
	-@erase "$(INTDIR)\compdata.obj"
	-@erase "$(INTDIR)\compdata.sbr"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\dataobj.sbr"
	-@erase "$(INTDIR)\delebase.obj"
	-@erase "$(INTDIR)\delebase.sbr"
	-@erase "$(INTDIR)\land.obj"
	-@erase "$(INTDIR)\land.sbr"
	-@erase "$(INTDIR)\mmccrack.obj"
	-@erase "$(INTDIR)\mmccrack.sbr"
	-@erase "$(INTDIR)\people.obj"
	-@erase "$(INTDIR)\people.sbr"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\registry.sbr"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\sky.obj"
	-@erase "$(INTDIR)\sky.sbr"
	-@erase "$(INTDIR)\space.obj"
	-@erase "$(INTDIR)\space.sbr"
	-@erase "$(INTDIR)\statnode.obj"
	-@erase "$(INTDIR)\statnode.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\wmi.bsc"
	-@erase "$(OUTDIR)\WMISnap.dll"
	-@erase "$(OUTDIR)\WMISnap.exp"
	-@erase "$(OUTDIR)\WMISnap.ilk"
	-@erase "$(OUTDIR)\WMISnap.lib"
	-@erase "$(OUTDIR)\WMISnap.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "UNICODE" /D "_UNICODE" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Resource.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wmi.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\about.sbr" \
	"$(INTDIR)\basesnap.sbr" \
	"$(INTDIR)\comp.sbr" \
	"$(INTDIR)\compdata.sbr" \
	"$(INTDIR)\dataobj.sbr" \
	"$(INTDIR)\delebase.sbr" \
	"$(INTDIR)\land.sbr" \
	"$(INTDIR)\mmccrack.sbr" \
	"$(INTDIR)\people.sbr" \
	"$(INTDIR)\registry.sbr" \
	"$(INTDIR)\sky.sbr" \
	"$(INTDIR)\space.sbr" \
	"$(INTDIR)\statnode.sbr"

"$(OUTDIR)\wmi.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib wbemuuid.lib /nologo /base:"0x11000000" /dll /incremental:yes /pdb:"$(OUTDIR)\WMISnap.pdb" /debug /machine:I386 /def:".\basesnap.def" /out:"$(OUTDIR)\WMISnap.dll" /implib:"$(OUTDIR)\WMISnap.lib" /pdbtype:sept 
DEF_FILE= \
	".\basesnap.def"
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\basesnap.obj" \
	"$(INTDIR)\comp.obj" \
	"$(INTDIR)\compdata.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\delebase.obj" \
	"$(INTDIR)\land.obj" \
	"$(INTDIR)\mmccrack.obj" \
	"$(INTDIR)\people.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\sky.obj" \
	"$(INTDIR)\space.obj" \
	"$(INTDIR)\statnode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\WMISnap.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\WMISnap.dll
InputPath=.\Debug\WMISnap.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"

OUTDIR=.\Ansi_release
INTDIR=.\Ansi_release
# Begin Custom Macros
OutDir=.\Ansi_release
# End Custom Macros

ALL : "$(OUTDIR)\WMISnap.dll" ".\Ansi_release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\basesnap.obj"
	-@erase "$(INTDIR)\comp.obj"
	-@erase "$(INTDIR)\compdata.obj"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\delebase.obj"
	-@erase "$(INTDIR)\land.obj"
	-@erase "$(INTDIR)\mmccrack.obj"
	-@erase "$(INTDIR)\people.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\sky.obj"
	-@erase "$(INTDIR)\space.obj"
	-@erase "$(INTDIR)\statnode.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\WMISnap.dll"
	-@erase "$(OUTDIR)\WMISnap.exp"
	-@erase "$(OUTDIR)\WMISnap.lib"
	-@erase ".\Ansi_release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WMI_EXPORTS" /Fp"$(INTDIR)\wmi.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Resource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wmi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib wbemuuid.lib /nologo /base:"0x11000000" /dll /incremental:no /pdb:"$(OUTDIR)\WMISnap.pdb" /machine:I386 /def:".\basesnap.def" /out:"$(OUTDIR)\WMISnap.dll" /implib:"$(OUTDIR)\WMISnap.lib" 
DEF_FILE= \
	".\basesnap.def"
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\basesnap.obj" \
	"$(INTDIR)\comp.obj" \
	"$(INTDIR)\compdata.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\delebase.obj" \
	"$(INTDIR)\land.obj" \
	"$(INTDIR)\mmccrack.obj" \
	"$(INTDIR)\people.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\sky.obj" \
	"$(INTDIR)\space.obj" \
	"$(INTDIR)\statnode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\WMISnap.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_release
TargetPath=.\Ansi_release\WMISnap.dll
InputPath=.\Ansi_release\WMISnap.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"

OUTDIR=.\Ansi_debug
INTDIR=.\Ansi_debug
# Begin Custom Macros
OutDir=.\Ansi_debug
# End Custom Macros

ALL : "$(OUTDIR)\WMISnap.dll" "$(OUTDIR)\wmi.bsc" ".\Ansi_debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\about.sbr"
	-@erase "$(INTDIR)\basesnap.obj"
	-@erase "$(INTDIR)\basesnap.sbr"
	-@erase "$(INTDIR)\comp.obj"
	-@erase "$(INTDIR)\comp.sbr"
	-@erase "$(INTDIR)\compdata.obj"
	-@erase "$(INTDIR)\compdata.sbr"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\dataobj.sbr"
	-@erase "$(INTDIR)\delebase.obj"
	-@erase "$(INTDIR)\delebase.sbr"
	-@erase "$(INTDIR)\land.obj"
	-@erase "$(INTDIR)\land.sbr"
	-@erase "$(INTDIR)\mmccrack.obj"
	-@erase "$(INTDIR)\mmccrack.sbr"
	-@erase "$(INTDIR)\people.obj"
	-@erase "$(INTDIR)\people.sbr"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\registry.sbr"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\sky.obj"
	-@erase "$(INTDIR)\sky.sbr"
	-@erase "$(INTDIR)\space.obj"
	-@erase "$(INTDIR)\space.sbr"
	-@erase "$(INTDIR)\statnode.obj"
	-@erase "$(INTDIR)\statnode.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\wmi.bsc"
	-@erase "$(OUTDIR)\WMISnap.dll"
	-@erase "$(OUTDIR)\WMISnap.exp"
	-@erase "$(OUTDIR)\WMISnap.ilk"
	-@erase "$(OUTDIR)\WMISnap.lib"
	-@erase "$(OUTDIR)\WMISnap.pdb"
	-@erase ".\Ansi_debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Resource.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wmi.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\about.sbr" \
	"$(INTDIR)\basesnap.sbr" \
	"$(INTDIR)\comp.sbr" \
	"$(INTDIR)\compdata.sbr" \
	"$(INTDIR)\dataobj.sbr" \
	"$(INTDIR)\delebase.sbr" \
	"$(INTDIR)\land.sbr" \
	"$(INTDIR)\mmccrack.sbr" \
	"$(INTDIR)\people.sbr" \
	"$(INTDIR)\registry.sbr" \
	"$(INTDIR)\sky.sbr" \
	"$(INTDIR)\space.sbr" \
	"$(INTDIR)\statnode.sbr"

"$(OUTDIR)\wmi.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib wbemuuid.lib /nologo /base:"0x11000000" /dll /incremental:yes /pdb:"$(OUTDIR)\WMISnap.pdb" /debug /machine:I386 /def:".\basesnap.def" /out:"$(OUTDIR)\WMISnap.dll" /implib:"$(OUTDIR)\WMISnap.lib" /pdbtype:sept 
DEF_FILE= \
	".\basesnap.def"
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\basesnap.obj" \
	"$(INTDIR)\comp.obj" \
	"$(INTDIR)\compdata.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\delebase.obj" \
	"$(INTDIR)\land.obj" \
	"$(INTDIR)\mmccrack.obj" \
	"$(INTDIR)\people.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\sky.obj" \
	"$(INTDIR)\space.obj" \
	"$(INTDIR)\statnode.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\WMISnap.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_debug
TargetPath=.\Ansi_debug\WMISnap.dll
InputPath=.\Ansi_debug\WMISnap.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("wmi.dep")
!INCLUDE "wmi.dep"
!ELSE 
!MESSAGE Warning: cannot find "wmi.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WMI - Win32 Release" || "$(CFG)" == "WMI - Win32 Debug" || "$(CFG)" == "WMI - Win32 Ansi Release" || "$(CFG)" == "WMI - Win32 Ansi Debug"
SOURCE=.\about.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\about.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\about.obj"	"$(INTDIR)\about.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\about.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\about.obj"	"$(INTDIR)\about.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\basesnap.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\basesnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\basesnap.obj"	"$(INTDIR)\basesnap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\basesnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\basesnap.obj"	"$(INTDIR)\basesnap.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\comp.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\comp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\comp.obj"	"$(INTDIR)\comp.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\comp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\comp.obj"	"$(INTDIR)\comp.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\compdata.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\compdata.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\compdata.obj"	"$(INTDIR)\compdata.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\compdata.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\compdata.obj"	"$(INTDIR)\compdata.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\dataobj.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\dataobj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\dataobj.obj"	"$(INTDIR)\dataobj.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\dataobj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\dataobj.obj"	"$(INTDIR)\dataobj.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\delebase.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\delebase.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\delebase.obj"	"$(INTDIR)\delebase.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\delebase.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\delebase.obj"	"$(INTDIR)\delebase.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\land.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\land.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\land.obj"	"$(INTDIR)\land.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\land.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\land.obj"	"$(INTDIR)\land.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\mmccrack.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\mmccrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\mmccrack.obj"	"$(INTDIR)\mmccrack.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\mmccrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\mmccrack.obj"	"$(INTDIR)\mmccrack.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\people.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\people.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\people.obj"	"$(INTDIR)\people.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\people.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\people.obj"	"$(INTDIR)\people.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\registry.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\registry.obj"	"$(INTDIR)\registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\registry.obj"	"$(INTDIR)\registry.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Resource.rc

"$(INTDIR)\Resource.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\sky.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\sky.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\sky.obj"	"$(INTDIR)\sky.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\sky.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\sky.obj"	"$(INTDIR)\sky.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\space.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\space.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\space.obj"	"$(INTDIR)\space.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\space.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\space.obj"	"$(INTDIR)\space.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\statnode.cpp

!IF  "$(CFG)" == "WMI - Win32 Release"


"$(INTDIR)\statnode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Debug"


"$(INTDIR)\statnode.obj"	"$(INTDIR)\statnode.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Release"


"$(INTDIR)\statnode.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "WMI - Win32 Ansi Debug"


"$(INTDIR)\statnode.obj"	"$(INTDIR)\statnode.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

