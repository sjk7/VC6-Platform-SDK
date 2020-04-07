
# Microsoft Developer Studio Generated NMAKE File, Based on idl.dsp
!IF "$(CFG)" == ""
CFG=idl - Win64 Debug
!MESSAGE No configuration specified. Defaulting to idl - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "idl - Win64 Release" && "$(CFG)" != "idl - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "idl64.mak" CFG="idl - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "idl - Win64 Release" (based on "Win64 (IA64) Generic Project")
!MESSAGE "idl - Win64 Debug" (based on "Win64 (IA64) Generic Project")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.
INTDIR=.\ps_Win64\Release
# Begin Custom Macros
OutDir=.
# End Custom Macros

ALL : "$(OUTDIR)\ps_win64\FullSvr.tlb"


CLEAN :
	-@erase ".\ps_win64\FullSvr.tlb"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

MTL=midl.exe

!IF  "$(CFG)" == "idl - Win64 Release"

!ELSEIF  "$(CFG)" == "idl - Win64 Debug"

!ENDIF 

MTL_PROJ=/out "ps_win64" /Oicf /env win64 $(MIDL_OPTIMIZATION)

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("idl.dep")
!INCLUDE "idl.dep"
!ELSE 
!MESSAGE Warning: cannot find "idl.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "idl - Win64 Release" || "$(CFG)" == "idl - Win64 Debug"
SOURCE=..\FullSvr\FullSvr.idl

!IF  "$(CFG)" == "idl - Win64 Release"

MTL_SWITCHES=/tlb "$(OUTDIR)\FullSvr.tlb" /out "ps_win64" /Oicf /env win64 

".\ps_win64\FullSvr.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "idl - Win64 Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\FullSvr.tlb" /out "ps_win64" /Oicf /env win64 

".\ps_win64\FullSvr.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 
