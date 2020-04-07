
All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f dogps64.mak CFG="dogps - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f dogps64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f dogps.mak CFG="dogps - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f dogps.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF