


All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f inproc64.mak CFG="inproc - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f inproc64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f inproc.mak CFG="inproc - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f inproc.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF