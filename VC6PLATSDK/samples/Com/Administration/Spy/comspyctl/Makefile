All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f ComSpyCtl64.mak CFG="ComSpyCtl - Win64 Unicode Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f ComSpyCtl64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f ComSpyCtl.mak CFG="ComSpyCtl - Win32 Unicode Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f ComSpyCtl.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF