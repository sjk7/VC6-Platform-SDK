


All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f mta64.mak CFG="mta - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f mta64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f mta.mak CFG="mta - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f mta.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF