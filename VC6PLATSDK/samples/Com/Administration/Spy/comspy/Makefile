All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f ComSpy64.mak CFG="ComSpy - Win64 Unicode Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f ComSpy64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f ComSpy.mak CFG="ComSpy - Win32 Unicode Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f ComSpy.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF