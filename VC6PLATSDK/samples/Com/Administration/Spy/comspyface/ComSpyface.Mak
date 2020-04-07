# Microsoft Developer Studio Generated NMAKE File, Based on ComSpyFace.dsp
!IF "$(CFG)" == ""
CFG=ComSpyFace - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ComSpyFace - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ComSpyFace - Win32 Release" && "$(CFG)" != "ComSpyFace - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComSpyFace.mak" CFG="ComSpyFace - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComSpyFace - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "ComSpyFace - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

ALL : "$(OUTDIR)\ComSpyAudit.tlb" "$(OUTDIR)\ComSpyCtl.tlb"


CLEAN :
	-@erase "$(INTDIR)\ComSpyAudit.tlb"
	-@erase "$(INTDIR)\ComSpyCtl.tlb"

!IF  "$(CFG)" == "ComSpyFace - Win32 Release"

MTL=midl.exe
MTL_PROJ=

!ELSEIF  "$(CFG)" == "ComSpyFace - Win32 Debug"

MTL=midl.exe
MTL_PROJ=/D "_DEBUG" 

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ComSpyFace.dep")
!INCLUDE "ComSpyFace.dep"
!ELSE 
!MESSAGE Warning: cannot find "ComSpyFace.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ComSpyFace - Win32 Release" || "$(CFG)" == "ComSpyFace - Win32 Debug"
SOURCE=.\ComSpyAudit.idl

!IF  "$(CFG)" == "ComSpyFace - Win32 Release"

MTL_SWITCHES=/tlb "$(OUTDIR)\ComSpyAudit.tlb" 

"$(INTDIR)\ComSpyAudit.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSpyFace - Win32 Debug"

MTL_SWITCHES=/D "_DEBUG" /tlb "$(OUTDIR)\ComSpyAudit.tlb" 

"$(INTDIR)\ComSpyAudit.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ComSpyCtl.idl

!IF  "$(CFG)" == "ComSpyFace - Win32 Release"

MTL_SWITCHES=/tlb "$(OUTDIR)\ComSpyCtl.tlb" 

"$(INTDIR)\ComSpyCtl.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ComSpyFace - Win32 Debug"

MTL_SWITCHES=/D "_DEBUG" /tlb "$(OUTDIR)\ComSpyCtl.tlb" 

"$(INTDIR)\ComSpyCtl.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

