



All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f sserver64.mak CFG="sserver - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f sserver64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f sserver.mak CFG="sserver - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f sserver.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF