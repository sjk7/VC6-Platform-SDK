!include <win32.mak>

!IF "$(CPU)" != "IA64"
!IF "$(MSVCVER)" == "6.0"

All:
!IFDEF NODEBUG
   nmake /f Disp1.mak CFG="Disp1 - Win32 Release MinSize" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f Disp1.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF

!ELSE
!MESSAGE $(VC6MSG)
!ENDIF

!ELSE
!MESSAGE $(WIN64MSG)
!ENDIF
