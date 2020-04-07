
All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f custsur64.mak CFG="custsur - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f custsur64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f custsur.mak CFG="custsur - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f custsur.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF