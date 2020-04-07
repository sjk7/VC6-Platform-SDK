





All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f CallBackClient64.mak CFG="CallBackClient - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f CallBackClient64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f CallBackClient.mak CFG="CallBackClient - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f CallBackClient.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF