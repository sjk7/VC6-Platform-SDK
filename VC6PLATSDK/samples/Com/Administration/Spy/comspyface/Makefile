All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f ComSpyFace.mak64 CFG="ComSpyFace - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f ComSpyFace.mak64 -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f ComSpyFace.mak CFG="ComSpyFace - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f ComSpyFace.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF