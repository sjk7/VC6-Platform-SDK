



All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f cancel64.mak CFG="cancel - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f cancel64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f cancel.mak CFG="cancel - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f cancel.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF