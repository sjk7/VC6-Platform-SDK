





All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f Fullsrvps64.mak CFG="FullSrvps - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f Fullsrvps64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f Fullsrvps.mak CFG="FullSrvps - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f Fullsrvps.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF