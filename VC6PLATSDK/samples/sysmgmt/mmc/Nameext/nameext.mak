# Microsoft Developer Studio Generated NMAKE File, Based on nameext.dsp
!IF "$(CFG)" == ""
CFG=NameExt - Win32 Ansi Debug
!MESSAGE No configuration specified. Defaulting to NameExt - Win32 Ansi Debug.
!ENDIF 

!IF "$(CFG)" != "NameExt - Win32 Release" && "$(CFG)" != "NameExt - Win32 Debug" && "$(CFG)" != "NameExt - Win32 Ansi Debug" && "$(CFG)" != "NameExt - Win32 Ansi Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nameext.mak" CFG="NameExt - Win32 Ansi Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NameExt - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NameExt - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NameExt - Win32 Ansi Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NameExt - Win32 Ansi Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "NameExt - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\nameext.dll" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\comp.obj"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\delebase.obj"
	-@erase "$(INTDIR)\mmccrack.obj"
	-@erase "$(INTDIR)\NameExt.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\resource.res"
	-@erase "$(INTDIR)\sky.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\nameext.dll"
	-@erase "$(OUTDIR)\nameext.exp"
	-@erase "$(OUTDIR)\nameext.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NameExt_EXPORTS" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\nameext.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\resource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nameext.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x13000000" /dll /incremental:no /pdb:"$(OUTDIR)\nameext.pdb" /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\nameext.dll" /implib:"$(OUTDIR)\nameext.lib" 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\comp.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\delebase.obj" \
	"$(INTDIR)\mmccrack.obj" \
	"$(INTDIR)\NameExt.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\sky.obj" \
	"$(INTDIR)\resource.res"

"$(OUTDIR)\nameext.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\nameext.dll
InputPath=.\Release\nameext.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "NameExt - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\nameext.dll" "$(OUTDIR)\nameext.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\BaseSnap.sbr"
	-@erase "$(INTDIR)\comp.obj"
	-@erase "$(INTDIR)\comp.sbr"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\dataobj.sbr"
	-@erase "$(INTDIR)\delebase.obj"
	-@erase "$(INTDIR)\delebase.sbr"
	-@erase "$(INTDIR)\mmccrack.obj"
	-@erase "$(INTDIR)\mmccrack.sbr"
	-@erase "$(INTDIR)\NameExt.obj"
	-@erase "$(INTDIR)\NameExt.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\resource.res"
	-@erase "$(INTDIR)\sky.obj"
	-@erase "$(INTDIR)\sky.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\nameext.bsc"
	-@erase "$(OUTDIR)\nameext.dll"
	-@erase "$(OUTDIR)\nameext.exp"
	-@erase "$(OUTDIR)\nameext.ilk"
	-@erase "$(OUTDIR)\nameext.lib"
	-@erase "$(OUTDIR)\nameext.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "UNICODE" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\resource.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nameext.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\BaseSnap.sbr" \
	"$(INTDIR)\comp.sbr" \
	"$(INTDIR)\dataobj.sbr" \
	"$(INTDIR)\delebase.sbr" \
	"$(INTDIR)\mmccrack.sbr" \
	"$(INTDIR)\NameExt.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\sky.sbr"

"$(OUTDIR)\nameext.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x13000000" /dll /incremental:yes /pdb:"$(OUTDIR)\nameext.pdb" /debug /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\nameext.dll" /implib:"$(OUTDIR)\nameext.lib" /pdbtype:sept 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\comp.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\delebase.obj" \
	"$(INTDIR)\mmccrack.obj" \
	"$(INTDIR)\NameExt.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\sky.obj" \
	"$(INTDIR)\resource.res"

"$(OUTDIR)\nameext.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\nameext.dll
InputPath=.\Debug\nameext.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Debug"

OUTDIR=.\Ansi_debug
INTDIR=.\Ansi_debug
# Begin Custom Macros
OutDir=.\Ansi_debug
# End Custom Macros

ALL : "$(OUTDIR)\nameext.dll" "$(OUTDIR)\nameext.bsc" ".\Ansi_debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\About.sbr"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\BaseSnap.sbr"
	-@erase "$(INTDIR)\comp.obj"
	-@erase "$(INTDIR)\comp.sbr"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\dataobj.sbr"
	-@erase "$(INTDIR)\delebase.obj"
	-@erase "$(INTDIR)\delebase.sbr"
	-@erase "$(INTDIR)\mmccrack.obj"
	-@erase "$(INTDIR)\mmccrack.sbr"
	-@erase "$(INTDIR)\NameExt.obj"
	-@erase "$(INTDIR)\NameExt.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\resource.res"
	-@erase "$(INTDIR)\sky.obj"
	-@erase "$(INTDIR)\sky.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\nameext.bsc"
	-@erase "$(OUTDIR)\nameext.dll"
	-@erase "$(OUTDIR)\nameext.exp"
	-@erase "$(OUTDIR)\nameext.ilk"
	-@erase "$(OUTDIR)\nameext.lib"
	-@erase "$(OUTDIR)\nameext.pdb"
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\resource.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nameext.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\About.sbr" \
	"$(INTDIR)\BaseSnap.sbr" \
	"$(INTDIR)\comp.sbr" \
	"$(INTDIR)\dataobj.sbr" \
	"$(INTDIR)\delebase.sbr" \
	"$(INTDIR)\mmccrack.sbr" \
	"$(INTDIR)\NameExt.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\sky.sbr"

