# Microsoft Developer Studio Generated NMAKE File, Based on idl.dsp
!IF "$(CFG)" == ""
CFG=idl - Win32 Debug
!MESSAGE No configuration specified. Defaulting to idl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "idl - Win32 Release" && "$(CFG)" != "idl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "idl.mak" CFG="idl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "idl - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "idl - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.
INTDIR=.\ps_Win32\Release
# Begin Custom Macros
OutDir=.
# End Custom Macros

ALL : "$(OUTDIR)\ps_Win32\ComSpy.tlb" "$(OUTDIR)\ps_Win32\ComSpyAudit.tlb" "$(OUTDIR)\ps_Win32\ComSpyCtl.tlb"


CLEAN :
	-@erase ".\ps_Win32\ComSpy.tlb"
	-@erase ".\ps_Win32\ComSpyAudit.tlb"
	-@erase ".\ps_Win32\ComSpyCtl.tlb"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

!IF  "$(CFG)" == "idl - Win32 Release"

MTL=midl.exe
MTL_PROJ=/out "ps_Win32" /env win32 

!ELSEIF  "$(CFG)" == "idl - Win32 Debug"

MTL=midl.exe
MTL_PROJ=/out "ps_win32" /env win32 

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("idl.dep")
!INCLUDE "idl.dep"
!ELSE 
!MESSAGE Warning: cannot find "idl.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "idl - Win32 Release" || "$(CFG)" == "idl - Win32 Debug"
SOURCE=..\ComSpy\ComSpy.idl

!IF  "$(CFG)" == "idl - Win32 Release"

MTL_SWITCHES=/tlb "$(OUTDIR)\ComSpy.tlb" /out "ps_Win32" /env win32 

".\ps_Win32\ComSpy.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "idl - Win32 Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\ComSpy.tlb" /out "ps_win32" /env win32 

".\ps_Win32\ComSpy.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ComSpyAudit.idl

!IF  "$(CFG)" == "idl - Win32 Release"

MTL_SWITCHES=/tlb "$(OUTDIR)\ComSpyAudit.tlb" /out "ps_Win32" /env win32 

".\ps_Win32\ComSpyAudit.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "idl - Win32 Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\ComSpyAudit.tlb" /out "ps_win32" /env win32 

".\ps_Win32\ComSpyAudit.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ComSpyCtl.idl

!IF  "$(CFG)" == "idl - Win32 Release"

MTL_SWITCHES=/tlb "$(OUTDIR)\ComSpyCtl.tlb" /out "ps_Win32" /env win32 

".\ps_Win32\ComSpyCtl.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "idl - Win32 Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\ComSpyCtl.tlb" /out "ps_win32" /env win32 

".\ps_Win32\ComSpyCtl.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

