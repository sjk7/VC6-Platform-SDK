# Microsoft Developer Studio Generated NMAKE File, Based on tbarext.dsp
!IF "$(CFG)" == ""
CFG=TBarExt - Win32 Ansi Debug
!MESSAGE No configuration specified. Defaulting to TBarExt - Win32 Ansi Debug.
!ENDIF 

!IF "$(CFG)" != "TBarExt - Win32 Release" && "$(CFG)" != "TBarExt - Win32 Debug" && "$(CFG)" != "TBarExt - Win32 Ansi Debug" && "$(CFG)" != "TBarExt - Win32 Ansi Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tbarext.mak" CFG="TBarExt - Win32 Ansi Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TBarExt - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TBarExt - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TBarExt - Win32 Ansi Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TBarExt - Win32 Ansi Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "TBarExt - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\tbarext.dll" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\basesnap.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\resource.res"
	-@erase "$(INTDIR)\TBarExt.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\tbarext.dll"
	-@erase "$(OUTDIR)\tbarext.exp"
	-@erase "$(OUTDIR)\tbarext.lib"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TBarExt_EXPORTS" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\tbarext.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tbarext.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x13000000" /dll /incremental:no /pdb:"$(OUTDIR)\tbarext.pdb" /machine:I386 /def:".\basesnap.def" /out:"$(OUTDIR)\tbarext.dll" /implib:"$(OUTDIR)\tbarext.lib" 
DEF_FILE= \
	".\basesnap.def"
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\basesnap.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\TBarExt.obj" \
	"$(INTDIR)\resource.res"

"$(OUTDIR)\tbarext.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\tbarext.dll
InputPath=.\Release\tbarext.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "TBarExt - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\tbarext.dll" "$(OUTDIR)\tbarext.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\about.sbr"
	-@erase "$(INTDIR)\basesnap.obj"
	-@erase "$(INTDIR)\basesnap.sbr"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\registry.sbr"
	-@erase "$(INTDIR)\resource.res"
	-@erase "$(INTDIR)\TBarExt.obj"
	-@erase "$(INTDIR)\TBarExt.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\tbarext.bsc"
	-@erase "$(OUTDIR)\tbarext.dll"
	-@erase "$(OUTDIR)\tbarext.exp"
	-@erase "$(OUTDIR)\tbarext.ilk"
	-@erase "$(OUTDIR)\tbarext.lib"
	-@erase "$(OUTDIR)\tbarext.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "_UNICODE" /D "UNICODE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tbarext.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\about.sbr" \
	"$(INTDIR)\basesnap.sbr" \
	"$(INTDIR)\registry.sbr" \
	"$(INTDIR)\TBarExt.sbr"

"$(OUTDIR)\tbarext.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x13000000" /dll /incremental:yes /pdb:"$(OUTDIR)\tbarext.pdb" /debug /machine:I386 /def:".\basesnap.def" /out:"$(OUTDIR)\tbarext.dll" /implib:"$(OUTDIR)\tbarext.lib" /pdbtype:sept 
DEF_FILE= \
	".\basesnap.def"
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\basesnap.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\TBarExt.obj" \
	"$(INTDIR)\resource.res"

"$(OUTDIR)\tbarext.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\tbarext.dll
InputPath=.\Debug\tbarext.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "TBarExt - Win32 Ansi Debug"

OUTDIR=.\Ansi_debug
INTDIR=.\Ansi_debug
# Begin Custom Macros
OutDir=.\Ansi_debug
# End Custom Macros

ALL : "$(OUTDIR)\tbarext.dll" "$(OUTDIR)\tbarext.bsc" ".\Ansi_debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\about.sbr"
	-@erase "$(INTDIR)\basesnap.obj"
	-@erase "$(INTDIR)\basesnap.sbr"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\registry.sbr"
	-@erase "$(INTDIR)\resource.res"
	-@erase "$(INTDIR)\TBarExt.obj"
	-@erase "$(INTDIR)\TBarExt.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\tbarext.bsc"
	-@erase "$(OUTDIR)\tbarext.dll"
	-@erase "$(OUTDIR)\tbarext.exp"
	-@erase "$(OUTDIR)\tbarext.ilk"
	-@erase "$(OUTDIR)\tbarext.lib"
	-@erase "$(OUTDIR)\tbarext.pdb"
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tbarext.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\about.sbr" \
	"$(INTDIR)\basesnap.sbr" \
	"$(INTDIR)\registry.sbr" \
	"$(INTDIR)\TBarExt.sbr"