"$(OUTDIR)\nameext.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x13000000" /dll /incremental:yes /pdb:"$(OUTDIR)\nameext.pdb" /debug /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\nameext.dll" /implib:"$(OUTDIR)\nameext.lib" /pdbtype:sept 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\comp.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\delebase.obj" \
	"$(INTDIR)\mmccrack.obj" \
	"$(INTDIR)\NameExt.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\sky.obj" \
	"$(INTDIR)\resource.res"

"$(OUTDIR)\nameext.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_debug
TargetPath=.\Ansi_debug\nameext.dll
InputPath=.\Ansi_debug\nameext.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Release"

OUTDIR=.\Ansi_release
INTDIR=.\Ansi_release
# Begin Custom Macros
OutDir=.\Ansi_release
# End Custom Macros

ALL : "$(OUTDIR)\nameext.dll" ".\Ansi_release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\About.obj"
	-@erase "$(INTDIR)\BaseSnap.obj"
	-@erase "$(INTDIR)\comp.obj"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\delebase.obj"
	-@erase "$(INTDIR)\mmccrack.obj"
	-@erase "$(INTDIR)\NameExt.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\resource.res"
	-@erase "$(INTDIR)\sky.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\nameext.dll"
	-@erase "$(OUTDIR)\nameext.exp"
	-@erase "$(OUTDIR)\nameext.lib"
	-@erase ".\Ansi_release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NameExt_EXPORTS" /Fp"$(INTDIR)\nameext.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\resource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\nameext.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x13000000" /dll /incremental:no /pdb:"$(OUTDIR)\nameext.pdb" /machine:I386 /def:".\BaseSnap.Def" /out:"$(OUTDIR)\nameext.dll" /implib:"$(OUTDIR)\nameext.lib" 
DEF_FILE= \
	".\BaseSnap.Def"
LINK32_OBJS= \
	"$(INTDIR)\About.obj" \
	"$(INTDIR)\BaseSnap.obj" \
	"$(INTDIR)\comp.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\delebase.obj" \
	"$(INTDIR)\mmccrack.obj" \
	"$(INTDIR)\NameExt.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\sky.obj" \
	"$(INTDIR)\resource.res"

"$(OUTDIR)\nameext.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_release
TargetPath=.\Ansi_release\nameext.dll
InputPath=.\Ansi_release\nameext.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("nameext.dep")
!INCLUDE "nameext.dep"
!ELSE 
!MESSAGE Warning: cannot find "nameext.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NameExt - Win32 Release" || "$(CFG)" == "NameExt - Win32 Debug" || "$(CFG)" == "NameExt - Win32 Ansi Debug" || "$(CFG)" == "NameExt - Win32 Ansi Release"
SOURCE=.\About.cpp

!IF  "$(CFG)" == "NameExt - Win32 Release"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Debug"


"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Debug"


"$(INTDIR)\About.obj"	"$(INTDIR)\About.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Release"


"$(INTDIR)\About.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\BaseSnap.cpp

!IF  "$(CFG)" == "NameExt - Win32 Release"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Debug"


"$(INTDIR)\BaseSnap.obj"	"$(INTDIR)\BaseSnap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Debug"


"$(INTDIR)\BaseSnap.obj"	"$(INTDIR)\BaseSnap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Release"


"$(INTDIR)\BaseSnap.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\comp.cpp

!IF  "$(CFG)" == "NameExt - Win32 Release"


"$(INTDIR)\comp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Debug"


"$(INTDIR)\comp.obj"	"$(INTDIR)\comp.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Debug"


"$(INTDIR)\comp.obj"	"$(INTDIR)\comp.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Release"


"$(INTDIR)\comp.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\dataobj.cpp

!IF  "$(CFG)" == "NameExt - Win32 Release"


"$(INTDIR)\dataobj.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Debug"


"$(INTDIR)\dataobj.obj"	"$(INTDIR)\dataobj.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Debug"


"$(INTDIR)\dataobj.obj"	"$(INTDIR)\dataobj.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Release"


"$(INTDIR)\dataobj.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\delebase.cpp

!IF  "$(CFG)" == "NameExt - Win32 Release"


"$(INTDIR)\delebase.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Debug"


"$(INTDIR)\delebase.obj"	"$(INTDIR)\delebase.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Debug"


"$(INTDIR)\delebase.obj"	"$(INTDIR)\delebase.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Release"


"$(INTDIR)\delebase.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\mmccrack.cpp

!IF  "$(CFG)" == "NameExt - Win32 Release"


"$(INTDIR)\mmccrack.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Debug"


"$(INTDIR)\mmccrack.obj"	"$(INTDIR)\mmccrack.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Debug"


"$(INTDIR)\mmccrack.obj"	"$(INTDIR)\mmccrack.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Release"


"$(INTDIR)\mmccrack.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\NameExt.cpp

!IF  "$(CFG)" == "NameExt - Win32 Release"


"$(INTDIR)\NameExt.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Debug"


"$(INTDIR)\NameExt.obj"	"$(INTDIR)\NameExt.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Debug"


"$(INTDIR)\NameExt.obj"	"$(INTDIR)\NameExt.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Release"


"$(INTDIR)\NameExt.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Registry.cpp

!IF  "$(CFG)" == "NameExt - Win32 Release"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Debug"


"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Debug"


"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Release"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\sky.cpp

!IF  "$(CFG)" == "NameExt - Win32 Release"


"$(INTDIR)\sky.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Debug"


"$(INTDIR)\sky.obj"	"$(INTDIR)\sky.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Debug"


"$(INTDIR)\sky.obj"	"$(INTDIR)\sky.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NameExt - Win32 Ansi Release"


"$(INTDIR)\sky.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\resource.rc

"$(INTDIR)\resource.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

