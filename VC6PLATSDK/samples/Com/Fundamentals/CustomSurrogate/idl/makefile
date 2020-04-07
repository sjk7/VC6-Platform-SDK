
All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f idl64.mak CFG="idl - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f idl64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f idl.mak CFG="idl - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f idl.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF