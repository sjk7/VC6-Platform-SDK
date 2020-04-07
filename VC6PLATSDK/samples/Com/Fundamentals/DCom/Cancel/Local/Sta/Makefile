


All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f sta64.mak CFG="sta - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f sta64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f sta.mak CFG="sta - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f sta.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF