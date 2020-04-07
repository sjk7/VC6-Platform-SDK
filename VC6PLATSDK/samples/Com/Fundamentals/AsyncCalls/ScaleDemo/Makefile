





All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f scaledemo64.mak CFG="scaledemo - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f scaledemo64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f scaledemo.mak CFG="scaledemo - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f scaledemo.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF