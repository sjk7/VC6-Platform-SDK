
All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f dog64.mak CFG="dog - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f dog64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f dog.mak CFG="dog - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f dog.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF