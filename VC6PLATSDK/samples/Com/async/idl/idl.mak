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
INTDIR=.\..\ps_win32\Release

ALL : "..\ps_win32\Proxy.tlb"


CLEAN :
	-@erase "..\ps_win32\Proxy.tlb"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

MTL=midl.exe

!IF  "$(CFG)" == "idl - Win32 Release"

!ELSEIF  "$(CFG)" == "idl - Win32 Debug"

!ENDIF 

MTL_PROJ=/out "..\ps_win32" /Oicf /env win32 

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("idl.dep")
!INCLUDE "idl.dep"
!ELSE 
!MESSAGE Warning: cannot find "idl.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "idl - Win32 Release" || "$(CFG)" == "idl - Win32 Debug"
SOURCE=..\proxy\Proxy.idl
MTL_SWITCHES=/tlb "$(OUTDIR)\Proxy.tlb" /out "..\ps_win32" /Oicf /env win32 

"..\ps_win32\Proxy.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<



!ENDIF 