"$(OUTDIR)\tbarext.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x13000000" /dll /incremental:yes /pdb:"$(OUTDIR)\tbarext.pdb" /debug /machine:I386 /def:".\basesnap.def" /out:"$(OUTDIR)\tbarext.dll" /implib:"$(OUTDIR)\tbarext.lib" /pdbtype:sept 
DEF_FILE= \
	".\basesnap.def"
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\basesnap.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\TBarExt.obj" \
	"$(INTDIR)\resource.res"

"$(OUTDIR)\tbarext.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_debug
TargetPath=.\Ansi_debug\tbarext.dll
InputPath=.\Ansi_debug\tbarext.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "TBarExt - Win32 Ansi Release"

OUTDIR=.\Ansi_release
INTDIR=.\Ansi_release
# Begin Custom Macros
OutDir=.\Ansi_release
# End Custom Macros

ALL : "$(OUTDIR)\tbarext.dll" ".\Ansi_release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\about.obj"
	-@erase "$(INTDIR)\basesnap.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\resource.res"
	-@erase "$(INTDIR)\TBarExt.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\tbarext.dll"
	-@erase "$(OUTDIR)\tbarext.exp"
	-@erase "$(OUTDIR)\tbarext.lib"
	-@erase ".\Ansi_release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TBarExt_EXPORTS" /Fp"$(INTDIR)\tbarext.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tbarext.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mmc.lib /nologo /base:"0x13000000" /dll /incremental:no /pdb:"$(OUTDIR)\tbarext.pdb" /machine:I386 /def:".\basesnap.def" /out:"$(OUTDIR)\tbarext.dll" /implib:"$(OUTDIR)\tbarext.lib" 
DEF_FILE= \
	".\basesnap.def"
LINK32_OBJS= \
	"$(INTDIR)\about.obj" \
	"$(INTDIR)\basesnap.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\TBarExt.obj" \
	"$(INTDIR)\resource.res"

"$(OUTDIR)\tbarext.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Ansi_release
TargetPath=.\Ansi_release\tbarext.dll
InputPath=.\Ansi_release\tbarext.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("tbarext.dep")
!INCLUDE "tbarext.dep"
!ELSE 
!MESSAGE Warning: cannot find "tbarext.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TBarExt - Win32 Release" || "$(CFG)" == "TBarExt - Win32 Debug" || "$(CFG)" == "TBarExt - Win32 Ansi Debug" || "$(CFG)" == "TBarExt - Win32 Ansi Release"
SOURCE=.\about.cpp

!IF  "$(CFG)" == "TBarExt - Win32 Release"


"$(INTDIR)\about.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Debug"


"$(INTDIR)\about.obj"	"$(INTDIR)\about.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Ansi Debug"


"$(INTDIR)\about.obj"	"$(INTDIR)\about.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Ansi Release"


"$(INTDIR)\about.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\basesnap.cpp

!IF  "$(CFG)" == "TBarExt - Win32 Release"


"$(INTDIR)\basesnap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Debug"


"$(INTDIR)\basesnap.obj"	"$(INTDIR)\basesnap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Ansi Debug"


"$(INTDIR)\basesnap.obj"	"$(INTDIR)\basesnap.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Ansi Release"


"$(INTDIR)\basesnap.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\registry.cpp

!IF  "$(CFG)" == "TBarExt - Win32 Release"


"$(INTDIR)\registry.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Debug"


"$(INTDIR)\registry.obj"	"$(INTDIR)\registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Ansi Debug"


"$(INTDIR)\registry.obj"	"$(INTDIR)\registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Ansi Release"


"$(INTDIR)\registry.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\TBarExt.cpp

!IF  "$(CFG)" == "TBarExt - Win32 Release"


"$(INTDIR)\TBarExt.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Debug"


"$(INTDIR)\TBarExt.obj"	"$(INTDIR)\TBarExt.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Ansi Debug"


"$(INTDIR)\TBarExt.obj"	"$(INTDIR)\TBarExt.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TBarExt - Win32 Ansi Release"


"$(INTDIR)\TBarExt.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\resource.rc

"$(INTDIR)\resource.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

