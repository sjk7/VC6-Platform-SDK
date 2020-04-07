
# Microsoft Developer Studio Generated NMAKE File, Based on oleimp.dsp
!IF "$(CFG)" == ""
CFG=oleimp - Win64 Debug
!MESSAGE No configuration specified. Defaulting to oleimp - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "oleimp - Win64 Release" && "$(CFG)" != "oleimp - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "oleimp64.mak" CFG="oleimp - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "oleimp - Win64 Release" (based on "Win64 (IA64) Application")
!MESSAGE "oleimp - Win64 Debug" (based on "Win64 (IA64) Application")
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

!IF  "$(CFG)" == "oleimp - Win64 Release"

OUTDIR=.\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\Release\IA64
# End Custom Macros

ALL : "$(OUTDIR)\oleimp.exe"


CLEAN :
	-@erase "$(INTDIR)\oleimp.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\oleimp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /GX /O2 /D "NDEBUG" /D "WIN64" /D "WIN32"  /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\oleimp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win64 $(MIDL_OPTIMIZATION)
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\oleimp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\oleimp.pdb" /machine:IA64 /out:"$(OUTDIR)\oleimp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\oleimp.obj" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\oleimp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "oleimp - Win64 Debug"

OUTDIR=.\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\Debug\IA64
# End Custom Macros

ALL : "$(OUTDIR)\oleimp.exe"


CLEAN :
	-@erase "$(INTDIR)\oleimp.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\oleimp.exe"
	-@erase "$(OUTDIR)\oleimp.ilk"
	-@erase "$(OUTDIR)\oleimp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN64" /D "WIN32"  /D "_WINDOWS" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\oleimp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win64 $(MIDL_OPTIMIZATION)
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\oleimp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\oleimp.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\oleimp.exe"  
LINK32_OBJS= \
	"$(INTDIR)\oleimp.obj" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\oleimp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("oleimp.dep")
!INCLUDE "oleimp.dep"
!ELSE 
!MESSAGE Warning: cannot find "oleimp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "oleimp - Win64 Release" || "$(CFG)" == "oleimp - Win64 Debug"
SOURCE=.\oleimp.Cpp

"$(INTDIR)\oleimp.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\util.Cpp

"$(INTDIR)\util.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 
