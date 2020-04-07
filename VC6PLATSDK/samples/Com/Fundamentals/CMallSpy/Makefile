
All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f cmallspy64.mak CFG="cmallspy - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f cmallspy64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f cmallspy.mak CFG="cmallspy - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f cmallspy.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF