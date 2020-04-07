









All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f FullSvr64.mak CFG="FullSvr - Win64 Release MinDependency" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f FullSvr64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f FullSvr.mak CFG="FullSvr - Win32 Release MinDependency" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f FullSvr.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF