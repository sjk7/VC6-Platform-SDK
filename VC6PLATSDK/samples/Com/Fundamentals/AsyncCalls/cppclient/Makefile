





All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f CppClient64.mak CFG="CppClient - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f CppClient64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f CppClient.mak CFG="CppClient - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f CppClient.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF