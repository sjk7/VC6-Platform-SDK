
# Microsoft Developer Studio Generated NMAKE File, Based on psperflib.dsp
!IF "$(CFG)" == ""
CFG=psperflib - Win64 Debug
!MESSAGE No configuration specified. Defaulting to psperflib - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "psperflib - Win64 Release" && "$(CFG)" != "psperflib - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "psperflib64.mak" CFG="psperflib - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "psperflib - Win64 Release" (based on "Win64 (IA64) Generic Project")
!MESSAGE "psperflib - Win64 Debug" (based on "Win64 (IA64) Generic Project")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.
INTDIR=.\ps_Win64\Release\IA64
# Begin Custom Macros
OutDir=.
# End Custom Macros

ALL : "$(OUTDIR)\ps_Win64\psperf.tlb"


CLEAN :
	-@erase ".\ps_Win64\psperf.tlb"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

MTL=midl.exe

!IF  "$(CFG)" == "psperflib - Win64 Release"

!ELSEIF  "$(CFG)" == "psperflib - Win64 Debug"

!ENDIF 

MTL_PROJ=/out "ps_Win64" /env win64 $(MIDL_OPTIMIZATION)

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("psperflib.dep")
!INCLUDE "psperflib.dep"
!ELSE 
!MESSAGE Warning: cannot find "psperflib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "psperflib - Win64 Release" || "$(CFG)" == "psperflib - Win64 Debug"
SOURCE=.\psperf.Idl
MTL_SWITCHES=/tlb "$(OUTDIR)\psperf.tlb" /out "ps_Win64" /env win64 

".\ps_Win64\psperf.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<



!ENDIF 
