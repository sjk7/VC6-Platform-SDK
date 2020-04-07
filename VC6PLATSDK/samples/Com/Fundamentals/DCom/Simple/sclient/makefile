


All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f sclient64.mak CFG="sclient - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f sclient64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f sclient.mak CFG="sclient - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f sclient.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF