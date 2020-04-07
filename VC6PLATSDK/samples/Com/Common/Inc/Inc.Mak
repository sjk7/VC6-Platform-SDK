!include <disable.mak>

# Microsoft Developer Studio Generated NMAKE File, Based on Include.dsp
!IF "$(CFG)" == ""
CFG=Inc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Inc - Win32 Debug.
!ENDIF 

!IF "$(PROCESSOR_ARCHITECTURE)" == "ALPHA"
mach_type="ALPHA"
!ELSE
mach_type="I386"
!ENDIF

!IF "$(CFG)" != "Inc - Win32 Release" && "$(CFG)" != "Inc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Include.mak" CFG="Inc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Inc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Inc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Inc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\TxFileDisp_i.c" ".\TxFileDisp.tlb" ".\TxFileDisp.h" ".\rmworker_i.c" ".\rmworker.tlb" ".\rmworker.h" ".\MtsUserEventObj_i.c" ".\MtsUserEventObj.tlb" ".\MtsUserEventObj.h" ".\MtsSpy_i.c" ".\MtsSpy.tlb" ".\MtsSpy.h" ".\MtsAudit_i.c" ".\MtsAudit.tlb" ".\MtsAudit.h" ".\CopyImage_i.c" ".\CopyImage.tlb" ".\CopyImage.h" 


CLEAN :
	-@erase 
	-@erase ".\CopyImage.h"
	-@erase ".\CopyImage.tlb"
	-@erase ".\CopyImage_i.c"
	-@erase ".\MtsAudit.h"
	-@erase ".\MtsAudit.tlb"
	-@erase ".\MtsAudit_i.c"
	-@erase ".\MtsSpy.h"
	-@erase ".\MtsSpy.tlb"
	-@erase ".\MtsSpy_i.c"
	-@erase ".\MtsUserEventObj.h"
	-@erase ".\MtsUserEventObj.tlb"
	-@erase ".\MtsUserEventObj_i.c"
	-@erase ".\rmworker.h"
	-@erase ".\rmworker.tlb"
	-@erase ".\rmworker_i.c"
	-@erase ".\TxFileDisp.h"
	-@erase ".\TxFileDisp.tlb"
	-@erase ".\TxFileDisp_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\Include.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Include.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Include.pdb" /machine:$(mach_type) /out:"$(OUTDIR)\Include.exe" 
LINK32_OBJS= \
	

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\TxFileDisp_i.c" ".\TxFileDisp.tlb" ".\TxFileDisp.h" ".\rmworker_i.c" ".\rmworker.tlb" ".\rmworker.h" ".\MtsUserEventObj_i.c" ".\MtsUserEventObj.tlb" ".\MtsUserEventObj.h" ".\MtsSpy_i.c" ".\MtsSpy.tlb" ".\MtsSpy.h" ".\MtsAudit_i.c" ".\MtsAudit.tlb" ".\MtsAudit.h" ".\CopyImage_i.c" ".\CopyImage.tlb" ".\CopyImage.h" 


CLEAN :
	-@erase 
	-@erase ".\CopyImage.h"
	-@erase ".\CopyImage.tlb"
	-@erase ".\CopyImage_i.c"
	-@erase ".\MtsAudit.h"
	-@erase ".\MtsAudit.tlb"
	-@erase ".\MtsAudit_i.c"
	-@erase ".\MtsSpy.h"
	-@erase ".\MtsSpy.tlb"
	-@erase ".\MtsSpy_i.c"
	-@erase ".\MtsUserEventObj.h"
	-@erase ".\MtsUserEventObj.tlb"
	-@erase ".\MtsUserEventObj_i.c"
	-@erase ".\rmworker.h"
	-@erase ".\rmworker.tlb"
	-@erase ".\rmworker_i.c"
	-@erase ".\TxFileDisp.h"
	-@erase ".\TxFileDisp.tlb"
	-@erase ".\TxFileDisp_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\Include.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 $(MIDL_OPTIMIZATION)
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Include.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Include.pdb" /debug /machine:$(mach_type) /out:"$(OUTDIR)\Include.exe" /pdbtype:sept 
LINK32_OBJS= \
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Include.dep")
!INCLUDE "Include.dep"
!ELSE 
!MESSAGE Warning: cannot find "Include.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Inc - Win32 Release" || "$(CFG)" == "Inc - Win32 Debug"
SOURCE=.\CpyImage.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

InputPath=.\CpyImage.idl

".\CopyImage.h"	".\CopyImage_i.c"	".\CopyImage.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\CpyImage.h" /tlb ".\CpyImage.tlb" /iid   ".\CpyImage_i.c"    "CpyImage.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

InputPath=.\CpyImage.idl

".\CopyImage.h"	".\CopyImage_i.c"	".\CopyImage.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\CpyImage.h" /tlb ".\CpyImage.tlb" /iid   ".\CpyImage_i.c"    "CpyImage.idl"
<< 
	

!ENDIF 

SOURCE=.\MtsAudit.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

InputPath=.\MtsAudit.idl

".\MtsAudit.h"	".\MtsAudit_i.c"	".\MtsAudit.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\MtsAudit.h" /tlb ".\MtsAudit.tlb" /iid   ".\MtsAudit_i.c"    "MtsAudit.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

InputPath=.\MtsAudit.idl

".\MtsAudit.h"	".\MtsAudit_i.c"	".\MtsAudit.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\MtsAudit.h" /tlb ".\MtsAudit.tlb" /iid   ".\MtsAudit_i.c"    "MtsAudit.idl"
<< 
	

!ENDIF 

SOURCE=.\MtsSpyCtl.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

InputPath=.\MtsSpyCtl.idl

".\MtsSpy.h"	".\MtsSpy_i.c"	".\MtsSpy.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\MtsSpyCtl.h" /tlb ".\MtsSpyCtl.tlb" /iid   ".\MtsSpyCtl_i.c"    "MtsSpyCtl.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

InputPath=.\MtsSpyCtl.idl

".\MtsSpy.h"	".\MtsSpy_i.c"	".\MtsSpy.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\MtsSpyCtl.h" /tlb ".\MtsSpyCtl.tlb" /iid   ".\MtsSpyCtl_i.c"    "MtsSpyCtl.idl"
<< 
	

!ENDIF 

SOURCE=.\MtsUserEventObj.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

InputPath=.\MtsUserEventObj.idl

".\MtsUserEventObj.h"	".\MtsUserEventObj.tlb"	".\MtsUserEventObj_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\MtsUserEventObj.h" /tlb ".\MtsUserEventObj.tlb"   /iid   ".\MtsUserEventObj_i.c"  "MtsUserEventObj.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

InputPath=.\MtsUserEventObj.idl

".\MtsUserEventObj.h"	".\MtsUserEventObj.tlb"	".\MtsUserEventObj_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\MtsUserEventObj.h" /tlb ".\MtsUserEventObj.tlb"   /iid   ".\MtsUserEventObj_i.c"  "MtsUserEventObj.idl"
<< 
	

!ENDIF 

SOURCE=.\RmWorker.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

InputPath=.\RmWorker.idl

".\rmworker.h"	".\rmworker.tlb"	".\rmworker_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\RmWorker.h" /tlb ".\RmWorker.tlb" /iid   ".\RmWorker_i.c"    "RmWorker.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

InputPath=.\RmWorker.idl

".\rmworker.h"	".\rmworker.tlb"	".\rmworker_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\RmWorker.h" /tlb ".\RmWorker.tlb" /iid   ".\RmWorker_i.c"    "RmWorker.idl"
<< 
	

!ENDIF 

SOURCE=.\TxFileDisp.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

InputPath=.\TxFileDisp.idl

".\TxFileDisp.h"	".\TxFileDisp_i.c"	".\TxFileDisp.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\TxFileDisp.h" /tlb ".\TxFileDisp.tlb" /iid     ".\TxFileDisp_i.c"  "TxFileDisp.idl"
<< 
	

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

InputPath=.\TxFileDisp.idl

".\TxFileDisp.h"	".\TxFileDisp_i.c"	".\TxFileDisp.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h ".\TxFileDisp.h" /tlb ".\TxFileDisp.tlb" /iid     ".\TxFileDisp_i.c"  "TxFileDisp.idl"
<< 
	

!ENDIF 


!ENDIF 

