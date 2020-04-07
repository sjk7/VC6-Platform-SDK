


All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f Proxy64.mak CFG="proxy - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f Proxy64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f Proxy.mak CFG="proxy - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f Proxy.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF