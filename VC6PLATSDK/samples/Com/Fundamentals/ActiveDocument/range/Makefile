
All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f range64.mak CFG="range - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f range64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f range.mak CFG="range - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f range.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF