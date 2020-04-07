# Microsoft Developer Studio Generated NMAKE File, Based on psperflib.dsp
!IF "$(CFG)" == ""
CFG=psperflib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to psperflib - Win32 Debug.
!ENDIF 

!message Setting Target
!IF "$(TARGETOS)" == "WIN95"
MIDL_OPTIMIZATION=-target NT40
!ELSEIF "$(TARGETOS)" == "WINNT"
!IF "$(APPVER)" == "5.0"
MIDL_OPTIMIZATION=-target NT50
!ELSEIF "$(APPVER)" == "5.01"
MIDL_OPTIMIZATION=-target NT51
!ELSEIF "$(APPVER)" == "4.0"
MIDL_OPTIMIZATION=-target NT40
!ENDIF
!ENDIF

!IF ("$(TARGETOS)" == "WINNT" ) && ("$(APPVER)" != "4.0")
MIDL_OPTIMIZATION = $(MIDL_OPTIMIZATION) /robust
!ENDIF

!IF "$(CFG)" != "psperflib - Win32 Release" && "$(CFG)" != "psperflib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "psperflib.mak" CFG="psperflib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "psperflib - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "psperflib - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.
INTDIR=.\ps_Win32\Release\x86
# Begin Custom Macros
OutDir=.
# End Custom Macros

ALL : "$(OUTDIR)\ps_Win32\psperf.tlb"


CLEAN :
	-@erase ".\ps_Win32\psperf.tlb"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

MTL=midl.exe

!IF  "$(CFG)" == "psperflib - Win32 Release"

!ELSEIF  "$(CFG)" == "psperflib - Win32 Debug"

!ENDIF 

MTL_PROJ=/out "ps_Win32" /env win32 $(MIDL_OPTIMIZATION)

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("psperflib.dep")
!INCLUDE "psperflib.dep"
!ELSE 
!MESSAGE Warning: cannot find "psperflib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "psperflib - Win32 Release" || "$(CFG)" == "psperflib - Win32 Debug"
SOURCE=.\psperf.Idl
MTL_SWITCHES=/tlb "$(OUTDIR)\psperf.tlb" /out "ps_Win32" /env win32 $(MIDL_OPTIMIZATION)

".\ps_Win32\psperf.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
        $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

