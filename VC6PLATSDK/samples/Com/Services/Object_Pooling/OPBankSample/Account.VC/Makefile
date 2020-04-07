!if "$(CPU)" == "IA64"
!message Sorry building this sample for 64bit is not currently supported.
!else
All:
!IFDEF NODEBUG
   nmake /f account.mak CFG="account - Win32 Release MinSize" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f account.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF

!endif
