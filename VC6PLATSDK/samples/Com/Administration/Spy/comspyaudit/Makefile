All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f ComSpyAudit64.mak CFG="ComSpyAudit - Win64 Unicode Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f ComSpyAudit64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f ComSpyAudit.mak CFG="ComSpyAudit - Win32 Unicode Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f ComSpyAudit.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF