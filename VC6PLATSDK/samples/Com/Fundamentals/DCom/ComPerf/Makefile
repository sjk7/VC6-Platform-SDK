



All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f comperf64.mak CFG="comperf - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f comperf64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f comperf.mak CFG="comperf - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f comperf.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF