

All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f client64.mak CFG="client - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f client64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f client.mak CFG="client - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f client.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF